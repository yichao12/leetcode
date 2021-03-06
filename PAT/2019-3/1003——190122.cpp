//15:36—— 
//——16:28   13分其余答案错误
//更新最短路径数量的情况和更新最大营救队伍数量的情况不一样。
//所需条件也不一致。
 
//开始下面写错
//相等时，就可以更新最短数量了
//相等且，营救队伍更大时，才更新最大营救队伍。
 
//原点到原点的特殊情况解决后，的16分。 

//看了答案发现，最短路径数量的更新方法自己写的有问题。
//如果 d[u]+g[u][v]<d[v] 则到达v的最短路径条数，等于到达u的最短路径条数
//如果 d[u]+g[u][v]==d[v] 则num[v]+=num[u]; 

//上面这个点改完后25分
 

#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn =505;
const int inf = 1000000000;
bool isvisit[maxn]={false};
int g[maxn][maxn];
int d[maxn];
int rescue[maxn];
int mrescue[maxn]={0};  //表示到这个城市时，可以聚集的最大营救人员数量。 
int main()
{
	int n,m;
	int st,ed;
	int c1,c2,len;
	scanf("%d%d%d%d",&n,&m,&st,&ed);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&rescue[i]);
	}
	//开始忘记填充下面，导致10分钟的耗费。 
	fill(g[0],g[0]+maxn*maxn,inf);
	for(int i=0;i<m;i++)
	{
		scanf("%d%d%d",&c1,&c2,&len);
		g[c1][c2]=len;
		g[c2][c1]=len;
	}
	fill(d,d+maxn,inf);
	d[st]=0;
	//printf("%d %d %d** **\n",d[1],d[2],d[4]);
	mrescue[st]=rescue[st];
	int shortnum[maxn];
	shortnum[st]=1; 
	for(int i=0;i<n;i++)
	{
		int u =-1;
		int min =inf;
		for(int j=0;j<n;j++)
		{
			if(isvisit[j]==false&&d[j]<min)
			{
				min = d[j];
				u=j;
			}
		}
		if(u==-1)
		break;
		isvisit[u]=true;
		//printf("%d**%d\n",u,d[u]);
		for(int v=0;v<n;v++)
		{
			if(isvisit[v]==false&&g[u][v]!=inf)
			{
				if(d[u]+g[u][v]<d[v])
				{
					d[v]=d[u]+g[u][v];
					mrescue[v]=mrescue[u]+rescue[v];
					shortnum[v]=shortnum[u];
				}
				//开始下面写错
				//相等时，就可以更新最短数量了
				//相等且，营救队伍更大时，才更新最大营救队伍。	
				else if(d[u]+g[u][v]==d[v])
				{
					shortnum[v]+=shortnum[u];
					if(mrescue[u]+rescue[v]>mrescue[v]) 
					{
						mrescue[v]=mrescue[u]+rescue[v];
					}
						
				}
			}
		}
	}		
	printf("%d %d\n",shortnum[ed],mrescue[ed]);
	return 0;	
 } 
