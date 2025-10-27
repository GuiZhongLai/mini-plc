
// Generated from /home/lai/mini_plc/tools/../grammar/st_grammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "st_grammarParser.h"


namespace antlrcpptest {

/**
 * This interface defines an abstract listener for a parse tree produced by st_grammarParser.
 */
class  st_grammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(st_grammarParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(st_grammarParser::ProgramContext *ctx) = 0;

  virtual void enterVarBlock(st_grammarParser::VarBlockContext *ctx) = 0;
  virtual void exitVarBlock(st_grammarParser::VarBlockContext *ctx) = 0;

  virtual void enterVariableDeclaration(st_grammarParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(st_grammarParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterTypeSpec(st_grammarParser::TypeSpecContext *ctx) = 0;
  virtual void exitTypeSpec(st_grammarParser::TypeSpecContext *ctx) = 0;

  virtual void enterElementaryType(st_grammarParser::ElementaryTypeContext *ctx) = 0;
  virtual void exitElementaryType(st_grammarParser::ElementaryTypeContext *ctx) = 0;

  virtual void enterArrayType(st_grammarParser::ArrayTypeContext *ctx) = 0;
  virtual void exitArrayType(st_grammarParser::ArrayTypeContext *ctx) = 0;

  virtual void enterDimensionRange(st_grammarParser::DimensionRangeContext *ctx) = 0;
  virtual void exitDimensionRange(st_grammarParser::DimensionRangeContext *ctx) = 0;

  virtual void enterStatement(st_grammarParser::StatementContext *ctx) = 0;
  virtual void exitStatement(st_grammarParser::StatementContext *ctx) = 0;

  virtual void enterIfStatement(st_grammarParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(st_grammarParser::IfStatementContext *ctx) = 0;

  virtual void enterStatementList(st_grammarParser::StatementListContext *ctx) = 0;
  virtual void exitStatementList(st_grammarParser::StatementListContext *ctx) = 0;

  virtual void enterForStatement(st_grammarParser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(st_grammarParser::ForStatementContext *ctx) = 0;

  virtual void enterWhileStatement(st_grammarParser::WhileStatementContext *ctx) = 0;
  virtual void exitWhileStatement(st_grammarParser::WhileStatementContext *ctx) = 0;

  virtual void enterAssignment(st_grammarParser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(st_grammarParser::AssignmentContext *ctx) = 0;

  virtual void enterReturnStatement(st_grammarParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(st_grammarParser::ReturnStatementContext *ctx) = 0;

  virtual void enterExitStatement(st_grammarParser::ExitStatementContext *ctx) = 0;
  virtual void exitExitStatement(st_grammarParser::ExitStatementContext *ctx) = 0;

  virtual void enterArgumentList(st_grammarParser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(st_grammarParser::ArgumentListContext *ctx) = 0;

  virtual void enterArgument(st_grammarParser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(st_grammarParser::ArgumentContext *ctx) = 0;

  virtual void enterExpression(st_grammarParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(st_grammarParser::ExpressionContext *ctx) = 0;

  virtual void enterOrExpression(st_grammarParser::OrExpressionContext *ctx) = 0;
  virtual void exitOrExpression(st_grammarParser::OrExpressionContext *ctx) = 0;

  virtual void enterAndExpression(st_grammarParser::AndExpressionContext *ctx) = 0;
  virtual void exitAndExpression(st_grammarParser::AndExpressionContext *ctx) = 0;

  virtual void enterEqualityExpression(st_grammarParser::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(st_grammarParser::EqualityExpressionContext *ctx) = 0;

  virtual void enterRelationalExpression(st_grammarParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(st_grammarParser::RelationalExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(st_grammarParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(st_grammarParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(st_grammarParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(st_grammarParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterUnaryExpression(st_grammarParser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(st_grammarParser::UnaryExpressionContext *ctx) = 0;

  virtual void enterPrimaryExpression(st_grammarParser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(st_grammarParser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterLiteral(st_grammarParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(st_grammarParser::LiteralContext *ctx) = 0;

  virtual void enterFunctionCall(st_grammarParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(st_grammarParser::FunctionCallContext *ctx) = 0;

  virtual void enterVariable(st_grammarParser::VariableContext *ctx) = 0;
  virtual void exitVariable(st_grammarParser::VariableContext *ctx) = 0;

  virtual void enterDbVariable(st_grammarParser::DbVariableContext *ctx) = 0;
  virtual void exitDbVariable(st_grammarParser::DbVariableContext *ctx) = 0;

  virtual void enterDbArea(st_grammarParser::DbAreaContext *ctx) = 0;
  virtual void exitDbArea(st_grammarParser::DbAreaContext *ctx) = 0;

  virtual void enterAbsoluteAddressBase(st_grammarParser::AbsoluteAddressBaseContext *ctx) = 0;
  virtual void exitAbsoluteAddressBase(st_grammarParser::AbsoluteAddressBaseContext *ctx) = 0;

  virtual void enterBitSpecifier(st_grammarParser::BitSpecifierContext *ctx) = 0;
  virtual void exitBitSpecifier(st_grammarParser::BitSpecifierContext *ctx) = 0;


};

}  // namespace antlrcpptest
