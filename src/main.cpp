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
#include "DrunkEffectManager.hpp"
#include "CandleManager.hpp"

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

// Global Uniform Buffer Object: Shared data for all shaders
struct GlobalUniformBufferObject {
    alignas(16) glm::vec3 lightDir; // Direction of the sun light
    alignas(16) glm::vec4 lightColor; // Color of the sun (changes during day/night cycle)
    alignas(16) glm::vec3 eyePos; // Camera position for specular calculations
    alignas(16) float time; // Total elapsed time for procedural animations (e.g., wind)
};

// Uniforms for animated characters using skeletal skinning
struct UniformBufferObjectChar {
    alignas(16) glm::vec4 debug1; // Debugging data (e.g., bone indices or transparency)
    alignas(16) glm::mat4 mvpMat[65]; // Model-View-Projection matrices for up to 65 bones
    alignas(16) glm::mat4 mMat[65]; // Model matrices (World space) for each bone
    alignas(16) glm::mat4 nMat[65]; // Normal matrices (inverse-transpose) for correct lighting on bones
};

// Uniforms for static objects (no skeletal animation)
struct UniformBufferObjectSimp {
    alignas(16) glm::mat4 mvpMat; // Transforms local coordinates to clip space (Screen)
    alignas(16) glm::mat4 mMat; // Transforms local coordinates to world space
    alignas(16) glm::mat4 nMat; // Normal matrix used to calculate lighting directions correctly
};

// Uniforms for the Skybox environment
struct skyBoxUniformBufferObject {
    alignas(16) glm::mat4 mvpMat; // Position of the skybox
    alignas(16) glm::vec4 settings; // x = blendFactor (0 night , 1 day)
};

// Point Light structure: Defines an individual lamp's properties
struct PointLight {
    alignas(16) glm::vec3 position; // World space position of the light source
    alignas(16) glm::vec3 color; // Light emission color (RGB)
};

// Buffer for multiple point lights (supports up to 100 lamps)
struct PointLightBufferObject {
    PointLight lights[100];
    int numActiveLights; // Current count of lights to be processed by the shader
    int numLampLights; // Number of lights that are lamps (with dynamic color)
};

// Storage for candle and study lights (activated based on distance)
struct StoredLight {
    glm::vec3 position;
    glm::vec3 color;
};
std::vector<StoredLight> lampLights;
std::vector<StoredLight> candleLights;
std::vector<StoredLight> studyLights;

glm::mat4 takenCandleWm;

// MAIN !
class E09 : public BaseProject {
private:
    std::vector<CollisionObject> houseCollisions;
    std::vector<Teleporter *> teleporters;
    Teleporter *activeTeleporter;
    std::deque<int> path;

    float getGroundHeight(const glm::vec3 &pos);

    // --- WELL ANIMATION SETTINGS ---
    enum WellState { W_IDLE, W_DOWN, W_UP };

    WellState currentWellState = W_IDLE;

    // CONSTANTS
    const float BEAM_Y = 1.85f; // Fixed height of the support beam
    const float HANDLE_OFFSET = 0.18f; // Distance to subtract from bucket center to reach handle

    // DYNAMIC COORDINATES
    float bucketAnimY = 1.14f; // Current Y position of the bucket
    float ropeAnimY = 1.14f; // Separate Y tracker for the rope (for calibration)
    float maskOffset = 0.06f; // Offset for the water surface mask

    // SEPARATED SPEEDS (Tune these to prevent detachments)
    float bucketDescSpeed = 0.5f; // Descending speed for the bucket
    float ropeDescSpeed = 1.0f; // Descending speed for the rope

    float bucketAscSpeed = 0.8f; // Ascending speed for the bucket
    float ropeAscSpeed = 1.6f; // Ascending speed for the rope

    float wellBottomLimit = -2.0f;
    bool wellDebounce = false; // Input debounce for the 'E' key
    
    // Candle interaction debounce
    bool candleDebounce = false;
    float candleCooldown = 0.0f;
    const float CANDLE_COOLDOWN_TIME = 0.5f; // 500ms cooldown between actions

    // SPLASH ANIMATION SETTINGS
    const float WATER_LEVEL = 0.0f; // Y level where splashes occur
    float splashJump[8] = {0.0f}; // Current vertical offset for each cube

    // BUCKET SWAP SETTINGS
    bool bucketIsOnGround = false; // Logic flag: is the full bucket near the well?
    glm::vec3 groundedBucketPos = glm::vec3(1.2f, 0.3f, 0.0f); // Where the full bucket spawns

    // --- CAST 3 RISING ANIMATION ---
    enum CastState { CAST_HIDDEN, CAST_RISING, CAST_VISIBLE, CAST_CHASING, CAST_RETURNING };

    CastState currentCastState = CAST_HIDDEN;
    glm::vec3 castCurrentPos = glm::vec3(350.0f, -3.0f, -110.0f); // Current cast3 position
    float castCurrentRotation = 0;
    float castTargetHeight = 5.0f; // How high it rises
    float castRiseSpeed = 1.0f; // Rising speed
    float chaseSpeed = 3.0f;
    float floatingValue = 0.0;
    float floatMax = 1.2;
    bool floatUp = true;
    bool floatDown = false;
    float rotation_speed = 0.001f;
    float return_speed = 0.001f;
    glm::vec3 statuePos = glm::vec3(350.0f, 0.0f, -110.0f); // Statue position in graveyard
    glm::vec3 castReturnPos = glm::vec3(350.0f, -3.0f, -110.0f); // Where cast3 returns to
    bool castDebounce = false; // Input debounce for trigger key
    float timeBeforeChasing = 3.0f;
    float chaseTime = 10.0;
    float chaseTimer = 0.0;
    bool isCutscene1 = false; // Cutscene during CAST_RISING
    bool isCutscene2 = false; // Cutscene during CAST_VISIBLE
    bool isCutscene = false; // Combined cutscene flag (OR of cutscene1 and cutscene2)


protected:
    PointLightBufferObject plboData; // Buffer containing data for all point lights (positions/colors)

    /** * DESCRIPTOR SET LAYOUTS
 * These act as a "contract" between the C++ code and the Shaders.
 * They define which buffers and textures the shaders should expect.
 */
    DescriptorSetLayout DSLlocalChar, DSLlocalSimp, DSLlocalPBR, DSLglobal, DSLskyBox;
    DescriptorSetLayout DSLveg; // Specialized layout for vegetation (swaying logic)
    DescriptorSetLayout DSLdebug; // Layout used for visualizing collision boxes

    /** * VERTEX DESCRIPTORS
 * Define the memory layout of a single vertex (e.g., Position, Normals, UVs, Bone Weights).
 */
    VertexDescriptor VDchar; // For animated characters (includes bone weights)
    VertexDescriptor VDsimp; // For static objects
    VertexDescriptor VDskyBox; // Minimal layout for the skybox (positions only)
    VertexDescriptor VDtan; // For PBR objects (includes Tangents for normal mapping)
    RenderPass RP; // Describes the attachments (Color, Depth) used during a draw call

