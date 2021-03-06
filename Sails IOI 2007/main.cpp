/*
    -Sort the masts by height from lowest to highest, now do the following greedy algorithm:
        Keep track of how many sails we have placed for every height, and for every mast place the k sails on the heights where we have placed the lowest amount of sails placed before.
    -When doing this, we can keep the array of number of sails per height sorted decreasingly (when looking at height 0,1,2...)
    -I used a segment tree to update the number of sails per height and just get the final result at the end.
*/
#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define f first
#define s second
#define all(x) x.begin(), x.end()

using namespace std;

const int N=1e5+5;
vector<int> minn(4*N),maxx(4*N),lazy(4*N);
void prop(int i)
{
    minn[2*i]+=lazy[i];
    minn[2*i+1]+=lazy[i];
    maxx[2*i]+=lazy[i];
    maxx[2*i+1]+=lazy[i];
    lazy[2*i]+=lazy[i];
    lazy[2*i+1]+=lazy[i];
    lazy[i]=0;
}
void update(int i)
{
    minn[i]=min(minn[2*i],minn[2*i+1]);
    maxx[i]=max(maxx[2*i],maxx[2*i+1]);
}
void inc(int qs,int qe,int l=0,int r=N-1,int i=1)
{
    if(qs>qe)
        return;
    if(qs>r||qe<l)
        return;
    if(qs<=l&&qe>=r)
    {
        lazy[i]++;
        minn[i]++;
        maxx[i]++;
        return;
    }
    prop(i);
    int m=(l+r)>>1;
    inc(qs,qe,l,m,2*i);
    inc(qs,qe,m+1,r,2*i+1);
    update(i);
}
int get(int pos,int l=0,int r=N-1,int i=1)
{
    if(l>pos||r<pos)
        return 0;
    if(l==pos&&r==pos)
        return minn[i];
    prop(i);
    int m=(l+r)>>1;
    return get(pos,l,m,2*i)+get(pos,m+1,r,2*i+1);
}
int getfirst(int vr,int l=0,int r=N-1,int i=1)
{
    if(l==r)
        return l;
    prop(i);
    int m=(l+r)>>1;
    if(maxx[2*i]>=vr)
        return getfirst(vr,l,m,2*i);
    else
        return getfirst(vr,m+1,r,2*i+1);
}
int getlast(int vr,int l=0,int r=N-1,int i=1)
{
    if(l==r)
        return l;
    prop(i);
    int m=(l+r)>>1;
    if(minn[2*i+1]<=vr)
        return getlast(vr,m+1,r,2*i+1);
    else
        return getlast(vr,l,m,2*i);
}
void add(int h,int k)
{
    int start=N-h;
    int koji=get(start+k-1);
    int l=max(start,getfirst(koji)),r=getlast(koji);
    int ostalo=start+k-l;
    inc(start,l-1);
    inc(r-ostalo+1,r);
}
ll getres(int l=0,int r=N-1,int i=1)
{
    if(l==r)
        return (ll)minn[i]*(minn[i]-1)/2;
    prop(i);
    int m=(l+r)>>1;
    return getres(l,m,2*i)+getres(m+1,r,2*i+1);
}
int main()
{
    int n;
	scanf("%i",&n);
	vector<pair<int,int> > sails(n);
	for(int i=0;i<n;i++)
        scanf("%i %i",&sails[i].f,&sails[i].s);
    sort(all(sails));
    for(auto p:sails)
        add(p.f,p.s);
    printf("%lld\n",getres());
    return 0;
}
