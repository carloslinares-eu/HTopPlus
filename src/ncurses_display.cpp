#include <curses.h>
#include <string>
#include <thread>
#include <vector>

#include "format.h"
#include "ncurses_display.h"
#include "system.h"

using std::string;
using std::to_string;

std::string NCursesDisplay::ProgressBar(float percent) {
    std::string result{"0%"};
    int size{50};
    float bars{percent * static_cast<float>(size)};

    for (int i{0}; i < size; ++i) {
        result += static_cast<float>(i) <= bars ? '|' : ' ';
    }

    string display{to_string(percent * 100).substr(0, 4)};
    if (percent < 0.1 || percent == 1.0)
        display = " " + to_string(percent * 100).substr(0, 3);
    return result + " " + display + "/100%";
}

void NCursesDisplay::DisplaySystem(System &system, WINDOW *window) {
    int row{0};
    mvwprintw(window, ++row, 2, "%s", ("OS: " + system.getOperatingSystem()).c_str());
    mvwprintw(window, ++row, 2, "%s", ("Kernel: " + system.getKernel()).c_str());
    mvwprintw(window, ++row, 2, "CPU: ");
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, row, 10, "");
    wprintw(window, "%s", ProgressBar(system.getSystemCPU().getUtilization()).c_str());
    wattroff(window, COLOR_PAIR(1));
    mvwprintw(window, ++row, 2, "Memory: ");
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, row, 10, "");
    wprintw(window, "%s", ProgressBar(system.getMemoryUtilization()).c_str());
    wattroff(window, COLOR_PAIR(1));
    mvwprintw(window, ++row, 2,
              "%s", ("Total processes: " + to_string(system.getTotalProcesses())).c_str());
    mvwprintw(
            window, ++row, 2,
            "%s", ("Running processes: " + to_string(system.getRunningProcesses())).c_str());
    mvwprintw(window, ++row, 2,
              "%s", ("Up Time: " + Format::ElapsedTime(system.getUpTime())).c_str());
    wrefresh(window);
}

void NCursesDisplay::DisplayProcesses(std::vector<Process>& processes,
                                      WINDOW *window, int n) {
    int row{0};
    int const pid_column{2};
    int const user_column{9};
    int const cpu_column{16};
    int const ram_column{26};
    int const time_column{35};
    int const command_column{46};
    wattron(window, COLOR_PAIR(2));
    mvwprintw(window, ++row, pid_column, "PID");
    mvwprintw(window, row, user_column, "USER");
    mvwprintw(window, row, cpu_column, "cpu[%%]");
    mvwprintw(window, row, ram_column, "RAM[MB]");
    mvwprintw(window, row, time_column, "TIME+");
    mvwprintw(window, row, command_column, "COMMAND");
    wattroff(window, COLOR_PAIR(2));
    for (int i = 0; i < n; ++i) {

        mvwprintw(window, ++row, pid_column, "%s", (string(window->_maxx - 2, ' ').c_str()));

        mvwprintw(window, row, pid_column, "%s", to_string(processes[i].getPid()).c_str());
        mvwprintw(window, row, user_column, "%s", processes[i].getUser().substr(0, 4).c_str());
        float cpu = processes[i].getCpuUtilization() * 100;
        mvwprintw(window, row, cpu_column, "%s", to_string(cpu).substr(0, 4).c_str());
        mvwprintw(window, row, ram_column, "%s", (std::to_string(processes[i].getRamUtilization())).c_str());
        mvwprintw(window, row, time_column,
                  "%s", Format::ElapsedTime(processes[i].getUpTime()).c_str());
        mvwprintw(window, row, command_column,
                  "%s", processes[i].getCommand().substr(0, window->_maxx - 46).c_str());
    }
}

[[noreturn]] void NCursesDisplay::Display(System &system, int n) {
    initscr();
    noecho();
    cbreak();
    start_color();

    int x_max{getmaxx(stdscr)};
    WINDOW *system_window = newwin(9, x_max - 1, 0, 0);
    WINDOW *process_window =
            newwin(3 + n, x_max - 1, system_window->_maxy + 1, 0);

    while (true) {
        init_pair(1, COLOR_BLUE, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        box(system_window, 0, 0);
        box(process_window, 0, 0);
        system.Running();
        DisplaySystem(system, system_window);
        DisplayProcesses(system.getSystemProcesses(), process_window, n);
        wrefresh(system_window);
        wrefresh(process_window);
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
