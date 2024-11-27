#include "AStar.hpp"

AStar::sNode* AStar::nodes = nullptr;      // ������ ����� �����
int AStar::nMapWidth = WINDOW_WIDTH;         // ������ �����
int AStar::nMapHeight = WINDOW_HEIGHT;         // ������ �����
vector<Vector2f> AStar::obstacles = vector<Vector2f>();

AStar::AStar() {
    OnUserCreate();  // ������������� �����
}

// ��������� ��������� ������� ��� A* ���������
void AStar::setStart(int x, int y) {
    nodeStart = &nodes[y * nMapWidth + x];
}

// ��������� �������� ������� ��� A* ���������
void AStar::setEnd(int x, int y) {
    nodeEnd = &nodes[y * nMapWidth + x];
}

// ��������� ����������� �� �����
void AStar::setObstacle(int x, int y) {
    nodes[y * nMapWidth + x].bObstacle = true;
    obstacles.push_back(Vector2f(x * PIXELS_FOR_OBSTACLE, y * PIXELS_FOR_OBSTACLE));  // ���������� ��������� �����������
}

// �������� ����������� � �����
void AStar::unsetObstacle(int x, int y) {
    nodes[y * nMapWidth + x].bObstacle = false;

    // �������� ��������� ����������� �� ������
    obstacles.erase(remove_if(obstacles.begin(), obstacles.end(),
        [=](Vector2f pos) { return pos.x == x * PIXELS_FOR_OBSTACLE && pos.y == y * PIXELS_FOR_OBSTACLE; }), obstacles.end());
}

void AStar::removeAllObstacle()
{
    obstacles = std::vector<sf::Vector2f>();
}



// ���������� ������ ���� �����������
vector<Vector2f> AStar::getObstacles() {
    return obstacles;
}


// ������� ��� ��������� ���� �� ��������� �� �������� �����
vector<AStar::sNode*> AStar::getPath() {
    vector<sNode*> path;
    if (nodeEnd != nullptr) {
        sNode* p = nodeEnd;
        // ��������������� ���� �� �������� �� ��������� �����
        while (p->parent != nullptr) {
            path.push_back(p);
            p = p->parent;
        }
        reverse(path.begin(), path.end()); // �������������� ����, ����� �� ��� �� ������ �� �����
    }
    return path;
}

/* ������������� ����� ����� :
*   ��������� ����, ������� �� �����������
*   ������������ �� ������� �������������
*   ��������� ������� ��� �����
*/
void AStar::OnUserCreate() {
    nodes = new sNode[nMapWidth * nMapHeight];
    for (int x = 0; x < nMapWidth; x++)
        for (int y = 0; y < nMapHeight; y++) {
            nodes[y * nMapWidth + x].x = x;
            nodes[y * nMapWidth + x].y = y;
            nodes[y * nMapWidth + x].bObstacle = false;  // �� ��������� ���� �� �������� �������������
            nodes[y * nMapWidth + x].parent = nullptr;   // ��� ������������ ����� �� ������
            nodes[y * nMapWidth + x].bVisited = false;   // ���� ��� �� ���������
        }

    // ��������� ������� ��� ������� ����
    for (int x = 0; x < nMapWidth; x++)
        for (int y = 0; y < nMapHeight; y++) {
            if (y > 0)
                nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + x]);  // ������� �����
            if (y < nMapHeight - 1)
                nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + x]);  // ������ �����
            if (x > 0)
                nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[y * nMapWidth + (x - 1)]);  // ����� �����
            if (x < nMapWidth - 1)
                nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[y * nMapWidth + (x + 1)]);  // ������ �����
        }

    nodeStart = &nodes[0];   // ��������� ���� �� ���������
    nodeEnd = &nodes[12];    // �������� ���� �� ���������
}

// �������� ������ ���� A*
void AStar::Solve_AStar() {
    // ����� ���� ����� ��� ������ ������
    for (int x = 0; x < nMapWidth; x++)
        for (int y = 0; y < nMapHeight; y++) {
            nodes[y * nMapWidth + x].isParent = false;
            nodes[y * nMapWidth + x].bVisited = false;
            nodes[y * nMapWidth + x].fGlobalGoal = INFINITY;
            nodes[y * nMapWidth + x].fLocalGoal = INFINITY;
            nodes[y * nMapWidth + x].parent = nullptr;
        }

    // ������� ��� ���������� ���������� ����� ����� ������
    auto distance = [](sNode* a, sNode* b) {
        return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
        };

    sNode* nodeCurrent = nodeStart;  // �������� � ���������� ����
    nodeStart->fLocalGoal = 0.0f;    // ��������� ���� ��� ���������� ���� � 0
    nodeStart->fGlobalGoal = distance(nodeStart, nodeEnd);  // ���������� ���� � ��������� �� �����

    list<sNode*> listNotTestedNodes;
    listNotTestedNodes.push_back(nodeStart);  // ��������� ��������� ���� � ������

    // �������� ���� A* ���������
    while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd) {
        // ���������� ����� �� ���������� ������
        listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

        // ������� ����, ������� ��� ���� ��������
        while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
            listNotTestedNodes.pop_front();

        if (listNotTestedNodes.empty())
            break;

        nodeCurrent = listNotTestedNodes.front();
        nodeCurrent->bVisited = true;  // �������� ���� ��� ����������

        // ������������ ���� ������� �������� ����
        for (auto nodeNeighbour : nodeCurrent->vecNeighbours) {
            if (!nodeNeighbour->bVisited && !nodeNeighbour->bObstacle)
                listNotTestedNodes.push_back(nodeNeighbour);

            // ��������� ������������ ����� �������� ���� ����� ������� ����
            float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

            // ���� ������ ����� �������� ����, ��������� ������ ����
            if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal) {
                nodeNeighbour->parent = nodeCurrent;
                nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;
                nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + distance(nodeNeighbour, nodeEnd);
            }
        }
    }
}

// ��������������� ���� �� ��������� ���� � ����������, ������� ��� ��� ����������
void AStar::path() {
    if (nodeEnd != nullptr) {
        sNode* p = nodeEnd;
        while (p->parent != nullptr) {
            nodes[p->y * nMapWidth + p->x].isParent = true;
            p = p->parent;
        }
    }
}
