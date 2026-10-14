#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <memory>
#include <string>
#include <map>
#include "SDL2_Common.h"

class Renderer;

class TextureManager {

public:
	~TextureManager();

	static std::shared_ptr<TextureManager> instance();
	void init();
	SDL_Texture* findTexture(std::string name);
	void cacheTexture(std::string name, std::string path);
	void cacheTextures();
private:
	TextureManager();

	static std::shared_ptr<TextureManager> textureManager;
	std::map<std::string, SDL_Texture*> textures;
	std::shared_ptr<Renderer> renderer;
	SDL_Texture* texture;
};

#endif