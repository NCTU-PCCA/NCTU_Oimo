#define F(n) Fi(i, n)
#define Fi(i, n) Fl(i, 0, n)
#define Fl(i, l, n) for(int i = l ; i < n ; ++i)
#include <bits/stdc++.h>
using namespace std;
int D, quota[205], weight[205][5];
int S, scoretodep[12005][205], score[5];
int P, prefer[12005][85], iter[12005];
int ans[12005];
typedef pair<int, int> PII;
map<int, int> samescore[205];
typedef priority_queue<PII, vector<PII>, greater<PII>> QQQ;
QQQ pri[205];
void check(int d) {
	PII t = pri[d].top();
	int v;
	if (pri[d].size() - samescore[d][t.first] + 1 <= quota[d]) return;
	while (pri[d].top().first == t.first) {
		v = pri[d].top().second;
		ans[v] = -1;
		--samescore[d][t.first];
		pri[d].pop();
	}
}
void push(int s, int d) {
	if (pri[d].size() < quota[d]) {
		pri[d].push(PII(scoretodep[s][d], s));
		ans[s] = d;
		++samescore[s][scoretodep[s][d]];
	} else if (scoretodep[s][d] >= pri[d].top().first) {
		pri[d].push(PII(scoretodep[s][d], s));
		ans[s] = d;
		++samescore[s][scoretodep[s][d]];
		check(d);
	}
}
void f() {
	int over;
	while (true) {
		over = 1;
		Fi (q, S) {
			if (ans[q] != -1 || iter[q] >= P) continue;
			push(q, prefer[q][iter[q]++]);
			over = 0;
		}
		if (over) break;
	}
}
main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int sadmit, stof, dexceed, dfew;
	while (cin >> D, D) { // Beware of the input format or judge may troll us.
		sadmit = stof = dexceed = dfew = 0;
		memset(iter, 0, sizeof(iter));
		memset(ans, 0, sizeof(ans));
		Fi (q, 205) {
			pri[q] = QQQ();
			samescore[q].clear();
		}
		cin >> S >> P;
		Fi (q, D) {
			cin >> quota[q];
			Fi (w, 5) cin >> weight[q][w];
		}
		Fi (q, S) {
			Fi (w, 5) cin >> score[w];
			Fi (w, D) {
				scoretodep[q][w] = 0;
				F (5) scoretodep[q][w] += weight[w][i] * score[i];
			}
		}
		Fi (q, S) Fi (w, P) {
			cin >> prefer[q][w];
			--prefer[q][w];
		}
		f();
		Fi (q, D) sadmit += pri[q].size();
		Fi (q, S) if (ans[q] == prefer[q][0]) ++stof;
		Fi (q, D) if (pri[q].size() > quota[q]) ++dexceed;
		Fi (q, D) if (pri[q].size() < quota[q]) ++dfew;
		cout << sadmit << ' ' << stof << ' ' << dexceed << ' ' << dfew << '\n';
	}
}








