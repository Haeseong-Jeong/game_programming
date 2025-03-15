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

	bool check_collision(Entity* e, Entity* b); // ��ü�� ���밡 �浹�ߴ��� �Ǻ�
	void is_hit(); // �Ѿ˰� ���� �¾Ҵ��� �Ǻ�, check_collision() Ȱ��
	bool is_dead(); // �÷��̾�� ���� �¾Ҵ��� �Ǻ�, check_collision() Ȱ��
	bool is_out_boundary(sf::Vector2u window_size); // ��ü�� ȭ�� ������ �������� �Ǻ�

private:
	GameObjectManager* objectmanager;
};

