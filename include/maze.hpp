#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <raylib.h>
#include <string>

using namespace std;

enum block
{
    air, obstacle, visited, start, end
};

struct point
{
    int x, y;
};

enum state
{
    ai, play
};

class Maze
{
public:
    vector<vector<block>> blocks;
    vector<vector<bool>> visited;
    vector<point> starts, ends;       
    point player;
    string path;                  
    Rectangle cellShape;            

    Maze();
    void setData();
    void drawMaze();
    void render();
    void processInput();
    bool isValidMove(int x, int y);
    bool ai(int n);

    int solutions = 0;
    int start = 0;
    state now = state::play;
};

#endif