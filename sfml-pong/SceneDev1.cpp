#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"

SceneDev1::SceneDev1()
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf");
	go->SetString("Dev 1");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	AddGameObject(go);

	testGo = new TextGo("fonts/DS-DIGIT.ttf");
	testGo->SetString("Dev 1");
	testGo->SetCharacterSize(30);
	testGo->SetFillColor(sf::Color::Red);
	AddGameObject(testGo);

	Scene::Init();
}

void SceneDev1::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		testGo->sortingOrder = -1;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		testGo->sortingOrder = 1;
	}

	sf::Vector2f dir;
	dir.x = InputMgr::GetAxis(Axis::Horizontal);
	dir.y = InputMgr::GetAxis(Axis::Vertical);

	std::cout << InputMgr::GetAxis(Axis::Horizontal) << std::endl;

	sf::Vector2f pos = testGo->GetPosition();
	pos += dir * 100.f * dt;
	testGo->SetPosition(pos);

	if (InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		std::cout << InputMgr::GetMousePosition().x << ", " << InputMgr::GetMousePosition().y << std::endl;
		testGo->SetPosition((sf::Vector2f)InputMgr::GetMousePosition());
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	
}

void SceneDev1::Exit()
{
	Scene::Exit();
}
