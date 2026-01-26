#include <iostream>
#include <bits/stdc++.h>
#include <mutex>
#include <thread>
using namespace std;

// The Singleton Design Pattern ensures that a class has only one instance and provides a global point of access to it.
// Key Features
// Only one instance exists
// Global access point
// Lazy or eager initialization
// Thread-safe (in modern implementations)

class Singleton{
private:
    static Singleton* instance;
    static mutex mtx; // Mutex for thread safety
    int data;

    // Private constructor to prevent instantiation
    Singleton() : data(0) {}

    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // Double checked locking pattern
    static Singleton* getInstance(){
        // First check (no locking) - for performance
        if(instance == nullptr){
            // Lock only when instance is null
            lock_guard<mutex> lock(mtx);

            // Second check (with locking) - to ensure instance is still null
            if(instance == nullptr){
                instance = new Singleton();
            }
        }
        return instance;
    }
    void setData(int value){
        data = value;
    }
    int getData(){
        return data;
    }
    void showMessage() {
        cout << "Singleton instance at address: " << this 
             << ", data: " << data << endl;
    }
    static void destroyInstance() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }
};

// Initialize static members
Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

// Function to test thread safety
void threadFunction(int threadId){
    cout<<"Thread " << threadId << " is trying to get Singleton instance." << endl;
    Singleton* s = Singleton::getInstance();
    s->showMessage();
    s->setData(threadId);
    cout<<"Thread " << threadId << " set data to " << s->getData() << endl;
}

int main(){
    thread t1(threadFunction, 1);
    thread t2(threadFunction, 2);
    thread t3(threadFunction, 3);
    thread t4(threadFunction, 4);
    thread t5(threadFunction, 5);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    Singleton::destroyInstance();
    
    return 0;
}