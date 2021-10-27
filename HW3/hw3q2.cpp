#include <iostream>

using namespace std;

class TreeNode
{
public:
  string d;
  TreeNode *l, *r;
  TreeNode(string d) : d(d), l(nullptr), r(nullptr) {}
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
   void insert(string val)
   {
       if (isOperator(val))
       {
          TreeNode *nptr = new TreeNode(val);
          nptr->l = pop();
          nptr->r= pop();
          push(nptr);
       }
      else
      {
         TreeNode *nptr = new TreeNode(val);
         push(nptr);
      }
   }

   bool isOperator(string s)
   {
      return s == "+" || s == "-" || s == "*" || s == "/";
   }


   void buildTree(string eqn[], int length)
   {
      for (int i = length - 1; i >= 0; i--)
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
         cout << ptr->d << " ";
         preOrder(ptr->l);
         preOrder(ptr->r);
      }
   }
private:
  StackNode *top;
};

int main()
{
   string s1[3] ={"+", "7", "24"};
   ExpressionTree tree1;
   tree1.buildTree(s1,3);
   cout << "Prefix: ";
   tree1.prefix();
   cout << endl;

   string s[7] = {"/", "*", "A", "+", "B", "C", "D"};
   ExpressionTree tree2;
   tree2.buildTree(s,7);
   cout << "Prefix: ";
   tree2.prefix();
   cout << endl;

   return 0;
}
