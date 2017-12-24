#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <random>
#include <chrono>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define Lose 0

#define MAXOBJECT 300
#define OBJECT_BUILDING 0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3
#define Team_Top 0
#define Team_Bottom 1

#define LIFE 1000000.f
#define BUILDING_LIFE  500
#define CHARACTER_LIFE 100
#define BULLET_LIFE 15
#define ARROW_LIFE 10


#define ATTACK_GROUND 0
#define ATTACK_SKY 1
#define ATTACK_ALL 2

#define UNIT_GROUND 0
#define UNIT_SKY 1
#define UNIT_NEUTRAL 2

#define BUILDING_SIZE 100
#define CHARACTER_SIZE 10
#define BULLET_SIZE 5
#define ARROW_SIZE 5

#define CHARACTER_SPEED 300
#define BULLET_SPEED 450
#define ARROW_SPEED 600

#define RANGE 30

#   define  GLUT_BITMAP_9_BY_15   
#   define  GLUT_BITMAP_8_BY_13
#   define  GLUT_BITMAP_TIMES_ROMAN_10
#   define  GLUT_BITMAP_TIMES_ROMAN_24
#   define  GLUT_BITMAP_HELVETICA_10
#   define  GLUT_BITMAP_HELVETICA_12
#   define  GLUT_BITMAP_HELVETICA_18
