#include "stdafx.h"
#include "SceneMgr.h"
#include "Sound.h"

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

	Resource_Sound();

	AddObject(0, 320, OBJECT_BUILDING, Team_Top, false, ATTACK_ALL, UNIT_GROUND);
	AddObject(-200, 300, OBJECT_BUILDING, Team_Top, false, ATTACK_ALL, UNIT_GROUND);
	AddObject(200, 300, OBJECT_BUILDING, Team_Top, false, ATTACK_ALL, UNIT_GROUND);

	AddObject(0, -320, OBJECT_BUILDING, Team_Bottom, false, ATTACK_ALL, UNIT_GROUND);
	AddObject(-200, -300, OBJECT_BUILDING, Team_Bottom, false, ATTACK_ALL, UNIT_GROUND);
	AddObject(200, -300, OBJECT_BUILDING, Team_Bottom, false, ATTACK_ALL, UNIT_GROUND);

	m_Sound->PlaySound(sound_index, true, 0.2f);
}

void SceneMgr::Resource_Sound()
{
	// ���ҽ�
	char Nexus[] = "./Resource/Nexus.png";
	char Zerg[] = "./Resource/colony.png";
	char Back_Map[] = "./Resource/Cb.png";
	char Mechanic[] = "./Resource/Mecha.png";
	char Monster[] = "./Resource/Zergmon.png";
	char Particle1[] = "./Resource/Particle1.png";
	char Particle2[] = "./Resource/Particle2.png";
	char Back_fire[] = "./Resource/fire.png";
	char Sky_Monster[] = "./Resource/test.png";
	char Arrow_par[] = "./Resource/Arrow_parti.png";
	char witch[] = "./Resource/witch.png";

	Turret = renderer->CreatePngTexture(Nexus);
	colony = renderer->CreatePngTexture(Zerg);
	Map_cb = renderer->CreatePngTexture(Back_Map);
	Player_bot = renderer->CreatePngTexture(Mechanic);
	Player_top = renderer->CreatePngTexture(Monster);
	Particle_1 = renderer->CreatePngTexture(Particle1);
	Particle_2 = renderer->CreatePngTexture(Particle2);
	Arrow_particle = renderer->CreatePngTexture(Arrow_par);
	fire = renderer->CreatePngTexture(Back_fire);
	Sky_monster = renderer->CreatePngTexture(Sky_Monster);
	witch_terran = renderer->CreatePngTexture(witch);

	// ����
	char file_path8[] = "./Mp3/Terran.mp3";
	char file_path10[] = "./Mp3/Attack.mp3";
	char file_path11[] = "./Mp3/ProtossAttack.mp3";
	char Zergling[] = "./Mp3/zergling.mp3";
	char Sky_Sound[] = "./Mp3/sky_monster.mp3";
	char Hit[] = "./Mp3/Hit.mp3";

	sound_index = m_Sound->CreateSound(file_path8);
	AttackSound = m_Sound->CreateSound(file_path10);
	ProtossAttackSound = m_Sound->CreateSound(file_path11);
	ZerglingSound = m_Sound->CreateSound(Zergling);
	Skymon_Sound = m_Sound->CreateSound(Sky_Sound);
	HitSound = m_Sound->CreateSound(Hit);

}
void SceneMgr::DrawBack()
{

	renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1, 1, Map_cb, 0.5);

	renderer->DrawText(-90, 0, GLUT_BITMAP_TIMES_ROMAN_24, 1.f, 1.f, 1.f, "2013180015 byunkm");

	renderer->DrawParticle(
		50, 50, 0, 20,
		1, 1, 1, 1,
		0.4, 0.3,
		fire, Particle_time, 0.01f
	);
	renderer->DrawParticle(
		-135, 77, 0, 20,
		1, 1, 1, 1,
		-0.4, 0.3,
		fire, Particle_time, 0.01f
	);
	renderer->DrawParticle(
		225, 135, 0, 20,
		1, 1, 1, 1,
		0.4, 0.3,
		fire, Particle_time, 0.01f
	);
	renderer->DrawParticle(
		-100, -135, 0, 20,
		1, 1, 1, 1,
		0.4, 0.3,
		fire, Particle_time, 0.01f

	);
	renderer->DrawParticle(
		100, -200, 0, 20,
		1, 1, 1, 1,
		0.4, 0.3,
		fire, Particle_time, 0.01f
	);
	renderer->DrawParticle(
		65, 220, 0, 20,
		1, 1, 1, 1,
		0.4, 0.3,
		fire, Particle_time, 0.01f
	);
	// �ʿ� ��������
}
void SceneMgr::DrawAllObjects()
{
	DrawBack(); // ���׸���
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
					if (m_Objects[i]->get_U_type() == UNIT_SKY)
					{
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
							Sky_monster,
							transform, 0,
							4, 4,
							0.1
						);
					}
					if (m_Objects[i]->get_U_type() == UNIT_GROUND)
					{
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
							Player_top,
							transform, 0,
							4, 4,
							0.1
						);
					}
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
					if (m_Objects[i]->get_U_type() == UNIT_GROUND)
					{
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
					}

					if (m_Objects[i]->get_U_type() == UNIT_SKY)
					{
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
							witch_terran,
							transform2, 3,
							4, 4,
							0.1
						);
					}

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
					if (m_Objects[i]->get_type() == OBJECT_ARROW) {
						renderer->DrawParticle(
							m_Objects[i]->get_x(),
							m_Objects[i]->get_y(),
							0,
							m_Objects[i]->get_size(),
							m_Objects[i]->get_colorR(),
							m_Objects[i]->get_colorG(),
							m_Objects[i]->get_colorB(),
							m_Objects[i]->get_colorA(),
							-m_Objects[i]->get_vx() / m_Objects[i]->get_speed(),
							-m_Objects[i]->get_vy() / m_Objects[i]->get_speed(),
							Arrow_particle,
							m_Objects[i]->Particle_time_B,
							0.1
						);
					}

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
								-m_Objects[i]->get_vx() / m_Objects[i]->get_speed(),
								-m_Objects[i]->get_vy() / m_Objects[i]->get_speed(),
								Particle_1,
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
								-m_Objects[i]->get_vx() / m_Objects[i]->get_speed(),
								-(m_Objects[i]->get_vy() / m_Objects[i]->get_speed()),
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
	// Ȥ�ö� �����ִٸ� ����
}

