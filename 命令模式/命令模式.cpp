//将请求(命令)封装成一个对象，从而可以用不同的请求、队列或者日志来参数化对象，同时支持可撤销的操作（将请求的调用者和接收者解耦。）

// Command（命令接口）：定义一个执行操作的接口。
// ConcreteCommand（具体命令类）：实现命令接口，绑定一个接收者对象，调用接收者的相关操作。
// Receiver（接收者）：执行实际操作的类。
// Invoker（调用者）：持有命令对象并调用命令。

//举例，技能燃烧在不同角色中采取相同算法（函数）而具体行为不一致
#include <iostream>
#include <memory>
using namespace std;

// 接收者类：灯
class Light {
public:
    void turnOn() { cout << "The light is ON." << endl; }
    void turnOff() { cout << "The light is OFF." << endl; }
};

// 命令接口
class Command {
public:
    virtual void execute() = 0; // 执行命令
    virtual ~Command() {}
};

// 具体命令类：打开灯
class LightOnCommand : public Command {
private:
    Light* light; // 持有接收者的引用
public:
    LightOnCommand(Light* l) : light(l) {}
    void execute() override {
        light->turnOn();
    }
};

// 具体命令类：关闭灯
class LightOffCommand : public Command {
private:
    Light* light; // 持有接收者的引用
public:
    LightOffCommand(Light* l) : light(l) {}
    void execute() override {
        light->turnOff();
    }
};

// 调用者类：遥控器
class RemoteControl {
private:
    Command* command; // 当前命令
public:
    void setCommand(Command* cmd) {
        command = cmd;
    }
    void pressButton() {
        if (command) {
            command->execute();
        }
    }
};

// 客户端代码
int main() {
    // 创建接收者
    Light light;

    // 创建具体命令
    LightOnCommand lightOn(&light);
    LightOffCommand lightOff(&light);

    // 创建调用者
    RemoteControl remote;

    // 设置命令并执行
    remote.setCommand(&lightOn);
    remote.pressButton(); // 输出：The light is ON.

    remote.setCommand(&lightOff);
    remote.pressButton(); // 输出：The light is OFF.

    return 0;
}
