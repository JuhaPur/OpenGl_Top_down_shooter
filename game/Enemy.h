#pragma once
#include <stdio.h> // Include stdio.h, which contains printf-function
#include <glad/gl.h> // Include glad
#include <GLFW/glfw3.h>   // Include glfw
#include <math.h>
#include "Component.h"
#include "Entity.h"
//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



class Enemy : public Component
{
public:
	Enemy();
	virtual ~Enemy();
	void loadEnemy();



private:

};

class Bullet : public Component
{
public:
	Bullet() {};
	virtual ~Bullet() {};
	void loadBullet() {};
	


private:

};

