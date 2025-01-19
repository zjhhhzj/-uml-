// 用于提供一种顺序访问聚合对象中各个元素的方法，而无需暴露其内部表示。它将遍历逻辑与集合的实现分离

// Iterator（抽象迭代器）：定义访问和遍历元素的接口，例如 next() 方法。
// ConcreteIterator（具体迭代器）：实现 Iterator 接口，并维护遍历状态（如当前索引）。
// Aggregate（抽象聚合类）：定义创建迭代器的接口（createIterator()）。
// ConcreteAggregate（具体聚合类）：实现 Aggregate 接口，提供存储和管理元素的功能，并返回一个具体迭代器。

// 举例，自定义vector代码

// 抽象迭代器模板
template <typename T>
class Iterator
{
public:
    virtual void First() = 0;
    virtual bool IsEnd() = 0;
    virtual void Next() = 0;
    virtual T &Get() = 0;
    virtual ~Iterator() {}
};

// 抽象聚合类模板
template <typename T>
class Aggregate
{
public:
    virtual Iterator<T>* createIterator() = 0;
    virtual int GetSize() = 0;
    virtual T& GetItem(int index) = 0;
};

// 具体迭代器
template <typename T>
class ConcreteIterator : public Iterator<T>
{
private:
    Aggregate<T> *pAgrt;
    int currentPosition;

public:
    ConcreteIterator(Aggregate<T> *agg) : pAgrt(agg), currentPosition(0) {}

    void next() override
    {
        if (currentPosition < pAgrt->GetSize())
            ++currentPosition;
    }
    void First() override
    {
        currentPosition = 0;
    }
    bool IsEnd() override
    {
        return currentPosition >= pAgrt->GetSize();
    }
    T &Get() override
    {
        return pAgrt->GetItem(currentPosition);
    }
};

// 具体聚合类
template <typename T>
class ConcreteAggregate : public Aggregate<T>
{
private:
    T elem[10];

public:
    virtual Iterator<T> *createIterator() override
    {
        return new ConcreteIterator<T>(this);
    }
    virtual int GetSize() override
    {
        return 10;
    }
    virtual T &GetItem(int index) override
    {
        return elem[index];
    }
};

// 测试代码
int main()
{
    Aggregate<int> *pAgg = new ConcreteAggregate<int>;
    Iterator<int> *iter = pAgg->createIterator();

    for(iter->First();!iter->IsEnd();iter->Next())      //访问
        iter->Get()++;                                  //操作

    delete pAgg;
    delete iter;
}