#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()

/*
binary search for the minimum difference between taking one more cow and not taking the extra cow.
I coded it with O(log^2(1e16)*n) but it got TLE, so i looked in the solution to get the idea to use the quadratic formula to solve it.
It took me a lot of time to make it work but i managed to do it.
*/
long double eps=1e-12;
long double razlika(ll n,ll k)
{
    return (long double)n/k/(k+1);
}
int main()
{
    int n;
    ll k;
    FILE *f1,*f2;
    f1=fopen("tallbarn.in","r");
    f2=fopen("tallbarn.out","w");
    fscanf(f1,"%i %lld",&n,&k);
    vector<ll> niz(n);
    for(int i=0;i<n;i++)
    {
        fscanf(f1,"%lld",&niz[i]);
    }
    long double lo=0,hi=1e18;
    long double mid;
    while(fabs(hi-lo)>eps)
    {
        mid=(long double)(hi+lo)/2;
        ll broj=0;
        for(int i=0;i<n;i++)
        {
            long double lol=((long double)((long double)sqrt((long double)1+4*(long double)niz[i]/mid)-1)/2);
            ll r=lol;
            r++;
            broj+=(ll)r;
        }
        if(broj>=k)
        {
            lo=mid;
        }
        else
        {
            hi=mid;
        }
    }
    long double time=0;
    ll krave=0;
    long double raz=0;
    for(int i=0;i<n;i++)
    {
        long double lol=((long double)((long double)sqrt((long double)1+4*(long double)niz[i]/lo)-1)/2);
        ll r=lol;
        if((ll)(lol-eps)<r)
        {
            raz=razlika(niz[i],r);
        }
        r++;
        krave+=r;
        time+=(long double)niz[i]/r;
    }
    time-=(k-krave)*raz;
    fprintf(f2,"%lld\n",(ll)(time+0.5));
    return 0;
}
