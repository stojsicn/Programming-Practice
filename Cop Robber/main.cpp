/*
    -Make a table value[i][j][move], i meaning where the cop is located, j meaning where the robber is located and move telling us who needs to make the next move.
    -A state is winning if:
        *i==j
        *Its the cops move and he can move to a winning state
        *Its the robbers move and he cant avoid going to a winning state
    -Calculate the values that we know for sure in this table(there might me a cycle in the graph so we cant tell if a position is winning or losing, in that case we can just think of it as a losing position)
    -For every cops move calculate the move that leads us to a winning state
    -All states need to be winning in order to be able to catch the cop.
    -Also if we can catch a cop starting from one location, we can do it from any location.
*/
#include <bits/stdc++.h>
#include "coprobber.h"
using namespace std;
#define pb push_back
vector<vector<int> > graph(MAX_N);
int value[MAX_N][MAX_N][2],nxt[MAX_N][MAX_N],degree[MAX_N][MAX_N],pos=0;
vector<vector<int> > todo;
int start(int N, bool A[MAX_N][MAX_N])
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(A[i][j])
                graph[i].pb(j);
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(i==j)
            {
                todo.pb({i,j,0});
                todo.pb({i,j,1});
                value[i][j][0]=1;
                value[i][j][1]=1;
                continue;
            }
            degree[i][j]+=graph[j].size();
        }
    }
    while(todo.size())
    {
        vector<vector<int> > futuretodo;
        for(auto d:todo){
            int x=d[0],y=d[1],z=d[2];
            if(z==1)
            {
                int i=x,j=y,k=0;
                if(value[i][j][k]==0)
                {
                    value[i][j][k]=1;
                    nxt[i][j]=x;
                    futuretodo.pb({i,j,k});
                }
                for(auto p:graph[x])
                {
                    i=p;j=y;k=0;
                    if(value[i][j][k]==0)
                    {
                        value[i][j][k]=1;
                        nxt[i][j]=x;
                        futuretodo.pb({i,j,k});
                    }
                }
            }
            else
            {
                for(auto p:graph[y])
                {
                    int i=x,j=p,k=1;
                    if(value[i][j][k]==0)
                    {
                        degree[i][j]--;
                        if(degree[i][j]==0)
                        {
                            value[i][j][k]=1;
                            futuretodo.pb({i,j,k});
                        }
                    }
                }
            }
        }
        todo=futuretodo;
    }
    bool t=true;
    for(int i=1;i<N;i++)
        if(value[0][i][0]!=1)
            t=false;
    if(t)
        return 0;
    return -1;
}
int nextMove(int R)
{
    return pos=nxt[pos][R];
}