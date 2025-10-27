
// Generated from /home/lai/mini_plc/tools/../grammar/st_grammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "st_grammarListener.h"


namespace antlrcpptest {

/**
 * This class provides an empty implementation of st_grammarListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  st_grammarBaseListener : public st_grammarListener {
public:

  virtual void enterProgram(st_grammarParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(st_grammarParser::ProgramContext * /*ctx*/) override { }

  virtual void enterVarBlock(st_grammarParser::VarBlockContext * /*ctx*/) override { }
  virtual void exitVarBlock(st_grammarParser::VarBlockContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(st_grammarParser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(st_grammarParser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterTypeSpec(st_grammarParser::TypeSpecContext * /*ctx*/) override { }
  virtual void exitTypeSpec(st_grammarParser::TypeSpecContext * /*ctx*/) override { }

  virtual void enterElementaryType(st_grammarParser::ElementaryTypeContext * /*ctx*/) override { }
  virtual void exitElementaryType(st_grammarParser::ElementaryTypeContext * /*ctx*/) override { }

  virtual void enterArrayType(st_grammarParser::ArrayTypeContext * /*ctx*/) override { }
  virtual void exitArrayType(st_grammarParser::ArrayTypeContext * /*ctx*/) override { }

  virtual void enterDimensionRange(st_grammarParser::DimensionRangeContext * /*ctx*/) override { }
  virtual void exitDimensionRange(st_grammarParser::DimensionRangeContext * /*ctx*/) override { }

  virtual void enterStatement(st_grammarParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(st_grammarParser::StatementContext * /*ctx*/) override { }

  virtual void enterIfStatement(st_grammarParser::IfStatementContext * /*ctx*/) override { }
  virtual void exitIfStatement(st_grammarParser::IfStatementContext * /*ctx*/) override { }

  virtual void enterStatementList(st_grammarParser::StatementListContext * /*ctx*/) override { }
  virtual void exitStatementList(st_grammarParser::StatementListContext * /*ctx*/) override { }

  virtual void enterForStatement(st_grammarParser::ForStatementContext * /*ctx*/) override { }
  virtual void exitForStatement(st_grammarParser::ForStatementContext * /*ctx*/) override { }

  virtual void enterWhileStatement(st_grammarParser::WhileStatementContext * /*ctx*/) override { }
  virtual void exitWhileStatement(st_grammarParser::WhileStatementContext * /*ctx*/) override { }

  virtual void enterAssignment(st_grammarParser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(st_grammarParser::AssignmentContext * /*ctx*/) override { }

  virtual void enterReturnStatement(st_grammarParser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(st_grammarParser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterExitStatement(st_grammarParser::ExitStatementContext * /*ctx*/) override { }
  virtual void exitExitStatement(st_grammarParser::ExitStatementContext * /*ctx*/) override { }

  virtual void enterArgumentList(st_grammarParser::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(st_grammarParser::ArgumentListContext * /*ctx*/) override { }

  virtual void enterArgument(st_grammarParser::ArgumentContext * /*ctx*/) override { }
  virtual void exitArgument(st_grammarParser::ArgumentContext * /*ctx*/) override { }

  virtual void enterExpression(st_grammarParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(st_grammarParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterOrExpression(st_grammarParser::OrExpressionContext * /*ctx*/) override { }
  virtual void exitOrExpression(st_grammarParser::OrExpressionContext * /*ctx*/) override { }

  virtual void enterAndExpression(st_grammarParser::AndExpressionContext * /*ctx*/) override { }
  virtual void exitAndExpression(st_grammarParser::AndExpressionContext * /*ctx*/) override { }

  virtual void enterEqualityExpression(st_grammarParser::EqualityExpressionContext * /*ctx*/) override { }
  virtual void exitEqualityExpression(st_grammarParser::EqualityExpressionContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(st_grammarParser::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(st_grammarParser::RelationalExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(st_grammarParser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(st_grammarParser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(st_grammarParser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(st_grammarParser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(st_grammarParser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(st_grammarParser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterPrimaryExpression(st_grammarParser::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(st_grammarParser::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterLiteral(st_grammarParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(st_grammarParser::LiteralContext * /*ctx*/) override { }

  virtual void enterFunctionCall(st_grammarParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(st_grammarParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterVariable(st_grammarParser::VariableContext * /*ctx*/) override { }
  virtual void exitVariable(st_grammarParser::VariableContext * /*ctx*/) override { }

  virtual void enterDbVariable(st_grammarParser::DbVariableContext * /*ctx*/) override { }
  virtual void exitDbVariable(st_grammarParser::DbVariableContext * /*ctx*/) override { }

  virtual void enterDbArea(st_grammarParser::DbAreaContext * /*ctx*/) override { }
  virtual void exitDbArea(st_grammarParser::DbAreaContext * /*ctx*/) override { }

  virtual void enterAbsoluteAddressBase(st_grammarParser::AbsoluteAddressBaseContext * /*ctx*/) override { }
  virtual void exitAbsoluteAddressBase(st_grammarParser::AbsoluteAddressBaseContext * /*ctx*/) override { }

  virtual void enterBitSpecifier(st_grammarParser::BitSpecifierContext * /*ctx*/) override { }
  virtual void exitBitSpecifier(st_grammarParser::BitSpecifierContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace antlrcpptest
