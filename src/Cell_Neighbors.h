#ifndef CELL_NEIGHBORS_H
#define CELL_NEIGHBORS_H
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
                int i=index(x,y);
                for (int dy=-1;dy<=1;dy+=2)
                {
                    int ny=y+dy;
                    if (ny>=0 && ny<height)
                    {
                        int n=index(x,ny);
                        add(i,n);
                    }
                }
                for (int dx=-1;dx<=1;dx+=2)
                {
                    int nx=x+dx;
                    if (nx>=0 && nx<width)
                    {
                        int n=index(nx,y);
                        add(i,n);
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
