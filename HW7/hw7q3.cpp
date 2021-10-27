#include <iostream>
using namespace std;

void insertionSort(int arr[], int size)
{
  int i;
  int j;
  int key;
  for (i = 1; i < size; i++)
  {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key)
    {
      arr[j+1] = arr[j];
      j = j - 1;
    }
    arr[j+1] = key;
  }
}

void print(int arr[], int size)
{
  int i;
  for (i = 0; i < size; i++)
    cout << arr[i] << " ";
  cout << endl;
}

int main()
{
  //you can make a new array or change the values to test other scenarios
  int arr[8] = {21, 7, 12, 41, 2, 38, 19, 25};
  int size = 8;
  cout << "Original Array: " << endl;
  print(arr,size);
  insertionSort(arr, size);
  cout << "Array after Merge Sort: " << endl;
  print(arr, size);

  return 0;
}
