#ifndef CELLS_H
#define CELLS_H
#include "Includes.h"

class Cells
{
    std::array<Cell,width*height> cells;
    
 public:
    Cells()
    {
        
    }
    
    Cell& operator[](int i)
    { return cells[i]; }

    const Cell& operator[](int i) const
    { return cells[i]; }

    vector<int> filter_free(const vector<int>& cells)
    {
        vector<int> free;
        for (int i : cells)
            if (((*this)[i]).is_free())
                free.push_back(i);
        return free;
    }
    
    void draw(const Window_Param& wp)
    {
        Col white=MyColor(255,255,255,255);
        for (int y=0;y<width+1;y++)
            lineColor(sdl()->renderer(),
                      wp.border,wp.border+y*wp.cell_height,
                      wp.width-wp.border,wp.border+y*wp.cell_height, white); // draw line
        for (int x=0;x<width+1;x++)
            lineColor(sdl()->renderer(),
                      wp.border+x*wp.cell_width,wp.border,
                      wp.border+x*wp.cell_width,wp.height-wp.border, white); // draw line
    }
    
    friend ostream& operator<<(ostream& os,const Cells& c);
};

ostream& operator<<(ostream& os,const Cells& c)
{
    for (int y=0;y<height;y++)
    {
        for (int x=0;x<width;x++)
            os<<c[index(x,y)];
        os<<'\n';
    }
    return os;
}

#endif
