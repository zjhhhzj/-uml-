//将一个复杂对象的构建过程与它的表示分离，使得同样的构建过程可以创建不同的表示(与模板方法相似，但侧重点在于创建复杂对象而非复用算法的结构)

// Builder（抽象建造者）：定义构建产品的抽象接口。
// ConcreteBuilder（具体建造者）：实现 Builder 接口，完成具体产品的构建。提供获取最终产品的方法。
// Director（指挥者）：控制建造过程，按照一定的顺序调用建造者的方法。不直接创建产品，而是通过建造者完成。
// Product（产品）：最终要创建的复杂对象。

//举例，僵尸由头部，躯干，四肢组成
// 定义抽象角色(产品)
typedef Character Product;
class Character
{
}; 
// 战士角色
class Chct_Warrior : public Character
{
};
// 法师角色
class Chct_Mage : public Character
{
};

// 抽象建造者
class Builder
{
public:
    virtual bool LoadTrunk() = 0;   // 装载躯干
    virtual void LoadHead() = 0;    // 装载头部
    virtual void LoadLimbs() = 0;   // 装载四肢

    Character* GetResult(){
        return pChct;
    }

protected:
    Character* pChct;             
};
// 战士建造者
class Warrior_Builder: public Builder
{
public:
    Warrior_Builder(){
        pChct=new Chct_Warrior;
    };

    virtual bool LoadTrunk(){};   // 装载躯干
    virtual void LoadHead(){};    // 装载头部
    virtual void LoadLimbs(){};   // 装载四肢
};
// 法师建造者
class Mage_Builder: public Builder
{
public:
    Mage_Builder(){
        pChct=new Chct_Mage;
    };

    virtual bool LoadTrunk(){};   // 装载躯干
    virtual void LoadHead(){};    // 装载头部
    virtual void LoadLimbs(){};   // 装载四肢
};

//指挥者
// 指挥者
class Director {
public:
    Director(Builder* ptmpBuilder):pBuilder(ptmpBuilder){};
    void setBuilder(Builder* ptmpBuilder) { pBuilder = ptmpBuilder; }//指定新的建造者

    void Construct() {       //组装
        if (pBuilder) {
            pBuilder->LoadTrunk();
            pBuilder->LoadHead();
            pBuilder->LoadLimbs();
        }
    }

private:
    Builder* pBuilder;
};

int main() {
    // 创建战士建造者
    Builder* builder = new Warrior_Builder;

    // 创建指挥者并设置建造者
    Director director(builder);

    // 指挥者控制建造过程
    director.Construct();

    // 获取最终产品
    Character* pChct = builder->GetResult();

    // 清理内存
    delete builder;
    delete pChct;

    return 0;
}
