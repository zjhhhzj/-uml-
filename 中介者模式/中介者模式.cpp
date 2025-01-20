//通过一个中介对象来封装一组对象之间的交互。中介者使各对象不需要显式地相互引用，从而使其耦合松散，并可以独立地改变它们之间的交互

// Mediator（中介者接口）：定义了对象之间交互的接口。
// ConcreteMediator（具体中介者）：实现中介者接口，协调各对象之间的交互。
// Colleague（同事类）：定义与中介者交互的接口，每个同事类只知道中介者，而不知道其他同事类。

//举例，UI的界面组件交互

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 中介者接口
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void CreateClg()=0;
    virtual void Operater(Colleague* colleague) = 0;
};

// 具体中介者类
class ConcreteMediator : public Mediator {
public:
    virtual ~ConcreteMediator(){
        if(pA){delete pA,pA=nullptr;}
        if(pB){delete pB,pB=nullptr;}
    }
    void CreateClg() override{
        pA= new ConcreteColleagueA(this);
        pB= new ConcreteColleagueB(this);
    }
    void Operater(Colleague* Opt) override {
        if(Opt==pA){
            //操作pB
        }else if(Opt==pB){
            //操作pA
        }
    }
private:
    ConcreteColleagueA* pA=nullptr;
    ConcreteColleagueB* pB=nullptr;
};

// 同事类UI接口
class Colleague {
protected:
    Mediator* mediator; // 持有中介者的引用
public:
    Colleague(Mediator* m) : mediator(m) {}
    virtual ~Colleague() = default;
    virtual void Enable(bool sign) = 0;
};

// UI接口A
class ConcreteColleagueA : public Colleague {
public:
    ConcreteColleagueA(Mediator* m) : Colleague(m) {}
    void Enable(bool sign) override {}
};

// UI接口B
class ConcreteColleagueB : public Colleague {
public:
    ConcreteColleagueB(Mediator* m) : Colleague(m) {}
    void Enable(bool sign) override {}
};

class A{
public:
    A(int x,int y,int z){
        cout<<x+y+z;
    }
};
int main() {
    // 创建中介者
    Mediator *mediator=new ConcreteMediator;
    A* a=new A(1,2,3);

    return 0;
}
