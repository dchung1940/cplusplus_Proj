#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze m;
    m.makeMaze(88,52);
    PNG png;
    png.readFromFile("background.png");
    PNG creative = m.drawCreativeMaze(png);
    creative.writeToFile("creative.png");
    // delete creative;
    std::cout << "make Creative.png complete" << std::endl;

    // cout << "Add your own tests here! Modify main.cpp" << endl;
    return 0;
}
