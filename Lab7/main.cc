/*
Name: Yu-Che Cheng
SID: 86142301
Date: 5/23/15
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <set>
#include <unordered_set>
#include <ctime>
#include <cstdlib>
#include <utility>
using namespace std;

//self-balancing tree: set
//hash table: unordered set
void scramble(vector<string> &v)
{
    srand(0);
    for(unsigned i = 0; i < v.size(); i++)
    {
        int randIndex = rand() % v.size();
        swap(v.at(i), v.at(randIndex));
    }
}


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "Usage: ./a.out <file1> <file2>" << endl;
    }
    ifstream fin  (argv[1]);
    ofstream fout (argv[2]);
    if(!fin.is_open() || !fout.is_open())
    {
        cout << "Error: Trouble opening files." << endl;
        exit(1);
    }
    
    vector<string> words;
    string word;
    while(fin >> word)
    {
        words.push_back(word);
    }
    
    int wordCount;
    std::chrono::duration<double> treeInsertTime, hashInsertTime;
    std::chrono::duration<double> treeQueryTime, hashQueryTime;
    set<string> mySet;
    unordered_set<string> myUnorderedSet;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    
    for(int i = 1; i < 11; i++)
    {
        mySet.clear();
        myUnorderedSet.clear();
        scramble(words);
        wordCount = 5000 * i;
        
        //treeInsertTime
        start = std::chrono::system_clock::now();
        for(int i = 0; i < wordCount; i++)
        {
            mySet.insert(words.at(i));
        }
        end = std::chrono::system_clock::now();
        treeInsertTime = end - start;
        
        //hashInsertTime
        start = std::chrono::system_clock::now();
        for(int i = 0; i < wordCount; i++)
        {
            myUnorderedSet.insert(words.at(i));
        }
        end = std::chrono::system_clock::now();
        hashInsertTime = end - start;
        
        //treeQueryTime
        start = std::chrono::system_clock::now();
        for(int i = 0; i < wordCount; i++)
        {
            mySet.find(words.at(i));
        }
        end = std::chrono::system_clock::now();
        treeQueryTime = end - start;
        
        //hashQueryTime
        start = std::chrono::system_clock::now();
        for(int i = 0; i < wordCount; i++)
        {
            myUnorderedSet.find(words.at(i));
        }
        end = std::chrono::system_clock::now();
        hashQueryTime = end - start;
        
        fout << wordCount << " " << treeInsertTime.count() * 1000 << " " 
            << hashInsertTime.count() * 1000 << " " 
            << treeQueryTime.count() * 1000 << " " 
            << hashQueryTime.count() * 1000 << "\n";
    }
    return 0;
}