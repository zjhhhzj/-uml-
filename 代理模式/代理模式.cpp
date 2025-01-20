//为其他对象提供一种代理以控制对这个对象的访问。代理对象可以在不改变目标对象接口的情况下，控制、增强或简化对目标对象的访问

// Subject（抽象主题）定义目标对象和代理对象的公共接口，例如 request() 方法。
// RealSubject（真实主题）实现目标对象的核心业务逻辑。
// Proxy（代理类）持有对 RealSubject 的引用，通过代理对象控制对真实对象的访问。

//举例(虚拟代理): 有一个图片加载的场景，通过代理模式可以在真正需要加载图片时才执行加载操作

#include <iostream>
#include <string>
#include <memory>
using namespace std;

// 抽象主题接口
class Image {
public:
    virtual ~Image() = default;
    virtual void display() = 0; // 显示图片
};

// 真实主题类：负责加载和显示图片
class RealImage : public Image {
private:
    string filePath;

    void loadFromDisk() {
        cout << "Loading image from disk: " << filePath << endl;
    }

public:
    RealImage(const string& filePath) : filePath(filePath) {
        loadFromDisk(); // 构造时加载图片
    }

    void display() override {
        cout << "Displaying image: " << filePath << endl;
    }
};

// 代理类：控制对 RealImage 的访问
class ProxyImage : public Image {
private:
    string filePath;
    shared_ptr<RealImage> realImage; // 延迟加载的真实图片

public:
    ProxyImage(const string& filePath) : filePath(filePath), realImage(nullptr) {}

    void display() override {
        if (!realImage) {
            // 延迟加载图片
            realImage = make_shared<RealImage>(filePath);
        }
        realImage->display();
    }
};

int main() {
    // 创建代理对象
    ProxyImage proxyImage("/example.jpg");

    // 图片未加载，此时不会触发加载
    cout << "Image not loaded yet." << endl;

    // 第一次显示图片，触发加载
    proxyImage.display();

    // 第二次显示图片，不再加载
    proxyImage.display();

    return 0;
}
