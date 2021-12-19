#ifndef A_STAR_H_INCLUDED
#define A_STAR_H_INCLUDED
#include "Includes.h"

struct index_dist_score
{
    int index,dist;
    double score;
    
    index_dist_score(int index,int dist,double score)
    { this->index=index; this->dist=dist; this->score=score; }
};

bool operator<(const index_dist_score& is1,const index_dist_score& is2)
{ return is1.score>is2.score; }

ostream& operator<<(ostream& os,const index_dist_score& i)
{ return os<<"i:"<<i.index<<" d:"<<i.dist<<" s:"<<i.score; }

class A_Star
{
    unordered_map<int,int> closed;
    std::priority_queue<index_dist_score> fringe;

    void clear()
    {
        closed.clear();
        fringe=std::priority_queue<index_dist_score>();
    }
    
 public:
    A_Star()
    {
    }
    
    vector<index_dist_score> plan_path(const Cells& cells,const Cell_Neighbors& cell_neighbors,int begin,int end,vector<int>& ends)
    {
        clear();
        vector<index_dist_score> ends_dist;
        fringe.push({begin,0,distance(begin,end)});
        while (fringe.size()>0 && ends.size()>0)
        {
            auto best=fringe.top();
            //cout<<"best.index:"<<best.index<<'\n';
            fringe.pop();
            auto children=cells.filter_free(cell_neighbors[best.index]);
            for (auto i : children)
            {
                if (closed.find(i)==closed.end())
                {
                    closed.insert({i,best.index});
                    int dist=best.dist+1;
                    double score=dist+distance(i,end);
                    index_dist_score ids{i,dist,score};
                    fringe.push(ids);
                    auto found=find(ends.begin(), ends.end(), i);
                    if (found!=ends.end())
                    {
                        ends_dist.push_back(ids);
                        ends.erase(found);
                    }
                }
            }
        }
        return ends_dist;
    }

    void draw(const Window_Param& wp)
    {
        Col red=MyColor(255,0,0,255);
        for (auto i : closed)
        {
            auto c1=xy(i.first);
            auto c2=xy(i.second);
            int x1=wp.border+wp.cell_width/2+c1.x*wp.cell_width;
            int y1=wp.border+wp.cell_height/2+c1.y*wp.cell_height;
            int x2=wp.border+wp.cell_width/2+c2.x*wp.cell_width;
            int y2=wp.border+wp.cell_height/2+c2.y*wp.cell_height;
            lineColor(sdl()->renderer(),x1,y1,x2,y2, red); // draw line
        }
    }
    
    friend ostream& operator<<(ostream& os,const A_Star& a);
};

ostream& operator<<(ostream& os,[[maybe_unused]] const A_Star& a)
{
    //for (auto i : a.fringe)
    //    os<<i<<'\n';
    return os;
}

#endif
