// CSCI 51.01 Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

int main()
{    
    vector<double> arrivalTime(0);
    vector<double> burstTime(0);
    vector<double> priority(0);
    int numTestCase, numProcess, inputArrival, inputBurst, inputPriority;
    string scheduleAlgorithm;

    cin >> numTestCase;
    cin >> numProcess >> scheduleAlgorithm;



    for (int i = 0; i < numTestCase; i++)
    {
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
            //just made this to test if the inputs are being recieved
            cout << "schedule algorithm: " << scheduleAlgorithm << "\n";
            for (int q = 0; q < arrivalTime.size(); q++)
            {
                cout << "process " << q << ": " << arrivalTime.at(q) << " " << burstTime.at(q) << " " << priority.at(q) << "\n";
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

