

Hash Table 


HASH TABLE BASED DICTIONARY

	[CODE]
	Dictionary<KeyType, ValueType> d;
	d[k] = v;

HASH TABLE CONTAINS THREE THINGS
1. Hash Function -> transport input into a hash identifier 
2. An array -> stores the data that is indexed in by the hash function
3. Collisions Handling Strategy -> to sort out when hash function map two different function to the same array 

PERFECT HASH FUNCTION

STRUCTURE
1. Transformn into integer value
2. compress within the bounds of an array (with a mod operator or %N )

3 CHARACTERISTICS OF A GOOD HASH FUNCTION 
1. Computation time 
	- Constant time O(1) run time
2. Deterministic 
	- if we hash a string once and we hash it a second time, the output is the same 
3. Satisfy the SUHA
	- Simple uniform hashing assumption 
	- result of our hash algorithm must be uniform across the entire key space 
	- any random two values are going to randomly be in different place in an array with equal probability (aka hash into both even or odd space with equal probability)

Which collision resolution strategy is better?
1. Big Records
    - separate chaining
2. Structure Speed
    - double hashing

What structure do hash tables replace?
    - dictionary
    - important to know what structure is suitable for what. ex: AVL tree (good with range finding the nearest neighbor - hashing is not good at this)

What constraint exists on hashing that does not exist with BSTs?
    - the idea that BST has a great nearest neighbor approach while hashing does that have that
    - hash function great at doing lookups at O(1) lookup times

Why talk about BSTs at all?
    - Hash tables does not solve everything

