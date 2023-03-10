/****************
Template created by Kazumi Slott
CS311

Your name: Jared Falcon
Your programmer number: 5
Any difficulties?: ??????
*****************/

#ifndef BST_H
#define BST_H
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

//forward declaration of BST class. We need this because BST class is used as a friend in Node. 
//Check your stack_L_T.h if you don't know what to put here.
template <class T>//?????
class BST;//?????

//Make Node and BST template classes.
//You put the class definition and member function implementations in .h when you use template.  
//If you don't know how to make them template,
//Check page 3 of CS211 "Lec Notes on Exception Handling". I have a template stack class there.
//Also you made stack_L_T.h using template at the beginning of this semester.

template <class T>//???????????  //make it a templare class
class Node
{
  friend class BST<T>;//??????? BST<T>; //BST wants to access private members of Node
private:
  T el;//???? el;
  Node* right;
  Node* left;
public:
  Node() {right = left = NULL;}; //default constructor. set right and left to NULL
  Node(const T& e){el = e; right = NULL; left = NULL;/*????? What do you do here?*/}; 
  T getEl() const {return el;} //returns el
};

//Make it a template class
template <class T>
class BST
{
private:
  Node<T>* root;//???? root; //check stack_L_T.h to see how to declare top

  //You will need 10 private functions here.  WHY private?
  void destroy(Node<T>* p);
  void remove(Node<T>*& p);
  void insertNodeR(Node<T>*& p, const T& e);
  void inOrderPrint(Node<T>* p);
  void preOrderPrint(Node<T>* p);
  void postOrderPrint(Node<T>* p);
  int getMaxLength(Node<T>* p);
  int getMinLength(Node<T>* p);
  int getNumNodes(Node<T>* p);
  int getEvenNodes(Node<T>* p);
  Node<T>* searchR(Node<T>* p, const T& e);

 public:
  BST() {root = NULL;} //implement constructor here
  ~BST(); 
  void BFTprint();
  void DFTprint();
  bool remove(const T& e);
  void insertNodeR(const T& e);
  void insertNodeI(const T& e);
  void inOrderPrint();
  void preOrderPrint();
  void postOrderPrint();
  int getMaxLength();
  int getMinLength();
  int getNumNodes();
  int getEvenNodes();
  Node<T>* searchI(const T& e);
  Node<T>* searchR(const T& e);
};

//implement the member functions in the header if you are making a template class


//destructor.
//If you don't know how to make the destructor, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>//???????? 
BST<T>::~BST()
{
  destroy(root);
}

/*******************************************************************
p is the pointer that points to the root of the tree

This fucntion will destroy all the newly made nodes in the tree.
Its a private function because it needs to have access to the root
which is also private.
 *****************************************************************/
template <class T>//???????
void BST<T>::destroy(Node<T>* p) //private function. WHY?
{
  if(!p)//p==NULL
    return;
  destroy(p->left);//call destroy on the left
  destroy(p->right);//destroy right side
  //  cout << p->el << "-->";
  delete p;
  //destroy all nodes
}
/********************************************************************
This function will print the tree from top to bottom and left to right.
It will use a queue to save the elements in a specific order.
 *******************************************************************/
template <class T>
void BST<T>::BFTprint()  //Breadth First Traversal Print
{
  //Use the library's queue. https://www.google.com/url?client=internal-element-cse&cx=000747561938282180878:lrfgxur\
  //  gbda&q=https://www.cplusplus.com/reference/queue/queue/&sa=U&ved=2ahUKEwimjMj9v-nzAhXDCjQIHXeYDm8QFnoECAUQAQ&usg=AOv \
  //Vaw3vUfDpaPV6Q--9naQsl681

  //Make sure to include <queue> at the top
  //create a queue obj of pointers to Nodes
  queue<Node<T>*> q;//create a queue of node pointers
  q.push(root);//push the first node in the q

  while(!q.empty())//run loop until the q is empty 
   {
     cout << q.front()->el << "->" ;//print element

     if(q.front()->left != NULL)//check the left side of the front elemenet
       q.push(q.front()->left);//push left element

     if(q.front()->right != NULL)//check the right side 
       q.push(q.front()->right);//push left element

     q.pop();//pop the first element 
   }
 //algorithm is discussed in lecture

 //NOTICE
 //front() gives you the front element but it doesn't remove it from the queue.
 //pop() removes the front element
}
/****************************************************
This will print the tree using a stack the same way inorder
is printed. 
 ***************************************************/
