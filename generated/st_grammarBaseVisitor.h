
// Generated from /home/lai/mini_plc/tools/../grammar/st_grammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "st_grammarVisitor.h"


namespace antlrcpptest {

/**
 * This class provides an empty implementation of st_grammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  st_grammarBaseVisitor : public st_grammarVisitor {
public:

  virtual std::any visitProgram(st_grammarParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarBlock(st_grammarParser::VarBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(st_grammarParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSpec(st_grammarParser::TypeSpecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementaryType(st_grammarParser::ElementaryTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayType(st_grammarParser::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDimensionRange(st_grammarParser::DimensionRangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(st_grammarParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(st_grammarParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementList(st_grammarParser::StatementListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStatement(st_grammarParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(st_grammarParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(st_grammarParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(st_grammarParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExitStatement(st_grammarParser::ExitStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(st_grammarParser::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument(st_grammarParser::ArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(st_grammarParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrExpression(st_grammarParser::OrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndExpression(st_grammarParser::AndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualityExpression(st_grammarParser::EqualityExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationalExpression(st_grammarParser::RelationalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveExpression(st_grammarParser::AdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicativeExpression(st_grammarParser::MultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpression(st_grammarParser::UnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpression(st_grammarParser::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(st_grammarParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(st_grammarParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable(st_grammarParser::VariableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDbVariable(st_grammarParser::DbVariableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDbArea(st_grammarParser::DbAreaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAbsoluteAddressBase(st_grammarParser::AbsoluteAddressBaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitSpecifier(st_grammarParser::BitSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace antlrcpptest
