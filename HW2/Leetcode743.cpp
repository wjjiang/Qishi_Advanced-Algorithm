class Solution {
private:
    int maxDelayTime = 0;
    
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        // Bellman-Ford
        // Step 1. initialize distance vector w/ INT_MAX
        vector<int> dist(N + 1, numeric_limits<int>::max());
        // Step 2. set distance to source to 0
        dist[K] = 0;
        // Step 3. loop through network
        for (int i = 0; i < N; i++) {
            for (const auto& time : times) {
                // u: source-node, v: target-node, w: weight
                int u = time[0], v = time[1], w = time[2];
                // update dist[v] by dist[u] + w
                if (dist[u] != numeric_limits<int>::max() && dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                }
            }
        }
        // Step 4. loop through network to calculate maximum delay time
        for (int i = 1; i <= N; i++) {
            maxDelayTime = max(maxDelayTime, dist[i]);
        }
        // Step 5. return
        return (maxDelayTime == numeric_limits<int>::max()) ? -1 : maxDelayTime;
    }
};