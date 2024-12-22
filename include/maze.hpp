#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

enum block
{
    air, obstacle, visited, start, end
};

struct point
{
    int x, y;
};

class Maze
{
public:
    vector<vector<block>> blocks;
    point start, end;
    string path;

    //SFML
    sf::RenderWindow window;
    sf::RectangleShape cellShape;

public:
    Maze();
    void setData();
    void display();
    void render();
    bool findPath(); // 迷宫路径查找
    void drawMaze(); // 绘制迷宫
};