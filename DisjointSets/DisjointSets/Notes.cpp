*********************************************************************** DISJOINT SETS ***********************************************************************

Disjoint Set - series fo sets which as disjoint fron eachother but eery element within the set is considered equivalent to each other. 
.
.    EXAMPLE: 
.
.    There are four disjoint sets. 2,5,9 are considered equivalent to eachother given they are in the same set, but different that other numbers
.    because they are in different sets. 
.
.    Each set has a representative member that serves as the unique identifier. For example, it could be the first element in each of these sets or the second element. 
.
.    [2,5,9]        representative is 2
.    [0,1,4,8]      representative is 0
.    [7]            representative is 7
.    [3,6]          representative is 3
.
API: 
.    void makeSet (const T & t);
.    void set_union( const T & k1, const T & k2);  //not union because that's a c language
.    T & find(const T & k)


******************************************************************** API FUNCTIONS EXPLAINED ********************************************************************

makeSet
. - creates the disjoint sets 

FIND() 
. - locates the element and returns the representative
.
.   ex) Find(5)   // output is 2
.
. - need to make sure that the same representative returns for each element in the same sets 
.
.    ex) Find(5) == Find(2) == Find(9) == true


UNION()
. - combines two sets together 
.
.    ex) set_union(find(2),find(7)) // [2,5,9,7]

UNION-FIND DYNAMIC
.
.  if(find(2)!=find(7)){
.       set_union(find(2),find(7));
.   }                                  // notice 7 now has a different identity than before. its identity is now find(2)

*********************************************************** NAIVE IMPLEMENTATION A DISJOINT SET ALGORITH *****************************************************************

** GOOD for Find, BAD for Unions

[EXAMPLE:]
.        DISJOINT SET :                  
.        [0,1,4] [2,7] [3,5,6]
.
.        ARRAY VIEW: (SINCE THE 8 NUMBER VALUES ARE BETWEEN 0 - 7, IT CAN FIT INTO AN ARRAY, OTHERWISE USE HASH ALGORITHM TO CREATE AN INDEX INTO AN ARRAY)
.        INDEX #: [0][1][2][3][4][5][6][7]
.        ARRAY  :  0  0  2  3  0  3  3  2  
.
[ANALYSIS;]
.        The array format allows us to quickly find the identity (representative member) of a set, but it is very slow for unions  
.
.        - find the identity gives a run time of 0(1) because can look at the index number and return the corresponding value in array 
.        - union is O(n) run time because have to sort through every element to identify if a number is in a union or not
.        
.        [EX] union 
.            [0,1,4,2,7] [3,5,6] 
.
.             INDEX #: [0][1][2][3][4][5][6][7]
.             ARRAY  :  0  0  2  3  0  3  3  2  -> need to sort through the array starting from the beginning to upate the identifiers for 2 and 7 to 0


*********************************************************** UPTREE IMPLEMENTATION A DISJOINT SET ALGORITH *****************************************************************

A faster way to find the indentifier in Unions by using pointers to connect the representative elements together

The value of the array is -1 if we have found the representative element. 
The value of the array is the index of the parent if the value is not the representative element 
By updating only one pointer, we can update the representative element for multiple keys. 

[EXAMPLE] Update every key below to identifier of 0

.            Index (is the key)          [ 0 ][ 1 ][ 2 ][ 3 ]
.            Array Values (identifers)   [-1 ][-1 ][-1 ][-1 ]
.
.            Index (is the key)          [ 0 ][ 1 ][ 2 ][ 3 ]     [3]->[0]        // [3] points to [0]
.            Array Values (identifers)   [-1 ][-1 ][-1 ][ 0 ]  
.
.            Index (is the key)          [ 0 ][ 1 ][ 2 ][ 3 ]     [3]->[0]   
.            Array Values (identifers)   [-1 ][-1 ][ 1 ][ 0 ]     [2]->[1]        //[2] points to [1] (now [1) is the parent of [2])
.
.
.            Index (is the key)          [ 0 ][ 1 ][ 2 ][ 3 ]     [3]->[0]        // create a tree where       [0]
.            Array Values (identifers)   [-1 ][ 0 ][ 1 ][ 0 ]     [2]->[1]->[0]                                 |
.                                                                                 //                    [2]->[1] [3]

[EXAMPLE] Update one pointer to Union Find(4) to Find(7)
.
. Disjoint Set            [2,5,9]    [7]    [0,1,4,8]     [3,6]
.                            5        7         4           3
. Tree View of Set           |                  |           |
.                           9 2               0   8 <-1      6
.   
. Index(key)         [ 0 ][ 1 ][ 2 ][ 3 ][ 4 ][ 5 ][ 6 ][ 7 ][ 8 ][ 9 ]           // original view
. Array(Identifer)     4    8    5   -1   -1   -1    3   -1    4    5
.
. Index(key)         [ 0 ][ 1 ][ 2 ][ 3 ][ 4 ][ 5 ][ 6 ][ 7 ][ 8 ][ 9 ]           // after updating pointer
. Array(Identifer)     4    8    5   -1    7   -1    3   -1    4    5
.

