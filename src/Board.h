#ifndef BOARD_H
#define BOARD_H
#include "Includes.h"

template <int width, int height>
class Board
{
    Cells<width,height> cells;
    Cell_Neighbors<width,height> cell_neighbors;
    Snake snake;
    
 public:
    Board()
    {
        
    }
    
    void draw()
    {
        cells.draw();
    }
    
    template <int w, int h>
    friend ostream& operator<<(ostream& os,const Board<w,h>& b);
};

template <int width, int height>
ostream& operator<<(ostream& os,const Board<width,height>& b)
{
    return os<<b.cells;
}

#endif
