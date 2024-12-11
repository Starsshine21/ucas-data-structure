#include<stdio.h>
#include<stdlib.h>
typedef struct arcnode{
    struct arcnode* next;
    int v;
}arcnode;
struct node{
    int u;
    arcnode* head;
}node[5005];
void add(int u,int v){
    arcnode* nv=(arcnode*)malloc(sizeof(arcnode));
    nv->v=v;
    if(node[u].head==NULL){
        node[u].head=(arcnode*)malloc(sizeof(arcnode));
        node[u].head->next=NULL;
    }
    nv->next=node[u].head;
    node[u].head=nv;
}
int len[5005];
int dfs(int u){
    int len=0;
    for(arcnode* j=node[u].head;j!=NULL;j=j->next){
        int temp=dfs(j->v)+1;
        if(temp>len)len=temp;
    }
    return len;
}
int main(){
    int n;
    scanf("%d",&n);
    while(1){
        int u,v;char ch;
        scanf("%d-%d%c",&u,&v,&ch);
        add(u,v);
        if(ch!=',')break;
    }
    for(int i=1;i<=n;i++){
        len[i]=dfs(i);
    }
    for(int i=1;i<n;i++)printf("%d,",len[i]);
    if(n>0)printf("%d",len[n]);
    return 0;
}

