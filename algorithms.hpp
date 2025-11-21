#pragma once

#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

enum ProcessState { NEW, READY, RUNNING, FINISHED };

class Process {
  private:
    string name;
    int burstTime;
    int arrivalTime = -1;
    vector<string> processLine;
    ProcessState processState = NEW;

    void decrementBurstTime() { burstTime--; }

    friend class Scheduler;
    friend class FIFO;
    friend class SJF;
    friend class SRTF;
    friend class RR;
    friend struct CompareBurstTime;

  public:
    Process() : name("NONE"), burstTime(1) {}
    Process(int burstTime);
    Process(string name, int burstTime);
    ~Process() {}
};

class FIFO {
  private:
    int timeCurrent;
    void init(vector<Process> processes, vector<int> arrivalTimes, int& totalTime, vector<vector<string>>& processesLines, vector<string>& processNames, Process CPU);
    friend class Scheduler;
};

class SJF {
  private:
    int timeCurrent;
    void init(vector<Process> processes, vector<int> arrivalTimes, int& totalTime, vector<vector<string>>& processesLines, vector<string>& processNames, Process CPU);
    friend class Scheduler;
};

class SRTF {
  private:
    int timeCurrent;
    void init(vector<Process> processes, vector<int> arrivalTimes, int& totalTime, vector<vector<string>>& processesLines, vector<string>& processNames, Process CPU);
    friend class Scheduler;
};

class RR {
  private:
    int timeCurrent;
    void init(vector<Process> processes, vector<int> arrivalTimes, int& totalTime, vector<vector<string>>& processesLines, vector<string>& processNames, Process CPU, int quantum);
    friend class Scheduler;
};

class Scheduler {
  private:
    FIFO fifo;
    SJF sjf;
    SRTF srtf;
    RR rr;

    string algorithmName;
    Process CPU;

    vector<Process> processes;
    vector<int> arrivalTimes;
    int totalTime;
    vector<vector<string>> processesLines;
    vector<string> processNames;

    void displayProcessTable(int startX, int startY, int fontSize);

  public:
    Scheduler(vector<Process>& processes, vector<int>& arrivalTimes);
    ~Scheduler() {}

    void FIFO() { fifo.init(processes, arrivalTimes, totalTime, processesLines, processNames, CPU); algorithmName = "FIFO"; }
    void SJF() { sjf.init(processes, arrivalTimes, totalTime, processesLines, processNames, CPU); algorithmName = "SJF"; }
    void SRTF() { srtf.init(processes, arrivalTimes, totalTime, processesLines, processNames, CPU); algorithmName = "SRTF"; }
    void RR(int quantum = 1) { rr.init(processes, arrivalTimes, totalTime, processesLines, processNames, CPU, quantum); algorithmName = "Round Robin"; }

    void showProcessTable();
    void showGanttDiagram();
    void showAnimatedGanttDiagram(int milliseconds = 150);
    void displayAnimatedGanttDiagram(int milliseconds = 150);
};

void showPresentation();

