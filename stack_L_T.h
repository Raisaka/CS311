/***********************************
This program will be able to implemnet a stack using a linked list
it will be able to use various functions such as push(), pop(), getSize(), getTop()
and later on will be updated to have a copy function. It also has a few operator overloading functions, one
of them being an ostream<< operator overloading function that will be able to print the whole stack at once. 
 
Template created by Kazumi Slott
CS311
Stack implemented with a LL

Your name here: Jared Falcon
Your programmer number here: 5
******************************************************************************************************************/
#ifndef STACK_L_T_H
#define STACK_L_T_H

#include <iostream> 
using namespace std;

template < class T > //forward declaration needed so we can make stack class a friend of node
class Stack;

template < class T > //forward declaration needed so we can make operator<< a friend of node and Stack
ostream& operator<<(ostream& o, const Stack<T>& s);


template <class T>
class Node
{
  friend class Stack<T>; //Stack class accesses the private members of Node
  friend ostream& operator<< <T>(ostream& o, const Stack<T>& s); //operator<< accesses the private members of Node
  
 private:
  T elem;//make the elemenet any data type
  Node<T>* next;//node pointer that points to the next node

 public:
  Node(){next = NULL;} //default constructor
  Node(const T& e){e = next; e = elem ;}//constructor for a node
};

template <class T>
class Stack
{
  friend ostream& operator<< <T>(ostream& o, const Stack& s); //operator<< accesses the private members of Stack

 private:
  Node<T>* top;//node pointer that will point to the top element in the stack 
  int size;//size of the stack

 //helper functions - private because they won't be called from client
  void destroy();
  void copy(const Stack& source);

 public:
  Stack() {top = NULL; size = 0;} //Implement a small function inside the class definition 
  Stack(const Stack& other);
  ~Stack();
  Stack& operator=(const Stack& rhs); //rhs = right hand side of the operator   LHS_obj = RHS_obj
  bool empty() const{return (top == NULL && size == 0);} //implement a small function inside the class definition
  int getSize() const{return size;} //implement here
  void push (const T& val);
  void pop();
  T& getTop(); //Return type is T& so client can change the top value
  const T& getTop() const; //A const object needs to call a const member function

  //Make an exception class here - You need to figure out where to throw an exception - I am throwing in 3 functions.
  class Underflow{};//class underflow for exception handling 

  //??????????
};

/******************************************************************
This function will be able push a new node onto the stack while moving
the top pointer to the newly added node

val is for the value we want to have the new added node to have 
 ******************************************************************/
template <class T>
void Stack<T>::push(const T& val)
{
  
  Node<T>* temp = new Node<T>;//make temp pointer that point to newly created node
  temp->elem = val;//assign value to temp node
  
  temp->next = top;//temp->next points down to the node below which is top 

  top = temp; //move top to the newly created node
  size++;//increment size of stack
  //  cout << "here" << endl;


//FYI, I have 4 lines of code here. You may have less or more.
}


/*******************************************************************
This fucntion should be able to delete/pop and element/node from the 
stack and will use underflow to keep the program from aborting if 
we try to delete from an empty stack.

no parameters 
 ******************************************************************/
template <class T>
void Stack<T>::pop()
{
  if(empty())//check if stack is empty
    throw Underflow();//throw underflow so the program doesnt abort 
  else//otherwise delete node
    {
      Node<T>* temp = top;//create temp pointer that point to the top element
      top = top->next;//move top to the node below 
      temp->next = NULL;//make the node that will be deleted point to NULL
      delete temp;//delete it
      size--;//decrement size
    }
  
}


/*************************************************
This fucntion will return the top element of the
stack. Since its return type is passed by reference 
it can be changed in main

returns the top element 
 *************************************************/
template <class T>
T& Stack<T>::getTop()
{
  //cout << "Here top" << endl;
  if(empty())
    throw Underflow();
  else
    return top->elem; //return the top element. Since the return type is T&, the client can change the top.
}



