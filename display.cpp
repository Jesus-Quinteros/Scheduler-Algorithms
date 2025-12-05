#include "raylib.h"
#include "algorithms.hpp"
#include <iostream>

void Scheduler::displayProcessTable(int startX, int startY, int fontSize) {
    int center = 10;

    // Línea separadora
    DrawLine(startX, startY - 30 + fontSize, startX + 630, startY - 30 + fontSize, BLACK);

    // Encabezados
    DrawText("Processes", startX + center, startY, fontSize, BLACK);
    DrawText("Burst_Time", startX + 150 + center, startY, fontSize, BLACK);
    DrawText("Arrival_Time", startX + 300 + center, startY, fontSize, BLACK);
    DrawText("Completion_Time", startX + 450 + center, startY, fontSize, BLACK);

    // Línea separadora
    DrawLine(startX, startY + fontSize + 5, startX + 630, startY + fontSize + 5, BLACK);

    // Filas
    for (int i = 0; i < processNames.size(); i++) {
        int rowY = startY - 10 + (i + 2) * (fontSize + 5);

        // Nombre del proceso
        DrawText(processNames[i].c_str(), startX + center * 6, rowY, fontSize, BLACK);

        // Burst time
        DrawText(TextFormat("%d", processes[i].originalBurstTime),
                 startX + 150 + center * 7, rowY, fontSize, BLACK);

        // Arrival time
        DrawText(TextFormat("%d", arrivalTimes[i]),
                 startX + 300 + center * 7, rowY, fontSize, BLACK);
        // Completion time
        DrawText(TextFormat("%d", processes[i].completionTime),
                 startX + 450 + center * 7, rowY, fontSize, BLACK);
    }

    // Línea inferior
    DrawLine(startX, startY + (processNames.size() + 2) * (fontSize + 5),
             startX + 630, startY + (processNames.size() + 2) * (fontSize + 5), BLACK);

    // Separadores verticales
    DrawLine(startX, startY - 30 + fontSize, startX, startY + (processNames.size() + 2) * (fontSize + 5), BLACK);
    DrawLine(startX + 150, startY - 30 + fontSize, startX + 150, startY + (processNames.size() + 2) * (fontSize + 5), BLACK);
    DrawLine(startX + 300, startY - 30 + fontSize, startX + 300, startY + (processNames.size() + 2) * (fontSize + 5), BLACK);
    DrawLine(startX + 450, startY - 30 + fontSize, startX + 450, startY + (processNames.size() + 2) * (fontSize + 5), BLACK);
    DrawLine(startX + 630, startY - 30 + fontSize, startX + 630, startY + (processNames.size() + 2) * (fontSize + 5), BLACK);
}

