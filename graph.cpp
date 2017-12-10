#include "graph.h"

Graph::Graph() {

}

Graph::Graph(vector<QString> vNames):discoveryEdge(0),backEdge(0)
{
    for(unsigned int i = 0; i<vNames.size(); i++)
    {
        vNode vertex;
        vertex.key = i;
        vertex.nodeName = vNames[i];
        vertex.distance = 0;
        vertex.visited = false;
        vector<vNode> eachVertexList;
        eachVertexList.push_back(vertex);
        adjacencyList.push_back(eachVertexList);
    }
}

// this function will add new vertexes (and consequently edges) to the graph
void Graph::addAdjacentNoDirect(int indexV1, int indexV2, double dist) //O(n)
{
    lesserComparator obj;
    bool has = false;
    /*
    //To Avoid Duplications Due to duplicatedclient code
    for(unsigned int i =0; i<adjacencyList[indexV1].size(); i++)
    {
        if(adjacencyList[indexV1][i].nodeName == verticesNames[indexV2])
            return;
    }*/
    //connecting v1 to v2
    vNode adjacentVertex;
    adjacentVertex.key = indexV2;
    adjacentVertex.nodeName = adjacencyList[indexV2][0].nodeName;
    adjacentVertex.distance = dist;
    adjacentVertex.visited = false;
    for (int i = 0; i < adjacencyList[indexV1].size(); i++)
    {
        if (adjacencyList[indexV1][i] == adjacentVertex)
        {
            has = true;
            break;
        }
    }
    if (!has)
    {
    adjacencyList[indexV1].push_back(adjacentVertex);
    sort(adjacencyList[indexV1].begin()+1, adjacencyList[indexV1].end(), obj);//sorts children of node at indexV2 according to distance
    }
    //since there is no direction, connecting v2 to v1
    //Comment out this part of you add all the edges
    vNode adjacentVertex2;
    adjacentVertex2.key = indexV1;
    adjacentVertex2.nodeName = adjacencyList[indexV1][0].nodeName;
    adjacentVertex2.distance = dist;
    adjacentVertex2.visited = false;
    has = false;
    for (int i = 0; i < adjacencyList[indexV2].size(); i++)
    {
        if (adjacencyList[indexV2][i] == adjacentVertex2)
        {
            has = true;
            break;
        }
    }
    if (!has)
    {
    adjacencyList[indexV2].push_back(adjacentVertex2);
    sort(adjacencyList[indexV2].begin()+1, adjacencyList[indexV2].end(), obj);//sorts children of node at indexV2 according to distance
    }
}

vector<vector<vNode> > Graph::getAdjacencyList()
{
    return adjacencyList;
}
//this function will print the graph
void Graph::printGraph()
{
    qDebug()<<"printing"<<endl;
    for(unsigned int i =0; i<adjacencyList.size(); i++)
    {
        for(unsigned int j = 0; j<adjacencyList[i].size();j++)
        {
            qDebug()<<adjacencyList[i][j].nodeName<<"   ";
        }
        qDebug()<<endl;
    }
}

//this function will implement and output the Depth First Traversal.
//It also populates discoveryEdge vector, and backEdge vector
void Graph::partialDFS(int startingIndex, bool visited[])
{
    if(!adjacencyList[startingIndex][0].visited)
    {
        qDebug()<<adjacencyList[startingIndex][0].nodeName<<"   ";
        visited[startingIndex] = true;
        adjacencyList[startingIndex][0].visited = true;
    }
    bool nextFound = false;

    //since each vector in adjacancyList[i] is sorted (sorted in caller DFS function), just check visited attribute
    for(vector<vNode>::iterator it = adjacencyList[startingIndex].begin(); it != adjacencyList[startingIndex].end(); it++)
    {
        if(!visited[it->key])	//if the node in general is visited skip, if not
        {
            //visited[it->key] = true;
            it->visited = true;

            //after setting b in a---b to visited now set a in b---a to visited
            vector<vNode>::iterator ti = find(adjacencyList[it->key].begin(),adjacencyList[it->key].end(), adjacencyList[startingIndex][0]);
            ti->visited = true; //since undirected graph: when a---b is visited, b---a is also visited

            //making discovery edge
            edge e;
            e.begining = adjacencyList[startingIndex][0].nodeName;
            e.end = it->nodeName;
            e.distance = it->distance;
            discoveryEdge.push_back(e); //adding e to the list of discovery edges
            partialDFS(it->key, visited); //recursive call
            nextFound=true;
            break;
        }

    }
    //if closet unvisited node has been found
    if(!nextFound)
        return;
    //if partialDFS call in if(nextFound) returned, the child had no other unvisited grand-child, so check if there is any other unvisited child for startingIndex vertex
    partialDFS(startingIndex, visited);
}

