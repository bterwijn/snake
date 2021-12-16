#include "Cell.h"

template <int width, int height>
class Board
{
    std::array<Cell, width*height> free;

 public:
    Board()
    {

    }

    Cell& operator[](int i)
    { return free[i]; }

    const Cell& operator[](int i) const
    { return free[i]; }

    int index(int y,int x) const
    { return y*width+x; }

    template <int w, int h>
    friend ostream& operator<<(ostream& os,const Board<w,h>& b);
};

template <int width, int height>
ostream& operator<<(ostream& os,const Board<width,height>& b)
{
    for (int y=0;y<height;y++)
    {
        for (int x=0;x<width;x++)
            os<<b[b.index(y,x)];
        os<<'\n';
    }
    return os;
}
