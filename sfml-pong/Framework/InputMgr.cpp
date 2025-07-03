#include "stdafx.h"
#include "InputMgr.h"

std::list<sf::Keyboard::Key> InputMgr::downKeys;
std::list<sf::Keyboard::Key> InputMgr::heldKeys;
std::list<sf::Keyboard::Key> InputMgr::upKeys;

// 0: �ȴ��� , 1 : �� ������ , 2 ; ������ ���� , 3 : �� ��
std::vector<int> InputMgr::mouseButtonCondition(sf::Mouse::ButtonCount, 0);

//Ű �ʱ�ȭ
std::unordered_map<Axis, AxisInfo> InputMgr::axisInfoMap;

void InputMgr::Init()
{
	// ������ Ű �Ҵ�
	AxisInfo infoH;
	infoH.axis = Axis::Horizontal;
	infoH.positivies.push_back(sf::Keyboard::Right);
	infoH.positivies.push_back(sf::Keyboard::D);
	infoH.negativies.push_back(sf::Keyboard::Left);
	infoH.negativies.push_back(sf::Keyboard::A);
	axisInfoMap.insert({ Axis::Horizontal, infoH });

	// ������ Ű �Ҵ�
	AxisInfo infoV;
	infoV.axis = Axis::Vertical;
	infoV.positivies.push_back(sf::Keyboard::Down);
	infoV.positivies.push_back(sf::Keyboard::S);
	infoV.negativies.push_back(sf::Keyboard::Up);
	infoV.negativies.push_back(sf::Keyboard::W);
	axisInfoMap.insert({ Axis::Vertical, infoV });

	std::fill(mouseButtonCondition.begin(), mouseButtonCondition.end(), 0); //0���� �ʱ�ȭ
}

void InputMgr::Clear() 
{
	downKeys.clear();
	upKeys.clear();

	for (int& condition : mouseButtonCondition)
	{
		if (condition == 1)
		{
			condition = 2;
		}
		
		if (condition == 3)
		{
			condition = 0;
		}
	}
}

void InputMgr::UpdateEvent(const sf::Event& ev) 
{
	switch (ev.type)
	{
		case sf::Event::KeyPressed:
			if (!Contains(heldKeys, ev.key.code))
			{
				downKeys.push_back(ev.key.code);
				heldKeys.push_back(ev.key.code);
			}
			break;
		case sf::Event::KeyReleased:
			Remove(heldKeys, ev.key.code);
			upKeys.push_back(ev.key.code);
			break;

		case sf::Event::MouseButtonPressed:
			if (mouseButtonCondition[ev.mouseButton.button] == 0)
			{
				mouseButtonCondition[ev.mouseButton.button] = 1;
			}

			else if (mouseButtonCondition[ev.mouseButton.button] == 1)
			{
				mouseButtonCondition[ev.mouseButton.button] = 2;
			}
			break;

		case sf::Event::MouseButtonReleased:
			mouseButtonCondition[ev.mouseButton.button] = 3;
			break;
	}
}

void InputMgr::Update(float dt) 
{

}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
	return Contains(downKeys, key);
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
	return Contains(upKeys, key);
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
	return Contains(heldKeys, key);
}

bool InputMgr::Contains(const std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key)
{
	return std::find(list.begin(), list.end(), key) != list.end();
}

bool InputMgr::Contains(const std::vector<int>& list, sf::Mouse::Button button, int condition)
{
	return list[button] == condition;
}

void InputMgr::Remove(std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key)
{
	list.remove(key);
}

void InputMgr::Remove(std::vector<int>& list, sf::Mouse::Button button)
{
	list[button] = 0;
}

float InputMgr::GetAxisRaw(Axis axis)
{
	// held Ű���� ���ʿ� �ִ� ���� �޾Ƽ� ���� �ѱ��.
	//Ű�� �Ű������� �Ѱܼ� iterator ������������ ��ȯ
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end()) //Ű�� ���°��
	{
		return 0.f;
	}

	const AxisInfo axisInfo = findIt->second; //�ప ����
	//�̰� �ڿ������� ��ȸ�ؾ��Ѵ�.
	auto it = heldKeys.rbegin(); //rbegin() : ������ ���� iterator(��ġ) ��ȯ �Լ�
	while (it != heldKeys.rend()) //������ ��ȸ
	{
		sf::Keyboard::Key code = *it; //���� ��ȸ�ϰ��ִ� iterator�� ��
		if (Contains(axisInfo.positivies, code)) //Ű������ Ű�� ����ִ��� Ȯ��
		{
			return 1.f;
		}
		if (Contains(axisInfo.negativies, code)) //Ű������ Ű�� ����ִ��� Ȯ��
		{
			return -1.f;
		}
		++it;
	}
	return 0.0f;
}

float InputMgr::GetAxis(Axis axis)
{
	return 0.0f;
}

bool InputMgr::GetMouseButtonDown(sf::Mouse::Button button)
{
	return Contains(mouseButtonCondition, button, 1);
}

bool InputMgr::GetMouseButtonUp(sf::Mouse::Button button)
{
	return Contains(mouseButtonCondition, button, 3);
}

bool InputMgr::GetMouseButton(sf::Mouse::Button button)
{
	return Contains(mouseButtonCondition, button, 2);
}

sf::Vector2i InputMgr::GetMousePosition()
{
	return sf::Mouse::getPosition(FRAMEWORK.GetWindow());
}

