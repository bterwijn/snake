#ifndef CONSTRAINT_H_INCLUDED
#define CONSTRAINT_H_INCLUDED
#include "Includes.h"

class Constraint
{
    vector<int> vars;
    int connection_count;
    
 public:
    Constraint(vector<int> vars,int connection_count)
    {
        this->vars=vars;
        this->connection_count=connection_count;
    }

    void draw(const Window_Param& wp)
    {
    }
    
    friend ostream& operator<<(ostream& os,const Constraint& c);
};

ostream& operator<<(ostream& os,[[maybe_unused]] const Constraint& c)
{ return os<<c.vars<<" "<<c.true_count<<":"<<c.false_count; }

#endif
