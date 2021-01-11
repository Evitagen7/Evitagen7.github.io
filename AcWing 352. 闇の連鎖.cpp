#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m,t,ans,top,head[N],nxt[N],ver[N],tot;
int d[N],f[N][100],cnt[N];
queue<int> q;
void add(int x,int y){
	ver[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void bfs()
{
    q.push(1);
    d[1]=1;
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=nxt[i])
        {
            int y=ver[i];
            if(d[y])	continue;
            d[y]=d[x]+1;
            f[y][0]=x;
            for(int j=1;j<=t;++j)
            	f[y][j]=f[f[y][j-1]][j-1];
            q.push(y);
        }
    }
}
int lca(int x,int y){
	if(d[x]>d[y]) swap(x,y);
	for(int i=t;i>=0;i--) if(d[f[y][i]]>=d[x]) y=f[y][i];
	if(x==y) return x;
	for(int i=t;i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
void dfs(int x,int fa){
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(fa==y) continue;
		dfs(y,x);
		cnt[x]+=cnt[y];
	}
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
	for(int i=1;i<=m;i++){
		int a,b;cin>>a>>b;
		cnt[a]++,cnt[b]++;//树上差分，计算该边所覆盖的附加边有多少 
		cnt[lca(a,b)]-=2;
	}
	dfs(1,0);
	for(int i=2;i<=n;i++){
		if(!cnt[i]) ans+=m;
		if(cnt[i]==1) ans++;
	}
	cout<<ans<<endl;
	return 0;
}
