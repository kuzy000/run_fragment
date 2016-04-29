#pragma once

#include "Configuration.h"
#include "OnScopeEnd.h"

#include <mutex>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace RunFragment {

class Renderer {
public:
	enum class Target { Main, Channel0, Channel1, Channel2, Channel3 };
	
	Renderer(const Configuration& config, Target target, GLFWwindow* window);
	
	void run();
	void render();
	void reloadFile();
private:
	void reloadShader();
	
	GLuint compileShader(GLenum type, const std::string& source);
	
	const Configuration& config;
	const Target target;
	const std::string path;
	
	GLFWwindow* window;
	
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint ebo = 0;
	
	GLuint vertex = 0;
	GLuint fragment = 0;
	GLuint program = 0;
	
	GLint iResolution = -1; // done
	GLint iGlobalTime = -1; // done
	GLint iGlobalDelta = -1;
	GLint iGlobalFrame = -1;
	GLint iChannelTime = -1;
	GLint iMouse = -1; // done
	GLint iDate = -1; // done
	GLint iSampleRate = -1;
	GLint iChannelResolution = -1;
	GLint iChannel0 = -1;
	GLint iChannel1 = -1;
	GLint iChannel2 = -1;
	GLint iChannel3 = -1;
	
	std::mutex sourceChanging;
	
	std::string fragmentSource;
	bool changed = false;
	
	std::chrono::high_resolution_clock::time_point startTime;
	
	OnScopeEnd onDestruction;
};

}

