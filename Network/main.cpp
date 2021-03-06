
/*
    - Find all the leaves in dfs traversal order.
    - Connect the i-th leaf with i+leaves.size()/2 for every i=[0,(leaves.size()+1)/2]
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()

const int N=500005;
vector<vector<int> > graf(N);
vector<int> leaves;
void dfs(int tr,int par)
{
    if(graf[tr].size()==1)
        leaves.pb(tr);
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        dfs(p,tr);
    }
}
int main()
{
    int n;
    scanf("%i",&n);
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        graf[a].pb(b);
        graf[b].pb(a);
    }
    dfs(1,-1);
    int t=leaves.size()/2;
    printf("%i\n",(leaves.size()+1)/2);
    for(int i=0;i<(leaves.size()+1)/2;i++)
    {
        printf("%i %i\n",leaves[i],leaves[i+t]);
    }
    return 0;
}
