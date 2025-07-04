#include "stdafx.h"
#include "Bat.h"

Bat::Bat(const std::string& name)
	: GameObject(name)
{
}

void Bat::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);

	shape.setPosition(pos);
}

void Bat::SetRotation(float rot)
{
	GameObject::SetRotation(rot);

	shape.setRotation(rot);
}

void Bat::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);

	shape.setScale(s);
}

void Bat::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	shape.setOrigin(o);
}

void Bat::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(shape, preset);
	}
}

void Bat::Init()
{
	if (SCENE_MGR.GetStartSceneId() == SceneIds::Game)
	{
		shape.setSize({ 100.f, 5.f });
		shape.setFillColor(sf::Color::White);
		SetOrigin(Origins::TC);
	}
	else if (SCENE_MGR.GetStartSceneId() == SceneIds::DuoGame)
	{
		shape.setSize({ 5.f, 100.f });
		shape.setFillColor(sf::Color::White);
		SetOrigin(Origins::ML);
	}
}

void Bat::Release()
{
}

void Bat::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
	{
		SetPosition({ bounds.width * 0.5f, bounds.height - 20.f });

		sf::Vector2f size = shape.getSize();
		minX = bounds.left + size.x * 0.5f; //왼쪽 경계 검사
		maxX = (bounds.left + bounds.width) - size.x * 0.5f; //오른쪽 경계 검사
	}
	else if (SCENE_MGR.GetCurrentSceneId() == SceneIds::DuoGame)
	{
		if (side == Sides::Left)
		{
			SetPosition({ 20.f, bounds.height* 0.5f });

			sf::Vector2f size = shape.getSize();
			minY = bounds.top + size.y * 0.5f; //위쪽 경계 검사
			maxY = (bounds.top + bounds.height) - size.y * 0.5f; //아래쪽 경계 검사
		}
		else if (side == Sides::Right)
		{
			SetPosition({ bounds.width - 20.f, bounds.height * 0.5f });

			sf::Vector2f size = shape.getSize();
			minY = bounds.top + size.y * 0.5f; //위쪽 경계 검사
			maxY = (bounds.top + bounds.height) - size.y * 0.5f; //아래쪽 경계 검사
		}
	}
}

void Bat::Update(float dt)
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
	{
		direction.x = InputMgr::GetAxis(Axis::Horizontal);
		sf::Vector2f pos = GetPosition() + direction * speed * dt;
		pos.x = Utils::Clamp(pos.x, minX, maxX);
		SetPosition(pos);
	}
	else if (SCENE_MGR.GetCurrentSceneId() == SceneIds::DuoGame)
	{
		direction.y = InputMgr::GetAxis(Axis::Vertical);
		sf::Vector2f pos = GetPosition() + direction * speed * dt;
		pos.y = Utils::Clamp(pos.x, minX, maxX);
		SetPosition(pos);
	}
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
