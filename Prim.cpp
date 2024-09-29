#include <bits/stdc++.h>
using namespace std;

#define non '/'

#define Priority_Queue  priority_queue<pair<int,char>, vector<pair<int,char>>,greater<pair<int,char>>>
#define adjancentlist   unordered_map<char, vector<pair<char, int>>>
#define LIST            unordered_set<pair<char,char>, pair_hash>
#define Vector          vector<int>

#define Pair            pair<char,char> 
#define u               first
#define v               second


//custom hash function for `pair<char,char>` cause C++ dont have defualt one.
struct pair_hash {
    size_t operator()(const pair<char, char>& p) const {
        size_t h1 = hash<char>()(p.first);
        size_t h2 = hash<char>()(p.second);
        return h1 ^ (h2 << 1);     
    }
};







bool cycleExist(LIST & visited_edge, Pair edge) {
    return visited_edge.find( {edge.u, edge.v} ) != visited_edge.end(); //edge is already taken!!        
}

LIST Prim(adjancentlist & G, char &start) {
    LIST MST;
    Vector vertex_weight(10000, 1000);


    LIST       visited_edge;
    set<char>  visited_node;
        
    
    Priority_Queue Q; 
    Q.push( {100, start} );
    
    Pair min_edge;
    
    while ( !Q.empty() ) {
        auto [current_weight, current_node] = Q.top();
        Q.pop();

        if ( visited_node.find(current_node) != visited_node.end() ) continue;

        min_edge = {non, non};

        for (const auto &[neibour, neibour_weight] : G[current_node]) {
            if ( cycleExist(visited_edge, {current_node, neibour}) ) continue;

            if (vertex_weight[neibour] > neibour_weight) {
                vertex_weight[neibour] = neibour_weight;
                min_edge = {current_node, neibour};
            }
            
            //push the node if only its not visited.
            if ( visited_node.find(neibour) == visited_node.end() ) Q.push( {neibour_weight, neibour} );
        }
      
        //we insert visited edges in reverse way, ex : a -> g become g -> a.
        //to prevent the upcoming node 'g' from choosing a.
        //because this edge 'a -> g' is taken.
        visited_edge.insert( {min_edge.v, min_edge.u} );
        visited_node.insert(current_node);
        
        if (min_edge.u != non) MST.insert(min_edge); 
    }
    
    return MST;
}









int main() {

    adjancentlist G;

    int V, E;
    cin >> V >> E;

    while ( E-- ) {
        char u, v;
        int weight;

        cin >> u >> v >> weight;

        //undirected.
        G[u].push_back( {v, weight} );
        G[v].push_back( {u, weight} );
    }
   
    char start; cin >> start;

    LIST mst = Prim(G, start);

    cout             << endl; 
    cout << "MST : " << endl;
    for (const auto & [ff, ss] : mst) {
        cout << "["<<ff<<","<<ss<<"]" << endl; 
    }

    return 0;
}
