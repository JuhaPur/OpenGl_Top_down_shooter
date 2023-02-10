#pragma once
#include <stdio.h>			// Include stdio.h, which contains printf-function
#include <glad/gl.h>
#include <GLFW/glfw3.h>		// Include glfw
#include <kgfw/GLUtils.h>
#include <vector>
#include <algorithm>
#include <graphics/Shader.h>
#include <Transform.h>
#include <graphics/Camera.h>
#include <graphics/Texture.h>
#include <graphics/GraphicsSystem.h>
#include <Entity.h>
#include <GameplaySystem.h>
#include <graphics/SpriteBatch.h>
#include <graphics/TextRendering.h>


// Include STB-image library
#include <stb_image.h>


class Application {
public:
	std::vector< std::shared_ptr<System> > systems;

	// Function to create components
	std::shared_ptr<Component> createComponent(const std::string& type, const System::Args& args) {
		for (auto system : m_systems) {
			auto component = system->createComponent(type, args);
			if (component) {
				return component;
			}
		}
		return 0;
	}

	std::shared_ptr<Entity> createEntity(const std::string& type, Entity* parent = 0, const System::Args& args = {}) {
		if ("MainCamera" == type) {
			std::shared_ptr<Entity> camera = std::make_shared<Entity>();
			camera->addComponent(std::make_shared<Transform>(parent));
			camera->addComponent(createComponent("Camera", args));
			return camera;
		}
		if ("Background" == type) {
			std::shared_ptr<Entity> backround = std::make_shared<Entity>();
			backround->addComponent(std::make_shared<Transform>(parent));
			backround->addComponent(createComponent("Background", { "../Assets/jotain.png" }));
			backround->getComponent<Transform>()->setScaling(glm::vec3(800.0f, 600.0f, 0.0f));
			backround->getComponent<Transform>()->setPosition(glm::vec3(400.0f, 300.0f, -1.0f));
			return backround;
		}
		if ("Player" == type) {
			std::shared_ptr<Entity> player = std::make_shared<Entity>();			
			player->addComponent(std::make_shared<Transform>(parent));
			player->addComponent(createComponent("Sprite", {"../Assets/Player1.png"}));
			player->addComponent(createComponent("Player", {"50"}));
			player->addComponent(createComponent("Collider", {}));
			player->getComponent<Transform>()->setScaling(glm::vec3(50.0f, 50.0f, 50.0f));
			player->getComponent<Transform>()->setPosition(glm::vec3(400.0f, 300.0f, 1.0f));
			return player;
		}
		if ("Enemy" == type) {
			std::shared_ptr<Entity> enemy = std::make_shared<Entity>();			
			enemy->addComponent(std::make_shared<Transform>(parent));
			enemy->addComponent(createComponent("Sprite", { "../Assets/download.png" }));
			enemy->addComponent(createComponent("Enemy", { "50" }));
			enemy->addComponent(createComponent("Collider", {}));
			enemy->getComponent<Transform>()->setScaling(glm::vec3(50.0f, 50.0f, 00.0f));
			enemy->getComponent<Transform>()->setPosition(glm::vec3(600.0f, 150.0f, 1.0f));
			return enemy;
		}
		if ("Enemy2" == type) {
			std::shared_ptr<Entity> enemy = std::make_shared<Entity>();
			enemy->addComponent(std::make_shared<Transform>(parent));
			enemy->addComponent(createComponent("Sprite", { "../Assets/download.png" }));
			enemy->addComponent(createComponent("Enemy2", { "50" }));
			enemy->getComponent<Transform>()->setScaling(glm::vec3(50.0f, 50.0f, 00.0f));
			enemy->getComponent<Transform>()->setPosition(glm::vec3(500.0f, 100.0f, 1.0f));
			return enemy;
		}
		if ("Bullet" == type) {
			std::shared_ptr<Entity> bullet = std::make_shared<Entity>();
			bullet->addComponent(std::make_shared<Transform>(parent));
			bullet->addComponent(createComponent("Sprite", { "../Assets/bullet.png" }));
			bullet->addComponent(createComponent("Bullet", { "50" }));
			bullet->getComponent<Transform>()->setScaling(glm::vec3(30.0f, 30.0f, 00.0f));
			bullet->getComponent<Transform>()->setPosition(glm::vec3(5000.0f, 5000.0f, 1.0f));
			return bullet;
		}
		return 0;
	}

