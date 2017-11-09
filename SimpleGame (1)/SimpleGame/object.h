#pragma once
#include <cstdlib>

class Object
{

public:
	Object(float x, float y, int type);
	~Object();

private:
	float m_x;
	float m_y;
	float m_vX;
	float m_vY;
	float speed;
	
	float m_size;
	float colorR;
	float colorG;
	float colorB;
	float colorA;

	float m_life;
	float m_lifeTime;

	int Object_type;

public:

	float get_x() { return m_x; }
	float get_y() { return m_y; }
	float get_vx() { return m_vX; }
	float get_vy() { return m_vY; }

	float get_size() { return m_size; }
	float get_speed() {	return speed;}

	float get_colorR() { return colorR; }
	float get_colorG() { return colorG; }
	float get_colorB() { return colorB; }
	float get_colorA() { return colorA; }

	float get_life() { return m_life; }
	float get_lifetime() { return m_lifeTime; }

	int get_type() { return Object_type; }

public:
	void set_x(float input) { m_x = input; }
	void set_y(float input) { m_y = input; }
	void set_vx(float input) { m_vX = input; }
	void set_vy(float input) { m_vY = input; }
	void set_speed(float input) { speed = input; }

	void set_size(float input) { m_size = input; }
	void set_colorR(float input) { colorR = input; }
	void set_colorG(float input) { colorG = input; }
	void set_colorB(float input) { colorB = input; }
	void set_colorA(float input) { colorA = input; }

	void set_life(float input) { m_life = input; }
	void set_lifetime(float input) { m_lifeTime = input; }

	void set_type(int input) { Object_type = input; }

public:
	void Update(float elapsedTime);
};

