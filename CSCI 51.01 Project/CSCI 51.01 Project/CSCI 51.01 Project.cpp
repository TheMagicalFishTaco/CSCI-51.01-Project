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
    int arrivalTime, burstTime, priority, PID, waitingTime, turnaroundTime, responseTime;

    Process() {
        arrivalTime = 0;
        burstTime = 0;
        priority = 0;
        waitingTime = 0;
        turnaroundTime = 0;
        responseTime = 0;
    }
};

bool compareByArrivalTime (const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

bool compareByPID (const Process &a, const Process &b) {
    return a.PID < b.PID;
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
            Process p;
            p.arrivalTime = inputArrival;
            p.burstTime = inputBurst;
            p.priority = inputPriority;
            p.PID = o + 1;
            processVector.push_back(p);
        }

        if (scheduleAlgorithm == "FCFS")
        {
            outputFile << i+1 << " " << scheduleAlgorithm << "\n";
            sort(processVector.begin(), processVector.end(), compareByArrivalTime);

            for (auto j = processVector.begin(); j != processVector.end(); ++j) {
                // this is to fast forward the time in case processes haven't arrived yet
                if (time < processVector[distance(processVector.begin(), j)].arrivalTime) {
                    time = processVector[distance(processVector.begin(), j)].arrivalTime;
                }

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

        //Lance's part
        else if (scheduleAlgorithm == "P")
        {
            outputFile << i+1 << " " << scheduleAlgorithm << "\n";
            //sorts the stack by their arrival time
            sort(processVector.begin(), processVector.end(), compareByArrivalTime);
            //the final process is separated, i don't know why but it doesn't like it if I "process" it within this while loop
            while (processVector.size() > 1)
            {
                //This will check if the process will complete before the next process arrives, or if the current process has a higher priority than the next process
                //if either condition's good, it will finish the current process completely
                if ((time + processVector[0].burstTime) < processVector[1].arrivalTime || processVector[0].priority < processVector[1].priority)
                {
                    outputFile << time << " " << processVector[0].burstTime << " " << processVector[0].priority << "X\n";
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
                        outputFile << time << " " << processVector[1].arrivalTime - time << " " << processVector[0].priority << "\n";
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

        int summationBT = 0, summationWT = 0, summationTT = 0, summationRT = 0;

        // re-sorting everything just to make life easier when displaying the metrics for each process
        sort(processVector.begin(), processVector.end(), compareByPID);

        //gets the sum of the metrics, which will be later divided by the vector size to get average
        for (auto i = processVector.begin(); i != processVector.end(); ++i) {
            summationBT += (*i).burstTime;
            summationWT += (*i).waitingTime;
            summationTT += (*i).turnaroundTime;
            summationRT += (*i).responseTime;
        }

        // Output logs
        outputFile << "Total Time Elapsed: " << time <<" ns"<<"\n";
        outputFile << "Total CPU Burst Time: " << summationBT << " ns"<<"\n";
        outputFile << "CPU Utilization: " << (int) (summationBT / time * 100) << "%\n";
        outputFile << "Throughput: " << (float) processVector.size() / time << " processes/ns" << "\n";
        outputFile << "Waiting times:\n";
        for (int i = 0; i < processVector.size(); i++) {
            outputFile << " Process " << i+1 << ": " << processVector[i].waitingTime << "ns\n";
        }
        outputFile << "Average waiting time: " << (float) summationWT / processVector.size() << "ns\n";
        outputFile << "Turnaround times:\n";
        for (int i = 0; i < processVector.size(); i++) {
            outputFile << " Process " << i+1 << ": " << processVector[i].turnaroundTime << "ns\n";
        }
        outputFile << "Average turnaround time: " << (float) summationTT / processVector.size() << "ns\n";
        outputFile << "Response times:\n";
        for (int i = 0; i < processVector.size(); i++) {
            outputFile << " Process " << i+1 << ": " << processVector[i].responseTime << "ns\n";
        }
        outputFile << "Average response time: " << (float) summationRT / processVector.size() << "ns\n";
    }
    return 0;
}

