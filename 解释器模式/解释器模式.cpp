// 用于定义语言的语法表示，并实现一个解释器来解释这些语法表达式。它适用于某些特定领域的语言处理，能够将问题分解为一系列的表达式，从而解决复杂的计算或逻辑问题

// AbstractExpression（抽象表达式）：定义解释操作的接口。
// TerminalExpression（终结符表达式）：实现与语法规则相关的操作，通常是语法树的叶子节点。
// NonTerminalExpression（非终结符表达式）：表示语法规则中非终结符的部分，通常是语法树的内部节点。
// Context（上下文）：包含解释器的全局信息，例如输入字符串或变量的值。
// Client（客户端）：构建语法树，并调用解释器解释语法树。

// 举例，技能燃烧在不同角色中采取相同算法（函数）而具体行为不一致

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <stack>
using namespace std;

// 上下文类
class Context
{
private:
    map<string, int> variables;

public:
    void setVariable(const string &name, int value)
    {
        variables[name] = value;
    }

    int getVariable(const string &name) const
    {
        return variables.at(name); // 如果键不存在，会抛出 std::out_of_range 异常
    }
};

// 抽象表达式类
class Expression
{
public:
    virtual int interpret(const Context &context) const = 0;
    virtual ~Expression() = default;
};

// 终结符表达式：变量
class VariableExpression : public Expression
{
private:
    string name;

public:
    explicit VariableExpression(const string &varName) : name(varName) {}

    int interpret(const Context &context) const override
    {
        return context.getVariable(name);
    }
};

// 终结符表达式：常量
class ConstantExpression : public Expression
{
private:
    int value;

public:
    explicit ConstantExpression(int val) : value(val) {}

    int interpret(const Context &context) const override
    {
        return value;
    }
};

// 非终结符表达式：加法
class AddExpression : public Expression
{
private:
    shared_ptr<Expression> left;
    shared_ptr<Expression> right;

public:
    AddExpression(shared_ptr<Expression> leftExpr, shared_ptr<Expression> rightExpr)
        : left(move(leftExpr)), right(move(rightExpr)) {}

    int interpret(const Context &context) const override
    {
        return left->interpret(context) + right->interpret(context);
    }
};

// 非终结符表达式：减法
class SubtractExpression : public Expression
{
private:
    shared_ptr<Expression> left;
    shared_ptr<Expression> right;

public:
    SubtractExpression(shared_ptr<Expression> leftExpr, shared_ptr<Expression> rightExpr)
        : left(move(leftExpr)), right(move(rightExpr)) {}

    int interpret(const Context &context) const override
    {
        return left->interpret(context) - right->interpret(context);
    }
};

int main()
{
    // 创建上下文并设置变量
    Context context;
    context.setVariable("x", 10);
    context.setVariable("y", 20);

    // 构建表达式：x + y - 5
    shared_ptr<Expression> expression = make_shared<SubtractExpression>(
        make_shared<AddExpression>(
            make_shared<VariableExpression>("x"),
            make_shared<VariableExpression>("y")),
        make_shared<ConstantExpression>(5));

    // 解释表达式
    cout << "Result: " << expression->interpret(context) << endl;

    return 0;
}