/***************************************************
This fucntion is the same as the one above but this 
fucntion is exclusively for constant members fucntions
It is only allowed to be called by const functions and
the value cannot be changed like the function above.

returns const top element
***************************************************/
template <class T>
const T& Stack<T>::getTop() const
{
  if(empty())//check if the stack is empty
    throw Underflow();//throw undeflow to be caught in main

  return top->elem; // same as the getTop() above. We need to provide this so a const object can call getTop(). Recall a const object can only call const member functions.
}




//This function will show all the elements in the stack in the following format.
//cout << stackObj; <== This cout is calling the following function.   
//     --- Top ---
//     2
//     1
//     --- Bottom ---
/*************************************************************
This operator overloading fucntion will be able to print a 
the whole stack using ostream.

o is the ostream object we are returning 
s is the stack we want to display 
returns ostream o object to print stack 
 ************************************************************/
template <class T>
ostream& operator<<(ostream& o, const Stack<T>& s)
{
  //print from top to bottom.

  cout << "--- Top ---" << endl;
  Node<T>* temp = s.top; //temp node pointer to point to the top of the stack 
  while(temp)//(temp != NULL)//while temp does not point to NULL got through the stack
    {
      o << temp->elem << endl;//add elemenet to the stream object, so it can be printed
      temp = temp->next;//move to the node below
    }
  cout << "--- Bottom ---" << endl;
  return o;//return the ostream object 
}


/*****************************************************
Destructor function that will destory the nodes at the
end of the program 
 *****************************************************/
template <class T>
Stack<T>::~Stack()
{
  destroy();//call destroy function 
}


//helper function - called from destructor and operator=
/*********************************************************
This function will pop/delete all the nodes in the stack
until the stack is empty
 ********************************************************/
template<class T>
void Stack<T>::destroy() //This function will be called by destructor and operator=
{
  while(!empty())//check if its empty, if not empty go through the stack
    {
      pop();//call pop function to destroy the nodes 
    }      
  //destroy all nodes
  //?????????????? 
}



/***************************************************
This fucntion will allow us to ovverload the = operator
when we want to compare/assign objects to each other.
This operator allows us to deep copy our stack object
instead of making a shallow copy.

const Stack rhs is the stack we want to copy from or 
compare. Its const becuase we dont want to change it.
***************************************************/
template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) //rhs = right hand side of the operator
{
  //good reading from cal tech
  //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html

  //deep copy
  if(this != &rhs) //Check the addresses of the left and right objects. If they are the same, you are trying to assign the same object   s = s;
              //You copy only if the left object is not the same as the right object.
    {
      this->destroy();//call this->destroy to empty our ddestination stack
      copy(rhs);//call copy to copy the right hand stack
      //destroy any memory space "this" is using. "this" may have elements already. call destroy
      //call copy
    }
  return *this; //return the "this" object 
}


/***************************************************
This function will copy every element from the source
stack to this(new) stack. This has to be done by making 
completly new nodes for the new stack. 

source is the stack we want to copy the elements from
***************************************************/
//helper fuction. called from operator= and copy constructor
template <class T>
void Stack<T>::copy(const Stack& source) //source is the stack object copied from. 
{
  if(source.empty())//check to see if its empty
    return;//just return and do nothing
 
  Node<T>* temp;//make a temp pointer
 
  int size = source.size; //assign source size to variable size to use for our loop
  int y;//y vvariable to be used for size and how many times our second loop runs
  while(size > 0)//check while the size is bigger than 0
    {
      y = size;//assign size to y so we can loop the second loop a certain amount of times
      temp = source.top;//resets the temp pointer to the top of the sttack
      for(y; y-1 > 0; y--)//this loop will helps us advance temp to the next node a certain amount of times
	temp = temp->next;//advances temp to the next node
      push(temp->elem);//push the element
      size--;//decrement our whille loop counter for size

    }
}


/***************************************************
This fucntion sets the data members of this to their
default values before assign or copying values from 
another stack.

other is the other stack we want to copy from
***************************************************/
//copy constructor
template <class T>
Stack<T>::Stack(const Stack& other)
{
  //This is a copy constructor. This new object will get the same values as the other object. 
  //You still need to initialize the data members.
  //  ???????
  // ???????
  this->top = NULL;//initialze this->top to NULL
  this->size = 0;//size to 0 to get us started with a new stack object
  
//Then you can call the copy function
  copy(other);
}

#endif // end the definition here
