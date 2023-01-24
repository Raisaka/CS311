/************************
Templated created by Kazumi Slott
CS311

Your name: Jared
Your programmer number: 5
Any difficulties?: remove function was challenging 
*********************/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

//unsigned for positive numbers or zero only. long takes up 4 bytes. 0-2^32(4294967295)
unsigned long hashNum(const string& key);

class entry //this is basically a node
{
  //What do you do if hashTbl needs to access the private members of entry?
  //If you don't say private or public, it is private by default.
  friend class hashTbl;//make hashTbl a friend to access variables

  string ID;
  string name;
  int age;
  double GPA;
  entry* next; //points to the next entry

public:
  entry()
  { 
    ID = name = "", age = -999, GPA = -999.0, next = NULL; 
  }
  entry(const string& ID, const string& name, int age, double GPA )
  { 
    this->ID = ID, this->name = name, this->age = age, this->GPA = GPA, next = NULL;
  }
  string getID() const { return ID; }
  string getName() const { return name; }
  int getAge() const{ return age; }
  double getGPA() const { return GPA; }
  entry* getNext() const{ return next; }
};

class hashTbl
{
  entry** table;   //table points to a dynamic array. Each slot points to an entry, which points to the next entry, ...
  int size; //size of the array
public:
  hashTbl(int size);
  ~hashTbl();
  void put(entry* e); //add a new entry to the table
  entry* get(const string& key) const; //look up a key
  entry remove(const string& key); //remove an entry
  entry** getTbl() const {return table;} //return the pointer to the table
  class underflow //exception class - used when key wasn't found
  {
    string message;
  public:
    underflow(const string& mes) { message = mes; }
    string getMessage() { return message; }
  };
};

/*************************************************************
//constructor
//s is the size of the table
This is the constructor to initialize s and add a new entry
in very slot of the table. It will have to add NULLL to every 
slot at the start.
*************************************************************/
hashTbl::hashTbl(int s)
{
  //set private member size
  size = s;//set size
  //make a dynamic array that has s slots
  //put NULL in each slot of the array. Remember Each slot contains a pointer to an entry.
  table = new entry*[s];//make new entry array
  
  for(int i = 0; i < s; i++)//go through the table and insert 
    {
      table[i] = NULL;//insert NULL in every slot with the index starting at 0
    }
}

//destructor
/*************************************************************
This is the destructor so we can delete all the new data that 
was made. That also includes the dynamic array.
 ************************************************************/
hashTbl::~hashTbl()
{
  //you need to destroy everything created using new.
  //destroy all the entries belong to each slot of the table
  //don't forget to destroy the dynamic array
  entry* temp;//make entry pointer
  entry* del;//make delete pointer
  for(int i = 0; i < size; i++)//for loop to go through each slot 
    {
      temp = table[i];//make the entry pointer point to the first table index----table[0]
      while(temp != NULL)//go trough each node in the slot until there are none
	{
	  del = temp;//make del point to the same entry as temp
	  temp = temp->next;//advance temp
	  delete del;//delete the node
	}
      
    }
  del = NULL;//make del point to NULL
  temp = NULL;//make entry temp point to NULL
  delete [] table;//destroy the table
}
/*************************************************************
//insert an entry to the table
//e is a pointer to an entry

This function will put a take a new entry in its given table index.
*************************************************************/
void hashTbl::put(entry* e)
{
  //This function is like LL::addFront() from CS211

  //string key = use ID for key 
  string key = e->getID();//get the ID for key
  int index = hashNum(key) % size;//calculate the index by calling hashNum 
  entry* cur = table[index];//make cur point to the corresponding table index

  //add the entry at the beginning of the list coming out of index	
  if(table[index] == NULL)//if the first slot in table is NULL
    {
      table[index] = e;//add the new entry to the first slot
      e->next = NULL;//make its next point to NULL
    }
  else//otherwise there is already at least one node 
    {
      table[index] = e;//make the new entry be the first entry
      e->next = cur;//connect the new entry with the second entry
    }
}
/********************************************************************
//look up key and return the pointer to it. Assume keys are unique.

This function will return the pointer pointing to the key if it was
found. Otherwise we would throw an underflow.
********************************************************************/
entry* hashTbl::get(const string& key) const
{
  //This function is like LL::search() from CS211

  int index = hashNum(key) % size;//calculate the index by calling hashNum
  entry* cur = table[index];//make cur point to the corresponding table index

  if(cur == NULL)//if the table index is NULL
      throw underflow(key);

  while(cur != NULL)//while loop so we go through the nodes
    {
      if(cur->getID() == key)//if we find the key in the linked list
	return cur;//return the pointer to the key 
      cur = cur->next;//advance cur to the next node
    }
  // return cur;
  if(cur == NULL)//if we didnt find the key, cur will be NULL so throw underflow 
    throw underflow(key);

  //look for key in the linked list. Return the pointer to the entry with key.
}
/**********************************************************************
//remove the entry with key. Assume keys are unique.

This function will remove an entry from the table and return it. It will 
throw an exception if the slot for the ID is empty. It will also throw
an exception if we traversed the list and it wasnt found. It will have 
a condition of the key is found in the first node. It will also throw an
exception if the key was not found in the list. 
**********************************************************************/
entry hashTbl::remove(const string& key)
{
  //This function is like LL::remove() from CS211
 
  int index = hashNum(key) % size;//calculate index using hashNum
  entry* cur = table[index];//make cur point to the first slot
  entry* prev = NULL;//set a new pointer to NULL
  entry hi;//used to save our returning object
  //mimic put and get

  if (cur == NULL /*the slot is empty*/)
    throw underflow(key);
  /*    
  if(get(key) == NULL)
    throw underflow(key);
  */
  if(cur == get(key))//if the key is found in the first slot
    {
      prev = cur->next;//make prev point to the next node
      table[index] = prev;//the first slot is now the second node
      hi = *cur;//save the first object pointed by cur and dereference cur so we can return the object
      delete cur;//delete the node pointed to by cur
      return hi;//return the object stored in high
    }
  
  while(cur->next != get(key))//this will go through the list and stop when cur->next is the key  
    {
      prev = cur;//make prev point to cur
      cur = cur->next;//advance cur to the next node
    }
  if(cur == NULL/*traversed the list, but didn't find key*/)
    throw underflow(key);

  prev = cur->next;//make prev point to the next node
  cur->next = prev->next;//make cur next point to the node after prev
  hi = *prev;//save the object into a temp object
  delete prev;//delete the node pointed to by prev
  return hi;//return the object
  
 //return the entry found

}

