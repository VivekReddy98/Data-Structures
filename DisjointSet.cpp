/*
  Author : Vivek Reddy
  Date   : May'20
  DS     : Disjoint Set with Union-by-Rank, Easily Extensible to any custom variant of the DisjointSet Element.
           Primitive or Non-Primitive
  Source : https://www.techiedelight.com/disjoint-set-data-structure-union-find-algorithm/
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
1) For Primitive Types, int, string, char

   A) Initialize the DisjointSet class using  DisjointSet<int,std::hash<int>>

2) Guide for user-defined objects

    T => any user-defined class

    A) Template for Custom Hash Function
        class MyHashFunction {
        public:
            size_t operator()(const T& t) const
            {
                // Write a Hash Funtion
            }
        };

    B)  DisjointSet Implementation would need these three, but follow rule of 5 if possible)

        Overload Equality Check operator
        bool operator==(const T& t) const;

        Overload Copy Constructor
        T(const t& rhs);

        Overload Copy Assignment Operator
        T& operator=(const MyClass& rhs );

    C) Initialize the DisjointSet class using  DisjointSet<T,MyHashFunction> ;

*/

/* Class: T and Corresponding Class which can give Hash Value*/
template<Class T, Class H>
class DisjointSet
{
    unordered_map<T, int, H> rankTable;
    unordered_map<T, T*, H> parentTable;

public:
    // perform MakeSet operation
    void makeSet(T& Node)
    {
        if (rankTable.find(Node) != rankTable.end()){
            std::cout << "Element Already Exists in the Disjoint Set" << std::endl;
        }
        else{
            rankTable[Node] = 0;
            parentTable[Node] = Node;
        }
    }

    // Find the root of the set in which element k belongs
    T& Find(T& Node)
    {
        // if k is not root
        auto it = parentTable.find(Node)
        if (it->second != &Node)
            // path compression
            parent[k] = Find(parent[k]);

        return parent[k];
    }

    // Perform Union of two subsets
    void Union(int a, int b)
    {
        // find root of the sets in which elements
        // x and y belongs
        int x = Find(a);
        int y = Find(b);

        // if x and y are present in same set
        if (x == y)
            return;

        // Always attach smaller depth tree under the
        // root of the deeper tree.
        if (rank[x] > rank[y])
            parent[y] = x;
        else if (rank[x] < rank[y])
            parent[x] = y;
        else
        {
            parent[x] = y;
            rank[y]++;
        }
    }
};

void printSets(vector<int> const &universe, DisjointSet &ds)
{
    for (int i : universe)
        cout << ds.Find(i) << ' ';

    cout << '\n';
}

// Disjoint-Set Data Structure (Union Find Algorithm)
int main()
{
    // universe of items
    vector<int> universe = { 1, 2, 3, 4, 5 };

    // initialize DisjointSet class
    DisjointSet ds;

    // create singleton set for each element of universe
    ds.makeSet(universe);
    printSets(universe, ds);

    ds.Union(4, 3); // 4 and 3 are in same set
    printSets(universe, ds);

    ds.Union(2, 1); // 1 and 2 are in same set
    printSets(universe, ds);

    ds.Union(1, 3); // 1, 2, 3, 4 are in same set
    printSets(universe, ds);

    return 0;
}
