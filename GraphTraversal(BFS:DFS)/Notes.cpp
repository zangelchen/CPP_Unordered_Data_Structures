 ************************************************************************ Breadth-First Search (BFS)Traversal ************************************************************************

 Traversal 
  - OBJECTIVE is to visit every vertex and every edge in the graph

  DIFFICULTY
  -  no obvious start
  -  no particular order
  -  no notion of completeness 

[EXAMPLE]
.                                                     
.      [A]                   [A] B C D     //STEP 1: Visited
.    /  /  \                 [B] A C E     //STEP 2: Visited
. [B]--[C]--[D]              [C] A D E F
.   \  / \  /                [D] A C F
.   [E]--[F]                 [E] B C F
.                            [F] E C D
       
Query           Output  
A                A                                 // STEP 1: Add A to the queue, remove A from the queue, THEN mark A as visited        
B C D            A                                 // STEP 1: Line up the incident edges of list [A] 
C D              A B                               // STEP 2: Look at the next node in the queue being visited, dequeue [B], mark [B] as visited
C D E            A B                               // STEP 2: Enqueue incident edges of [B] that is not already in the queue
D E              A B C                             // keep repeating this process until all the nodes are dequeue 
D E F            A B C 
E F              A B C D 
F                A B C D E 
_                A B C D E F

[SAMPLE CODE] ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PURPOSE:     
.    Input: Graph, G
.    Output: A labeling of the edges on G as discover and cross edges     //discovery means the path through every node. cross edges are the edges that are there but we did not traverse
.
.
.    BFS(G){
.        
.        std::for_each ( Vertex v: G.vertices())      //initially mark every vertex as unexplored
.            {
.                setLable(v, UNEXPLORED);
.            }
.        std::for_each ( Edge e: G.edges())           //initially mark every edge as unexplored
.            {
.                setLable(e, UNEXPLORED);
.            }       
.        std::for_each ( Vertex v: G.vertices())      // if the vertex is unexplored, then go down to the BFS(G,v) function
.            {
.                if (getLabel(v)== UNEXPLORED){
.                    BFS(G,v);
.                }
.            }
.    }       
.    BFS(G,v){                                        // explore the graph starting at vertex v
.        Queue q                                      // create a Queue called q
.        setLabel( v, VISITED)                        // mark vertex v as VISITED
.        q.enqueue(v)                                 // put vertex v into q (queue)
.
.        while (!q.empty())                           // while q is not empty
.        {                           
.            v = q.dequeue();                              // remove v from the queue
.            std::for_each (Vertex w: G.adjacent(v))  // look at each adjacent vertex to v (set as vertex w)
.                {
.                    if (getLable(w) == UNEXPLORED)   // if vertex w is unexplored
.                    {      
.                        setLabel( v, w, DISCOVERY);      // the edge of (v,w) is marked as DISCOVERY
.                        setLable( w, VISITED);           // w is marked as visited
.                        q.enqueue(w);                    // w is placed into the queue
.                    } elseif {
.                        getLable(v,w)==UNEXPLORED;   // if vertex w is NOT labeled unexplored but the edge (v,w) is unexplored
.                        setLable(v,w,CROSS);             // then lable that edge as CROSS
.                    }
.            }
.        }                                            // the while loop then does this over again with vertex w and it's adjacent nodes
.    }

**************************************************************************** DEPTH-FIRST SEARCH TRAVERSAL ********************************************************************************

Uses a stack structure but do not need to focus on the structure 

[EXAMPLE]
.                        // imagine the below as a linear path, where => is discovery path and ~~> is "back" aka "cross", where you're taking one step "back"                    
.      [A]                   [A] => [B] => [E] => [F] => [D] ~~> [A]
.    /  /  \                 [D] => [C] ~~> [A] 
. [B]--[C]--[D]              [C] ~~> [B]
.   \  / \  /                [C] ~~> [E]
.   [E]--[F]                 [C] ~~> [F]
.

[SAMPLE CODE] ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PURPOSE:     
.    Input: Graph, G
.    Output: A labeling of the edges on G as discover and back edges     //discovery means the path through every node. back edges are the edges that are there but we did not traverse
.
.    DFS(G){
.        
.        std::for_each ( Vertex v: G.vertices())      //initially mark every vertex as unexplored
.            {
.                setLable(v, UNEXPLORED);
.            }
.        std::for_each ( Edge e: G.edges())           //initially mark every edge as unexplored
.            {
.                setLable(e, UNEXPLORED);
.            }       
.        std::for_each ( Vertex v: G.vertices())      // if the vertex is unexplored, then go down to the BFS(G,v) function
.            {
.                if (getLabel(v)== UNEXPLORED){
.                    DFS(G,v);
.                }
.            }
.    }       
.    DFS(G,v){                                          // explore the graph starting at vertex v
.        setLabel( v, VISITED);                         // mark vertex v as VISITED
.                    
.        std::for_each (Vertex w: G.adjacent(v))        // look at each adjacent vertex to v (set as vertex w)
.            {
.                if (getLable(w) == UNEXPLORED)         // if vertex w is unexplored
.                   {      
.                      setLabel( v, w, DISCOVERY);          // the edge of (v,w) is marked as DISCOVERY
.                      setLable( w, VISITED);               // w is marked as visited
.                      DFS(G,w);                            // start the DFS(G,v) starting at w
.                    } elseif {
.                           getLable(v,w)==UNEXPLORED;   // if vertex w is NOT labeled unexplored but the edge (v,w) is unexplored
.                           setLable(v,w,BACK);             // then lable that edge as BACK
.                    }
.            }
.     }           

[RUN TIME ANALYSIS] ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BFS                                  RUN TIME
Queries Vertex: n =>                   O(n)               // go through each vertex once
Queries Edge: sum(degree(v)) => 2*m => O(m)               // summing up all the vertices gives us an expression that's twice the number of edges

DFS 
Labeling Vertex: 2*n =>                O(n)               // go through each vertex twice, once to see if unexplored, second for visited
Labeling Edge:   2*m =>                O(m)               // go through each edge twice, once to see if unexplored, another label as back

