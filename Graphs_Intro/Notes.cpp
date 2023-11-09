****************************************************************** VOCABULARY ***************************************************************************

INCIDENT EDGES    - Edges connecting two points                                         
VERTICES/NODE     - used interchangeably
GRAPH (G)         - big graph (G) is a collection of VERTICES (V) and EDGES (E) 
DEGREE            - number of incident edges a node has
ADJACENT VERTICES - the nodes attached to the ends of the incident edges of a node       [w] ---d-- [z]  w and z are adjacent vertices for edge d
PATH              - sequence of vertices
CYCLE             - a path that starts and ends at the same node
SIMPLE GRAPH      - graph with no self loop, and one edge between each node

[PRACTICE]
.    Running times are often reported by n, the number of vertices, but often depend on m, the number of edges 
.                                                               
.       [v]                 Min Not Connected Edges:     0      0
.      /   \                Min Connected Edges:         5      n-1
.    [u]---[x]--[z] 
.      \   / |              Max Simple Edges:            8      n(n-1)/2    => number pattern n=1  n=2  n=3   n=4   => ~O(n^2)
.       [w]  |              Max Not Simple Edges:       +inf   +inf                             0    1    3     6 
.          \ |
.           [y]
 

********************************************************************** GRAPH ADT ************************************************************************

FUNCTION: 
.  - insertVertex ( K key);                        // insert vertex given some key ( K key)        
.  - insertEdge ( Vertex v1, Vertext v2, K key);   // insert an edge between two verticies and assign some data (K key) associated with the edge
.
.  - removeVertex (Vertex v);
.  - removeEdge(Vertex v1, Vertex v2);              // remove the edge between two vertexes
.
.  - incidentEdges(Vertex v);                       // find the number of incident edges with a vertex
.  - areAdjacent(Vertex v1, Vertex v2);             // are two two vertices adjacent
.
.  - origin(Edge e);                                //if edge is directional, what is the origin and destination it is pointing to
.  - destination(Edge e);
                                  
[EDGE LIST IMPLEMENTATION]
.                                   
.          [u]      [K]
.       a /   \ c
.       [v]---[w]---[z]
.           b     d 
.
.      Vertex  Edge List
.       [u]    [u][v][a]            [ANALYSIS of EDGE LIST IMPLEMENTATION RUNTIME]                               
.       [v]    [v][w][b]               - insertVertex(K key);                  O(1) via hash table
.       [w]    [u][w][c]               - removeVertex(Vertex v);               O(m) via hash table
.       [z]    [w][z][d]               - areAdjacent(Vertex v1, Vertex v2);    O(m) need to look at every single element and ask, are they adjacent? 
.       [K]    [u][v][a]               - incidentEdges(Vertex v);              O(m) need to check through each edge to see if they are incidences of vertex v

[ADJACENCY MATRIX IMPLEMENTATION]
.                                   [ANALYSIS of MATRIX  IMPLEMENTATION RUNTIME]        
.          [u]      [K]                * insertVertex(K key);                  O(n) every time a new vertex is added, need to create an entire row and column in the matrix table
.       a /   \ c    | e               * removeVertex(Vertex v);               O(n) every time a new vertex is removed, need to remove an entire row and column in the matrix table
.       [v]---[w]---[z]                * areAdjacent(Vertex v1, Vertex v2);    O(1) do a simple search (like an array) into the matrix table 
.           b     d                    - incidentEdges(Vertex v);              O(m) need to scan through the row and column to see how many overlap there are (ex: in Caps)
.
.      Vertex  Edge List            Adjacent Matrix      
.       [u]    [u][v][a]               [u][v][w][z][K]      [u][v][w][z][K]    // There are clear trade offs in the run time. Matrix improves the adjacent search at the loss of             
.       [v]    [v][w][b]            [u] 0  1  1  0  0    [u] 0  A  c  0  0     // longer insert/remove times
.       [w]    [u][w][c]            [v]    0  1  0  0    [v]    0  B  0  0
.       [z]    [w][z][d]            [w]       0  1  0    [w]       0  d  0
.       [K]    [u][v][a]            [z]          1  1    [z]          0  e
.                                   [K]             0    [K]             0
.                                   matrix table with     matrix with pointer
.                                   true/false if an      to the edge
.                                   edge exists

[ADJACENCY LIST IMPLEMENTATION]

.                                   [ANALYSIS of MATRIX  IMPLEMENTATION RUNTIME]        
.          [u]      [K]                - insertVertex(K key);                  O(1)                            simply add on to the linked list
.       a /   \ c    | e               - removeVertex(Vertex v);               O(degree(v))                    need to remove the adjacent nodes as well 
.       [v]---[w]---[z]                - areAdjacent(Vertex v1, Vertex v2);    O(min(degree(v1),degree(v2)))   need to go through every edge of the two vertex to see if it is adjacent between the two
.           b     d                    - incidentEdges(Vertex v);              O(degree(v))                    degree of v since it is a linked list, do not need to count through everything
.
.       Vertex linked list                 Edge List   
.       [u] => [*a] => [*c]               [*u][ v][ a]  //*u points to *a in [u]                        
.       [v] => [ a] => [ b]               [ v][*w][ b]                            //*w points to *b in [w]            
.       [w] => [*b] => [*c] => [*d]       [*u][*w][ c]  //*u points to *c in [u]  //*w points to *c in [w]                  
.       [z] => [ d] => [ e]               [*w][ z][ d]                            //*w points to *d in [w]             
.       [K] => [ e]                       [ u][ v][ a]
.
.        //essentially creates a giant pointer loop between the vertex linked list and edge list table

[RUNTIME SUMMARY TABLE]                               
.                                        EDGE LIST    ADJ_MATRIX      ADJ_LIST
.           Amount of Space Required;     n+m             n^2           n+m             // n for edge list, m for implementation list (vertext list)
.                insertVertex(K key);      1               n             1
.             removeVertex(Vertex v);      m               n            deg(v)          // if not a hash list, then edge list would require a linear path 
.         insertEdge( v1, v2, K key);      1               1             1
.               removeEdge ( v1, v2);      1               1             1
.  areAdjacent(Vertex v1, Vertex v2);      m               1            min(deg(v1), deg(v2))
.            incidentEdges(Vertex v);      m               n            deg(v)

        //each have respective trade-offs, so choose the table based on what you're trying to run
