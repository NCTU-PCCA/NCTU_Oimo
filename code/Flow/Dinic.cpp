//Dinic
#define V 1000
struct edge{
    edge(){}
    edge(int a,int b,int c):to(a),cap(b),rev(c){}
    int to,cap,rev;
};
vector<edge> g[V];
int level[V];
int iter[V];
void add_edge(int from,int to,int cap){
    g[from].push_back(edge(to,cap,g[to].size()));
    g[to].push_back(edge(from,0,g[from].size()-1));
}
void bfs(int s){
    memset(level,-1,sizeof(level));
    queue<int>que;
    level[s]=0;
    que.push(s);
    while(!que.empty()){
        int v=que.front();
        que.pop();
        for(int q=0;q<g[v].size();q++){
            edge &e=g[v][q];
            if(e.cap>0&&level[e.to]<0){
                level[e.to]=level[v]+1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v,int t,int f){
    if(v==t)return f;
    for(int &q=iter[v];q<g[v].size();++q){
        edge &e=g[v][q];
        if(e.cap>0&&level[v]<level[e.to]){
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0){
                e.cap-=d;
                g[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}
int max_flow(int s,int t){
    int flow=0;
    for(;;){
        bfs(s);
        if(level[t]<0)return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while((f=dfs(s,t,1e9))>0)
              flow+=f;
    }
}