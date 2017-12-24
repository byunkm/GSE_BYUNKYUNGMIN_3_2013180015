#include "stdafx.h"
#include "Object.h"
#include <math.h>
Object::Object(float x, float y, int type, int team, bool status, bool Attack_type, bool Unit_type)
{
	Arrow_delay = 0.f;
	TopBullet_delay = 0.f;
	BottomBullet_delay = 0.f;
	
	if (type == OBJECT_BUILDING) // 건물
	{
		set_x(x);
		set_y(y);

		set_vx(0);
		set_vy(0);

		set_size(BUILDING_SIZE);
		set_colorR(1); set_colorG(1); set_colorB(1); set_colorA(1);

		set_life(BUILDING_LIFE);
		set_lifetime(LIFE);
		set_type(type);
		set_team(team);
		set_Status(status);
		set_A_type(Attack_type);
		set_U_type(Unit_type);
	}

	if (type == OBJECT_CHARACTER) // 캐릭터
	{
		set_x(x);
		set_y(y);
		set_speed(CHARACTER_SPEED);

		set_vx(get_speed() *(((float)std::rand() / (float)RAND_MAX) - 0.5f));
		set_vy(get_speed() *(((float)std::rand() / (float)RAND_MAX) - 0.5f));

		set_size(CHARACTER_SIZE);

		set_life(CHARACTER_LIFE);
		set_lifetime(LIFE);

		set_type(type);
	    set_team(team);
		set_Status(status);
		set_A_type(Attack_type);
		set_U_type(Unit_type);
		if (team == Team_Top)
		{
			set_colorR(1); set_colorG(0); set_colorB(0); set_colorA(1);
		}
		else if (team == Team_Bottom)
		{
			set_colorR(0); set_colorG(0); set_colorB(1); set_colorA(1);
		}
	}

	if (type == OBJECT_BULLET) // 총알
	{
		set_x(x);
		set_y(y);
		set_speed(BULLET_SPEED);

		set_vx((get_speed()*((float)std::rand() / (float)RAND_MAX - 0.5f)));

		set_size(BULLET_SIZE);
		set_life(BULLET_LIFE);
		set_lifetime(LIFE);

		set_type(type);
		set_team(team);
		set_Status(status);
		set_A_type(Attack_type);
		set_U_type(Unit_type);
		if (team == Team_Top) // Top
		{
			set_colorR(1); set_colorG(0); set_colorB(0); set_colorA(1);
			set_vy((get_speed()*-((float)(std::rand()) / (float)RAND_MAX)));

		}
		else if (team == Team_Bottom)
		{
			set_colorR(0); set_colorG(0); set_colorB(1); set_colorA(1);
			set_vy((get_speed()*((float)(std::rand()) / (float)RAND_MAX)));

		}
	}

	if (type == OBJECT_ARROW) // 화살
	{
		set_x(x);
		set_y(y);
		set_speed(ARROW_SPEED);

		set_vx((get_speed()*(((float)std::rand() / (float)RAND_MAX) - 0.5f)));
		set_vy((get_speed()*(((float)std::rand() / (float)RAND_MAX) - 0.5f)));

		set_size(ARROW_SIZE);

		set_life(ARROW_LIFE);
		set_lifetime(LIFE);

		set_type(type);
		set_team(team);
		set_Status(status);
		set_A_type(Attack_type);
		set_U_type(Unit_type);
		if (team == Team_Top)
		{
			set_colorR(0.5f); set_colorG(0.2f); set_colorB(0.7f); set_colorA(1);
		}
		else if (team == Team_Bottom)
		{
			set_colorR(1); set_colorG(1); set_colorB(0); set_colorA(1);
		}
	}
}


Object::~Object()
{

}
void Object::Update(float elapsedTime, bool status)
{
	float elapsedTimeInSecond = elapsedTime / 1000.f;
	
	Arrow_delay += elapsedTimeInSecond;
	TopBullet_delay += elapsedTimeInSecond;
	BottomBullet_delay += elapsedTimeInSecond;

	Particle_time_B += elapsedTimeInSecond ;

	if (status == false) // 같은 유닛상태를 만나지 않았을때만 움직인다.
	{
		set_x(get_x() + get_vx()*elapsedTimeInSecond);
		set_y(get_y() + get_vy()*elapsedTimeInSecond);

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
			if (get_lifetime() != LIFE)
				set_lifetime(get_lifetime() - 0.5f);
		}
	}
}
