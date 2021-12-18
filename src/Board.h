#ifndef BOARD_H
#define BOARD_H
#include "Includes.h"

class Board
{
    Cells cells;
    Cell_Neighbors cell_neighbors;
    Snake snake;
    A_Star a_star;

    void snake_step_head(int i)
    {
        snake.add_head(i);
        cells[i].set_free(false);
    }

    int snake_step_tail()
    {
        int i=snake.remove_tail();
        cells[i].set_free(true);
        return i;
    }
    
 public:
    Board()
    {
        int si=rand()%(width*height);
        snake_step_head(si);
    }
    
    void step()
    {
        int head=snake.get_head();
        auto neighbors=cells.filter_free(cell_neighbors[head]);
        if (neighbors.size()>0)
        {
            int r=neighbors[rand()%neighbors.size()];
            snake_step_head(r);
            if (snake.length()>5)
                snake_step_tail();
        }

        {
            int head=snake.get_head();
            int tail=snake.get_tail();
            auto neighbors=cells.filter_free(cell_neighbors[head]);
            cout<<"head:"<<head<<"neighbors:"<<neighbors<<'\n';
            a_star.plan_path(cells,cell_neighbors,tail,head,neighbors);
        }
    }
    
    void draw(const Window_Param& wp)
    {
        snake.draw(wp);
        cells.draw(wp);
        a_star.draw(wp);
    }
    
    friend ostream& operator<<(ostream& os,const Board& b);
};

ostream& operator<<(ostream& os,const Board& b)
{
    return os<<b.cells;//<<'\n'<<b.cell_neighbors;
}

#endif
