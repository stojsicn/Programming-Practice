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
#define ld long double

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
int n,k;
struct pt{
  ld x,y;
  pt operator-(pt a){return {x-a.x,y-a.y};}
  pt operator+(pt a){return {x+a.x,y+a.y};}
};
ld abs(pt a){return sqrtl(a.x*a.x+a.y*a.y);}
ostream& operator<<(ostream& out,pt p){out << "[" << p.x << "," << p.y << "]";return out;}
ld eps=1e-9;
ld eps1=2e-4;
const ld PI=acos(-1);
vector<pt> points;
pt rot(pt p,ld a){return {p.x*cos(a)-p.y*sin(a),p.x*sin(a)+p.y*cos(a)};}
pt sol;
bool test(ld r)
{
    for(int i=0;i<n;i++)
    {
        vector<pair<ld,int> > events;
        for(int j=0;j<n;j++)
        {
            if(i==j||abs(points[j]-points[i])>2*r)
                continue;
            ld ang=atan2((points[j]-points[i]).y,(points[j]-points[i]).x);
            ld x=acos(abs(points[j]-points[i])/2/r);
            events.pb({ang-x,-1});
            events.pb({ang+x,1});
            events.pb({ang-x+2*PI,-1});
            events.pb({ang+x+2*PI,1});
        }
        sort(all(events));
        int c=0;
        for(auto p:events)
        {
            c-=p.s;
            if(c==k-1)
            {
                pt a={r,0};
                a=rot(a,p.f)+points[i];
                sol=a;
                return true;
            }
        }
    }
    return false;
}
int check(vector<string> argv)
{

   FILE
      *fin  = fopen(argv[0].c_str(), "rt"),
      *foff = fopen(argv[1].c_str(), "rt"),
      *fout = fopen(argv[2].c_str(), "rt");

   if ( fin == NULL ) {
      fprintf( stderr, "Error opening input file (\"%s\") for reading!\n", argv[1] );
      return 2;
   }

   if ( foff == NULL ) {
      fprintf( stderr, "Error opening official output file (\"%s\") for reading!\n", argv[2] );
      return 2;
   }

   if ( fout == NULL ) {
      fprintf( stderr, "Error opening your output file (\"%s\") for reading!\n", argv[3] );
      return 1;
   }

   int N, K;
   static int px[1000], py[1000];

   if ( fscanf(fin, "%d%d", &N, &K) != 2 ) {
      fprintf( stderr, "Error reading input (N, K)!\n" );
      return 2;
   }

   for ( int i=0; i<N; ++i ) {
      if ( fscanf(fin, "%d%d", &px[i], &py[i]) != 2 ) {
         fprintf( stderr, "Error reading input (i-th point)!\n", i+1 );
         return 2;
      }
   }

   double R, Roff, x, y;
   if ( fscanf(foff, "%lf", &Roff) != 1 ) {
      fprintf( stderr, "Error reading official output!\n" );
      return 2;
   }

   if ( fscanf(fout, "%lf%lf%lf", &R, &x, &y) != 3 ) {
      fprintf( stderr, "Error reading your output!\n");
      return 2;
   }

   if ( R-Roff > 0.0001+1e-12 ) {
      printf( "Radius too large (%.6f, expected %.6f).\n", R, Roff );
      return 1;
   }

   R += 0.0002;

   int covered = 0;
   for ( int i=0; i<N; ++i ) {
      if ( (x-px[i])*(x-px[i]) + (y-py[i])*(y-py[i]) <= R*R+1e-12 )
         ++covered;
   }
   if ( covered < K ) {
      printf( "Covered only %d households (%d required).\n", covered, K );
      return 1;
   }

   printf( "Correct!\n" );
   return 0;
}
int main()
{
    for(int i=1;i<=20;i++){
        printf("Test %i: ",i);
        string num;
        if(i>=10)
            num+='0'+i/10;
        num+='0'+i%10;
        string in="antenna.in."+num;
        string out="antenna.out."+num;
        string myout="out.txt";
        ifstream io;
        ofstream outt;
        io.open(in.c_str());
        io >> n >> k;
        points.resize(n);
        for(int i=0;i<n;i++)
            io >> points[i].x >> points[i].y;
        io.close();
        int ti=clock();
        ld l=0,r=1e4;
        while(r-l>eps1)
        {
            ld m=(l+r)/2;
            if(test(m))
                r=m;
            else
                l=m;
        }
        printf("Time: %i  ",clock()-ti);
        outt.open(myout.c_str());
        outt << setprecision(15) << l << endl;
        outt << setprecision(15) << sol.x << " " << sol.y << endl;
        outt.close();
        vector<string> aa={in,out,myout};
        check(aa);
    }
    return 0;
}
