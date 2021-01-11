#include<bits/stdc++.h>
using namespace std;
const int N=500005;
int n,m,s;
int nxt[N*2],ver[N*2],head[N],cnt,t;
int d[N],f[N][20];
queue<int> q;
void add(int x,int y){
	ver[++cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
void build(){
	q.push(s);d[s]=1;
	while(q.size())
	{
		int x=q.front();q.pop();
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i];
			if(d[y]) continue;
			d[y]=d[x]+1;
			f[y][0]=x;
			for(int j=1;j<=t;j++)
				f[y][j]=f[f[y][j-1]][j-1];
			q.push(y);
		}
	}
}
int lca(int x,int y){
	if(d[x]>d[y]) swap(x,y);
	for(int i=t;i>=0;i--)
		if(d[f[y][i]]>=d[x]) y=f[y][i];//Ì§ÉýÉî¶È
	if(x==y) return x;
	for(int i=t;i>=0;i--)
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0]; 
}
int main()
{
	cin>>n>>m>>s;
	t=(int)(log(n)/log(2))+1;
	memset(d,0,sizeof(d));
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);add(b,a);
	}
	build();
	while(m--){
		int a,b;
		cin>>a>>b;
		cout<<lca(a,b)<<endl;
	}
	return 0;
}
