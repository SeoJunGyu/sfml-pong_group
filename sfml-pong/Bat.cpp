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
	if (!isDuo)
	{
		shape.setSize({ 100.f, 5.f });
		
	}
	else
	{
		shape.setSize({ 5.f, 100.f });
	}

	shape.setFillColor(sf::Color::White);
	SetOrigin(originPreset);
}

void Bat::Release()
{
}

void Bat::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	if (!isDuo)
	{
		SetPosition({ bounds.width * 0.5f, bounds.height - 20.f });

		sf::Vector2f size = shape.getSize();
		minX = bounds.left + size.x * 0.5f; //왼쪽 경계 검사
		maxX = (bounds.left + bounds.width) - size.x * 0.5f; //오른쪽 경계 검사
	}
	else
	{
		if (side == Sides::Left)
		{
			SetPosition({ bounds.left + 20.f, bounds.height * 0.5f });
		}
		else if (side == Sides::Right)
		{
			SetPosition({ bounds.left + bounds.width - 20.f, bounds.height * 0.5f });
		}

		sf::Vector2f size = shape.getSize();
		minY = bounds.top + size.y * 0.5f; //위쪽 경계 검사
		maxY = (bounds.top + bounds.height) - size.y * 0.5f; //아래쪽 경계 검사
	}
}

void Bat::Update(float dt)
{
	if (!isDuo)
	{
		direction.x = InputMgr::GetAxis(Axis::Horizontal);
		sf::Vector2f pos = GetPosition() + direction * speed * dt;
		pos.x = Utils::Clamp(pos.x, minX, maxX);
		SetPosition(pos);
	}
	else
	{
		direction.y = InputMgr::GetAxis(Axis::Vertical);

		if (
			(side == Sides::Left && InputMgr::GetKey(sf::Keyboard::W) && direction.y < 0) ||
			(side == Sides::Left && InputMgr::GetKey(sf::Keyboard::S) && direction.y > 0) ||
			(side == Sides::Right && InputMgr::GetKey(sf::Keyboard::Up) && direction.y < 0) ||
			(side == Sides::Right && InputMgr::GetKey(sf::Keyboard::Down) && direction.y > 0)
			)
		{
			sf::Vector2f pos = GetPosition() + direction * speed * dt;
			pos.y = Utils::Clamp(pos.y, minY, maxY);
			SetPosition(pos);
		}
	}
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
