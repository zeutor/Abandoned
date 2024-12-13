#pragma once

constexpr float WINDOW_HEIGHT = 720.0;
constexpr float WINDOW_WIDTH = 1280.0;
constexpr unsigned int FRAME_LIMIT = 60;

constexpr float TIME_MULTIPLIER = 7;

constexpr float SIZE_MULTIPLIER = 3.f;

constexpr float SLOW_WALK_DISTANCE = 24.f;

constexpr float DEFAULT_SPEED = 20.f * SIZE_MULTIPLIER;
constexpr float RUN_MULTIPLIER = 1.25f;
constexpr float SLOW_WALK_MULTIPLIER = 0.5f;

constexpr float COLLISION_MULTIPLIER = -0.1f;

constexpr int PIXELS_FOR_OBSTACLE = 8;

// �������� �������. ������ ����� ���� ��� ����������� �� ������ ����������� ���������� � ������� ����.
constexpr float PIXELS_PER_METER = 100.f;

// ��� ����� ������ �� ������. ���� ���� ���������, �� � SIZE_MULTIPLIER.
constexpr int PIXELS_PER_CELL = 16 * SIZE_MULTIPLIER;

// ������ ����������, � ������� ����� ���������, ��� �������� �������� �����.
constexpr float POSITION_EPSILON = PIXELS_PER_CELL /1.5;

// ���������� �� ������� �������� ������ ������������ �� ������������� ��������.
constexpr float BLOCK_EPSILON = 1.5f;