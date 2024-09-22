#include "Include.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <cstdio>


void mouseButtonCallback(int button, int state, int x, int y) {
    // Do nothing
}

// Function declarations
void setupScene();

GLFWwindow* window;
std::vector<glm::vec3> points;
//bool protect = false;



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("World");

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        return -1;
    }

    setupScene();
    // Registers the function renderScene as the callback function that GLUT will call whenever it needs to redraw the window content.
    glutDisplayFunc(sceneRenderer);

    //handle on-mouseclick glut
    glutMouseFunc(mouseButtonCallback);

    //handling keypresses for glut input
    glutKeyboardFunc(KeyPressProcessor);
    glutKeyboardUpFunc(KeyReleaseUpdater);
    // Change between pictures
    glutSpecialFunc(SpecialKeyPressUpdater);
    glutSpecialUpFunc(SpecialKeyReleaseUpdater);

    // Set the idle callback to continuously update the camera
    glutIdleFunc([]() {
        // Camera movement + reset
        CameraUpdater();
        // This function posts a redisplay request to the event loop, indicating that the window needs to be redrawn as soon as possible.
        glutPostRedisplay(); // Request a redraw after updating the camera
        });
    /* GLUT takes control of the program flow.
    * GLUT continuously checks for events such as mouse clicks, keyboard inputs, window resizing, and other system events.
    * When events occur, GLUT invokes the appropriate callback functions that we've registered */
    glutMainLoop();

    return 0;
}

/*


 */
void setupScene() {
    glEnable(GL_DEPTH_TEST);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Define light properties
    GLfloat lightPos[] = { 2.0f, 3.0f, 4.0f, 0.0f };
    GLfloat lightAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat lightDiffuse[] = { 0.9f, 0.9f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.2f, 1.2f, 1.2f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    // GL_PROJECTION: Used for perspective or orthogonal projection transformations, which define how 3D scenes are projected onto the 2D viewport.
    glMatrixMode(GL_PROJECTION);
    /*It loads the current matrix(in the mode set by glMatrixMode()) with the identity matrix.
    //If you're in GL_PROJECTION mode, glLoadIdentity(); resets the projection matrix to its default state
    // If you're in GL_MODELVIEW mode, for instance, glLoadIdentity(); resets any previously applied transformations (such as translations or rotations) and sets the matrix to represent the "default" or no transformation state.*/
    glLoadIdentity();
    /* Field of View(fovy) : The first parameter 45.0 specifies the field of view angle in degrees in the y - direction.
     Aspect Ratio(aspect) : The second parameter specifies the aspect ratio of the viewport.It's calculated as the width divided by the height of the viewport.
    This ensures that the aspect ratio of the scene matches the aspect ratio of the window or viewport where the graphics will be rendered.
    The third parameter specifies the distance from the viewer to the near clipping plane. Objects closer to the viewer than this distance will not be rendered. Setting a small value for zNear prevents objects from disappearing when they are very close to the camera.
    The fourth parameter specifies the distance from the viewer to the far clipping plane. Objects farther away from the viewer than this distance will not be rendered. Setting a large value for zFar ensures that distant objects are still visible within the frustum.*/
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    // Background color - clear the view
    glClearColor(0.15f, 0.2f, 0.30f, 1.0f);
}
