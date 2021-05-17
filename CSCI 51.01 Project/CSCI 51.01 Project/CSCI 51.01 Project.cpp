// CSCI 51.01 Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{    
    vector<int> arrivalTime(0);
    vector<int> burstTime(0);
    vector<int> priority(0);
    int numTestCase, numProcess, inputArrival, inputBurst, inputPriority;
    string scheduleAlgorithm;

    //creates the output text file
    ofstream outputFile("testOutput.txt");

    cin >> numTestCase;




    for (int i = 0; i < numTestCase; i++)
    {    
        cin >> numProcess >> scheduleAlgorithm;
        arrivalTime.clear();
        burstTime.clear();
        priority.clear();

        //input loop for the processes, stores them into vectors
        for (int o = 0; o < numProcess; o++)
        {
            cin >> inputArrival >> inputBurst >> inputPriority;
            arrivalTime.push_back(inputArrival);
            burstTime.push_back(inputBurst);
            priority.push_back(inputPriority);
        }

        if (scheduleAlgorithm == "FCFS")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << "\n";
            for (int q = 0; q < arrivalTime.size(); q++)
            {
                outputFile << "process " << q+1 << ": " << arrivalTime.at(q) << " " << burstTime.at(q) << " " << priority.at(q) << "\n";
            }
        }
        else if (scheduleAlgorithm == "SJF")
        {

        }
        else if (scheduleAlgorithm == "SRTF")
        {

        }
        else if (scheduleAlgorithm == "P")
        {

        }
        else if (scheduleAlgorithm == "RR")
        {

        }
    }

}

