#include "GameObjectFactory.hpp"

#include "Background.hpp"
#include "Player.hpp"
#include "SmallShip.hpp"
#include "Bullet.hpp"
#include "Boss.hpp"
#include "TextBox.hpp"
 
// Components 
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Vector3f.hpp"
#include "PhysicsComponent.hpp"
#include "Collider.hpp"

#include "Window.hpp"
#include "Game.hpp"
#include "Renderer.hpp"

#include "TextureManager.hpp"

#include "SDL2_Common.h"

#include <string>

std::shared_ptr<GameObjectFactory> GameObjectFactory::gof = nullptr;

GameObjectFactory::GameObjectFactory()
{
    renderer = nullptr;
    textureManager = nullptr;
}


std::shared_ptr<GameObjectFactory> GameObjectFactory::instance()
{
    if (!gof) 
    {
        gof.reset(new GameObjectFactory());
        gof->init();
    }
    return gof;
}

void GameObjectFactory::init()
{
    renderer = Game::instance()->getRenderer();
    textureManager = TextureManager::instance();
}

GameObjectFactory::~GameObjectFactory()
{
    renderer.reset();
    renderer = nullptr;

    textureManager.reset();
    textureManager = nullptr;
}

std::shared_ptr<Background> GameObjectFactory::createBackground(std::shared_ptr<Vector3f> position)
{
    std::shared_ptr<Background> background = std::shared_ptr<Background>(new Background());

    // Sprite
    std::shared_ptr<Sprite> backgroundSprite = std::shared_ptr<Sprite>(new Sprite());

    // Texture
    std::shared_ptr<Texture> backgroundTexture = std::shared_ptr<Texture>(new Texture());

    backgroundTexture->setTexture(textureManager->findTexture("background"));

    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    
    SDL_QueryTexture(backgroundTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    backgroundTexture->setSourceRectangle(source);

    backgroundSprite->setTexture(backgroundTexture);

    // Setup two way relationship
    backgroundSprite->setGameObject(background);
    background->setSprite(backgroundSprite);

    // Add to engine - registerGameObject()?
    // renderEngine->addSprite(backgroundSprite);

    // Transform
    std::shared_ptr<Transform> backgroundTransform = std::shared_ptr<Transform>(new Transform());
    backgroundTransform->setAngle(0.0f);  
    
    float bgScaleX = Window::WINDOW_WIDTH/(float)source.w;
    float bgScaleY = Window::WINDOW_HEIGHT/(float)source.h;

    backgroundTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(bgScaleX,bgScaleY,0.0f))); 

    backgroundTransform->setPosition(position);
    backgroundTransform->getPosition()->add(std::shared_ptr<Vector3f>(new Vector3f((source.w / 2.0f) * bgScaleX, (source.h / 2.0f) * bgScaleY, 0.0f)));

    background->setTransform(backgroundTransform);

    // Physics
    std::shared_ptr<PhysicsComponent> physics = std::shared_ptr<PhysicsComponent>(new PhysicsComponent());
    physics->setVelocity(std::shared_ptr<Vector3f>(new Vector3f(0.0f, 0.0f, 0.0f)));

    // setup two way relationship
    physics->setGameObject(background);
    background->setPhysicsComponent(physics);

    background->enable();

    Game::instance()->registerGameObject(background);

    return background;
}

/* Note: Fixed scaling on this one :-) */
std::shared_ptr<Player> GameObjectFactory::createPlayer()
{
    const float SCALE = 1.0f;
    
    std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player());
    player->init(MAX_BULLETS);

    // Sprite
    std::shared_ptr<Sprite> playerSprite = std::shared_ptr<Sprite>(new Sprite());

    // Texture
    std::shared_ptr<Texture> playerTexture = std::shared_ptr<Texture>(new Texture());

    playerTexture->setTexture(textureManager->findTexture("player"));

    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    
    SDL_QueryTexture(playerTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    playerTexture->setSourceRectangle(source);
    playerTexture->setAngleOffset(90.0f);

    playerSprite->setTexture(playerTexture);
    
    // Setup two way relationship
    player->setSprite(playerSprite);
    playerSprite->setGameObject(player);

    // Transform
    std::shared_ptr<Transform> playerTransform = std::shared_ptr<Transform>(new Transform());
    playerTransform->setAngle(0.0f);
    playerTransform->setPosition(std::shared_ptr<Vector3f>(new Vector3f(100.0f,100.0f,0.0f)));  

    playerTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(SCALE, SCALE,0.0f)));

    player->setTransform(playerTransform);

    // Physics
    std::shared_ptr<PhysicsComponent> physics = std::shared_ptr<PhysicsComponent>(new PhysicsComponent());
    physics->setVelocity(std::shared_ptr<Vector3f>(new Vector3f(1.0f,1.0f,0.0f)));
    
    // setup two way relationship
    physics->setGameObject(player);
    player->setPhysicsComponent(physics);

    // Collider
    std::shared_ptr<Collider> collider = std::shared_ptr<Collider>(new Collider());
    collider->setRadius(playerTexture->getSourceRectangle().w/2.0f * SCALE);
    collider->setResolution(true);

    // setup two way relationship
    collider->setGameObject(player);
    player->setCollisionComponent(collider);

    player->enable();

    Game::instance()->registerGameObject(player);

    return player;
}

