/*
Name: Yu-Che Cheng
SID: 861142301
Date: 04/13/2015
TA: Dingwen Tao
*/
#ifndef LAB02_H
#define LAB02_H

#include <iostream>
#include <algorithm>
#include <forward_list>
using namespace std;

//checks is inputted integer is a prime number
//returns true is it is a prime, false otherwise
bool isPrime(int i)
{
    if(i == 1 || i == 2)
    {
        return true;
    }
    if(i <= 0)
    {
        return false;
    }
    int div_count = 0;
    for(int num = 1; num < i; num++)
    {
        if(i % num == 0)
        {
            div_count++;
        }
    }
    return (div_count == 1);
}

//returns the amount of prime numbers within the inputted forward_list
int primeCount(forward_list<int> lst)
{
    int output = 0;
    for(auto it = lst.begin(); it != lst.end(); it++)
    {
        if(isPrime(*it))
        {
            output++;
        }
    }
    return output;
}

template <typename Type>
void listCopy(forward_list<Type> L, forward_list<Type>& P)
{
    L.reverse();
    P.reverse();
    while(!L.empty())
    {
        P.push_front(L.front());
        L.pop_front();
    }
    P.reverse();
}

//add onto P
template <typename Type>
void printLots(forward_list<Type> L, forward_list<int> P)
{
    int L_size = distance(L.begin(), L.end());
    for(int i = 0; i < L_size; i++)
    {
        if(!P.empty() && i == P.front())
        {
            cout << L.front() << " ";
            P.pop_front();
        }
        L.pop_front();
    }
    cout << endl;
    return; //stub
}

template <typename Type>
struct Node
{
    Type data;
    Node<Type>* next;
    //constructor
    Node(Type value): data(value), next(0) {}
};

template <typename Type>
class List
{
 private:    
    Node<Type>* head;
    Node<Type>* tail;
 public:
    //constructor
    List(): head(0), tail(0) {}
    
    //destructor
    ~List()
    {
        while(head != 0)
        {
            Node<Type>* currObj = head;
            head = head->next;
            delete currObj;
        }
    }
    
    //adds a new node at the end of the List
    void push_back(Type value)
    {
        Node<Type>* temp = new Node<Type>(value);
        if(tail != 0)
        {
            tail->next = temp;
        }
        tail = temp;
        if(head == 0)
        {
            head = temp;
        }
    }
    
    //displays the contents of a List
    void display() const
    {
        Node<Type>* currObj = head;
        if(currObj != 0)
        {
            cout << currObj->data;
            while(currObj->next != 0)
            {
                currObj = currObj->next;
                cout << " " << currObj->data;
            }
        }
    }  
    
    //returns a List with the elements a pos and pos+1 swapped
    //no need for bounds checking
    List<Type> elementSwap(int pos)
    {
        if(head == 0 || head->next == 0)
        {
            return *this;
        }
        
        Node<Type>* currObj = head;
        for(int i = 0; i < pos; i++)
        {
            currObj = currObj->next;
        }
        Node<Type>* nextObj = currObj->next;
        
        if(pos == 0)
        {
            head = nextObj;
        }
        else
        {
            Node<Type>* prevObj = head;
            for(int i = 0; i < pos - 1; i++)
            {
                prevObj = prevObj->next;
            }
            prevObj->next = nextObj;
        }
        currObj->next = nextObj->next;
        nextObj->next = currObj;
        if(tail == nextObj)
        {
            tail = currObj;
        }
        return *this;
    }
};

#endif