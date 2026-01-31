// This has been adapted from the Vulkan tutorial
#include <sstream>
#include <iomanip>
#include <json.hpp>
#include <list>
#include <deque>

#include "modules/Starter.hpp"
#include "modules/TextMaker.hpp"
#include "modules/Scene.hpp"
#include "modules/Animations.hpp"

#include "MapManager.hpp"
#include "CollisionBox.hpp"
#include "CollisionBoxGenerator.hpp"
#include "Teleporter.hpp"
#include "TeleporterList.hpp"

// The uniform buffer object used in this example
struct VertexChar {
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 UV;
    glm::uvec4 jointIndices;
    glm::vec4 weights;
};

struct VertexSimp {
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 UV;
};

struct skyBoxVertex {
    glm::vec3 pos;
};

struct VertexTan {
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 UV;
    glm::vec4 tan;
};

struct GlobalUniformBufferObject {
    alignas(16) glm::vec3 lightDir;
    alignas(16) glm::vec4 lightColor;
    alignas(16) glm::vec3 eyePos;
    alignas(4) float time; //Wind animation
};

struct UniformBufferObjectChar {
    alignas(16) glm::vec4 debug1;
    alignas(16) glm::mat4 mvpMat[65];
    alignas(16) glm::mat4 mMat[65];
    alignas(16) glm::mat4 nMat[65];
};

struct UniformBufferObjectSimp {
    alignas(16) glm::mat4 mvpMat;
    alignas(16) glm::mat4 mMat;
    alignas(16) glm::mat4 nMat;
};

struct skyBoxUniformBufferObject {
    alignas(16) glm::mat4 mvpMat;
    alignas(16) glm::vec4 settings; // x = blendFactor (0 night , 1 day)
};

// Matches the GLSL structure for std140 alignment
struct PointLight {
    alignas(16) glm::vec3 position;
    alignas(16) glm::vec3 color;
};

struct PointLightBufferObject {
    PointLight lights[100];
    int numActiveLights;
};

// MAIN !
class E09 : public BaseProject {
private:
    std::vector<CollisionObject> houseCollisions;
    std::vector<Teleporter*> teleporters;
    Teleporter* activeTeleporter;
    std::deque<int> path;

    float getGroundHeight(const glm::vec3& pos);

    // --- WELL ANIMATION SETTINGS ---
    enum WellState { W_IDLE, W_DOWN, W_UP };

    WellState currentWellState = W_IDLE;

    // 1. CONSTANTS
    const float BEAM_Y = 1.85f; // Fixed height of the support beam
    const float HANDLE_OFFSET = 0.18f; // Distance to subtract from bucket center to reach handle

    // 2. DYNAMIC COORDINATES
    float bucketAnimY = 1.14f; // Current Y position of the bucket
    float ropeAnimY = 1.14f; // Separate Y tracker for the rope (for calibration)
    float maskOffset = 0.06f; // Offset for the water surface mask

    // 3. SEPARATED SPEEDS (Tune these to prevent detachments)
    float bucketDescSpeed = 0.5f; // Descending speed for the bucket
    float ropeDescSpeed = 1.0f; // Descending speed for the rope (Adjust if it leads/lags)

    float bucketAscSpeed = 0.8f; // Ascending speed for the bucket
    float ropeAscSpeed = 1.6f; // Ascending speed for the rope (Adjust if it leads/lags)

    float wellBottomLimit = -2.0f;
    bool wellDebounce = false; // Input debounce for the 'E' key

    // 4. SPLASH ANIMATION SETTINGS
    const float WATER_LEVEL = 0.0f; // Y level where splashes occur
    float splashJump[8] = {0.0f}; // Current vertical offset for each cube

    // 5. BUCKET SWAP SETTINGS
    bool bucketIsOnGround = false; // Logic flag: is the full bucket near the well?
    glm::vec3 groundedBucketPos = glm::vec3(1.2f, 0.3f, 0.0f); // Where the full bucket "spawns"

protected:
    PointLightBufferObject plboData;
    // Here you list all the Vulkan objects you need:

    // Descriptor Layouts [what will be passed to the shaders]
    DescriptorSetLayout DSLlocalChar, DSLlocalSimp, DSLlocalPBR, DSLglobal, DSLskyBox;
    DescriptorSetLayout DSLveg; // Layout for vegetation
    DescriptorSetLayout DSLdebug; //Layout for collision box

    // Vertex formants, Pipelines [Shader couples] and Render passes
    VertexDescriptor VDchar;
    VertexDescriptor VDsimp;
    VertexDescriptor VDskyBox;
    VertexDescriptor VDtan;
    RenderPass RP;
    Pipeline Pchar, PsimpObj, PskyBox, P_PBR;
    Pipeline Pveg; // Pipeline for vegetation rendering
    Pipeline Pdebug; // Pipeline for rendering of collision box
    //*DBG*/Pipeline PDebug;

    // Models, textures and Descriptors (values assigned to the uniforms)
    Scene SC;
    std::vector<VertexDescriptorRef> VDRs;
    std::vector<TechniqueRef> PRs;
    //*DBG*/Model MS;
    //*DBG*/DescriptorSet SSD;

    // To support animation
#define N_ANIMATIONS 5

    AnimBlender AB;
    Animations Anim[N_ANIMATIONS];
    SkeletalAnimation SKA;

    // to provide textual feedback
    TextMaker txt;

    // Other application parameters
    float Ar; // Aspect ratio

    glm::mat4 ViewPrj;
    glm::mat4 World;
    glm::vec3 Pos = glm::vec3(370, 0, -90);
    glm::vec3 cameraPos;
    float Yaw = glm::radians(0.0f);
    float Pitch = glm::radians(0.0f);
    float Roll = glm::radians(0.0f);
    float characterRotation = glm::radians(0.0f);

    //CAM VARIABLE
    bool isFirstPerson = false; //State of the cam
    bool c_pressed = false; //Debounce c clicked
    bool isWideView = false;
    bool v_pressed = false;
    bool canTeleport = false;
    float currentCamDist = 5.0f;
    bool resetCamera = false; //Flag to reset the camera

    //WINDOW VARIABLE
    bool f11_pressed = false;
    bool isFullScreen = false;
    //Save old window position
    int savedWindowX = 0;
    int savedWindowY = 0;
    int savedWindowW = 800;
    int savedWindowH = 600;

    //TPV VARIABLE
    bool walking = false;
    bool running = false;

    //MOUSE VARIABLE
    double lastX;
    double lastY;
    bool firstMouse = true; //Avoids crazy movements at the beginning
    float mouseSensitivity = 0.1f; //Mouse sensibility

    //Player state variables
    glm::vec3 oldPos;
    int currRunState = 1;
    float relDir = glm::radians(0.0f);
    float dampedRelDir = glm::radians(0.0f);
    glm::vec3 dampedCamPos = glm::vec3(0.0, 0.0, 5); //Initialize StartingPosition
    glm::vec4 debug1 = glm::vec4(0);

    // Here you set the main application parameters
    void setWindowParameters() {
        // window size, titile and initial background
        windowWidth = 800;
        windowHeight = 600;
        windowTitle = "E09 - Showing animations";
        windowResizable = GLFW_TRUE;

        // Initial aspect ratioF
        Ar = 4.0f / 3.0f;
    }

