#include<iostream>
#include <bits/stdc++.h>
using namespace std;

// Abstract Product
class Shape{
public:
    virtual void draw() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape{
public:
    void draw() override {
        cout << "Drawing Circle" << endl;
    }
};

class Square : public Shape{
public:
    void draw() override {
        cout << "Drawing Square" << endl;
    }
};

class shapeFactory{
public:
    static Shape* getShape(const string& shapeType){
        if(shapeType == "CIRCLE"){
            return new Circle();
        }
        else if(shapeType == "SQUARE"){
            return new Square();
        }
        return nullptr;
    }
};

enum class ShapeType{
    CIRCLE,
    SQUARE
};

class ShapeFactoryEnum{
public:
    static Shape* getShape(ShapeType shapeType){
        switch(shapeType){
            case ShapeType::CIRCLE:
                return new Circle();
            case ShapeType::SQUARE:
                return new Square();
            default:
                return nullptr;
        }
    }
};

int main(){
    Shape* shape1 = ShapeFactoryEnum::getShape(ShapeType::CIRCLE);
    shape1->draw();
    Shape* shape2 = ShapeFactoryEnum::getShape(ShapeType::SQUARE);
    shape2->draw();
    delete shape1;
    delete shape2;
    
    return 0;
}