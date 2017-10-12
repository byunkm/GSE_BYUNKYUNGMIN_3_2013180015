#pragma once

#include "Dependencies\glew.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

class Object
 {
	private:
	float x, y, z;
	float size;
	float R, G, B, A;
	int speed;

	public:
	Object();
	~Object();

	Object(float x, float y, float z, float size, float speed, float R, float G, float B, float A);

	float Get_x();
	float Get_y();
	float Get_z();
	float Get_size();
	float Get_speed();
	float Get_R();
	float Get_G();
	float Get_B();
	float Get_A();

	void Position();
	void Update();
	void moving();
};