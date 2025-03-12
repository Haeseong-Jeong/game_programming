#include "Game/ObjectManager.h"
#include "Object/Object.h"
//#include "Game/Game.h"
#include <iostream>>

ObjectManager::ObjectManager(Game* game)
{
}

ObjectManager::~ObjectManager()
{
    delete game->get_player();
    std::vector<Object*> objects = game->get_objects();
    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    };
}


void ObjectManager::spwan_player()
{
    float size = 3.0f;
    float speed = 550.f;
    sf::Vector2u window_size = game->get_window().getSize();
    Player* player = new Player(game, ObjectType::PLAYER, size, speed);
    player->get_shape()->setPosition({ sf::Vector2f(window_size.x / 2 - size, window_size.y / 2 - size)});
    game->get_objects().push_back(player);
    game->set_player(player);
}


void ObjectManager::spwan_enemy()
{
    float max_size = 3.0f;
    float max_speed = 350.f;
    static bool first_spwan = true;
    if (enemy_clock.getElapsedTime().asSeconds() >= enemy_period || first_spwan)
    {
        for (int i = 0; i < enemy_gen_num; i++)
        {
            Enemy* enemy = new Enemy(game, ObjectType::ENEMY, max_size, max_speed);
            game->get_objects().push_back(enemy);
        }
        first_spwan = false;
        enemy_clock.restart();
    }
}

void ObjectManager::spwan_bullet()
{
    float size = 5.0f;
    float speed = 550.f;
    static bool first_spwan = true;
    if (bullet_clock.getElapsedTime().asSeconds() >= shoot_period || first_spwan)
    {
        Bullet* bullet = new Bullet(game, ObjectType::BULLET, 5.f, 550.f);
        game->get_objects().push_back(bullet);
        first_spwan = false;
        bullet_clock.restart();
    }
}