#include "algorithms.hpp"

int main() {
  showPresentation();

  Process P1("P1", 7);
  Process P2("P2", 3);
  Process P3("P3", 4);
  Process P4("P4", 2);
  Process P5("P5", 4);
  // Process P6("P6", 1);
  // Process P7("P7", 5);
  // Process P8("P8", 8);
  // Process P9("P9", 3);
  // Process P10("P10", 2);

  vector<Process> processes = {P1, P2, P3, P4, P5/*, P6, P7, P8, P9, P10*/};
  vector<int> arrivalTimes = {0, 1, 2, 4, 5/*, 3, 1, 4, 7, 6*/};

  Scheduler scheduler(processes, arrivalTimes);
  scheduler.showProcessTable();

  // scheduler.FIFO();
  // scheduler.showGanttDiagram();
  // scheduler.SJF();
  // scheduler.showGanttDiagram();
  // scheduler.SRTF();
  // scheduler.showGanttDiagram();
  // scheduler.RR(3);
  // scheduler.showGanttDiagram();

  // scheduler.FIFO();
  // scheduler.showAnimatedGanttDiagram();
  // scheduler.displayAnimatedGanttDiagram();
  // scheduler.SJF();
  // scheduler.showAnimatedGanttDiagram();
  // scheduler.displayAnimatedGanttDiagram();
  // scheduler.SRTF();
  // scheduler.showAnimatedGanttDiagram();
  // scheduler.displayAnimatedGanttDiagram();
  scheduler.RR(3);
  // scheduler.showAnimatedGanttDiagram();
  scheduler.displayAnimatedGanttDiagram();
  scheduler.displayStepByStepGanttDiagram();

  return 0;
}

