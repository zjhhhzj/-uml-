// 通过为多个对象提供处理请求的机会，将请求的发送者和接收者解耦。多个处理对象形成一条链，请求沿着链传递，直到有对象处理它为止

// Handler（抽象处理者）：定义处理请求的接口，并包含一个指向下一个处理者的引用。
// ConcreteHandler（具体处理者）：实现处理请求的逻辑，如果无法处理请求，则将其传递给下一个处理者。
// Client（客户端）：向链中的处理者提交请求。

// 举例，审批流程(非单纯：一人处理后终止)

#include <iostream>
#include <memory>
#include <string>
using namespace std;

// 抽象处理者
class Handler
{
protected:
    Handler *next; // 下一个处理者
public:
    virtual ~Handler() = default;

    void setNext(Handler *nextHandler)
    {
        next = nextHandler;
    }

    virtual void handleRequest(const string &request)
    {
        if (next)
        {
            next->handleRequest(request); // 传递给下一个处理者
        }
        else
        {
            cout << "No handler could process the request: " << request << endl;
        }
    }
};

// 具体处理者A
class ConcreteHandlerA : public Handler
{
public:
    void handleRequest(const string &request) override
    {
        if (request == "A")
        {
            cout << "ConcreteHandlerA handled the request: " << request << endl;
        }
        else if (next)
        {
            next->handleRequest(request); // 传递给下一个处理者
        }
    }
};

// 具体处理者B
class ConcreteHandlerB : public Handler
{
public:
    void handleRequest(const string &request) override
    {
        if (request == "B")
        {
            cout << "ConcreteHandlerB handled the request: " << request << endl;
        }
        else if (next)
        {
            next->handleRequest(request); // 传递给下一个处理者
        }
    }
};
// 具体处理者C
class ConcreteHandlerC : public Handler
{
public:
    void handleRequest(const string &request) override
    {
        if (request == "C")
        {
            cout << "ConcreteHandlerC handled the request: " << request << endl;
        }
        else if (next)
        {
            next->handleRequest(request); // 传递给下一个处理者
        }
    }
};

int main()
{
    // 创建处理者
    Handler *handlerA = new ConcreteHandlerA;
    Handler *handlerB = new ConcreteHandlerB;
    Handler *handlerC = new ConcreteHandlerC;

    // 设置处理链
    handlerA->setNext(handlerB);
    handlerB->setNext(handlerC);

    // 客户端请求
    handlerA->handleRequest("C");

    return 0;
}
