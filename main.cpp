#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using std::cout;
using std::endl;
using std::string;
using std::vector;


void fcfsSimulation(vector<int> process_id, vector<int> burst_time, vector<int> arrival_time, int numProcesses);


int main(int argc, char** argv) {

    std::ifstream infile;

    vector<int> process_id;
    vector<int> burst_time;
    vector<int> arrival_time;
    int numProcesses = 0;

    // Check for correct number of arguments
    if (argc != 3) {
        cout << "Error - requires two arguments to run." << endl;
        return EXIT_FAILURE;
    } 

    // Read in file
    infile.open(argv[2]);

    if (infile.fail()) {
        cout << "Error - could not open file" << endl;
        return EXIT_FAILURE;
    } else {
        while (!infile.eof()) {

            int a, b, c;

            infile >> a >> b >> c;
            process_id.push_back(a);
            burst_time.push_back(b);
            arrival_time.push_back(c);

        }
    }

    infile.close();

    // cout << process_id.size() << endl;
    numProcesses = process_id.size();


    // Check for which process scheduler
    if (argv[1] == string("-fcfs")) {
        cout << "FCFS" << endl;
        fcfsSimulation(process_id, burst_time, arrival_time, numProcesses);

        // for (int i = 0; i < process_id.size(); ++i) {
        //     cout << process_id[i] << " " << burst_time[i] << " " << arrival_time[i] << endl;
        // }

        // for (int i : process_id) {
        //     cout << process_id[i-1] << " " << burst_time[i-1] << " " << arrival_time[i-1] <<endl;;
        // }

        // int totalProcessTime = 0;
        // for (int i : burst_time) {
        //     totalProcessTime += burst_time[i];
        // }

        // cout << "Total process time: " << totalProcessTime << endl;

    } else if (argv[1] == string("-sjf")) {
        cout << "SJF" << endl;
    } else if (argv[1] == string("-rr")) {
        cout << "RR" << endl;
    } else {
        cout << "Incorrect scheduling input" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


void fcfsSimulation(vector<int> process_id, vector<int> burst_time, vector<int> arrival_time, int numProcesses) {

    vector<int> waiting_time;
    vector<int> running_time;

    
    running_time.push_back(0);
    // Waiting time of first process is 0
    waiting_time.push_back(0);


    // Calculate the waiting time
    for(int i = 1; i < numProcesses; ++i) {

        // Calculate the running time by adding burst time of previous process
        running_time.push_back(running_time[i-1] + burst_time[i-1]);

        // Calculate waiting time for current process
        waiting_time.push_back(running_time[i] - arrival_time[i]);

        if (waiting_time[i] < 0) {
            waiting_time[i] = 0;
        }

        cout << "Waiting time for process " << process_id[i] << ": " << waiting_time[i] << endl;


    }



}