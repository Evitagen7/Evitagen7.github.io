#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>
#define N 100005
using namespace std;
int head[N],ver[N<<1],nex[N<<1],edge[N<<1];
int n,k,tot=1,fa[N],pre_pos,pos,maxn,pre[N],v[N],f[N];

inline void add(int x,int y,int z){
	nex[++tot]=head[x];
	head[x]=tot;ver[tot]=y;
	edge[tot]=z;
}
void dfs(int x,int val){
	if(val>maxn){
		pos=x;maxn=val;
	}
	for(int i=head[x];i;i=nex[i]){
		int y=ver[i];
		if(y==fa[x])continue;
		
		fa[y]=x;pre[y]=i;
		dfs(y,val+edge[i]);
	}
}
void reset(int x){//将直径上的边权取反，这样我们就不会在直径那条环上再找到第2条边了 
	if(pre[x]==0)return ;
	edge[pre[x]^1]=edge[pre[x]]=-1;
	reset(ver[pre[x]^1]);
}
void dp(int x){
	v[x]=1;
	for(int i=head[x];i;i=nex[i]){
		if(!v[ver[i]]){
			dp(ver[i]);
			maxn=max(maxn,f[ver[i]]+f[x]+edge[i]);
			f[x]=max(f[x],f[ver[i]]+edge[i]);
		}
	}
}
int main()
{
    cin>>n>>k;
    for(int i=1;i<n;i++){
	    int x,y,z;
		cin>>x>>y;z=1;
		add(x,y,z);add(y,x,z);
	}
	maxn=0;
	fa[1]=-1;
	dfs(1,0);
	maxn=0;memset(fa,0,sizeof(fa));
	pre_pos=pos;
	memset(pre,0,sizeof(pre));
	dfs(pos,0);
	long long ans=2*(n-1)-maxn+1;
	long long l=maxn;
	if(k==1){
		cout<<ans<<endl;
		return 0;
	}
	
	reset(pos);
	maxn=0;
	dp(1);
	ans=min(ans,2*n-l-maxn);
	cout<<ans<<endl;
	return 0;
}