******************************************************************** UPTREE SIMPLE RUNNING TIME *********************************************************************


[SAMPLE FIND() CODE] 
.
.       int DisjointSets::find() {
.            if ( s[i] < 0 ) {                       // if the value of array (s[i]) is less than 0 (aka equal to -1), then it is the identity element, return the index (i)
.                return i;
.            } 
.            else {                                  // if the value of array (s[i] is >= than 0, recursively call the _find algorithm to look at the element denoted inside the array (s[i])
.                return _find(s[i]);                 // and return the value of the array (s[i])
.            }
.        }

[WORST CASE UPTREE]               [IDEAL UPTREE]       
.        [4]                            [4]
.        [3]                             |
.        [2]                         [1][2][3]
.        [1]

[WHAT IS THE RUNNING TIME?]  O(n)
.  - run time is the height of the UpTree 
.  - to find 1, we need to find 2, which needs 3, which needs 4

[WHAT IS THE IDEAL RUNNING TIME?]  O(1)
.  - A single identity node as the root node, and every child is right underneath the root node
.  - Ideally locate what the descendants are of the root and point them directly to the root node. aka PATH COMPRESSION

**************************************************************** UPTREES: SMART UNION & PATH COMPRESSION ****************************************************************

[PATH COMPRESSION]
.
.        [BASE CASE UPTREE]    .....       [IDEAL UPTREE]        .....         [FINAL IDEAL UPTREE]   
.                [1]                             [1]                                    [1]
.                 |                               |                                      |
.              [2] [3]                     [2] [3] [4] [7]                    [2] [3] [4] [5] [6] [7]
.                   |                           |   |   |
.                [4] [5]                       [5] [6] [3]
.                 |  
.              [6] [7] ..locate find(5)

.    - first run starts at [7], then traverse all the way to the root node [1]
.    - as the function goes up the path, it notes that [4] and [3] are also descendants of [1] and points [4] and [3] directly to [1]
.    - next time we do Find(6), it points [6] to [1] after traversing down the length of the path 
.    - this is done until all of the descendants are directly under the identifier, so run time can be O(1)


[UNION BY HEIGHT]
.    - idea to keep the height of the tree as small as possibe
.    - place smaller height under the larger height 
.    - however, each node in the added subtree increases by 1

.    height = 1   height = 2      height = 2                                    
.        [3]         [4]              [4]
.         |           |                |
.    [2] [1] [0]     [5]          [3]     [5]
.                     |            |       |
.                    [6]       [2][1][0]  [6]


[UNION BY SIZE]
.    - idea is to minimize the number of nodes thati ncrease in height
.    
.    height = 1   height = 2           height = 3
.        [3]         [4]                   [3]
.         |           |                     |     
.    [2] [1] [0]     [5]             [2] [1] [0] [4]
.                     |                           |
.                    [6]                         [5]
.                                                 |
.                                                [6]
.

[SUMMARY OF UNION BY SIZE VS HEIGHT]

.   - Keepts the height run time at O(logn)
.   - Note: Identity node is -h-1 than just -1 because we want to also keep track of the height of the tree but not in a positive value or it'll clash with the other pointers

. [ 0 ][ 1 ][ 2 ][ 3 ][ 4 ][ 5 ][ 6 ]        // index
.   3    3    3    4   -3    4    5          // union by height - notice the height remains unchanged 
.   3    3    3   -4    3    4    5          // union by size - height increased nu individual nodes did not

[RUNTIME ANALYSIS]
.   - UPTREE algorithm has a near constant run time. Its run time is iterated log. 
.
.   - Iterated Log is the number of times you can take a log of a number
.
.             - Log refresher: Computer science assumes log base 2 (working in binary space, how many time can we halve a data set)
.                       log(8) = 3  (2^3 = 8)
.            - Iterated Log: 
.                             (             0 , n<=1)
.                     log*(n) ( 1+log*(log(n)), n> 1)
.
.           - [EXAMPLE] Find the iterated log of one disjoint set of size 2^65,536  (remember computer science is log base 2)

.               log*(2^65k) - log*(65k) - log*(254) - log*(16) - log*(4) - log*(2) - log*(1) - appx 1
.               
.               Answer: log*(65k) = 6 
.                      - we only have to go through the iterated log six times from the previous gigantic number. 
.                      - This means the algorithm grows proportional to the number of times you can take the log of a given number 
.    
.   -  Therefore any sequence of m union and find operations result in the worse case running time of 
.               O( m * log*(n) )
.   -  Where n is the number of items in the Disjoint Sets and m is the number of union/find we are doing for the number of disjoint sets
    
