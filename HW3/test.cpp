#include <iostream>

using namespace std;

class TreeNode
{
public:
  char d;
  TreeNode *l, *r;
  TreeNode(char d) : d(d), l(nullptr), r(nullptr) {}
};

class StackNode
{
public:
   TreeNode *t;
   StackNode *n;
   StackNode(TreeNode*t) : t(t), n(nullptr) {}
};

class ExpressionTree
{
public:
  ExpressionTree()
  {
      top = nullptr;
  }

  void push(TreeNode *ptr)
  {
    if (top == nullptr)
      top = new StackNode(ptr);
    else
    {
      StackNode *nptr = new StackNode(ptr);
      nptr->n = top;
      top = nptr;
      }
   }
   TreeNode *pop()
   {
      if (top == nullptr)
      {
        cout<<"Underflow"<<endl;
      }
      else
      {
        TreeNode *ptr = top->t;
        top = top->n;
        return ptr;
      }
   }

   TreeNode *peek()
   {
      return top->t;
   }
   void insert(char val)
   {
      if (isDigit(val))
      {
         TreeNode *nptr = new TreeNode(val);
         push(nptr);
      }
      else if (isOperator(val))
      {
         TreeNode *nptr = new TreeNode(val);
         nptr->l = pop();
         nptr->r= pop();
         push(nptr);
      }
      else
      {
         cout<<"Invalid Expression"<<endl;
         return;
      }
   }

   bool isDigit(char ch)
   {
      return ch >= '0' && ch <= '9';
   }

   bool isOperator(char ch)
   {
      return ch == '+' || ch == '-' || ch == '*' || ch == '/';
   }

   int toDigit(char ch)
   {
      return ch - '0';
   }

   void buildTree(string eqn)
   {
      for (int i = eqn.length() - 1; i >= 0; i--)
         insert(eqn[i]);
   }

   void prefix()
   {
      preOrder(peek());
   }

   void preOrder(TreeNode *ptr)
   {
      if (ptr != nullptr)
      {
         cout << ptr->d;
         preOrder(ptr->l);
         preOrder(ptr->r);
      }
   }
private:
  StackNode *top;
};

int main()
{
   string s;
   ExpressionTree tree;
   cout << "Enter equation in Prefix form: \n";
   cin >> s;
   tree.buildTree(s);
   cout<<"Prefix: ";
   tree.prefix();
   cout << endl;

   return 0;
}
