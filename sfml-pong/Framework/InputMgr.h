#pragma once

enum class Axis
{
	Horizontal, //���� �Է�
	Vertical, //���� �Է�
};

//�� ���� ����ü
struct AxisInfo
{
	Axis axis; //�� ����
	std::list<int> positivies; // 1.f -> ��� ��� ����Ʈ��.
	std::list<int> negativies; // -1.f -> ���� ��� ����Ʈ��.

	float sensi = 10.f; //�� ���� �ӵ� - ������ ������ ���ϰ� ũ�� ������ ���Ѵ�.
	float value = 0.f; //��ǻ� �� ���� ��ȯ�ϴ� ���̴�.
};

class InputMgr
{
private:
	static std::list<int> downKeys;
	static std::list<int> heldKeys;
	static std::list<int> upKeys;

	//Ű�� Ű�� ���� ���̴�.
	static std::unordered_map<Axis, AxisInfo> axisInfoMap;
	static sf::Vector2i mousePosition; //���콺 ��ǥ ����

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

	//�� ��������
	static float GetAxisRaw(Axis axis); //�ش� ���� -1 0 1 ��ȯ
	static float GetAxis(Axis axis); //-1 ~ 1 ������ ���� sensi�� �ӵ���ŭ ���������� �ٲ�°����� ��ȯ

	static bool GetMouseButtonDown(sf::Mouse::Button button);
	static bool GetMouseButtonUp(sf::Mouse::Button button);
	static bool GetMouseButton(sf::Mouse::Button button);

	static sf::Vector2i GetMousePosition(); //���콺 ��ǥ ��ȯ
};

