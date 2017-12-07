#pragma once
#include <cstdlib>
#include <iostream>
#include "Renderer.h"
#include "Sound.h"
#include "Object.h"

#define MAXOBJECT 300
#define OBJECT_BUILDING 0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3
#define Team_Top 0
#define Team_Bottom 1

class SceneMgr
{
public:
	SceneMgr(int width, int height);
	~SceneMgr();

	int AddObject(float x, float y, int Object_type, int team);

	void UpdateAllObjects(float elapsedTime);
	void DrawAllObjects();
	void Collision();
	bool CollisionCheck(float a_minX, float a_minY, float a_maxX, float a_maxY, float b_minX, float b_minY, float b_maxX, float b_maxY);

	int BulletNum = 0; // 총알 수 새는 변수
	int onwer = 0;     // 캐릭터 갯수
	float topCharacter = 0;
	float TopCharacter_delay = 0;
	float BottomCharacter_delay = 0;
	float transform_time = 0;

	float particle=0;
	int transform = 0;
	int transform2 = 0;
private:
	Renderer *renderer;
	Sound *m_Sound;

	Object *m_Objects[MAXOBJECT];
	
	int id=0;
	bool Shoot = true;
	bool ArrowShoot = true;
	bool term = true;


	int m_windowWidth;
	int m_windowHeight;


};

