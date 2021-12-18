#ifndef UTILS_H
#define UTILS_H
#include "Includes.h"

constexpr int width{10};
constexpr int height{10};

int index(int x,int y)
{ return x+y*width; }

struct Coord
{
    int x,y;

    int square_length()
    { return x*x+y*y; }
};

Coord operator+(const Coord& c1,const Coord& c2)
{ return Coord{c1.x+c2.x,c1.y+c2.y}; }

Coord operator-(const Coord& c1,const Coord& c2)
{ return Coord{c1.x-c2.x,c1.y-c2.y}; }

Coord xy(int index)
{ return {index%width, index/width}; }

int square_distance(int index1,int index2)
{
    Coord c1=xy(index1);
    Coord c2=xy(index2);
    return (c1-c2).square_length();
}

int distance(int index1,int index2)
{ return square_distance(index1,index2);}

struct Window_Param
{
    int border,width,height,cell_width,cell_height;
};

Window_Param window_param()
{
    Window_Param wp;
    wp.border=10;
    sdl()->getSize(wp.width,wp.height);
    wp.cell_width=(wp.width-wp.border*2)/width;
    wp.cell_height=(wp.height-wp.border*2)/height;
    return wp;
}

void press_enter()
{
    cout<<"hit ENTER";cin.get();
}

template<class T>
ostream& operator<<(ostream& os,const vector<T>& v)
{
    for (auto i : v)
        os<<i<<' ';
    return os;
}

template<class K,class V>
ostream& operator<<(ostream& os,const unordered_map<K,V>& v)
{
    for (auto i : v)
        os<<i.first<<':'<<i.second<<' ';
    return os;
}


#endif