    /** * PIPELINES
 * The "State Machine" of the GPU. Includes Shaders, Rasterization, and Blending settings.
 */
    Pipeline Pchar, PsimpObj, PskyBox, P_PBR;
    Pipeline Pveg; // Renders moving vegetation
    Pipeline Pdebug; // Renders wireframe/transparent collision boxes

    // Models, textures and Descriptors (values assigned to the uniforms)
    Scene SC; // Container for all 3D models, textures, and instances
    std::vector<VertexDescriptorRef> VDRs; // References to vertex layouts for the scene loader
    std::vector<TechniqueRef> PRs; // References to techniques (shader/pipeline combinations)

    /** * ANIMATION SYSTEM
 * Handles skeletal skinning and blending between different animation states.
 */
    #define N_ANIMATIONS 5
    AnimBlender AB; // Smoothly transitions between animations (e.g., walk to run)
    Animations Anim[N_ANIMATIONS]; // Array of loaded animation clips
    SkeletalAnimation SKA; // Computes final bone matrices for the current frame

    TextMaker txt; // Utility for rendering 2D UI text overlays

    // --- OTHER APPLICATION PARAMETERS ---
    float Ar; // Aspect Ratio (Width / Height)


    glm::mat4 ViewPrj; // Combined View and Projection matrix
    glm::mat4 World; // Global world transformation matrix
    glm::vec3 Pos = glm::vec3(0, 0, 5); // Character's current world position
    glm::vec3 cameraPos; // Physical location of the camera in 3D space
    float Yaw = glm::radians(0.0f); // Euler angles for camera/character orientation
    float Pitch = glm::radians(0.0f); // The Y-axis rotation specifically for the player model
    float Roll = glm::radians(0.0f);
    float characterRotation = glm::radians(0.0f); // Rotation value for character

    // --- CAM VARIABLE ---
    bool isFirstPerson = false; // Toggles between FPV (First Person) and TPV (Third Person) views
    bool c_pressed = false; // Debounce flag to prevent rapid-fire camera switching when 'C' is held
    bool isWideView = false; // Adjusts the Field of View or Camera Distance for a cinematic effect
    bool v_pressed = false; // Debounce flag to prevent rapid-fire camera switching when 'V' is held
    bool canTeleport = false; // Boolean flag checked when the player is near a teleportation trigger
    float currentCamDist = 5.0f; // Smoothly interpolated distance for the third-person camera
    bool resetCamera = false; // Trigger used to snap the camera back to a default position after an event

    // --- WINDOW VARIABLE ---
    bool f11_pressed = false;
    bool isFullScreen = false; // Tracks if the app is in borderless fullscreen mode
    // Cache to restore windowed mode
    int savedWindowX = 0;
    int savedWindowY = 0;
    int savedWindowW = 800;
    int savedWindowH = 600;

    // --- TPV VARIABLE ---
    // Used to determine which animation (AB) to play
    bool walking = false;
    bool running = false;

    // --- MOUSE VARIABLE ---
    // Stores previous cursor position to calculate delta movement
    double lastX;
    double lastY;

    bool firstMouse = true; // Prevents the camera from "jumping" on the first frame of input
    float mouseSensitivity = 0.1f; // Multiplier for mouse movement speed

    // --- PLAYER STATE VARIABLES ---
    glm::vec3 oldPos; // Stores position from the previous frame to resolve collisions
    int currRunState = 1; // Numerical ID for the current movement speed (Idle, Walk, Run)
    float relDir = glm::radians(0.0f); // The raw direction the player is trying to move in
    float dampedRelDir = glm::radians(0.0f); // Smoothed direction to prevent the model from snapping instantly
    glm::vec3 dampedCamPos = glm::vec3(0.0, 0.0, 5); // Lagged camera position for a "smooth follow" effect
    glm::vec4 debug1 = glm::vec4(0); // General purpose vector for on-screen debugging/testing


