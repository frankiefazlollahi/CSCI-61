#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <assert.h>
#include <queue>

using namespace std;
//Graph Class (using code from the provided graph.h class, I added the shortest_path function)
class Graph
{
public:
  Graph() {};
  //returns number of vertices
  int n()
  {
    return _v.size();
  }
  void add_vertex()
  {
    _v.push_back(list<int>());
  }
  void add_edge(int a, int b)
  {
    assert(a < n() && b < n());
    if (!is_edge(a, b))
    {
      _v[a].push_front(b);
      _v[b].push_front(a);
    }
  }
  bool is_edge(int a, int b)
  {
    if(a >= n() || b >= n())
    {
      return false;
    }
    for(auto e: _v[a])
    {
      if(e == b)
      {
        return true;
      }
    }
    return false;
  }
  //returns a path from source to dest with the least number of edges in this graph using bfs
  list<int> shortest_path(int start, int end)
  {
    //vector to hold parents
    vector<int> parent(n(),-1);

    bfs(start,parent);
    //if no answer found
    if(parent[end] == -1)
    {
      cout << "None";
      return list<int>();
    }
    //create answer list by tracing back parents from end word
    list<int> answer;
    list<int>::iterator it;
    for(int v = end; v!=start; v=parent[v])
    {
      answer.push_front(v);
    }
    answer.push_front(start);
    return answer;
  }
private:
  //adjacency list graph
  vector<list<int>> _v;
  //bfs traversal
  void bfs(int start, vector<int> &parent)
  {
    queue<int> vertex_num;
    vertex_num.push(start);
    parent[start] = start;
    while (!vertex_num.empty())
    {
      int current = vertex_num.front();
      vertex_num.pop();
      for (auto e:_v[current])
      {
        if(parent[e] == -1)
        {
          parent[e] = current;
          vertex_num.push(e);
        }
      }
    }
  }
};

//class that solves doublet puzzles of length 5
class DoubletPuzzle
{
public:
  DoubletPuzzle() {};
  //building the graph from the words in the dictionary
  void buildDictionary(string dict)
  {
    ifstream input(dict);
    string line;
    cout << "One moment please, building dictionary...\n" << endl;
    while(getline(input,line))
    {
      if(line.length() != 0)
      {
        graph.add_vertex();
        dictionary.push_back(line);
      }
    }
    input.close();

    string word1;
    string word2;
    //add edges to graph for words that have 4 common characters
    for(int i = 0; i < dictionary.size(); i++)
    {
      word1 = dictionary[i];
      for(int j = i; j < dictionary.size(); j++)
      {
        word2 = dictionary[j];
        if(commonChars(word1, word2) == 4)
        {
          graph.add_edge(i,j);
        }
      }
    }
  }
  //solves the doublet puzzle given the start and end words
  void solve(string start, string end)
  {
    int index1;
    int index2;
    //finding index of starting word
    for(int i = 0; i < dictionary.size(); i++)
    {
      if(start == dictionary[i])
      {
        index1 = i;
      }
    }
    //finding index of ending word
    for(int i = 0; i < dictionary.size(); i++)
    {
      if(end == dictionary[i])
      {
        index2 = i;
      }
    }
    //use bfs to find shortest path between the starting and ending words, then print the answer
    cout << "Doublet Puzzle from: " << start << " to " << end << ":" << endl;
    list <int> answer = graph.shortest_path(index1, index2);
    list <int>::iterator it;
    for(it = answer.begin(); it!= answer.end(); it++)
    {
      cout << dictionary[*it] << " ";
    }
    cout << endl;
  }
private:
  Graph graph;
  vector<string> dictionary;
  //returns number of characters two words have in common
  int commonChars(string string1, string string2)
  {
    int matches = 0;
    //count matching characters in strings of length 5
    for(int i=0; i < 5; i++)
    {
      if (string1[i] == string2[i])
      {
        matches++;
      }
    }
    return matches;
  }
};


int main()
{
  DoubletPuzzle puzzle;
  //name of dictionary file to use
  string const DICTIONARY = "knuth.txt";
  puzzle.buildDictionary(DICTIONARY);

  puzzle.solve("black", "white");
  cout << endl;
  puzzle.solve("tears", "smile");
  cout << endl;
  puzzle.solve("small", "giant");
  cout << endl;
  puzzle.solve("stone", "money");
  cout << endl;
  puzzle.solve("angel", "devil");
  cout << endl;
  puzzle.solve("amino", "right");
  cout << endl;
  puzzle.solve("amigo", "signs");
  cout << endl;

  return 0;
}
