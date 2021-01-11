#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,T;
int nxt[N*2],ver[N*2],head[N],edge[N*2],cnt,verx[N*2];
int dep[N],dist[N],f[N][20],vist[N*2],vis[N];
int dfsx[N],tot,idf[N];//dfsx存储时间戳，idf存储该戳对应的上一个节点是哪个节点
long long ans; 
int kkk[N];
std::set<int> st;
std::set<int>::iterator it;
void add(int x,int y,int z){
	ver[++cnt]=y;
	edge[cnt]=z;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
queue<int> q;
void bfs(){
	q.push(1),dep[1]=1,dist[1]=0;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i];
			if(dep[y]) continue;
			dep[y]=dep[x]+1;
			dist[y]=dist[x]+edge[i];
			f[y][0]=x;
			for(int j=T;j>=0;j--)
				f[y][j]=f[f[y][j-1]][j-1];
			q.push(y);
		}
	}
}
int lca(int x,int y){
	if(dep[x]>dep[y]) swap(x,y);
	for(int i=T;i>=0;i--) if(dep[f[y][i]]>=dep[x]) y=f[y][i];
	if(x==y) return x;
	for(int i=T;i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0]; 
}
int sum(int x,int y){
	return dist[x]+dist[y]-2*dist[lca(x,y)];
}
void add(int x){
	x=dfsx[x];
    if(!vis[idf[x]]) st.insert(x);
    int y=idf[(it=st.lower_bound(x))==st.begin() ? *--st.end():*--it];
    int z=idf[(it=st.upper_bound(x))==st.end() ? *st.begin():*it];
    if(vis[idf[x]]) st.erase(x);
    x=idf[x];
    int d=sum(x,y)+sum(x,z)-sum(y,z);
    if(!vis[x]) vis[x]=1,ans+=d;
    else  vis[x]=0,ans-=d;
	
}
void dfs(int x){
	dfsx[x]=++tot;
	idf[tot]=x;
	kkk[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(kkk[y]) continue;
		dfs(y);
	}
}
int main()
{
	cin>>n;
	int T=(int)(log(n)/log(2))+1;
	for(int i=1;i<n;i++){
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z);add(y,x,z);
	}	
	bfs();
	dfs(1);
	cin>>m;
	for(int i=1;i<=m;i++){
		int x;char opt;
		cin>>opt;
		if(opt=='?') cout<<ans/2<<endl;
		else {
			cin>>x;
			 add(x);
		}
	}
	return 0;
}
