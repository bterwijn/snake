#ifndef HAMILTON_CIRCUIT_H_INCLUDED
#define HAMILTON_CIRCUIT_H_INCLUDED
#include "Includes.h"

class Hamilton_Circuit
{
    using Constrait_Queue=priority_queue<Constraint,
                                     vector<Constraint>,
                                     greater<Constraint> >;
    
    Cell_To_Vars cell_to_vars;
    array<bool,width*height> vars;
    Constrait_Queue constraints;

    Constraint build_constraint_graph(const Board& board,Coord c,bool check_head_tail_move=true,int fixed_connections=0)
    {
        int cell_index=index(c);
        vector<int> vars;
        for (int d=0;d<Directions::nr_directions;d++)
        {
            auto neigbor=c+Directions::directions[d];
            if (is_on_board(neigbor))
            {
                int neigbor_index=index(neigbor);
                bool is_head_tail_move=(check_head_tail_move &&
                                        (neigbor_index==board.get_head() || neigbor_index==board.get_tail()));
                if (board.is_free_cell(neigbor_index) || is_head_tail_move)
                {
                    vars.push_back(cell_to_vars[cell_index][d]);
                }
            }
        }
        return Constraint(vars,2-fixed_connections);
    }
    
    void build_constraint_graph(const Board& board)
    {
        constraints=Constrait_Queue{};
        for (int y=0;y<height;y++)
        {
            for (int x=0;x<width;x++)
            {
                Constraint c=build_constraint_graph(board,Coord(x,y));
                constraints.push(c);
            }
        }
        if (board.snake_length()==1)
        {
            Constraint head=build_constraint_graph(board,xy(board.get_head()),false);
            constraints.push(head);
        }
        else
        {
            Constraint head=build_constraint_graph(board,xy(board.get_head()),false,1);
            constraints.push(head);
            Constraint tail=build_constraint_graph(board,xy(board.get_tail()),false,1);
            constraints.push(tail);
        }
    }

    bool hamilton_cycle(const Board& board)
    {
        build_constraint_graph(board);
        return true;
    }
    
 public:
    Hamilton_Circuit()
    {
    }
    
    bool step(Board& board)
    {
        return hamilton_cycle(board);
    }
    
    void draw(const Window_Param& wp)
    {
    }
    
    friend ostream& operator<<(ostream& os,const Hamilton_Circuit& h);
};

ostream& operator<<(ostream& os,[[maybe_unused]] const Hamilton_Circuit& h)
{
    os<<h.cell_to_vars<<'\n';
    os<<h.constraints<<'\n';
    return os;
}

#endif