    void setWindowParameters() {
        // Window size, title and initial background
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
        // --- INITIAL INPUT SETUP ---
        // Disable the mouse cursor and lock it to the window for camera control
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        lastX = windowWidth / 2.0;
        lastY = windowHeight / 2.0;
        firstMouse = true;

        for (auto &[id, info]: TeleporterList::teleporters) {
            teleporters.push_back(info.teleporter.get());
        }

        // --- GLOBAL DESCRIPTOR SET LAYOUT (DSLglobal) ---
        // This layout is shared across multiple pipelines (Set 0)
        DSLglobal.init(this, {
            // Binding 0: Global Uniform Buffer (Sun direction, color, time)
                           {
                               0,
                               VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                               VK_SHADER_STAGE_ALL_GRAPHICS,
                               sizeof(GlobalUniformBufferObject),
                               1
                           },
            // Binding 1: Point Light Buffer (The array of 100 lamps)
                           {
                               1,
                               VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                               VK_SHADER_STAGE_ALL_GRAPHICS,
                               sizeof(PointLightBufferObject),
                               1
                           }
                       });

        DSLlocalChar.init(this, {
                              // this array contains the binding:
                              // first  element : the binding number
                              // second element : the type of element (buffer or texture)
                              // third  element : the pipeline stage where it will be used
                              {
                                  0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                                  VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
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
        // --- SKYBOX LAYOUT (DSLskyBox) ---
        DSLskyBox.init(this, {
            // Binding 0: Uniform Buffer (Handles the Day/Night blend factor)
                           {
                               0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                               VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                               sizeof(skyBoxUniformBufferObject), 1
                           },

            // Binding 1: Sky Texture (The cubemap or panoramic sky image)
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
            // Binding 0: Local Matrices (MVP, World, Normal)
                        {
                            0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT,
                            sizeof(UniformBufferObjectSimp), 1
                        },
            // Binding 1: Albedo Texture (The actual tree/leaf image)
                        {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1},
            // Binding 2: Noise Texture (Used for procedural wind swaying)
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
        // --- CHARACTER VERTEX DESCRIPTOR (VDchar) ---
        // Includes extra attributes for skeletal animation (Joint Indices and Weights)
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

        // Initializes the render passes
        RP.init(this);
        // Sets the blue sky
        RP.properties[0].clearValue = {0.0f, 0.9f, 1.0f, 1.0f};


        // --- PIPELINE INITIALIZATION ---
        // Connects the Global and Local layouts to the specific shader files
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
                    }, 1, &VDskyBox);
        PRs[3].init("Vegetation", {
                        {
                            &Pveg, {
                                // Use the vegetation pipeline
                                /*DSLglobal*/ {},
                                /*DSLlocal*/ {
                                    {true, 0, {}}, // Texture 0: Tree/Bush
                                    {true, 1, {}}, // Texture 1: for Wind
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
                    }, 2, &VDsimp); // Uses 2 textures total

        // Models, textures and Descriptors (values assigned to the uniforms)
        // Sets the size of the Descriptor Set Pool
        DPSZs.uniformBlocksInPool = 2000;
        DPSZs.texturesInPool = 2000;
        DPSZs.setsInPool = 2000;

        // --- SCENE LOADING ---
        // This processes the scene.json file and allocates all necessary GPU memory
        std::cout << "\nLoading the scene\n\n";
        if (SC.init(this, /*Npasses*/1, VDRs, PRs, "assets/models/scene.json") != 0) {
            std::cout << "ERROR LOADING THE SCENE\n";
            exit(0);
        }

        //Initialize collision box
        houseCollisions = CollisionBoxGenerator::collisions;

        // Initializes animations
        for (int ian = 0; ian < N_ANIMATIONS; ian++) {
            Anim[ian].init(*SC.As[ian]);
        }
        AB.init({{0, 32, 0.0f, 0}, {0, 16, 0.0f, 1}, {0, 263, 0.0f, 2}, {0, 83, 0.0f, 3}, {0, 16, 0.0f, 4}});
        //AB.init({{0,31,0.0f}});

        // --- ANIMATION INITIALIZATION ---
        // Mixamo layer setup for the 5 animation clips
        SKA.init(Anim, 5, "Armature|mixamo.com|Layer0", 0);

        // Initializes the textual output
        txt.init(this, windowWidth, windowHeight);

        // Submits the main command buffer
        submitCommandBuffer("main", 0, populateCommandBufferAccess, this);

        // Prepares for showing the FPS count
        txt.print(1.0f, 1.0f, "FPS:", 1, "CO", false, false, true, TAL_RIGHT, TRH_RIGHT, TRV_BOTTOM,
                  {1.0f, 0.0f, 0.0f, 1.0f}, {0.8f, 0.8f, 0.0f, 1.0f});

        // Text to indicate current visual mode
        txt.print(-1.0f, -1.0f, "View: Third Person (Press C)", 2, "CO",
                  false, false, true, TAL_LEFT, TRH_LEFT, TRV_TOP,
                  {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});

        // Define the FPV crosshair
        txt.print(0.0f, 0.0f, "+", 3, "CO",
                  false, false, true, TAL_CENTER, TRH_CENTER, TRV_MIDDLE,
                  {1.0f, 1.0f, 1.0f, 1.0f}, // Colour: White
                  {0.0f, 0.0f, 0.0f, 1.0f}); // Border: Black

        // --- POINT LIGHT DETECTION ---
        // Automatically finds objects with "lamp" in their name and creates a light source
        plboData.numActiveLights = 0;
        plboData.numLampLights = 0;
        for (int i = 0; i < SC.TI[1].InstanceCount; i++) {
            auto &inst = SC.TI[1].I[i];
            if (inst.id->find("lamp") != std::string::npos) {
                lampLights.push_back({{inst.Wm[3][0], 4.5f, inst.Wm[3][2]}, {1.0f, 0.7f, 0.4f}});
                plboData.numLampLights++;
            }
            if (inst.id->find("candle") != std::string::npos) {
                candleLights.push_back({{inst.Wm[3][0], inst.Wm[3][1], inst.Wm[3][2]}, {0.42f, 0.22f, 0.06f}});
            }
            if (inst.id->find("study_table") != std::string::npos) {
                studyLights.push_back({{inst.Wm[3][0] - 0.4, inst.Wm[3][1] + 0.3, inst.Wm[3][2] + 0.6}, {0.42f, 0.22f, 0.06f}});
            }
        }
        std::cout << "[Light Setup] Found " << lampLights.size() << " lamps, " << candleLights.size() << " candles, " << studyLights.size() << " study lights in the scene." << std::endl;
    }

    // Here you create your pipelines and Descriptor Sets!
    void pipelinesAndDescriptorSetsInit() {
        // Initialize the Render Pass (Defines how color and depth buffers are cleared and stored)
        RP.create();

        // Create the Graphics Pipelines
        // These link the shaders to the render pass and set the GPU's state machine
        Pchar.create(&RP); // For animated characters (Skeletal Skinning)
        PsimpObj.create(&RP); // For standard static meshes (Houses, ground)
        PskyBox.create(&RP); // For the background skybox environment
        P_PBR.create(&RP); // For Physically Based Rendering (Advanced materials)

        Pveg.create(&RP); // For swaying vegetation (Handles wind and transparency)
        Pdebug.create(&RP); // For collision box visualization (Usually wireframe/translucent)

        // Delegate Descriptor Set allocation for the scene and UI
        // This connects the specific textures/buffers to the object instances
        SC.pipelinesAndDescriptorSetsInit();
        txt.pipelinesAndDescriptorSetsInit(); // Setup resources for screen-space text
    }

    // Here you destroy your pipelines and Descriptor Sets!
    void pipelinesAndDescriptorSetsCleanup() {
        // Destroy Pipeline State Objects (PSOs)
        // We destroy these first because they depend on the Render Pass
        Pchar.cleanup();
        PsimpObj.cleanup();
        PskyBox.cleanup();
        P_PBR.cleanup();

        Pveg.cleanup(); // Cleanup vegetation-specific pipeline
        Pdebug.cleanup(); // Cleanup collision debug pipeline

        // Destroy the Render Pass
        RP.cleanup();

        // Cleanup scene-wide and text-specific descriptors
        SC.pipelinesAndDescriptorSetsCleanup();
        txt.pipelinesAndDescriptorSetsCleanup();
    }

    // Here you destroy all the Models, Texture and Desc. Set Layouts you created!
    // You also have to destroy the pipelines
    void localCleanup() {
        // Destroy the "blueprints" that define the structure of data sent to shaders.
        // Without these, the engine no longer knows how to bind buffers or textures.
        DSLlocalChar.cleanup();
        DSLlocalSimp.cleanup();
        DSLlocalPBR.cleanup();
        DSLskyBox.cleanup();
        DSLveg.cleanup(); // Cleanup the specialized vegetation layout
        DSLdebug.cleanup(); // Cleanup the collision box layout
        DSLglobal.cleanup(); // Cleanup the global layout (Sun/Lights)

        // Permanently destroy the Pipeline State Objects (PSOs).
        // This removes the compiled shader code and fixed-function settings from the GPU.
        Pchar.destroy();
        PsimpObj.destroy();
        PskyBox.destroy();
        P_PBR.destroy();
        Pveg.destroy();
        Pdebug.destroy();

        // Destroy the object that defines how attachments (color/depth) are handled.
        RP.destroy();

        // Wipe the Scene (all 3D models, textures, and instances) and the Text module.
        SC.localCleanup();
        txt.localCleanup();

        // Release the memory occupied by each of the N_ANIMATIONS animation clips.
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

    void repositionCameraImmediately() {
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

        if (!isCutscene && (pressedC || pressedPadY) && !c_pressed) {
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

        if (!isCutscene && glfwGetKey(window, GLFW_KEY_1)) {
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

        if (!isCutscene && glfwGetKey(window, GLFW_KEY_2)) {
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

        if (!isCutscene && glfwGetKey(window, GLFW_KEY_P)) {
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

        if (!isCutscene && glfwGetKey(window, GLFW_KEY_O)) {
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

        if (!isCutscene && (pressedSpace || pressedPadA)) {
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

        if (!isCutscene && glfwGetKey(window, GLFW_KEY_E) && canTeleport) {
            if (!debounce) {
                debounce = true;
                curDebounce = GLFW_KEY_E;

                if (!activeTeleporter->pathVector.empty()) {
                    path.assign(activeTeleporter->pathVector.begin(), activeTeleporter->pathVector.end());
                    TeleporterList::SetupTeleportPath(activeTeleporter, path);
                }

                activeTeleporter->Teleport(Pos, Yaw, Pitch);
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

        if (!isCutscene && (pressedV || pressedPadB) && !v_pressed) {
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

        // Update combined cutscene flag
        isCutscene = isCutscene1 || isCutscene2;

        // --- CAST 3 RISING ANIMATION LOGIC ---
        float distToStatue = glm::length(Pos - statuePos);
        bool nearStatue = (distToStatue < 5.0f);

        if (!isCutscene && nearStatue && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !castDebounce) {
            if (currentCastState == CAST_HIDDEN) {
                currentCastState = CAST_RISING;
                castCurrentPos = statuePos; // Reset to statue position
                chaseTimer = 0.0f;

                // Start cutscene 1
                isCutscene1 = true;
                isFirstPerson = false;
                // Disable first person
            }
            castDebounce = true;
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) castDebounce = false;

        if (currentCastState == CAST_RISING) {
            castCurrentPos.y += deltaT * castRiseSpeed;
            if (castCurrentPos.y >= statuePos.y + castTargetHeight) {
                castCurrentPos.y = statuePos.y + castTargetHeight;
                currentCastState = CAST_VISIBLE;
                chaseTimer = 0.0f;

                // End cutscene 1, start cutscene 2
                isCutscene1 = false;
                isCutscene2 = true;
                isFirstPerson = false; // Keep camera disabled
            }
        }
        if (currentCastState == CAST_VISIBLE) {
            chaseTimer += deltaT;
            if (chaseTimer >= timeBeforeChasing) {
                currentCastState = CAST_CHASING;
                chaseTimer = 0.0f;

                // End cutscene 2, restore camera
                isCutscene2 = false;
                isFirstPerson = false; // Return to third person
            }
        }

        if (currentCastState == CAST_CHASING) {
            // Follow player position
            glm::vec3 targetPos = Pos + glm::vec3(0.0f, 2.0f + floatingValue, 0.0f); // Slightly above player
            glm::vec3 direction = targetPos - castCurrentPos;
            if (floatUp) {
                floatingValue += 2 * deltaT;
                if (floatingValue >= floatMax) {
                    floatUp = false;
                    floatDown = true;
                }
            }
            if (floatDown) {
                floatingValue -= 2 * deltaT;
                if (floatingValue <= -floatMax) {
                    floatUp = true;
                    floatDown = false;
                }
            }

            float distance = glm::length(direction);

            if (distance > 0.1f) {
                // Calculate rotation to face player (Y-axis rotation)
                glm::vec3 directionXZ = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));
                castCurrentRotation = atan2(directionXZ.x, directionXZ.z);

                glm::vec3 movement = glm::normalize(direction) * chaseSpeed * deltaT;
                if (glm::length(movement) < distance) {
                    castCurrentPos += movement;
                } else {
                    castCurrentPos = targetPos;
                }
            }

            chaseTimer += deltaT;
            if (chaseTimer >= chaseTime) {
                currentCastState = CAST_RETURNING;
                chaseTimer = 0.0f;
            }
        }

        if (currentCastState == CAST_RETURNING) {
            // Return to original position
            glm::vec3 direction = castReturnPos - castCurrentPos;
            float distance = glm::length(direction);
            if (distance > 0.5f) {
                glm::vec3 movement = glm::normalize(direction) * return_speed * deltaT;
                if (glm::length(movement) < distance) {
                    castCurrentPos += movement * deltaT;
                    castCurrentRotation += rotation_speed * deltaT;
                    rotation_speed *= 1.1f;
                    return_speed *= 1.1f;
                } else {
                    castCurrentPos = castReturnPos;
                    currentCastState = CAST_HIDDEN;
                }
            } else {
                castCurrentPos = castReturnPos;
                currentCastState = CAST_HIDDEN;
            }
        }

        // Apply cast3 animation to the cemetery_cast3 instance
        for (int k = 0; k < SC.TechniqueInstanceCount; k++) {
            for (int i = 0; i < SC.TI[k].InstanceCount; i++) {
                // Find the cemetery_cast3 instance
                std::string instanceId = *(SC.TI[k].I[i].id);
                if (instanceId == "cemetery_cast3") {
                    glm::vec3 baseScale = glm::vec3(1.0f, 1.0f, 1.0f);

                    // Use current position and rotation: translate, rotate, scale
                    glm::mat4 transform = glm::translate(glm::mat4(1.0f), castCurrentPos) *
                                          glm::rotate(glm::mat4(1.0f), castCurrentRotation,
                                                      glm::vec3(0.0f, 1.0f, 0.0f)) *
                                          glm::scale(glm::mat4(1.0f), baseScale);

                    SC.TI[k].I[i].Wm = transform;
                    break;
                }
            }
        }

        // --- CANDLE VISIBILITY CONTROL ---
        // Handle hiding/showing candles based on pickup state
        for (int k = 0; k < SC.TechniqueInstanceCount; k++) {
            for (int i = 0; i < SC.TI[k].InstanceCount; i++) {
                std::string instanceId = *(SC.TI[k].I[i].id);
                
                // If this is the held candle, hide it by scaling to 0
                if (CandleManager::isHoldingCandle && instanceId == CandleManager::heldCandleId) {
                    SC.TI[k].I[i].Wm = glm::scale(SC.TI[k].I[i].Wm, glm::vec3(0.0f));
                }
                // If this was just dropped, restore it to original position
                else if (!CandleManager::isHoldingCandle && instanceId == CandleManager::droppedCandle) {
                    // Reconstruct world matrix from original position with 2x scale
                    glm::vec3 originalPos = CandleManager::candlePositions[instanceId];
                    SC.TI[k].I[i].Wm = glm::translate(glm::mat4(1.0f), originalPos) *
                                       glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
                    CandleManager::droppedCandle = "";
                }
            }
        }

        // --- WELL INTERACTION AND STATE MACHINE ---
        // Calculate distance to the well (positioned at origin 0,0,0)
        float distToWell = glm::length(Pos - glm::vec3(0.0f, 0.0f, 0.0f));
        bool nearWell = (distToWell < 3.5f); // Interaction radius

        // Trigger interaction when 'E' is pressed near the well
        if (nearWell && !canTeleport && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !wellDebounce) {
            if (bucketIsOnGround) {
                // RESET: If the bucket was already full on the ground, reset it to the rope
                bucketIsOnGround = false; // Swap: Hide ground bucket, show rope bucket
                maskOffset = 0.06f;
                currentWellState = W_DOWN;
                bucketAnimY = 1.14f; // Starting height
                ropeAnimY = 1.14f;
            } else if (currentWellState == W_IDLE) {
                // START: Begin lowering the bucket
                currentWellState = W_DOWN;
            }
            wellDebounce = true; // Prevent multiple triggers from one press
        }
        // Reset debounce when key is released
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) wellDebounce = false;

        // --- ANIMATION UPDATE LOOP ---
        if (currentWellState == W_DOWN) {
            // LOWERING: Decrease Y positions based on independent speeds
            bucketAnimY -= deltaT * bucketDescSpeed;
            ropeAnimY -= deltaT * ropeDescSpeed;
            // Switch to ascending state once the bottom limit is reached
            if (bucketAnimY <= wellBottomLimit) currentWellState = W_UP;
        } else if (currentWellState == W_UP) {
            // ASCENDING: Move bucket back up
            bucketAnimY += deltaT * bucketAscSpeed;
            ropeAnimY += deltaT * ropeAscSpeed;
            // Animate the water surface mask (lowering it as the bucket "fills" and rises)
            if (maskOffset > -0.25f) maskOffset -= deltaT * 2.0f;

            // Finish animation when bucket returns to the top
            if (bucketAnimY >= 1.14f) {
                bucketAnimY = 1.14f;
                ropeAnimY = 1.14f;
                currentWellState = W_IDLE;
                bucketIsOnGround = true; // Swap logic: The full bucket is now "placed" on the floor
            }
        }

        // --- DYNAMIC ROPE GEOMETRY CALCULATIONS ---
        // Adjust the bottom of the rope to the bucket's handle height
        float ropeBottomY = ropeAnimY - HANDLE_OFFSET;
        // Calculate current rope length for scaling the cylinder mesh
        float currentLength = BEAM_Y - ropeBottomY;
        // Find the center point to position the rope segment correctly
        float midPointY = (BEAM_Y + ropeBottomY) / 2.0f;

        // --- PROCEDURAL SPLASH LOGIC (Sine Wave Simulation) ---
        // If the bucket is hitting the water level, simulate 8 bouncing "splash cubes"
        if (bucketAnimY <= WATER_LEVEL && !bucketIsOnGround) {
            float t = (float) glfwGetTime();
            for (int i = 0; i < 8; i++) {
                // Create unique frequencies and phases for chaotic movement
                float freq = 12.0f + (i * 1.5f);
                float phase = (float) i * 0.8f;
                // Calculate vertical jump using a sine wave, clamped at 0.0
                splashJump[i] = std::max(0.0f, (float) sin(t * freq + phase) * 0.25f);
            }
        } else {
            // Disable splashes when the bucket is above water or on the ground
            for (int i = 0; i < 8; i++) splashJump[i] = 0.0f;
        }

        // Calculate forward direction for bottle detection
        glm::vec3 forwardDir = glm::vec3(glm::rotate(glm::mat4(1.0f), Yaw, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1));

        //Drunk Effect
        if (DrunkEffectManager::canDrink(Pos, forwardDir) && !canTeleport && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            if (!debounce) {
                debounce = true;
                curDebounce = GLFW_KEY_E;
                DrunkEffectManager::drink();
            }else {
                if ((curDebounce == GLFW_KEY_E) && debounce) {
                    debounce = false;
                    curDebounce = 0;
                }

        }
        }

        // Update candle interaction cooldown
        if (candleCooldown > 0.0f) {
            candleCooldown -= deltaT;
        }

        //Pickup or drop candle (mutually exclusive with cooldown)
        if (!canTeleport && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !candleDebounce && candleCooldown <= 0.0f){
            // Try pickup first (only if not holding)
            if (CandleManager::canPickupCandle(Pos, forwardDir)) {
                CandleManager::pickupCandle();
                candleDebounce = true;
                candleCooldown = CANDLE_COOLDOWN_TIME;
            }
            // Try drop only if not picked up (only if holding)
            else if (CandleManager::canDropCandle(Pos, forwardDir)) {
                CandleManager::dropCandle();
                candleDebounce = true;
                candleCooldown = CANDLE_COOLDOWN_TIME;
            }
        }
        
        // Reset candle debounce when E key is released
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) {
            candleDebounce = false;
        }
        
        // --- DAY/NIGHT & SUNSET CYCLE START ---

        // Time Accumulator
        // Persistent variable to track the current rotation of the sun
        static float sunAngle = 0.0f;

        // Total real-world seconds for one full 360-degree cycle (5 minutes)
        float dayDuration = 300.0f;

        // Determine rotation speed: radians per second based on day duration
        float rotationSpeed = glm::radians(360.0f) / dayDuration;

        // Update angle based on frame delta time (deltaT)
        sunAngle += deltaT * rotationSpeed;

        // Sun Direction Calculation
        // Rotates the light vector around X (Rise/Set) with a fixed tilt on Y (-30 deg)
        // to simulate a more natural diagonal solar arc.
        glm::mat4 lightRot = glm::rotate(glm::mat4(1), glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
                             glm::rotate(glm::mat4(1), sunAngle, glm::vec3(1.0f, 0.0f, 0.0f));
        // Transform the default light vector (0,0,1) into the calculated world direction
        glm::vec3 currentLightDir = glm::vec3(lightRot * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

        // Atmosphere Color Definitions (RGBA)
        glm::vec4 dayColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Full Noon (White)
        glm::vec4 sunsetColor = glm::vec4(1.0f, 0.4f, 0.1f, 1.0f); // Horizon Transition (Orange/Red)
        glm::vec4 nightColor = glm::vec4(0.072f, 0.072f, 0.135f, 1.0f); // Midnight (Deep Blue)

        glm::vec4 currentLightColor;
        float blendFactor = 0.0f; // Interpolation factor for Skybox textures: 0 (Night), 1 (Day)

        // Phase Determination based on Sun Altitude
        // The 'y' component represents how high the sun is relative to the horizon
        float sunHeight = currentLightDir.y;

        // --- DISTANCE-BASED LIGHT ACTIVATION ---
        // Switch between lamps (near origin) and candles/study lights (far from origin)
        float distFromOrigin = glm::length(Pos);

        if (distFromOrigin < 800.0f) {
            // Near origin: activate lamps with dynamic color based on daylight
            plboData.numActiveLights = 0;

            // --- LOGICA LUCI DINAMICHE ---
            // lampIntensity va a 0 quando il sole è alto, e a 1 quando il sole scende
            float lampIntensity = glm::clamp(1.0f - (sunHeight + 0.1f) / 0.3f, 0.0f, 1.0f);

            // Moltiplichiamo per 10.0f per renderle MOLTO più luminose
            glm::vec3 warmAmber = glm::vec3(1.0f, 0.5f, 0.1f);
            float brightness = 3.0f;
            glm::vec3 currentLampColor = warmAmber * (lampIntensity * brightness);

            // Load lamp lights from storage and apply dynamic color
            for (const auto& light : lampLights) {
                if (plboData.numActiveLights >= 100) break;
                plboData.lights[plboData.numActiveLights].position = light.position;
                plboData.lights[plboData.numActiveLights].color = currentLampColor;
                plboData.numActiveLights++;
            }
        } else {
            // Far from origin: activate candles and study lights only
            plboData.numActiveLights = 0;

            // Add candle lights
            for (const auto& light : candleLights) {
                if (plboData.numActiveLights >= 100) break;
                if (CandleManager::isHoldingCandle && CandleManager::candlePositions[CandleManager::heldCandleId] == light.position) break;
                plboData.lights[plboData.numActiveLights].position = light.position;
                plboData.lights[plboData.numActiveLights].color = light.color;
                plboData.numActiveLights++;
            }

            // Add study lights
            for (const auto& light : studyLights) {
                if (plboData.numActiveLights >= 100) break;
                plboData.lights[plboData.numActiveLights].position = light.position;
                plboData.lights[plboData.numActiveLights].color = light.color;
                plboData.numActiveLights++;
            }
        }

        // --- ADD HELD CANDLE LIGHT ---
        // If player is holding a candle, add a dynamic light that follows them
        if (CandleManager::isHoldingCandle && plboData.numActiveLights < 100) {
            glm::vec3 candleLightPos = CandleManager::getCandleLightPosition(Pos, Yaw);
            plboData.lights[plboData.numActiveLights].position = candleLightPos;
            plboData.lights[plboData.numActiveLights].color = glm::vec3(0.42f, 0.22f, 0.06f); // Warm candle color
            plboData.numActiveLights++;
        }

        // --- LIGHTING PHASES: DAY vs SUNSET vs NIGHT ---

        if (sunHeight > 0.2f) {
            // PHASE: FULL DAY
            // Smooth transition from Sunset Orange to Day White as sun goes up
            float t = glm::clamp((sunHeight - 0.2f) / 0.3f, 0.0f, 1.0f);
            currentLightColor = mix(sunsetColor, dayColor, t);

            blendFactor = 1.0f; // Use Full Day MMTexture
        } else if (sunHeight > -0.2f) {
            // PHASE: TRANSITION (Sunrise/Sunset)
            // The sun is currently crossing the horizon line [-0.2 to 0.2]

            // Normalize sun height to a 0.0 - 1.0 factor for texture blending
            blendFactor = (sunHeight + 0.2f) / 0.4f;

            if (sunHeight > 0.0f) {
                // Just above the horizon: Locked to Sunset Orange
                currentLightColor = sunsetColor;
            } else {
                // Just below the horizon: Fade from Orange into Night Blue
                float t = (sunHeight + 0.2f) / 0.2f;
                currentLightColor = mix(nightColor, sunsetColor, t);
            }
        } else {
            // PHASE: FULL NIGHT
            currentLightColor = nightColor;
            blendFactor = 0.0f; // Display Night Skybox texture
        }

        // 5. Update Global Uniforms
        // Package all environmental data into the GUBO to be sent to shaders
        GlobalUniformBufferObject gubo{};
        gubo.lightDir = currentLightDir; // Updates shadows/light directions
        gubo.lightColor = currentLightColor; // Updates global ambient/diffuse color
        gubo.eyePos = cameraPos; // Required for specular highlights
        gubo.time = (float) glfwGetTime(); // Required for wind/sway vertex animations
        gubo.eyePos = cameraPos;

        // --- PLAYER CHARACTER RENDERING LOGIC ---
        // Calculate transparency based on distance (Dither/Fade effect)
        float distToPlayer = glm::distance(cameraPos, Pos + glm::vec3(0.0f, 1.2f, 0.0f));
        float fadeStart = 1.5f;
        float fadeEnd = 0.5f;
        // playerAlpha goes from 1.0 (opaque) to 0.0 (invisible)
        float playerAlpha = glm::clamp((distToPlayer - fadeEnd) / (fadeStart - fadeEnd), 0.0f, 1.0f);

        UniformBufferObjectChar uboc{};
        uboc.debug1 = debug1;
        uboc.debug1.w = playerAlpha; // Pass transparency to the fragment shader

        // Sample the current frame of the animation blender
        SKA.Sample(AB);
        std::vector<glm::mat4> *TMsp = SKA.getTransformMatrices();

        //printMat4("TF[55]", (*TMsp)[55]);

        // Build the base Model Matrix for the character (Scale -> Rotate -> Translate)
        glm::mat4 AdaptMat =
                glm::scale(glm::mat4(1.0f), glm::vec3(0.01f)) * glm::rotate(
                    glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(
                    glm::mat4(1.0f), glm::vec3(Pos.x * 100, Pos.z * 100, -Pos.y * 100)) * glm::rotate(
                    glm::mat4(1.0f), characterRotation, glm::vec3(0.0f, 0.0f, 1.0f));

        // In First Person View, we scale the player to 0 to hide the model from the camera
        if (isFirstPerson) {
            AdaptMat = glm::scale(AdaptMat, glm::vec3(0.0f));
        }

        for (Teleporter *tp: teleporters) {
            if (tp->CanTeleport(Pos, {Yaw, Pitch})) {
                canTeleport = true;
                activeTeleporter = tp;
                break;
            }
            canTeleport = false;
        }

        int instanceId;
        // Map the 65 bone matrices for skeletal animation
        for (instanceId = 0; instanceId < SC.TI[0].InstanceCount; instanceId++) {
            for (int im = 0; im < TMsp->size(); im++) {
                uboc.mMat[im] = AdaptMat * (*TMsp)[im];
                uboc.mvpMat[im] = ViewPrj * uboc.mMat[im];
                uboc.nMat[im] = glm::inverse(glm::transpose(uboc.mMat[im]));
                //std::cout << im << "\t";
                //printMat4("mMat", ubo.mMat[im]);
            }
            // Update GPU Descriptor Sets
            SC.TI[0].I[instanceId].DS[0][0]->map(currentImage, &gubo, 0); // Set 0, Binding 0
            SC.TI[0].I[instanceId].DS[0][0]->map(currentImage, &plboData, 1); // Set 0, Binding 1 (Lights)
            SC.TI[0].I[instanceId].DS[0][1]->map(currentImage, &uboc, 0); // Set 1, Binding 0 (Bones)
        }

        UniformBufferObjectSimp ubos{};

        // --- STATIC ENVIRONMENT RENDERING (TI[1]) ---
        for (instanceId = 0; instanceId < SC.TI[1].InstanceCount; instanceId++) {
            auto &inst = SC.TI[1].I[instanceId];
            ubos.mMat = glm::mat4(1.0f);

            // Dynamic Logic: Transform objects based on the Well State
            if (*inst.id == "well_rope_wire") {
                // Scale the rope cylinder based on the procedural length calculated earlier
                if (!bucketIsOnGround) {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, midPointY, 0.0f)) *
                                glm::scale(glm::mat4(1.0f), glm::vec3(0.025f, currentLength * 0.5f, 0.025f));
                } else {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -100.0f, 0.0f));
                }
            }
            else if (*inst.id == "well_bucket") {
                // Move the bucket attached to the rope
                if (!bucketIsOnGround) {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, bucketAnimY, 0.0f));
                } else {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -100.0f, 0.0f));
                }
            }
            else if (*inst.id == "spawned_bucket") {
                if (bucketIsOnGround) {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), groundedBucketPos);
                } else {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -100.0f, 0.0f));
                }
            }
            else if (*inst.id == "well_mask") {
                if (!bucketIsOnGround) {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, bucketAnimY + maskOffset, 0.0f)) *
                                glm::scale(glm::mat4(1.0f), glm::vec3(0.36f, 0.01f, 0.36f));
                } else {
                    ubos.mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -100.0f, 0.0f));
                }
            }
            else if (inst.id->find("well_splash_") != std::string::npos) {
                // Handle the 8 individual splash particles
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
            else {
                // Standard static object position from World Matrix
                ubos.mMat = inst.Wm;
            }

            ubos.mvpMat = ViewPrj * ubos.mMat;
            ubos.nMat = glm::inverse(glm::transpose(ubos.mMat));

            // Map data to GPU
            inst.DS[0][0]->map(currentImage, &gubo, 0);
            inst.DS[0][0]->map(currentImage, &plboData, 1);
            inst.DS[0][1]->map(currentImage, &ubos, 0);
        }

        // --- SKYBOX RENDERING ---
        // Center the skybox on the camera position and scale it to surround the scene
        skyBoxUniformBufferObject sbubo{};
        sbubo.mvpMat = ViewPrj * glm::translate(glm::mat4(1), cameraPos) * glm::scale(glm::mat4(1), glm::vec3(100.0f));
        sbubo.settings.x = blendFactor; // Controls Day/Night texture mixing
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

        // --- VEGETATION RENDERING (TI[3]) ---
        for (instanceId = 0; instanceId < SC.TI[3].InstanceCount; instanceId++) {
            ubos.mMat = SC.TI[3].I[instanceId].Wm;
            ubos.mvpMat = ViewPrj * ubos.mMat;
            ubos.nMat = glm::inverse(glm::transpose(ubos.mMat));

            // Global Data (Set 0, Binding 0) contains 'time' for the wind sway
            SC.TI[3].I[instanceId].DS[0][0]->map(currentImage, &gubo, 0);

            // Point Lights (Set 0, Binding 1) ensure trees are lit by lamps at night
            SC.TI[3].I[instanceId].DS[0][0]->map(currentImage, &plboData, 1);

            // Local Matrices (Set 1, Binding 0)
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

        // Updates the FPS
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
        }else if (DrunkEffectManager::canDrink(Pos, forwardDir)) {
            txt.print(-1.0f, -0.9f, "E to drink", 4, "CO",
                      false, false, true, TAL_LEFT, TRH_LEFT, TRV_TOP,
                      {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
        }else if (CandleManager::canPickupCandle(Pos, forwardDir)) {
        txt.print(-1.0f, -0.9f, "E to pickup candle", 4, "CO",
                  false, false, true, TAL_LEFT, TRH_LEFT, TRV_TOP,
                  {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
         }else if (CandleManager::canDropCandle(Pos, forwardDir)) {
            txt.print(-1.0f, -0.9f, "E to drop candle", 4, "CO",
                      false, false, true, TAL_LEFT, TRH_LEFT, TRV_TOP,
                      {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f});
        }
        else {
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
        // --- VIEW PARAMETERS ---
        const float FOVy = glm::radians(45.0f);
        const float nearPlane = 0.5f; // Prevents "near-clipping" inside house walls
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

        // --- INPUT ACQUISITION ---
        float deltaT;
        glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f); // 'r' won't be used for rotation
        bool fire = false;
        getSixAxis(deltaT, m, r, fire); // Retrieve keyboard/gamepad stick state

        // Disable all movement and rotation during cutscenes
        if (isCutscene) {
            m = glm::vec3(0.0f);
            r = glm::vec3(0.0f);
            fire = false;
        }

        //Implement Pad visual
        GLFWgamepadstate padState;
        //If the pad is connected
        if (glfwGetGamepadState(GLFW_JOYSTICK_1, &padState)) {
            float deadzone = 0.2f;
            float padRotSpeed = 2.5f * deltaT; //Pad rotation speed

            float rStickX = padState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
            float rStickY = padState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];

            //Update the stick in the dead zone, update Yaw and Pitch
            if (!isCutscene && std::abs(rStickX) > deadzone) {
                Yaw -= rStickX * padRotSpeed;
            }
            if (!isCutscene && std::abs(rStickY) > deadzone) {
                if (isFirstPerson) {
                    Pitch -= rStickY * padRotSpeed;
                } else {
                    Pitch += rStickY * padRotSpeed;
                }
            }
        }

        float MOVE_SPEED = fire ? MOVE_SPEED_RUN : MOVE_SPEED_BASE;

        // --- DYNAMIC CAMERA DISTANCE (TPV) ---
        // Smoothly interpolate camera distance when toggling "Wide View"
        const float DIST_NORMAL = 2.5f;
        const float DIST_WIDE = 6.0f;
        //Choose the target depending on isWideView status
        float targetDist = isWideView ? DIST_WIDE : DIST_NORMAL;
        currentCamDist += (targetDist - currentCamDist) * (1.0f - exp(-5.0f * deltaT));
        //Change the camera distance
        camDist = currentCamDist;

        ViewPrj = glm::mat4(1);
        World = glm::mat4(1);

        oldPos = Pos;

        // --- MOUSE LOOK & ORIENTATION ---
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

        // Disable mouse movement during cutscenes
        if (isCutscene) {
            xoffset = 0.0f;
            yoffset = 0.0f;
        }

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
            // FPV: Camera rotates directly with the mouse
            Yaw -= xoffset * (ROT_SPEED * mouseSensitivity) * deltaT;
            Pitch += yoffset * (ROT_SPEED * mouseSensitivity) * deltaT;

            // Clamping first person
            const float pitchLimit = glm::radians(89.0f);
            Pitch = Pitch < -pitchLimit ? -pitchLimit : (Pitch > pitchLimit ? pitchLimit : Pitch);
        } else {
            // TPV: Camera orbit rotation
            Yaw -= xoffset * (ROT_SPEED * mouseSensitivity) * deltaT;
            Pitch -= yoffset * (ROT_SPEED * mouseSensitivity) * deltaT;

            // Prevent camera from going too low (looking from below)
            const float minPitch_3rd = glm::radians(-10.0f);
            const float maxPitch_3rd = glm::radians(60.0f);

            Pitch = Pitch < minPitch_3rd ? minPitch_3rd : (Pitch > maxPitch_3rd ? maxPitch_3rd : Pitch);
        }
        
        DrunkEffectManager::drunkEffect(m, Yaw, Pitch, Roll, deltaT);

        float ef = exp(-10.0 * deltaT);

        // --- PROJECTION & VIEW MATRICES ---
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
            glm::vec3 target;
            if (isCutscene1) {
                // Cutscene 1: Camera fixed position, follow cast3 with look direction
                cameraPos = glm::vec3(357, 1, -104);
                target = castCurrentPos;
            } else if (isCutscene2) {
                // Cutscene 2: Camera rotates around cast3
                glm::vec3 cast3Center = glm::vec3(350, 0, -110);
                float radius = 4.5f; // Distance from cast3 in XZ plane
                float rotationSpeed = 0.1f; // Radians per second
                float angle = rotationSpeed * chaseTimer;

                float x = cast3Center.x + radius * cos(angle);
                float z = cast3Center.z + radius * sin(angle);
                cameraPos = glm::vec3(x, 7, z);
                target = castCurrentPos;
            } else {
                cameraPos = Pos + glm::vec3(0.0f, camHeight, 0.0f);
                target = cameraPos + front; // Normal forward look
            }

            View = glm::lookAt(cameraPos, target, up);

            // Player model (invisible) rotates with the camera
            World = glm::translate(glm::mat4(1), Pos) * glm::rotate(glm::mat4(1.0f), Yaw, glm::vec3(0, 1, 0));
        } else {
            // --- PLAYER MOVEMENT LOGIC ---
            Pos = Pos + MOVE_SPEED * m.x * ux * deltaT;
            Pos = Pos - MOVE_SPEED * m.z * uz * deltaT;

            float groundY = getGroundHeight(Pos);
            Pos.y = groundY;

            camHeight += MOVE_SPEED * m.y * deltaT;

            // Character Model Rotation handling
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

            // --- CAMERA COLLISION LOGIC (BUMPING) ---

            // Define the target (where the camera looks: player's head area)
            glm::vec3 target;
            if (isCutscene1) {
                // Cutscene 1: Camera fixed position, follow cast3 with look direction
                target = castCurrentPos;
            } else if (isCutscene2) {
                // Cutscene 2: To be implemented
                target = castCurrentPos;
            } else {
                target = Pos + glm::vec3(0.0f, camHeight, 0.0f); // Normal target
            }

            // 2. Create a rotation matrix based on current Yaw
            glm::mat4 camWorld = glm::translate(glm::mat4(1), Pos) * glm::rotate(
                                     glm::mat4(1.0f), Yaw, glm::vec3(0, 1, 0));

            // Skip collision detection and camera positioning during cutscenes
            if (isCutscene1) {
                // Fixed camera position during cutscenes
                cameraPos = glm::vec3(357, 1, -104);
                dampedCamPos = cameraPos;
                View = glm::lookAt(dampedCamPos, target, glm::vec3(0, 1, 0));
            } else if (isCutscene2) {
                // Cutscene 2: Camera rotates around cast3
                glm::vec3 cast3Center = glm::vec3(350, 0, -110);
                float radius = 4.5f; // Distance from cast3 in XZ plane
                float rotationSpeed = 0.1f; // Radians per second
                float angle = rotationSpeed * chaseTimer;

                float x = cast3Center.x + radius * cos(angle);
                float z = cast3Center.z + radius * sin(angle);
                cameraPos = glm::vec3(x, 7, z);
                dampedCamPos = cameraPos;
                View = glm::lookAt(dampedCamPos, target, glm::vec3(0, 1, 0));
            } else {
                // Normal camera behavior with collision detection
                // Progressive check along the camera vector to detect obstacles
                float finalCamDist = camDist; // Start with the desired distance
                const int SAMPLES = 12; // Number of collision checks along the ray
                float cameraRadius = 0.4f; // Thickness of the camera's physical presence

                for (int i = 1; i <= SAMPLES; i++) {
                    // Calculate current test distance from player to camera
                    float t = (float) i / (float) SAMPLES;
                    float checkDist = camDist * t;

                    // Position of the camera at this specific step
                    glm::vec3 testPos = camWorld * glm::vec4(0.0f, camHeight + checkDist * sin(Pitch),
                                                             checkDist * cos(Pitch), 1.0);

                    //if (cameraPos.y < 0.2f) {
                    //    cameraPos.y = 0.2f;
                    //}
                    // Create a temporary collision volume for the camera
                    CollisionObject camHitbox;
                    camHitbox.addBox(testPos, glm::vec3(cameraRadius), CollisionBox::sphere);

                    // Check against all existing house hitboxes
                    bool collisionDetected = false;
                    for (const auto &house: houseCollisions) {
                        if (camHitbox.collidesWith(house)) {
                            collisionDetected = true;
                            break;
                        }
                    }

                    // If a collision is found, shorten the camera distance immediately
                    if (collisionDetected) {
                        // Stop at the previous safe step (closer to the player)
                        finalCamDist = camDist * ((float) (i - 1) / (float) SAMPLES);
                        break;
                    }
                }

                // Calculate the FINAL position (either the ideal one or the shortened one)
                cameraPos = camWorld * glm::vec4(0.0f, camHeight + finalCamDist * sin(Pitch), finalCamDist * cos(Pitch),
                                                 1.0);

                // Floor constraint: don't let camera go under the grass
                if (cameraPos.y < 0.2f) {
                    cameraPos.y = 0.2f;
                }

                // Camera Teleport logic for respawns or TP
                if (resetCamera) {
                    dampedCamPos = cameraPos;
                    dampedRelDir = relDir;
                    resetCamera = false;
                }

                // Apply damping for smooth camera tracking
                dampedCamPos = ef * dampedCamPos + (1.0f - ef) * cameraPos;
                View = glm::lookAt(dampedCamPos, target, glm::vec3(0, 1, 0));
            } // End of non-cutscene camera behavior
        }
        // ===============================
        // COLLISION CHECK (COMMON)
        // ===============================
        CollisionObject playerCol;
        playerCol.addBox(
            Pos + glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(1, 2.0f, 1),
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

float E09::getGroundHeight(const glm::vec3 &pos) {
    // ---------- BRIDGE ----------
    if (pos.x > 215.0f && pos.x < 265.0f &&
        pos.z > -10.0f && pos.z < 10.0f) {
        return -1.1f;
    }
    // ---------- RAMP LEFT ----------
    if (pos.x >= 210.0f && pos.x <= 233.0f) {
        float t = (pos.x - 210.0f) / 23.0f; // 0 → 1
        return glm::mix(0.0f, -4.89f, t);
    }

    // ---------- RIVER BED ----------
    if (pos.x > 233.0f && pos.x < 247.0f) {
        return -4.89f;
    }

    // ---------- RAMP RIGHT ----------
    if (pos.x >= 247.0f && pos.x <= 270.0f) {
        float t = (pos.x - 247.0f) / 23.0f; // 0 → 1
        return glm::mix(-4.89f, 0.0f, t);
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
