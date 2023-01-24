/*****************************************
Template written by Kazumi Slott
CS311

Your name: Jared Falcon
Your programmer number: 5
Any difficulties?: My build_max_heap function wasnt working properly because I had the parent indexes wrong
i had 2 / n - 1 instead of n / 2 - 1 and was messing everything up. 
*******************************************/
#include <iostream>
using namespace std;

//print an integer array of size n
void print(int ar[], int n)
{
  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
  cout << endl;
}

//called from max_heapify and heapSort
/*************************************************
x value to be swapped
y value to be swapped

Helper function for swapping elements 
 ************************************************/
void exchange(int &x, int &y)
{
  //I have 3 lines of code here.
  int temp = x;//put the x in temp
  x = y;//put y in x now
  y = temp;// put temp(x) in y

}

//turn a heap into a max-heap rooted at i, assuming the left and right subtrees are already max-heaps.
//n is the size of the heap
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
void max_heapify(int ar[], int n, int i)
{
  
  int L = 2*i + 1; //the index of the left child of i
  int R = 2*i + 2; //the index of the right child of i
  int largest;//stores largest index

  //look for the largest among 3 elements at i, l and r. largest gets the index of the largest value.
  //Make sure l and r don't go over the heap's range. 
  //Recall how you found the largest value among 3 values in CS111.
  //???????? //I have 6 lines of code here. You can have more or less.
  largest = i;//make parent index largest index first 
  if(L < n && ar[L] > ar[largest])//compare with left child and keep range 
    largest = L;//if left child is bigger, it now becomes largest and takes its index
  if(R < n && ar[R] > ar[largest])//compare with right child and keep range
    largest = R;//if right child is bigger, it now becomes largest and takes its index
  

  //The largest is either the right or left child. In other words, it is not the root at i.
  if(largest != i)//only enter if largest is not parent ( i )
    {
      //exchange the 2 values
      exchange(ar[i], ar[largest]);//switch values parent and child
      //There might be a violation at the position that was exchanged. Call max_heapify to fix it.
      max_heapify(ar, n, largest);//make sure to correct it again if needed for lower children if any
    }
 
}


//turn the entire array/tree into a max heap rooted at 0
//n is the size of the array
/*************************************************************
ar is the heap array
n is the size of the array

This helper function will be able to create or fix any violations
in a heap array. It will find the parent indexes in the array and
call the function max_heap and work its way up visiting every 
parent. It will correct any violations of max heap all the way 
up to the root.
**************************************************************/
void build_max_heap(int ar[], int n)
{
  //2 lines of code in this function
  
  for(int i = n / 2 - 1; i >= 0; i--)//find the last parent and work your way up 
    max_heapify(ar, n, i);//call max heap on each parent index
	     //call max_heapify (turn the smallest subtrees into max-heaps and work your way up)
  
}
/******************************************************************
//a is an unordered list to start with
//use max_heapify to sort a
//n is the size of the array

This function will sort the heap array by exchanging the first and last 
elements in the array with one another and then calling max heapify
in order to correct any violations. It will decrease the size of the 
array once the last element is the correct order and will continue 
until the array size is 0.  
********************************************************************/
void heapSort(int a[], int n)
{
  //I have 6 lines of code in this function. You can have more or less.

  //build max heap from an unordered list
  //call build_max_heap
  build_max_heap(a, n);//make the array a max heap first

  int size = n; //size of the unsorted portion of the array

  while(size != 0) //repeat until heap is empty
    {  
      //swap max element with last element - max element is at the end of the array
      exchange(a[0], a[size-1]);
      //discard the last node from heap
      size--;
      //root may violate max-heap property, but children are max heaps. run max_heapify to fix it.
      max_heapify(a, size, 0); 
    }
}
/*******************************************************************************
a is a heap
i is the element index

this function corrects a violiation of max heap by bubbling up an element at i                                    
********************************************************************************/                             
void bubbleUp(int a[], int i)
{
  //Write this function after you made insert() and while you are making remove.
  int p = (i - 1) / 2;//find the index of the element's parent
  
  if(a[p] < a[i])//switch the elements if parent is smaller
    {
      exchange(a[i], a[p]);//call exchange
      bubbleUp(a, p);//call bubble up again in case theres another violation
    }

}
/*********************************************************************
a is a max heap                                                                                            
cap is the capacity of the heap                                                                            
n is the number of elements the heap currently has before insertion                                        
el is the new element to be inserted                                

This function will insert an element at the end of the heap array and will
call bubbleUp() to make sure it is in the correct order so we can have 
a max heap always. It will check the capacity of the array before inserting.
**********************************************************************/                                       
void insert(int a[], int cap, int& n, int el)
{
  //refer to lecture notes
  //write this function without calling bubbleUp first. When you work on remove, you will see you will
  //have to have the same code there. Move the code into bubbleUp and call it.
 
  if(n < cap)//check the number of elements already in the array and the capacity
    {//if theres room
      n++;//increase the amount of elements
      a[n-1] = el;//add el at the last index
      bubbleUp(a, n-1);//call bubbleUp for any violations
    }
}
/*********************************************************************
a is a max heap                                                                                            
n is the number of elements the heap currently has before deletion, then decrememted after deletion               
el is the element to be removed. Assume all elements are unique     

This function will remove an element from the array heap at a certain 
index. It will move the element to be removed to the end of the array
in order for it to be removed safely. It will then decrement the size 
of the array so it excludes the removed element. It will then call
bubbleUp if necessary to check the parent of the switched element and 
perform bubbleUp. It will also call max_heapify() to make sure the 
element switched is not making any violations caused by the switch. 
*********************************************************************/
void remove(int a[], int& n, int el)
{
  //refer to lecture notes
  //Call bubbleUp and max_heapify instead of coding the same things.
  int i;//declare i so it can go through the array and be used outside the for loop scope
  for(i = 0; i < n; i++)//go through array
    {
      if(a[i] == el)//if the array finds the element at the desired index
	break;//break out of the loop and now i holds the index of element to be removed
    }
  //  cout << "this is i: " << i << endl;
  exchange(a[n-1], a[i]);//call exchange to switch the element to be removed and place it at the end
  n--;//exclude it by decreasing the amount of elements the array has
  bubbleUp(a, i);//call bubbleUp for any violations above
  max_heapify(a, n, i);//call max_heapify for any violations below
}

