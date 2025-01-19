// 工厂模式将创建对象代码包装，实现创建对象代码与业务逻辑代码分离
// 抽象工厂模式是指提供一个接口，用于创建一系列相关或相互依赖的对象，而无需指定它们的具体类(一个工厂子类生产多种相同产品族的对象)
// 缺点：当产品族中新增产品（等级结构）时，需要修改抽象工厂接口，违背了开闭原则
// 举例:我的世界中的刷怪塔，置于雪地，沙漠，海洋三种不同环境

// 定义僵尸父类
class Zombie
{
public:
    Zombie(int life) : life(life) {};
    virtual ~Zombie();

protected:
    int life;
};
// 定义3种环境（产品等级结构）的普通僵尸（产品族）
class Zombie_Simple_Snow : public Zombie
{
public:
    Zombie_Simple_Snow(int life = 100) : Zombie(life) {};
};
class Zombie_Simple_Desert : public Zombie
{
public:
    Zombie_Simple_Desert(int life = 100) : Zombie(life) {};
};
class Zombie_Simple_Sea : public Zombie
{
public:
    Zombie_Simple_Sea(int life = 100) : Zombie(life) {};
};
// 定义3种环境（产品等级结构）的僵尸村民（产品族）
class Zombie_Villager_Snow : public Zombie
{
public:
    Zombie_Villager_Snow(int life = 80) : Zombie(life) {};
};
class Zombie_Villager_Desert : public Zombie
{
public:
    Zombie_Villager_Desert(int life = 80) : Zombie(life) {};
};
class Zombie_Villager_Sea : public Zombie
{
public:
    Zombie_Villager_Sea(int life = 80) : Zombie(life) {};
};
// 定义3种环境（产品等级结构）的溺尸（产品族）
class Zombie_Drowned_Snow : public Zombie
{
public:
    Zombie_Drowned_Snow(int life = 150) : Zombie(life) {};
};
class Zombie_Drowned_Desert : public Zombie
{
public:
    Zombie_Drowned_Desert(int life = 150) : Zombie(life) {};
};
class Zombie_Drowned_Sea : public Zombie
{
public:
    Zombie_Drowned_Sea(int life = 150) : Zombie(life) {};
};

// 定义僵尸工厂
class Zombie_Factor
{
public:
    virtual Zombie *Create_Zombie_Snow() = 0;
    virtual Zombie *Create_Zombie_Desert() = 0;
    virtual Zombie *Create_Zombie_Sea() = 0;
};

// 定义普通僵尸工厂
class Zombie_Simple_Factor : public Zombie_Factor
{
public:
    virtual Zombie *Create_Zombie_Snow()
    {
        return new Zombie_Simple_Snow;
    };
    virtual Zombie *Create_Zombie_Desert()
    {
        return new Zombie_Simple_Desert;
    };
    virtual Zombie *Create_Zombie_Sea()
    {
        return new Zombie_Simple_Sea;
    };
};
// 定义僵尸村民工厂
class Zombie_Villager_Factor : public Zombie_Factor
{
public:
    virtual Zombie *Create_Zombie_Snow()
    {
        return new Zombie_Villager_Snow;
    };
    virtual Zombie *Create_Zombie_Desert()
    {
        return new Zombie_Villager_Desert;
    };
    virtual Zombie *Create_Zombie_Sea()
    {
        return new Zombie_Villager_Sea;
    };
};
// 定义溺尸工厂
class Zombie_Drowned_Factor : public Zombie_Factor
{
public:
    virtual Zombie *Create_Zombie_Snow()
    {
        return new Zombie_Drowned_Snow;
    };
    virtual Zombie *Create_Zombie_Desert()
    {
        return new Zombie_Drowned_Desert;
    };
    virtual Zombie *Create_Zombie_Sea()
    {
        return new Zombie_Drowned_Sea;
    };
};
