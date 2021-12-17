#ifndef CELL_H
#define CELL_H
#include "Includes.h"


class Cell
{
    bool free;

 public:
    Cell()
    {
        free=true;
    }

    bool is_free()
    { return free; }
    
    void set_free(bool free)
    { this->free=free; }
    
    friend ostream& operator<<(ostream& os,const Cell& c);
};

ostream& operator<<(ostream& os,const Cell& c)
{
    return os<< (c.free ? " ." : " *");
}

#endif
