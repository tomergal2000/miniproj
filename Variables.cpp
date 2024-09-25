#include "Include.h"

// Window dimensions
const int WINDOW_WIDTH = 1152;
const int WINDOW_HEIGHT = 648;

// Camera transformation
glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 fwrd = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Camera rotation
float horiAngle = -90.0f; // Initialize horizontal angle to -90.0 degrees to align with the initial cam forward
float vertiAngle = 0.0f;

// Saved camera state
glm::vec3 savedCmrPos;
glm::vec3 savedCmrFront;
float rememberYaw;
float rememberPitch;


// Object transformation
glm::vec3 objPos = glm::vec3(0.0f, 0.0f, 0.0f);
float objRotX = 0.0f;
float objRotY = 0.0f;

// Image storage
std::vector<unsigned char> imageInfoVec;

// Saved camera states
std::vector<CameraInformation> savedCmrInfo;
int currCmrInfoIdx = 0;

std::vector<glm::vec3> cameraRoute;

CameraInformation lastInformation;
CameraInformation cameraPnpSol;
glm::vec3 upVectorPnP;
bool isTogglingCameraStates = false; // Initialize as false

PressedKey pKey;

extern std::vector<glm::vec3> pointLocations = {
    glm::vec3(-0.308449, 0.108678, 0.828841),
    glm::vec3(0.066533, -0.239370, 0.984600),
    glm::vec3(0.133617, 0.301779, 0.785580),
    glm::vec3(-0.647459, -0.256219, 0.759673),
    glm::vec3(0.647833, 0.317597, 0.449176),
    glm::vec3(0.699621, -0.291555, 0.702944),
    glm::vec3(0.441365, -0.043581, 0.832323),
    glm::vec3(1.071001, -0.250644, 0.231390),
    glm::vec3(1.450298, 0.405207, 0.089928),
    glm::vec3(-1.282548, -0.156362, 0.096585),
    glm::vec3(-0.989002, 0.307766, 0.093595),
    glm::vec3(-1.419127, 0.183090, 0.110749),
    glm::vec3(0.002757, 0.721196, 0.175685),
    glm::vec3(-0.389817, 0.397841, 0.647559),
    glm::vec3(0.061143, 0.574395, 0.065846),
    glm::vec3(1.347760, -0.024800, -0.048987),
    glm::vec3(1.212221, -0.302023, -0.068014),
    glm::vec3(0.781880, 0.305278, -0.141630),
    glm::vec3(0.880842, -0.153975, -0.416005),
    glm::vec3(0.774332, 0.157814, -0.384450),
    glm::vec3(0.664036, -0.331547, -0.740950),
    glm::vec3(0.433012, 0.276268, -0.678819),
    glm::vec3(0.436972, -0.024666, -0.823841),
    glm::vec3(0.369538, 0.484912, -0.132120),
    glm::vec3(0.102720, 0.490823, -0.333852),
    glm::vec3(0.136536, 0.138393, -0.852776),
    glm::vec3(-0.162180, 0.513635, -0.154918),
    glm::vec3(0.001832, 0.706638, -0.168473),
    glm::vec3(0.147036, -0.379243, -0.979532),
    glm::vec3(-0.303832, 0.116360, -0.824148),
    glm::vec3(-0.209537, -0.257004, -0.970786),
    glm::vec3(-0.748833, 0.276410, -0.293073),
    glm::vec3(-0.738760, -0.273868, -0.661690),
    glm::vec3(-0.620755, 0.002601, -0.683625),
    glm::vec3(-0.290948, 0.356814, -0.714065),
    glm::vec3(-0.581049, 0.389851, -0.485323),
    glm::vec3(-1.058821, 0.276515, -0.111486),
    glm::vec3(-1.095947, -0.341060, -0.111468),
    glm::vec3(-1.447946, 0.072557, -0.101323),
    glm::vec3(1.121704, -0.086714, -0.185901),
    glm::vec3(1.382458, 0.343283, -0.094736),
    glm::vec3(0.110684, -0.100818, -0.949602),
    glm::vec3(-0.496621, -0.554999, -0.764019),
    glm::vec3(0.360811, -0.603048, -0.795327),
    //TOP:
    glm::vec3(-0.479981,0.470951,-0.033954),
    glm::vec3(0.338919,0.465726,-0.361303),
    glm::vec3(0.066983,0.761826,0.133725),
    glm::vec3(-0.157624,0.469672,0.460073),
    glm::vec3(0.452753,0.456075,0.314161),
    //BOTTOM:
    glm::vec3(0.379137, -0.768555, 0.503808),
    glm::vec3(-0.166595, -0.790777, 0.090339),
    glm::vec3(0.213184, -0.790062, 0.145157),
    glm::vec3(-0.372306, -0.780183, 0.354519),
    glm::vec3(0.221517, -0.786941, -0.3006495),
    glm::vec3(0.529498, -0.775230, 0.230367),
    glm::vec3(-0.231264, -0.782391, 0.421961),
    glm::vec3(-0.536819, -0.776760, -0.190449),
    glm::vec3(-0.051200, -0.736386, -0.740976)
};

