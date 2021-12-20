#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#include "Includes.h"

class Snake
{
    deque<int> indices;
    vector<int> tail_undo;
    
    void add_head(int index)
    { indices.push_back(index); }

    int remove_head()
    {
        int i=get_head();
        indices.pop_back();
        return i;
    }

    void add_tail(int index)
    { indices.push_front(index); }
    
    int remove_tail()
    {
        int i=get_tail();
        indices.pop_front();
        return i;
    }
    
 public:
    Snake()
    {
    }

    int step(int i,bool step_tail=true)
    {
        int tail=-1;
        add_head(i);
        if (step_tail)
            tail=remove_tail();
        tail_undo.push_back(tail);
        return tail;
    }

    pair<int,int> undo_step()
    {
        int head=-1,tail=-1;
        if (tail_undo.size()>0)
        {
            tail=tail_undo.back();
            tail_undo.pop_back();
            if (tail>=0)
                add_tail(tail);
            head=remove_head();
        }
        return {head,tail};
    }
    
    int get_head(int i=0) const
    { return indices[indices.size()-1-i]; }

    int get_tail(int i=0) const
    { return indices[i]; }
        
    int length() const
    { return indices.size(); }

    void draw(const Window_Param& wp)
    {
        if (indices.size()==0)
            return;
        Col green=MyColor(0,255,0,255);
        auto c1=xy(indices[0]);
        CoorD w=wp.cell/4;
        Coord b=wp.border+wp.cell/2;
        for (size_t i=1;i<indices.size();i++)
        {
            auto c2=xy(indices[i]);
            int x1=c1.x*wp.cell.x;
            int x2=c2.x*wp.cell.x;
            if (x2<x1) swap(x1,x2);
            int y1=c1.y*wp.cell.y;
            int y2=c2.y*wp.cell.y;
            if (y2<y1) swap(y1,y2);
            boxColor(sdl()->renderer(), b.x+x1-w.x, b.y+y1-w.y,
                                        b.x+x2+w.x, b.y+y2+w.y, green);
            c1=c2;
        }
        Col light_green=MyColor(100,255,100,255);
        auto p=c1*wp.cell;
        w=wp.cell/2.7;
        filledEllipseColor(sdl()->renderer(), b.x+p.x, b.y+p.y,
                                              w.x    , w.y    , light_green);
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