int main()
{
  int ar[10] = {11, 3, 4, 5, 7, 19, 20, 2, 8, 1};
  int ar2[10] = {5, 3, 10, 4, 7, 9, 11, 2, 8, 1};
  int ar3[2] = {2,1};

  cout << "testing max_heap rooted at index 3" << endl;
  max_heapify(ar, 10, 3); //max-heapify rooted at index 3                                                                                      
  print(ar, 10);//11 3 4 8 7 19 20 2 5 1  --> the tree rooted at 3 is now a max-heap (8 is at root. 2 and 5 are its children)                  

  cout << endl << "testing max_heap rooted at index 1" << endl;
  max_heapify(ar, 10, 1); //max-heapify rooted at index 1                                                                                      
  print(ar, 10);//11 8 4 5 7 19 20 2 3 1  --> the tree rooted at 1 is now a max-heap (8 is at root. 5 and 7 are its children. 5's children are 2 and 3)                                                                                                                                      

  cout << endl << "testing build_max_heap" << endl;
  build_max_heap(ar, 10);
  print(ar, 10);//20 8 19 5 7 11 4 2 3 1                                                                                                       

  cout << endl << "testing heapSort" << endl;
  heapSort(ar2, 10);
  print(ar2, 10);//1 2 3 4 5 7 8 9 10 11                                                                                                       

  cout << endl << "testing heapSort" << endl;
  heapSort(ar3, 2);
  print(ar3, 2);//1 2                                                                                                                          
  
  cout << "testing insert" << endl;
  int ar4[15] = {20, 8, 19, 5, 7, 11, 4, 2, 3, 1, -1, -1, -1, -1, -1}; //max heap with 10 elements already   
  int n = 10; //n is the number of elements in the heap                                                      
  insert(ar4, 15, n, 15); //trying to insert 15                                                              
  print(ar4, n); //20 15 19 5 8 11 4 2 3 1 7                                                                 


  
  cout << "testing remove" << endl;
  remove(ar4, n, 15); //trying to remove 15                                                                  
  print(ar4, n);//20 8 19 5 7 11 4 2 3 1                                                                     
  
  return 0;
}

