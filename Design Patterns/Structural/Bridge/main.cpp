#include<iostream>
#include<string>
using namespace std;

// Implementation Interface
class Device{
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void setVolume(int volume) = 0;
    virtual ~Device() {}
};

// Concrete Implementation 1
class TV : public Device {
public:
    void turnOn() override {
        cout << "TV is turned ON" << endl;
    }
    void turnOff() override {
        cout << "TV is turned OFF" << endl;
    }
    void setVolume(int volume) override {
        cout << "TV volume set to " << volume << endl;
    }
};

// Concrete Implementation 2
class Radio : public Device {
public:
    void turnOn() override {
        cout << "Radio is turned ON" << endl;
    }
    void turnOff() override {
        cout << "Radio is turned OFF" << endl;
    }
    void setVolume(int volume) override {
        cout << "Radio volume set to " << volume << endl;
    }
};

// Abstraction
class RemoteControl {
protected:
    Device* device;
public:
    RemoteControl(Device* dev) : device(dev) {}
    virtual void turnOn() {
        device->turnOn();
    }
    virtual void turnOff() {
        device->turnOff();
    }
    virtual void setVolume(int volume) {
        device->setVolume(volume);
    }
    virtual ~RemoteControl() {}
};

// Refined Abstraction
class AdvancedRemoteControl : public RemoteControl {
public:
    AdvancedRemoteControl(Device* dev) : RemoteControl(dev) {}

    void mute() {
        device->setVolume(0);
        cout << "Device muted" << endl;
    }
};

int main() {
    Device* tv = new TV();
    RemoteControl* basicRemote = new RemoteControl(tv);
    basicRemote->turnOn();
    basicRemote->setVolume(10);
    basicRemote->turnOff();

    Device* radio = new Radio();
    AdvancedRemoteControl* advancedRemote = new AdvancedRemoteControl(radio);
    advancedRemote->turnOn();
    advancedRemote->setVolume(20);
    advancedRemote->mute();
    advancedRemote->turnOff();

    delete basicRemote;
    delete tv;
    delete advancedRemote;
    delete radio;

    return 0;
}