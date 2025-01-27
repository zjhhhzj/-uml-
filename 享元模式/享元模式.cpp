// 通过共享尽可能多的对象来减少内存消耗。适用于有大量相似对象的场景，通过将可共享的部分抽取出来，避免重复创建相同的数据

// 内部状态类（Intrinsic State）:对象的共享部分，不随环境变化而变化。内部状态存储在享元对象内部，可以被多个对象共享。
// 外部状态类（Extrinsic State）对象的非共享部分，随环境变化而变化。外部状态由客户端维护，并在使用时传递给享元对象。
// 享元工厂（Flyweight Factory）管理和维护享元对象的创建和共享。确保相同的享元对象可以被重复使用。

// 举例，围棋棋盘上有黑子和白子

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
using namespace std;

// 抽象享元类
class Flyweight
{
public:
    virtual ~Flyweight() = default;
    virtual void operation(int x, int y) = 0; // 接收外部状态
};

// 具体享元类：围棋棋子
class ConcreteFlyweight : public Flyweight
{
private:
    string color; // 内部状态：棋子颜色
public:
    ConcreteFlyweight(const string &color) : color(color) {}
    void operation(int x, int y) override
    {
        cout << "Chess piece [" << color << "] placed at (" << x << ", " << y << ")." << endl;
    }
};

// 享元工厂类
class FlyweightFactory
{
private:
    unordered_map<string, shared_ptr<Flyweight>> flyweights; // 享元池
public:
    shared_ptr<Flyweight> getFlyweight(const string &color)
    {
        // 如果享元池中不存在该颜色的棋子，则创建新的享元对象
        if (flyweights.find(color) == flyweights.end())
        {
            flyweights[color] = make_shared<ConcreteFlyweight>(color);
            cout << "Creating new chess piece of color [" << color << "]." << endl;
        }
        return flyweights[color];
    }
};

int main()
{
    FlyweightFactory factory;

    // 获取黑色棋子
    auto black1 = factory.getFlyweight("Black");
    black1->operation(1, 1);

    // 获取白色棋子
    auto white1 = factory.getFlyweight("White");
    white1->operation(2, 2);

    // 再次获取黑色棋子（共享已有对象）
    auto black2 = factory.getFlyweight("Black");
    black2->operation(3, 3);

    return 0;
}
