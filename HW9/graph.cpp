// FILE: graph.template (part of the namespace main_savitch_15)
// TEMPLATE CLASS IMPLEMENTED: graph<Item> (See graph.h for documentation.)
// This file is included in the header file and not compiled separately.
// INVARIANT for the graph class:
//   1. The number of vertices in the graph is stored in the member variable
//      many_vertices.
//   1. These vertices are numbered from 0 to many_vertices-1.
//   2. edges is the adjacency matrix for the graph (with true in edges[i][j]
//      to indicate an edge from vertex i to vertex j).
//   3. For each i < many_vertices, labels[i] is the label of vertex i.

#include <cassert>    // Provides assert
#include <cstdlib>    // Provides size_t
#include <set>        // Provides set

namespace main_savitch_15
{
    template <class Item>
    const std::size_t graph<Item>::MAXIMUM;

    template <class Item>
    void graph<Item>::add_edge(std::size_t source, std::size_t target)
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        edges[source][target] = true;
    }

    template <class Item>
    void graph<Item>::add_vertex(const Item& label)
    // Library facilities used: cassert, cstdlib
    {
        std::size_t new_vertex_number;
        std::size_t other_number;

        assert(size( ) < MAXIMUM);
        new_vertex_number = many_vertices;
        many_vertices++;
        for (other_number = 0; other_number < many_vertices; ++other_number)
        {
            edges[other_number][new_vertex_number] = false;
            edges[new_vertex_number][other_number] = false;
        }
        labels[new_vertex_number] = label;
    }

    template <class Item>
    bool graph<Item>::is_edge(std::size_t source, std::size_t target) const
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        return edges[source][target];
    }

    template <class Item>
    Item& graph<Item>::operator[ ] (std::size_t vertex)
    // Library facilities used: cassert, cstdlib
    {
        assert(vertex < size( ));
        return labels[vertex];     // Returns a reference to the label
    }

    template <class Item>
    Item graph<Item>::operator[ ] (std::size_t vertex) const
    // Library facilities used: cassert, cstdlib
    {
        assert(vertex < size( ));
        return labels[vertex];     // Returns only a copy of the label
    }

    template <class Item>
    std::set<std::size_t> graph<Item>::neighbors(std::size_t vertex) const
    // Library facilities used: cassert, cstdlib, set
    {
        std::set<std::size_t> answer;
        std::size_t i;

        assert(vertex < size( ));

        for (i = 0; i < size( ); ++i)
        {
            if (edges[vertex][i])
                answer.insert(i);
        }
        return answer;
    }

    template <class Item>
    void graph<Item>::remove_edge(std::size_t source, std::size_t target)
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        edges[source][target] = false;
    }
    //using modified version of Dijkstra's algorithm to find longest path instead of shortest based on the textbook
    template<class Item>
    int graph<Item>::longest_distance(Item source, Item target)
    {
      //finding the index of the source by traversing through labels[]
      int start = -1;
      for(int i = 0; i < many_vertices; i++)
      {
        if(labels[i] == source)
        {
          start = i;
          break;
        }
      }
      //if the source is not contained in labels return -1
      if(start == -1)
      {
        return -1;
      }
      //make array to keep track of the distances, and set the distance of the source to 0
      int distance[many_vertices];
      distance[start] = 0;
      //setting the distances of the other vertices to negative infinity
      for(int i = start+1; i < many_vertices; i++)
      {
        distance[i] = INT_MIN;
      }
      //set to contain the vertices we are currently allowing
      std::set<int> allowed_vertices;
      //n is number of vertices
      int n = many_vertices;
      //finding the index of the next smallest distance of a verticy to put into the set
      for(int allowed_size = start+1; allowed_size <= n; allowed_size++)
      {
        int smallest = INT_MAX;
        int next = 1;
        for(int i = 1; i < many_vertices; i++)
        {
          if(allowed_vertices.count(i) > 0)
          {
            if(smallest >= distance[i])
            {
              smallest = distance[i];
              next = i;
            }
          }
        }
        allowed_vertices.insert(next);
        //revise the distance array so the new vertex (next) may appear on permitted paths
        for(int v = 0; v < n; ++v)
        {
          if(allowed_vertices.count(v)==0 && is_edge(next, v))
          {
            int sum = -1*(distance[next] + 1);
            if(sum < (-1*distance[v]))
            {
              distance[v] = sum;
            }
          }
        }
      }
      //getting index of the target
      int index = -1;
      for(int i = 0; i < many_vertices; i++)
      {
        if(labels[i] == target)
        {
          index = i;
        }
      }
      //return its distance
      if(index != -1)
      {
        return distance[index];
      }
      //if the target is not found, then return -1
      else
      {
        return index;
      }
    }
}
