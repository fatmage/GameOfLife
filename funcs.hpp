#ifndef FUNCS_HPP
#define FUNCS_HPP

#ifndef __unix__
#include <windows.h>
#endif // __unix__

#include <chrono>
#include <thread>
#include <iostream>


#define DELAY 250ms
#define GENERATIONS 500

namespace gol
{

void play(int width, int height);
void turn(byte current[], byte result[], int width, int height);


class draw
{
public:
    int width;
    int height;
    byte *board;


    draw(byte *board, int width, int height);
    friend std::ostream& operator<<(std::ostream& out, const gol::draw& dw);
};


}
#endif // FUNCS_HPP
