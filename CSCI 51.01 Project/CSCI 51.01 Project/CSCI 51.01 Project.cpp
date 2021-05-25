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
        return arrivalTime < rhs.arrivalTime;
    }
};

int main()
{    
    vector<Process> processVector;

    int numTestCase, inputArrival, inputBurst, inputPriority;
    float time, numProcess;
    string scheduleAlgorithm;

    //creates the output text file
    ofstream outputFile("testOutput.txt");

    cin >> numTestCase;




    for (int i = 0; i < numTestCase; i++)
    {    
        time = 0;
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
            while (processVector.size() > 1)
            {
                if ((time + processVector[0].burstTime) < processVector[1].arrivalTime || processVector[0].priority < processVector[1].priority)
                {
                    outputFile << processVector[0].arrivalTime << " " << processVector[0].burstTime << " " << processVector[0].priority <<"X" << "\n";
                    time = time + processVector[0].burstTime;
                    processVector.erase(processVector.begin());
                }
                else
                {
                    if ((time > processVector[0].arrivalTime && time > processVector[1].arrivalTime) && processVector[0].priority > processVector[1].priority)
                    {
                        iter_swap(processVector.begin(), processVector.begin() + 1);
                    }
                    else
                    {
                        outputFile << processVector[0].arrivalTime << " " << processVector[1].arrivalTime - time << " " << processVector[0].priority << "\n";
                        processVector[0].burstTime = (time + processVector[0].burstTime) - processVector[1].arrivalTime;
                        time = time + (processVector[1].arrivalTime - time);
                        iter_swap(processVector.begin(), processVector.begin() + 1);
                    }
                }
            }
            outputFile << processVector[0].arrivalTime << " " << processVector[0].burstTime << " " << processVector[0].priority << "X" << "\n";
            time = time + processVector[0].burstTime;
            processVector.clear();
        }
        else if (scheduleAlgorithm == "RR")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << "\n";
            for (int q = 0; q < processVector.size(); q++)
            {

            }
        }
        outputFile << "Total Time Elapsed: " << time <<" ns"<<"\n";
        outputFile << "Total CPU Burst Time: " << time << " ns"<<"\n";
        outputFile << "CPU Utilization: " << "\n";
        outputFile << "Throughput: " << numProcess / time << " processes/ns"<< "\n";
    }

}

