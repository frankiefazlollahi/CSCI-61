#include <iostream>
#include <queue>
#include <chrono>
#include <ctime>
#include <map>
#include <set>
#include <fstream>
#include <vector>

using namespace std;

class Student
{
public:
  Student(): serviceTime(0), arrivalTime(0), urgency(1), name(""), topic("") {}
  Student(int t, int a, int u, string n, string top): serviceTime(t), arrivalTime(a), urgency(u), name(n), topic(top) {}
  double getServiceTime() const {return serviceTime;}
  int getArrivalTime() const {return arrivalTime;}
  int getUrgency() const {return urgency;}
  string getName() const {return name;}
  string getTopic() const {return topic;}
private:
  int serviceTime;
  int arrivalTime;
  int urgency;
  string name;
  string topic;
};

bool operator <(const Student& lhs, const Student& rhs);
bool operator >(const Student& lhs, const Student& rhs);
bool operator ==(const Student& lhs, const Student& rhs);
bool operator <=(const Student& lhs, const Student& rhs);
bool operator >=(const Student& lhs, const Student& rhs);

void maxHeapify(string topics[], string names[], int size, int i);
void ascendingHeapSort(string topics[], string names[], int size);
void minHeapify(string topics[], string names[], int size, int i);
void descendingHeapSort(string topics[], string names[], int size);
void sort(const string& in, char c);

bool searchStudent(const string& in, const string& studentName);
bool searchTopic(const string& in, const string& topicName);

string randomString();
void newArrivals(priority_queue<Student>& line, int& studentCount, const int timePassed, vector<string>& possibleStudents, ofstream& out, const int& sessionNum);
void helpStudent(priority_queue<Student>& line, int& timePassed, int waitTimes[], int& index, multimap<string, string>& map);
void runOfficeHours(const int officeTime, double& avgWaitTime, double& spentWithProf, double& overtime, multimap<string, string>& map, ofstream& out, const int& sessionNum);

//global list of all students in the class
const string studentList[30] = {"Student01", "Student02", "Student03", "Student04", "Student05", "Student06", "Student07",
"Student08", "Student09", "Student10", "Student11", "Student12", "Student13", "Student14", "Student15", "Student16",
"Student17", "Student18", "Student19", "Student20", "Student21", "Student22", "Student23", "Student24", "Student25",
"Student26", "Student27", "Student28", "Student29", "Student30"};

int main()
{

  multimap<string, string> map;

  const int officeTime = 60; //1 hour, 60 seconds in our program
  //variables to answer the questions to be passed into runOfficeHours()
  double avgWaitTime = 0;
  double spentWithProf = 0;
  double overtime = 0;
  //variables to get the total of each of the above variables
  double totAvgWaitTime = 0;
  double totAvgTimeSpentWithProf = 0;
  double totalOvertime = 0;
  //number of simulations
  int simulationCount = 100;
  srand(time(0));
  ofstream out;
  out.open("data.txt");
  for(int i = 0; i < simulationCount; i++)
  {
    runOfficeHours(officeTime, avgWaitTime, spentWithProf, overtime, map, out, i+1);
    //add to the total
    totAvgWaitTime += avgWaitTime;
    totAvgTimeSpentWithProf += spentWithProf;
    totalOvertime += overtime;
    //reset the variables
    avgWaitTime = 0;
    spentWithProf = 0;
    overtime = 0;
  }
  out.close();
  cout << "The average time a student spends waiting during an office hour visit: " << (totAvgWaitTime/simulationCount) << endl;
  cout << "The average time a student spends with the professor during an office hour visit: " << (totAvgTimeSpentWithProf/simulationCount) << endl;
  cout << "The average time a Professor spends at an office hour beyond the 1 hour he intended to: " << (totalOvertime/simulationCount) << endl;

  //outputting multimap contents to file

  ofstream output;
  output.open("StudentData.txt");
  multimap<string, string> :: iterator it;

  for(int i = 0; i < 30; i++)
  {
    int count = map.count(studentList[i]);
    output << studentList[i] << " came to office hours " << count << " times and they covered topics: ";
    for(it = map.begin(); it != map.end(); it++)
    {
      if(it->first == studentList[i])
      {
        output << it->second << " ";
      }
    }
    output << endl;
  }
  output.close();

  ofstream o;
  o.open("officeList.txt");
  multimap<string, string> :: iterator it2;
  for(it2 = map.begin(); it2 != map.end(); it2++)
  {
    o << it2->first << '\t' << it2->second << endl;
  }
  o.close();

  //takes in name of file that contains the data sorted by student name automatically because it is from the multimap
  string input = "officeList.txt";
  char c;
  //sort this file by topic instead of name in the ascending or descending order, determined by user input
  sort(input, c);

  //testing searching for Student07
  const string FILENAME = "data.txt";
  string name = "Student07";
  cout << "Searching for Student: " << name << "..." << endl;
  searchStudent(FILENAME, name);

  //testing searching for topic f
  string topic = "f";
  cout << "Searching for Topic: " << topic << "..." << endl;
  searchTopic(FILENAME, topic);

  return 0;
}

