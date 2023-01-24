/****************************
Templated created by Kazumi Slott
CS311

Your name: Jared Falcon
Your programmer number: 5
Any difficulties?: Yes
*****************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
#include <list>
#include <stack>
using namespace std;

class edge
{
  //????????????;  //## You want to access the private members of edge class from graph class
  friend class graph;
  int neighbor; //adjacent vertex
  int wt; //weight of the edge
 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w) {neighbor = u; wt = w; /* ## set data members */};
};

class graph
{
  int num_ver; //the total number of vertices in the graph
  list<edge*>* ver_ar; //pointer to the dynamic array that holds linked lists. The element of a node in a linked list is a pointer to an edge object 
                       //Let's use the library's list class. It is actually a doubly linked list. 
  int nextUnvisitedNodes(int* num);
  void DFT_helper(int v, int i, int* num, string& edges);
 public:
  graph(int V);
  ~graph();
  void addEdge(int v, int u, int w=1);  //If the weight is not given, 1 is used for wt.
  void BFT(int start);
  void DFT(int start);
  void DijkstraShortestPath(int start);
  void shortestPath(int start);
  
};

//constructor: num is the number of vertices
graph::graph(int num)
{
  //##
  num_ver = num;//assign num to num_ver to initialize 

  ver_ar = new list<edge*>[num_ver];//we make a new dynamic array 
  
  //##             //make a dynamic array with num slots where each slot holds a list object. 
                   //The element of a node in the linked list is a pointer to an edge object 
}

graph::~graph()
{
  //destroy all the edge objects created in heap                                                                                                        
  //For each vertex in ver_ar
  //    go through each node in the linked list. The element field of each node points to an edge object created with "new". You need to delete these.  
  for(int i = 0; i < num_ver; i++)//go through our dynamic array suing num_ver
    {
      for(list<edge*>::iterator u = ver_ar[i].begin(); u != ver_ar[i].end(); u++)//use the for loop to get to 
	{//each edge object and destroy it 
	  delete *u;//will destroy the edge object 
	}
    }

  delete [] ver_ar;//delete the dynamic array from heap 
  //The library's list class has a destructor. All nodes belonging to the list will be destroyed by the destructor.
  //https://www.cplusplus.com/reference/list/list/~list/

  //destroy the ver_ar dynamic array
}

/*********************************************
ar is the dynamic array
a is an element
b is an element
function to exchange values in the dynamic
array
 ********************************************/
void exchange(int* ar, int a, int b)
{
  //I have 3 lines of code here.
  int temp = ar[a];
  ar[a] = ar[b];
  ar[b] = temp;
}

/**********************************************
toBe is the dynamic array
size is the size of the array
u is the value to compare with the array value

This function will return true or false to check 
if the value is in the dynamic array
***********************************************/
bool YES(int* toBe, int size, int u)
{
  for(int i = 0; i < size; i++)
    {
      if(toBe[i] == u)//compare values
	return true;//return true
    }
  return false;//return true
}


/***********************************************************************
 ar the heap array
n is the size
i is the index of root

This helper function will be called at a specific index in the heap array
and check if the parent is greater than its child(ren). Assume the parent
has two children. If the parent is not greater than left child or the right
child, the parent has to switch with which ever is greater from the three.
If the switch happens, the function will call itself recrusively to make the
same comparison with any children under that as well. It will repeat until
it is a max heap.
**********************************************************************/
void min_heapify(int* toBe, int* curr, int n, int i)
{

  int L = 2*i + 1; //the index of the left child of i
  int R = 2*i + 2; //the index of the right child of i
  int small = i;//stores largest index

  //look for the largest among 3 elements at i, l and r. largest gets the index of the largest value.
  //Make sure l and r don't go over the heap's range.
  //Recall how you found the largest value among 3 values in CS111.
  //???????? //I have 6 lines of code here. You can have more or less.
  // small = i;//make parent index largest index first
  if(L < n && curr[toBe[L]] < curr[toBe[i]])//compare with left child and keep range
    small = L;//if left child is bigger, it now becomes largest and takes its index

  if(R < n && curr[toBe[R]] < curr[toBe[small]])//compare with right child and keep range
    small = R;//if right child is bigger, it now becomes largest and takes its index


  //The largest is either the right or left child. In other words, it is not the root at i.
  if(small != i)//only enter if largest is not parent ( i )
    {
      //exchange the 2 values
      exchange(toBe, i, small);//switch values parent and child
      //There might be a violation at the position that was exchanged. Call max_heapify to fix it.
      min_heapify(toBe, curr, n, small);//make sure to correct it again if needed for lower children if any
    }

}
/*************************************************************
ar is the heap array
n is the size of the array

This helper function will be able to create or fix any violations
in a heap array. It will find the parent indexes in the array and
call the function max_heap and work its way up visiting every
parent. It will correct any violations of max heap all the way
up to the root.
**************************************************************/
void build_min_heap(int* toBe, int* curr, int n)
{
  //2 lines of code in this function
  for(int i = n / 2 - 1; i >= 0; i--)//find the last parent and work your way up
    min_heapify(toBe, curr, n, i);//call max heap on each parent index
  //call max_heapify (turn the smallest subtrees into max-heaps and work your way up)
}