template <class T>
void BST<T>::DFTprint()  //Depth First Traversal Print
{
  //sssse library's stack class. https://www.google.com/url?client=internal-element-cse&cx=000747561938282180878:lrf\
  //  gxurgbda&q=https://www.cplusplus.com/reference/stack/stack/&sa=U&ved=2ahUKEwig4bzlwenzAhX1JTQIHWSNDsgQFnoECAYQAQ&usg \
  //=AOvVaw2WzZj1X_p59F2QRf2trcV3

    //Make sure to include <stack> at the top
    //create a stack of pointers to Nodes
 
  stack<Node<T>*> s;//make a stack of pointers
  
  s.push(root);//push the root
  Node<T>* p;//used to save a temporary node

 
  while(!s.empty())//while is not empty
    {
      p = s.top();//p points to the top or root
 
      cout << s.top()->el << "->";//display element
      s.pop();//pop it
      
      if(p->right != NULL)//look in the right 
        s.push(p->right);//push that node
      
      if(p->left != NULL)//look in the left
        s.push(p->left);//push that node second
    }
  
  //top() will give you the top element but it will not remove it from the stack.
  //pop() removes the top element.
}
template <class T>
bool BST<T>::remove(const T& e) //public function
{
  Node<T>* del = root; //del will point to the node to be deleted
  Node<T>* parent = NULL; //parent will point to the parent node of the node to be deletede
  
  //look for e in the tree
  while(del!=NULL && del->el != e) //If root is NULL, del is NULL to start with. While won't be entered and return f \
    //alse down below.
    {
      //parent follows del. In other words, del is ahead of parent. --> you did something similar in insertI()
      parent = del;
      //del will eventually point to the node to be deleted.
      if(e < del->el)
	del = del->left;
      else
        del = del->right;
    }
  
  //e doesn't exist or tree is empty.
  if(del == NULL)
    return false;
  
  //check to see if root should be removed
  if(root->el == e)
    remove(root); //root will change. call the other remove function down below
  //We are deleting a node other than the root node. Figure out if del's node is left or right child of parent's nod \
  // e
  else if(parent->left->el == e) //parent's left child to be removed
    remove(parent->left);
  else //parent's right child to be removed
    remove(parent->right);
  
  //deleted the node with e
  return true;
}

template <class T>
//p coming out of the parent node and points to the node to be deleted OR p points to root node if root node is the \
//one to be deleted.
//p will point to the grandchild (child node of the node to be deleted) if the node to be deleted has only one child\
// or NULL if p is root or the node to be deleted has no children. p will change. That is why we need to use &.

void BST<T>::remove(Node<T>*& p) //private function
{
  Node<T>* temp = p; //temp points to the node to be deleted initially
  Node<T>* t_parent; //t_parent will point to the parent node of temp's node
  
  //the node to be deleted has no right child (Check Diagram1 in the homework document "HMWK BST - BFT, DFT and remo \
  //ve" under "Assignments")
  //If the node to be deleted has no children, the following if will be executed.(Check Diagram2)
  if(p->right == NULL)
    p = p->left; //p(The left or right coming out of parent of del's node) now points to the root of the left subtre \
  //e under del's node. DONE.  If the node to be deleted has no children, p is set to NULL because p->left is NULL.
  //the node to be deleted has no left child (Check Diagram 3)
  else if(p->left == NULL)
    p = p->right;//p(The left or right coming out of parent of del's node) now points to the root of the right subtr \
  //ee under del's node. DONE.
  //If the node to be deleted has 2 children
  else
    {
      //we are going to replace e by the largest value in the left subtree
      temp = p->left; //temp points to the root of the left subtree under the node to be deleted to start with
      t_parent = temp; //t_parent points to the node to be deleted to start with
      
      //go to the largest value in the left subtree under the node to be deleted by going all the way down to right
      while(temp->right != NULL)
        {
          t_parent = temp; //temp is ahead of t_parent
          temp = temp->right; //temp will eventually point to the largest value
        }
      //copy the largest value into the node to be deleted
      //      ????????????;
      p->el = temp->el;

      if(p->left == temp) //the largest value is the direct left child of the node whose value was replaced b
	p->left = temp->left;
      else
	t_parent->right = temp->left;      
    }
  delete temp;
}

//If you don't know how to make the insert function using recursion, check the following.
//CS211 Lecture Notes on BST ??? insertNode
//CS211 Lecture recording - Lecture 4/26(Mon) - DLL::deleteFront, BST::insert(), search()

