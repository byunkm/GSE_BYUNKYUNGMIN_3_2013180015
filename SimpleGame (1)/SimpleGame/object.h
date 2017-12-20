#pragma once
#include <cstdlib>

class Object
{

public:
	Object(float x, float y, int type, int team);
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

	float Arrow_delay;
	float TopBullet_delay;
	float BottomBullet_delay;
	float Dir[2];

	int Object_type;
	int Object_ID;
	int team;
public:

	float Particle_time_B = 0.f;

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
	float get_Arrow_delay(){ return Arrow_delay; }
	float get_TopBullet_delay() { return TopBullet_delay; }
	float get_BottomBullet_delay() { return BottomBullet_delay; }
	float get_dirX() {
		return Dir[0];
	}
	float get_dirY() {
		return Dir[1];
	}
	int get_type() { return Object_type; }
	int get_ID() { return Object_ID; }
	int get_team() { return team; }
	

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
	void set_ID(int input) { Object_ID = input; }
	void set_team(int input) { team = input; }
	
	void set_Arrow_delay(float input) { Arrow_delay = input; }
	void set_TopBullet_delay(float input) { TopBullet_delay = input; }
	void set_BottomBullet_delay(float input) { BottomBullet_delay = input; }
	
	void SetDir0()
	{
		Dir[0] = get_vx() / get_speed();
		Dir[1] = get_vy() / get_speed();
	}
	
public:
	void Update(float elapsedTime);
};

