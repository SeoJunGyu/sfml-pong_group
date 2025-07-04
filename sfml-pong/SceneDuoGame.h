#pragma once
#include "Scene.h"

class Bat;
class Ball;

class SceneDuoGame :
    public Scene
{
protected:
    Bat* bat = nullptr;
    Ball* ball = nullptr;

    bool ballActive = false;

public:
    SceneDuoGame();
    ~SceneDuoGame() override = default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;

    void SetGameOver();
};

