#include <bits/stdc++.h>
#include <chrono>
using namespace std;

void approxVertexCover(vector<pair<int, int>> &edges, int n, int e)
{
    unordered_set<int> S;
    while (edges.size() != 0)
    {
        int u = edges[edges.size() - 1].first, v = edges[edges.size() - 1].second;
        S.insert(u);
        S.insert(v);
        for (int i = 0; i < edges.size(); i++)
        {
            if (S.count(edges[i].first) or S.count(edges[i].second))
                edges.erase(edges.begin() + i);
        }
    }
    for (auto it : S)
    {
        cout << it << "--";
    }
    cout << endl;
}

int main()
{
    int n, e;
    cout << "Enter no. of vertices in graph:";
    cin >> n;
    vector<int> adj[n];
    vector<pair<int, int>> edges;
    cout << "Enter the no. of edges in graph:";
    cin >> e;
    cout << "Enter edges:" << endl;
    int u, v;
    while (e--)
    {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
    }
    using namespace std::chrono;
    time_point<system_clock> begin, end;
    begin = system_clock::now();
    approxVertexCover(edges, n, e);
    end = system_clock::now();
    duration<double> duration = end - begin;
    cout << "\nTime taken is:" << duration.count() << "sec" << endl;
    return 0;
}