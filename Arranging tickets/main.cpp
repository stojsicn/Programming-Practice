/*
    -Binary search for the solution.
    -Do a greedy algorithm to test if it is possible to get the desired number of packages
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
	os << '{';
	for(int i=0;i<sz(a);i++)
	{
		if(i>0&&i<sz(a)-1)
			os << ", ";
		os << a[i];
	}
	os << '}';
    return os;
}
const int N=2e5+5;
vector<vector<pair<int,int> > > interval(N);
vector<ll> sum(N),temp(N),change(N);
int n;
bool test(ll max_flips,ll height)
{
    fill(all(temp),0);
    ll cnt=0;
    priority_queue<pair<int,pair<int,int> > > q;
    for(int i=1;i<=n;i++)
    {
        temp[i]+=temp[i-1];
        for(auto p:interval[i])
            q.push({p.first,{p.second,n-i}});
        ll now=sum[i]+temp[i];
        while(!q.empty()&&now>height)
        {
            int y=q.top().first,c=q.top().second.first,x=n-q.top().second.second;
            ll v=min((ll)c,(ll)(now-height+1)/2);
            q.pop();
            if(y<=i)
                continue;
            cnt+=v;
            temp[i]-=2*v;
            temp[y]+=2*v;
            now-=2*v;
            if(v<c)
                q.push({y,{c-v,x}});
        }
        if(cnt>max_flips||now>height)
            return false;
    }
    return true;
}
int main()
{
    int m;
    scanf("%i %i",&n,&m);
    for(int i=0;i<m;i++)
    {
        int a,b,c;
        scanf("%i %i %i",&a,&b,&c);
        if(a>b)
            swap(a,b);
        interval[a].pb({b,c});
        sum[a]+=c;
        sum[b]-=c;
    }
    ll maxV=0;
    for(int i=1;i<=n;i++)
        sum[i]+=sum[i-1],maxV=max(maxV,sum[i]);
    ll l=0,r=maxV;
    ll ans=-1;
    while(l<r)
    {
        ll mid=(l+r)>>1;
        if(test(maxV-mid,2*mid-maxV)||test(maxV-mid+1,2*mid-maxV-1))
            r=mid;
        else
            l=mid+1;
    }
    printf("%lld\n",l);
    return 0;
}