//public function to call insertNode()
template <class T>//??????
void BST<T>::insertNodeR(const T& e)
{
  insertNodeR(root, e);
}

/*************************************************************
p is the pointer that points to the root of the tree
e is the new element to be inserted 

This function will insert a new node into the binary tree.
Its a private function because it needs to have access to the root
which is also private.
 ************************************************************/
template <class T>
void BST<T>::insertNodeR(Node<T>*& p, const T& e) //private function. WHY?
{
  if(!p)//p==NULL
    p = new Node<T>(e);//make new node if p == NULL
  else if(e > p->el)//element is bigger
    insertNodeR(p->right, e);//go right and check again since its the element is bigger
  else
    insertNodeR(p->left, e);//go left if the element is smaller
}



//This is an insert function using iteration.
//You will see insert function using iteration is unwieldy compared to that using recursion above.
//The hemework document "HMWK BST - reveiw of cs211" has a diagram to show how this function works.
/*****************************************************************
e is the new element to be inserted

This function will insert a new node using iteration. It will check 
where the nodes should be inserted.
 ****************************************************************/
template <class T>
void BST<T>::insertNodeI(const T& e)
{
  Node<T>* newNode = new Node<T>(e);//make a new node.  Check stack_L_T.h to see how you made a new node.
  Node<T>* p = root;//p starts at root
  Node<T>* parent = NULL; //points to the parent of p. 

  //move p to NULL
  while(p != NULL)
    {
      //parent points to the parent node while p points to the left or right child.
      parent = p; //make parent point to p
      if(e < p->el) //if element is smaller than the current node
	p = p->left; //advance p to the left side
      else //p->el <= e
	p = p->right;//advance p to the right side
    }

  if(parent == NULL) //tree is empty
    root = newNode;//make the new node the root 
  else if(e < parent->el) //insert a child as the parent's left child
    parent->left = newNode;//parent left now points to newly added node
  else //parent->el <= e //insert a child as the parent's left child
    parent->right = newNode;//parent right now points to newly added node
}


//If you don't how to make this, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

//public function
template <class T>
void BST<T>::inOrderPrint()
{
  return inOrderPrint(root);
}
/****************************************************************
p is the pointer that points to the root of the tree

This function will print the tree in order which is the root in 
the middle.Its a private function because it needs to have access to the root
which is also private.
 ***************************************************************/
template <class T> //private function. WHY?
void BST<T>::inOrderPrint(Node<T>* p)
{
  if(!p)//p == NULL
    return;
  inOrderPrint(p->left);//print left side of the tree first
  cout << p->el << "-->";
  inOrderPrint(p->right);//print right side of the tree second
}


//public function
template <class T>
void BST<T>::preOrderPrint()
{
  //pre means print parent->left child ->right child
  return preOrderPrint(root);
}
/*****************************************************************
p is the pointer that points to the root of the tree

This function will print the tree pre order which is the root in
the front.Its a private function because it needs to have access to the root
which is also private.
 *****************************************************************/
template <class T>
void BST<T>::preOrderPrint(Node<T>* p) //private function. WHY?
{
  if(!p)//p == NULL
    return;
  cout << p->el << "-->";//print root first
  preOrderPrint(p->left);//left side second
  preOrderPrint(p->right);//right side third
}

//public function
template <class T>
void BST<T>::postOrderPrint()
{
  //post means left->right->parent last
  return postOrderPrint(root);
}
/**************************************************************
p is the pointer that points to the root of the tree

This function will print the tree post order which is the root in
the end.Its a private function because it needs to have access to the root
which is also private.
 *************************************************************/
template <class T>
void BST<T>::postOrderPrint(Node<T>* p) //private function. WHY?
{
  if(!p)//p == NULL
    return;
  postOrderPrint(p->left);//left side first
  postOrderPrint(p->right);//right side second
  cout << p->el << "-->";//root first
}



//If you don't know how to make this, check the following
//Lec Notes on BST :: Recursive Functions ??? getNumNodes
//CS211 Lecture recording - Lecture 4/30(Fri) - BST::getNumNodes, phase 3 of college

//public function
template <class T>
int BST<T>::getNumNodes()
{
  return getNumNodes(root);
}

/*********************************************************
p is the pointer that points to the root of the tree

This function will return the total amount of nodes in the tree.
Its a private function because it needs to have access to the root
which is also private.
 ********************************************************/
