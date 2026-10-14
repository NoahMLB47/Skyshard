#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include "SDL2_Common.h"
#include "GameObject.hpp"
#include <memory>
#include <string>

class Vector3f;

class TextBox : public GameObject {

public:
    TextBox();
    ~TextBox();

    void update();
    void handleCollision(std::shared_ptr<Collider> other);
    void updateMessage(std::string newMessage, SDL_Renderer* renderer);

private:

};

#endif