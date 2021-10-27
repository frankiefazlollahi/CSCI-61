#include <iostream>

using namespace std;
//highest amount of nodes in the tree
const int capacity = 20;
//array implementation of binary tree
//the left node of a root at position i in the array is 2*i+1 and the right node is 2*i+2
class BT{
public:
  BT(): used(0){tree[0] = 0;}
  void insert(int i){tree[used] = i; used++;}
  //function to set left child of parent where the parent is the parent's index in the array
  void setLeft(int child, int parent)
  {
    if(tree[parent] == 0 || parent >= capacity)
      return;
    else
      tree[parent*2 + 1] = child;
      used++;
  }
  //function to set right child of parent where the parent is the parent's index in the array
  void setRight(int child, int parent)
  {
    if(tree[parent] == 0 || parent >= capacity)
      return;
    else
      tree[parent*2 + 2] = child;
      used++;
  }
  void printTree()
  {
    for(int i = 0; i < used; i++)
    {
      if(tree[i] != 0)
        cout << tree[i] << " ";
    }
  }
  void swap(int a, int b)
  {
    int index1, index2;
    for(int i = 0; i < used; i++)
    {
      if(tree[i] == a)
        index1 = i;
    }
    for(int i = 0; i < used; i++)
    {
      if(tree[i] == b)
        index2 = i;
    }
    tree[index1] = b;
    tree[index2] = a;
  }
  //member variables
  int used;
  int tree[capacity];
};

void heapify(BT& bt, int i)
{
  int largest = i;
  int left = 2*i + 1;
  int right = 2*i + 2;
  //if left child is larger than root
  if (left < bt.used && bt.tree[left] > bt.tree[largest]){
    largest = left;
  }
  //if right child is larger than largest so far
  if (right < bt.used && bt.tree[right] > bt.tree[largest]){
    largest = right;
  }
  //if largest is not root
  if (largest != i) {
    bt.swap(bt.tree[i], bt.tree[largest]);
    //recursively heapify affected sub-tree
    heapify(bt, largest);
  }
}

//function to build a Max-Heap from the given array
void buildHeap(BT& bt)
{
  //index of last non-leaf node
  int startIdx = (bt.used / 2) - 1;
  //reverse level order traversal from last non leaf node and heapify each node
  for (int i = startIdx; i >= 0; i--) {
      heapify(bt, i);
  }
}

//function to delete the root from Heap
void deleteRoot(BT& heap)
{
    int lastElement = heap.tree[heap.used - 1];
    heap.tree[0] = lastElement;
    heap.used--;
    buildHeap(heap);
}

int main()
{
  //building binary tree
  BT tree;
  tree.insert(4);
  tree.insert(2);
  tree.insert(6);
  tree.insert(1);
  tree.insert(9);
  tree.insert(3);
  tree.insert(5);
  tree.insert(7);
  tree.insert(8);
  cout << "Original Tree: ";
  tree.printTree();
  cout << endl;

  cout << "Max Heapified Tree: ";
  buildHeap(tree);
  tree.printTree();
  cout << endl;
  cout << endl;

  cout << "Deleting Root of Heap" << endl;
  deleteRoot(tree);
  cout << "New Max Heap: ";
  tree.printTree();
  cout << endl;
  cout << endl;

  cout << "Deleting Root of Heap" << endl;
  deleteRoot(tree);
  cout << "New Max Heap: ";
  tree.printTree();
  cout << endl;
  cout << endl;

  cout << "Inserting 10" << endl;
  tree.insert(10);
  buildHeap(tree);
  cout << "Max Heapified Tree: ";
  tree.printTree();
  cout << endl;

  return 0;
}
