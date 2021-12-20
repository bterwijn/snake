#ifndef CELL_TO_VARS_H_INCLUDED
#define CELL_TO_VARS_H_INCLUDED
#include "Includes.h"

class Cell_To_Vars
{
 public:
    static constexpr int nr_directions=4;
    enum directions {left,up,right,down};
    using Vars = array<int,nr_directions>;
 private:
    array<Vars,width*height> cell_to_vars;
    
 public:
    Cell_To_Vars()
    {
        int var_index=0;
        for (int y=0;y<height;y++)
        {
            for (int x=0;x<width;x++)
            {
                Vars vars;
                if (x==0)
                    vars[left]=var_index++;
                else
                    vars[left]=cell_to_vars[index(x-1,y)][right];
                if (y==0)
                    vars[up]=var_index++;
                else
                    vars[up]=cell_to_vars[index(x,y-y)][down];
                vars[right]=var_index++;
                vars[down]=var_index++;
                cell_to_vars[index(x,y)]=vars;
            }
        }
    }

    const Vars& operator[](int i) const
    { return cell_to_vars[i]; }
    
    void draw(const Window_Param& wp)
    {
    }
    
    friend ostream& operator<<(ostream& os,const Cell_To_Vars& c);
};

ostream& operator<<(ostream& os,[[maybe_unused]] const Cell_To_Vars& c)
{
    for (int y=0;y<height;y++)
    {
        for (int x=0;x<width;x++)
        {
            int cell=index(x,y);
            cout<<"cell:"<<cell<<" "<<c.cell_to_vars[index(x,y)]<<'\n';
        }
    }
    return os;
}

#endif
