#include "stdafx.h"
#include "InputMgr.h"

std::list<int> InputMgr::downKeys;
std::list<int> InputMgr::heldKeys;
std::list<int> InputMgr::upKeys;

//Ű �ʱ�ȭ
std::unordered_map<Axis, AxisInfo> InputMgr::axisInfoMap;

sf::Vector2i InputMgr::mousePosition;

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
}

void InputMgr::Clear() 
{
	downKeys.clear();
	upKeys.clear();
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
			//Ű ī��Ʈ�� ���콺 �������� ���� ���ο� �ε������� ���콺 ��ư���� �ν��Ѵ�.
			if (!Contains(heldKeys, sf::Keyboard::KeyCount + ev.mouseButton.button))
			{
				downKeys.push_back(sf::Keyboard::KeyCount + ev.mouseButton.button);
				heldKeys.push_back(sf::Keyboard::KeyCount + ev.mouseButton.button);
			}
			
			break;

		case sf::Event::MouseButtonReleased:
			Remove(heldKeys, sf::Keyboard::KeyCount + ev.mouseButton.button);
			upKeys.push_back(sf::Keyboard::KeyCount + ev.mouseButton.button);
			break;
	}
}

void InputMgr::Update(float dt) 
{
	mousePosition = sf::Mouse::getPosition(FRAMEWORK.GetWindow());

	for (auto& pair : axisInfoMap)
	{
		AxisInfo& axisInfo = pair.second;

		float raw = GetAxisRaw(axisInfo.axis); //�ప -1 0 1 �� �ϳ��� ��ȯ�Ǿ� ����ȴ�.
		float dir = raw; //dir�� raw�� �ٸ� �뵵��. / raw : �ప , dir : ��ȯ�� �ప
		if (raw == 0.f && axisInfo.value != 0.f)
		{
			//raw == 0.f -> �ƹ��͵� �ȴ������ / �ȴ��ȴµ� ���� 0���� �ȹٲ����. => ��, 0���� �������Ѵ�.
			dir = axisInfo.value > 0.f ? -1.f : 1.f; //���ų� ���ؼ� 0���� �������Ѵ�.
		}

		//���� * �ӵ� * �����Ӱ� �ð� => �̵�
		//value -> �ּ� : -1 , �ִ� : 1
		axisInfo.value += dir * axisInfo.sensi * dt; //-1 0 1������ ����� �ӵ��� �޶�����.
		axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f); //-1 ~ 1 �ʰ� �̸��� ���Ѿ�� ������ �ɾ���.

		//0���� �������� -1�� ��������ų� 1�� ��������� �� �Դٰ��� �ϴ� ��찡 �ִ� -> 0 ��ó�� 0���� �ٲٴ� �۾��� �ؾ��Ѵ�.
		float stopThreshold = std::abs(dir * axisInfo.sensi * dt);
		if (raw == 0.f && std::abs(axisInfo.value) < stopThreshold)
		{
			axisInfo.value = 0.f;
		}
	}
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

bool InputMgr::Contains(const std::list<int>& list, int key)
{
	return std::find(list.begin(), list.end(), key) != list.end();
}

void InputMgr::Remove(std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key)
{
	list.remove(key);
}

void InputMgr::Remove(std::list<int>& list, int key)
{
	list.remove(key);
}

//�� ���� �ٷ� -1 0 1�� �ٷ� �Էµɶ� ���
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
		int code = *it; //���� ��ȸ�ϰ��ִ� iterator�� ��
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

//�� ������ ���������� �����ϴ°��� �����ϱ����� ���
//������Ʈ���� ���� ���� ��ȯ�Ǵ� ���̴�.
float InputMgr::GetAxis(Axis axis)
{
	auto findIt = axisInfoMap.find(axis); //���� Ű�� �ش� Ű�� ����ü axisinfo ��ȯ
	if (findIt == axisInfoMap.end())
	{
		//Ű���� ���� ���
		return 0.0f;
	}

	return findIt->second.value;
}

bool InputMgr::GetMouseButtonDown(sf::Mouse::Button button)
{
	return Contains(downKeys, sf::Keyboard::KeyCount + button);
}

bool InputMgr::GetMouseButtonUp(sf::Mouse::Button button)
{
	return Contains(upKeys, sf::Keyboard::KeyCount + button);
}

bool InputMgr::GetMouseButton(sf::Mouse::Button button)
{
	return Contains(heldKeys, sf::Keyboard::KeyCount + button);
}

sf::Vector2i InputMgr::GetMousePosition()
{
	return mousePosition;
}

