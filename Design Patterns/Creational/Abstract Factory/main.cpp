#include<iostream>
#include <bits/stdc++.h>
using namespace std;

// Abstract Product
class Button{
    public:
    virtual void info() = 0; // Pure virtual function
    virtual ~Button() {} // Virtual destructor
};

// Abstract Product
class Checkbox{
    public:
    virtual void info() = 0; // Pure virtual function
    virtual ~Checkbox() {} // Virtual destructor
};

// Concrete Product - Windows Button
class WindowsButton : public Button{
    public:
    void info() override {
        cout << "Windows Button" << endl;
    }
};

// Concrete Product - MacOS Button
class MacOSButton : public Button{
    public:
    void info() override {
        cout << "MacOS Button" << endl;
    }
};

// Concrete Product - Windows Checkbox
class WindowsCheckbox : public Checkbox{
    public:
    void info() override {
        cout << "Windows Checkbox" << endl;
    }
};

// Concrete Product - MacOS Checkbox
class MacOSCheckbox : public Checkbox{
    public:
    void info() override {
        cout << "MacOS Checkbox" << endl;
    }
};

// Abstract Factory Interface
class GUIFactory{
public:
    virtual Button* createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;
    virtual ~GUIFactory() {}
};

// Concrete Factory - Windows
class WindowsFactory : public GUIFactory{
public:
    Button* createButton() override {
        return new WindowsButton();
    }
    Checkbox* createCheckbox() override {
        return new WindowsCheckbox();
    }
};

// Concrete Factory - MacOS
class MacOSFactory : public GUIFactory{
public:
    Button* createButton() override {
        return new MacOSButton();
    }
    Checkbox* createCheckbox() override {
        return new MacOSCheckbox();
    }
};

// Client Code
class Application{
private:
    GUIFactory* factory;
    Button* button;
    Checkbox* checkbox;
public:
    Application(GUIFactory* f) : factory(f){
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }

    void renderUI(){
        button->info();
        checkbox->info();
    }

    ~Application(){
        delete button;
        delete checkbox;
        delete factory;
    }
};

// Factory provider - Determines which factory to use
GUIFactory* getFactory(const string& osType){
    if(osType == "WINDOWS"){
        return new WindowsFactory();
    }
    else if(osType == "MACOS"){
        return new MacOSFactory();
    }
    return nullptr;
}

int main(){
    // Windows Application
    GUIFactory* windowsFactory = getFactory("WINDOWS");
    Application* windowsApp = new Application(windowsFactory);
    windowsApp->renderUI();
    delete windowsApp;

    // MacOS Application
    GUIFactory* macFactory = getFactory("MACOS");
    Application* macApp = new Application(macFactory);
    macApp->renderUI();
    delete macApp;
    
    return 0;
}