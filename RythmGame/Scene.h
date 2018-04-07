#pragma once
#include "GameObject.h"
class Scene : public GameObject
{
private:
public:
	Scene();
	~Scene();

public:
	virtual void Init();
	virtual void Dinit();
	virtual void Update(int deltaTime);
	virtual void Render();
};