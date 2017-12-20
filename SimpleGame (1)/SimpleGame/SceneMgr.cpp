#include "stdafx.h"
#include "SceneMgr.h"
#include "Sound.h"
GLuint Turret = 0;
GLuint colony = 0;
GLuint Map_cb = 0;
GLuint Player_bot = 0;
GLuint Player_top = 0;
GLuint Star = 0;

GLuint Particle_1 = 0;
GLuint Particle_2 = 0;
float Particle_time = 0;
float Particle_time2 ;
float Particle_level = 0;
int sound_index = 0;

SceneMgr::SceneMgr(int width, int height)
{
	renderer = new Renderer(width, height);
	m_Sound = new Sound();
	m_windowWidth = width;
	m_windowHeight = height;

	for (int i = 0; i < MAXOBJECT; i++)
	{
		m_Objects[i] = NULL;
	}

	char file_path[] = "terret.png";
	char file_path2[] = "colony.png";
	char file_path3[] = "Cb.png";
	char file_path4[] = "Player_bottom.png";
	char file_path7[] = "Player_top.png";

	char file_path5[] = "Particle1.png";
	char file_path6[] = "Particle2.png";
	char file_path8[] = "Terran.mp3";
	char file_path9[] = "Star.png";

	sound_index = m_Sound->CreateSound(file_path8);
	m_Sound->PlaySound(sound_index, true, 0.2f);
	Turret = renderer->CreatePngTexture(file_path);
	colony = renderer->CreatePngTexture(file_path2);
	Map_cb = renderer->CreatePngTexture(file_path3);
	Player_bot = renderer->CreatePngTexture(file_path4);
	Player_top = renderer->CreatePngTexture(file_path7);
	Particle_1 = renderer->CreatePngTexture(file_path5);
	Particle_2 = renderer->CreatePngTexture(file_path6);
	Star = renderer->CreatePngTexture(file_path9);

	AddObject(0, 320, OBJECT_BUILDING, Team_Top);
	AddObject(-200, 300, OBJECT_BUILDING, Team_Top);
	AddObject(200, 300, OBJECT_BUILDING, Team_Top);

	AddObject(0, -320, OBJECT_BUILDING, Team_Bottom);
	AddObject(-200, -300, OBJECT_BUILDING, Team_Bottom);
	AddObject(200, -300, OBJECT_BUILDING, Team_Bottom);

	

}

