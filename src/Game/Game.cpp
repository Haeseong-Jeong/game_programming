#include "Game/Game.h"
#include "Game/GameLogic.h"
#include "Game/GameTextureManager.h"
#include "Game/GameObjectManager.h"

#include "Object/Entity/Entity.h"
//#include "Object/Entity/Enemy.h"
//#include "Object/Entity/Bullet.h"
//#include "Object/Entity/Player.h"
#include <iostream>

Game::Game(int window_w, int window_h)
    : background{ nullptr }, deltatime{ 0 }, score{ 0 }, end_game{ false }
{
    window_size = sf::Vector2u(window_w, window_h);
    window = sf::RenderWindow{ sf::VideoMode(window_size), "Game play" };

    texturemanager = new GameTextureManager();
    texturemanager->load_textures();
    objectmanager = new GameObjectManager(texturemanager, window_size);
    gamelogic = new GameLogic(objectmanager);
}

Game::~Game()
{}

sf::Window& Game::get_window() { return window; }


void Game::set_background()
{
    background = new sf::Sprite(texturemanager->get_background_texture());
    sf::Vector2f texture_size(256.f, 128.f);
    sf::IntRect crop_rect({ 257, 258 }, { 256, 128 });
    background->setTextureRect(crop_rect);
    sf::Vector2f scaleFactor(window_size.x / texture_size.x, window_size.y / texture_size.y);
    background->setScale(scaleFactor);
    background->setColor(sf::Color(255, 255, 255, 50));  // 4번째 인자가 투명도, 0 ~ 256 투명도 (0이 완전 투명)
}

bool Game::initialize_game() 
{
    set_background();
    initialize_entities();
    return true;
}


void Game::initialize_entities()
{
    objectmanager->spwan_player();
    objectmanager->spwan_enemy();
    objectmanager->spwan_bullet();
}

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
    if (!end_game)
    {
        deltatime = clock.restart().asSeconds();
        //player->move_by_mouse(window);

        objectmanager->spwan_enemy();
        objectmanager->spwan_bullet();
    }
}

void Game::update_game()
{
    // 1. Clear screen
    window.clear();
    window.draw(*background);

    // 2. Draw and Move Entity
    std::vector<Entity*>& entities = objectmanager->get_entities();

    if (gamelogic->is_dead() || gamelogic->is_out_boundary(window_size))
    {
        for (int i = 0; i < entities.size(); i++)
        {
            entities[i]->draw(window);
        }
        end_game = true;
        window.display();
        return;
    }

    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->draw(window);
        entities[i]->move(deltatime);
        entities[i]->make_bounding_box();
        entities[i]->make_skeleton(0.6);
    }

    //std::cout << "객체 개수 :" << entities.size() << std::endl;
    gamelogic->is_hit();// 피격 판정
    //end_game = gamelogic->is_dead();
    //end_game = gamelogic->is_out_boundary(window_size); // 화면 나감 판정

    objectmanager->erase_entities();

    // 3. Display the window
    window.display();
}


void Game::terminate_game()
{
    delete gamelogic;
    delete objectmanager;
    delete texturemanager;
    delete background;
}