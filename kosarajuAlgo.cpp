#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

void dfs(vector<int>* edges, int start, unordered_set<int> &vis, stack<int> &finishedVertices)
{
    vis.insert(start);
    for (int i = 0; i < edges[start].size(); ++i)
    {
        int adjacentVertex = edges[start][i];
        if(vis.find(adjacentVertex) == vis.end())
        {
            dfs(edges, adjacentVertex, vis, finishedVertices);
        }
    }
    finishedVertices.push(start);
}


void dfs2(vector<int>* edgesT, int start, unordered_set<int>* component, unordered_set<int> &vis)
{
    vis.insert(start);
    for (int i = 0; i < edgesT[start].size(); ++i)
    {
        int adjacentVertex = edgesT[start][i];
        if(vis.find(adjacentVertex) == vis.end())
        {
            dfs2(edgesT, adjacentVertex, component, vis);
        }
    }
}



unordered_set<unordered_set<int>*>* getStronglyConnectedComponents(vector<int> edges[], vector<int> edgesT[], int n)
{
    unordered_set<int> vis;
    stack<int> finishedVertices;
    for(int i=0;i<n;++i)
    {
        if(vis.find(i) == vis.end())
        {
            dfs(edges, i, vis, finishedVertices);
        }
    }
    unordered_set<unordered_set<int>*>* output = new unordered_set<unordered_set<int>*>();
    vis.clear();
    while(!finishedVertices.empty())
    {
        int element = finishedVertices.top();
        finishedVertices.pop();
        if(vis.find(element) == vis.end())
        {
            continue;
        }
        else
        {
            unordered_set<int>* component = new unordered_set<int>();
            dfs2(edgesT, element, component, vis);
            output->insert(component);
        }
    }
    return output;
}




int main()
{
    int n;
    cin >> n;
    vector<int> *edges = new vector<int>[n];
    vector<int> *edgesTranspose = new vector<int>[n];    // for taking transpose of the graph
    int m;      // number of edges
    cin >> m;
    for(int i=0;i<m;++i)
    {
        int j, k;
        cin >> j >> k;
        edges[j-1].push_back(k-1);
        edgesTranspose[k-1].push_back(j-1);
    }
    unordered_set<unordered_set<int>*>* components = getStronglyConnectedComponents(edges, edgesTranspose, n);
    auto it = components->begin();
    while(it != components->end())
    {
        unordered_set<int>* c = *it;
        auto it2 = c->begin();
        while(it2 != c->end())
        {
            cout << *it2 + 1 << " ";
            it2++;
        }
        cout << endl;
        delete c;
        it++;
    }

    
    
    delete components;
    delete []edges;
    delete []edgesTranspose;
}