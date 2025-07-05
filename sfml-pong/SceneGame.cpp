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

	//일반 가상함수이기에 부모씬에서 사용하던걸 호출하기위해 부모함수도 호출해야한다.
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
		//매 프레임마다 볼이 배트를 따라다닌다.
		ball->SetPosition(bat->GetPosition());

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			ballActive = true;

			//방향 : 오른쪽 위 대각선
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
