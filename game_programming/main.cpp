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

    // �ؽ�ó �ε�
    sf::Texture texture;
    if (!texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_BackGrounds.png"))
    //if (!texture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Ships.png"))
    {
        return -1;
    }

    sf::Sprite sprite(texture);

    // Ư�� ������ �߶� ��� (258,0)���� (128x256) ũ��
    sf::IntRect cropRect({ 0, 0 }, { 128, 256 });
    sprite.setTextureRect(cropRect);

    // 90�� ȸ��
    sprite.setRotation(sf::degrees(90.f));

    // ���� ũ�� (�ڸ� �κ��� ũ��)
    sf::Vector2f croppedSize(cropRect.size.x, cropRect.size.y);

    // ������ ũ�⿡ �°� ������ ���� (ȸ�� ��, width <-> height ����)
    float scaleX = static_cast<float>(window.getSize().y) / croppedSize.x;
    float scaleY = static_cast<float>(window.getSize().x) / croppedSize.y;
    sprite.setScale(sf::Vector2f{ scaleX, scaleY });

    // ȸ�� �߽��� �߶� �κ��� �߽����� ����
    sprite.setOrigin(sf::Vector2f{ croppedSize.x / 2.f, croppedSize.y / 2.f });

    // ȸ�� ��, ȭ�� �߾ӿ� ��ġ
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