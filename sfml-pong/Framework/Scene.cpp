#include "stdafx.h"
#include "Scene.h"

Scene::Scene(SceneIds id)
	: Id(id)
{
}

void Scene::Init()
{
	for (auto obj : gameObjects)
	{
		obj->Init();
	}

	for (auto obj : objectsToAdd)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		obj->Release();
		delete obj;
	}
	gameObjects.clear();
}

void Scene::Enter()
{
	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);
	SOUNDBUFFER_MGR.Load(soundIds);

	for (auto obj : gameObjects)
	{
		obj->Reset();
	}

	for (auto obj : objectsToAdd)
	{
		obj->Reset();
	}
}

void Scene::Exit()
{
	TEXTURE_MGR.Unload(texIds);
	FONT_MGR.Unload(fontIds);
	SOUNDBUFFER_MGR.Unload(soundIds);
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		//활성화 된 오브젝트만 업데이트 진행
		if (obj->GetActive())
		{
			obj->Update(dt);
		}

		obj->Update(dt);
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	// 1차 - sorting
	std::list<GameObject*> sortedObjects(gameObjects);

	//함수 객체 사용
	//DrawOrderComparer -> 임시객체를 만들어서 매개변수로 전달하는 것이다.
	sortedObjects.sort(DrawOrderComparer());

	for (auto obj : sortedObjects)
	{
		//활성화 된 오브젝트만 드로우 진행
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}

	// 추가할 오브젝트 검사 후 배열에 추가
	for (GameObject* go : objectsToAdd)
	{
		//중복 검사 후 없으면 추가
		if (std::find(gameObjects.begin(), gameObjects.end(), go) == gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	objectsToAdd.clear(); //이걸 안하면 다음 프레임에 또 담고를 반복한다.

	// 삭제도 같은 작용
	for (GameObject* go : objectsToRemove)
	{
		gameObjects.remove(go);
	}
	objectsToRemove.clear();

}

GameObject* Scene::AddGameObject(GameObject* go)
{
	objectsToAdd.push_back(go);
	return go;
}

void Scene::RemoveGameObject(GameObject* go)
{
	go->SetActive(false); //업데이트 되거나 드로우 못하게 비활성화

	objectsToRemove.push_back(go);
}

GameObject* Scene::FindGameObject(const std::string& name)
{

	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	return nullptr;
}