void Scheduler::displayAnimatedGanttDiagram(int milliseconds) {
  if (milliseconds < 0) {
    std::cerr << "--> ERROR: 'displayAnimatedGanttDiagram()' function does not allow a negative parameter.\n";
    exit(EXIT_FAILURE);
  }
  SetTraceLogLevel(LOG_WARNING);

    int sepYbetween = 20;
    int posXgeneral = 150;
    int posYgeneral = 40;

    // Inicializar ventana
    unsigned int W_width = ((totalTime + 1) * 30) + (posXgeneral * 2) - 60;
    if (W_width < 750) W_width = 750;
    unsigned int W_height = ((processes.size() + 1) * 30) + (processes.size() + 2) * 25 + (sepYbetween * 5) + posYgeneral;

    InitWindow(W_width, W_height, "SCHEDULER");
    SetTargetFPS(60);

    int finalTablePos = (processNames.size() + 2) * 25 + posYgeneral;

    int cellWidth = 30;   // ancho de cada tick
    int cellHeight = 30;  // alto de cada proceso
    int offsetX = 150;    // espacio para nombres
    int offsetY = finalTablePos + sepYbetween * 3;    // espacio superior

    // Paleta de colores para procesos
    Color colors[10] = { RED, GREEN, BLUE, ORANGE, PURPLE, PINK, GRAY, YELLOW, DARKBLUE, BROWN };

    for (int frame = 0; frame < totalTime && !WindowShouldClose(); frame++) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        displayProcessTable(posXgeneral, posYgeneral, 20);

        // Título
        DrawText(TextFormat("[%s]", algorithmName.c_str()), posXgeneral, sepYbetween + finalTablePos, 20, BLACK);

        // Dibujar nombres de procesos
        for (int i = 0; i < processNames.size(); i++) {
            DrawText(processNames[i].c_str(), posXgeneral - 60, offsetY + i * cellHeight, 20, BLACK);
        }

        // Dibujar líneas de tiempo hasta el frame actual
        for (int i = 0; i < processNames.size(); i++) {
            for (int j = 0; j <= frame; j++) {
                std::string cell = processesLines[i][j];

                if (cell.find("#") != std::string::npos) {
                    DrawRectangle(offsetX + j * cellWidth,
                                  offsetY + i * cellHeight,
                                  cellWidth, cellHeight,
                                  colors[i % 10]);
                }
                if (cell.find("X") != std::string::npos) {
                    DrawText("X",
                       offsetX + j * cellWidth + cellWidth/2 - 5,   // centrado horizontal
                       offsetY + i * cellHeight + cellHeight/2 - 10, // centrado vertical
                       20, BLACK);
                }

                // Bordes de celda
                DrawRectangleLines(offsetX + j * cellWidth,
                                   offsetY + i * cellHeight,
                                   cellWidth, cellHeight,
                                   BLACK);
            }
        }

        // Dibujar escala de tiempo
        for (int j = 0; j < totalTime; j++) {
            DrawText(TextFormat("%d", j),
                     offsetX + j * cellWidth + 10,
                     offsetY + processNames.size() * cellHeight + 10,
                     15, BLACK);
        }

        EndDrawing();

        // Espera entre frames
        WaitTime(milliseconds / 1000.0f);
    }

    // Mostrar último frame indefinidamente
    while (!WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginDrawing();
      ClearBackground(RAYWHITE);

      displayProcessTable(posXgeneral, posYgeneral, 20);

      // Título
      DrawText(TextFormat("[%s]", algorithmName.c_str()), posXgeneral, sepYbetween + finalTablePos, 20, BLACK);

      // Dibujar nombres de procesos
      for (int i = 0; i < processNames.size(); i++) {
          DrawText(processNames[i].c_str(), posXgeneral - 60, offsetY + i * cellHeight, 20, BLACK);
      }

      for (int i = 0; i < processNames.size(); i++) {
          for (int j = 0; j < processesLines[i].size(); j++) {
              std::string cell = processesLines[i][j];

              if (cell.find("#") != std::string::npos) {
                  DrawRectangle(offsetX + j * cellWidth,
                                offsetY + i * cellHeight,
                                cellWidth, cellHeight,
                                colors[i % 10]);
              }
              if (cell.find("X") != std::string::npos) {
                    DrawText("X",
                       offsetX + j * cellWidth + cellWidth/2 - 5,   // centrado horizontal
                       offsetY + i * cellHeight + cellHeight/2 - 10, // centrado vertical
                       20, BLACK);
              }

              // Bordes de celda
              DrawRectangleLines(offsetX + j * cellWidth,
                                 offsetY + i * cellHeight,
                                 cellWidth, cellHeight,
                                 BLACK);
          }
      }

      // Dibujar escala de tiempo
      for (int j = 0; j < totalTime; j++) {
          DrawText(TextFormat("%d", j),
                   offsetX + j * cellWidth + 10,
                   offsetY + processNames.size() * cellHeight + 10,
                   15, BLACK);
      }

      EndDrawing();
    }

    CloseWindow();
}

