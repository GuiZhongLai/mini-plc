#ifndef COMPILER_H
#define COMPILER_H

#include "st_grammarBaseVisitor.h"
#include "st_grammarParser.h"
#include "st_grammarLexer.h"
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <any>

using namespace antlrcpptest;
using namespace antlr4;

// 表示一个数组维度：[low .. high]
struct ArrayDimension
{
    int lower;
    int upper;
    int size() const { return upper - lower + 1; }

    ArrayDimension(int l, int h) : lower(l), upper(h) {}
};
// 数组信息
struct ArrayInfo
{
    std::vector<ArrayDimension> dimensions;
    std::string baseType;

    // 计算总大小
    int totalSize() const
    {
        int size = 1;
        for (const auto &dim : dimensions)
        {
            size *= dim.size();
        }
        return size;
    }
};

class Compiler : public st_grammarBaseVisitor
{
public:
    Compiler();
    ~Compiler();

    // 生成C++代码
    std::string generateCode(st_grammarParser::ProgramContext *program);

    // VAR块相关的方法
    virtual std::any visitVarBlock(st_grammarParser::VarBlockContext *ctx) override;
    virtual std::any visitVariableDeclaration(st_grammarParser::VariableDeclarationContext *ctx) override;
    virtual std::any visitTypeSpec(st_grammarParser::TypeSpecContext *ctx) override;
    virtual std::any visitElementaryType(st_grammarParser::ElementaryTypeContext *ctx) override;
    virtual std::any visitArrayType(st_grammarParser::ArrayTypeContext *ctx) override;

    // 处理程序结构
    virtual std::any visitProgram(st_grammarParser::ProgramContext *ctx) override;
    virtual std::any visitStatement(st_grammarParser::StatementContext *ctx) override;
    virtual std::any visitStatementList(st_grammarParser::StatementListContext *ctx) override;

    // 处理控制结构
    virtual std::any visitIfStatement(st_grammarParser::IfStatementContext *ctx) override;
    virtual std::any visitForStatement(st_grammarParser::ForStatementContext *ctx) override;
    virtual std::any visitWhileStatement(st_grammarParser::WhileStatementContext *ctx) override;

    // 处理语句和表达式
    virtual std::any visitAssignment(st_grammarParser::AssignmentContext *ctx) override;
    virtual std::any visitReturnStatement(st_grammarParser::ReturnStatementContext *ctx) override;
    virtual std::any visitExitStatement(st_grammarParser::ExitStatementContext *ctx) override;

    // 处理表达式层级
    virtual std::any visitExpression(st_grammarParser::ExpressionContext *ctx) override;
    virtual std::any visitOrExpression(st_grammarParser::OrExpressionContext *ctx) override;
    virtual std::any visitAndExpression(st_grammarParser::AndExpressionContext *ctx) override;
    virtual std::any visitEqualityExpression(st_grammarParser::EqualityExpressionContext *ctx) override;
    virtual std::any visitRelationalExpression(st_grammarParser::RelationalExpressionContext *ctx) override;
    virtual std::any visitAdditiveExpression(st_grammarParser::AdditiveExpressionContext *ctx) override;
    virtual std::any visitMultiplicativeExpression(st_grammarParser::MultiplicativeExpressionContext *ctx) override;
    virtual std::any visitUnaryExpression(st_grammarParser::UnaryExpressionContext *ctx) override;
    virtual std::any visitPrimaryExpression(st_grammarParser::PrimaryExpressionContext *ctx) override;

    // 处理变量
    virtual std::any visitVariable(st_grammarParser::VariableContext *ctx) override;
    virtual std::any visitLiteral(st_grammarParser::LiteralContext *ctx) override;

    // 处理函数调用
    virtual std::any visitFunctionCall(st_grammarParser::FunctionCallContext *ctx) override;

private:
    std::stringstream code_;                           // 用于构建生成的C++代码
    std::set<std::string> declaredVariables_;          // 记录已声明的变量，避免重复声明
    int indentLevel_ = 0;                              // 当前缩进级别，用于代码格式化
    std::map<std::string, std::string> variableTypes_; // 存储变量名到类型的映射
    std::map<std::string, ArrayInfo> arrayInfo_;       // 数组信息

    // 辅助函数
    std::string getIndent();                              // 获取当前缩进字符串
    void increaseIndent();                                // 增加缩进级别
    void decreaseIndent();                                // 减少缩进级别
    std::string convertOperator(const std::string &stOp); // 转换ST操作符到C++操作符
    std::string convertType(const std::string &stType);   // 类型转换方法
    std::string areaToString(const int a);
};

#endif