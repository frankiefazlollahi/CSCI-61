#include <iostream>

using namespace std;
/*
To get the number of possible binary trees created with n nodes, you need to add together the possibilities of all
previous trees, where the combination of two smaller trees gives the correct amount of nodes. For every 2 trees
(let's call them T1 and T2) there are binaryTreeCount(T1)*binaryTreeCount(T2) number of ways to combine them.
Since T1 is a number from 1 to n and T2 is the number n - T1, this recursive function works to provide the number of
possible binary trees that can be created with n nodes.
In other words, this function works by considering all possible pair of counts for nodes in the left and right subtrees,
and multiplying the counts for a particular pair. Finally you add the results of the pairs.
*/

//nodes variable is number of nodes
int binaryTreeCount(int nodes)
{
  if(nodes <= 1)
  {
    return 1;
  }
  int count = 0;
  for(int i = 0; i < nodes; i++)
  {
    count += binaryTreeCount(i)*binaryTreeCount(nodes-i-1);
  }
  return count;
}

int main()
{
  cout << "Number of binary trees with 3 nodes: " << binaryTreeCount(3) << endl;
  cout << "Number of binary trees with 4 nodes: " << binaryTreeCount(4) << endl;

  return 0;
}
