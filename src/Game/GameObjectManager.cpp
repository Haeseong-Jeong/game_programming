#include "Game/GameObjectManager.h"
#include "Game/GameTextureManager.h"

#include "Object/Object.h"
#include "Object/Entity/Enemy.h"
#include "Object/Entity/Player.h"
#include "Object/Entity/Bullet.h"

#include <iostream>>


GameObjectManager::GameObjectManager(GameTextureManager* texturemanager, sf::Vector2u window_size)
    : texturemanager{ texturemanager }, window_size{ window_size }, player{ nullptr }
{
}

GameObjectManager::~GameObjectManager()
{
    for (int i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    };
}

sf::Vector2u GameObjectManager::get_window_size() { return window_size; }
GameTextureManager* GameObjectManager::get_texturemanager() { return texturemanager; }
Player* GameObjectManager::get_player() { return player; }
std::vector<Entity*>& GameObjectManager::get_entities() { return entities; }


void GameObjectManager::spwan_player()
{
    float size = 3.0f;
    float speed = 550.f;
    Player* player = new Player(this, EntityType::PLAYER, size, speed);
    player->get_shape()->setPosition({ sf::Vector2f(window_size.x / 2 - size, window_size.y / 2 - size)});
    entities.push_back(player);
    this->player = player;
}


void GameObjectManager::spwan_enemy(bool first_spawn)
{
    float max_size = 3.0f;
    float max_speed = 350.f;
    if (enemy_clock.getElapsedTime().asSeconds() >= enemy_period || first_spawn)
    {
        for (int i = 0; i < enemy_gen_num; i++)
        {
            Enemy* enemy = new Enemy(this, EntityType::ENEMY, max_size, max_speed);
            entities.push_back(enemy);
        }
        enemy_clock.restart();
    }
}

void GameObjectManager::spwan_bullet(bool first_spawn)
{
    float size = 5.0f;
    float speed = 550.f;
    if (bullet_clock.getElapsedTime().asSeconds() >= shoot_period || first_spawn)
    {
        Bullet* bullet = new Bullet(this, EntityType::BULLET, 5.f, 550.f);
        entities.push_back(bullet);
        bullet_clock.restart();
    }
}


void GameObjectManager::erase_entities()
{
    std::erase_if(entities, [&](Entity* enty)
        {
            if (!enty->is_activate())
            {
                delete enty; // 먼저 객체를 삭제
                return true;   // 벡터에서 제거
            }
            return false;
        }
    );
}


void GameObjectManager::reset_entities()
{
    for (int i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    };
    entities.clear();
}