//DFS Traversal that fills creates discovery and back edge vectors
void Graph::DFS(int startingIndex)
{
    clearEdges(); //remove changes of any previous traversals
    discoveryEdge.clear();
    backEdge.clear();
    int size = adjacencyList.size();
    bool visited[size];
    for (int i = 0; i< size; i ++)
        visited[i] = false;
 /*  Already sorted after ading an edge
  *  //to sort the adjacent vertices by distance(== operator is overloaded for vNode struct
    for(unsigned int i = 0; i<adjacencyList.size(); i++)
    {
        sort(adjacencyList[i].begin()+1, adjacencyList[i].end());//sort children of node i in vList
    }*/
    partialDFS(startingIndex, visited);

    //finding back edges after the traversal is done and adding them to backedge vector
    for(unsigned int i = 0; i<adjacencyList.size(); i++)
    {
        for(unsigned int j = 0; j<adjacencyList[i].size(); j++)
        {
            if(!adjacencyList[i][j].visited)
            {
                edge e;
                e.begining = adjacencyList[i][0].nodeName;
                e.end =adjacencyList[i][j].nodeName;
                if(find(backEdge.begin(), backEdge.end(), e)==backEdge.end())//removes duplication of a---b b---a
                {
                    backEdge.push_back(e);
                }
            }
        }
    }
}

//This function will implement Breadth First Traversal level by level
//It also populates discoveryEdge vector
//vList is current level nodes
void Graph::partialBFS(vector<vNode> vList,  bool visited[])
{
    vector<vNode> newLevel(0);//next level nodesadjacencyList[vList[i].key][j]
    for(unsigned int i = 0; i < vList.size(); i++)
    {
            qDebug()<<vList[i].nodeName<<"  ";
            visited[vList[i].key] = true;
            adjacencyList[vList[i].key][0].visited = true;
    }
    for(unsigned int i = 0; i < vList.size(); i++)
    {
        for(unsigned int j = 1; j<adjacencyList[vList[i].key].size();j++)
        {
            int indexKey = adjacencyList[vList[i].key][j].key;
            if(!visited[indexKey])
            {
                newLevel.push_back(adjacencyList[vList[i].key][j]);
                visited[indexKey] = true;//to avoid duplication of same unvisited children in two separate parent nodes
                adjacencyList[vList[i].key][j].visited = true;//edge is visited

                //after setting b in a---b to visited now set a in b---a to visited
                vector<vNode>::iterator ti = find(adjacencyList[indexKey].begin(),adjacencyList[indexKey].end(), adjacencyList[vList[i].key][0]);
                ti->visited = true; //since undirected graph: when a---b is visited, b---a is also visited

                edge e;
                e.begining = vList[i].nodeName;
                e.end = adjacencyList[vList[i].key][j].nodeName;
                e.distance = adjacencyList[vList[i].key][j].distance;
                discoveryEdge.push_back(e);
            }
        }
    }
    if(newLevel.size()>0)
    {
        partialBFS(newLevel,  visited);
    }
    else
        return;
}

void Graph::BFS(int startingIndex)
{
    clearEdges();
    discoveryEdge.clear();
    crossEdge.clear();

    /* Already sorted: sorts after adding n new edge in addEdge method
    //sort all the lists in the graph except for the beginning node in each
    for(unsigned int i = 0; i<adjacencyList.size(); i++)
    {
        sort(adjacencyList[i].begin()+1, adjacencyList[i].end());//sort children of node i in vList
    }*/

    bool visited[12] = {false};
    vector<vNode> start;
    start.push_back(adjacencyList[startingIndex][0]);
    partialBFS(start,visited);

    //finding back edges after the traversal is done and adding them to backedge vector
    for(unsigned int i = 0; i<adjacencyList.size(); i++)
    {
        for(unsigned int j = 0; j<adjacencyList[i].size(); j++)
        {
            if(!adjacencyList[i][j].visited)
            {
                edge e;
                e.begining = adjacencyList[i][0].nodeName;
                e.end =adjacencyList[i][j].nodeName;
                if(find(crossEdge.begin(), crossEdge.end(), e)==crossEdge.end())//removes duplication of a---b b---a
                {
                    crossEdge.push_back(e);
                }
            }
        }
    }
}

