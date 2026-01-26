#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// The Prototype Design Pattern is a creational design pattern that allows you to create 
// new objects by copying existing objects (prototypes) instead of creating them from scratch.

class Shape{
    public:
    virtual Shape* clone() = 0; // Pure virtual function for cloning
    virtual void draw() = 0; // Pure virtual function for drawing
    virtual ~Shape() {} // Virtual destructor
};

class Circle:public Shape{
private:
    string color;
public:
    Circle(string c) : color(c) {}

    // Copy Constructor
    Circle(const Circle &other){
        color = other.color;
    }
    Shape* clone() override {
        return new Circle(*this);
    }
    void draw() override {
        cout << "Drawing a " << color << " circle." << endl;
    }
};

int main(){
    Shape* originalCircle = new Circle("red");
    originalCircle->draw();

    Shape* clonedCircle = originalCircle->clone();
    clonedCircle->draw();

    delete originalCircle;
    delete clonedCircle;
}