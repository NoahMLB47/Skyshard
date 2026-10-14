#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "GameObject.hpp"

class Background : public GameObject {

private:


public:
	Background();
	virtual ~Background();

	void update();
	void handleCollision(std::shared_ptr<Collider> other);
};

#endif