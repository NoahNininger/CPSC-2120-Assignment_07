#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type
unordered_map<string, bool> visited;
unordered_map<string, string> predecessor;
unordered_map<string, int> dist;  // distance
unordered_map<string, vector<string>> neighboringNode;

//Implement breadth-first search, refer to Lab 10

// helper function that uses recursion to find path
int findPath(string start, string end,vector<string> &path)
{
 // ensures last node has a predecessor
  if (predecessor.find(end) == predecessor.end())
    { return 0; }

  if (start.compare(end) != 0)
  {
   // recursion
    int step = 1 + findPath(start, predecessor[end], path);
    path.push_back(end);
    return step;
  }
  else
  {
    path.push_back(end);
    return 0;
  }
}

// helper function to build graph
void buildGraph(void)
{
  ifstream in ("wordlist05.txt");
  string current;

  while (in >> current)
    { V.push_back(current); }

  for (auto word : V)
  {
    for (long unsigned int i = 0; i < word.length(); i++)
    {
      for (char j = 'a'; j <= 'z'; j++)
      {
        if (j == word.at(i))
          { continue; }

        string current = word;
        current.at(i) = j;
        neighboringNode[word].push_back(current);
      }
    }
  }
}


void wordLadder(string s, string t, int &steps, vector<string> &path)
{
  //Implement this function
  buildGraph();  // builds graph

  queue<string> visitQueue;   // creates a queue for words to visit
  visitQueue.push(s);

  visited[s] = true;  // initializes the boolean to instanciate a visited word
  dist[s] = 0;  // initializes the distance to 0

  while (!visitQueue.empty())
  {
    string current = visitQueue.front();
    visitQueue.pop();

    for (string node : neighboringNode[current])
    {
     // if the node needs to be visited
      if (!visited[node])
      {
        predecessor[node] = current;
        dist[node] = 1 + dist[current];
        visited[node] = true;
        visitQueue.push(node);
      }
    }
  }

  steps = findPath(s, t, path);  // recursive helper
}

/*
int main(void)
{
  int steps = 0;
  string s, t;
  vector<string> path;
  
  cout << "Source: ";
  cin >> s;

  cout << "Target: ";
  cin >> t;

  wordLadder(s, t, steps, path);

  if (steps == 0)
  {
      cout << "No path!\n";
  }
  else
  {
      cout << "Steps: " << steps << "\n\n";
      for (int i=0; i<path.size(); i++)
      {
          cout << path[i] << endl;
      }
  }
  return 0;
}
*/
