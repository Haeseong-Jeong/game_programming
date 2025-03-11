#include "Game/ObjectManager.h"
#include "Object/Object.h"
//#include "Game/Game.h"
#include <iostream>>

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
    delete player;
    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    };
}


Player* ObjectManager::get_player() { return player; }
std::vector<Object*> ObjectManager::get_objects() { return objects; }


void ObjectManager::spwan_player(sf::Texture& texture, sf::Vector2f window_size)
{
    float size = 3.0f;
    float speed = 550.f;
    Player* player = new Player(texture, ObjectType::PLAYER, size, speed);
    player->get_shape()->setPosition({ sf::Vector2f(window_size.x / 2 - size, window_size.y / 2 - size) });
    objects.push_back(player);
    this->player = player;
}


void ObjectManager::spwan_enemy(sf::Texture& texture)
{
    static bool first_spwan = true;
    if (enemy_clock.getElapsedTime().asSeconds() >= enemy_period || first_spwan)
    {
        for (int i = 0; i < enemy_gen_num; i++)
        {
            Enemy* enemy = new Enemy(texture, ObjectType::ENEMY, 3.0f, 350.0f);
            objects.push_back(enemy);
        }
        first_spwan = false;
        enemy_clock.restart();
    }
}

void ObjectManager::spwan_bullet(sf::Texture& texture)
{
    static bool first_spwan = true;
    if (bullet_clock.getElapsedTime().asSeconds() >= shoot_period || first_spwan)
    {
        Bullet* bullet = new Bullet(texture, ObjectType::BULLET, 5.f, 550.f);
        objects.push_back(bullet);
        first_spwan = false;
        bullet_clock.restart();
    }
}