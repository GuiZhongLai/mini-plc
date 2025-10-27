
// Generated from /home/lai/mini_plc/tools/../grammar/st_grammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"


namespace antlrcpptest {


class  st_grammarLexer : public antlr4::Lexer {
public:
  enum {
    VAR = 1, END_VAR = 2, BOOL = 3, INT = 4, REAL = 5, STRING = 6, TIME = 7, 
    ARRAY = 8, OF = 9, IF = 10, THEN = 11, END_IF = 12, ELSIF = 13, ELSE = 14, 
    FOR = 15, TO = 16, BY = 17, DO = 18, END_FOR = 19, WHILE = 20, END_WHILE = 21, 
    RETURN = 22, EXIT = 23, AND = 24, OR = 25, NOT = 26, DB_NUMBER = 27, 
    DB_BIT = 28, DB_BYTE = 29, DB_WORD = 30, DB_DWORD = 31, ABS_INPUT_BIT = 32, 
    ABS_INPUT_BYTE = 33, ABS_INPUT_WORD = 34, ABS_INPUT_DWORD = 35, ABS_OUTPUT_BIT = 36, 
    ABS_OUTPUT_BYTE = 37, ABS_OUTPUT_WORD = 38, ABS_OUTPUT_DWORD = 39, ABS_MEMORY_BIT = 40, 
    ABS_MEMORY_BYTE = 41, ABS_MEMORY_WORD = 42, ABS_MEMORY_DWORD = 43, BOOLEAN_LITERAL = 44, 
    INTEGER_LITERAL = 45, REAL_LITERAL = 46, STRING_LITERAL = 47, ASSIGN = 48, 
    EQ = 49, NEQ = 50, LT = 51, LE = 52, GT = 53, GE = 54, ADD = 55, SUB = 56, 
    MUL = 57, DIV = 58, LPAREN = 59, RPAREN = 60, SEMI = 61, COMMA = 62, 
    LBRACK = 63, RBRACK = 64, DOT = 65, COLON = 66, DOTDOT = 67, ID = 68, 
    WS = 69, COMMENT = 70, LINE_COMMENT = 71
  };

  explicit st_grammarLexer(antlr4::CharStream *input);

  ~st_grammarLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

}  // namespace antlrcpptest
