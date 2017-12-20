#include "stdafx.h"
#include "Object.h"
#include <math.h>
Object::Object(float x, float y, int type, int team)
{
	Arrow_delay = 0.f;
	TopBullet_delay = 0.f;
	BottomBullet_delay = 0.f;

	if (type == 0) // 건물
	{
		set_x(x);
		set_y(y);

		set_vx(0);
		set_vy(0);

		set_size(100);
		set_colorR(1); set_colorG(1); set_colorB(1); set_colorA(1);

		set_life(BUILDING_LIFE);
		set_lifetime(LIFE);
		set_type(type);
		set_team(team);
	}

	if (type == 1) // 캐릭터
	{
		set_x(x);
		set_y(y);
		set_speed(300);

		set_vx(get_speed() *(((float)std::rand() / (float)RAND_MAX) - 0.5f));
		set_vy(get_speed() *(((float)std::rand() / (float)RAND_MAX) - 0.5f));

		set_size(10);

		set_life(CHARACTER_LIFE);
		set_lifetime(LIFE);

		set_type(type);
	    set_team(team);

		if (team == 0)
		{
			set_colorR(1); set_colorG(0); set_colorB(0); set_colorA(1);
		}
		else if (team == 1)
		{
			set_colorR(0); set_colorG(0); set_colorB(1); set_colorA(1);
		}
	}

	if (type == 2) // 총알
	{
		set_x(x);
		set_y(y);
		set_speed(300);

		set_vx((get_speed()*((float)std::rand() / (float)RAND_MAX - 0.5f)));

		set_size(5);
		set_life(BULLET_LIFE);
		set_lifetime(LIFE);

		set_type(type);
		set_team(team);

		if (team == 0) // Top
		{
			set_colorR(1); set_colorG(0); set_colorB(0); set_colorA(1);
			set_vy((get_speed()*-((float)(std::rand()) / (float)RAND_MAX)));

		}
		else if (team == 1)
		{
			set_colorR(0); set_colorG(0); set_colorB(1); set_colorA(1);
			set_vy((get_speed()*((float)(std::rand()) / (float)RAND_MAX)));

		}
	}

	if (type == 3) // 화살
	{
		set_x(x);
		set_y(y);
		set_speed(300);

		set_vx((get_speed()*(((float)std::rand() / (float)RAND_MAX) - 0.5f)));
		set_vy((get_speed()*(((float)std::rand() / (float)RAND_MAX) - 0.5f)));

		set_size(5);

		set_life(ARROW_LIFE);
		set_lifetime(LIFE);

		set_type(type);
		set_team(team);

		if (team == 0)
		{
			set_colorR(0.5f); set_colorG(0.2f); set_colorB(0.7f); set_colorA(1);
		}
		else if (team == 1)
		{
			set_colorR(1); set_colorG(1); set_colorB(0); set_colorA(1);
		}
	}
}

Object::~Object()
{

}

void Object::Update(float elapsedTime)
{
	float elapsedTimeInSecond = elapsedTime / 1000.f;
	
	set_x(get_x() + get_vx()*elapsedTimeInSecond);
	set_y(get_y() + get_vy()*elapsedTimeInSecond);

	Arrow_delay += elapsedTimeInSecond;
	TopBullet_delay += elapsedTimeInSecond;
	BottomBullet_delay += elapsedTimeInSecond;

	
	Particle_time_B += elapsedTimeInSecond *0.5;

	
	
	if (get_x() > 250)
	{
		set_vx(-get_vx());
	}

	if (get_x() < -250)
	{
		set_vx(-get_vx());
	}

	if (get_y() > 400)
	{
		set_vy(-get_vy());
	}

	if (get_y() < -400)
	{
		set_vy(-get_vy());
	}

	if (get_lifetime() > 0.f)
	{
		if(get_lifetime() != LIFE)
			set_lifetime(get_lifetime() - 0.5f);
	}

}
