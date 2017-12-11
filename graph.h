#ifndef GRAPH_H
#define GRAPH_H
#include<iostream>
#include<list>
#include<vector>
#include<iterator>
#include<algorithm>
#include <string>
#include<queue>
#include<stack>
#include<QString>
#include<QDebug>
using namespace std;
/**
 * @brief The vNode struct
 * the vertex for gtaph
 */

struct vNode
{
    int key;    //key
    QString nodeName;
    double distance;
    bool visited;
    bool operator < (vNode other)
    {
        if(this->distance<other.distance)
            return true;
        else
            return false;
    }
    bool operator > (vNode other)
    {
        if(this->distance<other.distance)
            return false;
        else
            return true;
    }
    bool operator == (vNode other)
    {
        if(nodeName==other.nodeName)
            return true;
        else
            return false;
    }
};

/**
 * @brief The edge struct
 * edge for grpah
 */
struct edge
{
    QString begining;
    QString end;
    int distance;
    bool operator == (edge other)
    {
        if((begining==other.begining || begining==other.end) && (end==other.begining || end==other.end))
            return true;
        else
            return false;
    }
};

/**
 * @brief The lesserComparator class
 * allows for vNode comparison
 */
class lesserComparator
{
public :
    bool operator () ( vNode& vertex1,  vNode& vertex2)
    {
        return(vertex2<vertex1);

    }
};

class greaterComp
{
public :
    bool operator () ( vNode& vertex1,  vNode& vertex2)
    {
        return(vertex2>vertex1);

    }
};

/**
 * @brief The Graph class
 * creates graphfor stadiums
 */
class Graph
{
public:
    /**
     * @brief Graph
     * @param vName
     * creates graph from qstrings
     */
    Graph( vector<QString> vName);
    /**
     * @brief Graph
     * default constructor
     */
    Graph();

    /**
     * @brief addAdjacentNoDirect
     * @param indexV1
     * @param indexV2
     * @param dist
     * adds to adjacency list
     */
    void addAdjacentNoDirect(int indexV1, int indexV2, double dist);

    /**
     * @brief getAdjacencyList
     * @return
     * returrns adjaccency list
     */
    vector<vector<vNode> > getAdjacencyList();

    /**
     * @brief printGraph
     * prints the graph
     */
    void printGraph();

    /**
     * @brief DFS
     * @param startingIndex
     * preforms DFS from starting points
     */
    void DFS(int startingIndex);

    /**
     * @brief BFS
     * @param startingIndex
     * preforms BFS from starting points
     */
    void BFS(int startingIndex);

    /**
     * @brief printDiscoveryEdges
     * pritns discvery edges
     */
    void printDiscoveryEdges();

    /**
     * @brief printDFSEdges
     * print DFS edges
     */
    void printDFSEdges();

    /**
     * @brief printBFSEdges
     * print BFS edges
     */
    void printBFSEdges();

    /**
     * @brief getTotalDiscoveryDistance
     * @return
     * returns tital discovery edges
     */
    int getTotalDiscoveryDistance();

    /**
     * @brief getDiscoveryEdges
     * @return
     * returns a;; discoery edges
     */
    vector<edge> getDiscoveryEdges();

    /**
     * @brief dijkstra
     * @param sourceIndex
     * @return
     *
     * return dijkstras path
     */
    vector<vNode> dijkstra(int sourceIndex);

    /**
     * @brief mst
     * @param sourceIndex
     * @return
     * returns an MST
     */
    vector<edge> mst(int sourceIndex);

    /**
     * @brief findEfficientPath
     * @param selectedStadiums
     * @param startingPoint
     * @param visited
     * finds most efficient path
     */
    void findEfficientPath(vector<vNode>& selectedStadiums, vNode startingPoint, vector<vNode>& visited);
    /**
     * @brief orderSpecifiedPath
     * @param selectedStadiums
     * @param startingPoint
     * @param visited
     * order specific path
     */
    void orderSpecifiedPath(vector<vNode>& selectedStadiums, vNode startingPoint, vector<vNode>& visited);

private:
    /**
     * @brief adjacencyList
     * vector of linkedLists of node type vertex
     */
    vector<vector<vNode> > adjacencyList; //vector of linkedLists of node type vertex
    /**
     * @brief discoveryEdge
     * based on last type traversals stores discovery edges
     */
    vector<edge> discoveryEdge;//based on last type traversals stores discovery edges

    /**
     * @brief backEdge
     * based on last type traversals stores back edges
     */
    vector<edge> backEdge;//based on last type traversals stores back edges
    /**
     * @brief crossEdge
     * based on last type traversals stores cross edges
     */
    vector<edge> crossEdge;//based on last type traversals stores cross edges

    /**
     * @brief clearEdges
     * clears all edges of the graph
     */
    void clearEdges();

    /**
     * @brief partialDFS
     * @param startingIndex
     * @param visited
     * used to create a ful; DFS
     */
    void partialDFS(int startingIndex, bool visited[]);

    /**
     * @brief partialBFS
     * @param vList
     * @param visited
     * used to created a full DFS
     */
    void partialBFS(vector<vNode> vList, bool visited[]);

    /**
     * @brief printEdgeList
     * @param v
     * prints edge list
     */
    void printEdgeList(vector<edge> v);
};

#endif // GRAPH_H
