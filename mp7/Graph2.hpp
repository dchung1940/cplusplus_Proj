#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
 #include <queue>
 #include <algorithm>
 #include <string>
 #include <list>

 /**
  * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
  *
  * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
  * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
  * be traveled along the shortest path.
  *
  * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
  *
  * @param start The key for the starting vertex.
  * @param end   The key for the ending vertex.
  */
 template <class V, class E>
 std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
   std::list<std::string> path;
   std::string min = start;
   std::string hold = min;
   std::string bef;
   std::unordered_map<std::string, std::pair<int, std::string>> info;
   std::unordered_map<std::string, bool> visit;
   std::list<E_byRef> adj;

   if (start == end)
     return path;
 // std::cout << "-- TESTING --" << std::endl;
 // std::cout << "Start:" << start << std::endl;
 // std::cout << "End:" << end << std::endl;
   for(auto v = vertexMap.begin(); v != vertexMap.end(); ++v)
   {
     info[v->first] = std::make_pair(INT_MAX, " ");
     visit[v->first] = false;
   }
   info[start].first = 0;

   for(unsigned int i=0; i<size(); i++)
   {
     // std::cout << std::endl << "pre: " << min << std::endl;
     bef = min;
  // std::cout << "Check Begin:------------------------" << std::endl;
     for(auto x=info.begin(); x!=info.end(); x++)
     {
    // std::cout << x->first << ": " << info[x->first].first << " | min: " <<min << ", " << info[min].first<< std::endl;
       if(!visit[x->first])
       {
         if(visit[min])
         {
           bef = min;
           min = x->first;
         }
         if(x->second.first < info[min].first)
         {
           bef = min;
           min = x->first;
         }
       }
     }
     // std::cout << "Check End:------------------------" << std::endl;
     visit[min] = true;
   // std::cout << "=== " << min << " ==="<< std::endl;
     adj = incidentEdges(min);
     bef = min;

     // std::cout << "IE: " << adj.begin()->get().source().key() << ", " << adj.begin()->get().dest().key() << std::endl;
     for(auto j = adj.begin(); j != adj.end(); j++)
     {
       std::string next = j->get().dest().key(); // Looking at current neighbor
       // std::cout << "Option 1: "  << j->get().dest().key() << std::endl;
       // std::cout << "Option 2: "  << j->get().source().key() << std::endl;
       // std::cout << "Next: "  << next << ", Min: " << min << std::endl;
       // std::cout << "TestNei 1: "  << next << std::endl;
       if(!j->get().directed()) // Indirected
         if(next == bef)
           next = j->get().source().key();
       // std::cout << "TestNei 2: "  << next << std::endl;
       if(!visit[next] || visit[next])
       {
         // std::cout << "Neigh - " << next << std::endl;
         int sum = info[bef].first+(int)j->get().weight(); // Insert new element
         // std::cout << next << "- " << info[next].first << ", " << sum << std::endl;
         if(sum < info[next].first)
         {
           std::pair<int,std::string> temp(sum, bef);
           info[next] = temp;
         }
         if(visit[min]) // Check if min is already visited
           min = next;
         if(info[next].first < info[min].first)
           min = next;
       }
       // info[min].second = bef;
     }
   }

   min = end;
   // std::cout << "-- Parents --" << std::endl;
   for(auto x=info.begin(); x!=info.end(); x++)
   {
     // std::cout << x->first << " | " << x->second.second << std::endl;
   }

   while(min != start)
   {
     // std::cout << "oops?" << std::endl;
     path.push_front(min);
     min = info[min].second;
   }
   path.push_front(start);

   return path;
 }
