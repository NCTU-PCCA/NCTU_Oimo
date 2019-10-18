//Not tested yet
const int MAXN = 1005;
int n, m;
struct node {
    int num;
} a[MAXN][MAXN];
struct segTree2D {
    node tree[4 * MAXN][4 * MAXN];
    void build() { build_x(1, 1, n); }
    void update_node_x(int index_x, int index_y) {
        tree[index_x][index_y].num =
            tree[index_x * 2][index_y].num + tree[index_x * 2 + 1][index_y].num;
    }
    void update_node_y(int index_x, int index_y) {
        tree[index_x][index_y].num =
            tree[index_x][index_y * 2].num + tree[index_x][index_y * 2 + 1].num;
    }
    void build_x(int vx, int lx, int rx) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            build_x(vx * 2, lx, mx);
            build_x(vx * 2 + 1, mx + 1, rx);
        }
        build_y(vx, lx, rx, 1, 1, m);
    }
    void build_y(int vx, int lx, int rx, int vy, int ly, int ry) {
        if (ly == ry) {
            if (lx == rx)
                tree[vx][vy] = a[lx][ly];
            else
                update_node_x(vx, vy);
        } else {
            int my = (ly + ry) / 2;
            build_y(vx, lx, rx, vy * 2, ly, my);
            build_y(vx, lx, rx, vy * 2 + 1, my + 1, ry);
            update_node_y(vx, vy);
        }
    }
    void update(int x, int y){
        //Add modify the corresponding a first.
        update_x(1,1,n,x,y);
    }
    void update_x(int vx, int lx, int rx, int x, int y) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            if (x <= mx)
                update_x(vx * 2, lx, mx, x, y);
            else
                update_x(vx * 2 + 1, mx + 1, rx, x, y);
        }
        update_y(vx, lx, rx, 1, 1, m, x, y);
    }
    void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y) {
        if (ly == ry) {
            if (lx == rx)
                tree[vx][vy] = a[lx][ly];
            else
                update_node_x(vx, vy);
        } else {
            int my = (ly + ry) / 2;
            if (y <= my)
                update_y(vx, lx, rx, vy * 2, ly, my, x, y);
            else
                update_y(vx, lx, rx, vy * 2 + 1, my + 1, ry, x, y);
            update_node_y(vx, vy);
        }
    }
    int ans_node(int vx, int vy){
        return tree[vx][vy].num;
    }
    int ans(int lx, int rx, int ly, int ry){
        return ans_x(1, 1,n,lx,rx,ly,ry);
    }
    int ans_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry){
        if(lx > rx){
            return 0;
        }
        if(lx == tlx && rx == trx){
            return ans_y(vx, 1, 1,m,ly,ry);
        }
        int tmx = (tlx+trx)/2;
        return ans_x(vx*2, tlx, tmx, lx, min(rx,tmx), ly, ry)+
            ans_x(vx*2+1, tmx+1, trx, max(lx,tmx+1), rx, ly, ry);
    }
    int ans_y(int vx, int vy, int tly, int try_, int ly, int ry){
        if (ly>ry)
            return 0;
        if(ly == tly&&ry == try_){
            return ans_node(vx, vy);
        }
        int tmy = (tly+try_)/2;
        return ans_y(vx,vy*2,tly, tmy,ly, min(ry,tmy))+
        ans_y(vx,vy*2+1,tmy+1, try_,max(ly,tmy+1),ry);
    }
} T;