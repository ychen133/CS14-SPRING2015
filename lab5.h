/*
Name: Yu-Che Cheng
SID: 861142301
Date: 5/10/15
*/
#ifndef BST_H
#define BST_H
#define TEST

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>
#include <list>
#include <math.h>
#include <vector>
using namespace std;

#define nil 0

//#define Value int
template <typename Value>
class BST
{
    class Node //binary tree node 
    {
     public:
        Node* left;
        Node* right;
        Value value;
        bool selected = false;
        //constructor
        Node(const Value v = Value())
        :left(nil), right(nil), value(v)
        {}
        
        //return reference of the node's value 
        Value& content()
        {
            return value;
        }
        
        //returns true if node is internal, false otherwise
        bool isInternal()
        {
            return left != nil && right != nil;
        }
        
        
        //returns true if node os external, false otherwise
        bool isExternal()
        {
            return left != nil || right != nil;
        }
        
        //returns true is the node is a leaf, false otherwise
        bool isLeaf()
        {
            return left == nil && right == nil;
        }
        
        //returns the height of the subtree rooted at this node
        int height()
        {
            int left_path = 0;
            int right_path = 0;
            if(left != nil)
            {
                if(left.isLeaf())
                {
                    left_path = 1;
                }
                else
                {
                    left_path = 1 + height(left);
                }
            }
            if(right != nil)
            {
                if(right.isLeaf())
                {
                    right_path = 1;
                }
                else
                {
                    right_path = 1 + height(right);
                }
            }
            if(left_path >= right_path)
            {
                return left_path;
            }
            else
            {
                return  right_path;
            }
        }
        
        //returns the size of the subtree rooted at this node
        int size()
        {
            int size = 1;
            if(left != nil)
            {
                size += left.size();
            }
            if(right != nil)
            {
                size += right.size();
            }
            return size; 
        }
    }; //Node
    
    //const Node*nil;
    Node* root;
    int count;
    
 public:
    //constructor
    BST(): root(nil), count(0) {}
    
    //returns size of the overall tree
    int size()
    {
        return root.size();
    }
    
    bool empty()
    {
        return size() = 0;
    }
    
    //Print the node's value
    void print_node(const Node* n) const
    {
        cout << n->value << endl;
    }
    
    //returns a pinter to the tree's root
    Node* get_root()
    {
        return root;
    }
    
    //search for a Value in the BST and return true iff it was found
    bool search(Value x)
    {
        bool output = false;
        Node* temp = root;
        if(root->value == x)
        {
            return true;
            //output = true;
        }
        while(temp->left != nil || temp->right != nil)
        {
            if(temp->left != nil && x < temp->value)
            {
                temp = temp->left;
                output = (x == temp->value);
            }
            if(temp->right != nil && x > temp->value)
            {
                temp = temp->right;
                output = (x == temp->value);
            }
        }
        return output;
    }
    
    //A helper function that recursively prints node values in preorder
    void preorder_helper(Node* p) const
    {
        print_node(p);
        if(p->left != nil)
        {
            preorder_helper(p->left);
        }
        if(p->right != nil)
        {
            preorder_helper(p->right);
        }
    }
    
    //Traverse and print the tree one Value per line in preorder
    void preorder() const
    {
        preorder_helper(root);
    }
    
    //A helper function that recursively prints node values in postorder
    void postorder_helper(Node* p) const
    {
        if(p->left != nil)
        {
            postorder_helper(p->left);
        }
        if(p->right != nil)
        {
            postorder_helper(p->right);
        }
        print_node(p);
    }
    
    //Traverse and print the tree one Value per line in postorder
    void postorder() const
    {
        postorder_helper(root);
    }
    
    void inorder_helper(Node* p) const
    {
        if(p->left != nil)
        {
            inorder_helper(p->left);
        }
        print_node(p);
        if(p->right != nil)
        {
            inorder_helper(p->right);
        }
    }
    
    //Traverse and print the tree one Value per line in inorder
    void inorder() const
    {
        inorder_helper(root);
    }
    
    void traverse(Node* node, vector<Node*>& nodes)
    {
        if(node->left != nil)
        {
            traverse(node->left, nodes);
        }
        nodes.push_back(node);
        if(node->right != nil)
        {
            traverse(node->right, nodes);
        }
    }
    
    //returns reference to the value field of the n-th Node
    Value& operator[](int n)
    {
        vector<Node*> nodes;
        traverse(root, nodes);
        return nodes.at(n)->value;
    }
    