    // What to do when the window changes size
    void onWindowResize(int w, int h) {
        std::cout << "Window resized to: " << w << " x " << h << "\n";
        Ar = (float) w / (float) h;
        // Update Render Pass
        RP.width = w;
        RP.height = h;

        // updates the textual output
        txt.resizeScreen(w, h);
    }

    // Here you load and setup all your Vulkan Models and Texutures.
    // Here you also create your Descriptor set layouts and load the shaders for the pipelines
    // Here you load and setup all your Vulkan Models and Texutures.
    // Here you also create your Descriptor set layouts and load the shaders for the pipelines
    void localInit() {
        // Hides the mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // Force the mouse position at the center
        lastX = windowWidth / 2.0;
        lastY = windowHeight / 2.0;
        firstMouse = true;

        for (auto& [id, info] : TeleporterList::teleporters) {
            teleporters.push_back(info.teleporter.get());
        }

        // Descriptor Layouts [what will be passed to the shaders]
        // Initialize the global Descriptor Set Layout
        // Binding 0: Sun/Global data
        // Binding 3: Array of 50 Point Lights for the lamps
        DSLglobal.init(this, {
                           {
                               0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS,
                               sizeof(GlobalUniformBufferObject), 1
                           },
                           {
                               1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, // CAMBIATO DA 3 A 1
                               sizeof(PointLightBufferObject), 1
                           }
                       });

        DSLlocalChar.init(this, {
                              // this array contains the binding:
                              // first  element : the binding number
                              // second element : the type of element (buffer or texture)
                              // third  element : the pipeline stage where it will be used
                              {
                                  0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT,
                                  sizeof(UniformBufferObjectChar), 1
                              },
                              {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1}
                          });

        DSLlocalSimp.init(this, {
                              // this array contains the binding:
                              // first  element : the binding number
                              // second element : the type of element (buffer or texture)
                              // third  element : the pipeline stage where it will be used
                              {
                                  0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT,
                                  sizeof(UniformBufferObjectSimp), 1
                              },
                              {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1},
                              {2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 1, 1}
                          });

        DSLskyBox.init(this, {
                           // Binding 0: Uniform Buffer (dati ciclo giorno/notte)
                           {
                               0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                               VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                               sizeof(skyBoxUniformBufferObject), 1
                           },

                           // Binding 1: Texture Giorno (UNICA TEXTURE)
                           {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1}
                       });

        DSLlocalPBR.init(this, {
                             // this array contains the binding:
                             // first  element : the binding number
                             // second element : the type of element (buffer or texture)
                             // third  element : the pipeline stage where it will be used
                             {
                                 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT,
                                 sizeof(UniformBufferObjectSimp), 1
                             },
                             {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1},
                             {2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 1, 1},
                             {3, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 2, 1},
                             {4, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 3, 1}
                         });

        DSLveg.init(this, {
                        // Binding 0: Uniform Buffer (Matrices)
                        {
                            0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT,
                            sizeof(UniformBufferObjectSimp), 1
                        },
                        // Binding 1: Texture (Albedo/Color) - Fragment Shader
                        {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1},
                        // Binding 2: Texture (Noise) - Used in Vertex or Fragment
                        {
                            2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 1, 1
                        }
                    });

        DSLdebug.init(this, {
                          {
                              0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT,
                              sizeof(UniformBufferObjectSimp), 1
                          },
                          {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1},
                          // Binding 2: Texture (Noise) - Used in Vertex or Fragment

                      });

        VDchar.init(this, {
                        {0, sizeof(VertexChar), VK_VERTEX_INPUT_RATE_VERTEX}
                    }, {
                        {
                            0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexChar, pos),
                            sizeof(glm::vec3), POSITION
                        },
                        {
                            0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexChar, norm),
                            sizeof(glm::vec3), NORMAL
                        },
                        {
                            0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexChar, UV),
                            sizeof(glm::vec2), UV
                        },
                        {
                            0, 3, VK_FORMAT_R32G32B32A32_UINT, offsetof(VertexChar, jointIndices),
                            sizeof(glm::uvec4), JOINTINDEX
                        },
                        {
                            0, 4, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(VertexChar, weights),
                            sizeof(glm::vec4), JOINTWEIGHT
                        }
                    });

        VDsimp.init(this, {
                        {0, sizeof(VertexSimp), VK_VERTEX_INPUT_RATE_VERTEX}
                    }, {
                        {
                            0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexSimp, pos),
                            sizeof(glm::vec3), POSITION
                        },
                        {
                            0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexSimp, norm),
                            sizeof(glm::vec3), NORMAL
                        },
                        {
                            0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexSimp, UV),
                            sizeof(glm::vec2), UV
                        }
                    });

        VDskyBox.init(this, {
                          {0, sizeof(skyBoxVertex), VK_VERTEX_INPUT_RATE_VERTEX}
                      }, {
                          {
                              0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(skyBoxVertex, pos),
                              sizeof(glm::vec3), POSITION
                          }
                      });

        VDtan.init(this, {
                       {0, sizeof(VertexTan), VK_VERTEX_INPUT_RATE_VERTEX}
                   }, {
                       {
                           0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexTan, pos),
                           sizeof(glm::vec3), POSITION
                       },
                       {
                           0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexTan, norm),
                           sizeof(glm::vec3), NORMAL
                       },
                       {
                           0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexTan, UV),
                           sizeof(glm::vec2), UV
                       },
                       {
                           0, 3, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(VertexTan, tan),
                           sizeof(glm::vec4), TANGENT
                       }
                   });

        VDRs.resize(4);
        VDRs[0].init("VDchar", &VDchar);
        VDRs[1].init("VDsimp", &VDsimp);
        VDRs[2].init("VDskybox", &VDskyBox);
        VDRs[3].init("VDtan", &VDtan);

        // initializes the render passes
        RP.init(this);
        // sets the blue sky
        RP.properties[0].clearValue = {0.0f, 0.9f, 1.0f, 1.0f};


        // Pipelines [Shader couples]
        // The last array, is a vector of pointer to the layouts of the sets that will
        // be used in this pipeline. The first element will be set 0, and so on..
        Pchar.init(this, &VDchar, "shaders/PosNormUvTanWeights.vert.spv", "shaders/CookTorranceForCharacter.frag.spv",
                   {&DSLglobal, &DSLlocalChar});

        PsimpObj.init(this, &VDsimp, "shaders/SimplePosNormUV.vert.spv", "shaders/CookTorrance.frag.spv",
                      {&DSLglobal, &DSLlocalSimp});

        PsimpObj.setCullMode(VK_CULL_MODE_BACK_BIT);

        PskyBox.init(this, &VDskyBox, "shaders/SkyBoxShader.vert.spv", "shaders/SkyBoxShader.frag.spv", {&DSLskyBox});
        PskyBox.setCompareOp(VK_COMPARE_OP_LESS_OR_EQUAL);
        PskyBox.setCullMode(VK_CULL_MODE_BACK_BIT);
        PskyBox.setPolygonMode(VK_POLYGON_MODE_FILL);

        P_PBR.init(this, &VDtan, "shaders/SimplePosNormUvTan.vert.spv", "shaders/PBR.frag.spv",
                   {&DSLglobal, &DSLlocalPBR});

        Pveg.init(this, &VDsimp, "shaders/Vegetation.vert.spv", "shaders/Vegetation.frag.spv", {&DSLglobal, &DSLveg});
        Pveg.setCullMode(VK_CULL_MODE_NONE);
        Pveg.setPolygonMode(VK_POLYGON_MODE_FILL);

        Pdebug.init(this, &VDsimp, "shaders/SimplePosNormUV.vert.spv", "shaders/CookTorrance.frag.spv",
                    {&DSLglobal, &DSLdebug});
        Pdebug.setPolygonMode(VK_POLYGON_MODE_FILL);

        PRs.resize(5);
        PRs[0].init("CookTorranceChar", {
                        {
                            &Pchar, {
                                //Pipeline and DSL for the first pass
                                /*DSLglobal*/{},
                                /*DSLlocalChar*/{
                                    /*t0*/{true, 0, {}} // index 0 of the "texture" field in the json file
                                }
                            }
                        }
                    }, /*TotalNtextures*/1, &VDchar);
        PRs[1].init("CookTorranceNoiseSimp", {
                        {
                            &PsimpObj, {
                                //Pipeline and DSL for the first pass
                                /*DSLglobal*/{},
                                /*DSLlocalSimp*/{
                                    /*t0*/{true, 0, {}}, // index 0 of the "texture" field in the json file
                                    /*t1*/{true, 1, {}} // index 1 of the "texture" field in the json file
                                }
                            }
                        }
                    }, /*TotalNtextures*/2, &VDsimp);
        PRs[2].init("SkyBox", {
                        {
                            &PskyBox, {
                                /*DSLskyBox*/{
                                    {true, 0, {}}, // Refers to the UBO
                                    {true, 0, {}}, // Refers to Texture index 0 in JSON (Day)
                                }
                            }
                        }
                    }, 1, &VDskyBox); // IMPORTANT: Changed TotalNtextures from 1 to
        PRs[3].init("Vegetation", {
                        {
                            &Pveg, {
                                // Use the vegetation pipeline
                                /*DSLglobal*/ {},
                                /*DSLlocal*/ {
                                    {true, 0, {}}, // Texture 0: Albedo (Tree/Bush)
                                    {true, 1, {}}, // Texture 1: Noise (for Wind)
                                }
                            }
                        }
                    }, 2, &VDsimp); // Uses 2 textures total

        PRs[4].init("DebugCollisionBoxes", {
                        {
                            &Pdebug, {
                                // Puoi usare PsimpObj o una pipeline dedicata wireframe
                                {}, // DSLglobal
                                {{true, 0, {}}, {true, 1, {}}} // DSLlocalSimp (Binding 0 e 1)
                            }
                        }
                    }, 2, &VDsimp);

        // Uses 2 textures total
        // Models, textures and Descriptors (values assigned to the uniforms)

        // sets the size of the Descriptor Set Pool
        DPSZs.uniformBlocksInPool = 2000;
        DPSZs.texturesInPool = 2000;
        DPSZs.setsInPool = 2000;

        std::cout << "\nLoading the scene\n\n";
        if (SC.init(this, /*Npasses*/1, VDRs, PRs, "assets/models/scene.json") != 0) {
            std::cout << "ERROR LOADING THE SCENE\n";
            exit(0);
        }

        //initialize collision box
        houseCollisions = CollisionBoxGenerator::collisions;

        // initializes animations
        for (int ian = 0; ian < N_ANIMATIONS; ian++) {
            Anim[ian].init(*SC.As[ian]);
        }
        AB.init({{0, 32, 0.0f, 0}, {0, 16, 0.0f, 1}, {0, 263, 0.0f, 2}, {0, 83, 0.0f, 3}, {0, 16, 0.0f, 4}});
        //AB.init({{0,31,0.0f}});
        SKA.init(Anim, 5, "Armature|mixamo.com|Layer0", 0);

        // initializes the textual output
        txt.init(this, windowWidth, windowHeight);

        // submits the main command buffer
        submitCommandBuffer("main", 0, populateCommandBufferAccess, this);

        // Prepares for showing the FPS count
        txt.print(1.0f, 1.0f, "FPS:", 1, "CO", false, false, true, TAL_RIGHT, TRH_RIGHT, TRV_BOTTOM,
                  {1.0f, 0.0f, 0.0f, 1.0f}, {0.8f, 0.8f, 0.0f, 1.0f});

        //Text to indicate current visual mode
        txt.print(-1.0f, -1.0f, "View: Third Person (Press C)", 2, "CO",
                  false, false, true, TAL_LEFT, TRH_LEFT, TRV_TOP,
                  {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});

        //Define the FPV crosshair
        txt.print(0.0f, 0.0f, "+", 3, "CO",
                  false, false, true, TAL_CENTER, TRH_CENTER, TRV_MIDDLE,
                  {1.0f, 1.0f, 1.0f, 1.0f}, // Colour: White
                  {0.0f, 0.0f, 0.0f, 1.0f}); // Border: Black

        // --- POINT LIGHTS SETUP ---
        plboData.numActiveLights = 0;
        for (int i = 0; i < SC.TI[1].InstanceCount; i++) {
            auto &inst = SC.TI[1].I[i];
            if (inst.id->find("lamp") != std::string::npos && plboData.numActiveLights < 100) {
                plboData.lights[plboData.numActiveLights].position = glm::vec3(inst.Wm[3][0], 4.5f, inst.Wm[3][2]);
                plboData.lights[plboData.numActiveLights].color = glm::vec3(1.0f, 0.7f, 0.4f);
                plboData.numActiveLights++;
            }
        }
        std::cout << "[Light Setup] Found " << plboData.numActiveLights << " lamps in the scene." << std::endl;
    }

    // Here you create your pipelines and Descriptor Sets!
    void pipelinesAndDescriptorSetsInit() {
        // creates the render pass
        RP.create();

        // This creates a new pipeline (with the current surface), using its shaders for the provided render pass
        Pchar.create(&RP);
        PsimpObj.create(&RP);
        PskyBox.create(&RP);
        P_PBR.create(&RP);

        Pveg.create(&RP); // Create the vegetation pipeline
        Pdebug.create(&RP); //Create the debug pipeline

        SC.pipelinesAndDescriptorSetsInit();
        txt.pipelinesAndDescriptorSetsInit();
    }

    // Here you destroy your pipelines and Descriptor Sets!
    void pipelinesAndDescriptorSetsCleanup() {
        Pchar.cleanup();
        PsimpObj.cleanup();
        PskyBox.cleanup();
        P_PBR.cleanup();

        Pveg.cleanup(); //Cleanup vegetation pipeline
        Pdebug.cleanup(); //Cleanup debug pipeline

        RP.cleanup();

        SC.pipelinesAndDescriptorSetsCleanup();
        txt.pipelinesAndDescriptorSetsCleanup();
    }

    // Here you destroy all the Models, Texture and Desc. Set Layouts you created!
    // You also have to destroy the pipelines
    void localCleanup() {
        DSLlocalChar.cleanup();
        DSLlocalSimp.cleanup();
        DSLlocalPBR.cleanup();
        DSLskyBox.cleanup();

        DSLveg.cleanup(); // Destroy layout

        DSLdebug.cleanup();

        DSLglobal.cleanup();

        Pchar.destroy();
        PsimpObj.destroy();
        PskyBox.destroy();
        P_PBR.destroy();

        Pveg.destroy(); // Destroy pipeline object
        Pdebug.destroy();

        RP.destroy();

        SC.localCleanup();
        txt.localCleanup();

        for (int ian = 0; ian < N_ANIMATIONS; ian++) {
            Anim[ian].cleanup();
        }
    }

    // Here it is the creation of the command buffer:
    // You send to the GPU all the objects you want to draw,
    // with their buffers and textures
    static void populateCommandBufferAccess(VkCommandBuffer commandBuffer, int currentImage, void *Params) {
        // Simple trick to avoid having always 'T->'
        // in che code that populates the command buffer!
        //std::cout << "Populating command buffer for " << currentImage << "\n";
        E09 *T = (E09 *) Params;
        T->populateCommandBuffer(commandBuffer, currentImage);
    }

    // This is the real place where the Command Buffer is written
    void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {
        // begin standard pass
        RP.begin(commandBuffer, currentImage);

        SC.populateCommandBuffer(commandBuffer, 0, currentImage);

        RP.end(commandBuffer);
    }

    void repositionCameraImmediately()
    {
        static float camHeight = 1.5;
        static float camDist = 5;
        // Ricalcola la posizione ideale della camera
        glm::mat4 camWorld =
                glm::translate(glm::mat4(1), Pos) *
                glm::rotate(glm::mat4(1.0f), Yaw, glm::vec3(0, 1, 0));

        cameraPos = camWorld *
                    glm::vec4(0.0f,
                              camHeight + camDist * sin(Pitch),
                              camDist * cos(Pitch),
                              1.0f);

        if (cameraPos.y < 0.2f)
            cameraPos.y = 0.2f;

        // Force the damped state
        dampedCamPos = cameraPos;
        dampedRelDir = relDir;
    }

    // Here is where you update the uniforms.
    // Very likely this will be where you will be writing the logic of your application.
    void updateUniformBuffer(uint32_t currentImage) {
        static bool debounce = false;
        static int curDebounce = 0;

        GLFWgamepadstate padButtons;
        bool hasPad = glfwGetGamepadState(GLFW_JOYSTICK_1, &padButtons);

        if (!walking) {
            AB.Start(2, 0.5);
        } else {
            if (running) {
                AB.Start(1, 0.5);
            } else {
                AB.Start(0, 0.5);
            }
        }
        // handle the ESC key to exit the app
        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        // Change window dimension
        if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS && !f11_pressed) {
            f11_pressed = true;
            isFullScreen = !isFullScreen;

            if (isFullScreen) {
                //Save current position and dimension
                glfwGetWindowPos(window, &savedWindowX, &savedWindowY);
                glfwGetWindowSize(window, &savedWindowW, &savedWindowH);

                //Get primary monitor and its video mode
                GLFWmonitor *monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode *mode = glfwGetVideoMode(monitor);

                //Change to full screen
                glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            } else {
                glfwSetWindowMonitor(window, nullptr, savedWindowX, savedWindowY, savedWindowW, savedWindowH, 0);
            }
        }

        if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_RELEASE) {
            f11_pressed = false;
        }

        // Camera changing management
        bool pressedC = glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS;
        bool pressedPadY = hasPad && (padButtons.buttons[GLFW_GAMEPAD_BUTTON_Y] == GLFW_PRESS);

        if ((pressedC || pressedPadY) && !c_pressed) {
            isFirstPerson = !isFirstPerson;
            c_pressed = true;
            Pitch = -Pitch;
            if (!isFirstPerson) {
                resetCamera = true;
                characterRotation = -Yaw + glm::radians(180.0f);
            }
        }

        if (!(pressedC || pressedPadY)) {
            c_pressed = false;
        }
        /*if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !c_pressed) {
            isFirstPerson = !isFirstPerson;
            c_pressed = true;
            // Reset the pitch when switching camera
            Pitch = -Pitch;
            if (!isFirstPerson) {
                resetCamera = true;
                characterRotation = -Yaw + glm::radians(180.0f);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
            c_pressed = false;
        }
*/

        if (glfwGetKey(window, GLFW_KEY_1)) {
            if (!debounce) {
                debounce = true;
                curDebounce = GLFW_KEY_1;

                debug1.x = 1.0 - debug1.x;
            }
        } else {
            if ((curDebounce == GLFW_KEY_1) && debounce) {
                debounce = false;
                curDebounce = 0;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_2)) {
            if (!debounce) {
                debounce = true;
                curDebounce = GLFW_KEY_2;

                debug1.y = 1.0 - debug1.y;
            }
        } else {
            if ((curDebounce == GLFW_KEY_2) && debounce) {
                debounce = false;
                curDebounce = 0;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_P)) {
            if (!debounce) {
                debounce = true;
                curDebounce = GLFW_KEY_P;

                debug1.z = (float) (((int) debug1.z + 1) % 65);
                std::cout << "Showing bone index: " << debug1.z << "\n";
            }
        } else {
            if ((curDebounce == GLFW_KEY_P) && debounce) {
                debounce = false;
                curDebounce = 0;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_O)) {
            if (!debounce) {
                debounce = true;
                curDebounce = GLFW_KEY_O;

                debug1.z = (float) (((int) debug1.z + 64) % 65);
                std::cout << "Showing bone index: " << debug1.z << "\n";
            }
        } else {
            if ((curDebounce == GLFW_KEY_O) && debounce) {
                debounce = false;
                curDebounce = 0;
            }
        }

        bool pressedSpace = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
        bool pressedPadA = hasPad && (padButtons.buttons[GLFW_GAMEPAD_BUTTON_A] == GLFW_PRESS);

        if (pressedSpace || pressedPadA) {
            if (!debounce) {
                debounce = true;
                curDebounce = GLFW_KEY_SPACE;
                running = true;
            }
        } else {
            if ((curDebounce == GLFW_KEY_SPACE) && debounce) {
                running = false;
                debounce = false;
                curDebounce = 0;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_E) && canTeleport) {
            if (!debounce) {
                debounce = true;
                curDebounce = GLFW_KEY_E;

                if (!activeTeleporter->pathVector.empty()){
                    path.assign(activeTeleporter ->pathVector.begin(), activeTeleporter ->pathVector.end());
                    TeleporterList::SetupTeleportPath(activeTeleporter,path);
                }

                activeTeleporter->Teleport(Pos,Yaw,Pitch);
                characterRotation = Yaw;
                repositionCameraImmediately();
            }
        } else {
            if ((curDebounce == GLFW_KEY_E) && debounce) {
                debounce = false;
                curDebounce = 0;
            }
        }
        /*
        static int curAnim = 0;
        if (glfwGetKey(window, GLFW_KEY_SPACE)) {
            if (!debounce) {
                debounce = true;
                curDebounce = GLFW_KEY_SPACE;
                running = true;
                std::cout << "Playing anim: " << curAnim << "\n";
            }
        } else {
            if ((curDebounce == GLFW_KEY_SPACE) && debounce) {
                running = false;
                debounce = false;
                curDebounce = 0;
            }
        }
*/
        // Makes the third person view wider
        bool pressedV = glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS;
        bool pressedPadB = hasPad && (padButtons.buttons[GLFW_GAMEPAD_BUTTON_B] == GLFW_PRESS);

        if ((pressedV || pressedPadB) && !v_pressed) {
            v_pressed = true;
            if (!isFirstPerson) {
                isWideView = !isWideView;
            }
        }
        if (!(pressedV || pressedPadB)) {
            v_pressed = false;
        }
        /*
        if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && !v_pressed) {
            v_pressed = true;
            if (!isFirstPerson) {
                isWideView = !isWideView;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_V) == GLFW_RELEASE) {
            v_pressed = false;
        }
*/
        // moves the view
        float deltaT = GameLogic();

        // updated the animation
        const float SpeedUpAnimFact = 0.85f;
        AB.Advance(deltaT * SpeedUpAnimFact);

        // --- WELL INTERACTION AND ANIMATION LOGIC ---
        float distToWell = glm::length(Pos - glm::vec3(0.0f, 0.0f, 0.0f));
        bool nearWell = (distToWell < 3.5f);

        if (nearWell && !canTeleport && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !wellDebounce) {
            if (bucketIsOnGround) {
                bucketIsOnGround = false; // Swap: Hide ground bucket, show rope bucket
                maskOffset = 0.06f;
                currentWellState = W_DOWN;
                bucketAnimY = 1.14f; // Reset positions
                ropeAnimY = 1.14f;
            } else if (currentWellState == W_IDLE) {
                currentWellState = W_DOWN;
            }
            wellDebounce = true;
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) wellDebounce = false;

        if (currentWellState == W_DOWN) {
            bucketAnimY -= deltaT * bucketDescSpeed;
            ropeAnimY -= deltaT * ropeDescSpeed;
            if (bucketAnimY <= wellBottomLimit) currentWellState = W_UP;
        } else if (currentWellState == W_UP) {
            bucketAnimY += deltaT * bucketAscSpeed;
            ropeAnimY += deltaT * ropeAscSpeed;
            if (maskOffset > -0.25f) maskOffset -= deltaT * 2.0f;

            if (bucketAnimY >= 1.14f) {
                bucketAnimY = 1.14f;
                ropeAnimY = 1.14f;
                currentWellState = W_IDLE;
                bucketIsOnGround = true; // SWAP TRIGGER: Bucket appears on ground
            }
        }

        // Rope Geometry
        float ropeBottomY = ropeAnimY - HANDLE_OFFSET;
        float currentLength = BEAM_Y - ropeBottomY;
        float midPointY = (BEAM_Y + ropeBottomY) / 2.0f;

        // --- CHAOTIC SPLASH LOGIC ---
        if (bucketAnimY <= WATER_LEVEL && !bucketIsOnGround) {
            float t = (float) glfwGetTime();
            for (int i = 0; i < 8; i++) {
                float freq = 12.0f + (i * 1.5f);
                float phase = (float) i * 0.8f;
                splashJump[i] = std::max(0.0f, (float) sin(t * freq + phase) * 0.25f);
            }
        } else {
            for (int i = 0; i < 8; i++) splashJump[i] = 0.0f;
        }

        // --- DAY/NIGHT & SUNSET CYCLE START ---

        // 1. Time Accumulator
        static float sunAngle = 0.0f;

        // Set day duration to 5 minutes (300 seconds)
        float dayDuration = 1000000000.0f;

        //Calculate rotation speed: 360 degrees divided by total duration
        float rotationSpeed = glm::radians(360.0f) / dayDuration;

        sunAngle += deltaT * rotationSpeed;

        // 2. Sun Position
        // Rotates around X (Rise/Set) with slight tilt on Y (-30 deg)
        glm::mat4 lightRot = glm::rotate(glm::mat4(1), glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
                             glm::rotate(glm::mat4(1), sunAngle, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::vec3 currentLightDir = glm::vec3(lightRot * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

        // 3. Define Colors
        glm::vec4 dayColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // White Day
        glm::vec4 sunsetColor = glm::vec4(1.0f, 0.4f, 0.1f, 1.0f); // Orange/Red Sunset
        glm::vec4 nightColor = glm::vec4(0.05f, 0.05f, 0.15f, 1.0f); // Dark Blue Night

        glm::vec4 currentLightColor;
        float blendFactor = 0.0f; // 0 = Night MMTexture, 1 = Day MMTexture

        // 4. Calculate Phase based on Sun Height (Y)
        float sunHeight = currentLightDir.y;

        // --- LOGICA LUCI DINAMICHE ---
        // lampIntensity va a 0 quando il sole è alto, e a 1 quando il sole scende
        float lampIntensity = glm::clamp(1.0f - (sunHeight + 0.1f) / 0.3f, 0.0f, 1.0f);

        // Moltiplichiamo per 10.0f per renderle MOLTO più luminose
        float brightness = 1.0f;
        glm::vec3 currentLampColor = glm::vec3(1.0f, 0.7f, 0.4f) * (lampIntensity * brightness);

        // Applichiamo il colore/intensità a tutti i lampioni trovati
        for (int i = 0; i < plboData.numActiveLights; i++) {
            plboData.lights[i].color = currentLampColor;
        }

        // --- LOGIC: DAY vs SUNSET vs NIGHT ---

        if (sunHeight > 0.2f) {
            // PHASE: FULL DAY
            // Smooth transition from Sunset Orange to Day White as sun goes up
            float t = glm::clamp((sunHeight - 0.2f) / 0.3f, 0.0f, 1.0f);
            currentLightColor = mix(sunsetColor, dayColor, t);

            blendFactor = 1.0f; // Use Full Day MMTexture
        } else if (sunHeight > -0.2f) {
            // PHASE: TRANSITION (Sunset / Sunrise)
            // The sun is crossing the horizon [-0.2 to 0.2]

            // Calculate mix for texture (0 at -0.2, 1 at 0.2)
            blendFactor = (sunHeight + 0.2f) / 0.4f;

            if (sunHeight > 0.0f) {
                // Upper Horizon: Pure Sunset Orange
                currentLightColor = sunsetColor;
            } else {
                // Lower Horizon: Fade from Orange to Night Blue
                float t = (sunHeight + 0.2f) / 0.2f;
                currentLightColor = mix(nightColor, sunsetColor, t);
            }
        } else {
            // PHASE: FULL NIGHT
            currentLightColor = nightColor;
            blendFactor = 0.0f; // Use Full Night MMTexture
        }

        // 5. Update Global Uniforms
        GlobalUniformBufferObject gubo{};
        gubo.lightDir = currentLightDir;
        gubo.lightColor = currentLightColor;
        gubo.eyePos = cameraPos;

        gubo.time = (float) glfwGetTime(); // Pass current time to shader for wind animation

        // --- DAY/NIGHT CYCLE END ---

        gubo.eyePos = cameraPos;

        // defines the local parameters for the uniforms
        UniformBufferObjectChar uboc{};
        uboc.debug1 = debug1;

        SKA.Sample(AB);
        std::vector<glm::mat4> *TMsp = SKA.getTransformMatrices();

        //printMat4("TF[55]", (*TMsp)[55]);

        glm::mat4 AdaptMat =
                glm::scale(glm::mat4(1.0f), glm::vec3(0.01f)) * glm::rotate(
                    glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(
                    glm::mat4(1.0f), glm::vec3(Pos.x * 100, Pos.z * 100, Pos.y * 100)) * glm::rotate(
                    glm::mat4(1.0f), characterRotation, glm::vec3(0.0f, 0.0f, 1.0f));

        // Hides player model when in FPV
        if (isFirstPerson) {
            AdaptMat = glm::scale(AdaptMat, glm::vec3(0.0f));
        }

        for (Teleporter* tp : teleporters){
            if (tp->CanTeleport(Pos,{Yaw,Pitch})){
                canTeleport = true;
                activeTeleporter = tp;
                break;
            }
            canTeleport = false;
        }

        int instanceId;
        // character
        for (instanceId = 0; instanceId < SC.TI[0].InstanceCount; instanceId++) {
            for (int im = 0; im < TMsp->size(); im++) {
                uboc.mMat[im] = AdaptMat * (*TMsp)[im];
                uboc.mvpMat[im] = ViewPrj * uboc.mMat[im];
                uboc.nMat[im] = glm::inverse(glm::transpose(uboc.mMat[im]));
                //std::cout << im << "\t";
                //printMat4("mMat", ubo.mMat[im]);
            }

            SC.TI[0].I[instanceId].DS[0][0]->map(currentImage, &gubo, 0); // Set 0
            // Link the Point Light buffer to Binding 3 for the character
            SC.TI[0].I[instanceId].DS[0][0]->map(currentImage, &plboData, 1);
            SC.TI[0].I[instanceId].DS[0][1]->map(currentImage, &uboc, 0); // Set 1
        }

        UniformBufferObjectSimp ubos{};

        // --- RENDERING STATIC OBJECTS (TI[1]) ---
        for (instanceId = 0; instanceId < SC.TI[1].InstanceCount; instanceId++) {
            auto &inst = SC.TI[1].I[instanceId];
            ubos.mMat = glm::mat4(1.0f); // Reset matrix for each object to avoid inheritance glitches

            // 1. THE ROPE
            if (*inst.id == "well_rope_wire") {
                if (!bucketIsOnGround) {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, midPointY, 0.0f)) *
                                glm::scale(glm::mat4(1.0f), glm::vec3(0.025f, currentLength * 0.5f, 0.025f));
                } else {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -100.0f, 0.0f)); // YEET to abyss
                }
            }
            // 2. THE BUCKET ON THE ROPE
            else if (*inst.id == "well_bucket") {
                if (!bucketIsOnGround) {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, bucketAnimY, 0.0f));
                } else {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -100.0f, 0.0f));
                }
            }
            // 3. THE FULL BUCKET ON THE GROUND
            else if (*inst.id == "spawned_bucket") {
                if (bucketIsOnGround) {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), groundedBucketPos);
                } else {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -100.0f, 0.0f));
                }
            }
            // 4. THE WATER MASK
            else if (*inst.id == "well_mask") {
                if (!bucketIsOnGround) {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, bucketAnimY + maskOffset, 0.0f)) *
                                glm::scale(glm::mat4(1.0f), glm::vec3(0.36f, 0.01f, 0.36f));
                } else {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -100.0f, 0.0f));
                }
            }
            // 5. THE SPLASHES (Uses FIND because we have 8 indexed IDs)
            else if (inst.id->find("well_splash_") != std::string::npos) {
                int idx = std::stoi(inst.id->substr(12)); // Get index after "well_splash_"
                float jump = splashJump[idx];
                if (jump > 0.001f) {
                    ubos.mMat = glm::translate(glm::mat4(1.0f),
                                               glm::vec3(inst.Wm[3][0], WATER_LEVEL + jump, inst.Wm[3][2])) *
                                glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));
                } else {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -100.0f, 0.0f));
                }
            }
            // 6. DEFAULT FOR ALL OTHER OBJECTS
            else {
                ubos.mMat = inst.Wm;
            }

            // Standard Uniform Mapping (Do not change)
            ubos.mvpMat = ViewPrj * ubos.mMat;
            ubos.nMat = glm::inverse(glm::transpose(ubos.mMat));
            inst.DS[0][0]->map(currentImage, &gubo, 0);
            inst.DS[0][0]->map(currentImage, &plboData, 1);
            inst.DS[0][1]->map(currentImage, &ubos, 0);
        }

        // skybox pipeline
        skyBoxUniformBufferObject sbubo{};
        sbubo.mvpMat = ViewPrj * glm::translate(glm::mat4(1), cameraPos) * glm::scale(glm::mat4(1), glm::vec3(100.0f));
        sbubo.settings.x = blendFactor;
        SC.TI[2].I[0].DS[0][0]->map(currentImage, &sbubo, 0);

        //TODO THIS CAUSED SOME CRASHES WHEN THE PROGRAM WAS COMPILED AND RUNNED IDK WHY SO I COMMENTED IT BECAUSE THEORETICALLY WE DO NOT USE PBR OBJECTS PLS CHECK THIS
        // PBR objects
        /*for (instanceId = 0; instanceId < SC.TI[3].InstanceCount; instanceId++) {
            ubos.mMat = SC.TI[3].I[instanceId].Wm;
            ubos.mvpMat = ViewPrj * ubos.mMat;
            ubos.nMat = glm::inverse(glm::transpose(ubos.mMat));

            SC.TI[3].I[instanceId].DS[0][0]->map(currentImage, &gubo, 0); // Set 0
            SC.TI[3].I[instanceId].DS[0][1]->map(currentImage, &ubos, 0); // Set 1
        }
        */

        // vegetation update
        for (instanceId = 0; instanceId < SC.TI[3].InstanceCount; instanceId++) {
            ubos.mMat = SC.TI[3].I[instanceId].Wm;
            ubos.mvpMat = ViewPrj * ubos.mMat;
            ubos.nMat = glm::inverse(glm::transpose(ubos.mMat));

            // Set 0: Global Uniforms (Binding 0)
            SC.TI[3].I[instanceId].DS[0][0]->map(currentImage, &gubo, 0);

            // --- ADD THIS LINE: You MUST map binding 3 even for trees! ---
            SC.TI[3].I[instanceId].DS[0][0]->map(currentImage, &plboData, 1);

            // Set 1: Local Uniforms (Binding 0)
            SC.TI[3].I[instanceId].DS[0][1]->map(currentImage, &ubos, 0);
        }

        // --- 5. DEBUG COLLISION BOXES MAPPING (Index 4) ---
        if (MapManager::debug) {
            if (SC.TI[4].InstanceCount > 0) {
                for (instanceId = 0; instanceId < SC.TI[4].InstanceCount; instanceId++) {
                    if (SC.TI[4].I[instanceId].DS[0][1] != nullptr) {
                        // Preparation of the matrices
                        ubos.mMat = SC.TI[4].I[instanceId].Wm;
                        ubos.mvpMat = ViewPrj * ubos.mMat;
                        ubos.nMat = glm::inverse(glm::transpose(ubos.mMat));

                        // CORRECTED MAPPING:
                        // The 3rd parameter is the BINDING INDEX, not the size.

                        // Set 0, Binding 0: Global Uniforms (gubo)
                        SC.TI[4].I[instanceId].DS[0][0]->map(currentImage, &gubo, 0);

                        // Set 0, Binding 1: Point Lights (plboData)
                        // Adding this for consistency with your other techniques
                        SC.TI[4].I[instanceId].DS[0][0]->map(currentImage, &plboData, 1);

                        // Set 1, Binding 0: Local Uniforms (ubos)
                        // Use 0 as the binding index. The engine knows the size from localInit.
                        SC.TI[4].I[instanceId].DS[0][1]->map(currentImage, &ubos, 0);
                    }
                }
            }
        }

        // updates the FPS
        static float elapsedT = 0.0f;
        static int countedFrames = 0;

        countedFrames++;
        elapsedT += deltaT;
        if (elapsedT > 1.0f) {
            float Fps = (float) countedFrames / elapsedT;

            std::ostringstream oss;
            oss << "FPS: " << Fps << "\n";

            txt.print(1.0f, 1.0f, oss.str(), 1, "CO", false, false, true, TAL_RIGHT, TRH_RIGHT, TRV_BOTTOM,
                      {1.0f, 0.0f, 0.0f, 1.0f}, {0.8f, 0.8f, 0.0f, 1.0f});

            elapsedT = 0.0f;
            countedFrames = 0;
        }

        // Updates cam's info text
        if (isFirstPerson) {
            txt.print(-1.0f, -1.0f, "View: First Person (Press C)", 2, "CO",
                      false, false, true, TAL_LEFT, TRH_LEFT, TRV_TOP,
                      {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
        } else {
            txt.print(-1.0f, -1.0f, "View: Third Person (Press C)", 2, "CO",
                      false, false, true, TAL_LEFT, TRH_LEFT, TRV_TOP,
                      {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
        }

        // Updates the crossair
        if (isFirstPerson) {
            txt.print(0.0f, 0.0f, "+", 3, "CO",
                      false, false, true, TAL_CENTER, TRH_CENTER, TRV_MIDDLE,
                      {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
        } else {
            txt.print(0.0f, 0.0f, " ", 3, "CO",
                      false, false, true, TAL_CENTER, TRH_CENTER, TRV_MIDDLE,
                      {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
        }

        if (canTeleport) {
            txt.print(-1.0f, -0.9f, "E to enter", 4, "CO",
                      false, false, true, TAL_LEFT, TRH_LEFT, TRV_TOP,
                      {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
        } else if (nearWell && currentWellState == W_IDLE) {
            txt.print(-1.0f, -0.9f, "E to draw water", 4, "CO", false, false, true, TAL_LEFT, TRH_LEFT, TRV_TOP,
                      {0.0f, 1.0f, 1.0f, 1.0f}, {0, 0, 0, 1});
        } else {
            txt.print(0.0f, 0.0f, " ", 4, "CO",
                      false, false, true, TAL_LEFT, TRH_LEFT, TRV_TOP,
                      {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
        }
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1)
                << "Player position  x: " << std::floor(Pos.x * 10) / 10
                << " y: " << std::floor(Pos.y * 10) / 10
                << " z: " << std::floor(Pos.z * 10) / 10;

        std::string coordinateTxt = oss.str();
        txt.print(-1.0, -0.8, coordinateTxt, 5, "CO", false, false, true,
                  TAL_LEFT, TRH_LEFT, TRV_TOP,
                  {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
        std::ostringstream oss2;
        oss2 << std::fixed << std::setprecision(1)
                << "Camera direction Yaw: " << std::floor(Yaw * 10) / 10
                << " Pitch: " << std::floor(Pitch * 10) / 10;

        std::string directionTxt = oss2.str();
        txt.print(-1.0, -0.7, directionTxt, 6, "CO", false, false, true,
                  TAL_LEFT, TRH_LEFT, TRV_TOP,
                  {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});


        txt.updateCommandBuffer();
    }

    float GameLogic() {
        // Parameters
        // Camera FOV-y, Near Plane and Far Plane
        const float FOVy = glm::radians(45.0f);
        const float nearPlane = 0.5f; //Fix for house cornering flickering
        const float farPlane = 100.f;
        // Player starting point
        const glm::vec3 StartingPosition = glm::vec3(0.0, 0.0, 5);
        // Camera target height and distance
        static float camHeight = 1.5;
        static float camDist = 5;
        // Camera Pitch limits
        // const float minPitch = glm::radians(-8.75f);
        // const float maxPitch = glm::radians(60.0f);
        // Rotation and motion speed
        const float ROT_SPEED = glm::radians(120.0f);
        const float MOVE_SPEED_BASE = 2.0f;
        const float MOVE_SPEED_RUN = 5.0f;
        const float ZOOM_SPEED = MOVE_SPEED_BASE * 1.5f;
        const float MAX_CAM_DIST = 7.5;
        const float MIN_CAM_DIST = 1.5;

        // Integration with the timers and the controllers
        float deltaT;
        glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f); // 'r' won't be used for rotation
        bool fire = false;
        getSixAxis(deltaT, m, r, fire);

        //Implement Pad visual
        GLFWgamepadstate padState;
        //If the pad is connected
        if (glfwGetGamepadState(GLFW_JOYSTICK_1, &padState)) {
            float deadzone = 0.2f;
            float padRotSpeed = 2.5f * deltaT; //Pad rotation speed

            float rStickX = padState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
            float rStickY = padState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];

            //Update the stick in the dead zone, update Yaw and Pitch
            if (std::abs(rStickX) > deadzone) {
                Yaw -= rStickX * padRotSpeed;
            }
            if (std::abs(rStickY) > deadzone) {
                if (isFirstPerson) {
                    Pitch -= rStickY * padRotSpeed;
                } else {
                    Pitch += rStickY * padRotSpeed;
                }
            }
        }

        float MOVE_SPEED = fire ? MOVE_SPEED_RUN : MOVE_SPEED_BASE;

        //Desired camera distance
        const float DIST_NORMAL = 2.5f;
        const float DIST_WIDE = 6.0f;

        //Choose the target depending on isWideView status
        float targetDist = isWideView ? DIST_WIDE : DIST_NORMAL;

        currentCamDist += (targetDist - currentCamDist) * (1.0f - exp(-5.0f * deltaT));

        //Change the camera distance
        camDist = currentCamDist;

        // To be done in the assignment
        ViewPrj = glm::mat4(1);
        World = glm::mat4(1);

        oldPos = Pos;

        // Calculates mouse offets
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = (float) (xpos - lastX);
        float yoffset = (float) (lastY - ypos); // Y-up
        lastX = xpos;
        lastY = ypos;

        if (m != glm::vec3(0, 0, 0)) {
            walking = true;
        } else {
            walking = false;
        }

        float oldCharacterRotation = characterRotation;
        if (isFirstPerson) {
            characterRotation = Yaw;
        } else {
            if (m == glm::vec3(0, 0, 0)) {
                characterRotation = oldCharacterRotation;
            } else {
                float targetRotation = -Yaw + atan2(m.z, m.x) + glm::radians(270.0f);
                float diff = targetRotation - characterRotation;
                const float PI = 3.14159265f;
                while (diff > PI) diff -= 2 * PI;
                while (diff < -PI) diff += 2 * PI;
                float rotSmoothness = 10.0f;
                characterRotation += diff * (1.0f - exp(-rotSmoothness * deltaT));
            }
        }

        if (isFirstPerson) {
            Yaw -= xoffset * (ROT_SPEED * mouseSensitivity) * deltaT;
            Pitch += yoffset * (ROT_SPEED * mouseSensitivity) * deltaT;

            // Clamping first person
            const float pitchLimit = glm::radians(89.0f);
            Pitch = Pitch < -pitchLimit ? -pitchLimit : (Pitch > pitchLimit ? pitchLimit : Pitch);
        } else {
            Yaw -= xoffset * (ROT_SPEED * mouseSensitivity) * deltaT;
            Pitch -= yoffset * (ROT_SPEED * mouseSensitivity) * deltaT;

            // Prevent camera from going too low (looking from below)
            const float minPitch_3rd = glm::radians(-10.0f);
            const float maxPitch_3rd = glm::radians(60.0f);

            Pitch = Pitch < minPitch_3rd ? minPitch_3rd : (Pitch > maxPitch_3rd ? maxPitch_3rd : Pitch);
        }

        float ef = exp(-10.0 * deltaT);

        // Projection matrix
        glm::mat4 Prj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
        Prj[1][1] *= -1;

        glm::mat4 View;

        // Calculates direction vectors
        glm::vec3 ux = glm::vec3(glm::rotate(glm::mat4(1.0f), Yaw, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 1));
        glm::vec3 uz = glm::vec3(glm::rotate(glm::mat4(1.0f), Yaw, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1));

        if (isFirstPerson) {
            // Calculate the front vector (where we are watching)
            glm::mat4 pitchRotation = glm::rotate(glm::mat4(1.0f), Pitch, ux);
            glm::vec3 front = glm::normalize(glm::vec3(pitchRotation * glm::vec4(uz, 0.0f)));

            // Calculate camera's up
            glm::vec3 up = glm::normalize(glm::cross(ux, front));

            // Lock the movement on the Y axis
            glm::vec3 moveFront = glm::vec3(front.x, 0.0f, front.z);

            // Normalize to avoid slowed movement when locking up or down
            if (glm::length(moveFront) > 0.001f) {
                moveFront = glm::normalize(moveFront);
            }

            Pos = Pos - MOVE_SPEED * m.z * front * deltaT;
            Pos = Pos + MOVE_SPEED * m.x * ux * deltaT;

            // Y position
            float groundY = getGroundHeight(Pos);
            Pos.y = groundY;

            // Camera is at eye height
            cameraPos = Pos + glm::vec3(0.0f, camHeight, 0.0f);
            glm::vec3 target = cameraPos + front;
            View = glm::lookAt(cameraPos, target, up);

            // Player model (invisible) rotates with the camera
            World = glm::translate(glm::mat4(1), Pos) * glm::rotate(glm::mat4(1.0f), Yaw, glm::vec3(0, 1, 0));
        } else {
            Pos = Pos + MOVE_SPEED * m.x * ux * deltaT;
            Pos = Pos - MOVE_SPEED * m.z * uz * deltaT;

            float groundY = getGroundHeight(Pos);
            Pos.y = groundY;
            
            camHeight += MOVE_SPEED * m.y * deltaT;

            // MMModel rotation
            if (glm::length(glm::vec3(m.x, 0.0f, m.z)) > 0.001f) {
                relDir = Yaw + atan2(m.x, m.z);
                dampedRelDir = dampedRelDir > relDir + 3.1416f
                                   ? dampedRelDir - 6.28f
                                   : dampedRelDir < relDir - 3.1416f
                                         ? dampedRelDir + 6.28f
                                         : dampedRelDir;
            }
            dampedRelDir = ef * dampedRelDir + (1.0f - ef) * relDir;
            World = glm::translate(glm::mat4(1), Pos) * glm::rotate(glm::mat4(1.0f), dampedRelDir, glm::vec3(0, 1, 0));

            glm::vec3 target = Pos + glm::vec3(0.0f, camHeight, 0.0f);
            glm::mat4 camWorld = glm::translate(glm::mat4(1), Pos) * glm::rotate(
                                     glm::mat4(1.0f), Yaw, glm::vec3(0, 1, 0));
            cameraPos = camWorld * glm::vec4(0.0f, camHeight + camDist * sin(Pitch), camDist * cos(Pitch), 1.0);

            //if (cameraPos.y < 0.2f) {
            //    cameraPos.y = 0.2f;
            //}

            //Start reset to improve camera movement when changing
            if (resetCamera) {
                dampedCamPos = cameraPos; //Teleport
                dampedRelDir = relDir;
                resetCamera = false;
            }

            dampedCamPos = ef * dampedCamPos + (1.0f - ef) * cameraPos;
            View = glm::lookAt(dampedCamPos, target, glm::vec3(0, 1, 0));
        }
        // ===============================
        // COLLISION CHECK (COMMON)
        // ===============================
        glm::vec3 colPos = Pos;
        colPos.y = 0.0f;
        CollisionObject playerCol;
        playerCol.addBox(
            Pos + glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(1.5f, 2.0f, 1.5f),
            CollisionBox::cylinder
        );

        for (const auto &house: houseCollisions) {
            if (playerCol.collidesWith(house)) {
                Pos = oldPos;
                break;
            }
        }

        ViewPrj = Prj * View;

        float vel = length(Pos - oldPos) / deltaT;

        if (vel < 0.2) {
            if (currRunState != 1) {
                currRunState = 1;
            }
        } else if (vel < 3.5) {
            if (currRunState != 2) {
                currRunState = 2;
            }
        } else {
            if (currRunState != 3) {
                currRunState = 3;
            }
        }

        return deltaT;
    }
};

float E09::getGroundHeight(const glm::vec3& pos) {
    // ---------- BRIDGE ----------
    if (pos.x > 215.0f && pos.x < 270.0f &&
        pos.z > -10.0f && pos.z < 10.0f) {
        return 0.0f;
    }
    // ---------- RAMP LEFT ----------
    if (pos.x >= 210.0f && pos.x <= 225.0f) {
        float t = (pos.x - 215.0f) / 10.0f;   // 0 → 1
        return glm::mix(0.0f, -2.3f, t);
    }

    // ---------- RIVER BED ----------
    if (pos.x > 225.0f && pos.x < 260.0f) {
        return -2.3f;
    }

    // ---------- RAMP RIGHT ----------
    if (pos.x >= 260.0f && pos.x <= 275.0f) {
        float t = (pos.x - 260.0f) / 10.0f;   // 0 → 1
        return glm::mix(-2.3f, 0.0f, t);
    }

    // ---------- NORMAL GROUND ----------
    return 0.0f;
}


// This is the main: probably you do not need to touch this!
int main() {
    E09 app;
    unsigned char response;
    std::cout << "Want to activate debug mode? Y/n\n";
    do {
        std::cin >> response;
    } while (
        std::tolower(static_cast<int>(response)) != 'y' &&
        std::tolower(static_cast<int>(response)) != 'n'
    );
    MapManager *mapManager = new MapManager();
    if (std::tolower(static_cast<int>(response)) == 'y') {
        std::cout << "in\n";
        mapManager->debug = true;
    } else mapManager->debug = false;
    mapManager->makeJson();
    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
