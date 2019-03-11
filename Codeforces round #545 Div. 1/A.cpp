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
	vector<vector<int> > smaller2(n,vector<int>(m)),greater2(n,vector<int>(m)),mat(n,vector<int>(m)),smaller1(n,vector<int>(m)),greater1(n,vector<int>(m));
	for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%i",&mat[i][j]);
	for(int i=0;i<n;i++)
    {
        vector<pair<int,int> > niz;
        set<int> lol;
        for(int j=0;j<m;j++)
            niz.pb({mat[i][j],j}),lol.insert(mat[i][j]);
        sort(all(niz));
        int sm=0;
        for(int j=0;j<m;j++)
        {
            if(j)
                if(niz[j].f!=niz[j-1].f)
                    sm++;
            smaller2[i][niz[j].s]=sm;
            greater2[i][niz[j].s]=lol.size()-sm-1;
        }
    }
    for(int i=0;i<m;i++)
    {
        vector<pair<int,int> > niz;
        set<int> lol;
        for(int j=0;j<n;j++)
            niz.pb({mat[j][i],j}),lol.insert(mat[j][i]);
        sort(all(niz));
        int sm=0;
        for(int j=0;j<n;j++)
        {
            if(j)
                if(niz[j].f!=niz[j-1].f)
                    sm++;
            smaller1[niz[j].s][i]=sm;
            greater1[niz[j].s][i]=lol.size()-sm-1;
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            printf("%i ",1+max(smaller2[i][j],smaller1[i][j])+max(greater2[i][j],greater1[i][j]));
        }
        printf("\n");
    }
    return 0;
}
