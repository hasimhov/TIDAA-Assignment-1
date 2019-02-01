#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> parent,dist;
vector<list<int> > adjList;

void DFS(int root)
{
    for(int a:adjList[root])
    {
        if(a == parent[root])
            continue;
        parent[a] = root;
        dist[a] = dist[root] + 1;
        DFS(a);
    }
}

int findOneEndOfDiameter()
{
    parent[0] = -1;
    dist[0] = 0;
    DFS(0);
    int max=0,node=0;
    for(int i=1;i<n;i++)
    {
        if(dist[i] > max)
        {
            max = dist[i];
            node = i;
        }
    }
    return node;
} 

vector<int> findDiameter()
{
    int u = findOneEndOfDiameter();
    dist[u] = 0;
    parent[u] = -1;
    DFS(u);
    int max=0,v=u;
    for(int i=0;i<n;i++)
    {
        if(dist[i] > max)
        {
            max = dist[i];
            v = i;
        }
    }
    vector<int> path(max+1);
    int i=0;
    while(v != -1)
    {
        path[i++] = v;
        v = parent[v];
    }
    return path;
}

int main()
{
    cin>>n;     
    parent.resize(n);
    dist.resize(n);
    adjList.resize(n);
    int m=n-1;
    int u,v;
    for(int i=0;i<m;i++)
    {
        cin>>u>>v;      //Enter a pair of vertices(which form the edge) in each line
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    vector<int> path = findDiameter();
    for(int a:path)
        cout<<a<<" ";
    cout<<endl;
    return 0;
}