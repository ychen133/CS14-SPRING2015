/*
Name: Yu-Che Cheng
SID: 861142301
Date: 04/20/2015
TA: Dingwen Tao
*/
#ifndef LAB3_H
#define LAB3_H

#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

template <typename T>
class TwoStackFixed
{
 private:
    unsigned sz;
    int sz1;
    int sz2;
    T* data;
    int partition;
    bool isFullStack1()
    {
        return (sz1 == partition);
    }
    bool isFullStack2()
    {
        return (sz2 == (sz - partition));
    }
    bool isEmptyStack1()
    {
        return (sz1 == 0);
    }
    bool isEmptyStack2()
    {
        return (sz2 == 0);
    }
 public:
    //constructor
    TwoStackFixed(int size, int maxtop)
    :sz(size),
    sz1(0),
    sz2(0),
    data(new T[size]),
    partition(maxtop)
    {}
    
    //adds an element to Stack 1
    void pushStack1(T value)
    {
        if(isFullStack1())
        {
            cout << "Error: Stack1 is full. Cannot push " << value << endl;
            return;
        }
        data[sz1] = value;
        sz1++;
    }
    
    //push element into second stack
    void pushStack2(T value)
    {
        if(isFullStack2())
        {
            cout << "Error: Stack2 is full. Cannot push " << value << endl;
            return;
        }
        data[sz - 1 - sz2] = value;
        sz2++;
    }
    
    T popStack1()
    {
        if(isEmptyStack1())
        {
            cout << "Error: Stack1 is empty. Cannot pop Stack1." << endl;
            exit(1);
        }
        auto output = data[sz1 - 1];
        sz1--;
        return output;
    }
    
    T popStack2()
    {
        if(isEmptyStack2())
        {
            cout << "Error: Stack2 is empty. Cannot pop Stack2." << endl;
            exit(1);
        }
        auto output = data[sz - sz2];
        sz2--;
        return output;
    }
};

template <typename T>
class TwoStackOptimal
{
 private:
    unsigned sz;
    int sz1;
    int sz2;
    T* data;
    int stack2_top;
    bool isFullStack1()
    {
        //return (&data[sz1] != &data[stack2_top]);
        return (sz == sz1 + sz2);
    }
    bool isFullStack2()
    {
        //return (data[sz - sz2 - 1] != NULL);
        //return (&data[sz1] != &data[stack2_top]);
        return (sz == sz1 + sz2);
    }
    bool isEmptyStack1()
    {
        return (sz1 == 0);
    }
    bool isEmptyStack2()
    {
        return (sz2 == 0);
    }
 public:
    //constructor
    TwoStackOptimal(int size)
    :sz(size),
    sz1(0),
    sz2(0),
    data(new T[size])
    {}
    
    void pushStack1(T value)
    {
        if(isFullStack1())
        {
            cout << "Error: Stack1 is full. Cannot push " << value << endl;
            return;
        }
        data[sz1] = value;
        sz1++;
    }
    
    void pushStack2(T value)
    {
        if(isFullStack2())
        {
            cout << "Error: Stack2 is full. Cannot push " << value << endl;
            return;
        }
        data[sz - 1 - sz2] = value;
        sz2++;
        
    }
    
    T popStack1()
    {
        if(isEmptyStack1())
        {
            cout << "Error: Stack1 is empty. Cannot pop Stack1." << endl;
            exit(1);
        }
        auto output = data[sz1 - 1];
        sz1--;
        return output;
    }
    
    T popStack2()
    {
        if(isEmptyStack2())
        {
            cout << "Error: Stack2 is empty. Cannot pop Stack2." << endl;
            exit(1);
        }
        auto output = data[sz - sz2];
        sz2--;
        return output;
    }
};

void hanoi(int disks, string source, string aux, string dest)
{
    if(disks == 1)
    {
        cout << "Moved disk from peg " << source << " to peg " << dest << endl;
    }
    else
    {
        hanoi(disks - 1, source, dest, aux);
        cout << "Moved disk from peg " << source << " to peg " << dest << endl;
        hanoi(disks - 1, aux, source, dest);
    }
    
}

#define VNAME(x) #x

template <typename T>
void showTowerStates(int n, stack<T>& A, stack<T>& B, stack<T>& C)
{
    // stack<T>* address_a = &A;
    // stack<T>* address_b = &B;
    // stack<T>* address_c = &C;
    if(n <= 0)
    {
        return;
    }
    
    if(n == 1)
    {
        cout << "Moved " << A.top() << " from peg " << VNAME(A) << " to peg " 
            << VNAME(C) << endl;
        auto element = A.top();
        A.pop();
        C.push(element);
    }
    else
    {
        showTowerStates(n - 1, A, C, B);
        
        cout << "Moved " << A.top() << " from peg " << VNAME(A) 
            << " to peg " << VNAME(C) << endl;
        auto element = A.top();
        A.pop();
        C.push(element);
        showTowerStates(n - 1, B, A, C);
    }
}

#endif