extern std::vector<glm::vec3> pointColors = {
glm::vec3(1.0f, 0.0f, 0.0f),   // Red
glm::vec3(0.0f, 1.0f, 0.0f),   // Green
glm::vec3(0.0f, 0.0f, 1.0f),   // Blue
glm::vec3(1.0f, 1.0f, 0.0f),   // Yellow
glm::vec3(1.0f, 0.0f, 1.0f),   // Magenta
glm::vec3(0.0f, 1.0f, 1.0f),   // Cyan
glm::vec3(0.5f, 0.5f, 0.5f),   // Gray
glm::vec3(0.6f, 0.0f, 0.0f),   // Dark Red
glm::vec3(0.0f, 0.6f, 0.0f),   // Dark Green
glm::vec3(0.0f, 0.0f, 0.6f),   // Dark Blue
glm::vec3(0.7f, 0.7f, 0.0f),   // Olive
glm::vec3(0.7f, 0.0f, 0.7f),   // Purple
glm::vec3(1.0f, 0.5f, 0.2f),   // Bright Orange
glm::vec3(0.3f, 1.0f, 0.7f),   // Turquoise
glm::vec3(1.0f, 0.4f, 0.7f),   // Pink
glm::vec3(0.9f, 0.9f, 0.9f),   // Light Gray
glm::vec3(1.0f, 0.8f, 0.4f),   // Gold
glm::vec3(0.2f, 0.2f, 1.0f),   // Royal Blue
glm::vec3(0.8f, 0.3f, 1.0f),   // Lavender
glm::vec3(1.0f, 0.6f, 0.6f),   // Light Coral
glm::vec3(0.5f, 1.0f, 0.4f),   // Light Green
glm::vec3(0.6f, 0.4f, 1.0f),   // Indigo
glm::vec3(0.7f, 0.4f, 0.2f),   // Brown
glm::vec3(1.0f, 0.2f, 0.7f),   // Hot Pink
glm::vec3(0.9f, 0.7f, 0.4f),   // Bronze
glm::vec3(0.8f, 1.0f, 0.2f),   // Lemon
glm::vec3(1.0f, 0.9f, 0.2f),   // Bright Yellow
glm::vec3(0.2f, 0.9f, 0.6f),   // Aqua
glm::vec3(1.0f, 0.2f, 0.4f),   // Ruby Red
glm::vec3(0.8f, 0.7f, 1.0f),   // Soft Lilac
glm::vec3(0.5f, 1.0f, 0.6f),   // Mint Green
glm::vec3(1.0f, 0.5f, 0.9f),   // Rose Pink
glm::vec3(0.4f, 0.7f, 1.0f),   // Sky Blue
glm::vec3(1.0f, 0.3f, 0.6f),   // Deep Pink
glm::vec3(0.7f, 0.8f, 0.9f),   // Soft Blue Gray
glm::vec3(1.0f, 0.4f, 0.4f),   // Cherry Red
glm::vec3(0.6f, 0.4f, 0.9f),   // Orchid Purple
glm::vec3(0.4f, 0.6f, 1.0f),   // Ice Blue
glm::vec3(0.7f, 1.0f, 0.3f),   // Lime
glm::vec3(0.9f, 0.5f, 0.7f),   // Light Violet
glm::vec3(1.0f, 0.9f, 0.5f),   // Sand Yellow
glm::vec3(0.3f, 1.0f, 0.5f),   // Bright Mint
glm::vec3(1.0f, 0.7f, 0.2f),   // Goldenrod
glm::vec3(0.7f, 1.0f, 0.7f),   // Bright Green
glm::vec3(1.0f, 0.4f, 0.8f),   // Mauve
glm::vec3(0.6f, 0.8f, 1.0f),   // Steel Blue
glm::vec3(1.0f, 0.5f, 0.3f),   // Burnt Orange
glm::vec3(0.3f, 1.0f, 0.9f),   // Light Aquamarine
glm::vec3(0.9f, 0.3f, 0.2f),   // Dark Coral
glm::vec3(0.4f, 1.0f, 0.4f),   // Bright Lime
glm::vec3(1.0f, 0.7f, 0.8f),   // Pale Pink
glm::vec3(0.6f, 0.9f, 1.0f),   // Light Blue
glm::vec3(1.0f, 0.9f, 0.4f),   // Light Gold
glm::vec3(0.7f, 0.6f, 0.3f),   //
glm::vec3(0.93f, 0.57f, 0.13f),  // Pumpkin Orange
glm::vec3(0.45f, 0.76f, 0.27f),  // Forest Green
glm::vec3(0.15f, 0.65f, 0.90f),  // Azure Blue
glm::vec3(0.88f, 0.09f, 0.42f),  // Crimson
glm::vec3(0.91f, 0.85f, 0.30f),  // Golden Yellow
glm::vec3(0.24f, 0.45f, 0.96f),  // Royal Blue
glm::vec3(0.78f, 0.28f, 0.25f),  // Brick Red
glm::vec3(0.35f, 0.18f, 0.70f),  // Deep Purple
glm::vec3(0.65f, 0.85f, 0.23f),  // Chartreuse
glm::vec3(0.98f, 0.66f, 0.12f),  // Amber
glm::vec3(0.72f, 0.50f, 0.19f),  // Mustard
glm::vec3(0.18f, 0.50f, 0.58f),  // Teal
glm::vec3(0.95f, 0.18f, 0.10f),  // Bright Red
};

//glm::vec3 colors[8] = {
//    glm::vec3(1.0f, 0.5f, 0.8f), // Pink
//    glm::vec3(0.9f, 0.2f, 0.5f), // Raspberry
//    glm::vec3(0.2f, 1.0f, 0.2f), // Lime
//    glm::vec3(0.7f, 0.3f, 0.1f), // Rust
//    glm::vec3(0.5f, 0.1f, 0.5f), // Purple
//    glm::vec3(0.5f, 0.4f, 1.0f), // Periwinkle
//    glm::vec3(0.8f, 0.6f, 0.1f), // Bronze
//    glm::vec3(0.8f, 0.8f, 0.0f)  // Gold
//};