void SceneMgr::DrawAllObjects()
{
	
	renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1,1, Map_cb, 0.5);

	renderer->DrawText(-90, 0, GLUT_BITMAP_TIMES_ROMAN_24, 1.f, 1.f, 1.f, "2013180015 byunkm");
	
	renderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.1, -0.1, Star, Particle_time, 0.01);

	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_Objects[i]->get_type() == OBJECT_BUILDING && m_Objects[i]->get_team() == Team_Top)
			{
					renderer->DrawTexturedRect(
					m_Objects[i]->get_x(),
					m_Objects[i]->get_y(),
					0,
					m_Objects[i]->get_size(),
					m_Objects[i]->get_colorR(),
					m_Objects[i]->get_colorG(),
					m_Objects[i]->get_colorB(),
					m_Objects[i]->get_colorA(),
					colony,
					0.1f
				);
					renderer->DrawSolidRectGauge(
						m_Objects[i]->get_x(),
						m_Objects[i]->get_y()+ 60,
						0,
						100,
						5,
						1,
						0,
						0,
						m_Objects[i]->get_colorA(),
						m_Objects[i]->get_life()/BUILDING_LIFE,
						0.2
				);
				
			}  
			
			if (m_Objects[i]->get_type() == OBJECT_BUILDING && m_Objects[i]->get_team() == Team_Bottom)
			{
				renderer->DrawTexturedRect(
					m_Objects[i]->get_x(),
					m_Objects[i]->get_y(),
					0,
					m_Objects[i]->get_size(),
					m_Objects[i]->get_colorR(),
					m_Objects[i]->get_colorG(),
					m_Objects[i]->get_colorB(),
					m_Objects[i]->get_colorA(),
					Turret,
					0.1f
				);
				renderer->DrawSolidRectGauge(
					m_Objects[i]->get_x(),
					m_Objects[i]->get_y() + 60,
					0,
					100,
					5,
					0,
					0,
					1,
					m_Objects[i]->get_colorA(),
					m_Objects[i]->get_life() / BUILDING_LIFE,
					0.2
				);
			}

			else
			{
				if (m_Objects[i]->get_type() == OBJECT_CHARACTER && m_Objects[i]->get_team() == Team_Top)
				{
					/*renderer->DrawSolidRect(
						m_Objects[i]->get_x(),
						m_Objects[i]->get_y(),
						0,
						m_Objects[i]->get_size(),
						m_Objects[i]->get_colorR(),
						m_Objects[i]->get_colorG(),
						m_Objects[i]->get_colorB(),
						m_Objects[i]->get_colorA(),
						0.2f
					);*/
					renderer->DrawTexturedRectSeq
					(
						m_Objects[i]->get_x(),
						m_Objects[i]->get_y(),
						0,
						m_Objects[i]->get_size()+50,
						m_Objects[i]->get_colorR(),
						m_Objects[i]->get_colorG(),
						m_Objects[i]->get_colorB(),
						m_Objects[i]->get_colorA(),
						Player_bot,
						transform, 0,
						4,4,
						0.1
					);

					renderer->DrawSolidRectGauge(
						m_Objects[i]->get_x(),
						m_Objects[i]->get_y() + 20,
						0,
						30,
						5,
						1,
						0,
						0,
						m_Objects[i]->get_colorA(),
						m_Objects[i]->get_life() / CHARACTER_LIFE,
						0.2
					);
				}

				if (m_Objects[i]->get_type() == OBJECT_CHARACTER && m_Objects[i]->get_team() == Team_Bottom)
				{
					/*renderer->DrawSolidRect(
						m_Objects[i]->get_x(),
						m_Objects[i]->get_y(),
						0,
						m_Objects[i]->get_size(),
						m_Objects[i]->get_colorR(),
						m_Objects[i]->get_colorG(),
						m_Objects[i]->get_colorB(),
						m_Objects[i]->get_colorA(),
						0.2f
					);*/

					renderer->DrawTexturedRectSeq
					(
						m_Objects[i]->get_x(),
						m_Objects[i]->get_y(),
						0,
						m_Objects[i]->get_size() + 50,
						m_Objects[i]->get_colorR(),
						m_Objects[i]->get_colorG(),
						m_Objects[i]->get_colorB(),
						m_Objects[i]->get_colorA(),
						Player_bot,
						transform2, 3,
						4, 4,
						0.1
					);

					renderer->DrawSolidRectGauge(
						m_Objects[i]->get_x(),
						m_Objects[i]->get_y() + 20,
						0,
						30,
						5,
						0,
						0,
						1,
						m_Objects[i]->get_colorA(),
						m_Objects[i]->get_life() / CHARACTER_LIFE,
						0.2
					);
				}
				if (m_Objects[i]->get_type() == OBJECT_BULLET
					|| m_Objects[i]->get_type() == OBJECT_ARROW)
				{
					renderer->DrawSolidRect(
						m_Objects[i]->get_x(),
						m_Objects[i]->get_y(),
						0,
						m_Objects[i]->get_size(),
						m_Objects[i]->get_colorR(),
						m_Objects[i]->get_colorG(),
						m_Objects[i]->get_colorB(),
						m_Objects[i]->get_colorA(),
						0.3f
					);

					if (m_Objects[i]->get_type() == OBJECT_BULLET)
					{
						if (m_Objects[i]->get_team() == Team_Top)
						{
							renderer->DrawParticle
							(
								m_Objects[i]->get_x(),
								m_Objects[i]->get_y(),
								0,
								m_Objects[i]->get_size(),
								m_Objects[i]->get_colorR(),
								m_Objects[i]->get_colorG(),
								m_Objects[i]->get_colorB(),
								m_Objects[i]->get_colorA(),
								0,
								1,
								0.1,
								m_Objects[i]->Particle_time_B,
								0.1
							);
						}

						if (m_Objects[i]->get_team() == Team_Bottom)
						{
							renderer->DrawParticle
							(
								m_Objects[i]->get_x(),
								m_Objects[i]->get_y(),
								0,
								m_Objects[i]->get_size(),
								m_Objects[i]->get_colorR(),
								m_Objects[i]->get_colorG(),
								m_Objects[i]->get_colorB(),
								m_Objects[i]->get_colorA(),
								0,
								-1,
								Particle_2,
								m_Objects[i]->Particle_time_B,
								0.1

							);
						}

					}
				}
			}
		}
	}
}

