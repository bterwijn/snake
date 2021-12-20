#ifndef CELLS_H_INCLUDED
#define CELLS_H_INCLUDED
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

    vector<int> filter_free(const vector<int>& cells) const
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
                      wp.border.x,wp.border.x+y*wp.cell.y,
                      wp.window.x-wp.border.x,wp.border.y+y*wp.cell.y, white); // draw line
        for (int x=0;x<width+1;x++)
            lineColor(sdl()->renderer(),
                      wp.border.x+x*wp.cell.x,wp.border.y,
                      wp.border.x+x*wp.cell.x,wp.window.y-wp.border.y, white); // draw line
    }

    void draw_non_free(const Window_Param& wp)
    {
        Col blue=MyColor(0,0,255,255);
        Coord b=wp.border+wp.cell/2;
        CoorD w=wp.cell/4;
        for (int y=0;y<width;y++)
        {
            for (int x=0;x<width;x++)
            {
                if (!cells[index(x,y)].is_free())
                {
                    auto p=Coord{x,y}*wp.cell;
                    filledEllipseColor(sdl()->renderer(), b.x+p.x ,b.y+p.y,
                                       (int)(w.x)     ,(int)(w.y)    , blue);
                }
            }
        }
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
