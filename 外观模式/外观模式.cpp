// 为子系统中的一组接口提供一个统一的高层接口，使得子系统更容易使用。它通过定义一个“外观类”（Facade），隐藏子系统的复杂性，简化客户端对子系统的访问

// Facade（外观类）：提供一个高层接口，客户端通过它访问子系统的功能。
// Subsystem Classes（子系统类）：实现子系统的具体功能。子系统可以有多个类，外观类负责调用它们。
// Client（客户端）：通过外观类与子系统交互，而不直接访问子系统类。

// 举例: 有多个子系统（如音响、投影仪、灯光等），通过外观类统一控制

#include <iostream>
using namespace std;

// 子系统类 1：音响
class SoundSystem
{
public:
    void turnOn() { cout << "Sound system is ON." << endl; }
    void turnOff() { cout << "Sound system is OFF." << endl; }
};

// 子系统类 2：投影仪
class Projector
{
public:
    void turnOn() { cout << "Projector is ON." << endl; }
    void turnOff() { cout << "Projector is OFF." << endl; }
};

// 子系统类 3：灯光
class Lighting
{
public:
    void dim() { cout << "Lighting is dimmed." << endl; }
    void brighten() { cout << "Lighting is brightened." << endl; }
};

// 外观类：家庭影院控制器
class HomeTheaterFacade
{
private:
    SoundSystem soundSystem;
    Projector projector;
    Lighting lighting;

public:
    void startMovie()
    {
        cout << "Starting movie..." << endl;
        soundSystem.turnOn();
        projector.turnOn();
        lighting.dim();
    }

    void endMovie()
    {
        cout << "Ending movie..." << endl;
        lighting.brighten();
        projector.turnOff();
        soundSystem.turnOff();
    }
};

// 客户端代码
int main()
{
    HomeTheaterFacade homeTheater;
    homeTheater.startMovie(); // 一键启动家庭影院
    homeTheater.endMovie();   // 一键关闭家庭影院
    return 0;
}
