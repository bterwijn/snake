#ifndef HAMILTON_CIRCUIT_H_INCLUDED
#define HAMILTON_CIRCUIT_H_INCLUDED
#include "Includes.h"

class Hamilton_Circuit
{
    const Cell_To_Vars cell_to_vars;
    vector<Variable> variables;
    Permutations permutations;
    vector<Constraint> constraints;
    
 public:
    Hamilton_Circuit() : cell_to_vars{}, variables(cell_to_vars.get_nr_vars())
    {
    }
    
    bool step(Board& board)
    {
        return hamilton_cycle(board);
    }
    
    void draw([[maybe_unused]]const Window_Param& wp)
    {
    }

private:

    void clear_constraints()
    {
        constraints.clear();
    }
    
    void add_constraint(const Constraint& constraint)
    {
        for (auto i : constraint.get_vars())
            variables[i].add_constraint_index(constraints.size());
        constraints.push_back(constraint);
    }
    
    Constraint build_constraint(const Board& board,Coord cell,bool check_head_tail_move=true,int fixed_connections=0)
    {
        int cell_index=index(cell);
        vector<int> vars;
        for (int d=0;d<Directions::nr_directions;d++)
        {
            auto neigbor=cell+Directions::directions[d];
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
        return Constraint(constraints.size(),vars,2-fixed_connections,permutations);
    }
    
    void build_constraint_graph(const Board& board)
    {
        clear_constraints();
        bool snake=board.snake_length()>0;
        for (int y=0;y<height;y++)
        {
            for (int x=0;x<width;x++)
            {
                auto cell=Coord(x,y);
                if (board.is_free_cell(cell))
                    add_constraint(build_constraint(board,cell,snake));
            }
        }
        if (snake)
        {
            if (board.snake_length()==1)
            {
                add_constraint(build_constraint(board,xy(board.get_head()),false));
            }
            else
            {
                add_constraint(build_constraint(board,xy(board.get_head()),false,1));
                add_constraint(build_constraint(board,xy(board.get_tail()),false,1));
            }
        }
    }

    pair<int,Constraint> get_lowest_contraint(const vector<Constraint>& constraints)
    {
        Constraint best;
        int count=0;
        for (const auto& c:constraints)
        {
            if (c.get_vars().size()>0)
            {
                if (count==0 || c<best)
                    best=c;
                count++;
            }
        }
        return pair<int,Constraint>(count,best);
    }

    vector<Constraint> set_variable(vector<Variable>& variables,int var,bool value,vector<Constraint>& constraints)
    {
        Variable& variable=variables[var];
        variable.set_value(value);
        vector<Constraint> undo;
        for (int ci : variable.get_constraint_indices())
        {
            undo.push_back(constraints[ci]);
            constraints[ci].set_variable(var,value);
            constraints[ci].update_nr_permutations(permutations);
        }
        return undo;
    }

    void undo(vector<Constraint>& constraints,const vector<Constraint>& undo_info)
    {
        for (const auto& c : undo_info)
            constraints[c.get_index()]=c;
    }
    
    bool solve(vector<Variable>& variables,vector<Constraint>& constraints)
    {
        cout<<*this;
        auto count_best=get_lowest_contraint(constraints);
        cout<<"count_best:"<<count_best<<'\n';
        if (count_best.first==0)
            return true;
        Constraint& constraint=count_best.second;
        if (count_best.first>0)
        {
            for (auto var : constraint.get_vars())
            {
                for (auto value : constraint.get_values())
                {
                    auto undo_info=set_variable(variables,var,value,constraints);
                    if (solve(variables,constraints))
                        return true;
                    undo(constraints,undo_info);
                }
            }
        }
        return false;
    }
    
    bool hamilton_cycle(const Board& board)
    {
        build_constraint_graph(board);
        solve(variables,constraints);
        return true;
    }
    
    friend ostream& operator<<(ostream& os,const Hamilton_Circuit& h);
};

ostream& operator<<(ostream& os,[[maybe_unused]] const Hamilton_Circuit& h)
{
    //os<<h.cell_to_vars<<'\n';
    os<<h.constraints<<'\n';
    os<<h.variables<<'\n';
    return os;
}

#endif
