#include "Game/Game.h"
#include "Game/GameLogic.h"
#include "Game/GameTextureManager.h"
#include "Game/GameObjectManager.h"

#include "Object/Entity/Entity.h"
#include <iostream>
#include <string>

Game::Game(int window_w, int window_h)
    : deltatime{ 0 }, end_game{ false }
{
    window_size = sf::Vector2u(window_w, window_h);
    window = sf::RenderWindow{ sf::VideoMode(window_size), "Game play" };

    texturemanager = new GameTextureManager();
    objectmanager = new GameObjectManager(texturemanager, window_size);
    gamelogic = new GameLogic(objectmanager);
}

Game::~Game() {}

sf::Window& Game::get_window() { return window; }

bool Game::initialize_game() 
{
    if (!texturemanager->load_textures())
    {
        std::cout << "Texture load failed!!" << std::endl;
        return false;
    }
    objectmanager->set_background();
    objectmanager->set_text();
    initialize_entities();
    return true;
}


void Game::initialize_entities()
{
    objectmanager->spwan_player();
    objectmanager->spwan_enemy(true);
    objectmanager->spwan_bullet(true);
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
        if (event->is<sf::Event::Closed>()) { window.close(); }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) { window.close(); }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) { reset_game(); }
    }
}

void Game::set_game()
{
    if (!end_game)
    {
        deltatime = clock.restart().asSeconds();
        //objectmanager->get_player()->move_by_mouse(window);
        objectmanager->spwan_enemy();
        objectmanager->spwan_bullet();
    }
}

void Game::update_game()
{
    // 1. Clear screen
    window.clear();
    window.draw(*objectmanager->get_background());
    window.draw(*objectmanager->get_text());

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
    gamelogic->update_score();
    objectmanager->erase_entities();

    // 3. Display the window
    window.display();
}


void Game::terminate_game()
{
    delete gamelogic;
    delete objectmanager;
    delete texturemanager;
}

void Game::reset_game()
{
    objectmanager->reset_entities();
    gamelogic->reset_score();
    initialize_entities();
    end_game = false;
}
