#ifndef SNAKE_H
#define SNAKE_H
#include "Includes.h"

class Snake
{
    deque<int> indices;

 public:
    Snake()
    {
    }

    void add_head(int index)
    { indices.push_back(index); }

    int remove_tail()
    {
        int i=indices.front();
        indices.pop_front();
        return i;
    }

    int length()
    { return indices.size(); }

    void draw(const Window_Param& wp)
    {
        Col green=MyColor(0,255,0,255);
        auto c1=xy(indices[0]);
        for (size_t i=1;i<indices.size();i++)
        {
            auto c2=xy(indices[i]);
            lineColor(sdl()->renderer(),
                      wp.border+wp.cell_width/2+c1.x*wp.cell_width, wp.border+wp.cell_height/2+c1.y*wp.cell_height,
                      wp.border+wp.cell_width/2+c2.x*wp.cell_width, wp.border+wp.cell_height/2+c2.y*wp.cell_height, green); // draw line
            c1=c2;
        }
    }
    
    friend ostream& operator<<(ostream& os,const Snake& s);
};

ostream& operator<<(ostream& os,const Snake& s)
{
    for (auto i: s.indices)
        os<< i <<' ';
    return os;
}

#endif
