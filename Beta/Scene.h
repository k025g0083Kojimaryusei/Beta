#pragma once

enum class SceneType
{
	Title,
	Play,
	Credit,
	Ranking
};

class Scene
{
public:
	virtual ~Scene() {}
	virtual void Update(char* keys, char* preKeys) = 0;
	virtual void Draw() = 0;
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void ChangeScene(SceneType newType);
	void UpdateCurrentScene(char* keys, char* preKeys);
	void DrawCurrentScene();

	SceneType GetCurrentSceneType() const { return currentType; }

private:
	Scene* currentScene;
	SceneType currentType;
};


