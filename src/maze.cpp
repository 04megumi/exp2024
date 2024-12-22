#include "maze.hpp"

Maze::Maze() : path("../res/maze.txt"), window(sf::VideoMode(800, 600), "Maze Game")
{
    cellShape.setSize(sf::Vector2f(30.f, 30.f)); // 设置单个迷宫格子的大小
    cellShape.setOutlineThickness(1.f); // 使格子有边框
    cellShape.setOutlineColor(sf::Color::Black); // 设置边框颜色
    setData();
    findPath();
    display();
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
        vector<int> numbers;
        if (cur == 0)
        {
            int width, height;
            iss >> width >> height;
            this->blocks.resize(height, vector<block>(width, air));
        }
        if (cur == 1 || cur == 2)
        {
            int x, y;
            iss >> x >> y;
            if (cur == 1)
                start.x = x, start.y = y;
            if (cur == 2)
                end.x = x, end.y = y;
        }
        else
        {
            int w = 0;
            while (iss >> number)
            {
                if (number)
                {
                    blocks[cur - 3][w] = obstacle;
                }
                else
                {
                    blocks[cur - 3][w] = air;
                }
                w++;
            }
        }
        cur++;
    }
    input.close();
    blocks[start.y][start.x] = block::start;
    blocks[end.y][end.x] = block::end;
    cout << "SUCCESS::SETDATA" << endl;
}

void Maze::display()
{
    window.clear(sf::Color::White);
    drawMaze();
    window.display();
}

void Maze::render()
{
    // 渲染主窗口
    window.clear();
    drawMaze();
    window.display();
}

void Maze::drawMaze()
{
    // 绘制迷宫
    for (int i = 0; i < blocks.size(); i++)
    {
        for (int j = 0; j < blocks[i].size(); j++)
        {
            if (blocks[i][j] == block::air)
                cellShape.setFillColor(sf::Color::White); // 空地
            if (blocks[i][j] == block::obstacle)
                cellShape.setFillColor(sf::Color::Black); // 障碍物
            if (blocks[i][j] == block::start)
                cellShape.setFillColor(sf::Color::Green); // 起点
            if (blocks[i][j] == block::end)
                cellShape.setFillColor(sf::Color::Red); // 终点
            if (blocks[i][j] == block::visited)
                cellShape.setFillColor(sf::Color(0, 0, 255, 128)); // 已访问的路径

            // 设置当前格子的显示位置
            cellShape.setPosition(j * 30.f, i * 30.f); // 位置根据每个单元格的大小和坐标计算
            window.draw(cellShape);
        }
    }
}

bool Maze::findPath()
{
    // 简单的广度优先搜索（BFS）寻找路径（这里只是一个例子，您可以使用更复杂的算法）
    int dx[] = {1, -1, 0, 0}; // x方向的移动
    int dy[] = {0, 0, 1, -1}; // y方向的移动
    vector<vector<bool>> visited(blocks.size(), vector<bool>(blocks[0].size(), false));
    vector<vector<point>> parent(blocks.size(), vector<point>(blocks[0].size()));

    vector<point> queue;
    queue.push_back(start);
    visited[start.y][start.x] = true;

    while (!queue.empty())
    {
        point current = queue.front();
        queue.erase(queue.begin());

        // 如果找到了终点，回溯路径
        if (current.x == end.x && current.y == end.y)
        {
            point p = current;
            while (p.x != start.x || p.y != start.y)
            {
                blocks[p.y][p.x] = block::visited;
                p = parent[p.y][p.x];
            }
            return true;
        }

        // 扩展搜索
        for (int i = 0; i < 4; i++)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < blocks[0].size() && ny >= 0 && ny < blocks.size() && !visited[ny][nx] && blocks[ny][nx] != obstacle)
            {
                visited[ny][nx] = true;
                parent[ny][nx] = current;
                queue.push_back({nx, ny});
            }
        }
    }
    return false;
}