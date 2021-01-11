#include<bits/stdc++.h>
using namespace std;
const int N=500005;
int n,s,root=1,maxn,pos;
int fa[N]={-1},res=0x3f3f3f3f;
int nxt[N*2],edge[N*2],head[N],ver[N*2],cnt,dist[N],v[N];
bool st[N];
int q[N],dmx[N],tt=-1,hh=0;
void add(int x,int y,int z){
	edge[++cnt]=z;
	ver[cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
void dfs1(int x){
	if(dist[x]>maxn){
		pos=x,maxn=dist[x];
	}
	v[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(v[y]) continue;
		fa[y]=x;dist[y]=dist[x]+edge[i];
		dfs1(y);
	}
}
int dfs2(int x,int fa){
	int t=0;//从x出发，不经过直径上的一点所能到达的最远点的长度 
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(y==fa||st[y]) continue;
		t=max(t,edge[i]+dfs2(y,x));
	}
	return t;
}
int main()
{
	cin>>n>>s;
	for(int i=1,a,b,c;i<n;i++){
		cin>>a>>b>>c;
		add(a,b,c);add(b,a,c);
	}
	dfs1(1);
	dist[pos]=0;
	memset(v,0,sizeof(v));
	int ed=pos;fa[pos]=0;maxn=0;
	
	dfs1(pos);
	int start=pos;
	//处理好直径问题 
	for(int i=pos;i;i=fa[i]){ st[i]=1;}
	for(int i=1;i<=n;i++)
		if(st[i]) dmx[i]=dfs2(i,0); 
	int l=pos;//左边界 
	for(int i=pos;i;i=fa[i]){
		while(tt>=hh&&dist[q[hh]]-dist[i]>s) hh++;//超过规定长度，出队 
		while(dist[l]-dist[i]>s) l=fa[l];//左边界节点与现在节点间长度过大，因此更换路径左端点 
		while(tt>=hh&&dmx[i]>=dmx[q[tt]]) tt--;//当前节点所能到达非直径最远距离如果队列中的距离长，那么决策更优 
		q[++tt]=i;
		res=min(res,max(max(dist[start]-dist[l],dist[q[tt]]-dist[ed]),dmx[q[hh]]));
	}
	cout<<res<<endl;
	return 0;
}
