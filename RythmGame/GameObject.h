#pragma once
class GameObject
{
private:
public:
	GameObject();
	~GameObject();

	virtual void Init() = 0;
	virtual void Dinit() = 0;
	virtual void Update(int deltaTime) = 0;
	virtual void Render() = 0;
};