/**************************************************************
tobe is one of the dynamic arrays
curr is the second dynamic array
size is the size of the arrays

This function will exchange the smallest value with the last 
value in the arrya nd then we will decrease the size of the 
array so it can get rid of the smallest value. It will return
the smallest value as well.
 *************************************************************/
int getMIN(int* toBe, int* curr, int& size)
{
  int min = toBe[0];//store first element
  exchange(toBe, 0, size-1);//exchange with last element
  // Exchange(toBe[0], toBe[size-1]);
  size--;//decrease size to keep heap
  min_heapify(toBe, curr, size, 0);
  return min;

}


//add an edge from v to u with weight w into the graph
/**********************************************************
v is the index for the array
u is the neighbor
w is the weight 

This function will create a new edge object and push that into
our array. 
 *********************************************************/
void graph::addEdge(int v, int u, int w)
{
  //We are using the list class from the library. Which member function do you need to use to add a node at the end of the list?
  //https://www.cplusplus.com/reference/list/list/
  //Don't create an edge object statically, then it would get destroyed as soon as you leave this function. You need to create an edge object dymamically in heap, which will remain in heap even after you leave this function.. Remember "new" operator returns the memory address of the newly created object.
  //I have one line of code in this function.
  ver_ar[v].push_back(new edge(u, w));
  
}


//start Traversal at start
/***************************************************
start is our starting point where we traverse

This function will help us traverse the graph using the
Depth First Traversal method 
 ***************************************************/
void graph::DFT(int start)
{
  string edges = "";//used to append the edges
  //I made dynamic array called "num"
  int* num = new int[num_ver];//create dynamic array with num_ver (amount of vertices)

  for(int i = 0; i < num_ver; i++)//intinialize the array and put 0 in every slot 
    num[i] = 0;

  int v = start;//v takes the value of start
  int i = 1;//initialize i to 1

  DFT_helper(v, i, num, edges);//call our helper function

  while(nextUnvisitedNodes(num) != -1)//allows us to access unvisited vertices 
    {
      v = nextUnvisitedNodes(num);//v will take the next unvisited node 
      DFT_helper(v, i, num, edges);//call DFT again with the new vertex
      //    v = nextUnvisitedNodes(num);
    }


    //I used do-while
  //I am calling nextUnvisitedNodes() to see if there are more unvisited nodes.


  cout << "edges = " << edges << endl;
  delete [] num;
  //Don't forget to destroy the dynamic array
}

/************************************************************************
//I made the following function to see if there are still unvisited nodes
num is our dynamic array 

This function will return the index of any unvisted node in the array
**********************************************************************/
int graph::nextUnvisitedNodes(int* num)
{
  //go through the num array to see if you find a vertext with num=0. If so, return the index. If all visited, return -1.
  for(int i = 0; i < num_ver; i++)//go through the array
    {
      if(num[i] == 0)//if we find one with 0, return the index
	return i;
    }
  return -1;//else return -1

}

/*********************************************************************
v is the array index 
i used to intialize the num current index
num* is the dynamic array
edges is the string we append the egdes to

This function will help us traverse the list of nodes with edges objects
It will help us append the current index with the neighbor vertex
 *********************************************************************/
