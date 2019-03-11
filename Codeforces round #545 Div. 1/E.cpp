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
#define D(x) cerr << #x << " is " << (x) << "\n";

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

int main()
{
	int n,m;
	scanf("%i %i",&n,&m);
	ll len=n;
	ll napred=0;
	vector<pair<pair<ll,ll>,pair<ll,ll> > > nazad;
    ll lazyb=0,lazys=1;
	while(m--)
    {
        int t;
        scanf("%i",&t);
        if(t==1)
        {
            int k;
            scanf("%i",&k);
            len+=k;
            napred=0;
            nazad.clear();
        }
        if(t==2)
        {
            int k;
            scanf("%i",&k);
            if(nazad.empty()||nazad.back().f!=0)
                nazad.pb({{0,(len+1)},{lazyb,lazys}});
            len+=k;
        }
        if(t==3)
        {
            ll b,s;
            scanf("%lld %lld",&b,&s);
            napred+=b;
            lazyb=lazyb*s+b;
            lazys=lazys*s;
            while(nazad.size()>1)
            {
                if(nazad.back().f.s*lazys/nazad.back().s.s-nazad.back().s.f+lazyb>nazad[nazad.size()-1].f.s*lazys/nazad.back().s.s-nazad.nazad[nazad.size()-1].s.f+lazyb||nazad.back().f.s*lazys/nazad.back().s.s-nazad.back().s.f+lazyb>nazad.front().f.s*lazys/nazad.back().s.s-nazad.nazad.front().s.f+lazyb)
                    nazad.pop_back();
            }
        }
        if(nazad.empty()||napred<=(nazad.back()).f)
        {
            printf("1 %lld\n",napred);
        }
        else
        {
            printf("%.0lf %.0lf\n",(nazad.back()).s*lazys+lazyb,(nazad.back()).f);
        }
    }
    return 0;
}
