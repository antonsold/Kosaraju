#include <iostream>
#include <vector>

enum colors{white, gray, black};

using namespace std;

void dfs_visit_first(vector<vector<int> > &adj_list, vector<colors> &colors_list, vector<int> &order, int vertex){
    colors_list[vertex] = gray;
    for (auto i : adj_list[vertex]){
        if (colors_list[i] == white)
            dfs_visit_first(adj_list, colors_list, order, i);
    }
    order.push_back(vertex);
    colors_list[vertex] = black;
}

void dfs_visit_second(vector<vector<int> > &inverted_adj_list, vector<colors> &colors_list, vector<int> &components, int component, int vertex){
    colors_list[vertex] = gray;
    components[vertex] = component;
    for (auto i : inverted_adj_list[vertex]){
        if (colors_list[i] == white)
            dfs_visit_second(inverted_adj_list, colors_list, components, component, i);
    }
}

int kosaraju_alg(vector<vector<int> > &adj_list, vector<vector<int> > &inverted_adj_list, vector<int> &components){
    int comp_count = -1;
    size_t n = adj_list.size();
    vector<int> order;
    vector<colors> colors_list(n, white);
    for (int i = 0; i < n; ++i){
        if (colors_list[i] == white) {
            ++comp_count;
            dfs_visit_first(adj_list, colors_list, order, i);
        }
    }
    colors_list.assign(n, white);
    int component = 0;
    for (int i = 0; i < n; ++i){
        int v = order[n - i - 1];
        if (colors_list[v] == white) {
            ++component;
            dfs_visit_second(inverted_adj_list, colors_list, components, component, v);
        }
    }
    return component;
}

int main() {
    size_t n, m;
    int from, to;
    cin >> n >> m;
    vector<vector<int> > adj_list(n), inverted_adj_list(n);
    for (int i = 0; i < m; ++i){
        cin >> from >> to;
        adj_list[from - 1].push_back(to - 1);
        inverted_adj_list[to - 1].push_back(from - 1);
    }
    vector<int> components(n);
    cout << kosaraju_alg(adj_list, inverted_adj_list, components) << endl;
    for (auto i : components)
        cout << i << ' ';
    return 0;
}