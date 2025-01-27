// 允许对象在其内部状态发生改变时改变其行为,将与状态相关的行为抽象到独立的状态类中，并通过状态对象的切换来改变对象的行为。

// Context（上下文）：维护当前状态的实例，并负责状态切换。
// State（抽象状态）：定义状态的公共接口。
// ConcreteState（具体状态）：实现具体状态的行为

// 举例，一个电灯有两种状态。每次按下开关时，电灯的状态会切换

#include <iostream>
#include <memory>
using namespace std;

// 上下文类
class Context
{
private:
    shared_ptr<State> state; // 当前状态
public:
    Context(shared_ptr<State> initialState) : state(initialState) {}

    void setState(shared_ptr<State> newState)
    {
        state = newState;
    }

    void Request()
    {
        state->Handle(this);
    }
};

// 抽象状态类
class State
{
public:
    virtual ~State() = default;
    virtual void Handle(class Context *context) = 0;
};

// 具体状态：开
class OnState : public State
{
public:
    void Handle(Context *context) override
    {
        cout << "Turning light off." << endl;
        context->setState(make_shared<OffState>());
    }
};

// 具体状态：关
class OffState : public State
{
public:
    void Handle(Context *context) override
    {
        cout << "Turning light on." << endl;
        context->setState(make_shared<OnState>());
    }
};

// 客户端代码
int main()
{
    auto initialState = make_shared<OffState>();
    Context light(initialState);

    // 模拟按下开关
    light.Request(); // Turning light on.
    light.Request(); // Turning light off.
    light.Request(); // Turning light on.

    return 0;
}
