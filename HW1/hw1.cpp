#include <iostream>
#include <stack>

using namespace std;

bool isOperator(const string& str);

int priority(const string& str);

string prefixToInfix(const string pre[], const int& size);

string infixToPrefix(const string infix[], const int& size);

int main()
{
  string test1[3] ={"+", "2", "30"};
  cout << "Prefix: ";
  for(int i = 0; i < 3; i++)
  {
    cout << test1[i] + " ";
  }
  cout << endl;
  cout << "Infix: " << prefixToInfix(test1,3) << endl << endl;

  string test2[7] = {"/", "*", "A", "+", "B", "C", "D"};
  cout << "Prefix: ";
  for(int i = 0; i < 7; i++)
  {
    cout << test2[i] + " ";
  }
  cout << endl;
  cout << "Infix: " << prefixToInfix(test2,7) << endl << endl;

  string test3[3] = {"14", "+", "86"};
  cout << "Infix: ";
  for(int i = 0; i < 3; i++)
  {
    cout << test3[i] + " ";
  }
  cout << endl;
  cout << "Prefix: " << infixToPrefix(test3,3) << endl << endl;

  string test4[9] = {"A", "*", "(", "B", "+", "C", "/", "D", ")"};
  cout << "Infix: ";
  for(int i = 0; i < 9; i++)
  {
    cout << test4[i] + " ";
  }
  cout << endl;
  cout << "Prefix: " << infixToPrefix(test4,9);

  return 0;
}

bool isOperator(const string& str)
{
  if((str == "+") || (str == "-") || (str == "*") || (str == "/"))
  {
    return true;
  }
  return false;
}

int priority(const string& str)
{
  if ((str == "-") || (str == "+"))
  {
    return 1;
  }
  else if ((str == "*") || (str == "/"))
  {
    return 2;
  }
  else if (str == "^")
  {
    return 3;
  }
  return 0;
}

string prefixToInfix(const string pre[], const int& size)
{
  stack<string> s;
  for(int i = size -1; i >= 0; i--)
  {
    if(isOperator(pre[i]))
    {
      string operator1 = s.top();
      s.pop();
      string operator2 = s.top();
      s.pop();
      string temp = "(" + operator1 + pre[i] + operator2 + ")";
      s.push(temp);
    }
    else
    {
      s.push(pre[i]);
    }
  }
  return s.top();
}

string infixToPrefix(const string infix[], const int& size)
{
  stack<string> operators;
  stack<string> operands;
  for(int i = 0; i < size; i++)
  {
    if(infix[i] == "(")
    {
      operators.push(infix[i]);
    }
    else if(infix[i] == ")")
    {
      while((operators.top() != "(") && !operators.empty())
      {
        string operand1 = operands.top();
        operands.pop();
        string operand2 = operands.top();
        operands.pop();
        string op = operators.top();
        operators.pop();
        string temp = op + " " + operand2 + " " + operand1;
        operands.push(temp);
      }
      operators.pop();
    }
    else if(!isOperator(infix[i]))
    {
      operands.push(infix[i]);
    }
    else
    {
      while(!operators.empty() && (priority(operators.top()) >= priority(infix[i])))
      {
        string operand1 = operands.top();
        operands.pop();
        string operand2 = operands.top();
        operands.pop();
        string op = operators.top();
        operators.pop();
        string temp = op + " " + operand2 + " " + operand1;
        operands.push(temp);
      }
      operators.push(infix[i]);
    }
  }
  while(!operators.empty())
  {
    string operand1 = operands.top();
    operands.pop();
    string operand2 = operands.top();
    operands.pop();
    string op = operators.top();
    operators.pop();
    string temp = op + " " + operand2 + " " + operand1;
    operands.push(temp);
  }
  return operands.top();
}
