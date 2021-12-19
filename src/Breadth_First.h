#ifndef BREADTH_FIRST_H_INCLUDED
#define BREADTH_FIRST_H_INCLUDED
#include "Includes.h"

class Breadth_First
{
    static constexpr int nr_rings=3;
    int current_ring=0;
    array<unordered_set<int>,nr_rings> rings;

    int ring_index(int r)
    { return (current_ring+r+nr_rings)%nr_rings; }

    unordered_set<int>& get_ring(int r=0)
    { return rings[ring_index(r)]; }
        
    void add_ring(int i,int r=0)
    { rings[ring_index(r)].insert(i); }

    bool is_in(int i,const unordered_set<int>& set)
    { return set.find(i)!=set.end(); }
    
    void next_ring()
    { current_ring++; }
    
    void clear_rings()
    {
        for (auto& ring : rings)
            ring.clear();
    }
    
    int min_dist(Board& board)
    {
        clear_rings();
        add_ring(board.get_head());
        int step=0;
        unordered_set<int> goals;
        while (get_ring().size()>0)
        {
            if (step<board.snake_length())
                goals.insert(board.get_tail(step));
            for (int i : get_ring())
            {
                for (int n : board.get_neighbors(i))
                {
                    if (is_in(n,goals))
                        return step;
                    if (board.is_free_cell(n) && !is_in(n,get_ring(-1)))
                        add_ring(n,+1);
                }
            }
            next_ring();
            get_ring(+1).clear();
            step++;
        }
        return -1;
    }
    
 public:
    Breadth_First()
    {
    }

    bool step(Board& board)
    {
        auto neigbors=board.get_free_neighbors(board.get_head());
        vector<int> indices;
        int best=-1;
        for (int i : neigbors)
        {
            board.step(i);
            int dist=min_dist(board);
            if (dist>best)
            {
                best=dist;
                indices.clear();
                indices.push_back(i);
            }
            else if (dist==best)
            {
                indices.push_back(i);
            }
            board.undo_step();
        }
        if (indices.size()>0)
        {
            int i=indices[rand()%indices.size()];
            board.step(i);
            return true;
        }
        return false;
    }
    
    void draw(const Window_Param& wp)
    {
    }
    
    friend ostream& operator<<(ostream& os,const Breadth_First& b);
};

ostream& operator<<(ostream& os,[[maybe_unused]] const Breadth_First& b)
{
    //for (auto i : a.fringe)
    //    os<<i<<'\n';
    return os;
}

#endif
