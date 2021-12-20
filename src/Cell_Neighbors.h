#ifndef CELL_NEIGHBORS_H_INCLUDED
#define CELL_NEIGHBORS_H_INCLUDED
#include "Includes.h"

class Cell_Neighbors
{
    array< vector<int>, width*height> neighbors;
    
 public:
    Cell_Neighbors()
    {
        for (int y=0;y<height;y++)
        {
            for (int x=0;x<width;x++)
            {
                Coord c=Coord(x,y);
                int ci=index(c);
                for (int d=0;d<Directions::nr_directions;d++)
                {
                    auto neigbor=c+Directions::directions[d];
                    if (is_on_board(neigbor))
                    {
                        add(ci,index(neigbor));
                    }
                }                
            }
        }
    }
    
    void add(int index,int neighbor)
    { neighbors[index].push_back(neighbor); }

    const vector<int>& operator[](int index) const
    { return neighbors[index]; }

    friend ostream& operator<<(ostream& os,const Cell_Neighbors& c);
};

ostream& operator<<(ostream& os,const Cell_Neighbors& c)
{
    for (int i=0;i<width*height;i++)
    {
        os<<i<<": ";
        for (auto n: c[i])
            os<<n<<' ';
        os<<'\n';
    }
    return os;
}

#endif