int SceneMgr::AddObject(float x, float y, int Object_type, int team, bool status, bool Attack_type, bool Unit_type)
{
	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[i] == NULL)
		{
			m_Objects[i] = new Object(x, y, Object_type, team, status, Attack_type, Unit_type);
			return i;
		}
	}
	return -1;	
}


void SceneMgr::UpdateAllObjects(float elapsedTime)
{
	Collision(); // �浹 üũ

	float elapsedTimeInSecond = elapsedTime / 1000.f;
	TopCharacter_delay += elapsedTimeInSecond;
	TopCharacter_delay2 += elapsedTimeInSecond;
	BottomCharacter_delay += elapsedTimeInSecond;
	BottomCharacter2_delay += elapsedTimeInSecond;
	Particle_time += elapsedTimeInSecond;
	Particle_level += elapsedTimeInSecond;
	transform_time += elapsedTimeInSecond;
	// �ð� ���� ������Ʈ

	if (Wincount_bot == Lose || Wincount_Top == Lose) // �����ִ� �ǹ��� ���� �÷��̾ �߻��ϸ� ���η��� ��������
	{
		glutLeaveMainLoop();
	}

	// bullet �� ������ �浹�ϸ� ȭ�� ��鸲 .
	if (Shake == true)
	{
		int shakeBias = rand() % 20;
		Sheke_time += elapsedTime * 0.001f;
		renderer->SetSceneTransform(shakeBias, shakeBias, 1, 1);
		if (Sheke_time >= 1.f)
		{
			Shake = false;
			Sheke_time = 0.f;
			renderer->SetSceneTransform(0, 0, 1, 1);
		}
	}

	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_Objects[i]->get_lifetime() < 0.0001f || m_Objects[i]->get_life() <= 0.0001f)
			{
				if (m_Objects[i]->get_type() == OBJECT_BUILDING) //�����ִ� �ǹ� ����
				{
					if (m_Objects[i]->get_team() == Team_Top)
						Wincount_Top -= 1;
					if (m_Objects[i]->get_team() == Team_Bottom)
						Wincount_bot -= 1;
				}
				delete m_Objects[i];
				m_Objects[i] = NULL;
			}
			// �ð��� �������� ���� ������Ʈ ����
			
			else
			{
				m_Objects[i]->Update(elapsedTime, m_Objects[i]->get_Status());
				if (m_Objects[i]->get_type() == OBJECT_BUILDING) // ������Ʈ�� Ÿ���� ���� �϶�
				{
					if (m_Objects[i]->get_TopBullet_delay() > 5.0f)  
					{
						if (m_Objects[i]->get_team() == Team_Top)
						{
							AddObject(m_Objects[i]->get_x(), m_Objects[i]->get_y(), OBJECT_BULLET, Team_Top, false, ATTACK_ALL, UNIT_GROUND);
							m_Objects[i]->set_TopBullet_delay(0.f);
						}
					}

					if (m_Objects[i]->get_BottomBullet_delay() > 5.0f)
					{
						if (m_Objects[i]->get_team() == Team_Bottom)
						{
							int arrow_ID = AddObject(m_Objects[i]->get_x(), m_Objects[i]->get_y(), OBJECT_BULLET, Team_Bottom, false, ATTACK_ALL, UNIT_GROUND);
							m_Objects[i]->set_BottomBullet_delay(0.f);
						}
					}
				}
				//�Ѿ�

				if (m_Objects[i]->get_type() == OBJECT_CHARACTER) // ������Ʈ Ÿ���� ĳ�����϶�
				{
					if (m_Objects[i]->get_Arrow_delay() > 1.0f )
					{
						if (m_Objects[i]->get_team() == Team_Top)
						{
							int arrow_ID = AddObject(m_Objects[i]->get_x(), m_Objects[i]->get_y(), OBJECT_ARROW, Team_Top, false, ATTACK_ALL, UNIT_GROUND);
							m_Objects[i]->set_Arrow_delay(0.f);
							m_Objects[i]->set_ID(i);
							m_Objects[arrow_ID]->set_ID(i);
							m_Sound->PlaySound(HitSound, false, 0.2f);

						}

						if (m_Objects[i]->get_team() == Team_Bottom)
						{
							int arrow_ID = AddObject(m_Objects[i]->get_x(), m_Objects[i]->get_y(), OBJECT_ARROW, Team_Bottom, false, ATTACK_ALL, UNIT_GROUND);
							m_Objects[i]->set_Arrow_delay(0.f);
							m_Objects[i]->set_ID(i);
							m_Objects[arrow_ID]->set_ID(i);
							m_Sound->PlaySound(HitSound, false, 0.2f);

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
			}
		}
	}

	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[i] == NULL)
		{
			if (TopCharacter_delay2 >= 3.0f)
			{
				default_random_engine dre;										
				uniform_int_distribution<int> yPos(100, 400);					
				dre.seed(time(NULL));

				default_random_engine dre2;
				uniform_int_distribution<int> xPos(-250, 250);
				dre.seed(time(NULL));

				AddObject(xPos(dre2), yPos(dre), OBJECT_CHARACTER, Team_Top, false, ATTACK_SKY, UNIT_SKY); // ���� ���� ���� ����
				m_Sound->PlaySound(Skymon_Sound, false, 0.2f);
				TopCharacter_delay2 = 0.0f;
			}

			if (TopCharacter_delay >= 5.0f)										
 			{
				default_random_engine dre;										// ���� ����
				uniform_int_distribution<int> yPos(100, 400);					// y ��ǥ���� ����( �������������� ����)
				dre.seed(time(NULL));

				default_random_engine dre2;
				uniform_int_distribution<int> xPos(-250, 250);
				dre.seed(time(NULL));

				AddObject(xPos(dre2), yPos(dre), OBJECT_CHARACTER, Team_Top, false, ATTACK_GROUND, UNIT_GROUND); // ���� ���� ĳ������ ����
				TopCharacter_delay = 0.f;
				m_Sound->PlaySound(ZerglingSound, false, 0.2f);
			}

			// ���� �� ĳ���� ����
		}
	}
}

