#pragma once
#include "SFML/Graphics.hpp"

class Character;

//��������� �����. �������� �� ���������� ���� ������� ���������� � �������� ��� �� ������� �� �����.
class PlayerController
{
private:
	PlayerController() = default;
	static PlayerController* _controller;
	sf::Vector2f _aimPosition;
public:
	PlayerController(PlayerController const&) = delete;
	void operator=(PlayerController const&) = delete;
	~PlayerController();

	static PlayerController* getController();

	void controllPlayer(Character& player, float time, sf::RenderWindow* window);
};

