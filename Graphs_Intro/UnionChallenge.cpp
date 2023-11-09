
#include <iostream>
#include <set>

class DisjointSets {
public:
  static constexpr int MAX_NODES = 256;                               // We'll statically allocate space for at most 256 nodes.

  int leader[MAX_NODES];                                              // Referes to the leader, it's -1 if it's vertex is the leader, otherwise returns the leader

  bool has_cycle[MAX_NODES];                                          // Determins if the vertex is part of a cycle in its connected component. True is it is. 
  
  int num_components;                                                 // The number of components found.

  DisjointSets() {                                                    //constructor for the DisjointSets class
    for (int i = 0; i < MAX_NODES; i++) leader[i] = -1;               // Initialize the leaders array, where each index represents a vertex with -1 for the identifier
    for (int i = 0; i < MAX_NODES; i++) has_cycle[i] = false;         // Initialize has_cycle array. Initially assumes the graph starts without any cycles
    num_components = 0;                                               // The components will need to be counted.
  }                                             
                                                        
  int find_leader(int i) {                                            // The leader is set to -1, if the leader returned is -1, then report vertex i as its
    if (leader[i] < 0) return i;                                      // own leader. Otherwise, keep looking for the leader recursively.
    else return find_leader(leader[i]);
  }                     
  
  bool query_cycle(int i) {                                         // query_cycle(i) returns true if vertex i is part of a connected component
    int root_i = find_leader(i);                                     // that has a cycle. Otherwise, it returns false. This relies on the has_cycle array  
    return has_cycle[root_i];     
  }

  void dsunion(int i, int j); //definition in Task 1
  void count_comps(int n);
};

// TASK 1:
// dsunion performs union on disjoin sets. The leader of vertex j becomes the leader of vertex i
// Modify the implementation of dsunion below so that query_cycle(root_j) accurately reports
// whether the connected component of root_j contains a cycle.
      // This is evident when a vertex is assigned a leader that is the same as the one it was already assigned previously.
      // Also, if you join two sets where either set already was known to have a cycle, then the joined set still has a cycle.

void DisjointSets::dsunion(int i, int j) {
  bool i_had_cycle = query_cycle(i);                                     //is vertex i part of a cycle
  bool j_had_cycle = query_cycle(j);                                     //is vertex j part of a cycle
  int root_i = find_leader(i);                                           //find leader (root_i) of vertex i using find_leader function
  int root_j = find_leader(j);                                           //find leader (root_j) of vertex j using find_leader function
  
  if (root_i != root_j) {                                                //if the leaders of vertex i and vertex j are NOT the same
    leader[root_i] = root_j;                                             //updates the leader array to make root_j the leader of vertex i (previously shown as root_i)
    root_i = root_j;                                                     //update the local variable root_i to new leader root_j (does not change the leader array)
  }
  else {
    has_cycle[root_i]=true;                                              //if the leaders ARE the same, then mark the connected component as having a cycle
  }
  bool original_cycle = i_had_cycle || j_had_cycle || has_cycle[root_i]; // set to true if vertix i is part a cycle, or vertex j is part of a cycle, or the connected component already has a cycle
  if (original_cycle == true){
  has_cycle[root_i]=original_cycle;                                      //mark the connected component as true
  }
}

// TASK 2:
// count_comps should count how many connected components there are in
// the graph, and it should set the num_components member variable
// to that value. The input n is the number of vertices in the graph.
// (Remember, the vertices are numbered with indices 0 through n-1.)
void DisjointSets::count_comps(int n) {

  // TODO: Your work here!
    std::set<int> countSet;                                             // create a set
    for (int i = 0; i < MAX_NODES; i++) {                               // iterate through the vertices                     
    if (leader[i]>-1){                                                  // find the leader of each vertices in the leader array 
         int root = find_leader(i);                                     // find the leader of the vertice
         countSet.insert(root);                                         // insert it into the created set if it's different
    }
    num_components = countSet.size();                                   // countSet stores the different leaders. the number of entries means the number of connected components (how many separate subtrees)
    }
}

int main() {

  constexpr int NUM_EDGES = 9;
  constexpr int NUM_VERTS = 8;

  int edges[NUM_EDGES][2] = {{0,1},{1,2},{3,4},{4,5},{5,6},{6,7},{7,3},{3,5},{4,6}};  

  DisjointSets d;                                                           //initiate DisjointSets class. d is a variable indicated an instance of DisjointSet class

  for (int i = 0; i < NUM_EDGES; i++)                                       //iterating through the array of edges and doing the union function on them
    d.dsunion(edges[i][0],edges[i][1]);

  d.count_comps(NUM_VERTS);                                                 // counting the number of connected components

  std::cout << "For edge list: ";                                           //returns the edge list
  for (int i = 0; i < NUM_EDGES; i++) {
    std::cout << "(" << edges[i][0] << ","
         << edges[i][1] << ")"
         // This avoids displaying a comma at the end of the list.
         << ((i < NUM_EDGES-1) ? "," : "\n");
  }

  std::cout << "You counted num_components: " << d.num_components << std::endl; //returns the connected compoents (Task 2)

  // The output for the above set of edges should be:
  // You counted num_components: 2

  std::cout << "Cycle reported for these vertices (if any):" << std::endl;      //returns the vertices in the cycle. This is done by the d.query_cycle
  for (int i=0; i<NUM_VERTS; i++) {                                             // disunion performs unions on each pair of vertices and updates has_cycle to mark the connected component as having a cycle
    if (d.query_cycle(i)) std::cout << i << " ";                                // if the conneted component has a cycle, query_cycle then determines if a specific vertex is part of that cycle by returning true/false
  }
  std::cout << std::endl;

  // The cycle detection output for the above set of edges should be:
  // Cycle reported for these vertices (if any):
  // 3 4 5 6 7 

  return 0;
}
