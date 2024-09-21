#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Include.h"
#include <opencv2/opencv.hpp>
using namespace cv;
extern glm::vec3 upVectorPnP;
// Define your virtual camera intrinsic parameters
float fov = 45.0f; // Field of view in degrees
float aspectRatio = static_cast<float>(WINDOW_WIDTH / 2) / WINDOW_HEIGHT;
float fovRad = glm::radians(fov);
float fy = (WINDOW_HEIGHT / 2.0f) / tan(fovRad / 2.0f);
float fx = fy * aspectRatio;
const float cx = WINDOW_WIDTH / 4;
const float cy = WINDOW_HEIGHT / 2;


std::vector<cv::Point2f> convert2dPointToCV(const std::vector<glm::vec2>& points) {
    std::vector<cv::Point2f> cvPoints;
    for (const auto& point : points) {
        cvPoints.emplace_back(point.x, point.y);
    }
    return cvPoints;
}

// Convert glm::vec3 to cv::Point3f
std::vector<cv::Point3f> convert3dPointToCV(const std::vector<glm::vec3>& points) {
    std::vector<cv::Point3f> cvPoints;
    for (const auto& point : points) {
        cvPoints.emplace_back(point.x, point.y, point.z);
    }
    return cvPoints;
}
