#ifndef GANESHENGINE_GHGLRENDERERMANAGER_H
#define GANESHENGINE_GHGLRENDERERMANAGER_H

#include "ghHeaders.h"
#include "ghSystem.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/ghGLModel.h"

class GLFWwindow;

namespace ganeshEngine {

using namespace std;

/**
 *
 */
extern vector<tuple<GLenum, string>> gGLContextParams;


class RendererManager : public System<RendererManager> {
	friend class System<RendererManager>;

private:
	/**
	 * Window used to render the game
	 */
    GLFWwindow* mpWindow;


	GLTexture *tex;
	GLMesh *mesh;
	GLProgram program;
	GLModel *model;

	RendererManager() {}

public:
	RendererManager(const RendererManager&) = delete;
	RendererManager& operator=(const RendererManager&) = delete;
	~RendererManager() {}

	/**
	 * This will clear the screen, then draw everything that needs to be drawn
	 * and finish by swapping the buffers
	 */
    void update();

protected:
	/**
	 * Initialization of GLFW and GLEW, creation of the windows and settings
	 * default rendering parameters
	 */
    void vInitialize() override;

    /**
     * Free everything used by GLFW and GLEW
     */
    void vDestroy() override;
};

/**
 * Triggered when GLFW throw an error, basically it will call the LoggerManager to log and error
 *
 * @param error GLFW specific error code
 * @param message description of the error
 */
void gGlfwErrorCallback(int error, const char *message);

/**
 * Global getter of reference to the RendererManager
 * @return reference to the RendererManager
 */
extern RendererManager&(*gRenderer)();
}

#endif //GANESHENGINE_GHGLRENDERERMANAGER_H
