#include "Include.h"

// Window dimensions
const int WINDOW_WIDTH = 1152;
const int WINDOW_HEIGHT = 648;

// Camera transformation
glm::vec3 Position = glm::vec3(0.0f, 0.0f, 5.0f);
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
bool isLoad = false;
bool isPicking = false;
bool chooseState = false;

std::vector<glm::vec3> cameraRoute;

CameraInformation lastInformation;
CameraInformation lastPickingInformation;
CameraInformation cameraPnpSol;

PressedKey pKey;

// Initialize the vector to store click coordinates
std::vector<MouseClickCoords> currCoords;

MouseClick mouseInputs;

glm::vec3 colors[8] = {
	glm::vec3(0.3f, 0.7f, 0.9f), // Sky blue
	glm::vec3(0.8f, 0.1f, 0.8f), // Fuchsia
	glm::vec3(0.1f, 0.8f, 0.5f), // Sea green
	glm::vec3(0.9f, 0.5f, 0.2f), // Copper
	glm::vec3(0.6f, 0.2f, 0.6f), // Amethyst
	glm::vec3(0.4f, 0.6f, 0.9f), // Cerulean
	glm::vec3(0.9f, 0.3f, 0.1f), // Tangerine
	glm::vec3(0.7f, 0.4f, 0.8f)  // Lavender
};