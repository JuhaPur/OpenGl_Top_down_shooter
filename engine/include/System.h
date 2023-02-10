#pragma once
#include <Component.h>
#include <vector>
#include <string>
#include <memory>

class System {
public:
    typedef std::vector<std::string> Args;
    virtual std::shared_ptr<Component> createComponent(const std::string& type, const Args& args) = 0;
	virtual void update(float deltaTime) = 0;
    virtual void start() = 0;
};

