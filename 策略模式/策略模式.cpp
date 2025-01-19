//定义了一系列算法，并将每个算法封装起来，使它们可以互相替换

// Context（上下文类）：持有一个 Strategy 对象的引用。客户端通过上下文类调用策略接口，而无需直接与具体策略交互。
// Strategy（抽象策略接口）：定义算法的通用接口。
// ConcreteStrategy（具体策略类）：实现 Strategy 接口，封装具体的算法或行为。

//例如，不同血瓶的策略
// 定义角色类(上下文类)
typedef Character Context;
class Character
{
private:
    int life;   // 生命值
    Strategy* strgy;
public:
    int GetLife(){return life;}
    void SetLife(int tmpLife){life=tmpLife;}
    
    void setStrategy(Strategy* tmpStrgy) {  //设置策略
        strgy = tmpStrgy;
    }
    void executeStrategy() {                //执行策略
        if (strgy) {
            strgy->Execute(this);
        }
    }
};

// 抽象策略
class Strategy {
public:
    virtual ~Strategy() {}
    virtual void Execute(Character*) = 0; // 抽象方法，定义算法接口
};

// 小血瓶策略
class Strgy_SmallBloodVials:public Strategy{
public:
    virtual void Execute(Character* pChct){
        pChct->SetLife(pChct->GetLife()+100);
    }
};

// 大血瓶策略
class Strgy_BigBloodVials:public Strategy{
public:
    virtual void Execute(Character* pChct){
        pChct->SetLife(pChct->GetLife()+500);
    }
};