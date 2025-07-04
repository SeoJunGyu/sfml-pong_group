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
	bat = (Bat*)AddGameObject(new Bat("Bat"));
	//ball = (Ball*)AddGameObject(new Ball("Ball"));

	bat->SetSide(Sides::Left);
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	std::cout << bounds.height * 0.5f;

	//ball->SetBat(bat);

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

	/*
	if (!ballActive)
	{
		//�� �����Ӹ��� ���� ��Ʈ�� ����ٴѴ�.
		ball->SetPosition(bat->GetPosition());

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			ballActive = true;

			//���� : ������ �� �밢��
			sf::Vector2f dir(1.f, -1.f);
			Utils::Normalize(dir);
			ball->Fire(dir, 500.f);
		}
	}
	*/
	
}

void SceneDuoGame::SetGameOver()
{
	SCENE_MGR.ChangeScene(SceneIds::Game);
}
