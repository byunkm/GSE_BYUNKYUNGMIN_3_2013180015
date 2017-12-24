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
Sound *m_Sound = NULL;

DWORD g_prevTime = 0;

bool LeftButtonDown = false;
bool RightButtonDown = false;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
			if (Scene->BottomCharacter_delay > 1.0f)
			{
				if (-y + 400 < 0) // 남쪽에서만 생성 수 있도록 함
				{
					Scene->AddObject(x - 250, -y + 400, OBJECT_CHARACTER, Team_Bottom, false, ATTACK_GROUND, UNIT_GROUND);  // 지상 캐릭터 생성
					Scene->BottomCharacter_delay = 0;
					//m_Sound->PlaySound(Birth_Sound, false, 0.5f);
				}
				else
					cout << "생성할 수 없는 지역입니다." << endl;
			}
		}
		LeftButtonDown = false;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		if (RightButtonDown)
		{
			if (Scene->BottomCharacter2_delay > 1.0f)
			{
				if (-y + 400 < 0) // 남쪽에서만 생성 수 있도록 함
				{
					Scene->AddObject(x - 250, -y + 400, OBJECT_CHARACTER, Team_Bottom, false, ATTACK_SKY, UNIT_SKY);     // 공중 캐릭터 생성
					Scene->BottomCharacter2_delay = 0;
					//m_Sound->PlaySound(Birth_Sound, false, 0.5f);
				}
				else
					cout << "생성할 수 없는 지역입니다." << endl;
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
	glutInitWindowSize(500, 800);
	glutCreateWindow("GAM SOGONG");

	glewInit();

	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW d is 3.0\n ";
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

	Scene = new SceneMgr(500, 800);
	

	g_prevTime = timeGetTime();

	glutMainLoop();

	delete Scene;

	return 0;
}

