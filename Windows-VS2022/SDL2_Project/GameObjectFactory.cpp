#include "GameObjectFactory.hpp"
#include "Player.hpp"
#include "PhysicsComponent.hpp"
#include "Vector3f.hpp"
#include "NPC.hpp"
#include "PhysicsEngine.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Background.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"

GameObjectFactory::GameObjectFactory()
{
	player = nullptr;
	background = nullptr;
	npc = nullptr;
    renderer = nullptr;
}

GameObjectFactory::~GameObjectFactory()
{
	player.reset();
	player = nullptr;

	background.reset();
	background = nullptr;

    npc.reset();
    npc = nullptr;

    renderer.reset();
    renderer = nullptr;
}

void GameObjectFactory::init()
{
    renderer = Game::instance()->getRenderer();
}

std::shared_ptr<Player> GameObjectFactory::createPlayer()
{
    player = std::shared_ptr<Player>(new Player());

    player->init();

    // PhysicsComponent
    std::shared_ptr<PhysicsComponent> playerPhysicsComponent = std::shared_ptr<PhysicsComponent>(new PhysicsComponent());
    playerPhysicsComponent->setVelocity(std::shared_ptr<Vector3f>(new Vector3f(0.0f, 0.0f, 0.0f)));
    playerPhysicsComponent->setGameObject(player);
    player->setPhysicsComponent(playerPhysicsComponent);


    // Texture
    std::shared_ptr<Texture> playerTexture = std::shared_ptr<Texture>(new Texture());

    SDL_Rect source;

    source.x = 0;
    source.y = 0;

    playerTexture->setTexture(SDL_CreateTextureFromSurface(renderer->getRenderer(), IMG_Load("assets/images/character.png")));

    SDL_QueryTexture(playerTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    playerTexture->setSrcRect(source);

    // Transform
    std::shared_ptr<Transform> playerTransform = std::shared_ptr<Transform>(new Transform());
    playerTransform->setPosition(std::shared_ptr<Vector3f>(new Vector3f(100.0f, -100.0f, 1.0f)));
    playerTransform->setAngle(0.0f);

    float scaleX = 0.5f;
    float scaleY = 0.5f;

    playerTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(scaleX, scaleY, 0.0f)));

    player->setTransform(playerTransform);

    // Sprite
    std::shared_ptr<Sprite> playerSprite = std::shared_ptr<Sprite>(new Sprite());
    playerSprite->setTexture(playerTexture);
    playerSprite->setGameObject(player);
    player->setSprite(playerSprite);

    // Collider
    std::shared_ptr<Collider> collider = std::shared_ptr<Collider>(new Collider());
    collider->setRadius(playerTexture->getSrcRect().w/4.5f);
    collider->setResolution(true);
    collider->setGameObject(player);
    player->setCollider(collider);

    // enable
    player->enable();

    return player;
}

std::shared_ptr<NPC> GameObjectFactory::createNPC()
{
    npc = std::shared_ptr<NPC>(new NPC());

    npc->init();

    // PhysicsComponent
    std::shared_ptr<PhysicsComponent> npcPhysicsComponent = std::shared_ptr<PhysicsComponent>(new PhysicsComponent());
    npcPhysicsComponent->setVelocity(std::shared_ptr<Vector3f>(new Vector3f(0.0f, 0.0f, 0.0f)));
    npcPhysicsComponent->setGameObject(npc);
    npc->setPhysicsComponent(npcPhysicsComponent);


    // Texture
    std::shared_ptr<Texture> npcTexture = std::shared_ptr<Texture>(new Texture());

    SDL_Rect source;

    source.x = 0;
    source.y = 0;

    npcTexture->setTexture(SDL_CreateTextureFromSurface(renderer->getRenderer(), IMG_Load("assets/images/character.png")));

    SDL_QueryTexture(npcTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    npcTexture->setSrcRect(source);

    // Transform
    std::shared_ptr<Transform> npcTransform = std::shared_ptr<Transform>(new Transform());

    std::shared_ptr<Vector3f> offscreen = std::shared_ptr<Vector3f>(new Vector3f(0.0f, 0.0f, 0.0f));

    float w = Window::WINDOW_WIDTH;
    float h = Window::WINDOW_HEIGHT;

    // make random
    offscreen->setX(w + 10.0f);
    offscreen->setY(h/2.0f);

    npcTransform->setPosition(std::shared_ptr<Vector3f>(offscreen));
    npcTransform->setAngle(0.0f);

    float scaleX = 0.5f;
    float scaleY = 0.5f;

    npcTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(scaleX, scaleY, 0.0f)));

    npc->setTransform(npcTransform);

    // Sprite
    std::shared_ptr<Sprite> npcSprite = std::shared_ptr<Sprite>(new Sprite());
    npcSprite->setTexture(npcTexture);
    npcSprite->setGameObject(npc);
    npc->setSprite(npcSprite);

    // Collider
    std::shared_ptr<Collider> collider = std::shared_ptr<Collider>(new Collider());
    collider->setRadius(npcTexture->getSrcRect().w / 4.5f);
    collider->setResolution(true);
    collider->setGameObject(npc);
    npc->setCollider(collider);

    // enable
    npc->enable();

    return npc;
}

