/******************************************************************
Jared Falcon
CS 311
9/16/2021

This program will simulate a calculator in which it will take an 
infix expression and then it will return a postfix expression. 
The postfix expression will then be evaluated and the answer will be 
returned. There will be a few catches in the main to figure out 
if the expression are correct or if the function pop() throws an 
Underflow.
 ****************************************************************/
#include <iostream>
#include "stack_L_T.h"


using namespace std;
double Postfix(Stack<double>& myStack, string exp);
void infixToPostfix(string s);
string Infix(Stack<char>& s);
string Enter();
int Pres(char c);
bool isOperator(char ch);
bool isOperand(char ch);
double charToInt(char ch);
double doMath(double opr1, char opt, double opr2);

int main()
{
  Stack<double> Stk;//uses doubles for the postfix answer
  Stack<char> S;//uses chars to push and pop operators
  string post;//postfix string to be evaluated
 
  try//try the following functions calls
    {
      post = Infix(S);//call infix
      cout << post << endl;//post the postfix notation
      cout << "Answer: " << Postfix(Stk, post) << endl;;//call postfix function and return the final answer
    }
  catch(Stack<char>::Underflow)//catches anything in the char stack
    {
      cout << "The expression is in the wrong format!" << endl;
    }
  catch(Stack<double>::Underflow)//catches any errors in the double stack
    {
      cout << "The expression is in the wrong format!" << endl;
    }
  catch(const char* msg)//points to the message we are throwing in our stacks
    {
      cout << msg << endl;
    }

  return 0;
}
/********************************************************************
This function will evaluate the postfix expression that is passed. 
It will calculate the expression and return the answer as a double. 
This function uses the satck to push and pop operands as operators 
show up and the push the answer or two operands back in the stack.
The remaining element in our stack if there are no errors, should be 
our final answer to our expression.

myStack is the stack used to push and pop operands as operators show up
exp is the postfix expression that is being passed 
 *******************************************************************/
double Postfix(Stack<double>& myStack, string exp)
{
 
  double num;//will store our converted char into int
  double ans;//will store the right hand side operand
  double ans2;//will store the left hadn side operand
  double ans3;//will store the product of ans and ans2, ans3 will be pushed into the stack
  bool full = false;//will help us enter and exit loops

  for(int i = 0; !full && i < exp.length(); i++)//for loop to acess every single character in the string
    {
      full = false;//full = false
      if(isOperator(exp[i]))//if the character is an operator
        {
          ans2 = myStack.getTop();//store top integer into ans2, before we pop it
          if(!myStack.empty())//check to see if stack is not empty before we pop
            {
              myStack.pop();//pop top number
            }
          else//wont pop or trigger exit(1)
            {
              cout << "Cant pop" << endl;
            }
          if(!myStack.empty())//checks to see if there are more integers in the stack to operate
            {
              ans = myStack.getTop();//stores left hand operand
              myStack.pop();//pop it to operate
              ans3 = doMath(ans, exp[i], ans2);//call doMath and operate
	      myStack.push(ans3);//push new integer into stack
            }
          else//if stack is empty, there are not enough operands
            {
              cout << endl;
              throw "The expression is in the wrong format!";
	      //cout << "Error: Not enough operands" << endl;
              full = true;//exit condition met
              cout << endl;
            }
        }
      else if(isOperand(exp[i]))//if the character is an operand
        {
          num = charToInt(exp[i]);//calls function to convert char into integer
	  myStack.push(num);//push the operand
        }
      else//if the character is not and operator or integer
        {
          cout << endl;
          cout <<"Error: Invalid item was found " << exp[i] << endl;
          full = true;//exit loop
          cout << endl;
        }
    }
  double answer;//stores our answer
      while(full == false)//while loop used if we dont have any errors yet, we can enter the loop
	{
	  answer = myStack.getTop();//store top element into answer
	  if(!myStack.empty())//check if the stack is not empty before we pop
	    {
	      myStack.pop();//pop
	    }
	  else//stack is empty
	    {
	      cout << "Cant pop" << endl;
	    }
	  if(!myStack.empty())//if the stack is not empty at this point, there are too many operands
	    {
	      cout << endl;
	      throw "The expression is in the wrong format!";
	      //cout << "Error: Too many operands" << endl;
	      full = true;//exit the while loop
	      cout << endl;
	    }
	  else //we already popped our answer and stored it, now just display it and the stack is empty
	    {	      
	      cout << endl;
	      full = true;//exit loop
	    }
	}
      return answer;//return final answer

}
/****************************************************************
This function will be able to take a mathematical expression (infix)
and return the postfix expression of it. It will go through an
infix expression string charcater by character. 

s is the stack we will be using to push and compare operators as well
as a left (. 
 ****************************************************************/
