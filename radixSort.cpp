/************************************
Template created by Kazumi Slott
CS311
Homework on radix sort

Description of this program: This program will be implementing radix sort using bucket sort with an array.
It will be using a linked list as well. It will sort sort items into an array with linked lists. 
Your name: Jared Falcon
Your programmer number: 5
Any difficulties?: radix sort itself was a bit confusing at first, I think I was overcomplicating it. 
************************************/

#include <iostream>
#include <fstream>

using namespace std;

const int LEN = 3; //the length of words
const int ALPHABET = 26; //total number of letters

class Node
{
  friend class LL;
private:
  string el;
  Node* next;
public:
  Node(const string& s){el = s; next = NULL;}
  string getElem() const {return el;}
};

class LL
{
private:
  Node* front;
  Node* rear;
  int num;
public:
  LL(){front = rear = NULL; num = 0;}
  ~LL();
  bool empty()const{return (front == NULL && rear == NULL && num == 0);}
  void addRear(const string& s);
  void addRear(Node* p);
  void append(const LL& other);
  void clear(){front = rear = NULL; num = 0;}
  Node* begin() const{return front;}
  Node* goToNext(Node* curr) const{return curr->next;}
  int size() const{return num;}
};

LL::~LL()
{
  cout << "destructor is called" << endl;
  Node* p = front;
  while(!empty())
    {
      front = front->next;
      delete p;
      p = front;
      if(front == NULL)
	rear = NULL;
      num--;
    }
}

//add a new node at the end of this list. The element of the new node is s.
void LL::addRear(const string& s)
{
  //This function is just like what you made in LL class from CS211.
  Node* p = new Node(s);

  if(empty())
    front = rear = p;
  else
    {
      rear->next = p;
      rear = rear->next;
    }    
  num++;
}

//Implementing this function
//add the node pointed to by p (p points to one of the nodes in all list) at the end of this list
/****************************************************************
p is the new node that already exits 

This function will add an existing node to a list of nodes at the 
end of the linked list.
 ****************************************************************/
void LL::addRear(Node* p)
{
  //Don't make a new node.
  //You need a special case when the list is empty
  if(empty())// checl if empty
    {
      front = rear = p;//if its the only node, make that the front and rear node
      
      // return;
    }
  else//otherwise
    {
      rear->next = p;//connect p to the list
      rear = rear->next;//rear is now pointing to p
      // num++;
    }
  num++;//incremenet size of list
  //you don't need to place NULL in the next field of the rear node of this list.
  //don't forget to increment num
  //Note: this function should have complexity O(1). There is no loop required. 
}

//Implement this function
//appending another linked list at the end of this linked list
/****************************************************************************
other is the list we want to connect

This fucntion will add two linked lists together. It will make "other" be at 
the end of the linked list if we have a list already. Otherwise it will become
the main list.
 ***************************************************************************/ 
void LL::append(const LL& other)
{
  //Don't forget to update num of this list
  if(!empty())//if not empty
    {
      this->rear->next = other.front;//connect the rear to the front of other list
      this->rear = other.rear;//make the end of other list the end of both lists combined
      this->rear->next = NULL; //make rear next point to NULL
    }
  else//otherwise its the only list
    {
      this->front = other.front;//make this front point the front of other
      this->rear = other.rear;//make the end of other list the end of both lists combined
      this->rear->next = NULL;//make rear next point to NULL
    }
  this->num += other.num;

  //close the end of this list by putting NULL in the next field of the rear node

  //Note: this function should have complexity O(1). There is no loop required. 
}

void radixSort(LL& all);
void makeLL(LL& all, const string a[], int n);
void printLL(const LL& l);
void checkBuckets(const LL buckets[], int n);
void combineLists(LL& all, LL buckets[]);
void makeLL(LL& all);

int main()
{
  LL all; //holds all words
  makeLL(all); //all contains strings in the original order
  radixSort(all);
  cout << "Final result ----" << endl;
  printLL(all); //all contains strings in sorted sorter
  cout << endl;

  return 0;
}

//Implement this function
//using the radix sort algorithm to sort strings that contain lowercase letters. 
/**********************************************************************
all is the linked list of all elements

This fucntion will implement radix sort by using an array of linked lists.
It will organize the list 3 times because thats the amount of letters we 
are dealing with. It will send the words into buckets of an array based on
the letter iteration we are in at the time. It moves from the back to the front
m a p this means it will take p first put it in the p bucket and then again, but
now with the a bucket and again with the m bucket. Once all letters have been
read it will create a final sorted list.
 *********************************************************************/
void radixSort(LL& all)
{
  //Each slot of the buckets array is a LL object.
  LL buckets[ALPHABET]; //bucket[0] is for 'a'. There are 26 buckets.   
  int x;//stores our letter element number
  int j;//used to iterate through the list
  Node* p;//p pointer to move through the nodes
  int index = LEN;//stores LEN 
  //checking each place
  for(int i = index-1; i >= 0; i--)//for loop to iterate a certain amount of times for the length of the words
    {
      for(j = 0, p = all.begin(); j < all.size(); j++, p = all.goToNext(p))//moves through the lists	
	{
	  x = p->getElem()[i] - 'a';//add the number from the letter to x
	  buckets[x].addRear(p);//x is not accessing the bucket at that number(letter)
	}
      combineLists(all, buckets);//call combine lists
    }
  //To go through each string in all list, check printLL() to see how to iterate
  //go to the correct bucket depending on the letter at the current place and add the node from the all list at the end of the bucket 
}

//Implement this function
//combining all lists from buckets
/*********************************************************************
all is the linked list with all words
buckets is the array with linked lists

This function will go through all the buckets with linked lists and 
add them together so we can make our final list.
 ********************************************************************/
void combineLists(LL& all, LL buckets[])
{
  //???????  //call clear() to reset the all list. All the nodes went to correct buckets already.
  all.clear();//call clear
  //populate the all list by combining the lists from the buckets by calling append()
  int x = 0;//will increment to match 
  while(x < ALPHABET)//x will go up to index 25
    {
      if(!buckets[x].empty())//check if the bucket is empty
	{
	  all.append(buckets[x]);//add the list into the main list using append
	  buckets[x].clear();//clear that bucket
	}
      x++;//increment x 
    }
  //???????  //reset each list in b[i] by calling clear(). All the nodes were moved to the all list already.
}

//Make a linked list of words from an input file  
void makeLL(LL& all)
{
  string s;  
  fstream fin;
  fin.open("radix.in");

  fin >> s;
  while(fin)
    {
      all.addRear(s);
      fin >> s;
    }
}

//This function shows the contents of all the buckets
void checkBuckets(const LL buckets[], int n)
{
  for(int i = 0; i < n; i++)
    {
      cout << i << ": ";
      printLL(buckets[i]);
      cout << endl;
    }
}

//This function prints all the elements in l
void printLL(const LL& l)
{
  int i;
  Node* p;

  //iterate l from the first node to last node
  for (i = 0, p = l.begin(); i < l.size(); i++, p = l.goToNext(p))
    cout << p->getElem() << ' ';
}