//Overloading < operator to work for comparing students so priority queue can function
bool operator <(const Student& lhs, const Student& rhs){
  return (lhs.getUrgency() < rhs.getUrgency());
}

//Additional overloading comparison operators to work for students
//Not needed for priority queue to function
bool operator >(const Student& lhs, const Student& rhs){
  return (lhs.getUrgency() > rhs.getUrgency());
}
bool operator ==(const Student& lhs, const Student& rhs){
  return (lhs.getUrgency() == rhs.getUrgency());
}
bool operator <=(const Student& lhs, const Student& rhs){
  return (lhs.getUrgency() <= rhs.getUrgency());
}
bool operator >=(const Student& lhs, const Student& rhs){
  return (lhs.getUrgency() >= rhs.getUrgency());
}
//helper function to heapify the topics array to a max heap
void maxHeapify(string topics[], string names[], int size, int i)
{
  int largest = i;
  int l = 2*i + 1;
  int r = 2*i + 2;
  if (l < size && topics[l] > topics[largest])
  {
    largest = l;
  }
  if (r < size && topics[r] > topics[largest])
  {
    largest = r;
  }
  if (largest != i)
  {
    swap(topics[i], topics[largest]);
    swap(names[i], names[largest]);
    maxHeapify(topics, names, size, largest);
  }
}
//function to heap sort in ascending order
void ascendingHeapSort(string topics[], string names[], int size)
{
  for (int i = size / 2 - 1; i >= 0; i--)
  {
    maxHeapify(topics, names, size, i);
  }
  for (int i = size - 1; i > 0; i--)
  {
    swap(topics[0], topics[i]);
    swap(names[0], names[i]);
    maxHeapify(topics, names, i, 0);
  }
}
//helper function to heapify the topics array to a min heap
void minHeapify(string topics[], string names[], int size, int i)
{
  int smallest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  if (l < size && topics[l] < topics[smallest])
  {
    smallest = l;
  }
  if (r < size && topics[r] < topics[smallest])
  {
    smallest = r;
  }
  if (smallest != i)
  {
    swap(topics[i], topics[smallest]);
    swap(names[i], names[smallest]);
    minHeapify(topics, names, size, smallest);
  }
}
//function to heap sort in descending order
void descendingHeapSort(string topics[], string names[], int size)
{
  for (int i = size / 2 - 1; i >= 0; i--)
  {
    minHeapify(topics, names, size, i);
  }
  for (int i = size - 1; i >= 0; i--)
  {
    swap(topics[0], topics[i]);
    swap(names[0], names[i]);
    minHeapify(topics, names, i, 0);
  }
}

