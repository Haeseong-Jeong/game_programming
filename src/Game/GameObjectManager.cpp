//#include "Game/GameEntityManager.h"
//#include "Entity/Entity.h"
////#include "Game/Game.h"
//#include <iostream>>
//
//GameEntityManager::GameEntityManager(Game* game) : game{ game }
//{
//}
//
//GameEntityManager::~GameEntityManager()
//{
//    ////delete player;
//    //for (int i = 0; i < entities.size(); i++)
//    //{
//    //    delete entities[i];
//    //};
//}
//
//Player* GameEntityManager::get_player()
//{
//    return player;
//}
//
//std::vector<Entity*>& GameEntityManager::get_entities()
//{
//    return entities;
//}
//
//
//void GameEntityManager::spwan_player()
//{
//    float size = 3.0f;
//    float speed = 550.f;
//    sf::Vector2u window_size = game->get_window().getSize();
//    Player* player = new Player(game, EntityType::PLAYER, size, speed);
//    player->get_shape()->setPosition({ sf::Vector2f(window_size.x / 2 - size, window_size.y / 2 - size)});
//    entities.push_back(player);
//    this->player = player;
//    
//    //game->get_entities().push_back(player);
//    //game->set_player(player);
//}
//
//
//void GameEntityManager::spwan_enemy()
//{
//    float max_size = 3.0f;
//    float max_speed = 350.f;
//    static bool first_spwan = true;
//    if (enemy_clock.getElapsedTime().asSeconds() >= enemy_period || first_spwan)
//    {
//        for (int i = 0; i < enemy_gen_num; i++)
//        {
//            Enemy* enemy = new Enemy(game, EntityType::ENEMY, max_size, max_speed);
//            entities.push_back(enemy);
//            //game->get_entities().push_back(enemy);
//        }
//        first_spwan = false;
//        enemy_clock.restart();
//    }
//}
//
//void GameEntityManager::spwan_bullet()
//{
//    float size = 5.0f;
//    float speed = 550.f;
//    static bool first_spwan = true;
//    if (bullet_clock.getElapsedTime().asSeconds() >= shoot_period || first_spwan)
//    {
//        Bullet* bullet = new Bullet(game, EntityType::BULLET, 5.f, 550.f);
//        entities.push_back(bullet);
//        //game->get_entities().push_back(bullet);
//        first_spwan = false;
//        bullet_clock.restart();
//    }
//}