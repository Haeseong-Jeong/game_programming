#pragma once


#include <SFML/Graphics.hpp>

class Entity;
class GameObjectManager;

class GameLogic
{
public:

public:
	GameLogic(GameObjectManager* objectmanager);
	~GameLogic();

	bool check_collision(Entity* e, Entity* b); // 객체의 뼈대가 충돌했는지 판별
	void is_hit(); // 총알과 적이 맞았는지 판별, check_collision() 활용
	bool is_dead(); // 플레이어와 적이 맞았는지 판별, check_collision() 활용
	bool is_out_boundary(sf::Vector2u window_size); // 객체가 화면 밖으로 나갔는지 판별

private:
	GameObjectManager* objectmanager;
};

