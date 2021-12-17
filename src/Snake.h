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

    int get_head()
    { return indices.back(); }

    int get_tail()
    { return indices.front(); }
        
    void add_head(int index)
    { indices.push_back(index); }

    int remove_tail()
    {
        int i=get_tail();
        indices.pop_front();
        return i;
    }

    int length()
    { return indices.size(); }

    void draw(const Window_Param& wp)
    {
        if (indices.size()==0)
            return;
        Col green=MyColor(0,255,0,255);
        auto c1=xy(indices[0]);
        int w=wp.cell_height/4;
        if (indices.size()==1)
        {
            int x1=wp.border+wp.cell_width/2+c1.x*wp.cell_width;
            int y1=wp.border+wp.cell_height/2+c1.y*wp.cell_height;
            boxColor(sdl()->renderer(),x1-w,y1-w,x1+w,y1+w,green);
        }
        else
        {
            for (size_t i=1;i<indices.size();i++)
            {
                auto c2=xy(indices[i]);
                int x1=wp.border+wp.cell_width/2+c1.x*wp.cell_width;
                int x2=wp.border+wp.cell_width/2+c2.x*wp.cell_width;
                if (x2<x1) swap(x1,x2);
                int y1=wp.border+wp.cell_height/2+c1.y*wp.cell_height;
                int y2=wp.border+wp.cell_height/2+c2.y*wp.cell_height;
                if (y2<y1) swap(y1,y2);
                boxColor(sdl()->renderer(),x1-w,y1-w,x2+w,y2+w,green);
                c1=c2;
            }
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
