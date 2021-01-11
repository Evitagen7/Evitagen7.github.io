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
inline bool dfs(int x,int las)//lasָ��ո��߹��������� 
{
	if(v[x]==1){
		v[x]=2,r[++cnt]=x,v2[x]=1;//��ʾ֮ǰ�Ѿ��߹�����ô����ڵ�Ϳ�����Ϊ���ڵ���˼�ܴ�  ����v2��ʾ����ڵ����ڵĻ������Ѿ��߹��� 
		return 1;
	}
	v[x]=1;
	for(int i=head[x];i;i=nxt[i])
		if(i!=((las-1)^1)+1&&dfs(ver[i],i)){ //��ǰ�߲�����һ���߶��ҵ�ǰ�ڵ��ڻ��� 
			if(v[x]!=2) //��ǰ�ڵ㲻���νӵ�
				r[++cnt]=x,s[cnt]=s[cnt-1]+edge[i],v2[x]=1;//r��ʾ���ϵĽڵ�ԭ����x 
			else{//���νӵ� 
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
	st=cnt+1,ans2=0,ans3=0;//st��ʾ�������Ŀ�ʼ 
	dfs(root,0);
	for(int i=st;i<=cnt;i++){//�������и��� 
		ans=0;
		tree_dp(r[i]);//��ֱ�� 
		ans2=max(ans2,ans);
		dp[i+cnt-st+1]=dp[i]=d[r[i]];
		s[i+cnt-st+1]=s[i+cnt-st]+s[i]-s[i-1];//����֮����� 
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
		if(!v2[i]) max_ans+=brt(i);//����ÿһ�������� 
//	for(int i=1;i<=n;i++)
//		cout<<s[i]<<" ";
//	cout<<endl;
	cout<<max_ans<<endl;
	return 0;
}
