// CSCI 51.01 Project.cpp : This file contains the 'main' function. Program execution begins and ends there.

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
    int burst, waiting, turnaround, response, processID;
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

    int numTestCase, inputArrival, inputBurst, inputPriority, totalBurstTime, time, numProcess, quantum;
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
        waitingTimeList.clear();

        if (scheduleAlgorithm == "RR") cin >> quantum;

        //input loop for the processes, stores them into vector
        for (int o = 0; o < numProcess; o++)
        {
            cin >> inputArrival >> inputBurst >> inputPriority;
            processVector.push_back({ inputArrival, inputBurst, inputPriority, o + 1 });
            totalBurstTime = totalBurstTime + processVector[o].burstTime;
        }

        if (scheduleAlgorithm == "FCFS")
        {
            WaitingTime wtl; 
            wtl.burst = 0;
            wtl.waiting = 0;
            wtl.turnaround = 0;
            wtl.response = 0;

            outputFile << i + 1 << " " << scheduleAlgorithm << "\n";
            std::sort(processVector.begin(), processVector.end(), compareArrival);

            for (int o = 0; o < numProcess; o++)
            {
                wtl.processID = processVector[o].processID;
                waitingTimeList.push_back(wtl);
            }

            for (auto j = processVector.begin(); j != processVector.end(); ++j) 
            {
                // this is to fast forward the time in case processes haven't arrived yet
                if (time < processVector[distance(processVector.begin(), j)].arrivalTime) 
                {
                    time = processVector[distance(processVector.begin(), j)].arrivalTime;
                }

                //output
                outputFile << time << " " << processVector[distance(processVector.begin(), j)].processID << " " << processVector[distance(processVector.begin(), j)].burstTime << "X" << "\n";

                // adds burst Time to the time elapsed so far
                time += processVector[distance(processVector.begin(), j)].burstTime;

                /// Setting the metrics
                // turnaroundTime -- equal to burstTime always
                waitingTimeList[distance(processVector.begin(), j)].turnaround = time - processVector[distance(processVector.begin(), j)].arrivalTime;

                // waitingTime -- for FCFS this is just equal to the Response Time
                // responseTime -- the only case where there is waiting time is if a new process arrives while old one is not yet done
                for (auto k = processVector.begin(); k != processVector.end(); ++k) {
                    if (processVector[distance(processVector.begin(), k)].arrivalTime < time && k > j)
                    {
                        waitingTimeList[distance(processVector.begin(), k)].waiting = time - processVector[distance(processVector.begin(), k)].arrivalTime;
                        waitingTimeList[distance(processVector.begin(), k)].response = waitingTimeList[distance(processVector.begin(), k)].waiting;
                    }
                    waitingTimeList[distance(processVector.begin(), k)].burst = processVector[distance(processVector.begin(), k)].burstTime;
                }
            }
        }

        //Lance's part
        else if (scheduleAlgorithm == "P")
        {
            vector<Process> tempVector;

            outputFile << i + 1 << " " << scheduleAlgorithm << endl;
            //sorts the stack by their arrival time
            sort(processVector.begin(), processVector.end(), compareArrival);
            //creates the vector that stores the performance metric values
            for (int counter = 0; counter < numProcess; counter++)
            {
                waitingTimeList.push_back({ 0, 0, 0, -1, counter + 1 });
            }
            //Since it's reliant on being able to compare processes within a vector, the final process is separated and the while loop is only until 2 processes are present
            //Otherwise it would throw an indexOutOfBounds error
            while (processVector.size() > 1)
            {
                //Checks if one of the upcoming processes have a higher priority than the one in index 0
                int indexOfHigherCurrentPriority = 0;
                for (int g = 0; g <= int((processVector.size())-1); ++g)
                {
                    if (processVector[g].priority < processVector[indexOfHigherCurrentPriority].priority)
                    {
                        indexOfHigherCurrentPriority = g;
                        break;
                    }
                }
                //Makes sure that the process has actually arrived first
                if (time >= processVector[0].arrivalTime)
                {
                    //This will check if the process will complete before the higher priority process will arrive, or if the current process has a higher priority than the next process
                    //if either condition's good, it will finish the current process completely
                    if (indexOfHigherCurrentPriority == 0 || (time + processVector[0].burstTime) < processVector[indexOfHigherCurrentPriority].arrivalTime)
                    {
                        if (waitingTimeList[(processVector[0].processID) - 1].response == -1)
                        {
                            waitingTimeList[(processVector[0].processID) - 1].response = time - processVector[0].arrivalTime;
                        }
                        outputFile << time << " " << processVector[0].processID << " " << processVector[0].burstTime << "X" << endl;

                        time += processVector[0].burstTime;

                        waitingTimeList[(processVector[0].processID) - 1].burst += processVector[0].burstTime;
                        waitingTimeList[(processVector[0].processID) - 1].turnaround = (time - processVector[0].arrivalTime);
                        waitingTimeList[(processVector[0].processID) - 1].processID = processVector[0].processID;
                        waitingTimeList[(processVector[0].processID) - 1].waiting = (time - (processVector[0].arrivalTime + waitingTimeList[(processVector[0].processID) - 1].burst));
                        processVector.erase(processVector.begin());

                    }
                    //If the previous check fails, there are 2 scenarios:
                    //1. The is a process that will arrive while the current one is being processed and has a higher priority. In this case, you process as much as you can and then swap them around
                    //2. There are processes ready but the next process has a higher priority. In this case you shuffle the vector around to slowly move the priority process into index 0
                    else
                    {
                        //This is scenario 2, 2 processes are ready but the one in index 0 is not the highest priority
                        //Swap them around
                        if (time >= processVector[0].arrivalTime && time >= processVector[indexOfHigherCurrentPriority].arrivalTime)
                        {
                            tempVector.push_back(processVector[0]);
                            processVector[0] = processVector[indexOfHigherCurrentPriority];
                            processVector[indexOfHigherCurrentPriority] = tempVector[0];
                            tempVector.erase(tempVector.begin());
                        }
                        //This is scenario 1, process as much as you can before putting it in the back of the queue again
                        else
                        {
                            outputFile << time << " " << processVector[0].processID << " " << processVector[indexOfHigherCurrentPriority].arrivalTime - time << endl;                            
                            processVector[0].burstTime = (time + processVector[0].burstTime) - processVector[indexOfHigherCurrentPriority].arrivalTime;
                            waitingTimeList[(processVector[0].processID) - 1].burst += processVector[indexOfHigherCurrentPriority].arrivalTime - time;
                            if (waitingTimeList[(processVector[0].processID) - 1].response == -1)
                            {
                                waitingTimeList[(processVector[0].processID) - 1].response = time - processVector[0].arrivalTime;
                            }
                            time = time + (processVector[indexOfHigherCurrentPriority].arrivalTime - time);

                            tempVector.push_back(processVector[0]);
                            processVector[0] = processVector[indexOfHigherCurrentPriority];
                            processVector[indexOfHigherCurrentPriority] = tempVector[0];
                            tempVector.erase(tempVector.begin());
                        }
                    }
                }
                //If the process hasn't arrived yet, just increase time by 1
                else
                {
                    time = processVector[0].arrivalTime;
                }

            }
            //The final process
            outputFile << time << " " << processVector[0].processID << " " << processVector[0].burstTime << "X" << endl;
            if (waitingTimeList[(processVector[0].processID) - 1].response == -1)
            {
                waitingTimeList[(processVector[0].processID) - 1].response = time - processVector[0].arrivalTime;
            }
            time = time + processVector[0].burstTime;

            //Setting the performance metrics of the final process
            waitingTimeList[(processVector[0].processID) - 1].burst += processVector[0].burstTime;
            waitingTimeList[(processVector[0].processID) - 1].turnaround = (time - processVector[0].arrivalTime);
            waitingTimeList[(processVector[0].processID) - 1].processID = processVector[0].processID;
            waitingTimeList[(processVector[0].processID) - 1].waiting = (time - (processVector[0].arrivalTime + waitingTimeList[(processVector[0].processID) - 1].burst));
        }

        else if (scheduleAlgorithm == "RR")
        {
            vector<Process> RRQueue, tempProcessVector;
            vector<WaitingTime> tempRRWaiting1, tempRRWaiting2;
            tempProcessVector = processVector;
            WaitingTime wtl; 
            wtl.burst = 0;
            wtl.waiting = 0;
            wtl.turnaround = 0;
            wtl.response = 0;

            outputFile << i + 1 << " " << scheduleAlgorithm << "\n";
            std::sort(processVector.begin(), processVector.end(), compareArrival);

            for (int o = 0; o < numProcess; o++)
            {
                wtl.processID = processVector[o].processID;
                tempRRWaiting1.push_back(wtl);
            }

            while (!RRQueue.empty() || !processVector.empty()) {                
                //check the RRQueue first if there's another process already there
                if (!processVector.empty() && time >=  processVector[0].arrivalTime) {
                    //fast forward time if process hasn't arrived yet
                    if (time < processVector[0].arrivalTime) 
                    {
                        time = processVector[0].arrivalTime;
                    }
                    
                    //responseTime
                    tempRRWaiting1[0].response = time - processVector[0].arrivalTime;

                    outputFile << time << " " << processVector[0].processID << " ";
                    
                    if (processVector[0].burstTime > quantum){
                        outputFile << quantum << "\n";
                        time += quantum;
                        processVector[0].burstTime -= quantum;
                        
                        RRQueue.push_back(processVector[0]);
                        tempRRWaiting2.push_back(tempRRWaiting1[0]);
                        processVector.erase(processVector.begin());
                        tempRRWaiting1.erase(tempRRWaiting1.begin());
                    }
                    else {
                        outputFile << processVector[0].burstTime << "X\n";
                        time += processVector[0].burstTime;
                        
                        //setting turnaroundTime
                        tempRRWaiting1[0].turnaround = time - processVector[0].arrivalTime;           

                        waitingTimeList.push_back(tempRRWaiting1[0]);
                        processVector.erase(processVector.begin());
                        tempRRWaiting1.erase(tempRRWaiting1.begin());
                    }

                } else {

                    outputFile << time << " " << RRQueue[0].processID << " ";
                   
                    if (RRQueue[0].burstTime > quantum){
                        outputFile << quantum << "\n";
                        time += quantum;
                        RRQueue[0].burstTime -= quantum;

                        RRQueue.push_back(RRQueue[0]);
                        tempRRWaiting2.push_back(tempRRWaiting2[0]);
                        RRQueue.erase(RRQueue.begin());
                        tempRRWaiting2.erase(tempRRWaiting2.begin());
                    } else {
                        outputFile << RRQueue[0].burstTime << "X\n";
                        time += RRQueue[0].burstTime;
                        
                        //setting turnaroundTime
                        tempRRWaiting2[0].turnaround = time - RRQueue[0].arrivalTime;

                        waitingTimeList.push_back(tempRRWaiting2[0]);
                        RRQueue.erase(RRQueue.begin());
                        tempRRWaiting2.erase(tempRRWaiting2.begin());
                    }
                    
                }
            }

            //setting waitingTime and burstTime (for waitingTimeList)
            sort(waitingTimeList.begin(), waitingTimeList.end(), compareProcessID);
            sort(waitingTimeList.begin(), waitingTimeList.end(), compareProcessID);
            for (auto i = waitingTimeList.begin(); i != waitingTimeList.end(); ++i) {
                waitingTimeList[distance(waitingTimeList.begin(), i)].waiting = waitingTimeList[distance(waitingTimeList.begin(), i)].turnaround - tempProcessVector[distance(waitingTimeList.begin(), i)].burstTime;
                waitingTimeList[distance(waitingTimeList.begin(), i)].burst = tempProcessVector[distance(waitingTimeList.begin(), i)].burstTime;
            }
        }

        //Syl's output logs
        int summationBT = 0, summationWT = 0, summationTT = 0, summationRT = 0;

        // re-sorting everything just to make life easier when displaying the metrics for each process
        std::sort(waitingTimeList.begin(), waitingTimeList.end(), compareProcessID);

        //gets the sum of the metrics, which will be later divided by the vector size to get average
        for (auto i = waitingTimeList.begin(); i != waitingTimeList.end(); ++i) {
            summationBT += (*i).burst;
            summationWT += (*i).waiting;
            summationTT += (*i).turnaround;
            summationRT += (*i).response;
        }

        // Output logs

        outputFile << "Total Time Elapsed: " << time << " ns" << "\n";
        outputFile << "Total CPU Burst Time: " << summationBT << " ns" << "\n";
        outputFile << "CPU Utilization: " << (int)((float)summationBT / (float)time * 100) << "%\n";
        outputFile << "Throughput: " << (float)waitingTimeList.size() / time << " processes/ns" << "\n";
        outputFile << "Waiting times:\n";
        for (int i = 0; i < int(waitingTimeList.size()); i++) {
            outputFile << " Process " << i + 1 << ": " << waitingTimeList[i].waiting << "ns\n";
        }
        outputFile << "Average waiting time: " << (float)summationWT / waitingTimeList.size() << "ns\n";
        outputFile << "Turnaround times:\n";
        for (int i = 0; i < int(waitingTimeList.size()); i++) {
            outputFile << " Process " << i + 1 << ": " << waitingTimeList[i].turnaround << "ns\n";
        }
        outputFile << "Average turnaround time: " << (float)summationTT / waitingTimeList.size() << "ns\n";
        outputFile << "Response times:\n";
        for (int i = 0; i < int(waitingTimeList.size()); i++) {
            outputFile << " Process " << i + 1 << ": " << waitingTimeList[i].response << "ns\n";
        }
        outputFile << "Average response time: " << (float)summationRT / waitingTimeList.size() << "ns\n";
    }
    return 0;
}
