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

//2:05
struct point{
    int x,y,i,visina;
};
bool cmp1(point a,point b)
{
    if(a.x==b.x)
        return a.y<b.y;
    return a.x<b.x;
}
bool cmp2(point a,point b)
{
    if(a.y==b.y)
        return a.x<b.x;
    return a.y<b.y;
}
vector<int> nxt;
int m;
struct segTree{
    vector<int> minn;
    void init()
    {
        minn.resize(4*m);
        fill(all(minn),-1);
    }
    void prop(int i)
    {
        if(minn[2*i]==-1)
            minn[2*i]=minn[i];
        if(minn[2*i+1]==-1)
            minn[2*i+1]=minn[i];
        minn[i]=-1;
    }
    void reset(int pos,int l=0,int r=m-1,int i=1)
    {
        if(l==r)
        {
            if(pos==l)
                minn[i]=-1;
            return;
        }
        int mi=(l+r)>>1;
        prop(i);
        reset(pos,l,mi,2*i);
        reset(pos,mi+1,r,2*i+1);
    }
    void set(int qs,int qe,int ind,int l=0,int r=m-1,int i=1)
    {
        if(qs>r||qe<l)
            return;
        //printf("%i %i %i %i %i %i\n",qs,qe,ind,l,r,i);
        if(qs<=l&&qe>=r)
        {
            if(minn[i]==-1)
                minn[i]=ind;
            return;
        }
        int mi=(l+r)>>1;
        prop(i);
        set(qs,qe,ind,l,mi,2*i);
        set(qs,qe,ind,mi+1,r,2*i+1);
    }
    void setup(int l=0,int r=m-1,int i=1)
    {
        if(l==r)
        {
            nxt[l]=minn[i];
            return;
        }
        int mi=(l+r)>>1;
        prop(i);
        setup(l,mi,2*i);
        setup(mi+1,r,2*i+1);
    }
}st;
int main()
{
    freopen("ispiti.in.2","r",stdin);
	int n;
	scanf("%i",&n);
	vector<pair<int,int> > q(n);
	vector<int> ver,hor;
	for(int i=0;i<n;i++)
    {
        char s[2];
        scanf("%s",s);
        if(s[0]=='D')
        {
            int a,b;
            scanf("%i %i",&a,&b);
            ver.pb(a);
            hor.pb(b);
            q[i]={a,b};
        }
        else
        {
            int a;
            scanf("%i",&a);
            a--;
            q[i]={a,-1};
        }
    }
    sort(all(ver));
    sort(all(hor));
    ver.erase(unique(all(ver)),ver.end());
    hor.erase(unique(all(hor)),hor.end());
    gp_hash_table<int,int> mapav,mapah;
    for(int i=0;i<(int)ver.size();i++)
        mapav[ver[i]]=i;
    for(int i=0;i<(int)hor.size();i++)
        mapah[hor[i]]=i;
    for(auto &p:q)
        if(p.s!=-1)
            p.f=mapav[p.f],p.s=mapah[p.s];
    vector<point> cords;
    int tr=0;
    for(int i=0;i<n;i++)
        if(q[i].s!=-1)
            cords.pb({q[i].f,q[i].s,tr++,-1});
    m=cords.size();
    st.init();
    sort(all(cords),cmp1);
    for(int i=0;i<m;i++)
        cords[i].visina=i;
    sort(all(cords),cmp2);
    /*for(int i=0;i<m;i++)
    {
        printf("%i %i %i %i\n",cords[i].x,cords[i].y,cords[i].visina,cords[i].i);
    }*/
    for(int i=0;i<m;i++)
    {
        st.set(0,cords[i].visina,cords[i].i);
        st.reset(cords[i].visina);
    }
    nxt.resize(m);
    st.setup();
    pair<int,int> up[m][20];
    sort(all(cords),cmp1);
    for(int i=0;i<m;i++)
        up[cords[i].i][0]={nxt[i],nxt[i]};
    /*for(int i=0;i<m;i++)
        printf("%i %i\n",up[i][0].f,up[i][0].s);
    printf("\n");*/
    for(int j=1;j<20;j++)
    {
        for(int i=0;i<m;i++)
        {
            pair<int,int> tr=up[i][j-1];
            if(tr.f==-1)
                up[i][j]=tr;
            else
                up[i][j]={up[tr.f][j-1].f,min(tr.s,up[tr.f][j-1].s)};
        }
    }
    //printf("Dosao!\n");
    int cnt=-1;
    for(int i=0;i<n;i++)
    {
        if(q[i].s==-1)
        {
            int tr=q[i].f;
            for(int j=19;j>=0;j--)
                if(up[tr][j].s>cnt)
                    tr=up[tr][j].f;
            tr=up[tr][0].f;
            if(tr==-1)
                printf("NE\n");
            else
                printf("%i\n",tr+1);
        }
        else
            cnt++;
    }
    return 0;
}
