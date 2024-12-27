#include "maze.hpp"
#include <raylib.h>

Maze::Maze() : path("../res/maze.txt"), player{0, 0} 
{
    cellShape.width = 30.f;
    cellShape.height = 30.f;
    setData();
    InitWindow(blocks[0].size() * 30, blocks.size() * 30 + 30, "Maze Game (Press H For AI)");
}

void Maze::setData()
{
    ifstream input(this->path);
    if (!input)
        cout << "ERROR::OPEN FILE" << endl;
    string line;
    int cur = 0;
    while (getline(input, line))
    {
        istringstream iss(line);
        int number;
        if (cur == 0)
        {
            int width, height;
            iss >> width >> height;
            this->blocks.resize(height, vector<block>(width, air));
            this->visited.resize(height, vector<bool>(width, false));
        }
        if (cur == 1)
        {
            int numstart, numend;
            iss >> numstart >> numend;
            //cout << numstart << " " << numend << endl;
            this->starts.resize(numstart), this->ends.resize(numend);
            int i = 0;
            while(i < numstart)
            {
                getline(input, line);
                istringstream iss(line);
                int x, y;
                iss >> x >> y;
                cout << i << ": " << x << y << endl;
                point newpoint = {x, y};
                this->starts[i] = newpoint;
                i++;
            }
            i = 0;
            while(i < numend)
            {
                getline(input, line);
                istringstream iss(line);
                int x, y;
                iss >> x >> y;
                point newpoint = {x, y};
                this->ends[i] = newpoint;
                i++;
            }
            cur = 2;
        }
        else
        {
            int w = 0;
            while (iss >> number)
            {
                blocks[cur - 3][w] = (number ? obstacle : air);
                w++;
            }
        }
        cur++;
    }
    input.close();
    for(auto point : this->starts)
    {
        blocks[point.y][point.x] = block::start;
    }
    for(auto point : this->ends)
    {
        blocks[point.y][point.x] = block::end;
    }
    player = this->starts[0]; 
}

void Maze::render()
{
    while(!WindowShouldClose())
    {
        if(this->now == state::play)
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            drawMaze();
            processInput();

            EndDrawing();
        } else {
            ai(0);
            this->now = state::play;
        }
        
    }
}

void Maze::drawMaze()
{
    for (int i = 0; i < blocks.size(); i++)
    {
        for (int j = 0; j < blocks[i].size(); j++)
        {
            int x = j * 30; 
            int y = i * 30; 

            if (blocks[i][j] == block::air)
                DrawRectangle(x, y, cellShape.width, cellShape.height, LIGHTGRAY); 
            if (blocks[i][j] == block::obstacle)
                DrawRectangle(x, y, cellShape.width, cellShape.height, DARKGRAY); 
            if (blocks[i][j] == block::start)
                DrawRectangle(x, y, cellShape.width, cellShape.height, GREEN);   
            if (blocks[i][j] == block::end)
                DrawRectangle(x, y, cellShape.width, cellShape.height, RED); 
            if (blocks[i][j] == block::visited)
                DrawRectangle(x, y, cellShape.width, cellShape.height, BLUE);    
        }
    }

    DrawRectangle(player.x * 30, player.y * 30, cellShape.width, cellShape.height, YELLOW);
    string s = "Find " + to_string(this->solutions) + " solutions";
    DrawText(s.c_str(), 20, 30*(blocks.size()-1)+30 , 30, DARKGRAY);
}

void Maze::processInput()
{
    // 根据用户的键盘输入移动玩家
    if (IsKeyPressed(KEY_W) && isValidMove(player.x, player.y - 1))
    {
        player.y--;
        for(auto end : this->ends)
        {
            if (player.x == end.x && player.y == end.y)
            {
                cout << "You Win" << endl;
                DrawText("You Win!", blocks[0].size() * 10, blocks.size() * 10, 40, GREEN);
                this->solutions ++;
            }
        }
    }
    if (IsKeyPressed(KEY_S) && isValidMove(player.x, player.y + 1))
    {
        player.y++;
        for(auto end : this->ends)
        {
            if (player.x == end.x && player.y == end.y)
            {
                cout << "You Win" << endl;
                DrawText("You Win!", blocks[0].size() * 10, blocks.size() * 10, 40, GREEN);
                this->solutions ++;
            }
        }
    }
    if (IsKeyPressed(KEY_A) && isValidMove(player.x - 1, player.y))
    {
        player.x--;
        for(auto end : this->ends)
        {
            if (player.x == end.x && player.y == end.y)
            {
                cout << "You Win" << endl;
                DrawText("You Win!", blocks[0].size() * 10, blocks.size() * 10, 40, GREEN);
                this->solutions ++;
            }
        }
    } 
    if (IsKeyPressed(KEY_D) && isValidMove(player.x + 1, player.y))
    {
        player.x++;
        for(auto end : this->ends)
        {
            if (player.x == end.x && player.y == end.y)
            {
                cout << "You Win" << endl;
                DrawText("You Win!", blocks[0].size() * 10, blocks.size() * 10, 40, GREEN);
                this->solutions ++;
            }
        }
    } 
    if (IsKeyPressed(KEY_H))
    {
        this->now = state::ai;
    }
    if (IsKeyPressed(KEY_N))
    {
        this -> start ++;
        player.x = starts[start%(this->starts.size())].x;
        player.y = starts[start%(this->starts.size())].y;
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        CloseWindow();
    }

}

bool Maze::isValidMove(int x, int y)
{
    return x >= 0 && x < blocks[0].size() && y >= 0 && y < blocks.size() && blocks[y][x] != obstacle;
}

bool Maze::ai(int n)
{
    if(n==0)
    {
        for(auto start :this->starts)
        {
            this->player.y = start.y, this->player.x = start.x;
            ai(n+1);
        }
        return true;
    }

    cout << player.y << "," << player.x << endl;
    bool flag = false, ans = false;
    if (this->blocks[player.y][player.x] == block::start)
        flag = true;
    this->visited[player.y][player.x] = true;
    this->blocks[player.y][player.x] = block::visited;
    usleep(10000);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    drawMaze();
    EndDrawing();
    for (auto end : this->ends)
    {
        if (player.x == end.x && player.y == end.y)
        {
            cout << "You Win" << endl;
            this->solutions++;
            this->blocks[player.y][player.x] = block::end;
            this->visited[player.y][player.x] = false;
            sleep(1);
            BeginDrawing();
            ClearBackground(RAYWHITE);
            drawMaze();
            EndDrawing();
            return true;
        }
    }
    if (isValidMove(player.x + 1, player.y) && !visited[player.y][player.x + 1])
    {
        player.x++;
        if (ai(n)) ans = true; // 子递归成功返回
        player.x--;
    }
    if (isValidMove(player.x, player.y + 1) && !visited[player.y + 1][player.x])
    {
        player.y++;
        if (ai(n)) ans = true;
        player.y--;
    }

    if (isValidMove(player.x - 1, player.y) && !visited[player.y][player.x - 1])
    {
        player.x--;
        if (ai(n)) ans = true;
        player.x++;
    }

    if (isValidMove(player.x, player.y - 1) && !visited[player.y - 1][player.x])
    {
        player.y--;
        if (ai(n)) ans = true;
        player.y++;
    }

    // 回溯：恢复状态
    if (flag)
    {
        this->blocks[player.y][player.x] = block::start;
    }
    else
    {
        this->blocks[player.y][player.x] = block::air;
    }

    this->visited[player.y][player.x] = false; // 回溯时重置访问标志

    usleep(10000);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    drawMaze();
    EndDrawing();

    return ans;
}