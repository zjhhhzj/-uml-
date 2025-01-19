//工厂模式将创建对象代码包装，实现创建对象代码与业务逻辑代码分离
//工厂方法模式是指将对象的创建延迟到子类，通过定义一个工厂接口或抽象类，让子类决定实例化哪一个具体类(每个类都有对应的工厂)
//举例:我的世界中的刷怪塔

//定义僵尸父类
class Zombie
{
public:
    Zombie(int life):life(life){};
    virtual ~Zombie();
protected:
    int life;
};
//定义普通僵尸
class Zombie_Simple:public Zombie
{
public:
    Zombie_Simple(int life=100):Zombie(life){};
    virtual ~Zombie_Simple();
};
//定义僵尸村民
class Zombie_Villager:public Zombie
{
public:
    Zombie_Villager(int life=80):Zombie(life){};
    virtual ~Zombie_Villager();
};
//定义溺尸
class Zombie_Drowned:public Zombie
{
public:
    Zombie_Drowned(int life=150):Zombie(life){};
    virtual ~Zombie_Drowned();
};

//定义僵尸工厂父类
class Zombie_Factor
{
public:
    virtual Zombie* Create_Zombie()=0;
};
//定义普通僵尸工厂
class Zombie_Simple_Factor:public Zombie_Factor
{
public:
    virtual Zombie* Create_Zombie()=0;
};
//定义僵尸村民工厂
class Zombie_Villager_Factor:public Zombie_Factor
{
public:
    virtual Zombie* Create_Zombie()=0;
};
//定义溺尸工厂
class Zombie_Drowned_Factor:public Zombie_Factor
{
public:
    virtual Zombie* Create_Zombie()=0;
};


Zombie* Zombie_Simple_Factor::Create_Zombie(){
    return new Zombie_Simple;
}
Zombie* Zombie_Villager_Factor::Create_Zombie(){
    return new Zombie_Villager;
}
Zombie* Zombie_Drowned_Factor::Create_Zombie(){
    return new Zombie_Drowned;
}


