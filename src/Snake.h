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
    
    friend ostream& operator<<(ostream& os,const Snake& s);
};

ostream& operator<<(ostream& os,const Snake& s)
{
    for (auto i: s.indices)
        os<< i <<' ';
    return os;
}

#endif
