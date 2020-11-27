class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        // Bellman-Ford
        // Step 1. initialize distance vector w/ INT_MAX
        vector<int> dist(n, numeric_limits<int>::max());
        // Step 2. set distance to source to 0
        dist[src] = 0;
        // Step 3. loop up to K times
        for(int i = 0; i <= K; i++) {
            // Step 3.1. change distance vector
            vector<int> dist_chg(dist);
            // Step 3.2. loop through flights network
            for(auto flight: flights) {
                int u = flight[0], v = flight[1], w = flight[2];
                // update elements in distance_change vector
                if (dist[u] != numeric_limits<int>::max() && dist_chg[v] > dist[u] + w) {
                    dist_chg[v] = dist[u] + w;
                }
            }
            // Step 3.3. update distance vector w/ distance_change vector
            dist = dist_chg;
        }
        // Step 4. return
        return (dist[dst] == numeric_limits<int>::max()) ? -1 : dist[dst];
    }
};