std::shared_ptr<Background> GameObjectFactory::createBackground()
{
    background = std::shared_ptr<Background>(new Background());
    
    // Sprite
    std::shared_ptr<Sprite> backgroundSprite = std::shared_ptr<Sprite>(new Sprite());
    backgroundSprite->setGameObject(background);
   
    // Texture
    std::shared_ptr<Texture> backgroundTexture = std::shared_ptr<Texture>(new Texture());
    SDL_Surface* temp = IMG_Load("assets/images/background.png");
    backgroundTexture->setTexture(SDL_CreateTextureFromSurface(renderer->getRenderer(), temp));

    SDL_FreeSurface(temp);
    temp = nullptr;

    background->setSprite(backgroundSprite);

    SDL_Rect source;
    source.x = 0;
    source.y = 0;

    SDL_QueryTexture(backgroundTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    backgroundTexture->setSrcRect(source);

    backgroundSprite->setTexture(backgroundTexture);

    // Transform
    std::shared_ptr<Transform> backgroundTransform = std::shared_ptr<Transform>(new Transform());
    backgroundTransform->setAngle(0.0f);
    backgroundTransform->setPosition(std::shared_ptr<Vector3f>(new Vector3f(0.0f, 0.0f, 0.0f)));

    float bgScaleX = Window::WINDOW_WIDTH / (float)source.w;
    float bgScaleY = Window::WINDOW_HEIGHT / (float)source.h;

    backgroundTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(bgScaleX, bgScaleY, 0.0f)));

    background->setTransform(backgroundTransform);

    // enable
    background->enable();

    return background;
}

std::shared_ptr<Bullet> GameObjectFactory::createBullet()
{
    bullet = std::shared_ptr<Bullet>(new Bullet());

    // PhysicsComponent
    std::shared_ptr<PhysicsComponent> bulletPhysicsComponent = std::shared_ptr<PhysicsComponent>(new PhysicsComponent());
    bulletPhysicsComponent->setVelocity(std::shared_ptr<Vector3f>(new Vector3f(0.0f, 0.0f, 0.0f)));
    bulletPhysicsComponent->setGameObject(bullet);
    bullet->setPhysicsComponent(bulletPhysicsComponent);


    // Texture
    std::shared_ptr<Texture> bulletTexture = std::shared_ptr<Texture>(new Texture());

    SDL_Rect source;

    source.x = 0;
    source.y = 0;

    bulletTexture->setTexture(SDL_CreateTextureFromSurface(renderer->getRenderer(), IMG_Load("assets/images/character.png")));

    SDL_QueryTexture(bulletTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    bulletTexture->setSrcRect(source);

    // Transform
    std::shared_ptr<Transform> bulletTransform = std::shared_ptr<Transform>(new Transform());

    std::shared_ptr<Vector3f> offscreen = std::shared_ptr<Vector3f>(new Vector3f(0.0f, 0.0f, 0.0f));

    float w = Window::WINDOW_WIDTH;
    float h = Window::WINDOW_HEIGHT;

    // make random
    offscreen->setX(w + 10000.0f);
    offscreen->setY(h / 2.0f);

    bulletTransform->setPosition(std::shared_ptr<Vector3f>(offscreen));
    bulletTransform->setAngle(0.0f);

    float scaleX = 0.5f;
    float scaleY = 0.5f;

    bulletTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(scaleX, scaleY, 0.0f)));

    bullet->setTransform(bulletTransform);

    // Sprite
    std::shared_ptr<Sprite> bulletSprite = std::shared_ptr<Sprite>(new Sprite());
    bulletSprite->setTexture(bulletTexture);
    bulletSprite->setGameObject(bullet);
    bullet->setSprite(bulletSprite);

    // Collider
    std::shared_ptr<Collider> collider = std::shared_ptr<Collider>(new Collider());
    collider->setRadius(bulletTexture->getSrcRect().w / 4.5f);
    collider->setResolution(true);
    collider->setGameObject(bullet);
    bullet->setCollider(collider);

    // enable
    bullet->enable();

    return bullet;
}

