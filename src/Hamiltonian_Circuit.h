#ifndef HAMILTONIAN_CIRCUIT_H_INCLUDED
#define HAMILTONIAN_CIRCUIT_H_INCLUDED
#include "Includes.h"

class Hamiltonian_Circuit
{
    const Cell_To_Vars cell_to_vars;
    vector<Variable> variables;
    Permutations permutations;
    vector<Constraint> constraints;
    
 public:
    Hamiltonian_Circuit() : cell_to_vars{}, variables(cell_to_vars.get_nr_vars())
    {
    }
    
    bool step(Board& board)
    {
        return hamiltonian_cycle(board);
    }
    
    void draw([[maybe_unused]]const Window_Param& wp)
    {
        Col col=MyColor(255,165,0,255);
        Coord b=wp.border+wp.cell/2;
        CoorD w{2,2};
        for (int i=0;i<cell_to_vars.size();i++)
        {
            Coord c=xy(i)*wp.cell;
            Cell_To_Vars::Vars vars=cell_to_vars[i];
            if (variables[vars[Directions::left_index]].get_value())
            {
                boxColor(sdl()->renderer(), b.x+c.x-wp.cell.x, b.y+c.y-w.y,
                                            b.x+c.x,           b.y+c.y+w.y, col);
            }
            if (variables[vars[Directions::up_index]].get_value())
            {
                boxColor(sdl()->renderer(), b.x+c.x-w.x, b.y+c.y-wp.cell.y,
                                            b.x+c.x+w.x, b.y+c.y,           col);
            }
        }
    }

private:

    void clear_constraints()
    {
        constraints.clear();
    }
    
    void add_constraint(const Constraint& constraint)
    {
        for (auto i : constraint.get_var_indices())
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
            if (c.is_active())
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
        //cout<<"set_variable var:"<<var<<" value:"<<value<<'\n';
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

    vector<bool> get_values_sorted(int var_index,vector<Variable>& variables,vector<Constraint>& constraints)
    {
        static int draw_count=0;
        const Variable& variable=variables[var_index];
        auto constraint_indices=variable.get_constraint_indices();
        array<pair<bool,int>,2> value_perms;
        int max_perms=999;
        value_perms[0]={true,max_perms};
        value_perms[1]={false,max_perms};
        for (auto& value_perms : value_perms)
        {
            for (int ci : constraint_indices)
            {
                Constraint c=constraints[ci]; // copy
                if (!c.is_valid_value(value_perms.first))
                {
                    value_perms.second=-1;
                }
                else
                {
                    c.set_variable(var_index,value_perms.first);
                    c.update_nr_permutations(permutations);
                    int perms=c.get_nr_permutations();
                    if (perms<value_perms.second)
                        value_perms.second=perms;
                }
            }
        }
        if (value_perms[0]>value_perms[1] ||
            (value_perms[0]==value_perms[1] && ((++draw_count)%2)>0)) // alternate on draw 
            swap(value_perms[0],value_perms[1]);
        //cout<<"value_perms:"<<value_perms<<'\n';
        vector<bool> values;
        for (auto& value_perms : value_perms)
            if (value_perms.second<max_perms && value_perms.second>0)
                values.push_back(value_perms.first);
        return values;
    }
    
    bool solve(vector<Variable>& variables,vector<Constraint>& constraints,int depth)
    {
        cout<<"solve depth:"<<depth<<'\n';
        //cout<<*this;
        const auto [count, constraint]=get_lowest_contraint(constraints);
        cout<<"count:"<<count<<" constraint:"<<constraint<<'\n';
        if (count==0)
            return true;
        int var_index=constraint.get_var_indices().front();
        auto values=get_values_sorted(var_index,variables,constraints);
        cout<<"var_index:"<<var_index<<" values:"<<values<<'\n';
        if (values.size()==0)
            return false;
        for (auto value : values)
        {
            //cout<<"var_index:"<<var_index<<" v:"<<value<<'\n';
            auto undo_info=set_variable(variables,var_index,value,constraints);
            if (solve(variables,constraints,depth+1))
                return true;
            cout<<"undo:"<<undo_info<<'\n';
            undo(constraints,undo_info);
        }
        return false;
    }
    
    bool hamiltonian_cycle(const Board& board)
    {
        build_constraint_graph(board);
        cout<<*this;
        bool solved=solve(variables,constraints,0);
        cout<<*this;
        cout<<"SOLVED:"<<solved<<'\n';
        return true;
    }
    
    friend ostream& operator<<(ostream& os,const Hamiltonian_Circuit& h);
};

ostream& operator<<(ostream& os,[[maybe_unused]] const Hamiltonian_Circuit& h)
{
    //os<<h.cell_to_vars<<'\n';
    //os<<h.permutations<<'\n';
    os<<h.constraints<<'\n';
    //os<<h.variables<<'\n';
    return os;
}

#endif