void graph::DFT_helper(int v, int i, int* num, string& edges)
{
  //I have to use a c-string to make a string of edges. You don't need to use it if you know another way.
  char ar[5] = "v->u"; //v->u plus NULL character = size 5   

  num[v] = i++;//increment the first index
  cout << char('A' + v) << "->";//display the letter

  //  v = nextUnvisitedNodes(num);
  //The following shows how to iterate the library's linked list. You use an iterator.
  //https://www.cplusplus.com/reference/list/list/end/ 
  //iterator class is nested inside list class
  for (list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)
    {
      //From the example on https://www.cplusplus.com/reference/list/list/end/
      //Notice *u gives you the element of the node pointed to by u. The element is a pointer to an edge object.
      //Between * and -> operator, -> has higher precedence. You need to use () around *u to get the element first. 
      
      if(num[(*u)->neighbor] == 0)
	{
	  ar[0] = char(v + 'A');//replace index 0 by the name of v 
	  ar[3] = char((*u)->neighbor + 'A'); //replace index 3 by the name of u
	  edges += string(ar) + ","; //add v->u, to the end of edges
	  //v = nextUnvisitedNodes(num);
	  DFT_helper((*u)->neighbor, i, num, edges);//call DFT with the new v which is neighbor 
	}

    }
}


/*******************************************************************
start is the index for the start vertex

This fucntion will help us traverse the graph using the Breadth First Traversal 
method. It will make sure to check if there are any disconnectd graphs 
we need to check. 
********************************************************************/
void graph::BFT(int start)
{
  string edges = "";//used to append the edges
  char ar[5] = " -> "; //"v->u"
  int v;//used to store start
  int x;//will be used to assign 1
  //Use the queue class from the library
  queue<int> queue;

  int* num = new int[num_ver];//dynamic array

  for(int i = 0; i < num_ver; i++)//intialize the array with 0s
    num[i] = 0;

  // v = start;//v takes start value
  x = 1;//the first vertex visited gets 1

  while(nextUnvisitedNodes(num) != -1)//allows us to visit disconnected graphs
    {
      num[start] = x++;//increment the index of num with the start value
      queue.push(start);// push the index value into the queue
      //I used do-while to visit all unconnected grap

      while(!queue.empty())//if the queue is not empty
        {
          start = queue.front();//v takes the value of the front of the queue
          cout << char('A' + start) << "->";//output
          queue.pop();//pop it

          //traverse the list of nodes that also have edges objects pointing out
          for(list<edge*>::iterator u = ver_ar[start].begin(); u != ver_ar[start].end(); u++)
            {

              if(num[(*u)->neighbor] == 0)//check the adjacent vertices of u to v
                {
                  num[(*u)->neighbor] = x++;//increment the neighbor of u
                  queue.push((*u)->neighbor); //add it to the queue
                  // edges = edges;
                  ar[0] = char(start + 'A');//change the edges string to replace the given letter
                  ar[3] = char((*u)->neighbor + 'A');//change that part of the array with the neighbor of u
                  edges += (string)ar + " ";//append it to the string
                }

            }

        }
      start = nextUnvisitedNodes(num);//take the value of the next unvisted node
    }

  //Check the manual to figure out what member functions of the queue class you need to use.
  // https://www.cplusplus.com/reference/queue/queue/

  cout << endl;
  cout << "edges = " << edges << endl;
  delete [] num;
}
/*********************************************************
start is the start of the index

This function will find the shortest path of a graph
using Dijkstra's alogorithm.  
 ********************************************************/
void graph::DijkstraShortestPath(int start)
{
  //I have 2 dynamic arrays here.
  int* current = new int[num_ver];//current dynamic array
  int* pre = new int[num_ver];//predecessor dynamic array
  int* toBeChecked = new int[num_ver];//tobechecked array
  int v;
  int size = num_ver;

  for(int i = 0; i < num_ver; i++)//intilialize the current array with a large value
    current[i] = 9999;

  current[start] = 0;//initiate current to 0
  pre[start] = 0;//initiate pre to 0 so it goes back to A
  for(int i = 0; i < num_ver; i++)//initialize tobeChecked to all vertices [A...X]
    toBeChecked[i] = i;

  while(size != 0)
    {
      // v = q.front();//v takes the value of the front value of the queue
      // q.pop();//pop the value
      build_min_heap(toBeChecked, current,  size);//call build_min_heap
      v = getMIN(toBeChecked, current, size);//call getMIN
      
      for(list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)//go through the list u adjacent v
        {
          if(YES(toBeChecked, size, (*u)->neighbor))
            {

              if(current[(*u)->neighbor] > current[v] + (*u)->wt)//check if the current weight is bigger
                {
                  current[(*u)->neighbor] = current[v] + (*u)->wt;//if it is then assign a new weight to it
                  pre[(*u)->neighbor] = v;//predecessor take the value of v
                  build_min_heap(toBeChecked, current, size);
                }

            }
        }

    }
  //After the each vertex gets the minimum distance from the start point and predecessor,
  //Show the information about each vertex and shortest path from origine to destination and total distance.
  //For expected outputs, please check /cs/slott/cs311/graph.out
  cout << "\nShowing the info on each vertex" << endl;
  //?????????
  for(int i = 0; i < num_ver; i++)//go through the arrays current and predecessor
    {
      cout << char('A' + i) << " = " << current[i] << " , " << char(pre[i]+'A') << endl;//display them
    }


  char dest;
  cout << "Enter the destination: ";
  cin >> dest;
  int xyz = int(dest - 'A');

  string path = "";//will have all paths from origine to destination
  stack<int> way;//use a stack

  while(xyz != start)//push all the elements up until we get to the start
    {
      way.push(xyz);//push the given destination
      xyz = pre[xyz];//acess the predecessor of xyz and that will take its place
    }
  way.push(start);//push the element at the start
  while(!way.empty())//will pop all elements out
    {
      path += char(way.top() + 'A');//add the top element to path
      path += string("->");//add arrow
      way.pop();//pop the top element
    }

  cout << "The shortest path from " << char(start + 'A') << " to " << dest << " is " << path << endl;
  cout << "The total distance is " << current[int(dest-'A')] << endl;

  //Don't forget to destroy the dynamic arrays

  delete [] current;
  delete [] pre;
  delete [] toBeChecked;
}

