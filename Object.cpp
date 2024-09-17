#include "Include.h"

/*


 */
void pickObject(GLFWwindow* window, int x, int y) {

}

std::vector<glm::vec3> pointsGenerator(int k) {
    std::vector<glm::vec3> points;
    for (int i = 0; i < k; ++i) {
        points.push_back(glm::vec3(rand() % 10 - 5, rand() % 10 - 5, rand() % 10 - 5));
    }
    return points;
}

/*


 */
void drawPoints(const std::vector<glm::vec3>& points) {
    glBegin(GL_POINTS);
    for (const auto& point : points) {
        glVertex3f(point.x, point.y, point.z);
    }
    glEnd();
}