//sorting by topic since the map already sorts by student name
void sort(const string& in, char c)
{
  //get user input to know whether to sort in ascending or descending order
  cout << "\nEnter 'a' to sort topics in ascending order or 'd' to sort topics in descending order\n";
  cin >> c;
  while(c != 'a' && c != 'd')
  {
    cout << "Error: User did not enter a valid order to sort.\n"
    << "(Enter 'a' to sort topics in ascending order or 'd' to sort topics in descending order)\n";
    cin >> c;
  }
  //putting all the topics and names from the file into their separate arrays
  ifstream input;
  input.open(in);
  string topics[2000];
  string names[2000];
  int index = 0;
  while(input >> names[index])
  {
    input >> topics[index];
    index++;
  }
  input.close();
  //sort by ascending order if user entered a
  if(c == 'a')
  {
    ascendingHeapSort(topics, names, index);
  }
  //sort by descending order if user entered d
  else if(c == 'd')
  {
    descendingHeapSort(topics, names, index);
  }
  //putting the sorted contents into a file
  ofstream out;
  out.open("SortedTopics.txt");
  for(int i = 0; i < index; i++)
  {
    out << topics[i] << " " << names[i] << endl;
  }
  out.close();
  cout << "Sorting successful, check SortedTopics.txt file." << endl;
  cout << endl;
}

bool searchStudent(const string& filename, const string& studentName)
{
  bool found = false;
  //maximum of 100 because its only possible for the student to arrive 100 times
  string topics[100];
  int sessions[100];
  ifstream input;
  input.open(filename);
  string temp;
  string next;
  int next2;
  int i = 0;
  while(input >> temp)
  {
    if(temp == studentName)
    {
      found = true;
      input >> next;
      topics[i] = next;
      input >> next2;
      sessions[i] = next2;
      i++;
    }
  }
  input.close();
  if(found)
  {
    cout << studentName << "'s Data:" << endl;
    for(int j = 0; j < i; j++)
    {
      cout << "Topic: " << topics[j] << "     Office Hour Session: " << sessions[j] << endl;
    }
    cout << endl;
  }
  else
  {
    cout << studentName << " did not come to any office hour session." << endl;
  }
  cout << endl;
  return found;
}

bool searchTopic(const string& filename, const string& topicName)
{
  bool found = false;
  string names[2000];
  int sessions[2000];
  ifstream input;
  input.open(filename);
  string temp;
  string next;
  int next2;
  int i = 0;
  while(input >> temp)
  {
    input >> next;
    if(next == topicName)
    {
      found = true;
      names[i] = temp;
      input >> next2;
      sessions[i] = next2;
      i++;
    }
  }
  input.close();
  if(found)
  {
    cout << "Data of Topic " << topicName << ":" << endl;
    for(int j = 0; j < i; j++)
    {
      cout << "Student: " << names[j] << "     Office Hour Session: " << sessions[j] << endl;
    }
    cout << endl;
  }
  else
  {
    cout << "No students asked about " << topicName << endl;
  }
  cout << endl;
  return found;
}


bool searchTopic();

//generates a random topic
string randomString()
{
  //srand(time(0));
  string topics[20] = { "a", "b", "c", "d", "e", "f", "g",
                        "h", "i", "j", "k", "l", "m", "n",
                        "o", "p", "q", "r", "s", "t"};
  string str = topics[(rand()%20)];
  return str;
}

//0 to 5 new students arrive
//student's service time is 1 to 15 min
void newArrivals(priority_queue<Student>& line, int& studentCount, const int timePassed, vector<string>& possibleStudents, ofstream& out, const int& sessionNum)
{
  int arrived = (rand() % 5+1);
  for(int i = 0; i < arrived; i++)
  {
    int t = (rand()%(possibleStudents.size()));
    string temp = possibleStudents[t];
    Student s = Student((rand() % 15 + 1), timePassed, (rand() % 5 + 1), temp, randomString());
    line.push(s);
    out << s.getName() << " " << s.getTopic() << " " << sessionNum << endl;
    studentCount++;
    //remove this student from the possible students who can come to office hours since they already came during this day
    possibleStudents.erase(possibleStudents.begin()+t);
    if(possibleStudents.empty())
    {
      break;
    }
  }
}
//student is helped, the time passes, and they are removed from the queue
void helpStudent(priority_queue<Student>& line, int& timePassed, int waitTimes[], int& index, multimap<string, string>& map)
{
  map.insert(pair<string, string> (line.top().getName(), line.top().getTopic()));
  waitTimes[index] = timePassed - (line.top()).getArrivalTime();
  index++;
  timePassed += (line.top()).getServiceTime();
  line.pop();
}

