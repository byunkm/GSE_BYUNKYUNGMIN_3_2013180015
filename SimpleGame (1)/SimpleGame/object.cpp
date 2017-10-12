#include "stdafx.h"
#include "Object.h"

 Object::Object()
{


}

Object::~Object()
{


}

Object::Object(float x, float y, float z, float size, float speed, float R, float G, float B, float A) : x(x), y(y), z(z), size(size), speed(speed),R(R), G(G), B(B), A(A)
{
	


}
float Object::Get_x() {
	return x;
	
}
float Object::Get_y() {
	return y;
	
}
float Object::Get_z() {
	return z;
	
}
float Object::Get_size() {
	return size;
	
}
float Object::Get_speed(){
	return speed;
}
float Object::Get_R() {
	return R;
	
}
float Object::Get_G() {
	return G;
	
}
float Object::Get_B() {
	return B;
	
}
float Object::Get_A() {
	return A;
}

void Object::Position()
{
	x = Get_x();
	y = Get_y();
	z = Get_z();
	size = Get_size();
}


void Object::Update()
{
	if (x < 500)
		moving();

}

void Object::moving()
{
	x += speed;
	y += speed;
}