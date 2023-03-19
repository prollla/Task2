#include <iostream>
#include "Components.h"
#include <vector>
using namespace std;


int main() {
    int input;
    int processId;
    std::cout << "Enter process id" << std::endl;
    std::cin >> processId;
    std::cout << std::endl;
    Process process(processId);
    while (input != 6) {
        cout << "Choose command" << endl;
        cout << "1. Show process info." << endl;
        cout << "2. Thread add." << endl;
        cout << "3. Lib add." << endl;
        cout << "4. Delete thread." << endl;
        cout << "5. Lib delete." << endl;
        cout << "6. Exit." << endl;
        cin >> input;
        switch (input) {
            case 1: {
                process.getProcessInfo();
                break;
            }
            case 2: {
                cout << "Enter thread id: " << endl;
                int threadId;
                cin >> threadId;
                vector<Thread> threads = process.getThreads();
                for (int i = 0; i < threads.size(); ++i) {
                    if (threads[i].getId() == threadId) {
                        cout << "Thread with id: " << threadId << "already usage" << endl;
                        break;
                    }
                }
                int threadMemory;
                threadMemory = rand();
                cout << "Thread usage memory: " << threadMemory << endl;
                Thread thread(threadId, threadMemory);
                process.addThread(thread);
                break;

            }
            case 3: {
                std::cout << "In what thread? (id)" << std::endl;
                int threadId = 0;
                std::cin >> threadId;
                std::vector<Thread> threads = process.getThreads();
                for (int i = 0; i < threads.size(); ++i) {
                    if (threads[i].getId() == threadId) {
                        std::cout << "Input lib id" << std::endl;
                        int libId = 0;
                        int libMemory = rand();
                        std::cin >> libId;
                        Lib lib(libId, libMemory);
                        process.addLib(threads[i], lib);
                        std::cout << "Thread was added" << std::endl;
                    }
                    else {
                        std::cout << "Incorrect id" << std::endl;
                    }
                }
                break;
            }
            case 4: {
                std::cout << "What thread delete?" << std::endl;
                int threadId = 0;
                std::cin >> threadId;
                process.deleteThreadFromProcess(threadId);
                break;
            }
            case 5: {
                std::cout << " In which thread to remove the library:" << std::endl;
                int threadId = 0;
                std::cin >> threadId;
                std::vector<Thread> threads = process.getThreads();
                for (int i = 0; i < threads.size(); ++i) {
                    if (threads[i].getId() == threadId) {
                        std::cout << "Lib id to delete" << std::endl;
                        int libId = 0;
                        std::cin >> libId;
                        process.deleteLib(threads[i], libId);
                    } else {
                        cout << "Incorrect id" << endl;
                    }
                }
                break;
            }
            case 6: {
                cout << "End." << endl;
                break;
            }
        }
    }
}