string Infix(Stack<char>& s)
{    
  string post;//postfix string to be returned
  string Inx = Enter();//call enter infix expression
 
  char popped;//stores popped chars

  for(int i = 0; i < Inx.length(); i++)//for loop to through the infix expression string
    {
      char ch = Inx[i];//save character into ch
      if(isOperand(ch)) //ch >= '0' && ch <= '9')//if the current token is an operand(number), add to string
	{
	  post += ch;//add operand to postfix expression
	}
      else if(ch == '(')//if the current token is a left parenthesis, push into stack
	{
	  s.push(ch);//push the left ( into the stack
	}
      else if(ch == ')')//if the current token is a right paranthesis
	{
	  while(s.getTop() != '(')//stop until you see a left ( to match the right )
	    {
	      post += s.getTop();//add top element to the postfix string
	      s.pop();//pop the element right after 		  
	    }
	  s.pop();//this will be used to pop the left (
	}
      else if(isOperator(Inx[i]))//if the character is an operator 
	{
	  while(!s.empty() && Pres(Inx[i]) <= Pres(s.getTop()))//if the stack is not empty and the presedence 
            {
	      if(s.getTop() == '(')//if the top element is a left (
		break;//get out of the loop
	      post += s.getTop();//otherwise add top element to the post string
	      s.pop();//then you pop it
            }
          s.push(ch);//if the stack was empty or element had lower presedence or it was a left ( just add it
        }
      else//this will check for invalid operators 
	{
	  throw "The expression is in the wrong format";//to be caught in main
	}          
    }
 
  while(!s.empty())//after the token is read, pop rest of stack and add to string
    {
      post += s.getTop();//store the element into the string
      s.pop();//pop right after
    }

  return post;//return our finished string
}
/***********************************************************
simple enter expression function 
 **********************************************************/
string Enter()
{
  string exp;//stores infix expression
  //  cout << "Enter infix expression: ";
  cin >> exp;
  return exp;//return infix 
}
/**********************************************************
This function will test the presedence of the operators that
will need to be pushed or pop depending on their presendence.

c is the operator to be passed and returns 2 or 1 for presedence
 *********************************************************/
int Pres(char c)
{
  switch(c)//switch for cases
    {
    case '*': return 2;
      break;
    case '/': return 2;
      break;
    case '+': return 1;
      break;
    case '-': return 1;
      break;
    }
}
/**********************************************************
ch will be our operator will return true, if not false

This function will return true if the character ch is
an operator and false if not.
***********************************************************/
bool isOperator(char ch)
{
  if(ch == '+' || ch == '-' || ch == '*' || ch == '/')//if ch is these operators return true
    {
      return true;
    }
  else//not these operators return false
    {
      return false;
    }
}
/*********************************************************
ch wil be our operand

This function will return true if our character is range of
'0' and '9' ascii value wise.
********************************************************/
bool isOperand(char ch)
{
  if(ch >= '0' && ch <= '9')//if ch is in the range of these characters values, return true
    return true;
  else//not, return false
    return false;

}
/***********************************************************
ch will be our character that will be an integer

This function will return the converted character into an integer.
Only if its an integer or characters '0' to '9'
**********************************************************/
double charToInt(char ch)
{
  double num;//stores converted character
  num = (double)ch - '0';//convert the character into and integer
  return num;//return the integer
}
/****************************************************************
This fucntion will return the answer for each operation that needs 
to be performed.

opr1 is the left operand
opt is the operation being performed 
opr2 is the right operand
 **************************************************************/
double doMath(double opr1, char opt, double opr2)
{
  switch(opt)//switch for each different operator and return the product
    {
    case '+':
      return (opr1 + opr2);
      break;
    case '-':
      return (opr1 - opr2);
      break;
    case '*':
      return (opr1 * opr2);
      break;
    case '/':
      return (opr1 / opr2);
      break;
    default: cout << "Invalid " << endl;

    }
}

