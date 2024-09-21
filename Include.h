#pragma once
#ifndef INCLUDE_H
#define INCLUDE_H

#undef APIENTRY

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <GL/glut.h>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <vector>
#include <iostream>

// From pnp:
std::vector<cv::Point2f> convert2dPointToCV(const std::vector<glm::vec2>& points);
std::vector<cv::Point3f> convert3dPointToCV(const std::vector<glm::vec3>& points);


// From camera:
void CameraViewTriangleRenderer(const glm::vec3& position, const glm::vec3& direction, bool flag);
void CameraPathRenderer();
struct CameraInformation saveCameraInfo();
void CameraImageLoader(GLFWwindow* window);
void NextCameraInfoLoader();
void CameraUpdater();
void CameraParameterLoader(glm::vec3 calculatedPos, float calcYaw, float calcPitch);

// From draw:
void drawTeapot();

void KeyPressProcessor(unsigned char input, int x, int y);
void KeyReleaseUpdater(unsigned char input, int x, int y);
void SpecialKeyPressUpdater(int input, int x, int y);
void SpecialKeyReleaseUpdater(int input, int x, int y);
void InteractionHandler(unsigned char input, int x, int y);
std::vector<glm::vec3> pointsGenerator(int k);

// From render:
void leftNormalViewportRenderer();
void rightNormalViewportRenderer();
void normalStateRenderer();
void sceneRenderer();
glm::vec3 pointGetter(int x, int y);
void setupRightViewport();
void drawPoints(const glm::vec3& threeDPoint, glm::vec3& color);

// Global variables:
// General states:
extern bool isLookAround;

// Window dimensions
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

// Camera transformation
extern glm::vec3 Position;
extern glm::vec3 fwrd;
extern glm::vec3 cUp;

// Camera rotation
extern float horiAngle;
extern float vertiAngle;

// Saved camera state
extern glm::vec3 savedCmrPos;
extern glm::vec3 savedCmrFront;
extern float rememberYaw;
extern float rememberPitch;

// Object transformation
extern glm::vec3 objPos;
extern float objRotX;
extern float objRotY;

// Image storage
extern std::vector<unsigned char> imageInfoVec;

struct CameraInformation {
    glm::vec3 position;
    glm::vec3 cFwrd;
    float horizAngle;
    float verticAngle;
    std::vector<unsigned char> infoImageVec;
};

struct PressedKey {
    bool w = false;
    bool a = false;
    bool s = false;
    bool d = false;
    bool r = false;
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
};

struct MouseClickCoords {
    double x;
    double y;
};

// Vector to store all click coordinates
extern std::vector<MouseClickCoords> currCoords;

extern PressedKey pKey;

// Saved camera states
extern std::vector<CameraInformation> savedCmrInfo;
extern int currCmrInfoIdx;


extern std::vector<glm::vec3> cameraRoute;

extern CameraInformation lastInformation;
extern CameraInformation lastPickingInformation;
extern CameraInformation cameraPnpSol;

struct Sphere {
    glm::vec3 center;
    float radius;
};

// Declare global variables
extern std::vector<Sphere> spheres;

// Point definitions:
//extern glm::vec3 colors[8];
extern std::vector<glm::vec3> pointLocations;
extern std::vector<glm::vec3> pointColors; 

#endif

void renderPointsInViewport(bool isLeftViewport);
