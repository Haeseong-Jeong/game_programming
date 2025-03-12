#include "Game/Game.h"
#include "Game/GameEntityManager.h"

#include <iostream>

Game::Game(int window_w, int window_h) 
    : window_w{ window_w }, window_h{ window_h }, window(sf::VideoMode({ sf::Vector2u(window_w, window_h) }), "Game play"), entitymanager{this}
{
    //entitymanager = GameEntityManager(this);
    //obm = EntityManager(this);
    //entities.clear();
    //enemy_gen_num = 5;
}

//Game::~Game()
//{
//    delete entitymanager;
//}

sf::Window& Game::get_window() { return window; }
sf::Texture& Game::get_ship_texture() { return ship_texture; }
sf::Texture& Game::get_projectile_texture() { return projectile_texture; }

GameEntityManager* Game::get_entitymanager()
{
    return &entitymanager;
}

//void Game::set_player(Player* player) { this->player = player; }
//Player* Game::get_player() { return player; }
//std::vector<Entity*> Game::get_entities() { return entities; }


bool Game::check_collision(Entity* e, Entity* b) 
{   
    std::optional<sf::Rect<float>> is_intersection = e->skeleton.getGlobalBounds().findIntersection(b->skeleton.getGlobalBounds());
    return is_intersection.has_value();
}

void Game::is_hit()
{
    std::vector<Entity*> entities = entitymanager.get_entities();

    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->get_type() == EntityType::BULLET)
        {
            for (int j = 0; j < entities.size(); j++)
            {
                if (entities[j]->get_type() != EntityType::ENEMY) { continue; }
                if (check_collision(entities[i], entities[j]))
                {
                    entities[i]->deactivate();
                    entities[j]->deactivate();
                    break;
                }
            }
        }
    }
}


void Game::is_out_boundary()
{
    std::vector<Entity*> entities = entitymanager.get_entities();

    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->get_type() == EntityType::ENEMY) { continue; }
        sf::Vector2f pos = entities[i]->get_position();
        if (pos.x < 0 || pos.x > window_w || pos.y < 0 || pos.y > window_h) { entities[i]->deactivate(); }
    }
}

//void Game::spwan_enemy()
//{
//    static bool first_spwan = true;
//    if (enemy_clock.getElapsedTime().asSeconds() >= enemy_period || first_spwan)
//    {
//        for (int i = 0; i < enemy_gen_num; i++)
//        {
//            Enemy* enemy = new Enemy(this, EntityType::ENEMY, 3.0f, 350.0f);
//            entities.push_back(enemy);
//        }
//        first_spwan = false;
//        enemy_clock.restart();
//    }
//}
//
//
//void Game::spwan_bullet()
//{
//    static bool first_spwan = true;
//    if (bullet_clock.getElapsedTime().asSeconds() >= shoot_period || first_spwan)
//    {
//        Bullet* bullet = new Bullet(this, EntityType::BULLET, 5.f, 550.f);
//        entities.push_back(bullet);
//        first_spwan = false;
//        bullet_clock.restart();
//    }
//}


bool Game::initialize_game() 
{
    if (!ship_texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Ships.png")) { return false; }
    if (!projectile_texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Projectiles.png")) { return false; }

    //initialize_entities();
    //std::cout << "객체 생성 전" << entities.size() << std::endl;
    entitymanager.spwan_player();

    //std::cout << "플레이어 객체 생성 후" <<entities.size() << std::endl;

    entitymanager.spwan_enemy();
    entitymanager.spwan_bullet();
    return true;
}


//void Game::initialize_entities()
//{
//    //Player* player = new Player(this, EntityType::PLAYER, 3.0f, 550.f);
//    //entities.push_back(player);
//    //this->player = player;
//    //spwan_enemy();
//    //spwan_bullet();
//    obm.spwan_player();
//    obm.spwan_enemy();
//    obm.spwan_bullet();
//}

void Game::running_game()
{
    while (window.isOpen())
    {
        process_events();
        set_game();
        update_game();
    }
}

void Game::process_events()
{
    // Process events
    while (const std::optional event = window.pollEvent())
    {
        // Close window: exit
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void Game::set_game()
{
    deltatime = clock.restart().asSeconds();
    //player->move_by_mouse(window);

    entitymanager.spwan_enemy();
    entitymanager.spwan_bullet();
}

void Game::update_game()
{
    // 1. Clear screen
    window.clear();

    // 2. Draw and Move Entity 
    std::vector<Entity*> entities = entitymanager.get_entities();

    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->draw(window);
        entities[i]->move(deltatime);
        entities[i]->make_bounding_box();
        entities[i]->make_skeleton(0.6);
    }

    std::cout << "객체 개수 :" << entities.size() << std::endl;
    is_hit();// 피격 판정
    is_out_boundary(); // 화면 나감 판정
    std::erase_if(entities, [&](Entity* entity) { return entity->is_activate() == false; }); // 화면 나가거나 피격 되면 제거

    // 3. Display the window
    window.display();
}


void Game::terminate_game()
{
    std::vector<Entity*> entities = entitymanager.get_entities();

    for (int i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    }
}