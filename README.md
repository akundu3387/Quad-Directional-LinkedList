# Quad-Directional Linked List

Arjun Kundu

09/11/21
------------------------------------------------------------------------------------------------------------------

To Compile: g++ -g -Wall graph.cpp mytest.cpp -o mytest

------------------------------------------------------------------------------------------------------------------
**Objectives:**

- Implementing a Quad-Directional Linked List container, with each node connected to 4 different nodes(north,east,south,west)

- Traverses through the LL to find a path specified in main() found in: mytest.cpp

- Contains classes Node and Graph, Graph objects use nodes from Node class to perform main functions(findPath(),Display())

- Loads input from a text file found in: Data.txt which contains a graph style grid , then initializes each node accordningly

- Implementing linked list routines, i.e. insertion, finding nodes, display, ect

- Practice the use of STACKS

- Practice C++ dynamic memory management, i.e. avoiding memory leaks, avoiding double free, protection against wrong accesses in memory (segmentation  fault), etc.

------------------------------------------------------------------------------------------------------------------
**Reading in input from data.txt:**

- First line is # of total Nodes

- Nodes in data are in 5 columns

- First Column is the node number

- Second Column is the node # at North Position

- Third Column is the node # at East Position

- Fourth Column is the node # at South Position

- Fifth Column is the node # at West Position
