#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

void do_work(int process_number) {
    auto start_time = std::chrono::steady_clock::now();
    std::cout << "[Process " << process_number << "] Starting work at "
              << std::chrono::duration_cast<std::chrono::milliseconds>(start_time.time_since_epoch()).count() / 1000.0
              << " seconds\n";

    int i = 0;
    for (int j = 0; j < 20000000; ++j) {
        i += 1;
    }

    auto end_time = std::chrono::steady_clock::now();
    double response_time = std::chrono::duration<double>(end_time - start_time).count();
    std::cout << "[Process " << process_number << "] Finished work at "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_time.time_since_epoch()).count() / 1000.0
              << " seconds. Response time: " << response_time << " seconds\n";
}

int main() {
    const int num_processes = 5;
    std::vector<std::thread> threads;

    // Start threads
    for (int process_number = 1; process_number <= num_processes; ++process_number) {
        threads.emplace_back(do_work, process_number);
        std::cout << "[Process " << process_number << "] Started.\n";
    }

    // Join threads
    int completed_count = 0;
    for (int process_number = 1; process_number <= num_processes; ++process_number) {
        threads[process_number - 1].join();
        ++completed_count;
        std::cout << "[Process " << process_number << "] Joined. Total processes joined: "
                  << completed_count << "/" << num_processes << "\n";
    }

    std::cout << "All " << completed_count << " processes completed.\n";
    return 0;
}
