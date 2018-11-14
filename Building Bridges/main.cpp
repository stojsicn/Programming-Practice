/*
    - Save in a segment tree for every future height, the heights at which we would benefit from taking the current pillar
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back
#define mp make_pair
using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()
int N;
pair<int,ll> nul=make_pair(-1,-1);
struct segmentTree{
    vector<pair<int,ll> > lazy;
    vector<bool> iszero;
    vector<ll> inc;
    void init()
    {
        lazy.resize(4*N+10);
        inc.resize(4*N+10);
        iszero.resize(4*N+10);
    }
    void prop(int i)
    {
        if(lazy[i]!=nul){
            lazy[2*i]=lazy[i];
            lazy[2*i+1]=lazy[i];
            lazy[i]=nul;
        }
        if(iszero[i])
        {
            iszero[2*i]=true;
            iszero[2*i+1]=true;
            return;
        }
        if(iszero[2*i])
        {
            inc[2*i]=0;
            iszero[2*i]=false;
            if(4*i<4*N)
            {
                iszero[4*i]=true;
            }
            if(4*i+1<4*N)
            {
                iszero[4*i+1]=true;
            }
        }
        inc[2*i]+=inc[i];
        if(iszero[2*i+1])
        {
            inc[2*i+1]=0;
            iszero[2*i+1]=false;
            if(4*i+2<4*N)
            {
                iszero[4*i+2]=true;
            }
            if(4*i+3<4*N)
            {
                iszero[4*i+3]=true;
            }
        }
        inc[2*i+1]+=inc[i];
        inc[i]=0;
    }
    void increase(int qs,int qe,ll x,int i=1,int l=0,int r=N-1)
    {
        if(qe<l||qs>r){
            return;
        }
        if(iszero[i])
        {
            inc[i]=0;
            iszero[i]=false;
        }
        if(qs<=l&&r<=qe)
        {
            inc[i]+=x;
            return;
        }
        prop(i);
        int m=(l+r)/2;
        increase(qs,qe,x,2*i,l,m);
        increase(qs,qe,x,2*i+1,m+1,r);
    }
    void set(int qs,int qe,pair<int,ll> x,int i=1,int l=0,int r=N-1)
    {
        if(qe<l||qs>r)
            return;
        if(qs<=l&&r<=qe)
        {
            lazy[i]=x;
            iszero[i]=true;
            return;
        }
        prop(i);
        int m=(l+r)/2;
        set(qs,qe,x,2*i,l,m);
        set(qs,qe,x,2*i+1,m+1,r);
    }
    pair<int,ll> get(int p,int i=1,int l=0,int r=N-1)
    {
        if(p<l||p>r)
            return nul;
        //printf("Trazim %i u %i %i,  %i %lld %lld\n",p,l,r,lazy[i].first,lazy[i].second,inc[i]);
        if(p<=l&&r<=p)
        {
            if(iszero[i])
                return lazy[i];
            return mp(lazy[i].first,lazy[i].second+inc[i]);
        }
        prop(i);
        int m=(l+r)/2;
        auto pp=get(p,2*i,l,m);
        if(pp!=nul)
            return pp;
        return get(p,2*i+1,m+1,r);
    }
} ST;
int hi,y,we;
ll W;
ll calc(int mid)
{
    ll o1=(ll)(mid-hi)*(ll)(mid-hi)+(ll)(hi-y)*(hi-y)+W;
    pair<int,ll> lol=ST.get(mid);
    int y2=lol.first;
    ll W2=lol.second;
    ll o2=(ll)(mid-y2)*(mid-y2)+we+W2;
    return o1-o2;
}
int main()
{
    int n;
    scanf("%i",&n);
    vector<int> h(n),w(n);
    for(int i=0;i<n;i++)
    {
        scanf("%i",&h[i]);
        N=max(N,h[i]);
    }
    ST.init();
    for(int i=0;i<n;i++)
    {
        scanf("%i",&w[i]);
    }
    //ll res1=calc(n-2,h[n-1]);
    //printf("%lld\n",calc(n-2,h[n-1]));
    ST.set(0,N,mp(h[0],0));
    //printf("Stavio od 0 do %i na %i %i\n",N,h[0],0);
    for(int i=1;i<n-1;i++)
    {
        //printf("Usao za %i  %i %i\n",i,h[i],w[i]);
        int l=0;
        pair<int,ll> lol=ST.get(h[i]);
        y=lol.first;
        W=lol.second;
        hi=h[i];
        we=w[i];
        ll last=-1;
        int lodd=-1;
        for(int j=0;j<=N;j++)
        {
            ll t=calc(j);
            /*//printf("%i\n",t);

            if(last==-1)
                last=t;
            else
            {
                if(t==last&&lodd!=1)
                {
                    assert(lodd==-1);
                    lodd=1;
                    //printf("ISTA!\n");
                }
                if(t<last&&lodd!=2)
                {
                    assert(lodd==-1);
                    lodd=2;
                    //printf("OPADA!\n");
                }
                if(t>last&&lodd!=3)
                {
                    assert(lodd==-1||lodd==2);
                    lodd=3;
                    //printf("RASTE!\n");
                }
                last=t;
            }*/
            if(t<0)
            {
                ST.set(j,j,mp(h[i],W+(ll)(h[i]-y)*(h[i]-y)));
            }
            else
            {
                ST.increase(j,j,w[i]);
            }
        }
    }
    int i=n-1;
    pair<int,ll> lol=ST.get(h[i]);
    int y=lol.first;
    ll W=lol.second;
   // printf("%i %lld %i\n",y,W,h[i]);
    ll res=(ll)(h[i]-y)*(h[i]-y)+W;
    printf("%lld\n",res);
    return 0;
}
