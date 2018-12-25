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
		if(i>0&&i<sz(a))
			os << ", ";
		os << a[i];
	}
	os << '}';
    return os;
}
const int N=150;
vector<int> initt;
struct segTree{
    vector<int> minn;
    void update(int i)
    {
        minn[i]=min(minn[2*i],minn[2*i+1]);
    }
    void build(int i=1,int l=0,int r=N-1)
    {
        if(l==r)
        {
            minn[i]=initt[l];
            return;
        }
        int m=(l+r)>>1;
        build(2*i,l,m);
        build(2*i+1,m+1,r);
        update(i);
    }
    void init()
    {
        minn.resize(4*N);
        build();
    }
    int gett(int qs,int qe,int i=1,int l=0,int r=N-1)
    {
        if(l>qe||r<qs)
            return INT_MAX;
        if(qs<=l&&qe>=r)
            return minn[i];
        int m=(l+r)>>1;
        return min(gett(qs,qe,2*i,l,m),gett(qs,qe,2*i+1,m+1,r));
    }
};
vector<vector<vector<int> > > matrix(N,vector<vector<int> > (N,vector<int> (N))),matrix2(N,vector<vector<int> > (N,vector<int> (N)));
int check(int p,int q,int h)
{
    int possible[p][q];
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            int dep=0;
            for(int k=0;k<h;k++)
            {
                if(matrix[i][j][k]==1)
                {
                    dep++;
                }
                else
                {
                    break;
                }
            }
            possible[i][j]=dep;
            //printf("possible[%i][%i]: %i\n",i,j,dep);
        }
    }
    vector<segTree> hor(q),ver(p);
    //printf("HOR!\n");
    for(int i=0;i<q;i++)
    {
        initt.clear();
        for(int j=0;j<p;j++)
        {
            initt.pb(possible[j][i]);
        }
        cout << initt << endl;
        hor[i].init();
    }
    //printf("VER!\n");
    for(int i=0;i<p;i++)
    {
        initt.clear();
        for(int j=0;j<q;j++)
        {
            initt.pb(possible[i][j]);
        }
        cout << initt << endl;
        ver[i].init();
    }
    int sol=0;
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            //printf("Pokusavam %i %i\n",i,j);
            int minn=INT_MAX;
            for(int k=0;k<min(p-i,q-j);k++)
            {
                int a1=hor[j+k].gett(i,i+k);
                int a2=ver[i+k].gett(j,j+k);
                //printf("Za kvadrat %i: %i %i\n",k,a1,a2);
                minn=min(minn,a1);
                minn=min(minn,a2);
                if(minn==0)
                    break;
                sol=max(sol,4*(k+1)*minn);
            }
        }
    }
    return sol;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int p,q,h;
	cin >> p >> q >> h;
	swap(p,q);
	for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            string s;
            cin >> s;
            for(int k=0;k<h;k++)
            {
                if(s[k]=='N')
                    matrix[i][j][k]=1;
            }
        }
    }
    int sol=check(p,q,h);
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            reverse(matrix[i][j].begin(),matrix[i][j].begin()+h);
        }
    }
    sol=max(sol,check(p,q,h));
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            reverse(matrix[i][j].begin(),matrix[i][j].begin()+h);
        }
    }
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            for(int k=0;k<h;k++)
            {
                matrix2[k][j][i]=matrix[i][j][k];
            }
        }
    }
    swap(p,h);
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            for(int k=0;k<h;k++)
            {
                matrix[i][j][k]=matrix2[i][j][k];
            }
        }
    }
    sol=max(sol,check(p,q,h));
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            reverse(matrix[i][j].begin(),matrix[i][j].begin()+h);
        }
    }
    sol=max(sol,check(p,q,h));
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            reverse(matrix[i][j].begin(),matrix[i][j].begin()+h);
        }
    }
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            for(int k=0;k<h;k++)
            {
                matrix2[i][k][j]=matrix[i][j][k];
            }
        }
    }
    swap(q,h);
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            for(int k=0;k<h;k++)
            {
                matrix[i][j][k]=matrix2[i][j][k];
            }
        }
    }
    sol=max(sol,check(p,q,h));
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            reverse(matrix[i][j].begin(),matrix[i][j].begin()+h);
        }
    }
    sol=max(sol,check(p,q,h));
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            reverse(matrix[i][j].begin(),matrix[i][j].begin()+h);
        }
    }
    printf("%i\n",sol);
    return 0;
}
