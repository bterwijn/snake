#ifndef PERMUTATIONS_H_INCLUDED
#define PERMUTATIONS_H_INCLUDED
#include "Includes.h"

class Permutations
{
    array<int,1<<5> nr_permutations_cache;
    
    int nr_permutations_helper(int nr_vars,int nr_connections)
    {
        if (nr_connections==0)
            return 1;
        int nr_non_connections=nr_vars-nr_connections;
        if (nr_non_connections==0)
            return 1;
        int nr_permutations=factorial(nr_vars);
        int fac_con=factorial(nr_connections);
        int fac_non_con=factorial(nr_non_connections);
        cout<<nr_permutations<<' '<<fac_con<<' '<<fac_non_con<<'\n';
        return nr_permutations/(fac_con*fac_non_con);
    }

    int get_index(int nr_vars,int nr_connections) const
    { return nr_vars<<2|nr_connections;}
    
 public:
    
    Permutations()
    {
        for (int nr_vars=0;nr_vars<=4;nr_vars++)
        {
            for (int nr_connections=0;nr_connections<=2;nr_connections++)
            {
                int index=get_index(nr_vars,nr_connections);
                int nr_perms=nr_permutations_helper(nr_vars,nr_connections);
                nr_permutations_cache[index]=nr_perms;
            }
        }
    }

    int nr_permutations(int nr_vars,int nr_connections) const
    { return nr_permutations_cache[get_index(nr_vars,nr_connections)];}
    
    friend ostream& operator<<(ostream& os,const Permutations& c);
};

ostream& operator<<(ostream& os,const Permutations& p)
{
    for (int nr_vars=0;nr_vars<=4;nr_vars++)
    {
        for (int nr_connections=0;nr_connections<=2;nr_connections++)
        {
            int nr_perms=p.nr_permutations(nr_vars,nr_connections);
            os<<"nr_vars:"<<nr_vars<<" nr_connections:"<<nr_connections<<" : "<<nr_perms<<'\n';
        }
    }
    return os;
}

#endif
