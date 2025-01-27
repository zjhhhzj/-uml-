// 通过一个中介对象来封装一组对象之间的交互。中介者使各对象不需要显式地相互引用，从而使其耦合松散，并可以独立地改变它们之间的交互

// Mediator（中介者接口）：定义了对象之间交互的接口。
// ConcreteMediator（具体中介者）：实现中介者接口，协调各对象之间的交互。
// Colleague（同事类）：定义与中介者交互的接口，每个同事类只知道中介者，而不知道其他同事类。

// 举例，UI的界面组件交互

#include <iostream>
#include <string>
using namespace std;

// 前向声明
class Colleague;
class ConcreteColleagueA;
class ConcreteColleagueB;

// 中介者接口
class Mediator
{
public:
    virtual ~Mediator() = default;
    virtual void Operater(Colleague *colleague) = 0; // 同事类通知中介者
};

// 同事类接口
class Colleague
{
protected:
    Mediator *mediator; // 持有中介者的引用
public:
    Colleague(Mediator *m) : mediator(m) {}
    virtual ~Colleague() = default;
    virtual void Enable(bool sign) = 0; // 启用或禁用
};

// 具体中介者类
class ConcreteMediator : public Mediator
{
private:
    ConcreteColleagueA *pA = nullptr;
    ConcreteColleagueB *pB = nullptr;

public:
    ~ConcreteMediator()
    {
        if (pA)
        {
            delete pA, pA = nullptr;
        }
        if (pB)
        {
            delete pB, pB = nullptr;
        }
    }

    void SetColleagueA(ConcreteColleagueA *colleagueA) { pA = colleagueA; }
    void SetColleagueB(ConcreteColleagueB *colleagueB) { pB = colleagueB; }

    void Operater(Colleague *Opt) override
    {
        if (dynamic_cast<ConcreteColleagueA *>(Opt))
        {
            // 如果操作的是 ColleagueA，则修改 ColleagueB 的状态
            pB->Enable(false); // 禁用 ColleagueB
        }
        else if (dynamic_cast<ConcreteColleagueB *>(Opt))
        {
            // 如果操作的是 ColleagueB，则修改 ColleagueA 的状态
            cout << "Mediator: ColleagueB changed, updating ColleagueA..." << endl;
            pA->Enable(false); // 禁用 ColleagueA
        }
    }
};

// 具体同事类A
class ConcreteColleagueA : public Colleague
{
public:
    ConcreteColleagueA(Mediator *m) : Colleague(m) {}

    void Enable(bool sign) override
    {
        if (sign)
        {
            cout << "ConcreteColleagueA is enabled." << endl;
        }
        else
        {
            cout << "ConcreteColleagueA is disabled." << endl;
        }
    }

    void NotifyMediator()
    {
        cout << "ConcreteColleagueA notifies Mediator." << endl;
        mediator->Operater(this);
    }
};

// 具体同事类B
class ConcreteColleagueB : public Colleague
{
public:
    ConcreteColleagueB(Mediator *m) : Colleague(m) {}

    void Enable(bool sign) override
    {
        if (sign)
        {
            cout << "ConcreteColleagueB is enabled." << endl;
        }
        else
        {
            cout << "ConcreteColleagueB is disabled." << endl;
        }
    }

    void NotifyMediator()
    {
        cout << "ConcreteColleagueB notifies Mediator." << endl;
        mediator->Operater(this);
    }
};

// 测试代码
int main()
{
    // 创建中介者
    ConcreteMediator *mediator = new ConcreteMediator;

    // 创建同事类并通过中介者进行关联
    ConcreteColleagueA *colleagueA = new ConcreteColleagueA(mediator);
    ConcreteColleagueB *colleagueB = new ConcreteColleagueB(mediator);

    mediator->SetColleagueA(colleagueA);
    mediator->SetColleagueB(colleagueB);

    // 测试交互
    cout << "=== ColleagueA triggers ===" << endl;
    colleagueA->NotifyMediator(); // ColleagueA 通知中介者

    cout << "\n=== ColleagueB triggers ===" << endl;
    colleagueB->NotifyMediator(); // ColleagueB 通知中介者

    // 清理内存
    delete colleagueA;
    delete colleagueB;
    delete mediator;

    return 0;
}