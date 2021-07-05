#include "funcs.hpp"



int main()
{
    int height, width;


    std::cout << "**************************************************" << std::endl;
    std::cout << "      Welcome to John Conway's Game of Life!      " << std::endl;
    std::cout << "**************************************************" << std::endl << std::endl;
    std::cout << "Enter width and height of the playing field :\n";

    std::cin >> width >> height;



    gol::play(width,height);


    return 0;
}
