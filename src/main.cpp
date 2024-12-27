#include "maze.hpp"
#include "phone.hpp"



int main()
{

    Maze maze;

    while (!WindowShouldClose()) 
    {
        maze.render();
    }

    CloseWindow();

    return 0;
}


/*
int main() {

    use();

    return 0;
}
*/