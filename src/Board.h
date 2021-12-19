#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include "Includes.h"

class Board
{
    int step_count=0;
    Snake snake;
    Cells cells;
    Cell_Neighbors cell_neighbors;
    //A_Star a_star;

    void step_helper(int i,bool step_tail=true)
    {
        int tail=snake.step(i,step_tail);
        cells[i].set_free(false);
        if (tail>=0)
            cells[tail].set_free(true);
    }
    
 public:
    Board()
    {
        int i=rand()%(width*height);
        step_helper(i,false);
    }

    int get_head(int i=0) const
    { return snake.get_head(i); }

    int get_tail(int i=0) const
    { return snake.get_tail(i); }

    int snake_length() const
    { return snake.length(); }

    bool is_free_cell(int i)
    { return cells[i].is_free(); }

    const vector<int>& get_neighbors(int i)
    { return cell_neighbors[i]; }
        
    vector<int> get_free_neighbors(int i)
    { return cells.filter_free(cell_neighbors[i]); }

    void step(int i)
    { step_helper(i,snake_length()>width*height*0.8); }
    
    void undo_step()
    {
        auto[head,tail]=snake.undo_step();
        if (head>=0)
            cells[head].set_free(true);
        if (tail>=0)
            cells[tail].set_free(false);
    }
    
    void step()
    {
        step_count++;
        int fase=20;
        if ((step_count%fase)<(fase/2))
        {
            if (snake.length()>0)
            {
                int head=snake.get_head();
                auto neighbors=cells.filter_free(cell_neighbors[head]);
                if (neighbors.size()>0)
                {
                    int i=neighbors[rand()%neighbors.size()];
                    step_helper(i,snake.length()>5);
                }
            }
        }
        else
        {
            if (snake.length()>1)
                undo_step();
        }
        
        /*
        {
            int head=snake.get_head();
            int tail=snake.get_tail();
            auto neighbors=cells.filter_free(cell_neighbors[head]);
            cout<<"head:"<<head<<"neighbors:"<<neighbors<<'\n';
            //a_star.plan_path(cells,cell_neighbors,tail,head,neighbors);
        }
        */
    }
    
    void draw(const Window_Param& wp)
    {
        cells.draw(wp);
        snake.draw(wp);
        //cells.draw_non_free(wp);
        //a_star.draw(wp);
    }
    
    friend ostream& operator<<(ostream& os,const Board& b);
};

ostream& operator<<(ostream& os,const Board& b)
{
    return os<<b.cells;//<<'\n'<<b.cell_neighbors;
}

#endif
