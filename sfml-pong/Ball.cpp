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
	minX = bounds.left + radius; //왼쪽 경계 검사
	maxX = (bounds.left + bounds.width) - radius; //오른쪽 경계 검사

	minY = bounds.top + radius * 2.f;
	maxY = bounds.top + bounds.height + 200.f; // 바닥 이후 200까지 가라는 뜻

	//첫 시작시 공은 정지
	direction = { 0.f, 0.f }; 
	speed = 0.f;
}

void Ball::Update(float dt)
{
	sf::Vector2f pos = GetPosition() + direction * speed * dt;

	if (pos.x < minX)
	{
		// 좌측 충돌
		pos.x = minX;
		direction.x *= -1.f;
	}
	else if (pos.x > maxX)
	{
		// 우측 충돌
		pos.x = maxX;
		direction.x *= -1.f;
	}

	if (pos.y < minY)
	{
		// 화면 상단 충돌
		pos.y = minY;
		direction.y *= -1.f;
	}
	else if (pos.y > maxY)
	{
		// 바닥쪽 충돌 / 주석은 바닥도 튕기게 하는 것이다.
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
		// 배트 충돌
		const sf::FloatRect& batBounds = bat->GetGlobalBounds();

		//intersects(floatRect) : 두 박스의 충돌 검사 함수
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

