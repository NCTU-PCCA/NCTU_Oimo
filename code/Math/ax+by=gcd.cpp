pair<int,int> extgcd(int a, int b){
    if (b==0) return {1,0};
    int k = a/b;
    pair<int,int> p = extgcd(b,a-k*b);
    return { p.second, p.first - k*p.second };
}
int inv[maxN];
LL invtable(int n,LL P){
	inv[1]=1;
	for(int i=2;i<n;++i)
		inv[i]=(P-(P/i))*inv[P%i]%P;
}
