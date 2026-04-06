#include <bits/stdc++.h>
using namespace std;

/*
使用dfs进行拓扑排序，使用state数组来标记节点的状态：三色标记来判断是否有环
通过reverse函数将后序加入的节点顺序反转得到正确的拓扑排序结果
*/

vector<vector<int>> graph;
vector<int> state; // 0: unvisited, 1: visiting, 2: visited
vector<int> result;
bool has_cycle = false;

void dfs(int u)
{
    state[u] = 1; // visiting
    for (int v : graph[u])
    {
        if (state[v] == 0)
        { // unvisited
            dfs(v);
            if (has_cycle)
                return;
        }
        else if (state[v] == 1)
        { // visiting
            has_cycle = true;
            return;
        }
    }
    state[u] = 2;        // visited
    result.push_back(u); // 后序加入
}

signed main()
{
    int n, m;
    cin >> n >> m;
    graph.resize(n);
    state.resize(n, 0);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    for (int i = 0; i < n; i++)
    {
        if (state[i] == 0)
        {
            dfs(i);
            if (has_cycle)
                break;
        }
    }
    if (has_cycle)
    {
        cout << "图中有环，无法进行拓扑排序" << endl;
    }
    else
    {
        reverse(result.begin(), result.end());
        cout << "拓扑排序的结果是: ";
        for (int u : result)
        {
            cout << u << " ";
        }
        cout << endl;
    }

    return 0;
}