#ifndef CELLS_H
#define CELLS_H
#include "Includes.h"

template <int width, int height>
class Cells
{
    std::array<Cell, width*height> cells;
    
 public:
    Cells()
    {
        
    }
    
    Cell& operator[](int i)
    { return cells[i]; }

    const Cell& operator[](int i) const
    { return cells[i]; }

    int index(int y,int x) const
    { return index_helper(y,x,width); }

    void draw()
    {
        int w,h;
        sdl()->getSize(w,h);
        int border=20;
        int cell_width=(w-border*2)/width;
        int cell_height=(h-border*2)/height;
        Col white=MyColor(255,255,255,255);
        for (int y=0;y<width+1;y++)
            lineColor(sdl()->renderer(),border,border+y*cell_height,w-border,border+y*cell_height, white); // draw line
        for (int x=0;x<width+1;x++)
            lineColor(sdl()->renderer(),border+x*cell_width,border,border+x*cell_width,h-border, white); // draw line
    }
    
    template <int w, int h>
    friend ostream& operator<<(ostream& os,const Cells<w,h>& c);
};

template <int width, int height>
ostream& operator<<(ostream& os,const Cells<width,height>& c)
{
    for (int y=0;y<height;y++)
    {
        for (int x=0;x<width;x++)
            os<<c[c.index(y,x)];
        os<<'\n';
    }
    return os;
}

#endif
