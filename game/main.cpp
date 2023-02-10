#include <Application.h>


int main(void) {

    // Global pointer to the application
    Application* g_app = 0;

	// Create application
	g_app = new Application();
	g_app->run();
	// Delete application
	delete g_app;
	g_app = 0;

	return 0;
}



