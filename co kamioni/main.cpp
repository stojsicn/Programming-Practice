/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2015/contest3_solutions/solutions.pdf
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

const int N=1e5+1;
vector<int> sol(N);
struct kamion{
    vector<pair<int,pair<int,int> > > update;
    ll lastupdate;
    int pos,dir;
    bool finished;
};
struct event{
    ll time;
    int id,pos;
    bool ending;
};
bool cmpevent(event a,event b)
{
    if(a.time==b.time)
        return a.ending<b.ending;
    return a.time<b.time;
}
vector<kamion> kam(N);
int getpos(int i,ll t)
{
    return kam[i].pos+kam[i].dir*(t-kam[i].lastupdate);
}
vector<event> e;
void applyevent(event a)
{
    for(auto &p:kam[a.id].update)
    {
        if(kam[p.s.f].finished)
        {
            if(kam[p.s.f].lastupdate>kam[a.id].lastupdate)
            {
                int pos=getpos(a.id,kam[p.s.f].lastupdate);
                pos=pos<kam[p.s.f].pos;
                if(pos!=p.f)
                    sol[p.s.s]++;
                p.f=pos;
            }
            continue;
        }
        int pos=getpos(p.s.f,a.time);
        pos=a.pos<pos;
        if(pos!=p.f)
            sol[p.s.s]++;
        p.f=pos;
    }
    kam[a.id].lastupdate=a.time;
    kam[a.id].pos=a.pos;
    kam[a.id].finished=a.ending;
    if(kam[a.id].dir==1)
        kam[a.id].dir=-1;
    else
        kam[a.id].dir=1;
}
int main()
{
    int n,m;
    scanf("%i %i",&n,&m);
    vector<int> k(n);
    for(int i=0;i<n;i++)
    {
        scanf("%i",&k[i]);
        int a;
        ll t=0;
        scanf("%i",&a);
        kam[i]={{},0,a,-1,0};
        for(int j=1;j<k[i];j++)
        {
            int b;
            scanf("%i",&b);
            t+=abs(b-a);
            if(j==1&&b>a)
                kam[i].dir=1;
            e.pb({t,i,b,0});
            a=b;
        }
        e.back().ending=1;
    }
    sort(all(e),cmpevent);
    for(int i=0;i<m;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;b--;
        if(k[a]>k[b])
            swap(a,b);
        kam[a].update.pb({kam[a].pos<kam[b].pos,{b,i}});
    }
    for(auto p:e)
        applyevent(p);
    for(int i=0;i<m;i++)
        printf("%i\n",sol[i]);
    return 0;
}
