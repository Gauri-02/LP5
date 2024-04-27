
#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

const int maxN = 1000;
vector<int> graph[maxN];

void bfs(int s)
{
    queue<int> q;
    vector<bool> visited(maxN, false);

    q.push(s);
    visited[s] = true;
    cout << "BFS: " << endl;

    while (q.empty() == false)
    {
        int u = q.front();
        q.pop();
        cout << u << " ";

#pragma omp parallel for
        for (int i = 0; i < graph[u].size(); i++)
        {
            int v = graph[u][i];
            if (visited[v] != true)
            {
                // cout<<v<<endl;
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

void dfs(int s)
{
    stack<int> st;
    vector<bool> visited(maxN, false);
    st.push(s);
    visited[s] = true;
    cout << endl;
    cout << "DFS: " << endl;

    while (!st.empty())
    {
        int u = st.top();
        st.pop();
        cout << u << " ";
#pragma omp parallel for
        for (int i = 0; i < graph[u].size(); i++)
        {
            int v = graph[u][i];
            if (!visited[v])
            {
                visited[v] = true;
                st.push(v);
            }
        }
    }
}

int main()
{
    int n, m, s; // number of vertices, number of edges, source vertex
    cin >> n >> m >> s;

    for (int i = 0; i < m; i++)
    {
        int u, v; // edge from u to v
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << graph[0].size();

    bfs(s);
    dfs(s);

    // print out the level of each vertex

    return 0;
}
