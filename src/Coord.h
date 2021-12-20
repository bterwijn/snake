#ifndef COORD_H_INCLUDED
#define COORD_H_INCLUDED
#include "Includes.h"

struct Coord
{
    int x,y;

 public:
    constexpr Coord(int x,int y) : x{x},y{y}
    { }

    constexpr int operator[](int i) const
    {
        switch(i)
        {
        case 0: return x;
        case 1: return y;
        }
        return -1;
    }

    constexpr int square_length() const
    { return x*x+y*y; }

};

struct Directions
{
    static constexpr int nr_directions=4;
    static constexpr Coord left{-1,0};
    static constexpr Coord up{0,-1};
    static constexpr Coord right{+1,0};
    static constexpr Coord down{0,+1};
    enum directions {left_index,up_index,right_index,down_index};
    static constexpr array<Coord,Directions::nr_directions> directions={left,up,right,down};
    constexpr const Coord& operator[](int i)
    { return Directions::directions[i];}
};
    
Coord& operator+=(Coord& c1,const Coord& c2)
{
    c1.x+=c2.x;
    c1.y+=c2.y; 
    return c1;
}

Coord& operator-=(Coord& c1,const Coord& c2)
{
    c1.x-=c2.x;
    c1.y-=c2.y; 
    return c1;
}
    
Coord operator+(const Coord& c1,const Coord& c2)
{
    Coord r=c1;
    return r+=c2;
}

Coord operator-(const Coord& c1,const Coord& c2)
{
    Coord r=c1;
    return r-=c2;
}

ostream& operator<<(ostream& os,[[maybe_unused]] const Coord& c)
{
    os<<c.x<<','<<c.y;
    return os;
}

#endif
