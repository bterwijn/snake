#include "Utils.h"

class Snake
{
    deque<int> indices;

 public:
    Snake()
    {
    }

    void add(int index)
    { indices.push_back(index); }

    void remove()
    { indices.pop_front(); }
    
    friend ostream& operator<<(ostream& os,const Snake& s);
};

ostream& operator<<(ostream& os,const Snake& s)
{
    for (auto i: s.indices)
        os<< i <<' ';
    return os;
}
