#include "stdafx.h"
#include "InputMgr.h"

std::list<sf::Keyboard::Key> InputMgr::downKeys;
std::list<sf::Keyboard::Key> InputMgr::heldKeys;
std::list<sf::Keyboard::Key> InputMgr::upKeys;

// 0: 안눌림 , 1 : 막 눌렀음 , 2 ; 누르고 있음 , 3 : 막 뗌
std::vector<int> InputMgr::mouseButtonCondition(sf::Mouse::ButtonCount, 0);

//키 초기화
std::unordered_map<Axis, AxisInfo> InputMgr::axisInfoMap;

void InputMgr::Init()
{
	// 가로축 키 할당
	AxisInfo infoH;
	infoH.axis = Axis::Horizontal;
	infoH.positivies.push_back(sf::Keyboard::Right);
	infoH.positivies.push_back(sf::Keyboard::D);
	infoH.negativies.push_back(sf::Keyboard::Left);
	infoH.negativies.push_back(sf::Keyboard::A);
	axisInfoMap.insert({ Axis::Horizontal, infoH });

	// 세로축 키 할당
	AxisInfo infoV;
	infoV.axis = Axis::Vertical;
	infoV.positivies.push_back(sf::Keyboard::Down);
	infoV.positivies.push_back(sf::Keyboard::S);
	infoV.negativies.push_back(sf::Keyboard::Up);
	infoV.negativies.push_back(sf::Keyboard::W);
	axisInfoMap.insert({ Axis::Vertical, infoV });

	std::fill(mouseButtonCondition.begin(), mouseButtonCondition.end(), 0); //0으로 초기화
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
	// held 키에서 뒤쪽에 있는 값을 받아서 값을 넘긴다.
	//키를 매개변수로 넘겨서 iterator 데이터형으로 반환
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end()) //키가 없는경우
	{
		return 0.f;
	}

	const AxisInfo axisInfo = findIt->second; //축값 저장
	//이걸 뒤에서부터 순회해야한다.
	auto it = heldKeys.rbegin(); //rbegin() : 역방향 시작 iterator(위치) 반환 함수
	while (it != heldKeys.rend()) //역방향 순회
	{
		sf::Keyboard::Key code = *it; //지금 순회하고있는 iterator의 값
		if (Contains(axisInfo.positivies, code)) //키보드의 키가 들어있는지 확인
		{
			return 1.f;
		}
		if (Contains(axisInfo.negativies, code)) //키보드의 키가 들어있는지 확인
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

