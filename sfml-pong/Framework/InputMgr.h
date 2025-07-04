#pragma once

enum class Axis
{
	Horizontal, //가로 입력
	Vertical, //세로 입력
};

//축 정보 구조체
struct AxisInfo
{
	Axis axis; //축 저장
	std::list<int> positivies; // 1.f -> 양수 출력 리스트다.
	std::list<int> negativies; // -1.f -> 음수 출력 리스트다.

	float sensi = 10.f; //값 증가 속도 - 작으면 느리게 변하고 크면 빠르게 변한다.
	float value = 0.f; //사실상 이 값을 반환하는 것이다.
};

class InputMgr
{
private:
	static std::list<int> downKeys;
	static std::list<int> heldKeys;
	static std::list<int> upKeys;

	//키와 키에 따른 값이다.
	static std::unordered_map<Axis, AxisInfo> axisInfoMap;
	static sf::Vector2i mousePosition; //마우스 좌표 저장

public:
	static void Init();
	static void Clear();

	static void UpdateEvent(const sf::Event& ev);
	static void Update(float dt);

	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);

	static bool Contains(const std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key);
	static bool Contains(const std::list<int>& list, int key);
	static void Remove(std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key);
	static void Remove(std::list<int>& list, int key);

	//축 가져오기
	static float GetAxisRaw(Axis axis); //해당 축의 -1 0 1 반환
	static float GetAxis(Axis axis); //-1 ~ 1 까지의 값이 sensi의 속도만큼 점진적으로 바뀌는값으로 반환

	static bool GetMouseButtonDown(sf::Mouse::Button button);
	static bool GetMouseButtonUp(sf::Mouse::Button button);
	static bool GetMouseButton(sf::Mouse::Button button);

	static sf::Vector2i GetMousePosition(); //마우스 좌표 반환
};

