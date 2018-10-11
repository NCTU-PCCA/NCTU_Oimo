#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> P;
struct edge{
    edge(){}
    edge(int a,int b,int c,int d):to(a),cap(b),cost(c),rev(d){}
    int to,cap,cost,rev;
};
#define V 210
#define inf 1000000000000000
vector<edge> g[V];
int h[V],dist[V],prev_v[V],prev_e[V];
void add_edge(int from,int to,int cap,int cost){
    g[from].push_back(edge(to,cap,cost,g[to].size()));
    g[to].push_back(edge(from,0,-cost,g[from].size()-1));
}
int min_costflow(int s,int t,int f){
    int res=0;
    memset(h,0,sizeof(h));
    while(f>0){
        priority_queue<P,vector<P>,greater<P> >que;
        fill(dist,dist+V,inf);
        dist[s]=0;
        que.push(P(dist[s],s));
        while(!que.empty()){
            P p=que.top();
            que.pop();
            int v=p.second;
            if(dist[v]<p.first)continue;
            for(int i=0;i<g[v].size();++i){
                edge &e=g[v][i];
                if(e.cap>0&&dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
                    dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
                    prev_v[e.to]=v;
                    prev_e[e.to]=i;
                    que.push(P(dist[e.to],e.to));
                }
            }
        }
        if(dist[t]==inf) return -1;
        for(int v=0;v<V;++v)h[v]+=dist[v];
        int d=f;
        for(int v=t;v!=s;v=prev_v[v]) d=min(d,g[prev_v[v]][prev_e[v]].cap);
        f-=d;
        res+=d*h[t];
        for(int v=t;v!=s;v=prev_v[v]){
            edge &e=g[prev_v[v]][prev_e[v]];
            e.cap-=d;
            g[v][e.rev].cap+=d;
        }
    }
    return res;
}
#undef int
int main()
{
#define int long long
    int T,n,m,cost,l,s,t,ans;
    cin>>T;
    while(T--){
    	cin>>n>>m;
        for(int q=0;q<V;++q)g[q].clear();
        s=m+n;
        t=m+n+1;
        for(int i=0;i<n;++i)
        	for(int j=0;j<m;++j){
        		cin>>cost;
        		if(cost>0)
        			add_edge(n+j,i,1,cost);
        	}
        for(int i=0;i<m;++i){
        	cin>>l;
        	add_edge(s,n+i,l,0);
        }
        for(int i=0;i<n;++i)
        	add_edge(i,t,1,0);
        ans=min_costflow(s,t,n);
        cout<<ans<<endl;
    }
    return 0;
}

