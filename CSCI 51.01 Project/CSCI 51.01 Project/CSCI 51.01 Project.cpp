// CSCI 51.01 Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int numTestCase, numProcess, inputArrival, inputBurst, inputPriority;
    string scheduleAlgorithm;

    cin >> numTestCase;
    cin >> numProcess >> scheduleAlgorithm;

    vector<double> arrivalTime(numProcess);
    vector<double> burstTime(numProcess);
    vector<double> priority(numProcess);

    for (int i = 0; i < numTestCase; i++)
    {
        for (int o = 0; i < numProcess; o++)
        {
            cin >> inputArrival >> inputBurst >> inputPriority;
            arrivalTime.push_back(inputArrival);
            burstTime.push_back(inputBurst);
            priority.push_back(inputPriority);
        }

        if (scheduleAlgorithm == "FCFS")
        {

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

