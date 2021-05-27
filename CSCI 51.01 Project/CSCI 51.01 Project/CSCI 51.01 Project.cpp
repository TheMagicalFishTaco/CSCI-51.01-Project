// CSCI 51.01 Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Process
{
    int arrivalTime, burstTime, priority, processID;
};

bool compareArrival(Process i1, Process i2)
{
    return (i1.arrivalTime < i2.arrivalTime);
}

bool compareBurst(Process i1, Process i2)
{
    return (i1.burstTime < i2.burstTime);
}

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
            processVector.push_back({ inputArrival, inputBurst, inputPriority, o + 1 });
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

            //sorts the stack by their burst time
            sort(processVector.begin(), processVector.end(), compareBurst);
            while (processVector.size() > 1)
            {
                outputFile << time << " " << processVector[0].processID << " " << processVector[0].burstTime <<"X" << "\n";
                time = time + processVector[0].burstTime;
                processVector.erase(processVector.begin());
            }
            //final process
            outputFile << time << " " << processVector[0].processID << " " << processVector[0].burstTime << "X" << "\n";
            time = time + processVector[0].burstTime;
            processVector.clear();
        }
        else if (scheduleAlgorithm == "SRTF")
        {

            outputFile << "schedule algorithm: " << scheduleAlgorithm << "\n";

            //sorts the stack by their arrival time
            sort(processVector.begin(), processVector.end(), compareArrival);
            for (int i = 0;i < processVector.size();i++) {
                cout << processVector[i].arrivalTime << endl;
            }

            while (processVector.size() > 1)
            {
                //This will check if the process will complete before the next process arrives, or if the current process has a lower burst time than the next process
                //if either condition's good, it will finish the current process completely
                if (((time + processVector[0].burstTime) < processVector[1].arrivalTime) || processVector[0].burstTime < processVector[1].burstTime)
                {

                    outputFile << time << " " << processVector[0].processID << " " << processVector[0].burstTime <<"X" << "\n";
                    time = time + processVector[0].burstTime;
                    processVector.erase(processVector.begin());

                    cout << "finished process" << endl;
                }
                //If the previous check fails, there are 2 scenarios:
                //1. The next process will arrive while the current one is being processed and has less burst time. In this case, you process as much as you can and then swap them around
                //2. Both processes have arrived but the next process has less burst time. In this case you immediately switch them around
                else
                {
                    //This is scenario 2, both processes are ready and waiting but the next process in the queue has less burst time
                    if ((time >= processVector[0].arrivalTime && time >= processVector[1].arrivalTime) && processVector[0].burstTime > processVector[1].burstTime)
                    {
                        processVector.push_back(processVector[0]);
                        processVector.erase(processVector.begin());
                        cout << "waiting process" << endl;
                    }
                    //This is scenario 1, process as much as you can before swapping to the newly arrived process
                    else
                    {
                        outputFile << time << " " << processVector[0].processID << " " << processVector[1].arrivalTime - time << "\n";
                        processVector[0].burstTime = (time + processVector[0].burstTime) - processVector[1].arrivalTime;
                        time = time + (processVector[1].arrivalTime - time);
                        processVector.push_back(processVector[0]);
                        processVector.erase(processVector.begin());
                        cout << "trying to finish process" << endl;
                    }
                }
            }
            //The final process
            outputFile << time << " " << processVector[0].processID << " " << processVector[0].burstTime << "X" << "\n";
            time = time + processVector[0].burstTime;
            processVector.clear();
        }
        //Lance's part
        else if (scheduleAlgorithm == "P")
        {
            outputFile << i+1 << " " << scheduleAlgorithm << "\n";

            //sorts the stack by their arrival time
            sort(processVector.begin(), processVector.end(), compareArrival);
            //the final process is separated, i don't know why but it doesn't like it if I "process" it within this while loop
            while (processVector.size() > 1)
            {
                //This will check if the process will complete before the next process arrives, or if the current process has a higher priority than the next process
                //if either condition's good, it will finish the current process completely
                if ((time + processVector[0].burstTime) < processVector[1].arrivalTime || processVector[0].priority < processVector[1].priority)
                {
                    outputFile << processVector[0].arrivalTime << " " << processVector[0].burstTime << " " << processVector[0].priority <<"X" << "\n";
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
                        outputFile << processVector[0].arrivalTime << " " << processVector[1].arrivalTime - time << " " << processVector[0].priority << "\n";
                        processVector[0].burstTime = (time + processVector[0].burstTime) - processVector[1].arrivalTime;
                        time = time + (processVector[1].arrivalTime - time);
                        iter_swap(processVector.begin(), processVector.begin() + 1);
                    }
                }
            }
            //The final process
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
        //Output logs, add the others later
        outputFile << "Total Time Elapsed: " << time <<" ns"<<"\n";
        outputFile << "Total CPU Burst Time: " << time << " ns"<<"\n";
        outputFile << "CPU Utilization: " << "\n";
        outputFile << "Throughput: " << numProcess / time << " processes/ns"<< "\n";
    }

}
