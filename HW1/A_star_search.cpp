#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;
using pair_item = pair<char, double>;
using tuple_item = tuple<char, char, double>;

// Step 1. modify STL's priority_queue template to include find & remove functionality
template<typename T>
class heapq : public priority_queue<T, vector<T>, greater<>> {
public:
    bool eleExist(const T& value) {
        auto it = lower_bound(this->c.begin(), this->c.end(), value);
        if (it != this->c.end())
            return true;
        else
            return false;
    }
    
    bool remove(const T& value) {
        auto it = lower_bound(this->c.begin(), this->c.end(), value);
        if (it != this->c.end()) {
            this->c.erase(it);
            make_heap(this->c.begin(), this->c.end(), this->comp);
            return true;
        }
        else {
            return false;
        }
    }
};

// Step 2. construct edges
unordered_map<char, vector<pair_item>> construct_edge(const vector<tuple_item>& edges) {
    unordered_map<char, vector<item>> mapped_edges;
    for (const auto& edge : edges) {
        mapped_edges[get<0>(edge)].emplace_back(get<1>(edge), get<2>(edge));
        mapped_edges[get<1>(edge)].emplace_back(get<0>(edge), get<2>(edge));
    }
    return mapped_edges;
}

// Step 3. construct A* function
void A_star(int vertices, const vector<tuple_item>& edges, unordered_map<char, double>& h, char source, char target) {
    // Step 3.1. convert edges into mapped format
    unordered_map<char, vector<pair_item>> mapped_edges = construct_edge(edges);

    // Step 3.2. initialize
    // Step 3.2.1. X = {source}
    unordered_set<char> X;
    X.emplace(source);
    // Step 3.2.2. g() = infinity except g(source)=0
    unordered_map<char, double> g;
    for (auto it = h.begin(); it != h.end(); ++it)
        g[it->first] = (it->first == source) ? 0 : numeric_limits<double>::max();
    // Step 3.2.3. f(source) = h(source)
    unordered_map<char, double> f;
    f[source] = h[source];
    // Step 3.2.4. priority_queue w/ {source, f(source)}
    heapq<pair_item> pq;
    pq.emplace(source, f[source]);

    // Step 3.3. iterate
    while (pq.top().first != target) {
        // Step 3.3.1. get pq's top
        pair_item V = pq.top();
        pq.pop();
        // Step 3.3.2. X to include V's 1st element
        char v = V.first;
        double f_v = V.second;
        X.emplace(v);
        // Step 3.3.3. loop V's 1st element's edges
        for (auto ele : mapped_edges[v]) {
            char w = ele.first;
            double l_vw = ele.second;
            // Step 3.3.3.0. exclude those edges inside X
            if (X.count(w))
                continue;
            // Step 3.3.3.1. g'(w) = g(v) + L_vw
            double g_prime = g[v] + l_vw;
            // Step 3.3.3.2. 2 updates if g'(w) < g(w)
            if (g_prime < g[w]) {
                // update g[w] to g_prime
                g[w] = g_prime;
                // calculate f(w) = g(w) + h(w)
                double f_w = g[w] + h[w];
                // update priority_queue
                if (pq.eleExist(w)) {
                    pq.remove(w);
                    pq.emplace(w, f_w);
                }
            }
        }
    }

    // Step 4. return minimum path
    cout << "The minimum path = " << g[target] << endl;
}

int main() {
    int vertices = 10;
    // edges
    vector<tuple_item> edges = {
        make_tuple('A', 'B', 6),
        make_tuple('A', 'F', 3),
        make_tuple('B', 'C', 3),
        make_tuple('B', 'D', 2),
        make_tuple('C', 'D', 1),
        make_tuple('C', 'E', 5),
        make_tuple('D', 'E', 8),
        make_tuple('E', 'I', 5),
        make_tuple('E', 'J', 5),
        make_tuple('F', 'G', 1),
        make_tuple('F', 'H', 7),
        make_tuple('G', 'I', 3),
        make_tuple('H', 'I', 2),
        make_tuple('I', 'J', 3)
    };
    // heuristics
    unordered_map<char, double> h;
    h['A'] = 10;
    h['B'] = 6;
    h['C'] = 5;
    h['D'] = 7;
    h['E'] = 3;
    h['F'] = 6;
    h['G'] = 5;
    h['H'] = 3;
    h['I'] = 1;
    h['J'] = 0;
    // Call A* function
    A_star(vertices, edges, h, 'A', 'J');

    return 0;
}