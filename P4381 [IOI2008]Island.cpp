#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
#define ll long long 
ll cnt,n,edge[N*2],ver[N*2],head[N],nxt[N*2];
ll tot,max_ans,ans,ans2,st,ans3;
ll v[N],v2[N],r[N],s[N],dp[2*N];
ll d[N];
inline void add(int x,int y,int z){
	ver[++tot]=y;
	edge[tot]=z;
	nxt[tot]=head[x];
	head[x]=tot;
}
inline bool dfs(int x,int las)//las指向刚刚走过的那条边 
{
	if(v[x]==1){
		v[x]=2,r[++cnt]=x,v2[x]=1;//表示之前已经走过，那么这个节点就可以作为根节点了思密达  其中v2表示这个节点所在的基环树已经走过了 
		return 1;
	}
	v[x]=1;
	for(int i=head[x];i;i=nxt[i])
		if(i!=((las-1)^1)+1&&dfs(ver[i],i)){ //当前边不是上一条边而且当前节点在环上 
			if(v[x]!=2) //当前节点不是衔接点
				r[++cnt]=x,s[cnt]=s[cnt-1]+edge[i],v2[x]=1;//r表示环上的节点原先是x 
			else{//是衔接点 
				s[st-1]=s[st]-edge[i];
				return 0;
			}
			return 1;
		}
	return 0;
}
inline void tree_dp(int x){
	v2[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(v2[y]) continue;
		tree_dp(y);
		ans=max(ans,d[x]+d[y]+edge[i]);
		d[x]=max(d[x],d[y]+edge[i]);
	}
}
inline ll brt(int root){
	st=cnt+1,ans2=0,ans3=0;//st表示基环树的开始 
	dfs(root,0);
	for(int i=st;i<=cnt;i++){//将环进行复制 
		ans=0;
		tree_dp(r[i]);//找直径 
		ans2=max(ans2,ans);
		dp[i+cnt-st+1]=dp[i]=d[r[i]];
		s[i+cnt-st+1]=s[i+cnt-st]+s[i]-s[i-1];//两点之间距离 
	}
	deque<int>q;
	for(int i=st;i<=2*cnt-st+1;i++){
		while(q.size()&&q.front()<=i-cnt+st-1)	
			q.pop_front();
		if(q.size()) 
			ans3=max(ans3,dp[i]+dp[q.front()]+s[i]-s[q.front()]);
		while(q.size()&&dp[q.back()]-s[q.back()]<=dp[i]-s[i]) 
			q.pop_back();
		q.push_back(i);
	}
	//cout<<ans2<<" "<<ans3<<endl; 
	return max(ans2,ans3);
}
int main()
{
	cin>>n;
	for(int i=1,a,b;i<=n;i++){
		scanf("%d%d",&a,&b);
		add(i,a,b);add(a,i,b);
	}
	for(int i=1;i<=n;i++)
		if(!v2[i]) max_ans+=brt(i);//搜索每一个基环树 
//	for(int i=1;i<=n;i++)
//		cout<<s[i]<<" ";
//	cout<<endl;
	cout<<max_ans<<endl;
	return 0;
}