SceneMgr::~SceneMgr()
{
	for (int i = 0; i < MAXOBJECT; i++) {
		if (m_Objects[i] != NULL)
		{
			delete m_Objects[i];
			m_Objects[i] = NULL;
		}
	}
	// 혹시라도 남아있다면 제거
}

int SceneMgr::AddObject(float x, float y, int Object_type, int team)
{
	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[i] == NULL)
		{
			m_Objects[i] = new Object(x, y, Object_type, team);
			return i;
		}
	}
	return -1;	
}


void SceneMgr::UpdateAllObjects(float elapsedTime)
{
	Collision();
	float elapsedTimeInSecond = elapsedTime / 1000.f;
	TopCharacter_delay += elapsedTimeInSecond;
	BottomCharacter_delay += elapsedTimeInSecond;
	Particle_time += elapsedTimeInSecond;
	Particle_level += elapsedTimeInSecond;
	transform_time += elapsedTimeInSecond;

	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_Objects[i]->get_lifetime() < 0.0001f || m_Objects[i]->get_life() <= 0.0001f)
			{
				delete m_Objects[i];
				m_Objects[i] = NULL;
			}
			// 시간과 라이프에 따른 오브젝트 제거
			
			else
			{
				m_Objects[i]->Update(elapsedTime);
				if (m_Objects[i]->get_type() == OBJECT_BUILDING) // 오브젝트의 타입이 빌딩 일때
				{
					if (m_Objects[i]->get_TopBullet_delay() > 1.0f)  
					{
						if (m_Objects[i]->get_team() == Team_Top)
						{
							AddObject(m_Objects[i]->get_x(), m_Objects[i]->get_y(), OBJECT_BULLET, Team_Top); 
							m_Objects[i]->set_TopBullet_delay(0.f);
						}
					}

					if (m_Objects[i]->get_BottomBullet_delay() > 1.0f)
					{
						if (m_Objects[i]->get_team() == Team_Bottom)
						{
							int arrow_ID = AddObject(m_Objects[i]->get_x(), m_Objects[i]->get_y(), OBJECT_BULLET, Team_Bottom); 
							m_Objects[i]->set_BottomBullet_delay(0.f);
						}
					}
				}
				//총알
				if (m_Objects[i]->get_type() == OBJECT_CHARACTER) // 오브젝트 타입이 캐릭터일때
				{
					if (m_Objects[i]->get_Arrow_delay() > 3.0f)
					{
						if (m_Objects[i]->get_team() == Team_Top)
						{
							int arrow_ID = AddObject(m_Objects[i]->get_x(), m_Objects[i]->get_y(), OBJECT_ARROW, Team_Top);  
							m_Objects[i]->set_Arrow_delay(0.f);
							m_Objects[i]->set_ID(i);
							m_Objects[arrow_ID]->set_ID(i);
						}
						if (m_Objects[i]->get_team() == Team_Bottom)
						{
							int arrow_ID = AddObject(m_Objects[i]->get_x(), m_Objects[i]->get_y(), OBJECT_ARROW, Team_Bottom);
							m_Objects[i]->set_Arrow_delay(0.f);
							m_Objects[i]->set_ID(i);
							m_Objects[arrow_ID]->set_ID(i);
						}
					}

					if (transform_time >= 0.1f)
					{
						transform += 1;
						transform2 += 1;
						transform = transform % 4;
						transform2 = transform % 4;
						transform_time = 0.f;
					}
				}
				//화살

			
			}
		}
	}

	
	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[i] == NULL)
		{
			if (TopCharacter_delay >= 5.0f)										// 북쪽 캐릭터의 생성 주기 5.0초
 			{
				default_random_engine dre;										// 랜덤 엔진
				uniform_int_distribution<int> yPos(100, 400);					// y 좌표값의 제한( 북쪽지역에서만 생성)
				dre.seed(time(NULL));

				default_random_engine dre2;
				uniform_int_distribution<int> xPos(-250, 250);
				dre.seed(time(NULL));

				AddObject(xPos(dre2), yPos(dre), OBJECT_CHARACTER, Team_Top);	// 북쪽 지역 캐릭터의 생성
				TopCharacter_delay = 0.f;
			}
			// 북쪽 팀 캐릭터 생성
		}
	}
}

