#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

enum block
{
    air, obstacle, visted, start, end
};

struct point
{
    int x, y;
};

class Maze
{
private:
    vector<vector<block> > blocks;
    point start, end;
    char* path;
public:
    Maze();
    void setData();
    void display();

};