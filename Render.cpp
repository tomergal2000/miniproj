#include "Include.h"
#include <glm/gtc/type_ptr.hpp>



bool protect = false;
extern glm::vec3 upVectorPnP;
void sceneRenderer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    normalStateRenderer();
    glutSwapBuffers(); // Use the passed window parameter
}

void normalStateRenderer() {
    leftNormalViewportRenderer();
    rightNormalViewportRenderer();
}


void leftNormalViewportRenderer() {
    // Left view (Global view)
    glViewport(0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)(WINDOW_WIDTH / 2) / (double)WINDOW_HEIGHT, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 globalView = glm::lookAt(glm::vec3(6.5f, 6.5f, 6.5f), objPos, cUp);
    glLoadMatrixf(glm::value_ptr(globalView));

    // Apply object transformations for normal
    glPushMatrix();
    glTranslatef(objPos.x, objPos.y, objPos.z);
    glRotatef(glm::degrees(objRotX), 1.0f, 0.0f, 0.0f);
    glRotatef(glm::degrees(objRotY), 0.0f, 1.0f, 0.0f);
    drawTeapot();
    glPopMatrix();

    // Draw pre-made points in the left viewport
    renderPointsInViewport(true);

    // Draw camera path
    CameraPathRenderer();
    
    for (int i = 0; i < savedCmrInfo.size(); ++i) {
        bool isCurrent = (i == currCmrInfoIdx); // Check if this is the current camera state
        CameraInformation info = savedCmrInfo[i];

        // Call the CameraViewTriangleRenderer for each saved camera state
        CameraViewTriangleRenderer(info.position, info.cFwrd, isCurrent);
    }

    // Show current position and direction
    CameraViewTriangleRenderer(Position, fwrd, true);
}


void rightNormalViewportRenderer() {
    // Right view (Camera view)
    glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)(WINDOW_WIDTH / 2) / (double)WINDOW_HEIGHT, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 cameraView = glm::lookAt(Position, Position + fwrd, cUp);
    glLoadMatrixf(glm::value_ptr(cameraView));

    // Apply object transformations for normal
    glPushMatrix();
    glTranslatef(objPos.x, objPos.y, objPos.z);
    glRotatef(glm::degrees(objRotX), 1.0f, 0.0f, 0.0f);
    glRotatef(glm::degrees(objRotY), 0.0f, 1.0f, 0.0f);
    drawTeapot();
    glPopMatrix();

    // Draw pre-made points in the right viewport
    renderPointsInViewport(false);

    // Won't be rendered if not needed:
    cameraOverlayRenderer();
}

void setupRightViewport() {
    // Right view (Camera view)
    glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)(WINDOW_WIDTH / 2) / (double)WINDOW_HEIGHT, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (isLookAround) {
        glm::mat4 cView = glm::lookAt(cameraPnpSol.position, cameraPnpSol.position + cameraPnpSol.cFwrd, upVectorPnP);
        glLoadMatrixf(glm::value_ptr(cView));
    }
    else { // Is this really necesarry or just causing problems?
        glm::mat4 cView = glm::lookAt(Position, Position + fwrd, cUp);
        glLoadMatrixf(glm::value_ptr(cView));
    }
}

void renderPointsInViewport(bool isLeftViewport) {
    float rad = 0.04f / 3.0f; // Make the radius smaller
    int seg = 12; // Number of segments for the spheres

    glDisable(GL_LIGHTING);
    for (size_t i = 0; i < pointLocations.size(); ++i) {
        glm::vec3 color = pointColors[i];
        glColor3f(color.x, color.y, color.z);

        if (isLeftViewport) {
            // Render the 2D points in the left viewport as 2D markers (optional if needed for left view)
            glm::vec3 point = pointLocations[i];
            glPushMatrix();
            glTranslatef(point.x, point.y, point.z);
            glutSolidSphere(rad, seg, seg);
            glPopMatrix();
        }
        else {
            // Render the 3D points in the right viewport
            glm::vec3 point = pointLocations[i];
            glPushMatrix();
            glTranslatef(point.x, point.y, point.z);
            glutSolidSphere(rad, seg, seg);
            glPopMatrix();
        }
    }
    glEnable(GL_LIGHTING);
}


glm::vec3 pointGetter(int x, int y) {
    setupRightViewport();
    double proj[16];
    int viewport[4];
    float winX, winY, winZ;
    double view[16];
    double posX, posY, posZ;
    /*
    GL_MODELVIEW_MATRIX: Returns the current modelview matrix.
    GL_PROJECTION_MATRIX: Returns the current projection matrix.
    */
    glGetDoublev(GL_MODELVIEW_MATRIX, view);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    // retrieve the current viewport dimensions.
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = static_cast<float>(x);
    winY = static_cast<float>(viewport[3] - y); // Invert Y coordinate
    // the depth value (winZ) at the specified pixel (winX, winY) is stored in the variable winZ
    glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    /*
    The function gluUnProject is used in OpenGL to convert window coordinates (winX, winY, winZ)
    into object coordinates (posX, posY, posZ) using the provided matrices (modelview and projection)
    and viewport parameters.*/
    gluUnProject(winX, winY, winZ, view, proj, viewport, &posX, &posY, &posZ);

    // Adjust for the position of the cosahedron 
    glm::vec3 point(posX, posY, posZ);
    point -= objPos; // Adjust for cosahedron's position if necessary

    return point;
}


/*


 */
void drawPoints(const glm::vec3& point, glm::vec3& color)
{
    float rad = 0.04f;      // Adjust radius as needed
    int segSliceCount = 36; // Number of slices (segments) for the sphere
    int segStackCount = 36; // Number of stacks (segments) for the sphere

    glDisable(GL_LIGHTING);
    // Save current matrix state
    glPushMatrix();

    // Translate to the sphere's center position relative to the cosahedron
    glTranslatef(point.x, point.y, point.z);

    // Draw the sphere using OpenGL commands
    glColor3f(color.x, color.y, color.z); // Set sphere color (colorful)
    glutSolidSphere(rad, segSliceCount, segStackCount);
    // Restore previous matrix state
    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void cameraOverlayRenderer() {
    if (isPnPCompleted && !savedCameraImage.empty()) {
        int width = WINDOW_WIDTH / 2;
        int height = WINDOW_HEIGHT;

        // Enable blending for transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Set transparency for the overlay image
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // Faded effect

        // Render the image on the right viewport
        glRasterPos2i(0, 0);
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, savedCameraImage.data());

        // Disable blending
        glDisable(GL_BLEND);
    }
}


/*


 */
void drawTeapot() {
    GLfloat mtrlAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat mtrlDiffuse[] = { 0.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mtrlSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mtrlShininess[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mtrlAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mtrlDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mtrlSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mtrlShininess);

    glutSolidTeapot(1.0f);
}