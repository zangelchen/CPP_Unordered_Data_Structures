COLLISION STRATEGIES

[ STRATEGY 1: SEPARATE CHAIN HASHING]

S={16,8,29,22}
h(k)= k % 7  				//hash function for input k. mod7 means array is of size 7

Divide each item in the array by 7 to know where to place into the hash table 

 4 % 7 = 4	  8 % 7 = 1		// COLLISION with 3 items in the first hash
16 % 7 = 2   11 % 7 = 4
29 % 7 = 1	 22 % 7 = 1
	  
Separate chaining: insert the collision in front of the itenger

0
1 -> [22] -> [29] -> [8]
2 -> [16]
3
4 -> [11] -> [4]
5
6

RUNTIME ANALYSIS 

LOAD FACTOR - determines how full the table is 

		alpha (load factor)= n/N  

		n = number of elements inside the table (S)
		N = size of table itself (mod7)(aka array size)

		alpah = 1 = table is full 
		alpha = 0.5 = table is half full
		alpha = 2 = two element per space in the table

SUMMARY TABLE 

		Worst Case 		Load Factor 
Insert   O(1)   		  O(1)
Remove	 O(n)		     O(alpha)
Find	 O(n)		     O(alpha)


[ STRATEGY 2:  PROBE BASED HASHING]

If the space is occuppied, we do a second hash to fill the next spot. 
- single hash (aka simply choosing the next empty spot) will caues a primary clustering where the probability will be uneven across the array 
- double has puts h(k) through another hash function (usually double the mod) and insert it at the next empty spot for even distribution of data  


The runningtime is only dependent on the proportion in alpha and NOT the amount of data we have 
 - can have a billion data points, as long as ratio of data point to array size is less than 1 (alpha) then run time is fast 