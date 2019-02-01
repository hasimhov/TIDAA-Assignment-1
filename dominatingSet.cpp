#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> parent,dist,degree;
unordered_map<int,unordered_set<int> > adjList;

vector<int> dominatingSet()
{
    vector<int> leaves,dom;
    vector<bool> dominated(n,false);
    for(int i=0;i<n;i++)
        if(degree[i] == 1)
            leaves.push_back(i);
        else if(degree[i] == 0)
        {
            dom.push_back(i);
            dominated[i] = true;
            adjList.erase(i);
        }
    for(int i=0;i<leaves.size();i++)
    {
        if(degree[leaves[i]] != 1)
            continue;
        int par = *(adjList[leaves[i]].begin());
        if(dominated[leaves[i]])
        {
            degree[par]--;
            if(degree[par] == 0 && !dominated[par])
            {
                dom.push_back(par);
                dominated[par] = true;
                adjList.erase(par);
            }

        }
        else
        {
            dom.push_back(par);
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
    }
    return dom;
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
    vector<int> path = dominatingSet();
    for(int a:path)
        cout<<a<<" ";
    cout<<endl;
    return 0;
}
