#include "stdafx.h"
#include "Object.h"
#include <math.h>


Object::Object(float x, float y, int type)
{
	if (type == 0) // 건물
	{
		set_x(x);
		set_y(y);

		set_vx(0);
		set_vy(0);

		set_size(50);
		set_colorR(1); set_colorG(0); set_colorB(1); set_colorA(0.5);

		set_life(500.f);

		set_type(type);
	}

	if (type == 1) // 캐릭터
	{
		set_x(x);
		set_y(y);
		set_speed(300);

		set_vx(get_speed() *(((float)std::rand() / (float)RAND_MAX) - 0.5f));
		set_vy(get_speed() *(((float)std::rand() / (float)RAND_MAX) - 0.5f));

		set_size(10);
		set_colorR(1); set_colorG(1); set_colorB(1); set_colorA(1);

		set_life(10.f);
		set_lifetime(1000.f);

		set_type(type);
	}

	if (type == 2) // 총알
	{
		set_x(x);
		set_y(y);
		set_speed(600);

		set_vx((get_speed()*(((float)std::rand() / (float)RAND_MAX) - 0.5f)));
		set_vy((get_speed()*(((float)std::rand() / (float)RAND_MAX) - 0.5f)));

		set_size(2);
		set_colorR(0); set_colorG(1); set_colorB(1); set_colorA(1);

		set_life(20.f);

		set_type(type);
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

	if (get_x() > 250)
	{
		set_vx(-get_vx());
	}

	if (get_x() < -250)
	{
		set_vx(-get_vx());
	}

	if (get_y() > 250)
	{
		set_vy(-get_vy());
	}

	if (get_y() < -250)
	{
		set_vy(-get_vy());
	}

	if (get_lifetime() > 0.f)
	{
		set_lifetime(get_lifetime() - 0.5f);
	}

}
