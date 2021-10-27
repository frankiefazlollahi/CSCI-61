/*
Whoever is peer reviewing this, can you please try to find out why only a few of the students come to office hours.
Ive been testing different things for hours but nothing I do seems to make this work properly. My program has worked
perfectly fine in the other 2 assignments it was used for so I'm not sure what's causing the problem. If I had to guess
it would be something to do with my newArrivals function because I think it might be creating the same student multiple times.
Thanks in advance :)
*/
#include <iostream>
#include <queue>
#include <chrono>
#include <ctime>
#include <map>
#include <set>
#include <fstream>

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
//pair class that holds the count of amount of times a student has come to office hours
//and has a set which is a list of the topics they covered
class Pair{
public:
  Pair(): count(0) {}
  Pair(int c): count(c) {}
  void increaseCount() {count++;}
  int count;
  set<string> topics;
};

bool operator <(const Student& lhs, const Student& rhs);
bool operator >(const Student& lhs, const Student& rhs);
bool operator ==(const Student& lhs, const Student& rhs);
bool operator <=(const Student& lhs, const Student& rhs);
bool operator >=(const Student& lhs, const Student& rhs);

string randomString();
void newArrivals(priority_queue<Student>& line, int& studentCount, const int timePassed);
void helpStudent(priority_queue<Student>& line, int& timePassed, int*& waitTimes, int& index, multimap<string, Pair>& map);
void runOfficeHours(const int officeTime, double& avgWaitTime, double& spentWithProf, double& overtime, multimap<string, Pair>& map);

//global list of all students in the class
const string studentList[30] = {"Student01", "Student02", "Student03", "Student04", "Student05", "Student06", "Student07",
"Student08", "Student09", "Student10", "Student11", "Student12", "Student13", "Student14", "Student15", "Student16",
"Student17", "Student18", "Student19", "Student20", "Student21", "Student22", "Student23", "Student24", "Student25",
"Student26", "Student27", "Student28", "Student29", "Student30"};

int main()
{
  srand(time(0));
  multimap<string, Pair> map;
  //adding all the students in the list to multimap
  for(int i = 0; i < 30; i++)
  {
    map.insert(pair <string, Pair> (studentList[i], Pair(0)));
  }

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
  for(int i = 0; i < simulationCount; i++)
  {
    runOfficeHours(officeTime, avgWaitTime, spentWithProf, overtime, map);
    //add to the total
    totAvgWaitTime += avgWaitTime;
    totAvgTimeSpentWithProf += spentWithProf;
    totalOvertime += overtime;
    //reset the variables
    avgWaitTime = 0;
    spentWithProf = 0;
    overtime = 0;
  }
  cout << "The average time a student spends waiting during an office hour visit: " << (totAvgWaitTime/simulationCount) << endl;
  cout << "The average time a student spends with the professor during an office hour visit: " << (totAvgTimeSpentWithProf/simulationCount) << endl;
  cout << "The average time a Professor spends at an office hour beyond the 1 hour he intended to: " << (totalOvertime/simulationCount) << endl;

  //outputting multimap contents to file
  ofstream output;
  output.open("output.txt");
  multimap<string, Pair> :: iterator it;
  for(it = map.begin(); it != map.end(); ++it)
  {
    output << it->first << " came to office hours " << it->second.count << " times and covered ";
    for (set<string>::iterator it2 = it->second.topics.begin(); it2!=it->second.topics.end(); it2++)
    {
      output << *it2 << " ";
    }
    output << endl;
  }
  output.close();

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
void newArrivals(priority_queue<Student>& line, int& studentCount, const int timePassed)
{
  //srand(time(0));
  int arrived = (rand() % 6);
  for(int i = 0; i < arrived; i++)
  {
    //srand(time(0));
    Student s = Student((rand() % 15 + 1), timePassed, (rand() % 5 + 1), studentList[(rand() % 30)], randomString());
    line.push(s);
    studentCount++;
  }
}
//student is helped, the time passes, and they are removed from the queue
void helpStudent(priority_queue<Student>& line, int& timePassed, int*& waitTimes, int& index, multimap<string, Pair>& map)
{
  //increasing the amount of times this student has come to office hours by 1, in the map
  map.find((line.top()).getName())->second.count++;
  //inserting this student's topic into their list of topics, in the map
  map.find((line.top()).getName())->second.topics.insert((line.top()).getTopic());
  waitTimes[index] = timePassed - (line.top()).getArrivalTime();
  index++;
  timePassed += (line.top()).getServiceTime();
  line.pop();
}

void runOfficeHours(const int officeTime, double& avgWaitTime, double& spentWithProf, double& overtime, multimap<string, Pair>& map)
{
  //storing how long each student waits in an array
  int* waitTimes = new int[100];
  int index = 0;

  int studentCount = 0;
  priority_queue<Student> line;
  int timePassed = 0;
  //srand(time(0));
  //The first student has arrived at the beginning of office hours.
  Student firstStudent((rand() % 10 + 1), 0, (rand() % 5 + 1), studentList[(rand() % 30)], randomString());
  studentCount++;
  line.push(firstStudent);
  //first student is helped
  helpStudent(line,timePassed, waitTimes, index, map);
  //if 10 minutes has passed, new people have arrived and the next student is helped
  if(timePassed >= 10)
  {
    newArrivals(line, studentCount, timePassed);
    helpStudent(line,timePassed,waitTimes, index, map);
  }
  //if less than 10 minutes has passed, time passes until it is 10 minutes
  else
  {
    timePassed = 10;
  }
  //students continue to arrive and are helped as long as the Professor has not been in office hours for an hour
  while(timePassed <= officeTime)
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
        newArrivals(line, studentCount, timePassed);
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
      newArrivals(line, studentCount,timePassed);
      break;
    }
    else if(timePassed >= 50)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index, map);
      }
      newArrivals(line, studentCount,timePassed);
    }
    else if(timePassed >= 40)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index, map);
      }
      newArrivals(line, studentCount,timePassed);
    }
    else if(timePassed >= 30)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index, map);
      }
      newArrivals(line, studentCount,timePassed);
    }
    else if(timePassed >= 20)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index, map);
      }
      newArrivals(line, studentCount,timePassed);
    }
    else if(timePassed >= 10)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index, map);
      }
      newArrivals(line, studentCount,timePassed);
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
  delete[] waitTimes;
  avgWaitTime /= studentCount;

  //for Question 2 (average time with the professor)
  spentWithProf = ((double)timePassed / studentCount);

  //for Question 3 (total overtime)
  overtime = ((double)timePassed - 60);

}
