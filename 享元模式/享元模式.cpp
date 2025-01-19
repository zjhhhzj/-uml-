//定义了一个操作中的算法框架，而将一些步骤的实现延迟到子类中。通过模板方法，子类可以在不改变算法结构的情况下，重新定义算法中的某些步骤。
//钩子方法：子类提供一种扩展或定制(控制)父类行为的机制，同时保持父类的整体算法结构不变（下面的Can_Use函数）。
//举例，技能燃烧在不同角色中采取相同算法（函数）而具体行为不一致

// 定义角色类
class Character
{
public:
    Character(int life, int magic, int attack) : life(life), magic(magic), attack(attack) {};
    virtual ~Character() {};

protected:
    // 角色属性值
    int life;   // 生命值
    int magic;  // 魔法值
    int attack; // 攻击力

public:
    virtual void Burn();              // 技能：燃烧

private:
    virtual bool Can_Use() = 0;       // 条件是否满足
    virtual void Effect_Enemy() = 0;  // 对敌人影响
    virtual void Effect_Self() = 0;   // 对自身影响
};

// 战士角色
class Chct_Warrior : public Character
{
public:
    Chct_Warrior(int life, int magic, int attack) : Character(life, magic, attack) {};
    virtual ~Chct_Warrior();
private:
    virtual bool Can_Use() = 0;       // 条件是否满足
    virtual void Effect_Enemy();  // 对敌人影响
    virtual void Effect_Self();   // 对自身影响
};

// 法师角色
class Chct_Mage : public Character
{
public:
    Chct_Mage(int life, int magic, int attack) : Character(life, magic, attack) {};
    virtual ~Chct_Mage();
private:
    virtual bool Can_Use() = 0;       // 条件是否满足
    virtual void Effect_Enemy();  // 对敌人影响
    virtual void Effect_Self();   // 对自身影响
};

// 父类定义算法框架：算法的整体逻辑由父类控制。
void Character::Burn()
{   
    if(Can_Use()){
        Effect_Enemy();
        Effect_Self();
    }
    
}

// 子类实现具体步骤：某些具体步骤的实现由子类完成。
bool Chct_Warrior::Can_Use() {
    if(life>100)return true;
    return false;
};
void Chct_Warrior::Effect_Enemy() 
{
    //敌人生命值减少600
};
void Chct_Warrior::Effect_Self() {
    life-=100;//自身生命值减少400
};

bool Chct_Mage::Can_Use() {
    if(magic>200)return true;
    return false;
};
void Chct_Mage::Effect_Enemy() 
{
    //敌人生命值减少1000
};
void Chct_Mage::Effect_Self() {
    magic-=100;//自身魔法值减少200
};