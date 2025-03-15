#include "Game/GameTextureManager.h"
#include "Game/GameObjectManager.h"

#include "Object/Entity/Bullet.h"
#include "Object/Entity/Player.h"

#include <iostream>


Bullet::Bullet(GameObjectManager* objectmanager, EntityType type, float size, float speed) 
    : Entity{ objectmanager, type, size, speed }

{
	shape = new sf::Sprite(objectmanager->get_texturemanager()->get_projectile_texture());
	//shape->setTextureRect(sf::IntRect({ 24,24 }, { 8,8 }));
    shape->setTextureRect(sf::IntRect({ 26,27 }, { 3,3 }));
    shape->setScale(sf::Vector2f(size, size));

    set_position();
    make_bounding_box();
    make_skeleton(0.6);
}
Bullet::~Bullet() {}


void Bullet::set_position()
{
    sf::Vector2f player_position = objectmanager->get_player()->get_position();
    shape->setPosition(player_position);
    direction = get_bullet_direction();
    if (direction == sf::Vector2f(0, 0)) { activate = false; }

}

sf::Vector2f Bullet::get_bullet_direction()
{
    sf::Vector2f min_dist_direction = sf::Vector2f(0, 0);
    float min_dist = 100000.0f;

    Player* player = objectmanager->get_player();
    std::vector<Entity*> entities = objectmanager->get_entities();

    for (int i = 1; i < entities.size(); i++)
    {
        if (entities[i]->get_type() != EntityType::ENEMY) { continue; }

        sf::Vector2f player_pos = player->get_position();
        sf::Vector2f enemy_pos = entities[i]->get_position();
        sf::Vector2f player_to_enemy = enemy_pos - player_pos;
        float dist = sqrt(player_to_enemy.x * player_to_enemy.x + player_to_enemy.y * player_to_enemy.y);

        if (dist < min_dist)
        {
            if (dist < EPSILON) { dist = EPSILON; }
            min_dist = dist;
            min_dist_direction = player_to_enemy / dist;
        }
    }
    return min_dist_direction;
}

void Bullet::move(float deltatime) { shape->move(direction * speed * deltatime); }