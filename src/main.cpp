#include "maze.hpp"

int main()
{
    Maze maze;

    while(maze.window.isOpen())
    {
        sf::Event event;
        while(maze.window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                maze.window.close();
        }
        maze.render();
    }

    return 0;
}