#include "stdafx.h"
#include "SceneMgr.h"

GLuint Texture_Num = 0;
SceneMgr::SceneMgr(int width, int height)
{
	renderer = new Renderer(width, height);
	m_windowWidth = width;
	m_windowHeight = height;

	for (int i = 0; i < MAXOBJECT; i++)
	{
		m_Objects[i] = NULL;
		m_bullet[i] = NULL;
	}

	char file_path[] = "terret.png";
	Texture_Num = renderer->CreatePngTexture(file_path);
}

void SceneMgr::DrawAllObjects()
{
	renderer->DrawSolidRect(0, 0, 0, m_windowWidth, 0, 0, 0, 0.4);

	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_Objects[i]->get_type() == OBJECT_BUILDING)
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
					Texture_Num
				);
			}
			else
			{
				renderer->DrawSolidRect(
					m_Objects[i]->get_x(),
					m_Objects[i]->get_y(),
					0,
					m_Objects[i]->get_size(),
					m_Objects[i]->get_colorR(),
					m_Objects[i]->get_colorG(),
					m_Objects[i]->get_colorB(),
					m_Objects[i]->get_colorA()
				);
			}
		}

		if (m_bullet[i] != NULL)
		{
			renderer->DrawSolidRect(
				m_bullet[i]->get_x(),
				m_bullet[i]->get_y(),
				0,
				m_bullet[i]->get_size(),
				m_bullet[i]->get_colorR(),
				m_bullet[i]->get_colorG(),
				m_bullet[i]->get_colorB(),
				m_bullet[i]->get_colorA()
			);
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

		if (m_bullet[i] != NULL)
		{
			delete m_bullet[i];
			m_bullet[i] = NULL;
		}
	}
	// 혹시라도 남아있다면 제거
}

int SceneMgr::AddObject(float x, float y, int Object_type)
{
	if (Object_type != OBJECT_BULLET)
	{
		for (int i = 0; i < MAXOBJECT; i++)
		{
			if (m_Objects[i] == NULL)
			{
				m_Objects[i] = new Object(x, y, Object_type);
				return i;
			}
		}
		return -1;
	}
}
int SceneMgr::Addbullet()
{
	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[0] != NULL && m_Objects[0]->get_type() == OBJECT_BUILDING)
		{
			if (m_bullet[i] == NULL && BulletNum <= 99) // 총알은 100개까지 생성
			{
				m_bullet[BulletNum] = new Object(m_Objects[0]->get_x(), m_Objects[0]->get_y(), OBJECT_BULLET);
				BulletNum += 1;
				return i;
			}
		}
	}
	return -1;
}


void SceneMgr::UpdateAllObjects(float elapsedTime)
{
	Collision();
	float elapsedTimeInSecond = elapsedTime / 1000.f;
	time += elapsedTimeInSecond;
	if (time >= 0.5f)
	{
		term = false;
		time = 0.f;
	}
	else 
	{
		term = true;
		Shoot = true; 
		ArrowShoot = true;
	}
	//// 0.5초에 한발씩 쏘기 위한 변수 설정
	

	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_Objects[i]->get_lifetime() < 0.0001f || m_Objects[i]->get_life() <= 0.0001f) // 시간과 라이프에 따른 오브젝트 제거
			{
				if (m_Objects[i]->get_type() == OBJECT_CHARACTER)
					onwer -= 1;
				delete m_Objects[i];
				m_Objects[i] = NULL;
			}

			else
			{
				m_Objects[i]->Update(elapsedTime);
				if (m_Objects[i]->get_type() == OBJECT_CHARACTER) // 오브젝트의 타입이 캐릭터일때
				{
					if (m_Objects[i]->get_Arrow_delay() > 0.5f)   // 화살 발사 간격
					{
						int arrow_ID = AddObject(m_Objects[i]->get_x(), m_Objects[i]->get_y(), OBJECT_ARROW); // 화살이 오브젝트 배열의 몇번째에 들어가는지 저장.
						m_Objects[i]->set_Arrow_delay(0.f);
						m_Objects[i]->set_ID(i);        // 부모 캐릭터에 아이디 부여
						m_Objects[arrow_ID]->set_ID(i); // 화살에 부모 캐릭터의 아이디 부여
					}
				}
			}

			if (term == false && Shoot == true)
			{
				Addbullet();	//0.5초간격 총알 추가
				Shoot = false;
			}
		}

		if (m_bullet[i] != NULL)										    //총알이 존재하면
		{
			m_bullet[i]->Update(elapsedTime);								// 총알 업데이트
		}
	}
}

void SceneMgr::Collision()
{
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
				
					if (m_Objects[i]->get_type() != m_Objects[j]->get_type())								 // 타입이 달라야 충돌체크를 실행한다
					{
						if (CollisionCheck(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
						{
							if (m_Objects[i]->get_type() == OBJECT_BUILDING)								 // 오브젝트 타입이 빌딩이라면
							{
								if (m_Objects[j]->get_type() == OBJECT_CHARACTER)
									onwer -= 1;

								m_Objects[i]->set_life(m_Objects[i]->get_life() - m_Objects[j]->get_life()); // 빌딩의 hp에서 플레이어의 hp를 뺀다
								delete m_Objects[j];														 // 빌딩과 부딪힌 오브젝트의 삭제
								m_Objects[j] = NULL;
							}

							if (m_Objects[i]->get_type() == OBJECT_CHARACTER && m_Objects[j]->get_type() ==OBJECT_ARROW) // 캐릭터와 화살 사이에 진행
							{
								if (m_Objects[i]->get_ID() != m_Objects[j]->get_ID()) // 아이디가 달라야 실행(자기가 쏜 총알이 아니어야한다)
								{
									m_Objects[i]->set_life(m_Objects[i]->get_life() - m_Objects[j]->get_life());
									delete m_Objects[j];
									m_Objects[j] = NULL;
								}
							}
						}
					}
				}

				if (m_bullet[j] != NULL) // 총알이 있을때 만 진행
				{
					float minX, minY;
					float maxX, maxY;

					float minBX, minBY;
					float maxBX, maxBY;

					minX = m_Objects[i]->get_x() - m_Objects[i]->get_size() / 2.f;
					minY = m_Objects[i]->get_y() - m_Objects[i]->get_size() / 2.f;
					maxX = m_Objects[i]->get_x() + m_Objects[i]->get_size() / 2.f;
					maxY = m_Objects[i]->get_y() + m_Objects[i]->get_size() / 2.f;

					minBX = m_bullet[j]->get_x() - m_bullet[j]->get_size() / 2.f;
					minBY = m_bullet[j]->get_y() - m_bullet[j]->get_size() / 2.f;
					maxBX = m_bullet[j]->get_x() + m_bullet[j]->get_size() / 2.f;
					maxBY = m_bullet[j]->get_y() + m_bullet[j]->get_size() / 2.f;


					if (CollisionCheck(minX, minY, maxX, maxY, minBX, minBY, maxBX, maxBY))				// 총알과 캐릭터 충돌 체크
					{
						if (m_Objects[i]->get_type() == OBJECT_CHARACTER || m_Objects[i]->get_type() == OBJECT_ARROW)
						{
							m_Objects[i]->set_life(m_Objects[i]->get_life() - m_bullet[j]->get_life()); // 플레이어 life - 총알 life
							delete m_bullet[j];															// 총알삭제
							m_bullet[j] = NULL;
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
