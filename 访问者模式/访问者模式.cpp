//允许在不修改对象结构的前提下，定义作用于对象结构中的新操作。通过将操作逻辑从对象结构中分离出来，访问者模式使得添加新操作变得更加容易(对象结构尽可能不改变)

// Visitor（访问者接口）：定义了对每种元素的访问操作。
// ConcreteVisitor（具体访问者）：实现访问者接口，定义具体的操作逻辑。
// Element（元素接口）：定义了一个接受访问者的方法（accept），该方法通常会将访问者对象传递给元素。
// ConcreteElement（具体元素）：实现元素接口，定义具体的接受访问者逻辑。
// ObjectStructure（对象结构）：包含一组元素，可以迭代这些元素并让访问者访问它们。

//举例，文件系统操作

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// 访问者接口
class Visitor {
public:
    virtual void visitFile(const string& fileName) = 0;
    virtual void visitFolder(const string& folderName) = 0;
    virtual ~Visitor() = default;
};

// 元素接口
class Element {
public:
    virtual void accept(shared_ptr<Visitor> visitor) = 0;
    virtual ~Element() = default;
};

// 具体元素：文件
class File : public Element {
private:
    string fileName;
public:
    File(const string& name) : fileName(name) {}
    void accept(shared_ptr<Visitor> visitor) override {
        visitor->visitFile(fileName);
    }
};

// 具体元素：文件夹
class Folder : public Element {
private:
    string folderName;
public:
    Folder(const string& name) : folderName(name) {}
    void accept(shared_ptr<Visitor> visitor) override {
        visitor->visitFolder(folderName);
    }
};

// 具体访问者：打印操作
class PrintVisitor : public Visitor {
public:
    void visitFile(const string& fileName) override {
        cout << "File: " << fileName << endl;
    }
    void visitFolder(const string& folderName) override {
        cout << "Folder: " << folderName << endl;
    }
};

// 对象结构
class ObjectStructure {
private:
    vector<shared_ptr<Element>> elements;
public:
    void addElement(shared_ptr<Element> element) {
        elements.push_back(element);
    }
    void accept(shared_ptr<Visitor> visitor) {
        for (auto& element : elements) {
            element->accept(visitor);
        }
    }
};

int main() {
    // 创建文件和文件夹
    auto file1 = make_shared<File>("file1.txt");
    auto file2 = make_shared<File>("file2.txt");
    auto folder = make_shared<Folder>("Documents");

    // 创建对象结构
    ObjectStructure structure;
    structure.addElement(file1);
    structure.addElement(file2);
    structure.addElement(folder);

    // 创建访问者并访问对象结构
    auto printVisitor = make_shared<PrintVisitor>();
    structure.accept(printVisitor);

    return 0;
}
