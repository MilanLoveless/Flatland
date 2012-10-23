#pragma once
class Scene
{
public:
	Scene(void);
	virtual void Draw(int *video, int w, int h) = 0;
	virtual void Update() = 0;
	virtual void Load() = 0;
	virtual ~Scene(void);
};

