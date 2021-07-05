#include "funcs.hpp"



int main()
{
    int height, width;
    
    #ifdef __unix__
    std::cout << "\u001b[2J\033[0;0H\033[0;0H";
    #endif // __unix__
    #ifndef __unix__
    system("CLS");
    #endif // __unix__
    

    std::cout << "********************************************************" << std::endl;
    std::cout << "         Welcome to John Conway's Game of Life!      " << std::endl;
    std::cout << "********************************************************" << std::endl << std::endl;
    std::cout << "Enter width and height of the playing field :\n";

    std::cin >> width >> height;


    gol::play(width,height);


    return 0;
}
