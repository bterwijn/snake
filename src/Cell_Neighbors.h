#include "Utils.h"

int index_helper(int y,int x,int width)
{ return y*width+x; }

template <int width,int height>
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
                int i=index(y,x);
                for (int dy=-1;dy<=1;dy+=2)
                {
                    int ny=y+dy;
                    if (ny>0 && ny<height)
                    {
                        int n=index(ny,x);
                        add(i,n);
                    }
                }
                for (int dx=-1;dx<=1;dx+=2)
                {
                    int nx=x+dx;
                    if (nx>0 && nx<width)
                    {
                        int n=index(y,nx);
                        add(i,n);
                    }
                }
            }
        }
    }

    int index(int y,int x) const
    { return index_helper(y,x,width); }
    
    void add(int index,int neighbor)
    { neighbors[index].push_back(neighbor); }

    const vector<int>& operator[](int index) const
    { return neighbors[index]; }

    template <int w,int h>
    friend ostream& operator<<(ostream& os,const Cell_Neighbors<w,h>& c);
};

template <int width,int height>
ostream& operator<<(ostream& os,const Cell_Neighbors<width,height>& c)
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
