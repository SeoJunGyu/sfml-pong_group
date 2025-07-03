#pragma once
#include "Scene.h"
class SceneDev1 : public Scene
{
protected:

public:
	SceneDev1();

	void Init() override;
	void Update(float dt) override;
};

