#pragma once

#include <SFML/Graphics.hpp>

class Entity;

class GameTextureManager;
class GameObjectManager;
class GameLogic;

class Game
{
public:
	GameObjectManager* objectmanager;
	GameTextureManager* texturemanager;
	GameLogic* gamelogic;

public:
	Game(int window_w, int window_h);
	~Game();

	sf::Window& get_window();

	void set_background();
	void set_text();
	void update_score();
	
	bool initialize_game(); // texture �ҷ�����, initialize_entities()
	void initialize_entities(); // create player, enemy, bullet

	void running_game();
	void process_events(); // close event
	void set_game(); //�ʱ� ����, 
	void update_game(); // clear -> draw, move, ����� �ڽ� ���� -> display

	void reset_game();

	void terminate_game(); // heap memory clear
	
private:
	bool end_game;

	sf::Vector2u window_size;
	sf::RenderWindow window;

	std::string score_text;
	sf::Text* text;
	sf::Sprite* background;

	sf::Clock clock;
	float deltatime;
};