std::shared_ptr<SmallShip> GameObjectFactory::createSmallShip(std::shared_ptr<Vector3f> position)
{
    const float SCALE = 2.0f;
    
    std::shared_ptr<SmallShip> smallShip = std::shared_ptr<SmallShip>(new SmallShip());

    // Sprite
    std::shared_ptr<Sprite> smallShipSprite = std::shared_ptr<Sprite>(new Sprite());

    // Texture
    std::shared_ptr<Texture> smallShipTexture = std::shared_ptr<Texture>(new Texture());

    smallShipTexture->setTexture(textureManager->findTexture("smallShip"));

    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    
    SDL_QueryTexture(smallShipTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    smallShipTexture->setSourceRectangle(source);

    smallShipSprite->setTexture(smallShipTexture);
    
    // Setup two way relationship
    smallShip->setSprite(smallShipSprite);
    smallShipSprite->setGameObject(smallShip);

    // Transform
    std::shared_ptr<Transform> smallShipTransform = std::shared_ptr<Transform>(new Transform());
    smallShipTransform->setAngle(0.0f);

   // std::shared_ptr<Vector3f> offscreen = std::shared_ptr<Vector3f>(new Vector3f(0.0f,0.0f,0.0f));

    float w = Window::WINDOW_WIDTH;
    float h = Window::WINDOW_HEIGHT;

    // Make this a random offscreen position
    //offscreen->setX(w-500.0f);
    //offscreen->setY(h/2.0f);
    
    smallShipTransform->setPosition(position);

    smallShipTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(SCALE, SCALE,0.0f)));

    smallShip->setTransform(smallShipTransform);

    // Physics
    std::shared_ptr<PhysicsComponent> physics = std::shared_ptr<PhysicsComponent>(new PhysicsComponent());
    physics->setVelocity(std::shared_ptr<Vector3f>(new Vector3f(1.0f,1.0f,0.0f)));
    
    // setup two way relationship
    physics->setGameObject(smallShip);
    smallShip->setPhysicsComponent(physics);

    // Collider
    std::shared_ptr<Collider> collider = std::shared_ptr<Collider>(new Collider());
    collider->setRadius((smallShipTexture->getSourceRectangle().w / SCALE));
    collider->setResolution(true);

    // setup two way relationship
    collider->setGameObject(smallShip);
    smallShip->setCollisionComponent(collider);

    Game::instance()->registerGameObject(smallShip);

    return smallShip;
}

std::shared_ptr<Bullet> GameObjectFactory::createBullet(std::string name)
{
    const float SCALE = 1.0f;
    
    std::shared_ptr<Bullet> bullet = std::shared_ptr<Bullet>(new Bullet());

    // Sprite
    std::shared_ptr<Sprite> bulletSprite = std::shared_ptr<Sprite>(new Sprite());

    // Texture
    std::shared_ptr<Texture> bulletTexture = std::shared_ptr<Texture>(new Texture());
    
    // This mess loads a texture .. make this better. 

    bulletTexture->setTexture(textureManager->findTexture("greenBullet"));

    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    
    SDL_QueryTexture(bulletTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    bulletTexture->setSourceRectangle(source);
   // bulletTexture->setAngleOffset(90.0f);

    bulletSprite->setTexture(bulletTexture);
    
    // Setup two way relationship
    bullet->setSprite(bulletSprite);
    bulletSprite->setGameObject(bullet);

    // Transform
    std::shared_ptr<Transform> bulletTransform = std::shared_ptr<Transform>(new Transform());
    bulletTransform->setAngle(0.0f);

    std::shared_ptr<Vector3f> offscreen = std::shared_ptr<Vector3f>(new Vector3f(0.0f,0.0f,0.0f));

    float w = Window::WINDOW_WIDTH;
    float h = Window::WINDOW_HEIGHT;

    // Make this a random offscreen position
    offscreen->setX(w+10.0f);
    offscreen->setY(h/2.0f);
    
    bulletTransform->setPosition(offscreen);  

    bulletTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(SCALE, SCALE,0.0f)));

    bullet->setTransform(bulletTransform);

    // Physics
    std::shared_ptr<PhysicsComponent> physics = std::shared_ptr<PhysicsComponent>(new PhysicsComponent());
    physics->setVelocity(std::shared_ptr<Vector3f>(new Vector3f(1.0f,1.0f,0.0f)));
    
    // setup two way relationship
    physics->setGameObject(bullet);
    bullet->setPhysicsComponent(physics);

    // Collider
    std::shared_ptr<Collider> collider = std::shared_ptr<Collider>(new Collider());
    collider->setRadius(bulletTexture->getSourceRectangle().w/2.0f * SCALE);
    collider->setResolution(false);

    // setup two way relationship
    collider->setGameObject(bullet);
    bullet->setCollisionComponent(collider);

    bullet->setName(name);

    bullet->enable();

    Game::instance()->registerGameObject(bullet);

    return bullet;
}