void SceneMgr::Collision()
{
	particle++;
	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_Objects[i]->get_type() == OBJECT_BULLET || m_Objects[i]->get_type() == OBJECT_ARROW)
			{
				if (m_Objects[i]->get_x() <= -250 || m_Objects[i]->get_x() >= 250
					|| m_Objects[i]->get_y() <= -400 || m_Objects[i]->get_y() >= 400)
				{
					delete m_Objects[i];
					m_Objects[i] = NULL;
				}
			}
		}
	}
	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			for (int j = 0; j < MAXOBJECT; j++)
			{
				if (i == j)
					continue;
				if (m_Objects[j] != NULL)
				{
					float minX, minY;
					float maxX, maxY;

					float minX1, minY1;
					float maxX1, maxY1;

					minX = m_Objects[i]->get_x() - m_Objects[i]->get_size() / 2.f;
					minY = m_Objects[i]->get_y() - m_Objects[i]->get_size() / 2.f;
					maxX = m_Objects[i]->get_x() + m_Objects[i]->get_size() / 2.f;
					maxY = m_Objects[i]->get_y() + m_Objects[i]->get_size() / 2.f;

					minX1 = m_Objects[j]->get_x() - m_Objects[j]->get_size() / 2.f;
					minY1 = m_Objects[j]->get_y() - m_Objects[j]->get_size() / 2.f;
					maxX1 = m_Objects[j]->get_x() + m_Objects[j]->get_size() / 2.f;
					maxY1 = m_Objects[j]->get_y() + m_Objects[j]->get_size() / 2.f;

					if (m_Objects[i]->get_type() != m_Objects[j]->get_type() && m_Objects[i]->get_team() != m_Objects[j]->get_team()) // 팀과 타입이 달라야 진행
					{
						if (CollisionCheck(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
						{
							if (m_Objects[i]->get_type() == OBJECT_BUILDING)								 // 오브젝트 타입이 빌딩이라면
							{
								m_Objects[i]->set_life(m_Objects[i]->get_life() - m_Objects[j]->get_life()); // 빌딩의 hp에서 부딪힌 오브젝트 hp를 뺀다
								delete m_Objects[j];														 // 빌딩과 부딪힌 오브젝트의 삭제
								m_Objects[j] = NULL;
							}

							if (m_Objects[i]->get_type() == OBJECT_CHARACTER) // 캐릭터일때
							{
								if (m_Objects[j]->get_type() == OBJECT_ARROW)
								{
									if (m_Objects[i]->get_ID() != m_Objects[j]->get_ID()) // 아이디가 달라야 실행(자기가 쏜 화살이 아니어야한다)
									{
										m_Objects[i]->set_life(m_Objects[i]->get_life() - m_Objects[j]->get_life());
										delete m_Objects[j];
										m_Objects[j] = NULL;
									}
								}
								else
								{
									
									m_Objects[i]->set_life(m_Objects[i]->get_life() - m_Objects[j]->get_life());
									delete m_Objects[j];
									m_Objects[j] = NULL;
								}
							}
						}
					}
				}
			}
		}	
	}
}

bool SceneMgr::CollisionCheck(float a_minX, float a_minY, float a_maxX, float a_maxY, float b_minX, float b_minY, float b_maxX, float b_maxY)
{
	if (a_minX > b_maxX)
		return false;
	if (a_maxX < b_minX)
		return false;

	if (a_minY > b_maxY)
		return false;
	if (a_maxY < b_minY)
		return false;

	return true;
}
