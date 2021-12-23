#ifndef CELL_TO_VARS_H_INCLUDED
#define CELL_TO_VARS_H_INCLUDED
#include "Includes.h"

class Cell_To_Vars
{
    using Vars = array<int,Directions::nr_directions>;
    array<Vars,width*height> cell_to_vars;
    int var_index=0;
    
 public:
    Cell_To_Vars()
    {
        for (int y=0;y<height;y++)
        {
            for (int x=0;x<width;x++)
            {
                Vars vars;
                if (x==0)
                    vars[Directions::left_index]=var_index++;
                else
                    vars[Directions::left_index]=cell_to_vars[index(x-1,y)][Directions::right_index];
                if (y==0)
                    vars[Directions::up_index]=var_index++;
                else
                    vars[Directions::up_index]=cell_to_vars[index(x,y-1)][Directions::down_index];
                vars[Directions::right_index]=var_index++;
                vars[Directions::down_index]=var_index++;
                cell_to_vars[index(x,y)]=vars;
            }
        }
    }

    int get_nr_vars() const
    { return var_index; }
    
    const Vars& operator[](int i) const
    { return cell_to_vars[i]; }
    
    friend ostream& operator<<(ostream& os,const Cell_To_Vars& c);
};

ostream& operator<<(ostream& os,[[maybe_unused]] const Cell_To_Vars& c)
{
    for (int y=0;y<height;y++)
    {
        for (int x=0;x<width;x++)
        {
            int cell=index(x,y);
            cout<<"cell:"<<cell<<" vars:"<<c.cell_to_vars[index(x,y)]<<'\n';
        }
    }
    return os;
}

#endif
