#include "algorithms.hpp"
#include <iostream>
#include <limits>

int main() {
  showPresentation();

  // Procesos originales (se mantienen para poder ejecutar varios algoritmos)
  Process P1("P1", 7);
  Process P2("P2", 3);
  Process P3("P3", 4);
  Process P4("P4", 2);
  Process P5("P5", 4);

  vector<Process> processesOriginal = {P1, P2, P3, P4, P5};
  vector<int> arrivalTimes = {0, 1, 2, 4, 5};

  bool running = true;
  while (running) {
    std::cout << "\n=== MENU Planificador ===\n";
    std::cout << "1) FIFO\n";
    std::cout << "2) SJF\n";
    std::cout << "3) SRTF\n";
    std::cout << "4) Round Robin (RR)\n";
    std::cout << "0) Salir\n";
    std::cout << "Seleccione una opcion: ";

    int opt;
    if (!(std::cin >> opt)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Entrada no valida. Intente de nuevo." << std::endl;
      continue;
    }

    if (opt == 0) {
      running = false;
      break;
    }

    // Crear copia fresca de procesos para cada ejecución
    vector<Process> processes = processesOriginal;
    Scheduler scheduler(processes, arrivalTimes);

    switch (opt) {
      case 1:
        scheduler.FIFO();
        scheduler.showProcessTable();
        scheduler.showGanttDiagram();
        break;
      case 2:
        scheduler.SJF();
        scheduler.showProcessTable();
        scheduler.showGanttDiagram();
        break;
      case 3:
        scheduler.SRTF();
        scheduler.showProcessTable();
        scheduler.showGanttDiagram();
        break;
      case 4: {
        std::cout << "Ingrese quantum (entero > 0): ";
        int q;
        if (!(std::cin >> q) || q < 1) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Quantum invalido. Se usara 1 por defecto." << std::endl;
          q = 1;
        }
        scheduler.RR(q);
        scheduler.showProcessTable();
        scheduler.showGanttDiagram();
        break;
      }
      default:
        std::cout << "Opcion no reconocida." << std::endl;
    }

    // Opciones de visualización avanzadas
    std::cout << "\nDesea ver la animacion grafica del Gantt? (s/n): ";
    char ans;
    std::cin >> ans;
    if (ans == 's' || ans == 'S') {
      // Por defecto usa los valores por defecto de la libreria grafica
      scheduler.displayAnimatedGanttDiagram();
    }

    std::cout << "\nDesea ver el Gantt paso a paso? (s/n): ";
    std::cin >> ans;
    if (ans == 's' || ans == 'S') {
      scheduler.displayStepByStepGanttDiagram();
    }
  }

  return 0;
}
