/**************************************
Template created by Kazumi Slott
CS311

Your name: Jared Falcon
Your programmer number:5
Any difficulties?:
**************************************/

#include <iostream>
using namespace std;

void swap(int& data1, int& data2)
{
  int temp = data1;
  data1 = data2;
  data2 = temp;
}

void print(const int ar[], int n)
{
  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
}
/******************************************************
ar is the array
n is the size

This algorithm works by comparing two elements together, it compares the first two if the right element is bigger than the left, we move the right element to the left side. We move to the next element, if it’s smaller than the left we move it down until it reaches the beginning of the array or it finds an element smaller than itself. If the element to the right is bigger than the one on the left, we move on the next element and then do the same thing, compare with the left elements to see if it’s smaller than all of them.   
 *****************************************************/
void insertionSort(int ar[], int n)
{
  //https://www.youtube.com/watch?v=ROalU379l3U
  //Implement the insertion sort by watching the above youTube video. Your algorithm has to match their dance.
   
  for(int i = 1; i < n; i++)//run for loop with i at index 1
    {
      int x = i;//make l the same as i both at index 1
      
      while(x > 0 && ar[x] < ar[x-1])//while x > 0 if ar[x] is less than ar[x-1] switch them
	{
	  swap(ar[x], ar[x-1]);//call swap
	  x--;//decrement x 
	}
    }
  //call swap
 
}
/*******************************************************************
ar is the array 
N is the size

This algorithm will find the biggest or smallest element in the array and move it to the back of the array. It will be able to move it and then decrement the size of the array so it will exclude the last element. It will need to exclude to exclude the last element so it doesn’t get compared or altered since it would already be considered sorted. 
 ******************************************************************/
void selectionSort(int array[], int N)
{
  //Implement selection sort by moving the smallest element to the beginning.
  //call swap
  //ar is an integer array of any size
  int SmallIndx; //the index of the largest value                         
  int temp; //temporary variable that holds the largest value                                   
  //last is the last index in unsorted portion                                     
  for(int first = 0; first < N-1; first++) //(int last = N-1; last >= 1; last--)
    {
      SmallIndx = first; //assume the first item is the largest                                                           
      //find the largest in unsorted portion ([0..last])                                                            
      for(int i = first + 1; i < N; i++)
        {
          if(array[i] < array[SmallIndx]) //The current item is larger                                              
            SmallIndx = i;
        }
      //swap the largest with the last item in the unsorted portion                                                 
      swap(array[SmallIndx], array[first]);
    }
  //You can find more information in my homework document
}

//Implemented by Kazumi Slott
//ar is an integer array of any size
//s is the size of the array
//For more info, read my CS211 lec notes "Lec notes 2-2: bubble sort"
//You could also watch my CS211 lecture recording "Lecture 2/5(Fri) - bubble sort and enum" 
/********************************************************************************
This function will sort the array using bubble sort. The idea is that the items in the array will bubble around until they are sorted. In this case the array will be sorted in descending order. The largest item in the front, and the smallest in the back of the array.
 *******************************************************************************/
