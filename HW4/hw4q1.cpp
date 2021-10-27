#include <iostream>
#include <vector>
using namespace std;
//basic binary search tree class
class BST
{
public:
  BST(): data(0), left(NULL), right(NULL){}
  BST(int val): data(val), left(NULL), right(NULL) {}
  BST* insert(BST *root, int val)
  {
    if(root == NULL)
    {
      return new BST(val);
    }
    if(val > root->data)
    {
      root->right = insert(root->right, val);
    }
    else
    {
      root->left = insert(root->left, val);
    }
    return root;
  }

  int data;
  BST *left, *right;
};

//Function to print Postorder Traversal of the tree
void postorderTraversal(BST* root)
{
    if (root == NULL)
    {
      return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}

//store the node values in arr in sorted order
void inorderTraversal(BST* root, vector<int>& arr)
{
    if (root == NULL)
    {
      return;
    }
    inorderTraversal(root->left, arr);
    arr.push_back(root->data);
    inorderTraversal(root->right, arr);
}

void BSTToMaxHeap(BST* root, vector<int> arr, int& index)
{
    if (root == NULL)
    {
      return;
    }
    BSTToMaxHeap(root->left, arr, index);
    BSTToMaxHeap(root->right, arr, index);
    //copy data at index of arr to the BST
    root->data = arr[++index];
}

//Helper function to convert given BST to max heap
void convertToMaxHeapHelper(BST* root)
{
    //vector to store data of all nodes of the BST
    vector<int> arr;
    int index = -1;
    //inorder traversal to populate arr
    inorderTraversal(root, arr);
    //convert BST to max heap
    BSTToMaxHeap(root, arr, index);
}

int main()
{
    //BST formation
    cout << "Test 1" << endl;
    BST tree;
    BST* root = NULL;
    root = tree.insert(root, 4);
    tree.insert(root, 2);
    tree.insert(root, 6);
    tree.insert(root, 1);
    tree.insert(root, 9);
    tree.insert(root, 3);
    tree.insert(root, 5);
    tree.insert(root, 7);
    tree.insert(root, 8);
    cout << "Original Postorder Traversal of Tree:" << endl;
    postorderTraversal(root);
    cout << endl;
    convertToMaxHeapHelper(root);
    cout << "Postorder Traversal of Max Heap:" << endl;
    postorderTraversal(root);
    cout << endl;
    cout << endl;

    cout << "Test 2" << endl;
    BST tree2;
    BST* root2 = NULL;
    root2 = tree2.insert(root2, 8);
    tree2.insert(root2, 12);
    tree2.insert(root2, 5);
    cout << "Postorder Traversal of Tree:" << endl;
    postorderTraversal(root2);
    cout << endl;
    convertToMaxHeapHelper(root2);
    cout << "Postorder Traversal of Max Heap:" << endl;
    postorderTraversal(root2);
    cout << endl;
    tree2.insert(root2, 29);
    tree2.insert(root2, 31);
    tree2.insert(root2, 18);
    cout << "Postorder Traversal of Tree:" << endl;
    postorderTraversal(root2);
    cout << endl;
    convertToMaxHeapHelper(root2);
    cout << "Postorder Traversal of Max Heap:" << endl;
    postorderTraversal(root2);
    cout << endl;
    tree2.insert(root2, 33);
    tree2.insert(root2, 16);
    tree2.insert(root2, 2);
    cout << "Postorder Traversal of Tree:" << endl;
    postorderTraversal(root2);
    cout << endl;
    convertToMaxHeapHelper(root2);
    cout << "Postorder Traversal of Max Heap:" << endl;
    postorderTraversal(root2);
    cout << endl;

    return 0;
}
