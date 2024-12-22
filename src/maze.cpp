#include "maze.hpp"

Maze::Maze() : path("../res/maze.txt")
{
    setData();
    display();
}

void Maze::setData()
{
    ifstream input(this->path);
    if(!input)
        cout << "ERROR::OPEN FILE" << endl;
    string line;
    int cur = 0;
    while(getline(input, line))
    {
        istringstream iss(line);
        int number;
        vector<int> numbers;
        if(cur==0)
        {
            int width, height;
            iss >> width >> height;
            //cout << width << height;
            this->blocks.resize(height, vector<block>(width, air));
        }
        if(cur==1 || cur==2)
        {
            int x, y;
            iss >> x >> y;
            if(cur==1)
                start.x=x, start.y=y;
            if(cur==2)
                end.x=x, end.y=y;
            //cout << "(" << x << "," << y << ")" << endl;
        }
        else
        {
            int w = 0;
            while(iss >> number)
            {
                if(number)
                {
                    blocks[cur-3][w] = obstacle;
                } else {
                    blocks[cur-3][w] = air;
                }
                w++;
            }
        }      
        cur ++;
    } 
    input.close();
    blocks[start.y][start.x] = block::start;
    blocks[end.y][end.x] = block::end;
    cout << "SUCCESS::SETDATA" << endl;
}

void Maze::display()
{
    for(int i=0;i<blocks.size();i++)
    {
        for(int j=0;j<blocks[i].size();j++)
        {
    
            if(blocks[i][j]==block::start) cout << "s";
            if(blocks[i][j]==block::start) cout << "e";
            if(blocks[i][j]==block::obstacle) cout << "#";
            if(blocks[i][j]==block::obstacle) cout << " ";
            if(blocks[i][j]==block::visted) cout << "O";
            
        }
        cout << endl;
    }
}