void bubbleSort(int ar[], int s)
{
  bool done = false; //set to false if there was swapping meaning not done yet.                                   
  int last = s - 2; //last is the index of the left element in the last pair to be checked. In the first step, last should point to the second to last.                                                                            
  while(!done) //swapping required in the previous iteration or the first iteration starts                        
    {
      done = true; //no swapping has happened yet when a new step starts.                                         

      for(int i = 0; i <= last; i++) //check each adjacent pair of items in the unsorted part                     
        {
	  if(ar[i] < ar[i + 1]) //the pair is out of order                                                          
	    {
	      swap(ar[i], ar[i+1]);
	      done = false; //swapping required. needs to proceed to the next iteration.                            
	    }
        }
      last--; //the area to be checked shrinks down after each iteration                                         
    }//end of while                                                                                               
}
/**************************************************
ar is the array
start is the starting point of the partition
end is used to find the pivot

This function will go through an array using two
indexes and moving the green one to compare with the
pivot. If the green index is less than the pivot,
swap it with the red index. After that you increment
the red index and move the green index again until
it reches the index before pivot. At this point you have
to swap whatever position the red index ended up at
with the position of the pivot.
************************************************/
int partition(int ar[], int start, int end)
{
  //copy and paste partition() from your quickSort.cpp
  int pivot = ar[end];//stores the last element as our pivot
  int green = start;//green index to start at the beginning
  int red = start;//red index to start at the beginning

  for(int j = start; j < end; j++)//for loop to go through the array
    {
      if(ar[green] <= pivot)//compare the green with the pivot
        {
          swap(ar[green], ar[red]);//call our swap function to swap our values,
          //also the values are retuning their address in order for them to be properly changed
          red++;//move red to the next index
        }
      green++;//move green to the next index regardless if there was a swap
    }
  swap(ar[red], ar[end]);//this will swap the red value with the pivot at the end

  return red;//return the index of the pivot after its swapped, so in the middle

}
/***********************************************************
ar the array to be sorted
start is the start position
end is the last index

This function will sort an array quick. It uses a partition function
that does all the work like the one above. It calls the partition
function first and then it calls itself on the left side and then
again on the right side. It will stop when the start is equal
to the end (ar, 0, 0) it will not enter the if statement.
***********************************************************/
void quickSort(int ar[], int start, int end)
{
  //copy and paste quickSort() from your quickSort.cpp   
  if(start < end) //If the partition has only one element or none, return.
    //In other words, if the partition has at least 2 elements, go inside the if.
    //use start and end to figure out.
    {
      //call partition.
      int part = partition(ar, start, end);//call partition and store the index
      //quickSort on the left partition
      quickSort(ar, start, part - 1);//uses index -1 because we dont want to include the original pivot
      //quickSort on the right partition
      quickSort(ar, part + 1, end);//same thing but + 1 for the right side
    }
}
/********************************************************************
ar is the array we are passing
first is the beginning of the array and subarray
middle is calculated for every subarray
last is the last index for the array and subarray

This fucntion will merge two arrays together in order of smallest to 
greatest. It will compare the elements of the two arrays one by one 
it will take the smaller element from the two arrays and add it to the 
temp array. It will keep doind this until either array is empty and then 
it will add the rest of the elements that remain to the temp array. At the
very end it will add all of the sorted elements from the temp array into 
the original array. 
*********************************************************************/
void merge(int ar[], int first, int middle, int last)
{
  //copy and paste merge() from your mergeSort.cpp   
  int* temp = new int[last-first +1];//make a dynamic array withe required size
  int i = first;//make i start at whatever position first is at for any subarray
  int j = middle + 1;//our index j will start after middle and cover through last index
  int k = 0;//this will be the index of the temp array

  while(i <= middle && j <= last)//loop so we dont go over the middle for the left and j doesnt go over last index
    {
      if(ar[i] <= ar[j])//compare the two array values, if left is smaller or equal
        temp[k++] = ar[i++];//add it to the temp array and increment boths arrays
      else//otherwise the element in the j array is smaller and add it, increment both arrays
        temp[k++] = ar[j++];
    }

  for(; i <= middle; i++, k++)//this for loop will add the remaining elements of the i(left) array into temp
    temp[k] = ar[i];//i keeps its current index place, no need to intialize again

  for(; j <= last; j++, k++)//this for loop will add the remaining elements of the j(right) array into temp
    temp[k] = ar[j];//i keeps its current index place, no need to intialize again

  for(i = first, k = 0; i <= last; i++, k++)//for loop to add all the elements into the original array
    ar[i] = temp[k];

  delete [] temp;//delete the temp array
  temp = NULL;//make temp pointer point to NULL

}
/**********************************************************
ar is the array we want to sort
first is the index of the array
last is the index at the end of the array

This function will be able to sort an array by divinding it into multiple
subarrays and then merging them together by halves. It calculates the
middle of the array and breaks it down that way. It calls itself on the left
and the right. At the end it will call merge to merge the subarrays until we are
left with just two subarrays that will merge into the big final array.
 *********************************************************/
void mergeSort(int ar[], int first, int last)

{
  //copy and paste mergeSort()from your mergeSort.cpp   
  if(first < last)//if there are more than 1 element
    {
      int middle = (first + last) / 2;//calculate middle
      mergeSort(ar, first, middle);//call sort on the left of middle
      mergeSort(ar, middle+1, last);//call sort on the right of middle +1 not including middle
      merge(ar, first, middle, last);//call merge to put it all together
    }
}


