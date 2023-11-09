************************************************************************* MINIMUM SPANNING TREES (MST) *************************************************************************

Using edge weights (the cost/distance to traverse/use an edge ), find the shortest path between two vertices

Input: connected, undirected graph G with edge weights.                              
Output: A graph G` with property of 
.    - is a spanning graph of G 
.    - is a tree 
.    - has a minimal total weight among all spanning trees.
.
.            ____[A]___                      [A]
.        8  /  2  |     \ 4                  2|
.        [B]--7--[C]--1--[D]           [B]   [C]--1--[D]
.        2 \  3 /  \ 9  / 5            2 \   /        / 5
.            [E]    [F]                   [E]      [F]

    
****************************************************************************** KRUSKAL'S ALGORITHM *****************************************************************************
.
.          Graph                                                     minHeap structure (in order of weights)
.            ____[A]___                      [A]                       [C,D]  1       C=>D  
.        8  /  2  |     \ 4                  2|                        [A,C]  2       A=>C=>D
.        [B]--7--[C]--1--[D]           [B]   [C]--1--[D]               [B,E]  2       A=>C=>D  B=>E
.        2 \  3 /  \ 9  / 5            2 \   /        / 5              [E,C]  3       A=>C=>D  B=>E=>C          //two connected groups are joined by C
.            [E]    [F]                   [E]      [F]                 [A,D]  4       X
.                                                                      [D,F]  5       A=>C=>D=>F  B=>E=>C
.                                                                      [A,B]  8       X
.                                                                      [C,F]  9       X                                                           
.
.
. Kruskal algorithm creates a table that lists the edge weights in increasing order and we are looking to create a disjoint set. Each edge are then evaluated to determine
. if the relationship of the two vectors is already in the set. If not, then union, if it is, then skip to the next edge. 
.

[SAMPLE CODE] --------------------------------------------------------------------------------------------------------------------------------------------------------------------

KruskalMST(G){
    DisjointSets forest;                                            // forest is initialized as an empty disjoint set data structure
    for_each ( Vertex v:G){                                         // each vertest is added to disjoint set 'forest', makeSet creates a disjoint set for each vertex
        forest.makeSet(v);
    }

    PriorityQueue Q;                                                // a queue is initialized 
    for_each (Edge e:G){            
        Q.insert(e);                                                // all the edges are inserted into the queue
    }

    Graph T = (V, {});                                              // new graph "T" is initialized with the same vertices but no edges connecting them (isolated vertices)

    while ( |T.edges()| < (n-1)){                                   // n = vertices, m = edges...there is always, at most, n-1 number of edges
        Vertex( u,v) = q.removeMin();                               // remove the smallest edge from te queue (where u,v represents the vertex)
        if (forest.find(u)!=forest.find(v)){                        // if the two vertex does not have the same root (aka not in the same disjoint set)
            T.addEdge(u,v);                                         // then add the edge to MST T
            forest.union(forest.find(u), forest.find(v));           // the connected component are containing v and u are merged together. By merging them, it updates them to share the same leader
        }                                                                       
    }                                                                            
    return T;                                                                   
}   

More Details: 

Disjoint Data Structure supports three main functions: 
1. makeSet(v)
2. find(v) 
3. union (v,w)

1. makeSet(v)
   - creates a a new disjoint data set containing a single element v 
   - this operation is called for each element of a set to create individual sets with one element in each set 
     ex) vertex is 1,2,3
         makeSet will create set 1, set 2, set 3 that can be used to union however we want


[RUNTIME ANALYSIS] ----------------------------------------------------------------------------------------------------------------------------------------------------------------

HEAP: 
- Building PriorityQueue:   O(m)  
- Each removeMin:          log(m)

Sorted Array 
- Building PriorityQueue:   O(mlog(m))  
- Each removeMin:            O(1)

********************************************************************************** PRIM'S ALGORITHM **********************************************************************************

PARTITION METHOD: 
- set each node weight to +inf except for the node we are starting at (set to 0)
- create queue of minHeap that lists the node weights in increasing order
- choose the smallest distance to traverse each time. Add onto the available distance to choose from the currently traversed nodes
.
.          Graph                                                     minHeap structure (in order of node weights)
.                                                                                S.1    S.2   S.3  S.4  S.5
.           ____[A]___                       [A]                     [A] 0        0      -     -    -    -
.        8  /  2  |     \ 4                  2|                      [B] +inf     8      7     7    7  =>7
.        [B]--7--[C]--1--[D]           [B]   [C]--1--[D]             [C] +inf   =>2      -     -    -    -
.        2 \  3 /  \ 9  / 5            2 \   / 3      / 5            [D] +inf     4    =>1     -    -    -
.            [E]    [F]                   [E]      [F]               [E] +inf    +inf    3   =>3    -    -
.                                                                    [F] +inf    +inf    9     5  =>5    -

[SAMPLE CODE] --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PrimMST(G,s){                                   
    for_each(Vertex v:G){                           
        d[v] = +inf;                                //d[v] means the distance of each vertex. set the value of each node to +inf
        p[v] = NULL;                                //p[v] is the predecessor of d[v] and is set to NULL. 
    }
    d[s]=0;                                         //set the first start node to 0 

    PriorityQueue Q;                                // initialize a queue
    Q.buildHeap(G.vertices());                      // build heap queue
    Graph T;                                        // initialize a graph T

    while ( !Q.empty()){                            // while the queue is not empty
        Vertex m=Q.removeMin();                     // vertex m is the smallest vertex of the heap stack 
        if (p[m]!=NULL){                            // this if function is only if you want to dynamically grow your graph. check if m has a predecessor (nul lmeans no predecessor)
            T.addVertex(m);                                 // add a vertex (note the addVertex is a defined function)
            T.addEdge(m,p[m],d[m]);                         // m = current vertex, p = predecessor, d = distance assigned (note that addEdge is a defined function)
        }   

        T.add(m);                                    // add vertex M to graph T
.                                                    // for_each (elementType variable_to_replace_the_iterable_container_in_the_loop: iterable_container)
        for_each(Vertex v: G.neighbors(m)){                 // for each neighbor of m not in T (predefined function 'neighbor'), which neighbor is shorter than the "current neighbor"
            if (cost(v,m) < d[v]){                          // if cost of traversing from neighbor to m is less than the current knwon minimum cost to reach v (at first it's +inf)
                d[v] = cost(v,m);                           // update the current known distance to the new min distance
                p[v] = m;                                   // set predecessor to vector value m 
                Q.decreaseKey(v,d[v]);                      // decrease key ensures that the proirity queue is ordered properly, helps the algorithm run more efficiently
            }
        }
    }
    return T;
};

[RUNTIME ANALYSIS] --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Sparse Graph (number of edges is less than the max number of edges possible)
m ~ n  => mlog(m) + mlog(m)  => mlog(m)

Dense Graph (graph contains max number of edges)
m ~ n^2  => n^2

.                          Adj Matrix                      Adj List

HEAP                      n^2 + mlog(n)                nlog(n) + mlog(n)

Unsorted Array                 n^2                            n^2
