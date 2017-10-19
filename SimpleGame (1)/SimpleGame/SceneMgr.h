#pragma once

#include "Dependencies\glew.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();

public:
	void Draw_AllRect();
	void Draw_Rect();

};