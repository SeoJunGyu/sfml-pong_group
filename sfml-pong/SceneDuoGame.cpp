#include "stdafx.h"
#include "SceneDuoGame.h"
#include "Bat.h"
#include "Ball.h"

SceneDuoGame::SceneDuoGame()
	: Scene(SceneIds::DuoGame)
{
}

void SceneDuoGame::Init()
{
	bat1 = (Bat*)AddGameObject(new Bat("Bat1"));
	bat2 = (Bat*)AddGameObject(new Bat("Bat2"));
	ball = (Ball*)AddGameObject(new Ball("Ball"));

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	bat1->SetSide(Sides::Left);
	bat1->SetPosition({ bounds.left + 20.f, bounds.height * 0.5f });
	bat1->SetDuo(true);
	bat1->SetOrigin(Origins::MR);

	bat2->SetSide(Sides::Right);
	bat2->SetPosition({ bounds.left + bounds.width - 20.f, bounds.height * 0.5f });
	bat2->SetDuo(true);
	bat2->SetOrigin(Origins::ML);
	
	ball->SetBat1(bat1);
	ball->SetBat2(bat2);
	ball->SetDuo(true);
	ball->SetOrigin(Origins::ML);

	//�Ϲ� �����Լ��̱⿡ �θ������ ����ϴ��� ȣ���ϱ����� �θ��Լ��� ȣ���ؾ��Ѵ�.
	Scene::Init();

}

void SceneDuoGame::Enter()
{
	ballActive = false;

	Scene::Enter();
}

void SceneDuoGame::Update(float dt)
{
	Scene::Update(dt);

	if (!ballActive)
	{
		//�� �����Ӹ��� ���� ��Ʈ�� ����ٴѴ�.
		ball->SetPosition(bat1->GetPosition());

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			ballActive = true;

			//���� : ������ �� �밢��
			sf::Vector2f dir(1.f, -1.f);
			Utils::Normalize(dir);
			ball->Fire(dir, 500.f);
		}
	}
	
}

void SceneDuoGame::SetGameOver()
{
	SCENE_MGR.ChangeScene(SceneIds::DuoGame);
}
