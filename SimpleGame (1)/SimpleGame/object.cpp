#include "stdafx.h"
#include "Object.h"

 Object::Object()
{


}

Object::~Object()
{


}

Object::Object(float x, float y, float z, float size, float R, float G, float B, float A) : x(x), y(y), z(z), size(size), R(R), G(G), B(B), A(A)
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