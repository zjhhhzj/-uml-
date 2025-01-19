//定义了对象间的一对多依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都会收到通知并自动更新

//核心思想是发布-订阅机制
//发布者（Subject）：负责维护观察者列表，并当状态变化时通知所有观察者。
//观察者（Observer）：订阅发布者的状态变化，并在收到通知后执行相应的操作。
//ConcreteSubject（具体发布者）：
//ConcreteObserver（具体观察者）：

//举例，一个观察者发布一条信息，同组的观察者都会订阅到
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

//抽象观察者接口
class Observer {
public:
    Observer(const char* name,int group ,Subject* subject): name(name), group(group),subject(subject) {}
    virtual ~Observer() {if(subject)delete subject;}

    virtual void publisher(Subject* tmpSbj,const char* pStr) = 0;  // 发布信息的接口
    virtual void Notifier(const char* pStr) = 0; // 接收信息的接口

    int GetGroup(){return group;}
    const char* GetName(){return name;}
private:
    const char* name;                   // 观察者的名字
    int group;                     // 观察者的组号
    Subject* subject;              // 关联的发布者
};

//具体观察者
class ConcreteObserver : public Observer {

public:
    ConcreteObserver(const char* name,int group ,Subject* subject): Observer(name,group,subject){};

    void publisher(Subject* tmpSbj,const char* pStr) override{
        tmpSbj->notify(this,pStr);
    }
    void Notifier(const char* pStr) override{
        cout<<*this->GetName()<<"收到了"<<*pStr<<'\n';
    }

};


// 抽象发布者接口
class Subject {
public:
    virtual ~Subject() {}
    virtual void attach(Observer* o) = 0; // 添加观察者
    virtual void detach(Observer* o) = 0; // 移除观察者
    virtual void notify(Observer*,const char*) = 0;            // 通知所有观察者
};

//具体发布者
class ConcreteSubject : public Subject {
private:
    map<int,vector<Observer*>> observers;    // 保存观察者列表
    const char* state;                           // 发布者的状态

public:
    void attach(Observer* tmpObsvr) override {
        observers[tmpObsvr->GetGroup()].push_back(tmpObsvr);
    }
    void detach(Observer* tmpObsvr) override {
        auto it=remove_if (observers[tmpObsvr->GetGroup()].begin(), observers[tmpObsvr->GetGroup()].end(), [tmpObsvr](Observer* o){return o->GetGroup()==tmpObsvr->GetGroup()?true:false;});
        observers[tmpObsvr->GetGroup()].erase(it, observers[tmpObsvr->GetGroup()].end());
    }

    void notify(Observer* tmpObsvr,const char* pStr) override {
        for (Observer* o : observers[tmpObsvr->GetGroup()]) {
            o->Notifier(pStr); // 通知每个观察者
        }
    }
};

int main() {
    // 创建发布者
    Subject *pSbj=new ConcreteSubject;
    // 创建具体观察者并订阅
    Observer *observer1=new ConcreteObserver("Observer1",1,pSbj);
    Observer *observer2=new ConcreteObserver("Observer2",1,pSbj);

    pSbj->attach(observer1);
    pSbj->attach(observer2);

    // 观察者发布信息
    observer1->publisher(pSbj,"this obj1");

    // 移除一个观察者
    pSbj->detach(observer1);
    return 0;
}
