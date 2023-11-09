********************************************************************************** DIJKSTRA'S ALGORITHM *************************************************************************************

Finds the shortest path instead of a minimum spanning tree by adding it cumulatively

.
.    Graph  (assuming pointed)                                                  
.                                                                             S.1        S.2       S.3     S.4      S.5
.            <___[A]__>                       [A]                  =>[A] 0     0          -         -       -        -
.        8  /  2  |     \ 4                  2|                      [B] 8     8                  2+3+2  =>2+3+2     -
.        [B]--7--[C]--1--[D]           [B]   [C]--1--[D]             [C] 2   =>2          -         -       -        -
.        2 \  3 /  \ 9  / 5            2 \   / 3      / 5            [D] 4     4       =>2+1        -       -        -
.            [E]    [F]                   [E]      [F]               [E] -     -         2+3     =>2+3      -        -
.                                                                    [F] -     -         2+9      2+1+5   2+1+5  =>2+1+5


        A   B  C  D  E  F           This way, it shows the shortest path 
    p: NULL A  A  C  C  D               A to F: 5 + d[D] = 5 + 1 + d[C] = 5 + 1 + 2 = 8
    d:  0   7  2  1  3  5

[SAMPLE CODE] ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DSK(G,s){                                   
    for_each(Vertex v:G){                           
        d[v] = +inf;                                //d[v] means the distance of each vertex. set the value of each node to +inf
        p[v] = NULL;                                //p[v] is the predecessor of d[v] and is set to NULL. 
    }
    d[s]=0;                                         //set the first start node to 0 

    PriorityQueue Q;                                // initialize a queue
    Q.buildHeap(G.vertices());                      // build heap queue
    Graph T;                                        // initialize a graph T

    while ( !Q.empty()){                            // while the queue is not empty
        Vertex u=Q.removeMin();                     // vertex m is the smallest vertex of the heap stack 

        T.add(u);                                    // add vertex M to graph T
.                                                    // for_each (elementType variable_to_replace_the_iterable_container_in_the_loop: iterable_container)
        for_each(Vertex v: G.neighbors(m)){                 // for each neighbor of m not in T (predefined function 'neighbor'), which neighbor is shorter than the "current neighbor"
            if ((cost(u,v)+d[u]) < d[v]){                          // if cost of traversing from neighbor to m is less than the current knwon minimum cost to reach v (at first it's +inf)
                d[v] = cost(u,v)+d[u];                           // update the current known distance to the new min distance
                p[v] = m;                                   // set predecessor to vector value m 
            }
        }
    }
    return T;
};

[EDGE CASES (when it fails)] --------------------------------------------------------------------------------------------------------------------------------------------------------------------

Dijsktra works with a unevenly spaced graphs or non-drectional graphs but it DOES NOT WORK with negative weights. 
Does not work with any negative weights because mathemathically, it will go in an infinite loop to keep decreasing the path. 


[RUN TIME] --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

the BEST runningtime than any short path algorithm 

O(m+nlog(n))


[Landmark Path Problem] --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1. What is the shortest path to get from A to G? What algorithm is best for finding this? 
  - Shortest path takes 2 paths, total weight of 6
  - Since each path are of equal weight, we just need to know shortest number of edges that we need to travel. and the shortest number of edges doesn't mean the shortest path. 
  - This is exactly what the minimum spanning tree gives us. use BFS 

2. What is the shortest path from A to G that visits L? 
        - Can do a BFS from A to L 
        - Then use BFS on L to get from L to G 
  2.a) What is the fastest algorithm to find this path? Whst are the specific calls to this algorithm?  
        - because we have a bi-drectional graph with equal weights, we can start the BFS on L and get the shortest path from L to A and L to G 
        - so actually, still do not need to use a Dijkstra's Algorithms
