#ifndef CONSTRAINT_H_INCLUDED
#define CONSTRAINT_H_INCLUDED
#include "Includes.h"

struct Constraint_Index;

class Constraint
{
    vector<int> vars;
    int index;
    int nr_connections;
    int nr_permutations;
    
 public:
    Constraint() {}
    Constraint(int index,vector<int> vars,int nr_connections,const Permutations& permutations)
        : vars{vars},index{index}, nr_connections{nr_connections}
    {
        update_nr_permutations(permutations);
    }

    int get_index() const
    { return index; }
    
    void update_nr_permutations(const Permutations& permutations)
    { nr_permutations=permutations.nr_permutations(vars.size(),nr_connections); }

    int get_nr_permutations() const
    { return nr_permutations; }

    const vector<int>& get_vars() const
    { return vars; }

    const vector<bool> get_values() const
    {
        if (nr_connections==0)
            return vector<bool>{false};
        if (nr_connections==(int)(vars.size()))
            return vector<bool>{true};
        return vector<bool>{true,false};
    }

    void set_variable(int var,int value)
    {
        auto found=find(vars.begin(), vars.end(), var);
        assert(found!=vars.end());
        vars.erase(found);
        if (value)
            nr_connections--;
    }
    
    friend ostream& operator<<(ostream& os,const Constraint& c);
    friend bool operator<(const Constraint& c1,const Constraint& c2);
};

bool operator<(const Constraint& c1,const Constraint& c2)
{
    if (c1.nr_permutations<c2.nr_permutations)
        return true;
    if (c1.nr_permutations==c2.nr_permutations && c1.vars.size()<c2.vars.size())
        return true;
    return false;
}

ostream& operator<<(ostream& os,const Constraint& c)
{ return os<<"index:"<<c.index<<" nr_connections:"<<c.nr_connections<<" vars:"<<c.vars<<" permutations:"<<c.nr_permutations<<'\n'; }

class Variable
{
    bool value;
    vector<int> constraint_indices;
public:
    bool get_value() const
    { return value; }

    void set_value(bool value)
    { this->value=value; }

    void add_constraint_index(int ci)
    { constraint_indices.push_back(ci); }

    const vector<int> get_constraint_indices() const
    { return constraint_indices; }
    
    friend ostream& operator<<(ostream& os,const Variable& v);
};

ostream& operator<<(ostream& os,const Variable& v)
{ return os<<v.value<<':'<<v.constraint_indices<<'\n'; }
    
#endif
