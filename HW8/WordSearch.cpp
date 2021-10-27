/*
NOTE: My program takes really long to search for the words because the list of words is more than 48,000 words long and
the puzzle grid is 250x250 characters (excluding the spaces between each character) and I'm searching for the word at every
character in the grid until I find one that contains the word in any of the 8 directions. So in the case where the word is not
in the grid, I go through every character in the grid and check all 8 directions of that character.
You can try testing with files that have a smaller grid to get a faster result but my program will provide all the found words in
the puzzle if you give it a while.
I left comments throughout the program so you can understand my method of searching.
*/
#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include <unordered_set>
#include <fstream>

using namespace std;

//Rows and Columns in given puzzle
//to test different puzzles, change the dimensions of the grid here
#define R 250
#define C 250

// For searching in all 8 direction
int x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};

//Search in all 8 directions from point (row, col) in grid[][]
bool search2D(char grid[R][C], int row, int col, string word)
{
  //check if 1st character of word matches with given starting point in grid
  if (grid[row][col] != word[0])
  {
    return false;
  }
  int length = word.length();
  //search word in all 8 directions starting from (row,col)
  for (int dir = 0; dir < 8; dir++)
  {
    //initialize starting point for current direction
    int k;
    int rd = row + x[dir];
    int cd = col + y[dir];
    //check for characters after the first
    for (k = 1; k < length; k++)
    {
      // If out of bound break
      if (rd >= R || rd < 0 || cd >= C || cd < 0)
      {
        break;
      }
      //if not matched, break
      if (grid[rd][cd] != word[k])
      {
        break;
      }
      //continue moving in particular direction
      rd += x[dir], cd += y[dir];
    }
    //if all character matched then value of must be equal to length of word
    if (k == length)
    {
      return true;
    }
  }
  return false;
}

//search given word in a given matrix in all 8 directions
void patternSearch(char grid[R][C], string word)
{
  //consider every point as starting point and search for the given word
  for (int row = 0; row < R; row++)
  {
    for (int col = 0; col < C; col++)
    {
      if (search2D(grid, row, col, word))
      {
        cout << word << " found at " << "(" << row << ", "<< col << ")" << endl;
        return;
      }
    }
  }
}


int main()
{
  //create grid that contains the puzzle
  char grid[R][C];
  //name of file that contains the puzzle
  //(change this if you want to test a different puzzle as well as the dimensions of the grid at the top of the program)
  const string PUZZLE = "puzzle.txt";
  ifstream input;
  input.open(PUZZLE);
  string line;
  vector<char> rows[R];
  int index = 0;
  //putting each line in the puzzle file into a vector that contains only the characters
  //each of these vectors is 1 line of the file and each vector is placed in an array of vectors
  while(getline(input, line))
  {
    vector<char> v;
    for(int i = 0; i < line.length(); i++)
    {
      if(isalpha(line[i]))
      {
        v.push_back(line[i]);
      }
    }
    rows[index] = v;
    index++;
  }
  //converting the array of vectors into the grid
  for(int i = 0; i < R; i++)
  {
    vector<char> t = rows[i];
    for(int j = 0; j < C; j++)
    {
      grid[i][j] = t[j];
    }
  }
  input.close();

  //this is the name of the file that contains all the words that can possibly
  //be searched if they meet the minimum length requirement
  const string WORD_LIST = "words.txt";
  const int MIN_LENGTH = 6;
  unordered_set<string> dictionary;
  ifstream in;
  in.open(WORD_LIST);
  string temp;
  bool validWord = true;
  //making the dictionary of words we will search by opening the given file and
  //inserting words of the minimum length into an unordered set
  while(in >> temp)
  {
    if(temp.length() >= MIN_LENGTH)
    {
      for(int i = 0; i < temp.length(); i++)
      {
        if(!isalpha(temp[i]))
        {
          validWord = false;
        }
      }
      if(validWord)
      {
        dictionary.insert(temp);
      }
      validWord = true;
    }
  }
  in.close();

  //iterate through the dictionary and at each index, search for that word throughout the whole puzzle
  for (auto it = dictionary.begin(); it != dictionary.end(); ++it)
  {
    patternSearch(grid, *it);
  }

  return 0;
}
