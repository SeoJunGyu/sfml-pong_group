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
		//Ȱ��ȭ �� ������Ʈ�� ������Ʈ ����
		if (obj->GetActive())
		{
			obj->Update(dt);
		}

		obj->Update(dt);
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	// 1�� - sorting
	std::list<GameObject*> sortedObjects(gameObjects);

	//�Լ� ��ü ���
	//DrawOrderComparer -> �ӽð�ü�� ���� �Ű������� �����ϴ� ���̴�.
	sortedObjects.sort(DrawOrderComparer());

	for (auto obj : sortedObjects)
	{
		//Ȱ��ȭ �� ������Ʈ�� ��ο� ����
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}

	// �߰��� ������Ʈ �˻� �� �迭�� �߰�
	for (GameObject* go : objectsToAdd)
	{
		//�ߺ� �˻� �� ������ �߰�
		if (std::find(gameObjects.begin(), gameObjects.end(), go) == gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	objectsToAdd.clear(); //�̰� ���ϸ� ���� �����ӿ� �� ��� �ݺ��Ѵ�.

	// ������ ���� �ۿ�
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
	go->SetActive(false); //������Ʈ �ǰų� ��ο� ���ϰ� ��Ȱ��ȭ

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
