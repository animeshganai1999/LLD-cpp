#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Product - Complex Object being built
class Computer{
private:
    string CPU;
    string GPU;
    string RAM;
    string Storage;
    bool hasWifi;
    bool hasBluetooth;
public:
    Computer() : hasWifi(false), hasBluetooth(false) {}

    // Setters
    void setCpu(const string& cpu) { CPU = cpu; }
    void setGpu(const string& gpu) { GPU = gpu; }
    void setRam(const string& ram) { RAM = ram; }
    void setStorage(const string& storage) { Storage = storage; }
    void setWifi(bool wifi) { hasWifi = wifi; }
    void setBluetooth(bool bluetooth) { hasBluetooth = bluetooth; }

    // Display configuration
    void showConfig(){
        cout << "Computer Configuration:" << endl;
        cout << "CPU: " << CPU << endl;
        cout << "GPU: " << GPU << endl;
        cout << "RAM: " << RAM << endl;
        cout << "Storage: " << Storage << endl;
        cout << "WiFi: " << (hasWifi ? "Yes" : "No") << endl;
        cout << "Bluetooth: " << (hasBluetooth ? "Yes" : "No") << endl;
    }
};

// Builder Interface
class ComputerBuilder{
protected:
    Computer* computer;
public:
    ComputerBuilder(){
        computer = new Computer();
    }
    virtual ~ComputerBuilder() {}

    // Build Setup
    virtual ComputerBuilder* buildCPU() = 0;
    virtual ComputerBuilder* buildGPU() = 0;
    virtual ComputerBuilder* buildRAM() = 0;
    virtual ComputerBuilder* buildStorage() = 0;
    virtual ComputerBuilder* buildWifi() = 0;
    virtual ComputerBuilder* buildBluetooth() = 0;

    // Get the final product
    Computer* getComputer(){
        return computer;
    }
};

// Concrete Builder - Gaming Computer
class GamingComputerBuilder : public ComputerBuilder{
public:
    ComputerBuilder* buildCPU() override {
        computer->setCpu("Intel i9");
        return this;
    }
    ComputerBuilder* buildGPU() override {
        computer->setGpu("NVIDIA RTX 3080");
        return this;
    }
    ComputerBuilder* buildRAM() override {
        computer->setRam("32GB");
        return this;
    }
    ComputerBuilder* buildStorage() override {
        computer->setStorage("1TB SSD");
        return this;
    }
    ComputerBuilder* buildWifi() override {
        computer->setWifi(true);
        return this;
    }
    ComputerBuilder* buildBluetooth() override {
        computer->setBluetooth(true);
        return this;
    }
};

// Concrete Builder - Office Computer
class OfficeComputerBuilder : public ComputerBuilder{
public:
    ComputerBuilder* buildCPU() override {
        computer->setCpu("Intel i5");
        return this;
    }
    ComputerBuilder* buildGPU() override {
        computer->setGpu("Integrated Graphics");
        return this;
    }
    ComputerBuilder* buildRAM() override {
        computer->setRam("16GB");
        return this;
    }
    ComputerBuilder* buildStorage() override {
        computer->setStorage("512GB SSD");
        return this;
    }
    ComputerBuilder* buildWifi() override {
        computer->setWifi(true);
        return this;
    }
    ComputerBuilder* buildBluetooth() override {
        computer->setBluetooth(false);
        return this;
    }
};

// Director (Optional) - Constructs objects using builder interface
class ComputerDirector {
private:
    ComputerBuilder* builder;
public:
    ComputerDirector(ComputerBuilder* b) : builder(b) {}

    void constructComputer() {
        builder->buildCPU();
        builder->buildGPU();
        builder->buildRAM();
        builder->buildStorage();
        builder->buildWifi();
        builder->buildBluetooth();
    }

    Computer* getComputer() {
        return builder->getComputer();
    }
};

int main(){
    // Direct building without Director
    ComputerBuilder* gamingBuilder = new GamingComputerBuilder();
    Computer* gamingPC = gamingBuilder->buildCPU()
                        ->buildGPU()
                        ->buildRAM()
                        ->buildStorage()
                        ->buildWifi()
                        ->buildBluetooth()
                        ->getComputer();
    gamingPC->showConfig();
    delete gamingBuilder;
    delete gamingPC;

    // Building using Director
    ComputerBuilder* officeBuilder = new OfficeComputerBuilder();
    ComputerDirector director(officeBuilder);
    director.constructComputer();
    Computer* officePC = director.getComputer();
    officePC->showConfig();

    delete officeBuilder;
    delete officePC;

    return 0;
}