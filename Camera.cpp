#include "Include.h"

bool isLookAround = false; // This simple boolean means: did we finish taking shots and are now toggling between them and solving pnp?

//bool protect = false;
// Purpose: Renders a view triangle from camera perspective.
void CameraViewTriangleRenderer(const glm::vec3& position, const glm::vec3& direction, bool cFlag) {
    glm::vec3 right = glm::normalize(glm::cross(direction, cUp)) * 0.2f;
    glm::vec3 up = glm::normalize(glm::cross(right, direction)) * 0.75f;

    glDisable(GL_LIGHTING);
    if (cFlag) {
        glColor3f(1.0f, 0.2f, 0.2f);
    }
    else {
        glColor3f(1.0f, 1.0f, 0.0f);

    }

    glBegin(GL_TRIANGLES);
    glVertex3f(position.x, position.y, position.z);
    glVertex3f(position.x + direction.x * 0.4f + right.x, position.y + direction.y * 0.4f + right.y, position.z + direction.z * 0.4f + right.z);
    glVertex3f(position.x + direction.x * 0.4f - right.x, position.y + direction.y * 0.4f - right.y, position.z + direction.z * 0.4f - right.z);
    glEnd();
    glEnable(GL_LIGHTING);
}

// Purpose: Renders the camera movement path. Used to visualize movement in scene.
void CameraPathRenderer() {
    if (cameraRoute.size() < 2) return; // Need at least two points to draw a line

    glPushAttrib(GL_ENABLE_BIT); // Save current enable bit states
    glDisable(GL_LIGHTING); // Disable lighting to ensure the color is applied correctly

    glEnable(GL_BLEND); // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blend function

    // glEnable(GL_LINE_SMOOTH); // Enable line smoothing
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Set the line smoothing hint to the highest quality

    glColor4f(1.0f, 1.0f, 0.545f, 1.0f); // Set line color with alpha for blending
    glLineWidth(7.0f); // Set line width

    glBegin(GL_LINE_STRIP);
    for (const auto& pos : cameraRoute) {
        glVertex3f(pos.x, pos.y,  pos.z);
    }
    glEnd();

    glPopAttrib(); // Restore previous enable bit states
}

struct CameraInformation saveCameraInfo() {
    CameraInformation information =
    {
        Position,
        fwrd,
        horiAngle,
        vertiAngle,
    };

    // Capture the right viewport (camera view)
    int width = WINDOW_WIDTH / 2;
    int height = WINDOW_HEIGHT;
    std::vector<unsigned char> infoImageVec(static_cast<size_t>(3) * static_cast<size_t>(width) * static_cast<size_t>(height));
    glReadPixels(width, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, infoImageVec.data());
    information.infoImageVec = std::move(infoImageVec);

    return information;
}

 // Purpose: Loads and renders camera images. Used in image processing.
void CameraImageLoader(GLFWwindow* window) {
    if (!savedCmrInfo.empty()) {
        currCmrInfoIdx = (currCmrInfoIdx + savedCmrInfo.size()) % savedCmrInfo.size();  // Ensure index wraps correctly
    }
    CameraInformation information = savedCmrInfo[currCmrInfoIdx];

    std::vector<unsigned char> infoImageVec = information.infoImageVec;

    glDrawPixels(WINDOW_WIDTH / 2, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, infoImageVec.data());
}

void NextCameraInfoLoader() {
    if (!savedCmrInfo.empty()) {
        // Load the next camera state
        currCmrInfoIdx = (currCmrInfoIdx) % savedCmrInfo.size();
        CameraInformation information = savedCmrInfo[currCmrInfoIdx];
        Position = information.position;
        fwrd = information.cFwrd;
        horiAngle = information.horizAngle;
        vertiAngle = information.verticAngle;

        // Recalculate the camera front vector based on the loaded horizontalAngle and verticalAngle
        glm::vec3 front;
        front.x = cos(glm::radians(horiAngle)) * cos(glm::radians(vertiAngle));
        front.y = sin(glm::radians(vertiAngle));
        front.z = sin(glm::radians(horiAngle)) * cos(glm::radians(vertiAngle));
        fwrd = glm::normalize(front);
    }

}

 // Purpose: Updates camera position and orientation based on user input.
void CameraUpdater() {
    const float cVelocity = 0.01f;
    constexpr float rotSen = glm::radians(0.1f);
    bool isPosUpdated = false;

    if (pKey.up) {
        Position += cVelocity * fwrd;
        isPosUpdated = true;
    }
    if (pKey.down) {
        Position -= cVelocity * fwrd;
        isPosUpdated = true;
    }
    if (pKey.left) {
        Position -= glm::normalize(glm::cross(fwrd, cUp)) * cVelocity;
        isPosUpdated = true;
    }
    if (pKey.right) {
        Position += glm::normalize(glm::cross(fwrd, cUp)) * cVelocity;
        isPosUpdated = true;
    }
    if (pKey.a) {
        horiAngle -= glm::degrees(rotSen);
    }
    if (pKey.d) {
        horiAngle += glm::degrees(rotSen);
    }
    if (pKey.w) {
        vertiAngle += glm::degrees(rotSen);
    }
    if (pKey.s) {
        vertiAngle -= glm::degrees(rotSen);
    }
    if (pKey.r) {
        vertiAngle = 0.0f;
        horiAngle = -90.0f;
        objPos = glm::vec3(0.0f, 0.0f, 0.0f);
        objRotX = 0.0f;
        objRotY = 0.0f;
        Position = glm::vec3(0.0f, 0.0f, 5.0f);
        fwrd = glm::vec3(0.0f, 0.0f, -1.0f);
        cUp = glm::vec3(0.0f, 1.0f, 0.0f);
        isPosUpdated = true;
        //currentCameraStateIndex = 0;
    }

    // Constrain the verticalAngle to prevent flipping
    if (vertiAngle > 89.0f) vertiAngle = 89.0f;
    if (vertiAngle < -89.0f) vertiAngle = -89.0f;

    // Calculate the new camera front vector
    glm::vec3 front;
    front.x = cos(glm::radians(horiAngle)) * cos(glm::radians(vertiAngle));
    front.y = sin(glm::radians(vertiAngle));
    front.z = sin(glm::radians(horiAngle)) * cos(glm::radians(vertiAngle));
    fwrd = glm::normalize(front);

    if (isPosUpdated) {
        cameraRoute.push_back(Position); // Save the new camera position
    }
}

 // Purpose: Loads parameters for camera settings. Used in dynamic adjustments.
