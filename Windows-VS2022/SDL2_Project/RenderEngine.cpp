#include "RenderEngine.hpp"

#include "Sprite.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Vector3f.hpp"

#ifdef DEBUG
    #include "Collider.hpp"
#endif

RenderEngine::RenderEngine()
{
    maxObjects = 0;
    renderer = nullptr;
}

RenderEngine::~RenderEngine()
{
    std::vector<std::shared_ptr<Sprite>>::iterator itt;
    for(itt = sprites.begin(); itt != sprites.end(); ++itt)
    {
        (*itt).reset(); // call reset on the shared pointer!
    }
    
    sprites.clear();

    renderer.reset();
    renderer = nullptr;
}

void RenderEngine::init(int maxObjects, std::shared_ptr<Renderer> renderer)
{
    sprites.resize(maxObjects);

    this->renderer = renderer;
}

void RenderEngine::addSprite(std::shared_ptr<Sprite> sprite)
{
    bool added = false;
    std::vector<std::shared_ptr<Sprite>>::iterator itt;
    for(itt = sprites.begin(); itt != sprites.end(); ++itt)
    {
        if(*itt == nullptr)
        {
            *itt = sprite;
            added = true;
            break;
        }
    }

   // if(added == false)
        //std::cout << "Ran out of pre-allocated sprite components" << std::endl;
}

bool RenderEngine::removeSprite(std::shared_ptr<Sprite> sprite)
{
    bool deleted = false;
    std::vector<std::shared_ptr<Sprite>>::iterator itt;
    for(itt = sprites.begin(); itt != sprites.end(); ++itt)
    {
        std::shared_ptr<Sprite> temp = *itt;
        if(temp == sprite)
        {
            sprites.erase(itt);
            // itt - now invalid as we've altered the vector!
            deleted = true;
            break;

            /* To erase all matching*/
            //itt = sprites.erase(itt);
        }
    }

    return deleted;
}

void RenderEngine::render()
{
    // slow?
    SDL_Renderer* gameRenderer = renderer->getRenderer();
    SDL_Rect destination;
    SDL_Rect source;
    SDL_Texture* tex;

    std::shared_ptr<Sprite> sprite;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Transform> transform;
    std::shared_ptr<Vector3f> scale;
    std::shared_ptr<Vector3f> position;
    float angle;

    std::vector<std::shared_ptr<Sprite>>::iterator itt;

    for(itt = sprites.begin(); itt != sprites.end(); ++itt)
    {
        sprite = *itt;

        if(sprite == nullptr)
            continue;

        if(sprite->getGameObject()->isEnabled() == false)
            continue;

        texture = sprite->getTexture();
        source = texture->getSourceRectangle();
        tex = texture->getTexture();

        transform = sprite->getGameObject()->getTransform();
        scale = transform->getScale();
        position = transform->getPosition();


        destination.w = source.w * scale->getX();
        destination.h = source.h * scale->getY();
        destination.x = position->getX() - destination.w / 2.0f;
        destination.y = position->getY() - destination.h / 2.0f;

        angle = transform->getAngle(); // angle of the game object.
        angle += texture->getAngleOffset(); // offset of image in the texture. 


        SDL_RenderCopyEx(gameRenderer, tex, &source, &destination, angle, NULL, SDL_FLIP_NONE);

#ifdef DEBUG
            if (sprite->getGameObject()->getCollisionComponent() != nullptr)
                drawCircle(position->getX(), position->getY(), sprite->getGameObject()->getCollisionComponent()->getRadius());
#endif
    }
}

void RenderEngine::drawCircle(int centerX, int centerY, int radius)
{
    SDL_Renderer* renderer = this->renderer->getRenderer();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    const int segments = 36; // Increase for a smoother circle
    float step = 2.0f * M_PI / segments;

    for (int i = 0; i < segments; i++) {
        float angle1 = i * step;
        float angle2 = (i + 1) * step;

        int x1 = centerX + (int)(cos(angle1) * radius);
        int y1 = centerY + (int)(sin(angle1) * radius);
        int x2 = centerX + (int)(cos(angle2) * radius);
        int y2 = centerY + (int)(sin(angle2) * radius);

        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}