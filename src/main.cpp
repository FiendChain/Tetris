#include "App.hpp"

int main(int argc, char *argv[])
{
    unsigned int gridSize = 30;
    unsigned int rows = 20, columns = 10;
    App app(columns*gridSize, rows*gridSize, 60, gridSize);
    app.Run();

    return 0;
}