#include "RenderEngine.hpp"
#include "Sprite.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Vector3f.hpp"

RenderEngine::RenderEngine()
{
	maxObjects = 0;
	renderer = nullptr;
}

RenderEngine::~RenderEngine()
{
	std::vector<std::shared_ptr<Sprite>>::iterator itt;
	for (itt = sprites.begin(); itt != sprites.end(); itt++)
		(*itt).reset(); // call reset on shared pointer
	
	sprites.clear();
}

void RenderEngine::addSprite(std::shared_ptr<Sprite> newSprite)
{
	sprites.push_back(newSprite);
}

void RenderEngine::render()
{
	SDL_Renderer* gameRenderer = renderer->getRenderer();
	SDL_Rect source;
	SDL_Rect destination;
	SDL_Texture* tex;
	float angle;
	std::shared_ptr<Sprite> sprite;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Transform> transform;
	std::shared_ptr<Vector3f> scale;
	std::shared_ptr<Vector3f> position;
	
	std::vector<std::shared_ptr<Sprite>>::iterator itt;
	for (itt = sprites.begin(); itt != sprites.end(); itt++)
	{
		sprite = *itt;

		if (sprite == nullptr)
			continue;

		if (sprite->getGameObject()->isEnabled() == false)
			continue;

		texture = sprite->getTexture();
		transform = sprite->getGameObject()->getTransform();
		tex = texture->getTexture();
		source = texture->getSrcRect();
		angle = transform->getAngle() + texture->getOffset();

		scale = transform->getScale();
		position = transform->getPosition();

		destination.x = position->getX();
		destination.y = position->getY();

		destination.w = source.w * scale->getX();
		destination.h = source.h * scale->getY();

		SDL_RenderCopyEx(gameRenderer, tex, &source, &destination, angle, NULL, SDL_FLIP_NONE);
	}

}

void RenderEngine::init(int maxObjects, std::shared_ptr<Renderer> r)
{
	sprites.resize(maxObjects);
	renderer = r;
}

bool RenderEngine::removeSprite(std::shared_ptr<Sprite> oldSprite)
{
	bool deleted = false;
	std::vector<std::shared_ptr<Sprite>>::iterator itt;
	for (itt = sprites.begin(); itt != sprites.end(); itt++)
	{
		std::shared_ptr<Sprite> temp = *itt;
		if (temp == oldSprite)
		{
			sprites.erase(itt);
			deleted = true;
			// itt - now invalid as we have altered the vector
			break;
		}
	}

	return deleted;
}
