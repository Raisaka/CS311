/******************************************
Template created by Kazumi Slott
CS311
Graph of social network implmemented with a matrix

Your name: Jared Falcon
Your programmer number: 5
Outputs:
Enter a person: A
Enter their friend: B
Yes, they are fiends!
These are A's friends: B C E
 This is refer  F G D H
Enter a friend: A
These are A friends: B D E
 This is 2nd refer  C G

Any difficulties?:
********************************************/


#include <iostream>
using namespace std;

const int NUM = 8;

void printArray(char ar[], int size)
{
  for(int i = 0; i < size; i++)
    cout << ar[i] << " ";
  //This would come in handy
}
//function that returns true if there are duplicate in the array
bool duplicate(char ar[], int size, char e)
{
  for(int i = 0; i < size; i++)
    {
      if(e == ar[i])
	return true;
    }
  return false;

}
int main()
{
  //This program should still work even if we change NUM to 100 and change the matrix.
  int MAX = 8;
  //       row column  
  int m[NUM][NUM] = {// A  B  C  D  E  F  G  H
                 /*A*/ {0, 1, 1, 0, 1, 0, 0, 0}, 
		 /*B*/ {1, 0, 1, 0, 0, 1, 1, 0},//1  
		 /*C*/ {1, 1, 0, 0, 1, 1, 0, 0},//2
		 /*D*/ {0, 0, 0, 0, 1, 0, 0, 0},
		 /*E*/ {1, 0, 1, 1, 0, 1, 0, 1},
		 /*F*/ {0, 1, 1, 0, 1, 0, 0, 0},//4
		 /*G*/ {0, 1, 1, 0, 1, 0, 0, 0},
		 /*H*/ {0, 0, 0, 0, 1, 0, 0, 0}
  };  //Mij where i is row and j is column
  //A(0), B(1), ....
  char homie1;
  char homie2;


  cout << "Enter a person: ";
  cin >> homie1;
  cout << "Enter their friend: ";
  cin >> homie2;

  //check if A and F are friends
  if(m[homie1-'A'][homie2-'A'] == 1)
    cout << "Yes, they are fiends!";
  else
    cout << "No, they are not homies :(";
  cout << endl;

  //Show all friends of A
  char friends[MAX]; //store all A's direct friends
  int s = 0;//keep track of the inddex
  for(int j = 0; j < NUM; j++)//goes through the row of A 
    {
      if(m[0][j] == 1)//checks every column of A
	{
	  friends[s] = char('A' + j);//add the column value to friend array
	  s++;
	}
    }
  cout << "These are A's friends: ";
  printArray(friends, s);
  //Aswer: B, C, E

  //refer A A's friends' direct friends 
  char refer[MAX]; //store reffered friends for A
  //I made one more function to keep the loop small  

  /*
  cout << endl;
  cout << friends[0]-'A' << endl; 
  cout << friends[1]-'A' << endl;
  cout << friends[2]-'A' << endl;
  */
  
  int y = 0;//tracks index
  for(int i = 0; i < s; i++)//loop will loop as many times as friend array has elements so three B C E
    {
      for(int k = 0; k < NUM; k++)//goes through the column
	{
	 	  
	  if(m[friends[i]-'A'][k] == 1)//checks the respective column 
	    { 
	      if(char('A' + k) != homie1)//makes sure our input is not included
		{
		  if(duplicate(refer, y, char('A' + k)) == false && duplicate(friends, s, char('A' + k)) == false)//if both the arrays have bo duplicates then you can add element to refer 
		    refer[y++] = char('A' + k);//add element to refer and increment, it was not a duplicate
		}
	    }
	}
    }
  

  cout << endl;
  cout << " This is refer " << " "; 
  printArray(refer, y);
  cout << endl;


  
  
  //Answer: D, F, G, H  (don't repeat the same person. Order doesn't matter)
  




  //Test your code above with a new matrix - the picture is in the document "Lec supplement - matrix for 11/15(Mon)"\ under "Assignments"
   int m2[NUM][NUM] = {{0, 1, 0, 1, 1, 0, 0, 0},
		       {1, 0, 1, 0, 0, 0, 0, 0},
		       {0, 1, 0, 0, 1, 1, 0, 0},
		       {1, 0, 0, 0, 1, 0, 0, 0},
		       {1, 0, 1, 1, 0, 0, 1, 0},
		       {0, 0, 1, 0, 0, 0, 0, 1},
		       {0, 0, 0, 0, 1, 0, 0, 1},
		       {0, 0, 0, 0, 0, 1, 1, 0}};

 //A's friends -> B, D, and E

   char homie3;
   cout << "Enter a friend: ";
   cin >> homie3;

   char Fr[MAX];
   int v = 0;
   for(int j = homie3-'A'; j < NUM; j++)
     {
       if(m2[homie3-'A'][j] == 1)
	 {
	   Fr[v] = char('A' + j);
	   v++;
	 }
     }
   cout << "These are " << homie3 << " friends: ";
   printArray(Fr, v);

   
 //friends referred to A -> C and G
   char REF[MAX];
   int z = 0;
   for(int i = 0; i < v; i++)
     {
       for(int k = 0; k < NUM; k++)
	 {

	   if(m2[Fr[i]-'A'][k] == 1)
	     {
	       if(char('A' + k) != homie3)
		 {
		   if(duplicate(REF, z, char('A' + k)) == false && duplicate(Fr, v, char('A' + k)) == false)
		     {
		       REF[z] = char('A' + k);
		       z++;
		     }

		 }
	     }
	 }
     }

   cout << endl;
   cout << " This is 2nd refer " << " ";
   printArray(REF, z);
   cout << endl;
   
  return 0;
}
