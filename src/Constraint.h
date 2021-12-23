#ifndef CONSTRAINT_H_INCLUDED
#define CONSTRAINT_H_INCLUDED
#include "Includes.h"

struct Constraint_Index;

class Constraint
{
    vector<int> var_indices;
    int index;
    int nr_connections;
    int nr_permutations;
    
 public:
    Constraint() {}
    Constraint(int index,vector<int> var_indices,int nr_connections,const Permutations& permutations)
        : var_indices{var_indices},index{index}, nr_connections{nr_connections}
    {
        update_nr_permutations(permutations);
    }

    bool is_active() const
    { return var_indices.size()>0; }
    
    int get_index() const
    { return index; }
    
    void update_nr_permutations(const Permutations& permutations)
    { nr_permutations=permutations.nr_permutations(var_indices.size(),nr_connections); }

    int get_nr_permutations() const
    { return nr_permutations; }

    const vector<int>& get_var_indices() const
    { return var_indices; }

    bool is_valid_value(bool value)
    {
        if (value)
            return nr_connections>0; // still connections left for variables
        else
            return (int)(var_indices.size())>nr_connections; // still variables left for connections
    }
    
    void set_variable(int var,bool value)
    {
        auto found=find(var_indices.begin(), var_indices.end(), var);
        assert(found!=var_indices.end());
        var_indices.erase(found);
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
    if (c1.nr_permutations==c2.nr_permutations &&
        c1.var_indices.size()>c2.var_indices.size())
        return true;
    return false;
}

ostream& operator<<(ostream& os,const Constraint& c)
{ return os<<"index:"<<c.index<<" nr_connections:"<<c.nr_connections<<" var_indices:"
           <<c.var_indices<<" permutations:"<<c.nr_permutations<<'\n'; }

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

    const vector<int>& get_constraint_indices() const
    { return constraint_indices; }
    
    friend ostream& operator<<(ostream& os,const Variable& v);
};

ostream& operator<<(ostream& os,const Variable& v)
{ return os<<v.value<<':'<<v.constraint_indices<<'\n'; }
    
#endif
