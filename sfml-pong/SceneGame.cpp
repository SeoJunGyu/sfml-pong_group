#include "stdafx.h"
#include "SceneGame.h"
#include "Bat.h"
#include "Ball.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	bat = (Bat*)AddGameObject(new Bat("Bat"));
	ball = (Ball*)AddGameObject(new Ball("Ball"));

	bat->SetOrigin(Origins::TC);
	ball->SetBat(bat);

	//�Ϲ� �����Լ��̱⿡ �θ������ ����ϴ��� ȣ���ϱ����� �θ��Լ��� ȣ���ؾ��Ѵ�.
	Scene::Init(); 

}

void SceneGame::Enter()
{
	ballActive = false;

	Scene::Enter();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

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
}

void SceneGame::SetGameOver()
{
	SCENE_MGR.ChangeScene(SceneIds::Game);
}
