#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

// Process implemenation
class Process {
private:
    int id;
    int tickets;
public:
    Process(int id, int tickets) : id(id), tickets(tickets) {}
    int getId() const {
        return id;
    }
    int getTickets() const {
        return tickets;
    }
};

// Scheduler implementation
class Scheduler {
private:
    vector<Process> processes;
public:
    void getProcess(const Process& process) {
        processes.push_back(process);
    }
    void placeTickets() {
        int totalTickets = 0;

        for (const Process& process : processes) {
            totalTickets += process.getTickets();
        }

        for (Process& process : processes) {
            double proportion = static_cast<double>(process.getTickets()) / totalTickets;
            process = Process(process.getId(), static_cast<int>(proportion * 100));
        }
    }

    Process getWinner() const {
        int randomNumber = rand() % 100 + 1;

        int cumulativeTickets = 0;
        for (const Process& process : processes) {
            cumulativeTickets += process.getTickets();
            if (randomNumber <= cumulativeTickets) {
                return process;
            }
        }

        throw runtime_error("Error: No process selected.");
    }
};

int main() {
    srand(time(NULL));
    Scheduler schedule;
    schedule.getProcess(Process(1, 10));
    schedule.getProcess(Process(2, 20));
    schedule.getProcess(Process(3, 30));
    schedule.placeTickets();
    Process winner = schedule.getWinner();
    cout << "Process #" << winner.getId() << " has won the lottery!" << endl;

    return 0;
}