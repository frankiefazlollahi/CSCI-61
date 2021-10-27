#include "set.h"

using namespace std;
using namespace main_savitch_11;

int main()
{
  set<int> set1;
  set1.insert(10);
  cout<<"Elements in set1 are:" << endl;
  set1.print(2);

  cout<<"\nAdding more elements..." << endl;
  set1.insert(28);
  set1.insert(2);
  set1.insert(5);
  set1.insert(16);
  set1.insert(19);
  set1.insert(0);
  set1.insert(1);
  set1.insert(3);
  set1.insert(4);
  cout<<"\nElements in set1 are now:" << endl;
  set1.print(2);

  cout<<"\nAdding more elements..." << endl;
  set1.insert(6);
  set1.insert(7);
  set1.insert(8);
  set1.insert(14);
  set1.insert(15);
  set1.insert(17);
  set1.insert(18);
  set1.insert(20);
  set1.insert(21);
  cout<<"\nElements in set1 are now:" << endl;
  set1.print(2);

  cout<<"\nAdding more elements..." << endl;
  set1.insert(33);
  set1.insert(40);
  set1.insert(31);
  set1.insert(32);
  set1.insert(34);
  set1.insert(35);
  cout<<"\nElements in set1 are:" << endl;
  set1.print(2);

  cout<<"\nElements in set1 after erasing 14 are:" << endl;
  set1.erase(14);
  set1.print(2);

  cout<<"\nElements in set1 after erasing 34 are:" << endl;
  set1.erase(34);
  set1.print(2);

  cout<<"\nElements in set1 after erasing 10 are:" << endl;
  set1.erase(10);
  set1.print(2);

  set<int> set2;
  set2 = set1;
  cout<<"\nSet2 is a copy of the set1:" << endl;
  cout<<"\nElements in set2 are:" << endl;
  set2.print(3);

  cout<<"\nElements in set2 after insertion of 100 are:" << endl;
  set2.insert(100);
  set2.print(3);

  cout<<"\nElements in set1 are:" << endl;
  set1.print(2);

  cout <<"\nThe set1 is now equal to set2.";
  cout<<"\nElements in original set are:" << endl;
  set1 = set2;
  set1.print(2);

  cout << "Is 100 present in set1? ";
  if(set1.count(100) == 0)
    cout << "100 is not present." << endl;
  else
    cout << "100 is present." << endl;

  cout << "Is 10 present in set1? ";
  if(set1.count(10) == 0)
    cout << "10 is not present." << endl;
  else
    cout << "10 is present." << endl;

}