std::shared_ptr<Boss> GameObjectFactory::createBoss()
{
    const float SCALE = 1.0f;

    std::shared_ptr<Boss> boss = std::shared_ptr<Boss>(new Boss());

    // Sprite
    std::shared_ptr<Sprite> bossSprite = std::shared_ptr<Sprite>(new Sprite());

    // Texture
    std::shared_ptr<Texture> bossTexture = std::shared_ptr<Texture>(new Texture());

    bossTexture->setTexture(textureManager->findTexture("boss"));

    SDL_Rect source;
    source.x = 0;
    source.y = 0;

    SDL_QueryTexture(bossTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    bossTexture->setSourceRectangle(source);

    bossSprite->setTexture(bossTexture);

    // Setup two way relationship
    boss->setSprite(bossSprite);
    bossSprite->setGameObject(boss);

    // Transform
    std::shared_ptr<Transform> bossTransform = std::shared_ptr<Transform>(new Transform());
    bossTransform->setAngle(0.0f);

    std::shared_ptr<Vector3f> offscreen = std::shared_ptr<Vector3f>(new Vector3f(0.0f,0.0f,0.0f));

    float w = Window::WINDOW_WIDTH;
    float h = Window::WINDOW_HEIGHT;

    // Make this a random offscreen position
    offscreen->setX(w);
    offscreen->setY(h/2.0f);

    bossTransform->setPosition(offscreen);

    bossTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(SCALE, SCALE, 0.0f)));

    boss->setTransform(bossTransform);

    // Physics
    std::shared_ptr<PhysicsComponent> physics = std::shared_ptr<PhysicsComponent>(new PhysicsComponent());
    physics->setVelocity(std::shared_ptr<Vector3f>(new Vector3f(-1.0f, 0.0f, 0.0f)));

    // setup two way relationship
    physics->setGameObject(boss);
    boss->setPhysicsComponent(physics);

    // Collider
    std::shared_ptr<Collider> collider = std::shared_ptr<Collider>(new Collider());
    collider->setRadius(bossTexture->getSourceRectangle().w / 2.0f * SCALE);
    collider->setResolution(true);

    // setup two way relationship
    collider->setGameObject(boss);
    boss->setCollisionComponent(collider);

    Game::instance()->registerGameObject(boss);

    boss->disable();

    return boss;
}

std::shared_ptr<TextBox> GameObjectFactory::createTextBox(std::string message, std::shared_ptr<Vector3f> position, SDL_Renderer* renderer)
{
    std::shared_ptr<TextBox> textBox = std::shared_ptr<TextBox>(new TextBox());

    // Sprite
    std::shared_ptr<Sprite> textBoxSprite = std::shared_ptr<Sprite>(new Sprite());

    // Texture
    std::shared_ptr<Texture> textBoxTexture = std::shared_ptr<Texture>(new Texture());

    float textScale = Window::WINDOW_WIDTH * 0.02083333333f;
    
    TTF_Font* sans = TTF_OpenFont("assets/fonts/SansSerifCollection.ttf", textScale);

    SDL_Color white = { 255, 255, 255 };

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sans, message.c_str(), white);

    // now you can convert it into a texture
    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    textBoxTexture->setTexture(messageTexture);

    SDL_Rect message_rect;
    message_rect.x = 0;
    message_rect.y = 0;
    message_rect.w = 100;
    message_rect.h = 100;

    SDL_QueryTexture(textBoxTexture->getTexture(), NULL, NULL, &message_rect.w, &message_rect.h);
    textBoxTexture->setSourceRectangle(message_rect);

    textBoxSprite->setTexture(textBoxTexture);

    // Setup two way relationship
    textBox->setSprite(textBoxSprite);
    textBoxSprite->setGameObject(textBox);

    // Transform
    std::shared_ptr<Transform> textBoxTransform = std::shared_ptr<Transform>(new Transform());
    textBoxTransform->setAngle(0.0f);

    textBoxTransform->setPosition(position);

    textBoxTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(1.0f, 1.0f, 0.0f)));

    textBox->setTransform(textBoxTransform);

    Game::instance()->registerGameObject(textBox);

    textBox->enable();

    return textBox;
}