    void insert(Value X)
    {
        root = insert(X, root);
    }
    
    //The normal binary tree insertion
    Node* insert(Value X, Node* T)
    {
        if(T == nil)
        {
            T = new Node(X);
        }
        else if(X < T->value)
        {
            T->left = insert(X, T->left);
        }
        else if(X > T->value)
        {
            T->right = insert(X, T->right);
        }
        else
        {
            T->value = X;
        }
        //rebalancing code here
        return T;
    }
    
    void remove(Value X)
    {
        root = remove(X, root);
    }
    
    //The normal binary tree removal 
    Node* remove(Value X, Node*& T)
    {
        if(T != nil)
        {
            if(X > T->value)
            {
                T->right = remove(X, T->right);    
            }
            else if(X < T->value)
            {
                T->left = remove(X, T->left);
            }
            else    //X == T->value
            {
                if(T->right != nil)
                {
                    Node* x = T->right;
                    while(x->left != nil) x = x->left;
                    T->value = x->value;
                    T->right = remove(T->value, T->right);
                }
                else if(T->left != nil)
                {
                    Node* x = T->left;
                    while(x->right != nil) x = x->right;
                    T->value = x->value;
                    T->left = remove(T->value, T->left);
                }
                else
                {
                    delete T;
                    T = nil;
                }
            }
        }
        //rebalancing code here
        return T;
    }
    
    void okay()
    {
        okay(root);
    }
    
    void okay(Node* T)
    {
        //diagnostic code here
        return;
    }
    
    void minCover_helper(Node* node)
    {
        if(node->left != nil && !node->left->isLeaf())
        {
            node->left->selected = true;
            minCover_helper(node->left);
        }
        if(node->right != nil && !node->right->isLeaf())
        {
            node->right->selected = true;
            minCover_helper(node->right);
        }
    }
    
    //change selected to true for nodes that are in min cover
    void minCover()
    {
        if(root->left != nil)  root->left->selected = true;
        if(root->right != nil) root->right->selected = true;
        minCover_helper(root);
    }
    
    //helper functions for displaying nodes of min cover recursively
    int displayMinCover_helper(Node* p)
    {
        int output = 0;
        if(p->selected)
        {
            cout << p->value << " ";
            output++;
        }
        if(p->left != nil)
        {
            output += displayMinCover_helper(p->left);
        }
        if(p->right != nil)
        {
            output += displayMinCover_helper(p->right);
        }
        return output;
    }
    
    //print out the values of nodes that are in min cover
    void displayMinCover()
    {
        int num = displayMinCover_helper(root);
        cout << endl << num << endl;
    }
    
    bool sumPathHelper(Node* n, int sum, vector<int> v)
    {
        if(!n->isLeaf() && sum - n->value > 0)
        {
            v.push_back(n->value);
            bool leftCheck;
            bool rightCheck;
            if(n->left != nil && (sum - n->value) > 0)
            {
                //bool leftCheck;
                leftCheck = sumPathHelper(n->left, sum - n->value, v);
            }
            if(n->right != nil && (sum - n->value) > 0)
            {
                //bool rightCheck;
                rightCheck = sumPathHelper(n->right, sum - n->value, v);
            }
            return (!rightCheck && !leftCheck);
        }
        else
        {
            if(sum - n->value == 0)
            {
                v.push_back(n->value);
                for(unsigned i = 0; i < v.size(); i++)
                {
                    cout << v.at(i) << " ";
                }
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    
    //finds and display all paths from root to leaf in the tree for which the 
    //sum of the node values on the path is equal to the input sum
    void findSumPath(Node* n, int sum, int buffer[])
    {
        int *pointer = buffer;
        *pointer = n->value;
        vector<int> v;
        if(!sumPathHelper(n, sum, v))
        {
            cout << 0 << " ";
        }
    }
    
    void vertSum_helper(Node* node, int hd, map<int, int>& m)
    {
        m[hd] += node->value;
        if(node->left != nil)
        {
            vertSum_helper(node->left, hd - 1, m);
        }
        if(node->right != nil)
        {
            vertSum_helper(node->right, hd + 1, m);
        }
    }
    
    //find the vertical  sum of nodes that lie on same vertical line in a tree
    void vertSum(Node* node, int hd, std::map<int, int>& m)
    {
        vertSum_helper(node, hd, m);
        for(map<int, int>::iterator it = m.begin(); it != m.end(); it++)
        {
            cout << it->second << " ";
        }
        cout << endl;
    }
    
}; //BST

#endif