void SceneMgr::Collision()
{
	for (int i = 0; i < MAXOBJECT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_Objects[i]->get_type() == OBJECT_BULLET || m_Objects[i]->get_type() == OBJECT_ARROW) //�Ѿ�, ȭ���� �ʹ����� ������ ����
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

					if (m_Objects[i]->get_type() == OBJECT_CHARACTER
						&& m_Objects[i]->get_team() != m_Objects[j]->get_team()) // �Ѵ� ĳ�����ϋ��� ���� �˻�
					{
						if (CollisionCheck(minX - RANGE, minY - RANGE, maxX+ RANGE, maxY + RANGE, minX1 - RANGE, minY1 - RANGE, maxX1 + RANGE, maxY1 + RANGE)) // ���� ���� �ȿ� �������
						{
							if (m_Objects[j]->get_type() == OBJECT_CHARACTER) // �Ѵ� ĳ���Ͷ��?
							{
								if (m_Objects[i]->get_A_type() == m_Objects[j]->get_U_type()) // ���� ����Ÿ�԰� ����� ���� Ÿ���� ���ٸ� (�ϴ� == �ϴ�)
								{
									m_Objects[i]->set_Status(true); // �Ѵ� �������� ���߰� �� �ڸ����� ������ ����Ѵ�.
									m_Objects[j]->set_Status(true);
								}
							}

							if (m_Objects[j]->get_type() == OBJECT_ARROW) 
							{
								if (m_Objects[i]->get_ID() != m_Objects[j]->get_ID()) // ���̵� �޶�� ����(�ڱⰡ �� ȭ���� �ƴϾ���Ѵ�)
								{
									m_Objects[i]->set_life(m_Objects[i]->get_life() - m_Objects[j]->get_life());
									delete m_Objects[j];
									m_Objects[j] = NULL;
								}
							}
						}
					}

					else if (m_Objects[i]->get_type() != m_Objects[j]->get_type() && m_Objects[i]->get_team() != m_Objects[j]->get_team()) // ���� Ÿ���� �޶�� �����ϴ� �浹üũ
					{
						if (CollisionCheck(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
						{
							if (m_Objects[i]->get_type() == OBJECT_BUILDING)								 // ������Ʈ Ÿ���� �����̶��
							{
								Shake = true;
								if (m_Objects[i]->get_team() == Team_Top)
									m_Sound->PlaySound(AttackSound, false, 0.2f);
								else
									m_Sound->PlaySound(ProtossAttackSound, false, 0.2f);
								m_Objects[i]->set_life(m_Objects[i]->get_life() - m_Objects[j]->get_life()); // ������ hp���� �ε��� ������Ʈ hp�� ����
								delete m_Objects[j];														 // ������ �ε��� ������Ʈ�� ����
								m_Objects[j] = NULL;
								
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
