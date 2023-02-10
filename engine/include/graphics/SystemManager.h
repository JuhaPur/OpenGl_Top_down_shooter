#pragma once

#include <System.h>

class Application;
class MyOpenGLWidget;


class SystemManager {
public:
    SystemManager(Application* app);
    SystemManager(MyOpenGLWidget* app);

    std::vector< std::shared_ptr<System> > m_systems;

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


    void update();

};
