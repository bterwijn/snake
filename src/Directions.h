#ifndef DIRECTIONS_H_INCLUDED
#define DIRECTIONS_H_INCLUDED
#include "Includes.h"

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

#endif
