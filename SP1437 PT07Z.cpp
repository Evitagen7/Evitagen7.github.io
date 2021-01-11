#include<bits/stdc++.h>
using namespace std;
#define N 10005
int n,d[N]={-1},deepest;
vector<int>edge[N];
void dfs(int now,int fa){
	d[now]=d[fa]+1;//���ӽڵ���ڸ��׽ڵ�+1 
	if(d[now]>d[deepest]) deepest=now;//���� 
	for(int i=0;i<edge[now].size();i++){
		int v;
		if((v=edge[now][i])!=fa)//�����ֻ���ѵ����׽ڵ�Ͳ������� 
			dfs(v,now);
	}
}
int main()
{
	cin>>n;
	for(int i=1,a,b;i<n;i++){
		cin>>a>>b;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	dfs(1,0);
	dfs(deepest,0);
	cout<<d[deepest]<<endl;
	return 0;
}
