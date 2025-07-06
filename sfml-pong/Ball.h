#pragma once
#include "GameObject.h"

class Bat;
class UiHud;

class Ball :
    public GameObject
{
protected:
    sf::CircleShape shape;
    
    float speed = 500.f;
    sf::Vector2f direction;

    Bat* bat = nullptr;
    Bat* bat1 = nullptr;
    Bat* bat2 = nullptr;
    UiHud* uiHud = nullptr;

    float minX = 0.f;
    float maxX = 0.f;
    float minY = 0.f;
    float maxY = 0.f;

    Sides side = Sides::None;
    bool isDuo = false;

public:
    Ball(const std::string& name = "");
    ~Ball() = default;

    void SetPosition(const sf::Vector2f& pos) override;
    void SetRotation(float rot) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetOrigin(const sf::Vector2f& o) override;
    void SetOrigin(Origins preset) override;

    // GameObject을(를) 통해 상속됨
    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void Fire(const sf::Vector2f& d, float s);
    void SetBat(Bat* bat) { this->bat = bat; }
    void SetBat1(Bat* bat) { this->bat1 = bat; }
    void SetBat2(Bat* bat) { this->bat2 = bat; }
    void SetUiHud(UiHud* uihud) { uiHud = uihud; }

    void SetDuo(bool duo) { isDuo = duo; }
    void SetSide(Sides side) { this->side = side; }
};

