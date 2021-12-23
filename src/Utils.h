#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include "Includes.h"

constexpr int width{5};
constexpr int height{5};
constexpr Coord zero,board_size{width,height};

int index(int x,int y)
{ return x+y*width; }

int index(const Coord& c)
{ return index(c.x,c.y); }

Coord xy(int index)
{ return {index%width, index/width}; }

bool is_on_board(const Coord& c)
{ return c>=zero && c<board_size; }

bool is_on_board(int x,int y)
{ return is_on_board(Coord{x,y}); }

int square_distance(int index1,int index2)
{
    Coord c1=xy(index1);
    Coord c2=xy(index2);
    return (c1-c2).square_length();
}

double distance(int index1,int index2)
{ return sqrt(square_distance(index1,index2));}

struct Window_Param
{
    Coord window,border;
    CoorD cell;
    Window_Param()
    {
        sdl()->getSize(window.x,window.y);
        this->border=Coord{20,20};
        double cx=(window.x-2.0*border.x)/width;
        double cy=(window.y-2.0*border.y)/height;
        this->cell=CoorD{cx,cy};
    }
};

void press_enter()
{
    cout<<"hit ENTER";cin.get();
}

template<class T,size_t S>
ostream& operator<<(ostream& os,const array<T,S>& a)
{
    for (auto i : a)
        os<<i<<' ';
    return os;
}

template<class T>
ostream& operator<<(ostream& os,const vector<T>& v)
{
    for (auto i : v)
        os<<i<<' ';
    return os;
}

template<class K,class V>
ostream& operator<<(ostream& os,const unordered_map<K,V>& m)
{
    for (auto i : m)
        os<<i.first<<':'<<i.second<<' ';
    return os;
}

template<class T>
ostream& operator<<(ostream& os,const unordered_set<T>& s)
{
    for (auto i : s)
        os<<i<<' ';
    return os;
}

template<class T,class Cont,class Comp>
ostream& operator<<(ostream& os,const priority_queue<T,Cont,Comp>& p)
{
    priority_queue<T,Cont,Comp> copy{p};
    while (copy.size()>0)
    {
        os<<copy.top()<<' ';
        copy.pop();
    }
    return os;
}
template<class T1,class T2>
ostream& operator<<(ostream& os,const pair<T1,T2>& p)
{ return os<<p.first<<':'<<p.second; }



int factorial(int n)
{
    int f=1;
    for (int i=2;i<=n;i++)
        f*=i;
    return f;
}

#endif
