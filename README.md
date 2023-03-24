# Data-Structures-and-Algorithms

codes for DSA, from pre-mid to finals

## Written by: Matthew Dave Desabelle

### Pre-midterm Topics

1)  Abstract Data Type (ADT)
2)  ADT List 
     a) List Operations:  Initialize, insert, delete, member, locate, and other operations 
     
     b) Implementations of ADT List:
     
        i) Array Implementation (4 versions)
        
           Version 1: List is a structure containing an array and variable count
           
           Version 2: List is a pointer to a structure containing an array  and variable count
           
           Version 3: List is a structure containing a pointer to the 1st element of a dynamic array, and variable count
           
           Version 4: List is a pointer to a structure containing a pointer to the 1st element of a dynamic array, and variable count 
           
        ii) Linked List Implementation (Singly Link)
       iii) Cursor-based Implementation
      c) Time Complexity of the List operations in different implementations : O(1), O(N), and O(N*N)
3) ADT Stack and Implementations
    a) Stack Operations:  Top, Pop, Push, and other utility functions such as initStack, isEmpty, and isFull 
    b) Implementations 
        i) Array Implementation (4 versions)
       ii) Linked List Implementation
      iii) Cursor-based Implementation
    c) Time Complexity:  O(1) and O(N)
4) ADT Queue and Implementations
    a) Queue Operations: Front, Dequeue, Enqueue, and other utility functions such as initQueue, isEmpty, and isFull
    b) Implementations
        i) Linked List Implementation
           1) Queue is a pointer to a dynamically allocated node
           2) Queue is a structure containing front and rear pointers to dynamically allocated node/s
        ii) Circular Array Implementation
            Solution 1: Add a counter
            Solution 2:  Queue is full if there are MAX-1 elements 
                          where MAX is the size of the array
    c) Time Complexity:  O(1) and O(N)
