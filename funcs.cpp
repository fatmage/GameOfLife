#include "funcs.hpp"




gol::draw::draw(byte* board, int width, int height)
{
    // this->board = new int[width*height];
    this->board = board;
    this->width = width;
    this->height = height;
}

namespace gol
{

std::ostream& operator<<(std::ostream& out, const gol::draw& dw)
{
#ifndef __unix__
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif // __unix__

#ifdef __unix__
#endif // __unix__

    for(int y = 0; y < dw.height; y++)
    {
        for(int x = 0; x < dw.width; x++)
        {
#ifdef __unix___
            if(dw.board[y*dw.width+x])
                out << "\033[48;5;180m";

            out << "  ";
            out << "\u001b[0m";
#endif // __unix___

#ifndef __unix___
            if(dw.board[y*dw.width+x])
                SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);

            out << "  ";
            SetConsoleTextAttribute(hConsole, 0x7);
#endif // __unix___
        }
        out << "\n";
    }

    return out;
}
}


void gol::turn(byte current[], byte result[], int width, int height)
{
    int neighbours=0;

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            neighbours=0;

            if(y-1>=0)
            {
                neighbours+=current[(y-1)*width+x];
                if(x-1>=0)
                    neighbours+=current[(y-1)*width+x-1];
                if(x+1<width)
                    neighbours+=current[(y-1)*width+x+1];
            }

            if(y+1<height)
            {
                neighbours+=current[(y+1)*width+x];
                if(x-1>=0)
                    neighbours+=current[(y+1)*width+x-1];
                if(x+1<width)
                    neighbours+=current[(y+1)*width+x+1];
            }

            if(x-1>=0)
                neighbours+=current[y*width+x-1];

            if(x+1<width)
                neighbours+=current[y*width+x+1];

            if(current[y*width+x])
            {
                if(neighbours==2 || neighbours==3)
                    result[y*width+x]=1;
                else
                    result[y*width+x]=0;
            }
            else
            {
                if(neighbours==3)
                    result[y*width+x]=1;
                else
                    result[y*width+x]=0;
            }
        }

    }

#ifdef __unix__
    std::cout << "costam";
#endif // __unix__
#ifndef __unix__
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD start;
    start.X=0;
    start.Y=0;
    SetConsoleCursorPosition(hConsole, start);
#endif // __unix__
    std::cout << gol::draw(result,width,height);
}



auto now()
{
    return std::chrono::steady_clock::now();
}

auto awake_time()
{
    using std::chrono::operator""ms;
    return now() + DELAY;
}

void gol::play(int width, int height)
{

    // Hiding the cursor to smoothen the displaying
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO curs;
    curs.dwSize = 100;
    curs.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &curs);

    // Create game grids and initialize the first one with random values
    byte *board1 = new byte[width*height];
    byte *board2 = new byte[width*height];

    srand(time(NULL));

    for(int i=0; i<width*height; i++)
        board1[i]=rand()%2;


     /**
     *** Gosper Glider Gun in the left corner
     **/

     /*
     memset(board1,0,width*height*sizeof(byte));

     board1[24]=1;
     board1[1*width+24]=1;
     board1[1*width+22]=1;
     board1[2*width+12]=1;
     board1[2*width+13]=1;
     board1[2*width+20]=1;
     board1[2*width+21]=1;
     board1[2*width+34]=1;
     board1[2*width+35]=1;
     board1[3*width+11]=1;
     board1[3*width+15]=1;
     board1[3*width+20]=1;
     board1[3*width+21]=1;
     board1[3*width+34]=1;
     board1[3*width+35]=1;
     board1[4*width+0]=1;
     board1[4*width+1]=1;
     board1[4*width+10]=1;
     board1[4*width+16]=1;
     board1[4*width+20]=1;
     board1[4*width+21]=1;
     board1[5*width+0]=1;
     board1[5*width+1]=1;
     board1[5*width+10]=1;
     board1[5*width+14]=1;
     board1[5*width+16]=1;
     board1[5*width+17]=1;
     board1[5*width+22]=1;
     board1[5*width+24]=1;
     board1[6*width+10]=1;
     board1[6*width+16]=1;
     board1[6*width+24]=1;
     board1[7*width+11]=1;
     board1[7*width+15]=1;
     board1[8*width+12]=1;
     board1[8*width+13]=1;
     */

#ifdef __unix__
     std::cout<<"\u001b[2J\033[0;0H\033[0;0H";
#endif // __unix__
#ifndef __unix__
    system("CLS");
#endif // __unix__


    std::cout << gol::draw(board1,width,height);

    for(int i=0; i<GENERATIONS; i++)
    {
        // Starting the minimal delay timer
        auto timer = awake_time();

        if(i%2)
            gol::turn(board2,board1,width,height);
        else
            gol::turn(board1,board2,width,height);

        // Waiting for the minimal delay timer
        std::this_thread::sleep_until(timer);
    }


    delete[] board1;
    delete[] board2;
}


