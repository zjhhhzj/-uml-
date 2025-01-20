//用于在不破坏封装的前提下，捕获对象的内部状态，并在以后需要时恢复到该状态。主要用于保存和恢复对象的状态

// Originator（发起人）：负责创建备忘录，记录当前状态，并可以使用备忘录恢复状态。
// Memento（备忘录）：存储发起人的内部状态，并防止其他对象访问。
// Caretaker（管理者）：负责保存和管理备忘录，但不能修改备忘录的内容。

//举例，游戏存档

#include <iostream>
#include <string>
#include <memory>
using namespace std;

// 备忘录类
class Memento {
private:
    string state; // 保存的状态
public:
    Memento(const string& s) : state(s) {}
    string getState() const { return state; }
};

// 发起人类
class Originator {
private:
    string state; // 当前状态
public:
    void setState(const string& s) {
        state = s;
        cout << "State set to: " << state << endl;
    }

    string getState() const { return state; }

    // 创建备忘录
    shared_ptr<Memento> createMemento() {
        return make_shared<Memento>(state);
    }

    // 从备忘录恢复状态
    void restoreMemento(shared_ptr<Memento> memento) {
        state = memento->getState();
        cout << "State restored to: " << state << endl;
    }
};

// 管理者类
class Caretaker {
private:
    shared_ptr<Memento> memento; // 保存的备忘录
public:
    void saveMemento(shared_ptr<Memento> m) {
        memento = m;
    }

    shared_ptr<Memento> getMemento() const {
        return memento;
    }
};

int main() {
    Originator originator;
    Caretaker caretaker;

    // 设置初始状态
    originator.setState("Level 1");

    // 保存状态
    caretaker.saveMemento(originator.createMemento());

    // 修改状态
    originator.setState("Level 2");

    // 恢复状态
    originator.restoreMemento(caretaker.getMemento());

    return 0;
}