void runOfficeHours(const int officeTime, double& avgWaitTime, double& spentWithProf, double& overtime, multimap<string, string>& map, ofstream& out, const int& sessionNum)
{
  vector<string> possibleStudents;
  for(int i = 0; i < 30; i++)
  {
    possibleStudents.push_back(studentList[i]);
  }
  //storing how long each student waits in an array
  int waitTimes[100];
  int index = 0;
  int studentCount = 0;
  priority_queue<Student> line;
  int timePassed = 0;

  //The first student has arrived at the beginning of office hours.
  int t = (rand()%(possibleStudents.size()));
  string temp = possibleStudents[t];
  Student firstStudent((rand() % 10 + 1), 0, (rand() % 5 + 1), temp, randomString());
  out << firstStudent.getName() << " " << firstStudent.getTopic() << " " << sessionNum << endl;
  possibleStudents.erase(possibleStudents.begin()+t);
  studentCount++;
  line.push(firstStudent);
  //first student is helped
  helpStudent(line,timePassed, waitTimes, index, map);
  //cout << "t";
  //if 10 minutes has passed, new people have arrived and the next student is helped
  if(timePassed >= 10)
  {
    newArrivals(line, studentCount, timePassed, possibleStudents, out, sessionNum);
    helpStudent(line,timePassed,waitTimes, index, map);
  }
  //if less than 10 minutes has passed, time passes until it is 10 minutes
  else
  {
    timePassed = 10;
  }
  //students continue to arrive and are helped as long as the Professor has not been in office hours for an hour and not all the students came to office hours.
  while(timePassed <= officeTime && !possibleStudents.empty())
  {
    int prevTime = timePassed;
    //if the time has not reached the next 10 min point, help the next student
    while((timePassed < prevTime + 10 - (prevTime % 10)) && !line.empty())
    {
      helpStudent(line,timePassed,waitTimes, index, map);
      prevTime = timePassed;
    }
    //if everyone has been helped and time has still not reached the next 10 min point, time passes to the next 10 min point
    if(line.empty())
    {
      if(timePassed == 10)
      {
        newArrivals(line, studentCount, timePassed, possibleStudents, out, sessionNum);
      }
      else
        timePassed = prevTime + 10 - (prevTime % 10);
    }
    //otherwise help the next student and new people arrive
    if(timePassed == 60)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index, map);
      }
      newArrivals(line, studentCount,timePassed, possibleStudents, out, sessionNum);
      break;
    }
    else if(timePassed >= 50)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index, map);
      }
      newArrivals(line, studentCount,timePassed, possibleStudents, out, sessionNum);
    }
    else if(timePassed >= 40)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index, map);
      }
      newArrivals(line, studentCount,timePassed, possibleStudents, out, sessionNum);
    }
    else if(timePassed >= 30)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index, map);
      }
      newArrivals(line, studentCount,timePassed, possibleStudents, out, sessionNum);
    }
    else if(timePassed >= 20)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index, map);
      }
      newArrivals(line, studentCount,timePassed, possibleStudents, out, sessionNum);
    }
    else if(timePassed >= 10)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index, map);
      }
      newArrivals(line, studentCount,timePassed, possibleStudents, out, sessionNum);
    }
  }

  //if there are still more students after scheduled office hours, the professor helps them
  while(!line.empty())
  {
    helpStudent(line,timePassed,waitTimes, index, map);
  }
  //for Question 1 (average time student is waiting)
  for(int j = 0; j < index; j++)
  {
    avgWaitTime += waitTimes[j];
  }
  avgWaitTime /= studentCount;

  //for Question 2 (average time with the professor)
  spentWithProf = ((double)timePassed / studentCount);

  //for Question 3 (total overtime)
  overtime = ((double)timePassed - 60);
  //empty the vector
  possibleStudents.clear();
}
