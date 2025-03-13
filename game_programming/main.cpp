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

    //Game game = Game(1200,800); //input window size
    //game.initialize_game();
    //game.running_game(); // set -> update(draw -> move)
    //game.terminate_game();

    sf::RenderWindow window(sf::VideoMode({ 1000, 500 }), "Sprite Bounding Box");

    // 텍스처 로드
    sf::Texture texture;
    if (!texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_BackGrounds.png"))
    //if (!texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Ships.png"))
    {
        return -1;
    }

    sf::Sprite sprite(texture);

    // 특정 영역만 잘라서 사용 (258,0)부터 (128x256) 크기
    sf::IntRect cropRect({ 0, 0 }, { 128, 256 });
    sprite.setTextureRect(cropRect);

    // 90도 회전
    sprite.setRotation(sf::degrees(90.f));

    // 원본 크기 (자른 부분의 크기)
    sf::Vector2f croppedSize(cropRect.size.x, cropRect.size.y);

    // 윈도우 크기에 맞게 스케일 적용 (회전 후, width <-> height 변경)
    float scaleX = static_cast<float>(window.getSize().y) / croppedSize.x;
    float scaleY = static_cast<float>(window.getSize().x) / croppedSize.y;
    sprite.setScale(sf::Vector2f{ scaleX, scaleY });

    // 회전 중심을 잘라낸 부분의 중심으로 설정
    sprite.setOrigin(sf::Vector2f{ croppedSize.x / 2.f, croppedSize.y / 2.f });

    // 회전 후, 화면 중앙에 배치
    sprite.setPosition(sf::Vector2f{ window.getSize().x / 2.f, window.getSize().y / 2.f });

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}