/**********************************************************************
start is the index for the start vertex

This fucntion will find the shortest path the graph can traverse to 
reach its given destination. 
**********************************************************************/
void graph::shortestPath(int start)
{
  //I have 2 dynamic arrays here.
  int* current = new int[num_ver];//current dynamic array
  int* pre = new int[num_ver];//predecessor dynamic array
  
  for(int i = 0; i < num_ver; i++)//intilialize the current array with a large value
    current[i] = 9999;
  int v;//will be used to take queue elements
  int first = start;//take the value of start 
  current[first] = 0;//intilialize current, so the distance from first to first is 0
  //I used a queue for toBeChecked 
  queue<int> q;//make a queue
  q.push(first);//push first into the queue
  
  while(!q.empty())//the queue is not empty 
    {
      v = q.front();//v takes the value of the front value of the queue
      q.pop();//pop the value
      
      for(list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)//go through the list u adjacent v
	{
	  if(current[(*u)->neighbor] > current[v] + (*u)->wt)//check if the current weight is bigger 
	    {
	      current[(*u)->neighbor] = current[v] + (*u)->wt;//if it is then assign a new weight to it 
	      pre[(*u)->neighbor] = v;//predecessor take the value of v 
	    }
	  
	  if(q.empty() || q.front() != (*u)->neighbor)//before we add the neighbor check if the front is not the sam
	    q.push((*u)->neighbor);//push the neighbor of u
	  
	    
	}


    }


  //After the each vertex gets the minimum distance from the start point and predecessor,
  //Show the information about each vertex and shortest path from origine to destination and total distance.
  //For expected outputs, please check /cs/slott/cs311/graph.out
  cout << "\nShowing the info on each vertex" << endl;
  //?????????
  for(int i = 0; i < num_ver; i++)//go through the arrays current and predecessor 
    {
      cout << char('A' + i) << " = " << current[i] << " , " << char(pre[i]+'A') << endl;//display them 
    }
  
  
  char dest;
  cout << "Enter the destination: ";
  cin >> dest;
  int xyz = int(dest - 'A');



  /*
  for(int i = 0; i < num_ver; i++)
    cout <<  char(pre[i]+'A') << " ";
  cout << endl;

  */
  /*
  cout << "this is the path " << endl;
  for(int i = start; i != xyz; xyz = pre[xyz])
    {
      cout <<  char(pre[xyz]+'A') << " ";
      //  xyz = pre[xyz];
    }
  */


  string path = "";//will have all paths from origine to destination
  stack<int> way;//use a stack

  while(xyz != start)//push all the elements up until we get to the start
    {
      way.push(xyz);//push the given destination
      xyz = pre[xyz];//acess the predecessor of xyz and that will take its place
    }
  way.push(start);//push the element at the start 
  while(!way.empty())//will pop all elements out
    {
      path += char(way.top() + 'A');//add the top element to path 
      path += string("->");//add arrow
      way.pop();//pop the top element
    }
  

  cout << "The shortest path from " << char(start + 'A') << " to " << dest << " is " << path << endl;
  cout << "The total distance is " << current[int(dest-'A')] << endl;

  //Don't forget to destroy the dynamic arrays

  delete [] current;
  delete [] pre;
}

#endif
