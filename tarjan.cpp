#include<bits/stdc++.h>
using namespace std;
void tarjan(int x){
	v[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(v[y]) continue;
		d[y]=d[x]+edge[i];
		tarjan(y);
		f[y]=x;
	}
	for(int i=0;i<query[x].size();i++){
		int y=query[x][i],id=query_id[x][i];
		if(v[y]==2){
			int lca=get(y);
			ans[id]=min(ans[id],d[x]+d[y]-2*d[lca]);
		}
	}
}
int main()
{
	for
	return 0;
}
