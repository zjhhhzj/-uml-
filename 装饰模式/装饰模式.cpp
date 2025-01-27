// 允许动态地向对象添加新的行为，而不改变其原始代码或结构。它是通过将对象嵌套在装饰器对象中实现的，这些装饰器对象可以在保持接口一致的同时扩展对象的功能

// Component(抽象组件)：定义对象的接口，确保装饰器和被装饰对象具有一致的接口。
// ConcreteComponent(具体组件)：实现 Component 接口的具体类，表示要被装饰的对象。
// Decorator(抽象装饰器类)：持有一个 Component 类型的引用，并定义与 Component 一致的接口。(与Component既是继承关系也是组合关系，与具体组件同一水平)
// ConcreteDecorator(具体的装饰器类)：，扩展 Decorator，通过重写方法为对象添加额外行为。

// 举例，文本编辑器，有加粗，斜体的功能
//  抽象组件
#include <iostream>
#include <string>
using namespace std;

// 抽象组件
class Component
{
public:
    virtual ~Component() {}
    virtual string operation() = 0; // 定义接口
};

// 具体组件
class ConcreteComponent : public Component
{
public:
    string operation() override
    {
        return "Text";
    }
};

// 抽象装饰器
class Decorator : public Component
{
protected:
    Component *component; // 持有一个组件指针

public:
    Decorator(Component *comp) : component(comp) {}
    virtual ~Decorator() { delete component; }

    string operation() override
    {
        return component->operation(); // 调用被装饰对象的方法
    }
};

// 具体装饰器 A：添加加粗功能
class BoldDecorator : public Decorator
{
public:
    BoldDecorator(Component *comp) : Decorator(comp) {}

    string operation() override
    {
        return "<b>" + Decorator::operation() + "</b>"; // 添加加粗标签
    }
};

// 具体装饰器 B：添加斜体功能
class ItalicDecorator : public Decorator
{
public:
    ItalicDecorator(Component *comp) : Decorator(comp) {}

    string operation() override
    {
        return "<i>" + Decorator::operation() + "</i>"; // 添加斜体标签
    }
};

// 测试代码
int main()
{
    // 创建一个具体组件
    Component *text = new ConcreteComponent();

    // 添加加粗功能
    Component *boldText = new BoldDecorator(text);

    // 在加粗的基础上再添加斜体功能
    Component *boldItalicText = new ItalicDecorator(boldText);

    // 输出结果
    cout << "Original: " << text->operation() << endl;
    cout << "Bold: " << boldText->operation() << endl;
    cout << "Bold + Italic: " << boldItalicText->operation() << endl;

    // 清理内存
    delete boldItalicText; // 会递归删除所有装饰器和组件

    return 0;
}