void CameraParameterLoader(glm::vec3 calculatedPos, float calcYaw, float calcPitch) {
    Position = calculatedPos;
    horiAngle = calcYaw;
    vertiAngle = calcPitch;

    glm::vec3 front;
    front.x = cos(glm::radians(vertiAngle)) * cos(glm::radians(horiAngle));
    front.y = sin(glm::radians(vertiAngle));
    front.z = cos(glm::radians(vertiAngle)) * sin(glm::radians(horiAngle));
    fwrd = glm::normalize(front);

    cameraPnpSol = saveCameraInfo();
}

 // Purpose: Manages loading and processing of different camera states.
void StateModeLoader(unsigned char input) {
    if (tolower(input) == '3') 
    {
        if (savedCmrInfo.size() == 0) 
        {
            return;
        }
        lastInformation.position = Position;
        lastInformation.cFwrd = fwrd;
        lastInformation.horizAngle = horiAngle;
        lastInformation.verticAngle = vertiAngle;
        NextCameraInfoLoader();
    }
    else 
    {
        Position = lastInformation.position;
        fwrd = lastInformation.cFwrd;
        horiAngle = lastInformation.horizAngle;
        vertiAngle = lastInformation.verticAngle;

        // Recalculate the camera front vector based on the loaded horizontalAngle and verticalAngle
        glm::vec3 front;
        front.x = cos(glm::radians(horiAngle)) * cos(glm::radians(vertiAngle));
        front.y = sin(glm::radians(vertiAngle));
        front.z = sin(glm::radians(horiAngle)) * cos(glm::radians(vertiAngle));
        fwrd = glm::normalize(front);
    }
 }

void InteractionHandler(unsigned char input, int x, int y) {
	// Handle state selection
	if (input == '3') {
		StateModeLoader(input);
		return;
	}

	else if (input == '4') {
		savedCmrInfo.push_back(saveCameraInfo());
	}
}

 // Purpose: Handles key press events, updates camera states and other interactions.
void KeyPressProcessor(unsigned char input, int x, int y) {
    // Might need to add some protection against movement after shots have been taken and when toggling between them.
    switch (tolower(input)) {
    case '1': case '2': case '3': case '4': InteractionHandler(input, x, y); break;
    case 'w': pKey.w = true; break;
    case 'a': pKey.a = true; break;
    case 's': pKey.s = true; break;
    case 'd': pKey.d = true; break;
    case 'r': pKey.r = true; break;
    }
}

// Purpose: Processes key release events, updating system states.
void KeyReleaseUpdater(unsigned char input, int x, int y) {
    switch (tolower(input)) {
    case '1': case '4': case '3': case '2': break;
    case 'w': pKey.w = false; break;
    case 'a': pKey.a = false; break;
    case 's': pKey.s = false; break;
    case 'd': pKey.d = false; break;
    case 'r': pKey.r = false; break;
    }
}

// Purpose: Handles special key events for advanced controls.
void SpecialKeyPressUpdater(int input, int x, int y) {
    if (isLookAround) {
        if (input == GLUT_KEY_RIGHT) {
            currCmrInfoIdx++;
            NextCameraInfoLoader();
            return; // Early return to prevent further processing of this key event
        }
        else if (input == GLUT_KEY_LEFT) {
            currCmrInfoIdx--;
            if (currCmrInfoIdx < 0) {
                currCmrInfoIdx = (int)savedCmrInfo.size() - 1;
            }
            NextCameraInfoLoader();
            return; // Early return to prevent further processing of this key event
        }
    }
    switch (input) {
    case GLUT_KEY_LEFT: pKey.left = true; break;
    case GLUT_KEY_RIGHT: pKey.right = true; break;
    case GLUT_KEY_UP: pKey.up = true; break;
    case GLUT_KEY_DOWN: pKey.down = true; break;
    }
}

// Purpose: Handles release of special keys, updating state accordingly.
void SpecialKeyReleaseUpdater(int input, int x, int y) {
    if (isLookAround) {
        return; // Early return to prevent further processing of this key event
    }
    switch (input) {
    case GLUT_KEY_LEFT: pKey.left = false; break;
    case GLUT_KEY_RIGHT: pKey.right = false; break;
    case GLUT_KEY_UP: pKey.up = false; break;
    case GLUT_KEY_DOWN: pKey.down = false; break;
    }
}