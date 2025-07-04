#include "stdafx.h"
#include "Ball.h"
#include "Bat.h"
#include "SceneGame.h"

Ball::Ball(const std::string& name)
	: GameObject(name)
{
}

void Ball::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);

	shape.setPosition(pos);
}

void Ball::SetRotation(float rot)
{
	GameObject::SetRotation(rot);

	shape.setRotation(rot);
}

void Ball::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);

	shape.setScale(s);
}

void Ball::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	shape.setOrigin(o);
}

void Ball::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(shape, preset);
	}
}

void Ball::Init()
{
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::Yellow);
	SetOrigin(Origins::BC);
}

void Ball::Release()
{
}

void Ball::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	SetPosition({ bounds.width * 0.5f, bounds.height - 20.f });

	float radius = shape.getRadius();
	minX = bounds.left + radius; //���� ��� �˻�
	maxX = (bounds.left + bounds.width) - radius; //������ ��� �˻�

	minY = bounds.top + radius * 2.f;
	maxY = bounds.top + bounds.height + 200.f; // �ٴ� ���� 200���� ����� ��

	//ù ���۽� ���� ����
	direction = { 0.f, 0.f }; 
	speed = 0.f;
}

void Ball::Update(float dt)
{
	sf::Vector2f pos = GetPosition() + direction * speed * dt;

	if (pos.x < minX)
	{
		// ���� �浹
		pos.x = minX;
		direction.x *= -1.f;
	}
	else if (pos.x > maxX)
	{
		// ���� �浹
		pos.x = maxX;
		direction.x *= -1.f;
	}

	if (pos.y < minY)
	{
		// ȭ�� ��� �浹
		pos.y = minY;
		direction.y *= -1.f;
	}
	else if (pos.y > maxY)
	{
		// �ٴ��� �浹 / �ּ��� �ٴڵ� ƨ��� �ϴ� ���̴�.
		//pos.y = maxY;
		//direction.y *= -1.f;

		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
		{
			SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrentScene();
			scene->SetGameOver();
		}
	}

	if (bat != nullptr)
	{
		// ��Ʈ �浹
		const sf::FloatRect& batBounds = bat->GetGlobalBounds();

		//intersects(floatRect) : �� �ڽ��� �浹 �˻� �Լ�
		if (shape.getGlobalBounds().intersects(batBounds))
		{
			pos.y = batBounds.top;
			direction.y *= -1.f;
		}
	}

	SetPosition(pos);
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Ball::Fire(const sf::Vector2f& d, float s)
{
	direction = d;
	speed = s;
}