	Application() {
	
		// Set c++-lambda as error call back function for glfw.
		glfwSetErrorCallback([](int error, const char* description) {
			fprintf(stderr, "Error %d: %s\n", error, description);
		});

		// Try to initialize glfw
		if (!glfwInit()) {
			return;
		}

		// Create window and check that creation was succesful.
		m_window = glfwCreateWindow(800, 600, "OpenGL window", NULL, NULL);
		if (!m_window) {
			glfwTerminate();
			return;
		}

		// Set current context
		glfwMakeContextCurrent(m_window);
		// Load GL functions using glad
		gladLoadGL(glfwGetProcAddress);

		// Specify the key callback as c++-lambda to glfw
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			// Close window if escape is pressed by the user.
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		});

		
		m_systems.push_back(std::make_shared<GraphicsSystem>());
		m_systems.push_back(std::make_shared<GameplaySystem>(this));
		
		m_sceneRoot = std::make_shared <Entity>();
		
		m_sceneRoot->addComponent(std::make_shared<Transform>());
		
		m_sceneRoot->addChild(createEntity("Background", m_sceneRoot.get(), { }));   // Creates Backround image Entity
		m_sceneRoot->addChild(createEntity("Player", m_sceneRoot.get(), { }));		// Creates Player Entity
		m_sceneRoot->addChild(createEntity("Enemy", m_sceneRoot.get(), { }));		// Creates Enemy Entity
		m_sceneRoot->addChild(createEntity("Enemy2", m_sceneRoot.get(), { }));		// Creates Second Enemy Entity
		m_sceneRoot->addChild(createEntity("MainCamera", m_sceneRoot.get(), { }));  // Creates Camera Entity		
		m_sceneRoot->addChild(createEntity("Bullet", m_sceneRoot.get(), { }));      // Creates Bullet Entity

	}

	~Application() {
		glfwDestroyWindow(m_window);// Destroy window
		glfwTerminate(); // Terminate glfw
	}

	void render(GLFWwindow* window) {
		// Query the size of the framebuffer (window content) from glfw.
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		// Setup the opengl wiewport (i.e specify area to draw)
		glViewport(0, 0, width, height);
		checkGLError();
		// Set color to be used when clearing the screen
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		checkGLError();
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
		checkGLError();

		// Call start function
		start();

		// Calls ghraphichssystem::update
		m_systems[0]->update(0.0f); //Graphics
	}

	void run() {
		// Get time using glfwGetTime-function, for delta time calculation.
		float prevTime = (float)glfwGetTime();
		while (!glfwWindowShouldClose(m_window)) {
			// Render the game frame and swap OpenGL back buffer to be as front buffer.
			render(m_window);
			glfwSwapBuffers(m_window);

			// Poll other window events.
			glfwPollEvents();

			// Compute application frame time (delta time) and update application
			float curTime = (float)glfwGetTime();
			float deltaTime = curTime - prevTime;
			prevTime = curTime;
			update(deltaTime);
		}
	}

	void start() {
		m_systems[0]->start();
	}
	
	//updates all systems
	void update(float deltaTime) {
		m_systems[1]->update(deltaTime);
	}

	// Get keyboard input
	bool getKeyState(int keyCode) {
       return glfwGetKey(m_window, keyCode);
	}

	// Get mouse button input
	bool getMouseState(int mouseButton) {
		return glfwGetMouseButton(m_window, mouseButton);
	}

	//gets the cursor position
	glm::vec3 getCursorPos() const {
		double xPos = 0;
		double yPos = 0;
		glfwGetCursorPos(m_window, &xPos, &yPos);
		return glm::vec3(xPos, yPos, 1);
	}

	// Gets the window size
	glm::vec3 getWindowSize() const {
		int width = 0;
		int height = 0;
		glfwGetWindowSize(m_window, &width, &height);
		return glm::vec3(width, height, 1);
	}


private:
	GLFWwindow* m_window = nullptr;
	std::vector< std::shared_ptr<System> > m_systems;
	std::shared_ptr<Entity> m_sceneRoot;
	
	
};
