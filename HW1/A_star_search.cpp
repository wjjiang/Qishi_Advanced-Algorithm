#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using pair_item = std::pair<char, double>;
using tuple_item = std::tuple<char, char, double>;

// Step 1. modify STL's priority_queue template, can remove any element in heap
template<typename T>
class heapq : public std::priority_queue<T, std::vector<T>, decltype([](auto e1, auto e2){return e1.second > e2.second;})> {
public:    
    template <typename Pred>
    bool remove_if(Pred pred) {
        const auto old_size = this->size();
        this->c.erase(std::remove_if(this->c.begin(), this->c.end(), pred), this->c.end());
        if (old_size == this->size()) return false;
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
        return true;
    }
};

// Step 2. construct edges
std::unordered_map<char, std::vector<pair_item>> construct_edge(const std::vector<tuple_item>& edges) {
    std::unordered_map<char, std::vector<pair_item>> mapped_edges;
    for (const auto& edge : edges) {
        mapped_edges[std::get<0>(edge)].emplace_back(std::get<1>(edge), std::get<2>(edge));
        mapped_edges[std::get<1>(edge)].emplace_back(std::get<0>(edge), std::get<2>(edge));
    }
    return mapped_edges;
}

// Step 3. construct A* function
void A_star(const std::vector<tuple_item>& edges, std::unordered_map<char, double>& h, char source, char target) {
    // Step 3.1. convert edges into mapped format
    std::unordered_map<char, std::vector<pair_item>> mapped_edges = construct_edge(edges);

    // Step 3.2. initialize
    // Step 3.2.1. X = {source}
    std::unordered_set<char> X;
    X.emplace(source);
    // Step 3.2.2. g() = infinity except g(source)=0
    std::unordered_map<char, double> g;
    for (auto it = h.begin(); it != h.end(); ++it)
        g[it->first] = (it->first == source) ? 0 : std::numeric_limits<double>::max();
    // Step 3.2.3. f(source) = h(source)
    std::unordered_map<char, double> f;
    f[source] = h[source];
    // Step 3.2.4. priority_queue w/ {source, f(source)}
    heapq<pair_item> pq;
    pq.emplace(source, f[source]);

    // Step 3.3. iterate & record path
    std::vector<char> path;
    while (pq.top().first != target) {
        // Step 3.3.1. get pq's top
        pair_item V = pq.top();
        pq.pop();
        // Step 3.3.2. X to include V's 1st element, record into path
        char v = V.first;
        X.emplace(v);
        path.emplace_back(v);
    
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
                // Step 3.3.3.2.1. update g(w) to g_prime
                g[w] = g_prime;
                // Step 3.3.3.2.2. calculate f(w) = g(w) + h(w)
                double f_w = g[w] + h[w];
                // Step 3.3.3.2.3. update priority_queue
                // Step 3.3.3.2.3.1. define lambda function for remove_if purpose
                auto first_is_w = [w](const auto& p) {
                    return p.first == w;
                };
                // Step 3.3.3.2.3.2. remove if w exists in pq
                pq.remove_if(first_is_w);
                // Step 3.3.3.2.3.3. push {w, f(w)} pair into pq
                pq.emplace(w, f_w);
            }
        }
    }

    // Step 4. print out shortest path and minimum distance
    std::cout << "The shortest path: (";
    for (char c : path) {
        std::cout << c << " -> ";
    }
    std::cout << target << ") has a total distance of " << g[target] << std::endl;
}

int main() {
    // edges
    std::vector<tuple_item> edges = {
        {'A', 'B', 6},
        {'A', 'F', 3},
        {'B', 'C', 3},
        {'B', 'D', 2},
        {'C', 'D', 1},
        {'C', 'E', 5},
        {'D', 'E', 8},
        {'E', 'I', 5},
        {'E', 'J', 5},
        {'F', 'G', 1},
        {'F', 'H', 7},
        {'G', 'I', 3},
        {'H', 'I', 2},
        {'I', 'J', 3}
    };
    // heuristics
    std::unordered_map<char, double> h;
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
    A_star(edges, h, 'A', 'J');

    return 0;
}