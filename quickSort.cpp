/**********************************
Templated created by Kazumi Slott
CS311

Your name:Jared Falcon
Your programmer number: 5
Any difficulties?:The only mistake i made while doing this was setting my end in the for loop to end-1 thinking
it would stop before the pivot, but it stopped two indexes before the pivot not 1 haha
***********************************/
#include <iostream>
using namespace std;

/*************************************************
ar is the array to be printed
s is the size

This function will print the contents of an array.
 ************************************************/
void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}

//It is good to have the swap function so partition() won't get crowded. 
/*************************************************
x pointer that points to an element 
y pointer that point to the second element

This swap function will use x and y to as our pointers 
in order to be able to change the values of the array 
permanently and not just in this function. 
 ************************************************/
void Swap(int* x, int* y)
{
  int temp = *x;//put the x in temp
  *x = *y;//put y in x now
  *y = temp;// put temp(x) in y 
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

  //I have 3 variables: pivot, i and swap_index. You may have any local variables.
  int pivot = ar[end];//stores the last element as our pivot
  int green = start;//green index to start at the beginning 
  int red = start;//red index to start at the beginning 

  for(int j = start; j < end; j++)//for loop to go through the array
    {
      if(ar[green] <= pivot)//compare the green with the pivot
	{	  
	  Swap(&ar[green], &ar[red]);//call our swap function to swap our values,
	  //also the values are retuning their address in order for them to be properly changed
	  red++;//move red to the next index
	}
      green++;//move green to the next index regardless if there was a swap
    }
  Swap(&ar[red], &ar[end]);//this will swap the red value with the pivot at the end

  return red;//return the index of the pivot after its swapped, so in the middle

  //For implementation of this function, refer to my lecture notes "quick sort". 
  //If you used a different implementation, I would assume you cheated and give you zero points.

  //This function returns the index where the pivot value went in. 
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

int main()
{
  int ar[] = {15, 10, 5, 7, 1, 4, 12, 8, 6};
  quickSort(ar, 0, 8);
  printAr(ar, 9); //1 4 5 6 7 8 10 12 15

  int ar1[] = {1, 7, 5, 3, 9, 4};
  quickSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  quickSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
