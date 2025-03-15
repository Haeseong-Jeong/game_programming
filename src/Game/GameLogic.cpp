#include "Game/GameLogic.h"
#include "Game/GameObjectManager.h"

#include "Object/Entity/Entity.h"

#include <iostream>>

GameLogic::GameLogic(GameObjectManager* objectmanager) : objectmanager{ objectmanager }
{
}

GameLogic::~GameLogic()
{
}

bool GameLogic::check_collision(Entity* e, Entity* b)
{
	std::optional<sf::Rect<float>> is_intersection = e->skeleton.getGlobalBounds().findIntersection(b->skeleton.getGlobalBounds());
	return is_intersection.has_value();
}

void GameLogic::is_hit()
{
    std::vector<Entity*>& entities = objectmanager->get_entities();

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
                    //score += 1;
                    break;
                }
            }
        }
    }
}


bool GameLogic::is_dead()
{
    std::vector<Entity*>& entities = objectmanager->get_entities();

    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->get_type() == EntityType::PLAYER)
        {
            for (int j = 0; j < entities.size(); j++)
            {
                if (entities[j]->get_type() != EntityType::ENEMY) { continue; }
                if (check_collision(entities[i], entities[j]))
                {
                    //end_game = true;
                    //break;
                    return true;
                }
            }
        }
    }
    return false;
}



bool GameLogic::is_out_boundary(sf::Vector2u window_size)
{
    std::vector<Entity*>& entities = objectmanager->get_entities();

    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->get_type() == EntityType::ENEMY) { continue; }
        sf::Vector2f pos = entities[i]->get_position();
        if (pos.x < 0 || pos.x > window_size.x || pos.y < 0 || pos.y > window_size.y)
        {
            if (entities[i]->get_type() == EntityType::PLAYER)
            {
                //end_game = true;
                //return;
                return true;
            }
            entities[i]->deactivate();
        }
    }
    return false;
}
