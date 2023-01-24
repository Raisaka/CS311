/**********************************
CS311 Kazumi Slott

Your name: Jared Falcon
Your program number:5
Describe any difficulties here: I couldnt get AlgoA to work properly, my logic for that alogorithm was there 
because I know what it does. I don't know how to implement it properly however. 
*********************************/

/********************************************************************
//Make your own test client and test your functions thorougly.
//You will submit this header file only. My test client will test your functions.
********************************************************************/


//What is the runntime complexity of this algorithm? O(n^2)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above.
/****************************************************************
a[] the array
sz is the size

This algorithm will compute the sum of every sub array starting at 1
the {2,2}, then {3, 3, 3}
 ***************************************************************/
int algoA(const int a[], int sz)//Don't change the function headers
{
  int sum = 0;
 
  // stores the maximum sum of subarray ending at the current position
  int temp = 0;
    
  // traverse the given array
  for (int i = 0; i < sz; i++)
    {
      
      for(int j = 0; j < sz; j++)
        {
          temp += a[j];
          //cout << temp << endl;
        }
      //temp = sum;
      if(temp > sum)
	sum = temp;
        
      temp = 0;
    }
  
  return sum;
}

//What is the runntime complexity of this algorithm? O(n)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
/**************************************************************
a[] the array
sz is the size

This algorithm should compute the sum of starting at index 1 and
save the bigger sum as it appears.
 *************************************************************/
int algoB(const int a[], int sz)
{
  int sum = 0;//max sum 
  int end = 0;//biggest sum at the time

  for(int i = 0; i < sz; i++)//loop through
    {
      if(a[i] <= end + a[i])//if the current element is less than end + current
	end += a[i];//add it to the total of end
      else//otherwise 
	end = a[i];//end is the current
   
      if(end > sum)//end being our highest sum at the time will compare with total sum 
	sum = end;//if end is bigger sum is now that total 
    }

  return sum;
}

//What is the runntime complexity of this algorithm? O(n)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
/*************************************************************
a[] the array
sz is the size

This algotithm will disregard any negative numbers if the sum of the array
so far is negative. It will make the keep our sum if the previous sum
was 0.
 ************************************************************/
int algoC(const int a[], int sz)
{
  int sum = 0;//stores sum
   
  int end = 0;//biggest sum end
    
  for (int i = 0; i < sz; i++)
    {
      end = end + a[i];//stores first sum
 
       
      if(end > 0)//if end is not 0 keep end
	end = end;
      else//if not, reset end to 0
	end = 0;

      
      if(sum > end)//if sum is bigger than end, keep sum
	sum = sum;//sum stays
      else//otherwise end is bigger than sum and now sum is end
	sum = end; 
    }
 
  return sum;
}
