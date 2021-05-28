// CSCI 51.01 Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
// ignore line 3 this is for me only - Syl
// run with C:\Users\Syl\Documents\AASylvane\"CSCI 51.01"\CSCI-51.01-Project\"CSCI 51.01 Project"\"CSCI 51.01 Project"\"CSCI 51.01 Project" < testInput.txt

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

    int numTestCase, inputArrival, inputBurst, inputPriority, totalBurstTime, time, numProcess,turnaroundTime, responseTime, waitingTime, processID;;
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

        //input loop for the processes, stores them into vector
        for (int o = 0; o < numProcess; o++)
        {
            cin >> inputArrival >> inputBurst >> inputPriority;
            processVector.push_back({ inputArrival, inputBurst, inputPriority, o + 1 });
            totalBurstTime = totalBurstTime + processVector[o].burstTime;
        }

        //Syl's part
        if (scheduleAlgorithm == "FCFS")
        {
            outputFile << i + 1 << " " << scheduleAlgorithm << "\n";
            sort(processVector.begin(), processVector.end(), compareArrival);

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
                turnaroundTime = processVector[distance(processVector.begin(), j)].burstTime;

                if (processVector[distance(processVector.begin(), j)].arrivalTime > time)
                {
                    waitingTime = time - processVector[distance(processVector.begin(), j)].arrivalTime;
                    responseTime = waitingTime;
                }
                else
                {
                    responseTime = 0;
                    waitingTime = 0;
                }
                waitingTimeList.push_back({ turnaroundTime, waitingTime, turnaroundTime, responseTime, processVector[distance(processVector.begin(), j)].processID });
                // waitingTime -- for FCFS this is just equal to the Response Time
                // responseTime -- the only case where there is waiting time is if a new process arrives while old one is not yet done
                //for (auto k = processVector.begin(); k != processVector.end(); ++k) 
                //{
                //    if (processVector[distance(processVector.begin(), k)].arrivalTime < time && k > j) 
                //    {
                //        //processVector[distance(processVector.begin(), k)].waitingTime = time - processVector[distance(processVector.begin(), k)].arrivalTime;
                //        //processVector[distance(processVector.begin(), k)].responseTime = processVector[distance(processVector.begin(), k)].waitingTime;
                //        waitingTimeList.push_back({ time - processVector[distance(processVector.begin(), k)].arrivalTime, turnaroundTime, time - processVector[distance(processVector.begin(), k)].arrivalTime, processVector[distance(processVector.begin(), k)].processID });
                //    }
                //    else
                //    {
                //        waitingTimeList.push_back({ 0, turnaroundTime, 0, processVector[distance(processVector.begin(), k)].processID });
                //    }
                //}
            }
        }
        
        /*
        else if (scheduleAlgorithm == "SJF")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << endl;
            for (int q = 0; q < processVector.size(); q++)
            {

                //output
                outputFile << time << " " << processVector[distance(processVector.begin(), j)].PID << " " << processVector[distance(processVector.begin(), j)].burstTime << "X" << "\n";
                
                // adds burst Time to the time elapsed so far
                time += processVector[distance(processVector.begin(), j)].burstTime;

                /// Setting the metrics
                // turnaroundTime -- equal to burstTime always
                processVector[distance(processVector.begin(), j)].turnaroundTime = processVector[distance(processVector.begin(), j)].burstTime;
                
                // waitingTime -- for FCFS this is just equal to the Response Time
                // responseTime -- the only case where there is waiting time is if a new process arrives while old one is not yet done
                for (auto k = processVector.begin(); k != processVector.end(); ++k) {
                    if (processVector[distance(processVector.begin(), k)].arrivalTime < time && k > j) {
                        processVector[distance(processVector.begin(), k)].waitingTime = time - processVector[distance(processVector.begin(), k)].arrivalTime;
                        processVector[distance(processVector.begin(), k)].responseTime = processVector[distance(processVector.begin(), k)].waitingTime;
                    }
                }     
            }
        }
        else if (scheduleAlgorithm == "SRTF")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << endl;
            for (int q = 0; q < processVector.size(); q++)
            {

        }
        */

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
                        waitingTimeList.push_back({processVector[0].burstTime,time, time - processVector[0].arrivalTime, time, processVector[0].processID});
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
            waitingTimeList.push_back({ processVector[0].burstTime, time, time - processVector[0].arrivalTime, time, processVector[0].processID });
            time = time + processVector[0].burstTime;
        }
        else if (scheduleAlgorithm == "RR")
        {
            outputFile << "schedule algorithm: " << scheduleAlgorithm << endl;
            for (int q = 0; q < processVector.size(); q++)
            {

            }
        }

        //Syl's output logs
        int summationBT = 0, summationWT = 0, summationTT = 0, summationRT = 0;

        // re-sorting everything just to make life easier when displaying the metrics for each process
        sort(waitingTimeList.begin(), waitingTimeList.end(), compareProcessID);

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
        for (int i = 0; i < waitingTimeList.size(); i++) {
            outputFile << " Process " << i + 1 << ": " << waitingTimeList[i].waiting << "ns\n";
        }
        outputFile << "Average waiting time: " << (float)summationWT / waitingTimeList.size() << "ns\n";
        outputFile << "Turnaround times:\n";
        for (int i = 0; i < waitingTimeList.size(); i++) {
            outputFile << " Process " << i + 1 << ": " << waitingTimeList[i].turnaround << "ns\n";
        }
        outputFile << "Average turnaround time: " << (float)summationTT / waitingTimeList.size() << "ns\n";
        outputFile << "Response times:\n";
        for (int i = 0; i < waitingTimeList.size(); i++) {
            outputFile << " Process " << i + 1 << ": " << waitingTimeList[i].response << "ns\n";
        }
        outputFile << "Average response time: " << (float)summationRT / waitingTimeList.size() << "ns\n";
    }
    return 0;
}