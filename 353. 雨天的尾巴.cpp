#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int nxt[2*N],head[N],ver[N];
int X[N],Y[N],Z[N],val[N];
int n,m,cnt,t,nodecnt,r;
int dep[N],f[N][25];
int root[N],ans[N];
void add(int x,int y){
	ver[++cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
queue<int> q;
void bfs(){
	q.push(1);dep[1]=1;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i];
			if(dep[y]) continue;
			dep[y]=dep[x]+1;
			f[y][0]=x;
			for(int j=1;j<=t;j++)
			 	f[y][j]=f[f[y][j-1]][j-1];
			q.push(y);
		}
	}
}
int lca(int x,int y){
	if(dep[x]>dep[y]) swap(x,y);
	for(int i=t;i>=0;i--) if(dep[f[y][i]]>=dep[x]) y=f[y][i];
	if(y==x) return x;
	for(int i=t;i>=0;i--) if(f[y][i]!=f[x][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}

//线段树开点
struct Node{
    int ls,rs;
    int val,pos;
}tr[N*40];
int nodeCnt=0;

void insert(int &p,int l,int r,int x,int val){
	if(!p) 	p=++nodecnt;//动态建点 
	if(l==r){
		tr[p].val+=val;
		tr[p].pos=l;return;
	}
	int mid=l+r>>1;
	if(x<=mid) insert(tr[p].ls,l,mid,x,val);
	else 	   insert(tr[p].rs,mid+1,r,x,val);
	tr[p].val=max(tr[tr[p].ls].val,tr[tr[p].rs].val);
	tr[p].pos=tr[tr[p].ls].val>=tr[tr[p].rs].val?tr[tr[p].ls].pos:tr[tr[p].rs].pos;
} 

int merge(int p,int q,int l,int r){
	if(!p) return q;
	if(!q) return p;
	if(l==r){
		tr[p].val+=tr[q].val;
		tr[p].pos=tr[p].val?l:0;
		return p;
	}
	int mid=l+r>>1;
	tr[p].ls=merge(tr[p].ls,tr[q].ls,l,mid);
	tr[p].rs=merge(tr[p].rs,tr[q].rs,mid+1,r);
	tr[p].val=max(tr[tr[p].ls].val,tr[tr[p].rs].val);
    tr[p].pos=tr[tr[p].ls].val>=tr[tr[p].rs].val?tr[tr[p].ls].pos:tr[tr[p].rs].pos;
    return p;
}
void dfs(int x){
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(dep[y]>dep[x]){
			dfs(y);
			root[x]=merge(root[x],root[y],1,r);
		}
	}
	ans[x]=tr[root[x]].pos;
}
int main()
{
	cin>>n>>m;
	t=(int)(log(n)/log(2))+1;
	for(int i=1;i<n;i++){
		int a,b;cin>>a>>b;
		add(a,b),add(b,a);
	}
	bfs();
	for(int i=1;i<=n;i++) root[i]=++nodecnt;
	for(int i=1;i<=m;i++) 
		cin>>X[i]>>Y[i]>>Z[i],val[i]=Z[i];
	sort(val+1,val+m+1);
	r=unique(val+1,val+m+1)-(val+1);
	for(int i=1;i<=m;i++){
		int x=X[i],y=Y[i];
		int z=lower_bound(val+1,val+r+1,Z[i])-val;
		int p=lca(x,y);
		insert(root[x],1,r,z,1);
		insert(root[y],1,r,z,1);
		insert(root[p],1,r,z,-1);
		insert(root[f[p][0]],1,r,z,-1);
		
	}
	dfs(1);
	for(int i=1;i<=n;i++)
       printf("%d\n",val[ans[i]]);
	return 0;
}