void Graph::printEdgeList(vector<edge> v)
{
    for(unsigned int i = 0; i<v.size(); i++)
    {
        qDebug()<<v[i].begining<<"________"<<v[i].end<<endl;
        //totalDist+= v[i].distance;
    }
}

void Graph::printDFSEdges()
{
    cout<<"DFS Discovery Edges: "<<endl;
    printEdgeList(discoveryEdge);
    cout<<endl<<"DFS Back Edges: "<<endl;
    printEdgeList(backEdge);
}

void Graph::printBFSEdges()
{
    cout<<"BFS Discovery Edges: "<<endl;
    printEdgeList(discoveryEdge);
    cout<<endl<<"BFS Cross Edges: "<<endl;
    printEdgeList(crossEdge);
}

//this function will return the Depth First Traversal total
int Graph::getTotalDiscoveryDistance()
{
    int totalDist = 0;
    for(unsigned int i = 0; i<discoveryEdge.size(); i++)
    {
        totalDist+= discoveryEdge[i].distance;
    }
    return totalDist;
}

//this function removes visited marks in the graph
void Graph::clearEdges()
{
    for(unsigned int i = 0; i<adjacencyList.size(); i++)
    {
        for(unsigned int j = 0; j<adjacencyList[i].size(); j++)
        {
            adjacencyList[i][j].visited = false;
        }
    }
}

vector<vNode> Graph::dijkstra(int sourceIndex)
{

    vector<int> cost(adjacencyList.size(), 1000000);
    vector<int> parent(adjacencyList.size(), -1);

    //priority queue using STL priority_queue
    std::priority_queue<vNode,std::vector<vNode>,lesserComparator> vertexPriorityQueue;
    cost[sourceIndex] = 0;
    vNode temp;
    vertexPriorityQueue.push(adjacencyList[sourceIndex][0]);
    while(!vertexPriorityQueue.empty())
    {
        temp.key = vertexPriorityQueue.top().key;
        temp.nodeName = vertexPriorityQueue.top().nodeName;
        temp.distance = vertexPriorityQueue.top().distance;
        vertexPriorityQueue.pop();
        //i starts at 1 because index 0 is the node itself, from 1 to n are indecis of children of the node
        for(unsigned int i = 1; i<adjacencyList[temp.key].size(); i++)
        {
            //for each child of temp, cost[child] = min(cost[temp]+dist(temp to child), current cost[child])
            if(adjacencyList[temp.key][i].distance + cost[temp.key]< cost[adjacencyList[temp.key][i].key])
            {
                cost[adjacencyList[temp.key][i].key] = adjacencyList[temp.key][i].distance + cost[temp.key];
                parent[adjacencyList[temp.key][i].key] = temp.key;
                vertexPriorityQueue.push(adjacencyList[temp.key][i]);
            }
        }
    }

    vector<vNode> vertices;//all the nodes and their distance from the starting point, exclusing starting point
    for(unsigned int i = 0; i<cost.size(); i++)
    {
        if(cost[i]!=0)//exclude the node itself
        {
            vNode vertex = adjacencyList[i][0];
            vertex.distance = cost[i];
            vertices.push_back(vertex);
        }
    }
    //sort from the closet to furthest
    //operator "<" has been overloaded for vNode struct
    sort(vertices.begin(), vertices.end());
    return vertices;
/*
    for(unsigned int i = 0; i<cost.size(); i++)
    {
        cout<<"vertex: "<<adjacencyList[i][0].nodeName<<", cost: "<<cost[i]<<endl;
    }

    cout<<endl;
    for(unsigned int i = 0 ; i<parent.size(); i++)
    {
        std::stack<int> path;
        int j = parent[i];	//j is parent of i
        path.push(i);
        while(j!=-1)
        {
            path.push(j);
            j = parent[j]; //find parent of current parent
        }
        while (!path.empty())
        {
            cout<<adjacencyList[path.top()][0].nodeName<<"    ";
            path.pop();
        }
        cout<<endl;
    }*/
}

