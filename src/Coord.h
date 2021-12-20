#ifndef COORD_H_INCLUDED
#define COORD_H_INCLUDED
#include "Includes.h"

template<class T>
struct CoordT
{
    T x,y;

 public:
    constexpr CoordT(T x,T y) : x{x},y{y}
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

using Coord = CoordT<int>;
using CoorD = CoordT<double>;

template<class T,class D>
CoordT<T>& operator+=(CoordT<T>& c1,const CoordT<D>& c2)
{
    c1.x+=c2.x;
    c1.y+=c2.y; 
    return c1;
}

template<class T,class D>
CoordT<T>& operator-=(CoordT<T>& c1,const CoordT<D>& c2)
{
    c1.x-=c2.x;
    c1.y-=c2.y; 
    return c1;
}

template<class T,class D>
CoordT<T> operator+(const CoordT<T>& c1,const CoordT<D>& c2)
{
    CoordT r=c1;
    return r+=c2;
}

template<class T,class D>
CoordT<T> operator-(const CoordT<T>& c1,const CoordT<D>& c2)
{
    CoordT r=c1;
    return r-=c2;
}

template<class T>
ostream& operator<<(ostream& os,[[maybe_unused]] const CoordT<T>& c)
{
    os<<c.x<<','<<c.y;
    return os;
}

#endif
