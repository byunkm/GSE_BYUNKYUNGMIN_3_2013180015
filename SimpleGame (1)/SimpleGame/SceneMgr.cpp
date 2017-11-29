#include "stdafx.h"
#include "SceneMgr.h"

GLuint Turret = 0;
GLuint colony = 0;

SceneMgr::SceneMgr(int width, int height)
{
	renderer = new Renderer(width, height);
	m_windowWidth = width;
	m_windowHeight = height;

	for (int i = 0; i < MAXOBJECT; i++)
	{
		m_Objects[i] = NULL;
	}

	char file_path[] = "terret.png";
	char file_path2[] = "colony.png";

	Turret = renderer->CreatePngTexture(file_path);
	colony = renderer->CreatePngTexture(file_path2);

	AddObject(0, 320, OBJECT_BUILDING, Team_Top);
	AddObject(-200, 300, OBJECT_BUILDING, Team_Top);
	AddObject(200, 300, OBJECT_BUILDING, Team_Top);

	AddObject(0, -320, OBJECT_BUILDING, Team_Bottom);
	AddObject(-200, -300, OBJECT_BUILDING, Team_Bottom);
	AddObject(200, -300, OBJECT_BUILDING, Team_Bottom);

}

void SceneMgr::DrawAllObjects()
{
	
	renderer->DrawSolidRect(0, 0, 0, m_windowWidth, 0, 0, 0, 0.4, 0.5);

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
					renderer->DrawSolidRect(
						m_Objects[i]->get_x(),
						m_Objects[i]->get_y(),
						0,
						m_Objects[i]->get_size(),
						m_Objects[i]->get_colorR(),
						m_Objects[i]->get_colorG(),
						m_Objects[i]->get_colorB(),
						m_Objects[i]->get_colorA(),
						0.2f
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
					renderer->DrawSolidRect(
						m_Objects[i]->get_x(),
						m_Objects[i]->get_y(),
						0,
						m_Objects[i]->get_size(),
						m_Objects[i]->get_colorR(),
						m_Objects[i]->get_colorG(),
						m_Objects[i]->get_colorB(),
						m_Objects[i]->get_colorA(),
						0.2f
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
					if (m_Objects[i]->get_TopBullet_delay() > 10.0f)  
					{
						if (m_Objects[i]->get_team() == Team_Top)
						{
							AddObject(m_Objects[i]->get_x(), m_Objects[i]->get_y(), OBJECT_BULLET, Team_Top); 
							m_Objects[i]->set_TopBullet_delay(0.f);
						}
					}

					if (m_Objects[i]->get_BottomBullet_delay() > 10.0f)
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
