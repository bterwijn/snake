#ifndef CONSTRAINT_H_INCLUDED
#define CONSTRAINT_H_INCLUDED
#include "Includes.h"

class Constraint
{
    vector<int> vars;
    int nr_connections;
    int nr_permutations;
    static const Permutations permutations;
    
 public:
    Constraint(vector<int> vars,int nr_connections)
    {
        this->vars=vars;
        this->nr_connections=nr_connections;
        update_nr_permutations();
    }

    void update_nr_permutations()
    { nr_permutations=permutations.nr_permutations(vars.size(),nr_connections); }
    
    friend ostream& operator<<(ostream& os,const Constraint& c);
    friend bool operator>(const Constraint& c1,const Constraint& c2);
    
};
const Permutations Constraint::permutations=Permutations{};

bool operator>(const Constraint& c1,const Constraint& c2)
{ return c1.nr_permutations>c2.nr_permutations; }

ostream& operator<<(ostream& os,[[maybe_unused]] const Constraint& c)
{ return os<<"cons:"<<c.nr_connections<<" vars:"<<c.vars<<" perm:"<<c.nr_permutations<<'\n'; }

#endif
