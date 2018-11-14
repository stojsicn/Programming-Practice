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
    void increase(int qs,int qe,ll x,int i=1,int l=0,int r=N)
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
        int m=(l+r)/2;
        increase(qs,qe,x,2*i,l,m);
        increase(qs,qe,x,2*i+1,m+1,r);
    }
    void set(int qs,int qe,pair<int,ll> x,int i=1,int l=0,int r=N)
    {
        if(qe<l||qs>r)
            return;
        if(qs<=l&&r<=qe)
        {
            lazy[i]=x;
            iszero[i]=true;
            return;
        }
        int m=(l+r)/2;
        set(qs,qe,x,2*i,l,m);
        set(qs,qe,x,2*i+1,m+1,r);
    }
    pair<int,ll> get(int p,int i=1,int l=0,int r=N)
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
ll calc(int mid,int h,int y,ll W,int w)
{
    ll o1=(ll)(mid-h)*(ll)(mid-h)+(ll)(h-y)*(h-y)+W;
    pair<int,ll> lol=ST.get(mid);
    int y2=lol.first;
    ll W2=lol.second;
    ll o2=(ll)(mid-y2)*(mid-y2)+w+W2;
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
    N++;
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
        int y=lol.first;
        ll W=lol.second;
        //printf("%i %lld\n",y,W);
        int mid;
        mid=0;
        ///negativno-uzmi pozitivno-nemoj uzeti
        int last=-1;
        int swaps=0;
        ll s=calc(N,h[i],y,W,w[i]);
        ll e=calc(N-1,h[i],y,W,w[i]);
        if(s>0&&e>s)
        {
            ST.increase(0,N,w[i]);
            continue;
        }
        if(calc(l,h[i],y,W,w[i])>0)
        {
            l++;
            int r=N;
            while(l<r)
            {
                int mid=(l+r)/2;
                ll t=calc(mid,h[i],y,W,w[i]);
                if(t<=0)
                {
                    r=mid;
                    continue;
                }
                ll t2=t;
                int c=1;
                while(true){
                if(mid+c>N)
                {
                    r=mid;
                    break;
                    continue;
                }
                ll t2=calc(mid+c,h[i],y,W,w[i]);
                if(t2>t)
                {
                    r=mid-1;
                    break;
                    continue;
                }
                if(t2<t)
                {
                    l=mid+1;
                    break;
                    continue;
                }
                c++;
                }
            }
        }
        int left=l,right=N;
        while(left<right)
        {
            int mid=(left+right)/2;
            ll t=calc(mid,h[i],y,W,w[i]);
            if(t<=0)
            {
                if(right-left==1)
                {
                    if(calc(mid+1,h[i],y,W,w[i])<=0)
                    {
                        left=right;
                        break;
                    }
                    else
                    {
                        right=left;
                        break;
                    }
                }
                left=mid;
            }
            else
            {
                right=mid-1;
            }
        }
        if(l>0)
            ST.increase(0,l-1,w[i]);
        if(left<N)
            ST.increase(left+1,N,w[i]);
        ST.set(l,left,mp(h[i],W+(ll)(h[i]-y)*(h[i]-y)));
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
