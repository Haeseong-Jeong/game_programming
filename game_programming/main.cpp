#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include "Game/Game.h"

#include <cmath>
#include <random>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{
    // ****** Detected memory leaks! ******
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //Game game;
    Game game = Game(1200,800); //input window size
    game.initialize_game();
    game.running_game(); // set -> update(draw -> move)
    game.terminate_game();

    //sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Sprite Bounding Box");

    //// 텍스처 로드
    //sf::Texture texture;
    //if (!texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Ships.png"))
    ////if (!texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Projectiles.png"))
    //{
    //    return -1;
    //}

    //// 스프라이트 설정
    //float size = 50.0f;
    //sf::Sprite sprite(texture);
    //sprite.setTextureRect(sf::IntRect({ 40,2 }, { 7,5 }));
    //sprite.setScale(sf::Vector2f(size, size));
    //sprite.setPosition({ 200.f, 150.f });  // 위치 설정

    //while (window.isOpen()) {

    //    while (const std::optional event = window.pollEvent())
    //    {
    //        // Close window: exit
    //        if (event->is<sf::Event::Closed>())
    //            window.close();
    //    }

    //    window.clear();

    //    // 바운딩 박스 설정
    //    sf::FloatRect bounds = sprite.getGlobalBounds();
    //    sf::RectangleShape boundingBox(sf::Vector2f(bounds.size.x, bounds.size.y));
    //    boundingBox.setPosition(sprite.getPosition());
    //    boundingBox.setFillColor(sf::Color::Transparent);
    //    boundingBox.setOutlineColor(sf::Color::Red);
    //    boundingBox.setOutlineThickness(0.7f);

    //    float bb_width = bounds.size.x;
    //    float bb_height = bounds.size.y;
    //    float sk_width = bb_width * 0.7;
    //    float sk_height = bb_height * 0.7;

    //    sf::RectangleShape skeleton(sf::Vector2f(sk_width, sk_height));
    //    skeleton.setPosition(bounds.getCenter() - sf::Vector2f(sk_width/2, sk_height/2));
    //    skeleton.setFillColor(sf::Color::Transparent);
    //    skeleton.setOutlineColor(sf::Color::Yellow);
    //    skeleton.setOutlineThickness(0.7f);

    //    // 바운딩 박스 그리기
    //    window.draw(sprite);
    //    window.draw(boundingBox);
    //    window.draw(skeleton);

    //    window.display();
    //}

    return 0;
}