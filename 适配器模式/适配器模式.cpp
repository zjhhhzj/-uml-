// 将一个类的接口转换成客户端期望的另一个接口，使得原本接口不兼容的类可以一起工作

// Target（目标接口）：定义客户端需要的接口。
// Adaptee（被适配者）：已有的接口，与客户端不兼容。
// Adapter（适配器）：将被适配者的接口转换为目标接口。

// 举例，两脚插头适配三脚插座

#include <iostream>
using namespace std;

// 目标接口：三脚插座
class ThreePinSocket
{
public:
    virtual ~ThreePinSocket() = default;
    virtual void connect() = 0; // 客户端需要的接口
};

// 被适配者：两脚插头
class TwoPinPlug
{
public:
    void specificConnect()
    {
        cout << "Two-pin plug connected." << endl;
    }
};

// 适配器：将两脚插头适配为三脚插座
class PlugAdapter : public ThreePinSocket
{
private:
    TwoPinPlug *twoPinPlug; // 组合被适配者
public:
    PlugAdapter(TwoPinPlug *plug) : twoPinPlug(plug) {}

    void connect() override
    {
        // 调用被适配者的方法
        twoPinPlug->specificConnect();
    }
};

int main()
{
    // 创建两脚插头
    TwoPinPlug twoPinPlug;

    // 使用适配器将两脚插头适配为三脚插座
    ThreePinSocket *adapter = new PlugAdapter(&twoPinPlug);

    // 客户端通过三脚插座使用两脚插头
    adapter->connect();

    delete adapter;
    return 0;
}
