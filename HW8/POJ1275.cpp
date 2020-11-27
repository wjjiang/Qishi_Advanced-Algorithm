#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

// Global parameters
const int N = 25;
int n, cnt[N], dis[N], R[N], num[N];
int tt, q[N];
bool st[N];

// Longest path
bool inline upd(int u, int v, int w) {
    if(dis[u] + w > dis[v]) {
        dis[v] = dis[u] + w;
        cnt[v] = cnt[u] + 1;
        if(cnt[v] >= 25) return false; 
        if(!st[v]) q[++tt] = v, st[v] = true;
    }
    return true;
}

// Search possibilities
bool spfa(int s24) {
    memset(dis, -0x3f, sizeof dis);
    memset(st, false, sizeof st);
    memset(cnt, 0, sizeof cnt);
    // stack by vector
    tt = 0;
    q[++tt] = 0; dis[0] = 0;
    while(tt) {
        int u = q[tt--];
        st[u] = false;
        // s[24] = s24
        if(u == 0 && !upd(0, 24, s24)) return false;
        if(u == 24 && !upd(24, 0, -s24)) return false;
        // s[i] - s[i - 1] >= 0
        if(u < 24 && !upd(u, u + 1, 0)) return false;
        // s[i] - s[i - 1] <= num[i]
        if(u > 0 && !upd(u, u - 1, -num[u])) return false;
        //s[i] - s[i - 8] >= R[i]
        if(u <= 16 && !upd(u, u + 8, R[u + 8])) return false;
        // s[i] + s[24] - s[24 - i] >= R[i]
        if(u >= 17 && !upd(u, u - 16, R[u - 16] - s24)) return false;
    }
    return true;
}

int main() {
    int T; cin >> T;
    while(T--) {
        memset(num, 0, sizeof num);
        for (int i = 1; i < N; i++) {
            scanf("%d", R + i);
        }
        cin >> n;
        for (int i = 1, x; i <= n; i++) {
            cin >> x;
            x++;
            num[x]++;
        }

        // Binary search to accelerate searching
        int l = 0, r = n;
        while(l < r) {
            int mid = (l + r) >> 1;
            if(spfa(mid)) r = mid;
            else l = mid + 1;
        }
        if(spfa(r)) cout << r << endl;
        else cout << "No Solution" << endl;
    }
    return 0;
}