// 将对象组织成树形结构以表示“部分-整体”的层次结构。组合模式使得客户端对单个对象和组合对象的使用具有一致性

// Component（抽象组件）：定义了组合对象和单个对象的公共接口。
// Leaf（叶子节点）：表示树的叶子节点。
// Composite（组合节点）：表示树的非叶子节点，可以包含子节点（既可以是叶子节点，也可以是其他组合节点）。

// 举例，文件系统

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
using namespace std;

// 抽象组件
class FileSystemComponent
{
protected:
    string name;

public:
    FileSystemComponent(const string &name) : name(name) {}
    virtual ~FileSystemComponent() = default;

    // 纯虚函数，定义接口
    virtual void display(int level=0) = 0;
    virtual void add(shared_ptr<FileSystemComponent>) = 0;
    virtual void del(shared_ptr<FileSystemComponent>) = 0;
};

// 叶子节点
class File : public FileSystemComponent
{
public:
    File(const string &name) :FileSystemComponent(name) {}
    void display(int level = 0) override
    {
        for (int i = 1; i <= level; i++)
            cout << "    ";
        cout << '-' << name << '\n';
    }
    void add(shared_ptr<FileSystemComponent>) override{
        throw logic_error("Its File");
    }
    void del(shared_ptr<FileSystemComponent>) override{
        throw logic_error("Its File");
    }
};

// 组合节点
class Folder : public FileSystemComponent
{
private:
    vector<shared_ptr<FileSystemComponent>> children;

public:
    Folder(const string &name) : FileSystemComponent(name) {}

    void add(shared_ptr<FileSystemComponent> component) override
    {
        children.push_back(component);
    }

    void del(shared_ptr<FileSystemComponent> component) override
    {
        children.erase(remove(children.begin(), children.end(), component), children.end());
    }

    void display(int level = 0) override
    {
        for (int i = 1; i <= level; i++)
            cout << "    ";
        cout<<'+'<<name<<'\n';
        for (auto& iter : children)
        {
            iter->display(level + 1);
        }
    }
};

// 客户端代码
int main()
{
    FileSystemComponent* f1=new Folder("f1");
    FileSystemComponent* f2=new Folder("f2");
    FileSystemComponent* f3=new Folder("f3");

    FileSystemComponent* f21=new File("f21");
    FileSystemComponent* f22=new File("f22");
    FileSystemComponent* f31=new File("f31");

    f1->add(shared_ptr<FileSystemComponent>(f2));
    f1->add(shared_ptr<FileSystemComponent>(f3));
    f2->add(shared_ptr<FileSystemComponent>(f21));
    f2->add(shared_ptr<FileSystemComponent>(f22));
    f3->add(shared_ptr<FileSystemComponent>(f31));

    // 显示整个文件系统结构
    f1->display();

    delete f1;
    delete f2;
    delete f3;
    delete f21;
    delete f22;
    delete f31;
    return 0;
}
