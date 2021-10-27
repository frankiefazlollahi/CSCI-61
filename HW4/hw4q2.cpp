#include <iostream>
#include <queue>
#include <chrono>
#include <ctime>

using namespace std;

class Student
{
public:
  Student(): serviceTime(0), arrivalTime(0), urgency(1) {}
  Student(int t, int a, int u): serviceTime(t), arrivalTime(a), urgency(u){}
  double getServiceTime() const {return serviceTime;}
  int getArrivalTime() const {return arrivalTime;}
  int getUrgency() const {return urgency;}
private:
  int serviceTime;
  int arrivalTime;
  int urgency;
};
bool operator <(const Student& lhs, const Student& rhs);
bool operator >(const Student& lhs, const Student& rhs);
bool operator ==(const Student& lhs, const Student& rhs);
bool operator <=(const Student& lhs, const Student& rhs);
bool operator >=(const Student& lhs, const Student& rhs);

void newArrivals(queue<Student>& line, int& studentCount, const int timePassed);
void helpStudent(queue<Student>& line, int& timePassed, int*& waitTimes, int& index);
void runOfficeHours(const int officeTime, double& avgWaitTime, double& spentWithProf, double& overtime);

int main()
{
  srand(time(0));
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
    runOfficeHours(officeTime, avgWaitTime, spentWithProf, overtime);
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

//0 to 5 new students arrive
//student's service time is 1 to 15 min
void newArrivals(priority_queue<Student>& line, int& studentCount, const int timePassed)
{
  srand(time(0));
  int arrived = (rand() % 6);
  for(int i = 0; i < arrived; i++)
  {
    Student s = Student((rand() % 15 + 1), timePassed, (rand() % 5 + 1));
    line.push(s);
    studentCount++;
  }
}
//student is helped, the time passes, and they are removed from the queue
void helpStudent(priority_queue<Student>& line, int& timePassed, int*& waitTimes, int& index)
{
  waitTimes[index] = timePassed - (line.top()).getArrivalTime();
  index++;
  timePassed += (line.top()).getServiceTime();
  line.pop();
}

void runOfficeHours(const int officeTime, double& avgWaitTime, double& spentWithProf, double& overtime)
{
  //storing how long each student waits in an array
  int* waitTimes = new int[100];
  int index = 0;

  int studentCount = 0;
  priority_queue<Student> line;
  int timePassed = 0;
  //The first student has arrived at the beginning of office hours.
  Student firstStudent((rand() % 10 + 1), 0, (rand() % 5 + 1));
  studentCount++;
  line.push(firstStudent);
  //first student is helped
  helpStudent(line,timePassed, waitTimes, index);
  //if 10 minutes has passed, new people have arrived and the next student is helped
  if(timePassed >= 10)
  {
    newArrivals(line, studentCount, timePassed);
    helpStudent(line,timePassed,waitTimes, index);
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
      helpStudent(line,timePassed,waitTimes, index);
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
        helpStudent(line,timePassed,waitTimes, index);
      }
      newArrivals(line, studentCount,timePassed);
      break;
    }
    else if(timePassed >= 50)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index);
      }
      newArrivals(line, studentCount,timePassed);
    }
    else if(timePassed >= 40)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index);
      }
      newArrivals(line, studentCount,timePassed);
    }
    else if(timePassed >= 30)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index);
      }
      newArrivals(line, studentCount,timePassed);
    }
    else if(timePassed >= 20)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index);
      }
      newArrivals(line, studentCount,timePassed);
    }
    else if(timePassed >= 10)
    {
      if(!line.empty())
      {
        helpStudent(line,timePassed,waitTimes, index);
      }
      newArrivals(line, studentCount,timePassed);
    }
  }
  //if there are still more students after scheduled office hours, the professor helps them
  while(!line.empty())
  {
    helpStudent(line,timePassed,waitTimes, index);
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
