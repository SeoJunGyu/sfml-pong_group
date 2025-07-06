#pragma once
#include "Scene.h"

class Bat;
class Ball;
class UiHud;

class SceneDuoGame :
    public Scene
{
protected:
    Bat* bat1 = nullptr;
    Bat* bat2 = nullptr;
    Ball* ball = nullptr;
    UiHud* uiHud = nullptr;

    bool ballActive = false;

    int score1 = 0;
    int score2 = 0;

public:
    SceneDuoGame();
    ~SceneDuoGame() override = default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;

    void SetGameOver();
};

