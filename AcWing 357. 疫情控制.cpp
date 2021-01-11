#include<bits/stdc++.h>
using namespace std;
#define mk(a,b) make_pair(a,b)
const int N=50000+200;
int head[N<<1],ver[N<<1],nxt[N<<1],edge[N<<1],tot;
int deep[N],fa[N][22],cnt,n,m,a[N],sum;
int tot2,tot3,tot4,t;
long long dis[N][22],Free[N],need2[N];
bool vis[N],okk,need[N];
pair<long long,int> h[N];//���Եִ���ڵ�Ľڵ�
void add(int x,int y,int z){
	ver[++cnt]=y;
	edge[cnt]=z;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
inline void bfs()
{
    queue<int> q;
    q.push(1);
    deep[1]=1;
    while(q.size())
    {
        int x=q.front();
        q.pop();
        for(int i=head[x]; i; i=nxt[i]) //����x�ĳ���
        {
            int y=ver[i];//����
            if(deep[y])
                continue;
            deep[y]=deep[x]+1;
            fa[y][0]=x,dis[y][0]=edge[i];//DP״̬
            for(int j=1; j<=t; j++)
            {
                fa[y][j]=fa[fa[y][j-1]][j-1];
                dis[y][j]=dis[y][j-1]+dis[fa[y][j-1]][j-1];
            }//DP
            q.push(y);
        }
    }
}
bool dfs(int x){//�ж��Ƿ����нڵ㶼�ܵ����� 
	bool ok=false;
	if(vis[x]) return true;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(deep[y]<deep[x]) continue;
		ok=true;
		if(!dfs(y))return false;
	}
	if(!ok) return false;
	return true;
}
bool check(long long s){
    memset(h,0,sizeof(h));
    memset(need,0,sizeof(need));
    memset(vis,false,sizeof(vis));
    memset(need2,0,sizeof(need2));
    memset(Free,0,sizeof(Free));
    tot2=tot3=tot4=0;
    for(int i=1;i<=m;i++){
    	long long ans=0,x=a[i];
    	for(int k=t;k>=0;k--) 
			if(fa[x][k]>1&&ans+dis[x][k]<=s) ans+=dis[x][k],x=fa[x][k];//�ҵ� ���޶�ʱ������������ 
    	if(fa[x][0]==1&&ans+dis[x][0]<=s) h[++tot2]=mk(s-(ans+dis[x][0]),x);//�������������ʣ��ʱ���λ�� 
    	else vis[x]=true;
    }
    for(int i=head[1];i;i=nxt[i])	if(!dfs(ver[i])) need[ver[i]]=true;
    sort(h+1,h+1+tot2); 
    for(int i=1;i<=tot2;i++) 
		if(need[h[i].second]&&h[i].first<dis[h[i].second][0]) need[h[i].second]=0;//�����˸��ڵ�
		else Free[++tot3]=h[i].first;//���ƶ�
 	for(int i=head[1];i;i=nxt[i]) 	
	 	if(need[ver[i]]) need2[++tot4]=dis[ver[i]][0];//��Ҫ���Ƶ�ʱ�� 
 	if(tot3<tot4) return false;//���Ӳ����� 
	sort(Free+1,Free+1+tot3);//���տ���������С��������
	sort(need2+1,need2+1+tot4);//פ�ؽڵ㰴��������۴�С��������
	int i=0,j=0;
	while(i<=tot4&&j<=tot3)
		if(Free[j]>=need2[i]) i++,j++;//����ȥפ�� 
		else j++;
	if(i>tot4) return true;//ȫ��פ������ 
	else return false;
}
long long query(){
	long long l=1,r=sum,mid=0;
	while(l<r){
		mid=l+r>>1;
		if(check(mid))
			r=mid,okk=true;
		else l=mid+1;
	}
	return r;
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);add(b,a,c);
		sum+=c;
	}
	cin>>m;
	for(int i=1;i<=m;i++) scanf("%d",&a[i]);
	okk=false;
	t=log2(n)+1;
	bfs();
	long long ans=query();
	if(okk) cout<<ans<<endl;
	else cout<<-1<<endl;
	return 0;
}
