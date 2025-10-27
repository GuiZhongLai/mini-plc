
// Generated from /home/lai/mini_plc/tools/../grammar/st_grammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "st_grammarParser.h"


namespace antlrcpptest {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by st_grammarParser.
 */
class  st_grammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by st_grammarParser.
   */
    virtual std::any visitProgram(st_grammarParser::ProgramContext *context) = 0;

    virtual std::any visitVarBlock(st_grammarParser::VarBlockContext *context) = 0;

    virtual std::any visitVariableDeclaration(st_grammarParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitTypeSpec(st_grammarParser::TypeSpecContext *context) = 0;

    virtual std::any visitElementaryType(st_grammarParser::ElementaryTypeContext *context) = 0;

    virtual std::any visitArrayType(st_grammarParser::ArrayTypeContext *context) = 0;

    virtual std::any visitDimensionRange(st_grammarParser::DimensionRangeContext *context) = 0;

    virtual std::any visitStatement(st_grammarParser::StatementContext *context) = 0;

    virtual std::any visitIfStatement(st_grammarParser::IfStatementContext *context) = 0;

    virtual std::any visitStatementList(st_grammarParser::StatementListContext *context) = 0;

    virtual std::any visitForStatement(st_grammarParser::ForStatementContext *context) = 0;

    virtual std::any visitWhileStatement(st_grammarParser::WhileStatementContext *context) = 0;

    virtual std::any visitAssignment(st_grammarParser::AssignmentContext *context) = 0;

    virtual std::any visitReturnStatement(st_grammarParser::ReturnStatementContext *context) = 0;

    virtual std::any visitExitStatement(st_grammarParser::ExitStatementContext *context) = 0;

    virtual std::any visitArgumentList(st_grammarParser::ArgumentListContext *context) = 0;

    virtual std::any visitArgument(st_grammarParser::ArgumentContext *context) = 0;

    virtual std::any visitExpression(st_grammarParser::ExpressionContext *context) = 0;

    virtual std::any visitOrExpression(st_grammarParser::OrExpressionContext *context) = 0;

    virtual std::any visitAndExpression(st_grammarParser::AndExpressionContext *context) = 0;

    virtual std::any visitEqualityExpression(st_grammarParser::EqualityExpressionContext *context) = 0;

    virtual std::any visitRelationalExpression(st_grammarParser::RelationalExpressionContext *context) = 0;

    virtual std::any visitAdditiveExpression(st_grammarParser::AdditiveExpressionContext *context) = 0;

    virtual std::any visitMultiplicativeExpression(st_grammarParser::MultiplicativeExpressionContext *context) = 0;

    virtual std::any visitUnaryExpression(st_grammarParser::UnaryExpressionContext *context) = 0;

    virtual std::any visitPrimaryExpression(st_grammarParser::PrimaryExpressionContext *context) = 0;

    virtual std::any visitLiteral(st_grammarParser::LiteralContext *context) = 0;

    virtual std::any visitFunctionCall(st_grammarParser::FunctionCallContext *context) = 0;

    virtual std::any visitVariable(st_grammarParser::VariableContext *context) = 0;

    virtual std::any visitDbVariable(st_grammarParser::DbVariableContext *context) = 0;

    virtual std::any visitDbArea(st_grammarParser::DbAreaContext *context) = 0;

    virtual std::any visitAbsoluteAddressBase(st_grammarParser::AbsoluteAddressBaseContext *context) = 0;

    virtual std::any visitBitSpecifier(st_grammarParser::BitSpecifierContext *context) = 0;


};

}  // namespace antlrcpptest
