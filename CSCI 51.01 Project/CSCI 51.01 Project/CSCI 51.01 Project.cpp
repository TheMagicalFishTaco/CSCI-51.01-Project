// CSCI 51.01 Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process
{
    int arrivalTime, burstTime, priority, processID;
    bool operator < (const Process& rhs) const 
    {
        return arrivalTime < rhs.arrivalTime;
    }
};

int main()
{    
    vector<Process> processVector;

    int numTestCase, inputArrival, inputBurst, inputPriority, totalBurstTime;
    float time, numProcess;
    string scheduleAlgorithm;

    //creates the output text file
    ofstream outputFile("testOutput.txt");

    cin >> numTestCase;


    for (int i = 0; i < numTestCase; i++)
    {    
        time = 0;
        totalBurstTime = 0;
        cin >> numProcess >> scheduleAlgorithm;
        processVector.clear();

        //input loop for the processes, stores them into vector
        for (int o = 0; o < numProcess; o++)
        {
            cin >> inputArrival >> inputBurst >> inputPriority;
            processVector.push_back({ inputArrival, inputBurst, inputPriority, o+1 });
            totalBurstTime = totalBurstTime + processVector[o].burstTime;
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
            //sorts the stack by their arrival time
            sort(processVector.begin(), processVector.end());
            //the final process is separated, i don't know why but it doesn't like it if I "process" it within this while loop
            while (processVector.size() > 1)
            {
                //Makes sure that the process has actually arrived first
                if (time >= processVector[0].arrivalTime)
                {               
                    //This will check if the process will complete before the next process arrives, or if the current process has a higher priority than the next process
                    //if either condition's good, it will finish the current process completely
                    if ((time + processVector[0].burstTime) < processVector[1].arrivalTime || processVector[0].priority < processVector[1].priority)
                    {
                        outputFile << time << " " << processVector[0].processID << " " << processVector[0].burstTime <<"X" << "\n";
                        time = time + processVector[0].burstTime;
                        processVector.erase(processVector.begin());
                    }
                    //If the previous check fails, there are 2 scenarios:
                    //1. The next process will arrive while the current one is being processed and has a higher priority. In this case, you process as much as you can and then swap them around
                    //2. Both processes have arrived but the next process has a higher priority. In this case you immediately switch them around
                    else
                    {
                        //This is scenario 2, both processes are ready and waiting but the next process in the queue has a higher priority
                        if ((time > processVector[0].arrivalTime && time > processVector[1].arrivalTime) && processVector[0].priority > processVector[1].priority)
                        {
                            iter_swap(processVector.begin(), processVector.begin() + 1);
                        }
                        //This is scenario 1, process as much as you can before swapping to the newly arrived process
                        else
                        {
                            outputFile << time << " " << processVector[0].processID << " " << processVector[1].arrivalTime - time << "\n";
                            processVector[0].burstTime = (time + processVector[0].burstTime) - processVector[1].arrivalTime;
                            time = time + (processVector[1].arrivalTime - time);
                            iter_swap(processVector.begin(), processVector.begin() + 1);
                        }
                    }
                }
                //If the process hasn't arrived yet, just increase time by 1
                else
                {
                    time = time++;
                }

            }
            //The final process
            outputFile << time << " " << processVector[0].processID << " " << processVector[0].burstTime <<"X" << "\n";
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
        //Output logs, add the others later
        outputFile << "Total Time Elapsed: " << time <<" ns"<<"\n";
        outputFile << "Total CPU Burst Time: " << totalBurstTime << " ns"<<"\n";
        outputFile << "CPU Utilization: " << (totalBurstTime / time) * 100 << "%" <<"\n";
        outputFile << "Throughput: " << numProcess / time << " processes/ns"<< "\n";

}

