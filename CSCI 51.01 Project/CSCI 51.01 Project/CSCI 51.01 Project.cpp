// CSCI 51.01 Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process
{
    int arrivalTime, burstTime, priority;
    bool operator < (const Process& rhs) const 
    {
        return priority < rhs.priority;
    }
};


int main()
{    
    vector<Process> processVector;

    int numTestCase, numProcess, inputArrival, inputBurst, inputPriority;
    string scheduleAlgorithm;

    //creates the output text file
    ofstream outputFile("testOutput.txt");

    cin >> numTestCase;




    for (int i = 0; i < numTestCase; i++)
    {    
        cin >> numProcess >> scheduleAlgorithm;
        processVector.clear();

        //input loop for the processes, stores them into vector
        for (int o = 0; o < numProcess; o++)
        {
            cin >> inputArrival >> inputBurst >> inputPriority;
            processVector.push_back({ inputArrival, inputBurst, inputPriority });
        }

        if (scheduleAlgorithm == "FCFS")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << "\n";
            for (int q = 0; q < processVector.size(); q++)
            {

            }
        }
        else if (scheduleAlgorithm == "SJF")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << "\n";
            for (int q = 0; q < processVector.size(); q++)
            {

            }
        }
        else if (scheduleAlgorithm == "SRTF")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << "\n";
            for (int q = 0; q < processVector.size(); q++)
            {

            }
        }
        //Lance's part
        else if (scheduleAlgorithm == "P")
        {
            outputFile << i+1 << " " << scheduleAlgorithm << "\n";
            sort(processVector.begin(), processVector.end());
            for (int q = 0; q < processVector.size(); q++)
            {
                outputFile << "process " << q + 1 << ": " << processVector[q].arrivalTime << " " << processVector[q].burstTime << " " << processVector[q].priority << "\n";
            }
        }
        else if (scheduleAlgorithm == "RR")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << "\n";
            for (int q = 0; q < processVector.size(); q++)
            {

            }
        }
    }

}

