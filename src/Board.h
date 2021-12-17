#ifndef BOARD_H
#define BOARD_H
#include "Includes.h"

class Board
{
    Cells cells;
    Cell_Neighbors cell_neighbors;
    Snake snake;
    
 public:
    Board()
    {
        int si=rand()%(width*height);
        snake.add_head(si);
        auto s=xy(si);
        si=index(s.x+1,s.y);
        snake.add_head(si);
        s=xy(si);
        si=index(s.x,s.y+1);
        snake.add_head(si);
    }
    
    void draw(const Window_Param& wp)
    {
        cells.draw(wp);
        snake.draw(wp);
    }
    
    friend ostream& operator<<(ostream& os,const Board& b);
};

ostream& operator<<(ostream& os,const Board& b)
{
    return os<<b.cells;
}

#endif
