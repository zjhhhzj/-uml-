// 确保一个类只有一个实例，并提供一个全局的访问点。它常用于需要控制全局共享资源（如配置管理器、日志记录器、数据库连接池等）的场景，适用于多线程

// 饿汉式: 类加载时就创建单例实例,优点：线程安全，简单实现。缺点：如果实例未被使用，会浪费资源。
// 懒汉式: 在第一次调用 getInstance() 时才创建单例实例。优点：延迟加载，只有在需要时才创建实例，节省资源。缺点：需要注意线程安全问题，可能引发多线程环境下的并发问题

// 举例: 一个项目的配置文件

#include <iostream>
#include <mutex>
using namespace std;

class Singleton
{
private:
    static Singleton *instance; // 静态指针，存储唯一实例
    static mutex mtx;           // 互斥锁，用于线程安全

    // 私有构造函数，禁止外部实例化
    Singleton()
    {
        cout << "Singleton instance created." << endl;
    }

public:
    virtual ~Singleton()
    {
        if (instance != nullptr)
            delete instance;
    }

    // 禁止拷贝构造和赋值操作
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    // 静态方法，获取唯一实例
    static Singleton *getInstance()
    {
        if (instance == nullptr)
        { // 双重检查锁定
            lock_guard<mutex> lock(mtx);
            if (instance == nullptr)
            {
                instance = new Singleton();
            }
        }
        return instance;
    }
};

// 初始化静态成员
Singleton *Singleton::instance = nullptr; // 懒汉式
mutex Singleton::mtx;

int main()
{
    // 获取单例实例并调用方法
    Singleton *s1 = Singleton::getInstance();

    // 再次获取实例，验证是同一个对象
    Singleton *s2 = Singleton::getInstance();
    cout << "Are s1 and s2 the same? " << (s1 == s2 ? "Yes" : "No") << endl;

    return 0;
}
