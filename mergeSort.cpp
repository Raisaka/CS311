/**********************************
Templated created by Kazumi Slott
CS311

Your name:Jared Falcon
Your programmer number: 5
Any difficulties?:I only had trouble keeping track of the three arrays 
***********************************/
#include <iostream>
using namespace std;

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}
/********************************************************************
ar is the array we are passing
first is the beginning of the array and subarray
middle is calculated for every subarray
last is the last index for the array and subarray
*********************************************************************/
void merge(int ar[], int first, int middle, int last)
{
  int* temp = new int[last-first +1];//make a dynamic array withe required size
  int i = first;//make i start at whatever position first is at for any subarray
  int j = middle + 1;//our index j will start after middle and cover through last index
  int k = 0;//this will be the index of the temp array

  while(i <= middle && j <= last)//loop so we dont go over the middle for the left and j doesnt go over last index
    {
      if(ar[i] < ar[j])//compare the two array values, if left is smaller
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
  //For implementation of this function, refer to my lecture notes "merge sort"
  //If you are using a different technique, I assume you cheated and will give you zero points.
  
  //Don't forget to destroy temp array, which is created dynamically
}
/********************************************************************
ar is the array we want to sort
first is the index of the array
last is the index at the end of the array

This function will be able to sort an array by divinding it into multiple
subarrays and then merging them together by halves. It calculates the 
middle of the array and breaks it down that way. It calls itself on the left
and the right. At the end it will call merge to merge the subarrays until we are
left with just two subarrays that will merge into the big final array. 
 *******************************************************************/
void mergeSort(int ar[], int first, int last)
{
  
  if(first < last)//if there are more than 1 element
    {
      int middle = (first + last) / 2;//calculate middle
      mergeSort(ar, first, middle);//call sort on the left of middle
      mergeSort(ar, middle+1, last);//call sort on the right of middle +1 not including middle 
      merge(ar, first, middle, last);//call merge to put it all together 
    }
  //For implementation of this function, refer to my lecture notes "merge sort"
}

int main()
{
  int ar[] = {1, 8, 6, 4, 10, 5, 3, 2, 22}; //the array used in my lecture notes
  mergeSort(ar, 0, 8);
  printAr(ar, 9); //1 2 3 4 5 6 8 10 22

  int ar1[] = {1, 7, 5, 3, 9, 4};
  mergeSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  mergeSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
