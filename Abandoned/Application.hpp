#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.hpp"

class Application
{
private:
	sf::RenderWindow* _window;
public:
	//�������� �� ������ ���� � ����������� �� FPS
	void INIT();
	//�������� �� ���� ������� ������� ���������:
	//1. �������� ������
	//2. ���������� ������
	//3. ������������� ������� � ��������� � ���������
	//4. �������� ������ ���������
	void RUN();
	// ������ ������ � ���. �� ��� ������?
	void CLOSE();
};

