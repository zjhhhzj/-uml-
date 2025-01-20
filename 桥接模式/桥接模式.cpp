//通过将抽象部分与实现部分分离，使它们可以独立变化。核心思想是将类的抽象和实现解耦，使得可以独立扩展，而不是通过继承绑定在一起
//体现在多个独立变化维度的业务需求

// Abstraction（抽象类）：定义高层抽象接口，维护一个对实现部分的引用。
// RefinedAbstraction（扩展抽象类）：扩展抽象类的接口。
// Implementor（实现接口）：定义实现部分的接口。
// ConcreteImplementor（具体实现类）：实现 Implementor 接口。

//举例，需要绘制形状（如圆形和正方形），同时形状可以有不同的颜色（如红色和蓝色）。通过桥接模式，我们将形状的抽象与颜色的实现分离

#include <iostream>
#include <string>
using namespace std;

// 实现接口：颜色
class Color {
public:
    virtual ~Color() = default;
    virtual string fill() const = 0; // 返回颜色的描述
};

// 具体实现类：红色
class Red : public Color {
public:
    string fill() const override {
        return "Red";
    }
};

// 具体实现类：蓝色
class Blue : public Color {
public:
    string fill() const override {
        return "Blue";
    }
};

// 抽象类：形状
class Shape {
protected:
    Color* color; // 颜色的实现部分
public:
    Shape(Color* c) : color(c) {}
    virtual ~Shape() = default;
    virtual void draw() const = 0; // 绘制形状
};

// 扩展抽象类：圆形
class Circle : public Shape {
public:
    Circle(Color* c) : Shape(c) {}
    void draw() const override {
        cout << "Drawing a Circle in " << color->fill() << " color." << endl;
    }
};

// 扩展抽象类：正方形
class Square : public Shape {
public:
    Square(Color* c) : Shape(c) {}
    void draw() const override {
        cout << "Drawing a Square in " << color->fill() << " color." << endl;
    }
};

int main() {
    // 创建颜色
    Color* red = new Red();
    Color* blue = new Blue();

    // 创建形状并为其赋予颜色
    Shape* redCircle = new Circle(red);
    Shape* blueSquare = new Square(blue);

    // 绘制形状
    redCircle->draw();
    blueSquare->draw();

    // 释放内存
    delete redCircle;
    delete blueSquare;
    delete red;
    delete blue;

    return 0;
}
