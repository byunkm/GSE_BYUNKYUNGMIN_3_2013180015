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

	void UpdateAllObjects(float elapsedTime);
	void DrawAllObjects();
	void DrawBack();
	void Collision();

	int AddObject(float x, float y, int Object_type, int team);
	int BulletNum = 0; // 총알 수 새는 변수
	int onwer = 0;     // 캐릭터 갯수
	int sound_index = 0;
	int AttackSound = 0;
	int ProtossAttackSound = 0;
	int transform = 0;
	int transform2 = 0;

	bool CollisionCheck(float a_minX, float a_minY, float a_maxX, float a_maxY, float b_minX, float b_minY, float b_maxX, float b_maxY);
	bool Shake = false;
	
	float topCharacter = 0;
	float TopCharacter_delay = 0;
	float BottomCharacter_delay = 0;
	float transform_time = 0;
	float Particle_time = 0;
	float Particle_level = 0;
	float Sheke_time = 0;
	float particle = 0;
	float Particle_time2 = 0;

private:
	Renderer *renderer;
	Sound *m_Sound;

	Object *m_Objects[MAXOBJECT];

	GLuint Turret = 0;
	GLuint colony = 0;
	GLuint Map_cb = 0;
	GLuint Player_bot = 0;
	GLuint Player_top = 0;
	GLuint fire = 0;

	GLuint Particle_1 = 0;
	GLuint Particle_2 = 0;

	int id=0;
	bool Shoot = true;
	bool ArrowShoot = true;
	bool term = true;


	int m_windowWidth;
	int m_windowHeight;


};

