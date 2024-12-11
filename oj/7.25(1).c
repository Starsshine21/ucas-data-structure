#include<stdio.h>
int graph[5005][5005];
int s[5005];
int fst[5005];
int lst[5005];
int indeg[5005];
void add(int u,int v){
    if(u==0||v==0)return ;
    if(graph[u][v]==1)return ;
    if(u==v)return ;
    graph[u][v]=1;
    indeg[v]++;
}
int n;
int stk[5005];
int stkp;
int topo(){
    int remain=n;
    int i;
    for(i=1;i<=n;i++)
        if(indeg[i]==0)
            stk[++stkp]=i;
    while(stkp>0){
        int u=stk[stkp];
        stkp--;
        remain--;
        int j;
        for(j=1;j<=n;j++){
            if(graph[u][j]==1){
                graph[u][j]=0;
                indeg[j]--;
                if(indeg[j]==0){
                    stk[++stkp]=j;
                }
            }
        }
    }
    return remain;
}

int main(){
    scanf("%d",&n);
    char ch;int tp=0;
    while(1){
        scanf("%d%c",&s[tp++],&ch);
        if(ch!=' ')break;
    }
    int i,j;
    for(i=0;i<=n;i++){
        scanf("%d",&fst[i]);
    }
    for(i=0;i<=n;i++){
        scanf("%d",&lst[i]);
    }
    for(i=1;i<=n;i++){
        if(fst[i]>lst[i])continue;
        for(j=fst[i];j<lst[i];j++){
            add(i,s[j]);
        }
    }
    int ans=topo();
    if(ans==0)printf("no");
    else printf("yes");
    return 0;
}

