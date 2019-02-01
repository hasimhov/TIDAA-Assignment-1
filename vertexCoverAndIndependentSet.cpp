#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> parent,dist,degree;
unordered_map<int,unordered_set<int> > adjList;

vector<int> vertexCover()
{
    vector<int> leaves;
    for(int i=0;i<n;i++)
        if(degree[i] == 1)
            leaves.push_back(i);
    vector<int> cover;
    for(int i=0;i<leaves.size();i++)
    {
        if(degree[leaves[i]] != 1)
            continue;
        int par = *(adjList[leaves[i]].begin());
        cover.push_back(par);
        adjList[par].erase(leaves[i]);
        for(int a:adjList[par])
        {
            degree[a]--;
            if(degree[a] == 1)
                leaves.push_back(a);
            adjList[a].erase(par);
        }
        adjList.erase(leaves[i]);
        degree[par] = 0;
        adjList.erase(par);
    }
    return cover;
}

vector<int> independentSet(vector<int>& cover)
{
    unordered_set<int> s(cover.begin(),cover.end());
    vector<int> set;
    for(int i=0;i<n;i++)
        if(s.find(i) == s.end())
            set.push_back(i);
    return set;
}

int main()
{
    cin>>n;     
    parent.resize(n);
    dist.resize(n);
    degree.resize(n,0);
    int m=n-1;
    int u,v;
    for(int i=0;i<m;i++)
    {
        cin>>u>>v;      //Enter a pair of vertices(which form the edge) in each line
        adjList[u].insert(v);
        adjList[v].insert(u);
        degree[u]++;
        degree[v]++;
    }
    vector<int> path = vertexCover();
    cout<<"Vertex Cover"<<endl;
    for(int a:path)
        cout<<a<<" ";
    cout<<endl;
    path = independentSet(path);
    cout<<"Independent Set"<<endl;
    for(int a:path)
        cout<<a<<" ";
    cout<<endl;
    return 0;
}
