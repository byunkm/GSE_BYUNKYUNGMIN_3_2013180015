/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "windows.h"

#include "SceneMgr.h"
#include "Object.h"

#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

SceneMgr *Scene = NULL;

DWORD g_prevTime = 0;

bool LeftButtonDown = false;
bool RightButtonDown = false;
bool Build = false;

void RenderScene(void)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;

	Scene->UpdateAllObjects((float)elapsedTime);
	Scene->DrawAllObjects();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

//button
//GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
//state
//GLUT_UP, GLUT_DOWN
void MouseInput(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		LeftButtonDown = true;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		RightButtonDown = true;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (LeftButtonDown)
		{
			if (Build == true) // 건물이 건설 완료 되어야 캐릭터를 생성시킬 수 있다.
				Scene->AddObject(x - 250, -y + 250, OBJECT_CHARACTER);
		}
		LeftButtonDown = false;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		if (RightButtonDown)
		{
			if (Build == false) // 건물은 한 채만 지을 수 있다. 파괴될경우 재생성 불가
			{
				Scene->AddObject(x - 250, -y + 250, OBJECT_BUILDING);
				Build = true;
			}
		}
		RightButtonDown = false;
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("GAM SOGONG");

	glewInit();

	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	Scene = new SceneMgr(500, 500);
	

	g_prevTime = timeGetTime();

	glutMainLoop();

	delete Scene;

	return 0;
}

