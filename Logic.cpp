#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Include.h"
#include <opencv2/opencv.hpp>

using namespace cv;

extern glm::vec3 upVectorPnP;
std::vector<std::pair<glm::vec2, glm::vec3>> correspondences; // Stores 2D (x, y) to 3D correspondences
std::vector<unsigned char> savedCameraImage;


// Define your virtual camera intrinsic parameters
float fov = 45.0f; // Field of view in degrees
float aspectRatio = static_cast<float>(WINDOW_WIDTH / 2) / WINDOW_HEIGHT;
float fovRad = glm::radians(fov);
float fy = (WINDOW_HEIGHT / 2.0f) / tan(fovRad / 2.0f);
float fx = fy * aspectRatio;
const float cx = WINDOW_WIDTH / 4;
const float cy = WINDOW_HEIGHT / 2;

void printCorrespondences() {
    std::cout << "2D-3D Correspondences:" << std::endl;
    for (const auto& correspondence : correspondences) {
        const glm::vec2& pixelPos = correspondence.first;
        const glm::vec3& point3D = correspondence.second;

        // Print the 2D pixel coordinates and the corresponding 3D point
        std::cout << "2D: (" << pixelPos.x << ", " << pixelPos.y << ")  ->  "
            << "3D: (" << point3D.x << ", " << point3D.y << ", " << point3D.z << ")" << std::endl;
    }

    std::cout << "Total correspondences: " << correspondences.size() << std::endl;
}


void extract2D3DCorrespondences() {
    // Clear any previous correspondences
    correspondences.clear();

    // Create a copy of pointColors, which will be modified as we encounter colors
    std::vector<glm::vec3> remainingColors = pointColors;

    // Get the viewport size for the right side
    int width = WINDOW_WIDTH / 2;
    int height = WINDOW_HEIGHT;

    // Allocate memory for pixel data (RGB)
    std::vector<unsigned char> pixelData(3 * width * height);

    // Read pixels from the right viewport
    glReadPixels(width, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixelData.data());

    // Loop over each pixel in the viewport
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Get the pixel color at (x, y)
            int pixelIndex = (y * width + x) * 3;
            glm::vec3 pixelColor(pixelData[pixelIndex] / 255.0f, pixelData[pixelIndex + 1] / 255.0f, pixelData[pixelIndex + 2] / 255.0f);

            // Check if the pixel color matches any of the remaining colors
            for (size_t i = 0; i < remainingColors.size(); ++i) {
                if (remainingColors[i] == glm::vec3(-1.0f, -1.0f, -1.0f)) {
                    continue; // Skip colors that have already been processed
                }

                if (glm::distance(pixelColor, remainingColors[i]) < 0.01f) {  // Allow for slight color variance
                    // We found a matching point, so save the 2D-3D correspondence
                    glm::vec2 pixelPos(x, y);        // 2D position (in the viewport)
                    glm::vec3 corresponding3D = pointLocations[i]; // Corresponding 3D point

                    // Store the correspondence
                    correspondences.push_back(std::make_pair(pixelPos, corresponding3D));

                    // Mark this color as processed by setting it to an invalid color
                    remainingColors[i] = glm::vec3(-1.0f, -1.0f, -1.0f);
                    break;  // Move to the next pixel
                }
            }
        }
    }
    printCorrespondences();
}

void convertCorrespondencesForCV(std::vector<cv::Point3f>& objectPoints, std::vector<cv::Point2f>& imagePoints) {
    objectPoints.clear();
    imagePoints.clear();

    // Convert correspondences from glm::vec types to OpenCV types
    for (const auto& correspondence : correspondences) {
        const glm::vec2& pixelPos = correspondence.first;
        const glm::vec3& point3D = correspondence.second;

        objectPoints.emplace_back(point3D.x, point3D.y, point3D.z);
        imagePoints.emplace_back(pixelPos.x, pixelPos.y);
    }
}

bool runSolvePnP(const std::vector<cv::Point3f>& objectPoints, const std::vector<cv::Point2f>& imagePoints, cv::Mat& rvec, cv::Mat& tvec) {
    // Define the camera matrix (intrinsic parameters)
    cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) <<
        fx, 0, cx,
        0, fy, cy,
        0, 0, 1);

    // Define distortion coefficients (assuming none for simplicity)
    cv::Mat distCoeffs = cv::Mat::zeros(4, 1, CV_64F);

    // Call solvePnP
    return cv::solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec);
}

void handlePnPResults(const cv::Mat& rvec, const cv::Mat& tvec) {
    // Calculate rotation matrix using Rodrigues
    cv::Mat R;
    cv::Rodrigues(rvec, R);

    // Adjust rotation matrix to align with OpenGL's coordinate system
    cv::Mat adjustY = (cv::Mat_<double>(3, 3) <<
        1, 0, 0,
        0, -1, 0,
        0, 0, 1);
    R = adjustY * R;

    // Convert rotation matrix to glm::mat3
    glm::mat3 rotationMatrix(
        R.at<double>(0, 0), R.at<double>(0, 1), R.at<double>(0, 2),
        R.at<double>(1, 0), R.at<double>(1, 1), R.at<double>(1, 2),
        R.at<double>(2, 0), R.at<double>(2, 1), R.at<double>(2, 2)
    );

    // Translation vector
    glm::vec3 translation(
        tvec.at<double>(0),
        tvec.at<double>(1),
        tvec.at<double>(2)
    );

    // Calculate the camera position in world space
    glm::vec3 cameraPosition = -glm::transpose(rotationMatrix) * translation;
    cameraPosition.y;

    // Calculate yaw and pitch based on the rotation matrix
    glm::vec3 front;
    front.x = rotationMatrix[2][0];
    front.y = rotationMatrix[2][1];
    front.z = rotationMatrix[2][2];
    front = glm::normalize(front);

    // Calculate yaw (horizontal angle) and pitch (vertical angle)
    float yaw = glm::degrees(atan2(front.z, front.x)) + 180.0f;  // Flip yaw by 180 degrees
    float pitch = -glm::degrees(asin(front.y));

    // Update the camera position, yaw, and pitch
    CameraParameterLoader(cameraPosition, yaw, pitch);

    // Capture the right viewport (camera view) after solvePnP
    int width = WINDOW_WIDTH / 2;
    int height = WINDOW_HEIGHT;
    std::vector<unsigned char> capturedImage(static_cast<size_t>(3) * static_cast<size_t>(width) * static_cast<size_t>(height));
    glReadPixels(width, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, capturedImage.data());

    // Save the image for overlay
    savedCameraImage = std::move(capturedImage);

    // Set flag to true indicating solvePnP is done
    isPnPCompleted = true;
}


// Wrapper function that ties everything together
void extractAndSolvePnP() {
    // Step 1: Extract 2D-3D correspondences
    extract2D3DCorrespondences();

    // Step 2: Convert correspondences for OpenCV
    std::vector<cv::Point3f> objectPoints;
    std::vector<cv::Point2f> imagePoints;
    convertCorrespondencesForCV(objectPoints, imagePoints);

    // Step 3: Run solvePnP
    cv::Mat rvec, tvec;
    bool success = runSolvePnP(objectPoints, imagePoints, rvec, tvec);



    // Step 4: Handle the results
    if (success) {
        handlePnPResults(rvec, tvec);
    }
    else {
        std::cerr << "solvePnP failed!" << std::endl;
    }
}

