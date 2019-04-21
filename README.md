# Bankers-Algorithm
The Banker's algorithm is a resource allocation & deadlock avoidance algorithm developed by Edsger Dijkstra that tests for safety by simulating the allocation of pre-determined maximum possible amounts of all resources, and then makes a "safe-state" check to test for possible deadlock conditions for all other pending activities, before deciding whether allocation should be allowed to continue. The algorithm was developed in the design process for the operating system and originally described (in Dutch) in EWD108. The name is by analogy with the way that bankers account for liquidity constraints. 
Algorithm The Banker's algorithm is run by the operating system whenever a process requests resources. The algorithm prevents deadlock by denying or postponing the request if it determines that accepting the request could put the system in an unsafe state (one where deadlock could occur). When a new process enters a system, it must declare the maximum number of instances of each resource type that may not exceed the total number of resources in the system.
Let us assume that there are n processes and m resource types. Some data structures that are used to implement the banker's algorithm 

##Safe and Unsafe States
 A state (as in the above example) is considered safe if it is possible for all processes to finish executing (terminate). Since the system cannot know when a process will terminate, or how many resources it will have requested by then, the system assumes that all processes will eventually attempt to acquire their stated maximum resources and terminate soon afterward. This is a reasonable assumption in most cases since the system is not particularly concerned with how long each process runs (at least not from a deadlock avoidance perspective). Also, if a process terminates without acquiring its maximum resources, it only makes it easier on the system. Given that assumption, the algorithm determines if a state is safe by trying to find a hypothetical set of requests by the processes that would allow each to acquire its maximum resources and then terminate (returning its resources to the system). Any state where no such set exists is an unsafe state.


#Given Problem:
Reena’s operating system uses an algorithm for deadlock avoidance to manage the allocation
of resources say three namely A, B, and C to three processes P0, P1, and P2. Consider the
following scenario as reference .user must enter the current state of system as given in this
example: Suppose P0 has 0,0,1 instances , P1 is having 3,2,0 instances and P2 occupies 2,1,1
instances of A,B,C resource respectively. Also the maximum number of instances required for P0
is 8,4,3 and for p1 is 6,2,0 and finally for P2 there are 3,3,3 instances of resources A,B,C
respectively. There are 3 instances of resource A, 2 instances of resource B and 2 instances of
resource C available.
Write a program to check whether Reena’s operating system is in a safe state or not in the
following independent requests for additional resources in the current state:
1. Request1: P0 requests 0 instances of A and 0 instances of B and 2 instances of C.
2. Request2: P1 requests for 2 instances of A, 0 instances of B and 0 instances of C.



## Note: The request must be given by user as input.

##Banker’s Algorithm:
Define quantities:
```
•	AVAILABLE : array [1 .. m] of integer; -- it specifies for each resource how many copies of it are available
•	ALLOCATION: array [1..n, 1..m] of integer; -- ALLOCATION[i,j] specifies the number of copies of resource j that are allocated to process i.
•	MAXIM: array [1..n, 1..m] of integer; -- MAXIM[i,j] specifies the maximum number of copies of resource j that process i will use.
•	NEED; array [1..n, 1..m] of integer; -- NEED[i,j] specifies the number of copies of resource j that process i still requires. It is equal to MAXIM[i,j]-ALLOCATION[i,j]

```
and the following notation
•	A < B, where A and B are m-ary vectors, is true iff for all i, A[i] < B[i]
•	If A is a rectangular matrix, Ai is its ith row.

```
    procedure BANKER(REQUEST_I: array[1..m] of integer;
                     i : 1..n) is
    {
        if REQUEST_I > NEEDi then
           ERROR;    -- The user is asking more than the agreed maximum
	repeat
            while (REQUEST_i > AVAILABLE)
	       yield; -- Resources are not available at this time
            ALLOCATION_i = ALLOCATION_i + REQUEST_i;
            AVAILABLE = AVAILABLE - REQUEST_I;
            if SAFE_STATE then
               RETURN;  -- The request is approved
            ALLOCATION_i = ALLOCATION_I - REQUEST_i;
            AVAILABLE = AVAILABLE + REQUEST_i;
            YIELD;  -- The request cannot safely be satisfied at this time
        forever;
    }

    BOOLEAN function SAFESTATE is -- Determines if current state is safe
    { NOCHANGE : boolean; 
      WORK : array[1..m] of INTEGER = AVAILABLE;
      FINISH : array[1..n] of boolean = [false, ..,false];
      I : integer;

      repeat
        NOCHANGE = TRUE;
        for I = 1 to N do
          if ((not FINISH[i]) and
             NEEDi <= WORK) then {
             WORK = WORK + ALLOCATION_i;
    	        FINISH[i] = true;
             NOCHANGE = false;
          }
      until NOCHANGE;
      return (FINISH == (true, .., true));
    }
```

The time complexity of the Banker's algorithm as a function of the number n of processes and m of resources is o(n*n*m).

#Banker’s (Safety) Algorithm:
 find a safe sequence:
i.e. is the system in a safe state?
```
1. Let Work and Finish be vectors length m and n respectively.
	Initialize Work = Available, and Finish[i]=false for i=0,...,n-1
2. Find a process i such that both
	• Finish[i] = = false, and
	• Needi ≤ Work
	If no such i exists, go to step 4.
3. Work = Work + Alloci
	Finish[i] = true
	Go to step 2.
4. If Finish[i] = = true for all i, then the system is in a safe state

```