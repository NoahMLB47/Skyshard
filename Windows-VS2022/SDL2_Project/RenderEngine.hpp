#pragma once
#include "SDL2_Common.h"
#include <memory>
#include <vector>

class Sprite;
class Renderer;

class RenderEngine {

private:
	int maxObjects;
	std::vector<std::shared_ptr<Sprite>> sprites;
	std::shared_ptr<Renderer> renderer;

public:
	RenderEngine();
	~RenderEngine();

	void addSprite(std::shared_ptr<Sprite> newSprite);
	void render();
	void init(int maxObjects, std::shared_ptr<Renderer> r);
	bool removeSprite(std::shared_ptr<Sprite> oldSprite);
};