//允许通过复制现有对象来创建新对象，而不是通过实例化类来创建。通过实现一个克隆接口（如 Clone() 方法），对象可以自我复制
//举例，某个角色的技能分身

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
    virtual Character* Clone()=0;              // 技能：分身
};

// 战士角色
class Chct_Warrior : public Character
{
public:
    Chct_Warrior(int life, int magic, int attack) : Character(life, magic, attack) {};
    Chct_Warrior(const Chct_Warrior& tmpWarrior) : Character(tmpWarrior.life,tmpWarrior.magic,tmpWarrior.attack) {};
    virtual ~Chct_Warrior();

    virtual Character* Clone(){
        return new Chct_Warrior(*this);
    };
};
// 法师角色
class Chct_Mage : public Character
{
public:
    Chct_Mage(int life, int magic, int attack) : Character(life, magic, attack) {};
    Chct_Mage(const Chct_Mage& tmpMage) : Character(tmpMage.life,tmpMage.magic,tmpMage.attack) {};
    virtual ~Chct_Mage();

    virtual Character* Clone(){
        return new Chct_Mage(*this);
    };
};
