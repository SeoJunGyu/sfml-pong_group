#include "stdafx.h"
#include "InputMgr.h"

std::list<int> InputMgr::downKeys;
std::list<int> InputMgr::heldKeys;
std::list<int> InputMgr::upKeys;

//키 초기화
std::unordered_map<Axis, AxisInfo> InputMgr::axisInfoMap;

sf::Vector2i InputMgr::mousePosition;

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
			//키 카운트와 마우스 열거형을 더한 새로운 인덱스값을 마우스 버튼으로 인식한다.
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

		float raw = GetAxisRaw(axisInfo.axis); //축값 -1 0 1 중 하나가 반환되어 저장된다.
		float dir = raw; //dir과 raw는 다른 용도다. / raw : 축값 , dir : 반환될 축값
		if (raw == 0.f && axisInfo.value != 0.f)
		{
			//raw == 0.f -> 아무것도 안눌린경우 / 안눌렸는데 값이 0으로 안바뀐경우다. => 즉, 0으로 만들어야한다.
			dir = axisInfo.value > 0.f ? -1.f : 1.f; //빼거나 더해서 0으로 만들어야한다.
		}

		//방향 * 속도 * 프레임간 시간 => 이동
		//value -> 최소 : -1 , 최대 : 1
		axisInfo.value += dir * axisInfo.sensi * dt; //-1 0 1에따라 방향과 속도가 달라진다.
		axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f); //-1 ~ 1 초과 미만을 못넘어가게 제한을 걸었다.

		//0으로 돌리려면 -1에 가까워지거나 1에 가까워지는 등 왔다갔다 하는 경우가 있다 -> 0 근처면 0으로 바꾸는 작업을 해야한다.
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

//축 값이 바로 -1 0 1이 바로 입력될때 사용
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
		int code = *it; //지금 순회하고있는 iterator의 값
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

//축 값까지 점진적으로 증가하는것을 실행하기위해 사용
//업데이트에서 계산된 값이 반환되는 것이다.
float InputMgr::GetAxis(Axis axis)
{
	auto findIt = axisInfoMap.find(axis); //축을 키로 해당 키의 구조체 axisinfo 반환
	if (findIt == axisInfoMap.end())
	{
		//키값이 없을 경우
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

