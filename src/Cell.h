#include "Utils.h"

class Cell
{
    bool free;

 public:
    Cell()
    {
        free=true;
    }

    friend ostream& operator<<(ostream& os,const Cell& c);
};

ostream& operator<<(ostream& os,const Cell& c)
{
    return os<< (c.free ? " ." : " *");
}
