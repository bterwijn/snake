#ifndef UTILS_H
#define UTILS_H
#include "Includes.h"

constexpr int width{10};
constexpr int height{10};

int index(int x,int y)
{ return x+y*width; }

struct Coord
{
    int x,y;
};

Coord xy(int index)
{ return {index%width, index/width}; }

struct Window_Param
{
    int border,width,height,cell_width,cell_height;
};

Window_Param window_param()
{
    Window_Param wp;
    wp.border=10;
    sdl()->getSize(wp.width,wp.height);
    wp.cell_width=(wp.width-wp.border*2)/width;
    wp.cell_height=(wp.height-wp.border*2)/height;
    return wp;
}

#endif
