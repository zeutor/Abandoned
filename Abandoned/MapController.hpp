#pragma once
#include <string>
#include "Constants.hpp"
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include "SFML/Graphics.hpp"

// ��������� �����, ���������� �� ��������, ��������� ����� � �������������� � �� ���������.
class MapController
{
private:
	MapController() = default;
	sf::Vector2i _mapSize;
	static MapController* _mapController;
	sf::Texture _tileSet;
	//��� ������� �����:
	//1. �����������
	//2. ��������� �������
	int** _activeMap[2];
	//������ ID �������� �� �����, ����� ������� ����� �� ����� ������
	static std::unordered_set<int> idOfCollisionObjs;
	//������ ID � ��������������� �� ����������� �� tileSet'� ������� �����
	static std::unordered_map<int, sf::Vector2i> idOfGroundTextures;
	//������ ID � ��������������� �� ����������� �� tileSet'� ������� ��������
	static std::unordered_map<int, sf::Vector2i> idOfObjsTextures;
public:
	MapController(MapController const&) = delete;
	void operator= (MapController const&) = delete;

	static void getInfoFromFile();
	static MapController* getController();
	
	sf::Vector2i getMapSize();

	//��� direction: 0 - UP, 1 - RIGHT, 2 - DOWN, 3 - LEFT
	//True ���� ���� ������ �� ����������
	bool checkCollision(int direction, sf::Vector2f characterPosition);
	void getMap(const char* mapTitle);
	//��� ��������� ����������� ���� 0, � ��� �������� 1
	void drawMap(sf::RenderWindow& window, int mapLayToDraw);

	bool isCollisionObjOnPos(sf::Vector2i position);

	
};

