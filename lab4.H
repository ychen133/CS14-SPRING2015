/*
Name: Yu-Che Cheng
SID: 861142301
Date: 04/27/2015
TA: Dingwen Tao
*/
#ifndef LAB4_H
#define LAB4_H

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <queue>
using namespace std;

void printPair(int m, int n)
{
    cout << m << " " << n << endl;
}

void calculatePreorder(int m, int n, int k)
{
    if((m + n) > k)
    {
        return;
    }
    else
    {
        printPair(m, n);
        calculatePreorder(2 * m - n, m, k);
        calculatePreorder(2 * m + n, m, k);
        calculatePreorder(m + 2 * n, n, k);
    }
}

void calculatePostorder(int m, int n, int k)
{
    if((m + n) > k)
    {
        return;
    }
    else
    {
        calculatePostorder(2 * m - n, m, k);
        calculatePostorder(2 * m + n, m, k);
        calculatePostorder(m + 2 * n, n, k);
        if(m + n <= k)
        {
            printPair(m, n);
        }
    }
}


// void sort_helper(int m, int n, int num, priority_queue<pair<int, int>>& mypq)
// {
//     if(m + n > num)
//     {
//         return;
//     }
//     if(m + n == num)
//     {
//         pair<int, int> p (m, n);
//         mypq.push(p);
//     }
//     sort_helper(2 * m - n, m, num, mypq);
//     sort_helper(2 * m + n, m, num, mypq);
//     sort_helper(m + 2 * n, n, num, mypq);
// }

void calculateSorted(int m, int n, int k, priority_queue<pair<int, int>>& mypq)
{
    if(m + n > k)
    {
        return;
    }
    pair<int, int> p (m, n);
    mypq.push(p);
    calculateSorted(2 * m - n, m, k, mypq);
    calculateSorted(2 * m + n, m, k, mypq);
    calculateSorted(m + 2 * n, n, k, mypq);
    // for(int i = m + n; i <= k; i++)
    // {
    //     sort_helper(m, n, i, mypq);
    // }
}

void printSorted_helper(priority_queue<pair<int, int>>& mypq1)
{
    while(!mypq1.empty())
    {
        pair<int, int> p (mypq1.top());
        mypq1.pop();
        printSorted_helper(mypq1);
        printPair(p.first, p.second);
    }
}

void printSorted(priority_queue<pair<int, int>> mypq1, 
                priority_queue<pair<int, int>> mypq2)
{
    while(!mypq2.empty())
    {
        mypq1.push(mypq2.top());
        mypq2.pop();
    }
    
    printSorted_helper(mypq1);
    // while(!mypq1.empty() || !mypq2.empty())
    // {
    //     int sum1 = mypq1.top().first + mypq1.top().second;
    //     int sum2 = mypq2.top().first + mypq2.top().second;
    //     if(mypq2.empty() || (sum1 < sum2))
    //     {
    //         printPair(mypq1.top().first, mypq1.top().second);
    //         mypq1.pop();
    //     }
    //     else
    //     {
    //         printPair(mypq2.top().first, mypq2.top().second);
    //         mypq2.pop();
    //     }
    // }
}

#endif

