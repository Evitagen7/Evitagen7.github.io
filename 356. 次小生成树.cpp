#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
long long INF=1e16;
int n,m,T,cnt;
long long ans,res,val1,val2,dp[N][25][2];
int fa[N*2],ver[N*2],edge[N*2],nxt[N*2],head[N];
int f[N][25],dep[N],vis[N];
struct node{
	int x,y,z;
}tr[N];
bool cmp(node a,node b){
	return a.z<b.z;
}
int get(int x){
	if(x==fa[x]) return x;
	else return fa[x]=get(fa[x]);
}
void add(int x,int y,int z){
	ver[++cnt]=y;
	edge[cnt]=z;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
void kru(){
	for(int i=1;i<=m;i++){
		int x=get(tr[i].x);
		int y=get(tr[i].y);
		if(x==y) continue;
		fa[x]=y;
		vis[i]=1;
		ans+=tr[i].z;
		add(tr[i].x,tr[i].y,tr[i].z);
		add(tr[i].y,tr[i].x,tr[i].z);
	}
}
queue<int> q;
void bfs(){
	q.push(1);dep[1]=0;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i];
			if(dep[y]) continue;
			dep[y]=dep[x]+1;
			f[y][0]=x;
			dp[y][0][0]=edge[i]; dp[y][0][1]=-INF;//0为最大边权，1为次大边权 
			q.push(y); 
			for(int j=1;j<=T;j++){
				f[y][j]=f[f[y][j-1]][j-1];
				if(dp[y][j-1][0]!=dp[f[y][j-1]][j-1][0]){
					dp[y][j][0]=max(dp[y][j-1][0],dp[f[y][j-1]][j-1][0]);
					dp[y][j][1]=max(dp[y][j-1][0],dp[f[y][j-1]][j-1][0]);
				}
				else{
					dp[y][j][0]=dp[y][j-1][0];
					dp[y][j][1]=max(dp[y][j-1][1],dp[f[y][j-1]][j-1][1]);
				}
			}
		}
	}
}
void query(int x){
	if(x>val1) val2=val1,val1=x;
	else if(x>val2&&x!=val1) val2=x;
}
void update(int x,int i){
	query(dp[x][i][0]);
	query(dp[x][i][1]);
}
void lca(int x,int y){
	val1=val2=-INF;
	if(dep[x]>dep[y]) swap(x,y);
	while(dep[y]>dep[x])
        {
            int t=(int)log2(dep[y]-dep[x]);
            update(y,t),y=f[y][t];
        } 
	if(x==y) return;
	for(int i=T;i>=0;i--){
		if(f[y][i]!=f[x][i]){
			update(x,i),update(y,i);
			y=f[y][i],x=f[x][i];
		}
	}  
	update(x,0),update(y,0);
}
int main()
{
	cin>>n>>m;
	T=(int)(log(n)/log(2))+1;
	for(int i=1;i<=m;i++){
		fa[i]=i;
		cin>>tr[i].x>>tr[i].y>>tr[i].z;
	}
	sort(tr+1,tr+m+1,cmp);
	kru();
	bfs();
	res=INF;
	for(int i=1;i<=m;i++){
		if(!vis[i]){
			lca(tr[i].x,tr[i].y);
			if(val1!=tr[i].z)
			res=min(res,ans-val1+tr[i].z);
			else 
			res=min(res,ans-val2+tr[i].z);
		}
	}
	cout<<res<<endl;
	return 0;
}
