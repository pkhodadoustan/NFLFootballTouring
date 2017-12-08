#ifndef GRAPH_H
#define GRAPH_H
#include<iostream>
#include<list>
#include<vector>
#include<iterator>
#include<algorithm>
#include<queue>
#include<stack>
using namespace std;


struct vNode
{
    int key;
    string nodeName;
    double distance;
    bool visited;
    bool operator < (vNode other)
    {
        if(distance<other.distance)
            return true;
        else
            return false;
    }
    bool operator == (vNode other)
    {
        if(nodeName==other.nodeName)
            return true;
        else
            return false;
    }
};

struct edge
{
    string begining;
    string end;
    int distance;
    bool operator == (edge other)
    {
        if((begining==other.begining || begining==other.end) && (end==other.begining || end==other.end))
            return true;
        else
            return false;
    }
};

class lesserComparator
{
public :
    bool operator () (vNode& vertex1, vNode& vertex2)
    {
        return(vertex2<vertex1);

    }
};

class Graph
{
public:
    Graph( vector<string> vName);
    void addAdjacentNoDirect(int indexV1, int indexV2, double dist);
    void printGraph();
    void DFS(int startingIndex);
    void BFS(int startingIndex);
    void printDiscoveryEdges();
    void printDFSEdges();
    void printBFSEdges();
    int getTotalDiscoveryDistance();
    void dijkstra(int sourceIndex);
    void mst(int sourceIndex);

private:
    vector<vector<vNode> > adjacencyList; //vector of linkedLists of node type vertex
    vector<edge> discoveryEdge;//based on last type traversals stores discovery edges
    vector<edge> backEdge;//based on last type traversals stores back edges
    vector<edge> crossEdge;//based on last type traversals stores cross edges
    void clearEdges();
    void partialDFS(int startingIndex, bool visited[]);
    void partialBFS(vector<vNode> vList, bool visited[]);
    void printEdgeList(vector<edge> v);
};

#endif // GRAPH_H