#include <iostream>
#include "lab5.h"
using namespace std;

int main()
{
    BST<int> tree = BST<int>();
    tree.insert(50);
    tree.insert(20);
    tree.insert(10);
    tree.insert(60);
    tree.insert(70);
    tree.insert(40);
    tree.insert(35);
    tree.insert(45);
    
    cout << "Part 1" << endl;
    tree.minCover();
    tree.displayMinCover();
    
    cout << "Part 2" << endl;
    int arr[1000];
    tree.findSumPath(tree.get_root(), 80, arr);
    cout << endl;
    
    cout << "Part 3" << endl;
    map<int, int> m;
    m[-2] = 0;
    m[-1] = 0;
    m[0] = 0;
    m[1] = 0;
    m[2] = 0;
    tree.vertSum(tree.get_root(), 0, m);
    
    return 0;
}