void Graph::mst(int sourceIndex)
{
    vector<int> cost(adjacencyList.size(), 100000);
    vector<int> parent(adjacencyList.size(), -1);
    vector<bool> visited(adjacencyList.size(), false);

    //priority queue using STL priority_queue
    std::priority_queue<vNode,std::vector<vNode>,lesserComparator> vertexPriorityQueue;

    cost[sourceIndex] = 0;
    vNode temp;
    vertexPriorityQueue.push(adjacencyList[sourceIndex][0]);
    //visited[sourceIndex] = true;

    while(!vertexPriorityQueue.empty())
    {
        temp.key = vertexPriorityQueue.top().key;
        temp.nodeName = vertexPriorityQueue.top().nodeName;
        temp.distance = vertexPriorityQueue.top().distance;
        vertexPriorityQueue.pop();
        visited[temp.key] = true;

        //i starts at 1 because index 0 is the node itself, from 1 to n are
        //indeces of children of the node
        for(unsigned int i = 1; i<adjacencyList[temp.key].size(); i++)
        {
            //for each child of temp, cost[child] = min(cost[temp]+dist
            //(temp to child), current cost[child])
            if(adjacencyList[temp.key][i].distance<cost[adjacencyList[temp.key][i].key]
               && !visited[adjacencyList[temp.key][i].key])
            {
                cost[adjacencyList[temp.key][i].key] = adjacencyList[temp.key][i].distance;
                parent[adjacencyList[temp.key][i].key] = temp.key;
                vertexPriorityQueue.push(adjacencyList[temp.key][i]);
                //visited[adjacencyList[temp.key][i].key] = true;

            }
        }
    }

    int total = 0;

    cout << "\n\nMST Edges:\n";
    for(unsigned int i = 0; i < cost.size(); i++)
    {
        total += cost[i];

        if(parent[i] != -1)
        {
            qDebug() << "Edge: " << adjacencyList[i][0].nodeName << "----"
                 << adjacencyList[parent[i]][0].nodeName << endl;

        }
    }

    cout << "\nTotal Mileage: " << total;

}

void Graph::findEfficientPath(vector<vNode>& selectedStadiums, vNode startingPoint, vector<vNode>& visited)
{
    qDebug()<<"********"<<startingPoint.nodeName<<"***********";
    visited.push_back(startingPoint);//distance of starting point is based on previous parent

    //find closest unvisited node and make it a starting opint of next recursive call
    //destination is ordered from closest to furthest
    if(selectedStadiums.size()>visited.size())
    {
        //dijkstra method returns All stadiums in graph sorted based on their sidtance to startnigPoint
        vector<vNode> destinations = dijkstra(startingPoint.key);
        for(unsigned int i = 0; i<destinations.size() ; i++)
        {

            //if destinations[i] is selected and is not visited, startingPoint = destination[i]
            //operator "==" has been overloaded for vNode struct
            if( find(visited.begin(), visited.end(), destinations[i])==visited.end()
                &&
                find(selectedStadiums.begin(), selectedStadiums.end(), destinations[i])!=selectedStadiums.end())
            {
                startingPoint = destinations[i];
                break;
            }
        }
        //next recursive call
        findEfficientPath(selectedStadiums, startingPoint, visited);
    }
    //else: all the stadiums are visited
    else
        return;
}

void Graph::orderSpecifiedPath(vector<vNode>& selectedStadiums, vNode startingPoint, vector<vNode>& visited)
{
    int index; //index of next stadium in the order in selected stadiums
    visited.push_back(startingPoint);//distance filesd of starting point is based on previous parent
    for(unsigned int j = 0 ; j<selectedStadiums.size(); j++)
    {
        if(startingPoint==selectedStadiums[j])
        {
            index = j+1;
        }
    }

    //find closest unvisited node and make it a starting opint of next recursive call
    //destination is ordered from closest to furthest
    if(selectedStadiums.size()>visited.size())
    {
        //dijkstra method returns stadiums and their distance from starting point
        vector<vNode> destinations = dijkstra(startingPoint.key);

        for(unsigned int i = 0; i<destinations.size() ; i++)
        {
            //if destinations[i] is selected and is not visited, startingPoint = destination[i]
            //operator "==" has been overloaded for vNode struct
            if( find(visited.begin(), visited.end(), destinations[i])==visited.end()
                &&
                selectedStadiums[index]==destinations[i])
            {
                startingPoint = destinations[i];
                break;
            }
        }
        //next recursive call
       orderSpecifiedPath(selectedStadiums, startingPoint, visited);
    }
    //else: all the stadiums are visited
    else
        return;
}
