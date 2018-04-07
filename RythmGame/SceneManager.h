#pragma once
enum eScene
{
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_LOADING,
	SCENE_GAME,
	SCENE_RESULT,
};
class Scene;
class SceneManager
{
private:
	static SceneManager* _instance;
public:
	static SceneManager* GetInstance();
private:
	SceneManager();
public:
	~SceneManager();
private:
	Scene* _scene;
public:
	void ChangeScene(eScene scene);
	void Update(int deltaTime);
	void Render();
};