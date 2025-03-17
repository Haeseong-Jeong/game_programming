#pragma once

#include <SFML/Graphics.hpp>

class GameTextureManager
{
public:

public:
	GameTextureManager();
	~GameTextureManager();

	bool load_textures();
	sf::Font& get_font();
	sf::Texture& get_ship_texture();
	sf::Texture& get_projectile_texture();
	sf::Texture& get_background_texture();

private:
	sf::Font font;
	sf::Texture ship_texture;
	sf::Texture projectile_texture;
	sf::Texture background_texture;
};

