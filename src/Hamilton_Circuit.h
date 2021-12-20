#ifndef HAMILTON_CIRCUIT_H_INCLUDED
#define HAMILTON_CIRCUIT_H_INCLUDED
#include "Includes.h"

class Hamilton_Circuit
{
    Cell_To_Vars cell_to_vars;
    array<bool,width*height> vars;
    vector<Constraint> constraints;

    void build_constraint_graph(const Board& board)
    {
        constraints.clear();
        for (int y=0;y<height;y++)
        {
            for (int x=0;x<width;x++)
            {
                int connection_count=0;
                vector<int> vars;
                if (x>0)
                {
                    int i=index(x-1,y);
                    if (board.is_free_cell(i))
                    {
                        vars.push_back(cell_to_vars[i][Directions::left_index]);
                        connection_count++;
                    }
                }
                if (y>0)
                {
                    int i=index(x,y-1);
                    if (board.is_free_cell(i))
                    {
                        vars.push_back(cell_to_vars[i][Directions::up_index]);
                        connection_count++;
                    }
                }
                if (x<width-1)
                {
                    int i=index(x+1,y);
                    if (board.is_free_cell(i))
                    {
                        vars.push_back(cell_to_vars[i][Directions::right_index]);
                        connection_count++;
                    }
                }
                if (y<height-1)
                {
                    int i=index(x,y+1);
                    if (board.is_free_cell(i))
                    {
                        vars.push_back(cell_to_vars[i][Directions::down_index]);
                        connection_count++;
                    }
                }
            }
        }
    }
    
 public:
    Hamilton_Circuit()
    {
    }

    bool hamilton_cycle(const Board& board)
    {
        
    }
    
    void draw(const Window_Param& wp)
    {
    }
    
    friend ostream& operator<<(ostream& os,const Hamilton_Circuit& h);
};

ostream& operator<<(ostream& os,[[maybe_unused]] const Hamilton_Circuit& h)
{
    os<<h.cell_to_vars<<'\n';
    return os;
}

#endif
