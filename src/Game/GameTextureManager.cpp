#include "Game/GameTextureManager.h"

GameTextureManager::GameTextureManager()
{
    //if (!load_textures())
    //{
    //    //std::cout << "Texture load failed!!" << std::endl;
    //}
}

GameTextureManager::~GameTextureManager() {}

bool GameTextureManager::load_textures()
{
    if (!ship_texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Ships.png")) { return false; }
    if (!projectile_texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Projectiles.png")) { return false; }
    if (!background_texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_BackGrounds.png")) { return false; }

    return true;
}


sf::Texture& GameTextureManager::get_ship_texture() { return ship_texture; }
sf::Texture& GameTextureManager::get_projectile_texture() { return projectile_texture; }
sf::Texture& GameTextureManager::get_background_texture() { return background_texture; }