//well known hash function called djb2
//http://www.cse.yorku.ca/~oz/hash.html
//For explanation of bit shifting, http://www.cplusplus.com/forum/beginner/95670/
//unsigned for positive numbers or zero only. long takes up 4 bytes. 0-2^32(4294967295)
unsigned long hashNum(const string& key)
{
  const char* cstr = key.c_str(); //converting C++ string to c-string. A c-string is a character array that is terminated by a '\0' (NULL terminator).
  
  unsigned long hash = 5381;
  int c;
  while (c = *cstr++) //checking each character until it reaches '\0'. When it reaches '\0', c gets the ascii number of '\0', which is 0. 0 means false -> getting out of while.
    {
      hash = ((hash << 5) + hash) + c;//hash * 33 + c;
    }
  return hash;
}

void showInfo(const entry& e);
void showTable(const int count[], const hashTbl& students);


const int SIZE = 1327; //prime number for a table size

int main()
{
  //make a hash table object with SIZE slots 
  hashTbl students(SIZE);
  //put entries into the table
 
  int count[SIZE] = {0}; //set all slots to 0. Used to see count in each index                                                                      

  ifstream fin;
  fin.open("hash.in");
  string id;
  string name;
  int age;
  double gpa;

  //adding entries from the input file
  fin >> id >> name >> age >> gpa;
  while(fin)
    {
      count[hashNum(id)%SIZE]++;//trying to see how many entries go into each slot
      students.put(new entry(id, name, age, gpa));
      fin >> id >> name >> age >> gpa;
    }

  //show the statistic about the table
  showTable(count, students);

  //##
  //put entries into the table
  //students.put(new entry("T1234567891", "Tom", 23, 4.0));
  //students.put(new entry("F5432112345", "Fred", 45, 3.5));
  //students.put(new entry("L1357915987", "Linsey", 48, 2.0));

  //searches and returns students in table without removing                                                                     
  try
    {
      cout << "trying to search" << endl;
      showInfo(*(students.get("P1429911332")));//middle at index 377                                                            
      showInfo(*(students.get("Y1098431884"))); //first entry at index 377                                                      
      showInfo(*(students.get("V1025438181"))); //last entry at index 377                                                       
      showInfo(*(students.get("A1234567891"))); //probably doesn't exist                                                        
      //search for key and show their info                                                                                      
    }
  catch (hashTbl::underflow obj)
    {
      cout << "Student with ID: " << obj.getMessage() << " could not be found" << endl;
    }

  //Try to remove a student from table                                                                                   
  cout << endl;
  try                                                                                                                           
    {
      cout << "trying to remove" << endl;
      showInfo((students.remove("P1429911332"))); //3rd entry at index 377                                                      
      showInfo((students.remove("V1025438181"))); //last entry(now 4th) at index 377                                            
      showInfo((students.remove("Y1098431884"))); //first entry at index 377                                                    
      showInfo((students.remove("A1234567891"))); //probably it doesn't exist                                                   
    }
  catch (hashTbl::underflow obj)
    {
      cout << "Student with ID: " << obj.getMessage() << " could not be removed" << endl;
    }


  //Try to remove a student from table
  //use try-catch

  return 0;
}
//Show the information about an entry
void showInfo(const entry& e)
{
  cout << e.getID() << " " << e.getName() << " " << e.getAge() << " " << e.getGPA() <<  endl;
}

//##
//Show the statistic about the hash table
void showTable(const int count[], const hashTbl& students)
{
  //we want to know the highest, lowest and empty counts
  int lowest = 1001;
  int highest = -1;
  int empty = 0;
  int hi_i; //index of the highest count

  cout << "print table" << endl;
  for(int i = 0; i < SIZE; i++)
    {
      if(count[i] < lowest)
        lowest = count[i];
      if(count[i] > highest)
	{
	  highest = count[i];
	  hi_i = i;
	}
      if(count[i] == 0)
        empty++;

      cout << setw(3) << count[i];
      if((i+1)%50 == 0)//Show 50 numbers per line
        cout << endl;
    }
  cout << endl << endl << "lowest is " << lowest << " highest is " << highest << " empty is " << empty << endl;

  cout << "highest count is at " << hi_i << endl;
  //Show the entries at the index that has the highest count
  entry* p = students.getTbl()[hi_i];
  while(p != NULL)
    {
      showInfo(*p);
      p = p->getNext();
    }
  cout << endl;

}
