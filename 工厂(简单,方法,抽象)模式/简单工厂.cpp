//工厂模式将创建对象代码包装，实现创建对象代码与业务逻辑代码分离
//简单工厂模式是指由一个工厂类根据参数决定创建哪一种具体产品类的实例(由一个工厂类负责创建所有对象)
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

//定义僵尸工厂
class Zombie_Factor
{
public:
    Zombie *pZomb;
    Zombie* Create_Zombie(char *const);
};

Zombie* Zombie_Factor::Create_Zombie(char *const zombieName){
    if(zombieName=="Zombie Simple"){
        pZomb=new Zombie_Simple;
    }else if(zombieName=="Zombie Villager"){
        pZomb=new Zombie_Villager;
    }else if(zombieName=="ZombieDrowned"){
        pZomb=new Zombie_Drowned;
    }
    return pZomb;
}


