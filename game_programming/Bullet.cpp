#include "Ctrl.h"
#include "Player.h"
#include "Bullet.h"
#include <iostream>

Bullet::Bullet(Ctrl* game_ctrl, ObjectType type, float size, float speed) : Object{ game_ctrl, type, size, speed }
{
	sf::Vector2f player_position = game_ctrl->get_player_ptr()->get_position();
	shape = new sf::Sprite(game_ctrl->get_projectile_texture());
	//shape->setTextureRect(sf::IntRect({ 24,24 }, { 8,8 }));
    shape->setTextureRect(sf::IntRect({ 26,27 }, { 3,3 }));
    shape->setScale(sf::Vector2f(size, size));
    //shape->scale(sf::Vector2f(size, size));

	shape->setPosition(player_position);
	direction = get_bullet_direction();
    if (direction == sf::Vector2f(0,0)) { activate = false; }

    make_bounding_box();
    make_skeleton(0.6);
}
Bullet::~Bullet() {}


sf::Vector2f Bullet::get_bullet_direction()
{
    sf::Vector2f min_dist_direction = sf::Vector2f(0, 0);
    float min_dist = 100000.0f;

    Player* player = game_ctrl->get_player_ptr();
    std::vector<Object*> objects = game_ctrl->get_objects();

    for (int i = 1; i < objects.size(); i++)
    {
        if (objects[i]->get_type() != ObjectType::ENEMY) { continue; }

        sf::Vector2f player_pos = player->get_position();
        sf::Vector2f enemy_pos = objects[i]->get_position();
        sf::Vector2f player_to_enemy = enemy_pos - player_pos;
        float dist = sqrt(player_to_enemy.x * player_to_enemy.x + player_to_enemy.y * player_to_enemy.y);

        if (dist < min_dist)
        {
            if (dist < game_ctrl->EPSILON) { dist = game_ctrl->EPSILON; }
            min_dist = dist;
            min_dist_direction = player_to_enemy / dist;
        }
    }
    return min_dist_direction;
}

void Bullet::move(float deltatime) 
{ 
    shape->move(direction * speed * deltatime); 

    //bounding_box.move(direction * speed * deltatime);
}