void Scheduler::displayStepByStepGanttDiagram() {
  SetTraceLogLevel(LOG_WARNING);

    int sepYbetween = 20;
    int posXgeneral = 150;
    int posYgeneral = 40;

    // Inicializar ventana
    unsigned int W_width = ((totalTime + 1) * 30) + (posXgeneral * 2) - 60;
    if (W_width < 750) W_width = 750;
    unsigned int W_height = ((processes.size() + 1) * 30) + (processes.size() + 2) * 25 + (sepYbetween * 5) + posYgeneral;

    InitWindow(W_width, W_height, "SCHEDULER");
    SetTargetFPS(60);

    int finalTablePos = (processNames.size() + 2) * 25 + posYgeneral;

    int cellWidth = 30;   // ancho de cada tick
    int cellHeight = 30;  // alto de cada proceso
    int offsetX = 150;    // espacio para nombres
    int offsetY = finalTablePos + sepYbetween * 3;    // espacio superior

    // Paleta de colores para procesos
    Color colors[10] = { RED, GREEN, BLUE, ORANGE, PURPLE, PINK, GRAY, YELLOW, DARKBLUE, BROWN };

    int frame = 0;

    while (frame < totalTime && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        displayProcessTable(posXgeneral, posYgeneral, 20);

        // Título
        DrawText(TextFormat("[%s]", algorithmName.c_str()), posXgeneral, sepYbetween + finalTablePos, 20, BLACK);

        // Dibujar nombres de procesos
        for (int i = 0; i < processNames.size(); i++) {
            DrawText(processNames[i].c_str(), posXgeneral - 60, offsetY + i * cellHeight, 20, BLACK);
        }

        // Dibujar líneas de tiempo hasta el frame actual
        for (int i = 0; i < processNames.size(); i++) {
            for (int j = 0; j <= frame; j++) {
                std::string cell = processesLines[i][j];

                if (cell.find("#") != std::string::npos) {
                    DrawRectangle(offsetX + j * cellWidth,
                                  offsetY + i * cellHeight,
                                  cellWidth, cellHeight,
                                  colors[i % 10]);
                }
                if (cell.find("X") != std::string::npos) {
                    DrawText("X",
                       offsetX + j * cellWidth + cellWidth/2 - 5,   // centrado horizontal
                       offsetY + i * cellHeight + cellHeight/2 - 10, // centrado vertical
                       20, BLACK);
                }

                // Bordes de celda
                DrawRectangleLines(offsetX + j * cellWidth,
                                   offsetY + i * cellHeight,
                                   cellWidth, cellHeight,
                                   BLACK);
            }
        }

        // Dibujar escala de tiempo
        for (int j = 0; j < totalTime; j++) {
            DrawText(TextFormat("%d", j),
                     offsetX + j * cellWidth + 10,
                     offsetY + processNames.size() * cellHeight + 10,
                     15, BLACK);
        }

        EndDrawing();

        // Avanzar si se presiona Enter
        if (IsKeyPressed(KEY_ENTER)) {
          frame++;
        }
    }

    // Mostrar último frame indefinidamente
    while (!WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginDrawing();
      ClearBackground(RAYWHITE);

      displayProcessTable(posXgeneral, posYgeneral, 20);

      // Título
      DrawText(TextFormat("[%s]", algorithmName.c_str()), posXgeneral, sepYbetween + finalTablePos, 20, BLACK);

      // Dibujar nombres de procesos
      for (int i = 0; i < processNames.size(); i++) {
          DrawText(processNames[i].c_str(), posXgeneral - 60, offsetY + i * cellHeight, 20, BLACK);
      }

      for (int i = 0; i < processNames.size(); i++) {
          for (int j = 0; j < processesLines[i].size(); j++) {
              std::string cell = processesLines[i][j];

              if (cell.find("#") != std::string::npos) {
                  DrawRectangle(offsetX + j * cellWidth,
                                offsetY + i * cellHeight,
                                cellWidth, cellHeight,
                                colors[i % 10]);
              }
              if (cell.find("X") != std::string::npos) {
                    DrawText("X",
                       offsetX + j * cellWidth + cellWidth/2 - 5,   // centrado horizontal
                       offsetY + i * cellHeight + cellHeight/2 - 10, // centrado vertical
                       20, BLACK);
              }

              // Bordes de celda
              DrawRectangleLines(offsetX + j * cellWidth,
                                 offsetY + i * cellHeight,
                                 cellWidth, cellHeight,
                                 BLACK);
          }
      }

      // Dibujar escala de tiempo
      for (int j = 0; j < totalTime; j++) {
          DrawText(TextFormat("%d", j),
                   offsetX + j * cellWidth + 10,
                   offsetY + processNames.size() * cellHeight + 10,
                   15, BLACK);
      }

      EndDrawing();
    }

    CloseWindow();
}

