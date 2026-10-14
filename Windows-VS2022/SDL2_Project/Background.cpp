#include "Background.hpp"

Background::Background() : GameObject()
{
	name = "Background";
}

Background::~Background()
{
}

void Background::update()
{

}

void Background::handleCollision(std::shared_ptr<Collider> other)
{
}
