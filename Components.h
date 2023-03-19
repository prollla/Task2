//
// Created by skull on 19.03.2023.
//

#ifndef UNTITLED_COMPONENTS_H
#define UNTITLED_COMPONENTS_H
using namespace std;
#include <vector>
#include <iostream>


class Lib {
private:
    int id;
    int memory;
public:
    Lib(int id, int memory):id(id), memory(memory){}

    int getLibId(){
        return id;
    }
    int getLibMemory(){
        return memory;
    }
    void LibInfo(){
        cout<< "Id lib: " << id <<endl;
        cout <<"Memory usage lib: " << memory << endl;
    }
};

class Thread {
private:
    int id;
    int memory;
    vector<Lib> libs;

public:
    Thread(int id, int memory): id(id), memory(memory){}

    int getId(){
        return id;
    }
    int getMemory(){
        int libsMemory = 0;
        for(int i=0; i<libs.size(); ++i){
            libsMemory+=libs[i].getLibMemory();
        }
        return memory + libsMemory;
    }

    int getAfterRemoveMemory(){
        return memory;
    }

    void addLib(Lib lib){
        libs.push_back(lib);
    }

    vector<Lib> getLibs() {
        return libs;
    };

    void deleteLibFomThread(int libId) {
        int index = -1;
        for (int i = 0; i < libs.size(); i++) {
            if (libs[i].getLibId() == libId) {
                index = i;
            }
        }
        libs.erase(libs.begin() + index);
    }

    void getInfoThread(){
        cout<< "Id thread: " << id <<endl;
        cout <<"Thread usage memory: " << memory << endl;
        int libsMemoryUsage = 0;
        for (int i = 0; i < libs.size(); ++i) {
            libsMemoryUsage += libs[i].getLibMemory();
        }
        std::cout << "All memory usage:" << memory + libsMemoryUsage << std::endl;
        std::cout << "--Libs info--" << std::endl;
        for (int i = 0; i < libs.size(); ++i) {
            libs[i].LibInfo();
        }
        std::cout << std::endl;
    }
};

class Process{
private:
    int id;
    int memory=0;
    vector<Thread> threads;
    vector<Lib> libs;
public:
    Process(int id): id(id) {}

    vector<Thread> getThreads(){
        return threads;
    }
    void addThread(Thread thread){
        threads.push_back(thread);
    }
    void getProcessInfo(){
        cout << "Process info" << endl;
        cout << "Id process: " << id << endl;
        int threadMemory = 0;
        for(int i =0; i<threads.size(); ++i){
            threadMemory+=threads[i].getMemory();
        }
        cout << "All memory usage in process: " << memory + threadMemory << endl;
        cout << "--Thread info--" << endl;
        for(int i = 0; i < threads.size(); ++i){
            threads[i].getInfoThread();
        }
    }
    void addLib(Thread threadToLib, Lib libToThread) {
        std::vector<Lib> libs = threadToLib.getLibs();
        Thread tempThread(threadToLib.getId(), threadToLib.getAfterRemoveMemory());
        for (int i = 0; i < libs.size(); ++i) {
            tempThread.addLib(libs[i]);
        }
        tempThread.addLib(libToThread);
        deleteThreadFromProcess(threadToLib.getId());
        addThread(tempThread);
    }
    void deleteLib(Thread threadToDelete, int libIdToDelete) {
        std::vector<Lib> libs = threadToDelete.getLibs();
        for (int i = 0; i < libs.size(); ++i)
        {
            if (libs[i].getLibId() == libIdToDelete)
            {
                Thread tempThread(threadToDelete.getId(), threadToDelete.getAfterRemoveMemory());
                threadToDelete.deleteLibFomThread(libIdToDelete);

                std::vector<Lib> newLibs = threadToDelete.getLibs();
                for (int i = 0; i < newLibs.size(); ++i) {
                    tempThread.addLib(newLibs[i]);
                }
                deleteThreadFromProcess(threadToDelete.getId());
                addThread(tempThread);
                std::cout << "Lib was deleted" << std::endl;
            }
            else
            {
                std::cout << "Lib not found " << endl;
            }
        }
    }
    void deleteThreadFromProcess(int threadId) {
        for (int i = 0; i < threads.size(); i++) {
            if (threads[i].getId() == threadId) {
                for (int i = 0; i < threads.size(); i++)
                {
                    if (threads[i].getId() == threadId)
                    {
                        threads.erase(threads.begin() + i);
                        std::cout << "Thread was deleted" << std::endl;
                    }
                }
            }
            else
            {
                cout << "Thread not found " << endl;
            }
        }
    }
};
#endif //UNTITLED_COMPONENTS_H
