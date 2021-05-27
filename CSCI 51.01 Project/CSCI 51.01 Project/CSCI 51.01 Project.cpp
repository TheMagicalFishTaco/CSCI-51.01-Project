// CSCI 51.01 Project.cpp : This file contains the 'main' function.Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process
{
    int arrivalTime, burstTime, priority, processID;
};
struct WaitingTime
{
    int waiting, turnaround, response, processID;
};

bool compareArrival(Process i1, Process i2)
{
    return (i1.arrivalTime < i2.arrivalTime);
}
bool compareProcessID(WaitingTime i1, WaitingTime i2)
{
    return (i1.processID < i2.processID);
}
int main()
{
    vector<Process> processVector;
    vector<WaitingTime> waitingTimeList;

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
            processVector.push_back({ inputArrival, inputBurst, inputPriority, o + 1 });
            totalBurstTime = totalBurstTime + processVector[o].burstTime;
        }


        if (scheduleAlgorithm == "FCFS")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << endl;
            for (int q = 0; q < processVector.size(); q++)
            {

            }
        }
        else if (scheduleAlgorithm == "SJF")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << endl;
            for (int q = 0; q < processVector.size(); q++)
            {

            }
        }
        else if (scheduleAlgorithm == "SRTF")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << endl;
            for (int q = 0; q < processVector.size(); q++)
            {

            }
        }
        //Lance's part
        else if (scheduleAlgorithm == "P")
        {
            outputFile << i + 1 << " " << scheduleAlgorithm << endl;
            //sorts the stack by their arrival time
            sort(processVector.begin(), processVector.end(), compareArrival);
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
                        outputFile << time << " " << processVector[0].processID << " " << processVector[0].burstTime << "X" << endl;
                        waitingTimeList.push_back({int(time), int(time) - processVector[0].arrivalTime, int(time), processVector[0].processID});
                        time = time + processVector[0].burstTime;
                        processVector.erase(processVector.begin());
                    }
                    //If the previous check fails, there are 2 scenarios:
                    //1. The is a process that will arrive while the current one is being processed and has a higher priority. In this case, you process as much as you can and then swap them around
                    //2. There are processes ready but the next process has a higher priority. In this case you immediately switch them around
                    else
                    {
                        //This is scenario 2, both processes are ready and waiting but the next process in the queue has a higher priority
                        if ((time >= processVector[0].arrivalTime && time >= processVector[1].arrivalTime) && processVector[0].priority > processVector[1].priority)
                        {
                            processVector.push_back(processVector[0]);
                            processVector.erase(processVector.begin());
                        }
                        //This is scenario 1, process as much as you can before swapping to the newly arrived process
                        else
                        {
                            outputFile << time << " " << processVector[0].processID << " " << processVector[1].arrivalTime - time << endl;
                            processVector[0].burstTime = (time + processVector[0].burstTime) - processVector[1].arrivalTime;
                            time = time + (processVector[1].arrivalTime - time);
                            processVector.push_back(processVector[0]);
                            processVector.erase(processVector.begin());
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
            outputFile << time << " " << processVector[0].processID << " " << processVector[0].burstTime << "X" << endl;
            waitingTimeList.push_back({ int(time), int(time) - processVector[0].arrivalTime, int(time), processVector[0].processID });
            time = time + processVector[0].burstTime;
            processVector.clear();
        }
        else if (scheduleAlgorithm == "RR")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << endl;
            for (int q = 0; q < processVector.size(); q++)
            {

            }
        }

        //Output logs, add the others later
        outputFile << "Total Time Elapsed: " << time << " ns" << endl;
        outputFile << "Total CPU Burst Time: " << totalBurstTime << " ns" << endl;
        outputFile << "CPU Utilization: " << (totalBurstTime / time) * 100 << "%" << endl;
        outputFile << "Throughput: " << numProcess / time << " processes/ns" << endl;

        sort(waitingTimeList.begin(), waitingTimeList.end(), compareProcessID);
        outputFile << "Waiting Times: " << endl;
        for (int i = 0; i <= numProcess-1; i++)
        {
            outputFile << " Process " << i+1 << ": " << waitingTimeList[i].waiting << " ns"<< endl;
        }
        outputFile << "Average Waiting Time: " << endl;

        outputFile << "Turnaround Times: " << endl;
        for (int i = 0; i <= numProcess-1; i++)
        {
            outputFile << " Process " << i+1 << ": " << waitingTimeList[i].turnaround << " ns" << endl;
        }
        outputFile << "Average Turnaround Time: " << endl;

        outputFile << "Response Times: " << endl;
        for (int i = 0; i <= numProcess-1; i++)
        {
            outputFile << " Process " << i+1 << ": " << waitingTimeList[i].response << " ns" << endl;
        }
        outputFile << "Average Response Time: " << endl;
    }
}