template <class T>
int BST<T>::getNumNodes(Node<T>* p) //private function WHY?
{
  if(!p)//p == NULL
    return 0;//theres node nodes
  return getNumNodes(p->left) + getNumNodes(p->right) + 1;//add the left and the right side and the root
}



//This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int BST<T>::getMaxLength()
{
  return getMaxLength(root);
}

/**********************************************************
p is the pointer that points to the root of the tree

This function will return the max length of nodes in the tree.
Its a private function because it needs to have access to the root
which is also private.
 *********************************************************/
template <class T>
int BST<T>::getMaxLength(Node<T>* p) //private function. Why?
{
  int left;//stores the left sided nodes
  int right;//stores right nodes

  if(!p)//p==NULL
    return 0;//no nodes
  if(p->left == NULL && p->right == NULL)//the root left and right are NULL
    return 1;//the only node is the root
  
  left = getMaxLength(p->left) + 1;//count the nodes on the left and add 1 for the root
  right = getMaxLength(p->right) + 1; //count the nodes on the right and add 1 for the root
  if(left >= right)//compare the left and right side, return whatever is bigger
    return left;
  else
    return right;
}


//public function
template <class T>
int BST<T>::getMinLength()
{
  return getMinLength(root);
}
/************************************************************
p is the pointer that points to the root of the tree

This function will return the minimum length of nodes in a row.
Its a private function because it needs to have access to the root
which is also private.
 ***********************************************************/
template <class T>
int BST<T>::getMinLength(Node<T>* p) //private function. WHY?
{
  int left;//stores the left sided nodes
  int right;//stores right nodes

  if(!p)//p==NULL
    return 0;//no nodes
  if(p->left == NULL && p->right == NULL)///the root left and right are NULL
    return 1;//the only node is the root

  left = getMinLength(p->left) + 1;//count the nodes on the left and add 1 for the root
  right = getMinLength(p->right) + 1; //count the nodes on the right and add 1 for the root
  if(left <= right)//compare the left and right side, return whatever is smaller
    return left;
  else
    return right;

}
                                                                                                    
//This function will return the number of even elements
template <class T>                                                                                    
int BST<T>::getEvenNodes()                                                                            
{                                                                                                     
  return getEvenNodes(root);
}                                                                                                     

/****************************************************************
p is the pointer that points to the root of the tree

This function will return the even amount of nodes in the tree.
Its a private function because it needs to have access to the root
which is also private.
 ***************************************************************/                  
template <class T>                                                                                    
int BST<T>::getEvenNodes(Node<T>* p) //private function. WHY?                                              
{                                                                                                     
  int even = 0;//initialize even to 0
  
  if(p)//p != NULL
    {
      even = getEvenNodes(p->left) + getEvenNodes(p->right);//call left and right side into even 
      if(p->el % 2 == 0)//check if they are even nodes
	even++;//increment even
    }
  
  return even;//return result
}                                                                                                     




//Make a search function using iteration. Return the pointer to the node having e
//return NULL if e is not found.
//return the pointer to the node with e
//return NULL if e is not found
/*************************************************************
e is the element we want to find 

This function will search for the given element in the tree 
using iteration. Its a private function because it needs to have access to the root
which is also private.
 ************************************************************/
template <class T>
Node<T>* BST<T>::searchI(const T& e)
{
  Node<T>* p = root;//start p at the root

  while(p)//p != NULL
    {
      if(p->el == e)//if the node pointed to by p is == to e return it
	return p;//returns the pointer 
      else if(p->el > e)//if the given element is smaller, search the left side
	p = p->left;//advance p the left side of the tree
      else//given element is bigger, search right side
	p = p->right;//advvance p to the right side 
    }
  return NULL;//element was not found, return NULL

  // Where do you return NULL?  

}



//Make a search function using recursion.
//Return the pointer to the node having e or return NULL if e is not found.
template <class T>
Node<T>* BST<T>::searchR(const T& e)
{
  return searchR(root, e);
}

/*************************************************************
p is the pointer that points to the root of the tree
e is the element we are searching for

This function will search for the given element using recursion.
Its a private function because it needs to have access to the root
which is also private.
 ************************************************************/
template <class T>
Node<T>* BST<T>::searchR(Node<T>* p, const T& e) //private function. WHY?
{
  if(p == NULL)//there are no nodes
    return NULL;
  if(p->el == e)//element is found
    return p;//return pointer
  else if(p->el > e)//given element is smaller
    return searchR(p->left, e);//search left side
  else//given element is bigger
    return searchR(p->right, e);//search right side
  // return NULL;
}


#endif
