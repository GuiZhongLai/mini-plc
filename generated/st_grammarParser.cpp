
// Generated from /home/lai/mini_plc/tools/../grammar/st_grammar.g4 by ANTLR 4.13.1


#include "st_grammarListener.h"
#include "st_grammarVisitor.h"

#include "st_grammarParser.h"


using namespace antlrcpp;
using namespace antlrcpptest;

using namespace antlr4;

namespace {

struct St_grammarParserStaticData final {
  St_grammarParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  St_grammarParserStaticData(const St_grammarParserStaticData&) = delete;
  St_grammarParserStaticData(St_grammarParserStaticData&&) = delete;
  St_grammarParserStaticData& operator=(const St_grammarParserStaticData&) = delete;
  St_grammarParserStaticData& operator=(St_grammarParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag st_grammarParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
St_grammarParserStaticData *st_grammarParserStaticData = nullptr;

void st_grammarParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (st_grammarParserStaticData != nullptr) {
    return;
  }
#else
  assert(st_grammarParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<St_grammarParserStaticData>(
    std::vector<std::string>{
      "program", "varBlock", "variableDeclaration", "typeSpec", "elementaryType", 
      "arrayType", "dimensionRange", "statement", "ifStatement", "statementList", 
      "forStatement", "whileStatement", "assignment", "returnStatement", 
      "exitStatement", "argumentList", "argument", "expression", "orExpression", 
      "andExpression", "equalityExpression", "relationalExpression", "additiveExpression", 
      "multiplicativeExpression", "unaryExpression", "primaryExpression", 
      "literal", "functionCall", "variable", "dbVariable", "dbArea", "absoluteAddressBase", 
      "bitSpecifier"
    },
    std::vector<std::string>{
      "", "'VAR'", "'END_VAR'", "'BOOL'", "'INT'", "'REAL'", "'STRING'", 
      "'TIME'", "'ARRAY'", "'OF'", "'IF'", "'THEN'", "'END_IF'", "'ELSIF'", 
      "'ELSE'", "'FOR'", "'TO'", "'BY'", "'DO'", "'END_FOR'", "'WHILE'", 
      "'END_WHILE'", "'RETURN'", "'EXIT'", "'AND'", "'OR'", "'NOT'", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "':='", "'='", "'<>'", "'<'", "'<='", "'>'", "'>='", "'+'", 
      "'-'", "'*'", "'/'", "'('", "')'", "';'", "','", "'['", "']'", "'.'", 
      "':'", "'..'"
    },
    std::vector<std::string>{
      "", "VAR", "END_VAR", "BOOL", "INT", "REAL", "STRING", "TIME", "ARRAY", 
      "OF", "IF", "THEN", "END_IF", "ELSIF", "ELSE", "FOR", "TO", "BY", 
      "DO", "END_FOR", "WHILE", "END_WHILE", "RETURN", "EXIT", "AND", "OR", 
      "NOT", "DB_NUMBER", "DB_BIT", "DB_BYTE", "DB_WORD", "DB_DWORD", "ABS_INPUT_BIT", 
      "ABS_INPUT_BYTE", "ABS_INPUT_WORD", "ABS_INPUT_DWORD", "ABS_OUTPUT_BIT", 
      "ABS_OUTPUT_BYTE", "ABS_OUTPUT_WORD", "ABS_OUTPUT_DWORD", "ABS_MEMORY_BIT", 
      "ABS_MEMORY_BYTE", "ABS_MEMORY_WORD", "ABS_MEMORY_DWORD", "BOOLEAN_LITERAL", 
      "INTEGER_LITERAL", "REAL_LITERAL", "STRING_LITERAL", "ASSIGN", "EQ", 
      "NEQ", "LT", "LE", "GT", "GE", "ADD", "SUB", "MUL", "DIV", "LPAREN", 
      "RPAREN", "SEMI", "COMMA", "LBRACK", "RBRACK", "DOT", "COLON", "DOTDOT", 
      "ID", "WS", "COMMENT", "LINE_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,71,332,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,1,0,3,0,68,8,0,1,0,5,0,71,
  	8,0,10,0,12,0,74,9,0,1,0,1,0,1,1,1,1,4,1,80,8,1,11,1,12,1,81,1,1,1,1,
  	1,2,1,2,1,2,1,2,1,2,3,2,91,8,2,1,2,3,2,94,8,2,1,3,1,3,3,3,98,8,3,1,4,
  	1,4,1,5,1,5,1,5,1,5,1,5,5,5,107,8,5,10,5,12,5,110,9,5,1,5,1,5,1,5,1,5,
  	1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,127,8,7,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,5,8,138,8,8,10,8,12,8,141,9,8,1,8,1,8,3,8,145,8,
  	8,1,8,1,8,1,9,5,9,150,8,9,10,9,12,9,153,9,9,1,10,1,10,1,10,1,10,1,10,
  	1,10,1,10,1,10,3,10,163,8,10,1,10,1,10,5,10,167,8,10,10,10,12,10,170,
  	9,10,1,10,1,10,1,11,1,11,1,11,1,11,5,11,178,8,11,10,11,12,11,181,9,11,
  	1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,14,1,14,1,14,1,15,
  	1,15,1,15,5,15,199,8,15,10,15,12,15,202,9,15,1,16,1,16,3,16,206,8,16,
  	1,16,1,16,1,17,1,17,1,18,1,18,1,18,5,18,215,8,18,10,18,12,18,218,9,18,
  	1,19,1,19,1,19,5,19,223,8,19,10,19,12,19,226,9,19,1,20,1,20,1,20,5,20,
  	231,8,20,10,20,12,20,234,9,20,1,21,1,21,1,21,5,21,239,8,21,10,21,12,21,
  	242,9,21,1,22,1,22,1,22,5,22,247,8,22,10,22,12,22,250,9,22,1,23,1,23,
  	1,23,5,23,255,8,23,10,23,12,23,258,9,23,1,24,3,24,261,8,24,1,24,1,24,
  	1,25,1,25,1,25,1,25,1,25,1,25,1,25,3,25,272,8,25,1,26,1,26,1,27,1,27,
  	1,27,1,27,1,27,5,27,281,8,27,10,27,12,27,284,9,27,3,27,286,8,27,1,27,
  	1,27,1,28,1,28,1,28,3,28,293,8,28,1,28,1,28,3,28,297,8,28,1,28,1,28,5,
  	28,301,8,28,10,28,12,28,304,9,28,1,28,1,28,1,28,1,28,5,28,310,8,28,10,
  	28,12,28,313,9,28,1,28,1,28,5,28,317,8,28,10,28,12,28,320,9,28,1,29,1,
  	29,1,29,1,29,1,30,1,30,1,31,1,31,1,32,1,32,1,32,0,0,33,0,2,4,6,8,10,12,
  	14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,
  	60,62,64,0,9,1,0,3,7,1,0,49,50,1,0,51,54,1,0,55,56,1,0,57,58,2,0,26,26,
  	56,56,1,0,44,47,1,0,28,31,1,0,32,43,337,0,67,1,0,0,0,2,77,1,0,0,0,4,85,
  	1,0,0,0,6,97,1,0,0,0,8,99,1,0,0,0,10,101,1,0,0,0,12,115,1,0,0,0,14,126,
  	1,0,0,0,16,128,1,0,0,0,18,151,1,0,0,0,20,154,1,0,0,0,22,173,1,0,0,0,24,
  	184,1,0,0,0,26,189,1,0,0,0,28,192,1,0,0,0,30,195,1,0,0,0,32,205,1,0,0,
  	0,34,209,1,0,0,0,36,211,1,0,0,0,38,219,1,0,0,0,40,227,1,0,0,0,42,235,
  	1,0,0,0,44,243,1,0,0,0,46,251,1,0,0,0,48,260,1,0,0,0,50,271,1,0,0,0,52,
  	273,1,0,0,0,54,275,1,0,0,0,56,292,1,0,0,0,58,321,1,0,0,0,60,325,1,0,0,
  	0,62,327,1,0,0,0,64,329,1,0,0,0,66,68,3,2,1,0,67,66,1,0,0,0,67,68,1,0,
  	0,0,68,72,1,0,0,0,69,71,3,14,7,0,70,69,1,0,0,0,71,74,1,0,0,0,72,70,1,
  	0,0,0,72,73,1,0,0,0,73,75,1,0,0,0,74,72,1,0,0,0,75,76,5,0,0,1,76,1,1,
  	0,0,0,77,79,5,1,0,0,78,80,3,4,2,0,79,78,1,0,0,0,80,81,1,0,0,0,81,79,1,
  	0,0,0,81,82,1,0,0,0,82,83,1,0,0,0,83,84,5,2,0,0,84,3,1,0,0,0,85,86,5,
  	68,0,0,86,87,5,66,0,0,87,90,3,6,3,0,88,89,5,48,0,0,89,91,3,34,17,0,90,
  	88,1,0,0,0,90,91,1,0,0,0,91,93,1,0,0,0,92,94,5,61,0,0,93,92,1,0,0,0,93,
  	94,1,0,0,0,94,5,1,0,0,0,95,98,3,8,4,0,96,98,3,10,5,0,97,95,1,0,0,0,97,
  	96,1,0,0,0,98,7,1,0,0,0,99,100,7,0,0,0,100,9,1,0,0,0,101,102,5,8,0,0,
  	102,103,5,63,0,0,103,108,3,12,6,0,104,105,5,62,0,0,105,107,3,12,6,0,106,
  	104,1,0,0,0,107,110,1,0,0,0,108,106,1,0,0,0,108,109,1,0,0,0,109,111,1,
  	0,0,0,110,108,1,0,0,0,111,112,5,64,0,0,112,113,5,9,0,0,113,114,3,8,4,
  	0,114,11,1,0,0,0,115,116,3,34,17,0,116,117,5,67,0,0,117,118,3,34,17,0,
  	118,13,1,0,0,0,119,127,3,16,8,0,120,127,3,20,10,0,121,127,3,22,11,0,122,
  	127,3,24,12,0,123,127,3,54,27,0,124,127,3,26,13,0,125,127,3,28,14,0,126,
  	119,1,0,0,0,126,120,1,0,0,0,126,121,1,0,0,0,126,122,1,0,0,0,126,123,1,
  	0,0,0,126,124,1,0,0,0,126,125,1,0,0,0,127,15,1,0,0,0,128,129,5,10,0,0,
  	129,130,3,34,17,0,130,131,5,11,0,0,131,139,3,18,9,0,132,133,5,13,0,0,
  	133,134,3,34,17,0,134,135,5,11,0,0,135,136,3,18,9,0,136,138,1,0,0,0,137,
  	132,1,0,0,0,138,141,1,0,0,0,139,137,1,0,0,0,139,140,1,0,0,0,140,144,1,
  	0,0,0,141,139,1,0,0,0,142,143,5,14,0,0,143,145,3,18,9,0,144,142,1,0,0,
  	0,144,145,1,0,0,0,145,146,1,0,0,0,146,147,5,12,0,0,147,17,1,0,0,0,148,
  	150,3,14,7,0,149,148,1,0,0,0,150,153,1,0,0,0,151,149,1,0,0,0,151,152,
  	1,0,0,0,152,19,1,0,0,0,153,151,1,0,0,0,154,155,5,15,0,0,155,156,5,68,
  	0,0,156,157,5,48,0,0,157,158,3,34,17,0,158,159,5,16,0,0,159,162,3,34,
  	17,0,160,161,5,17,0,0,161,163,3,34,17,0,162,160,1,0,0,0,162,163,1,0,0,
  	0,163,164,1,0,0,0,164,168,5,18,0,0,165,167,3,14,7,0,166,165,1,0,0,0,167,
  	170,1,0,0,0,168,166,1,0,0,0,168,169,1,0,0,0,169,171,1,0,0,0,170,168,1,
  	0,0,0,171,172,5,19,0,0,172,21,1,0,0,0,173,174,5,20,0,0,174,175,3,34,17,
  	0,175,179,5,18,0,0,176,178,3,14,7,0,177,176,1,0,0,0,178,181,1,0,0,0,179,
  	177,1,0,0,0,179,180,1,0,0,0,180,182,1,0,0,0,181,179,1,0,0,0,182,183,5,
  	21,0,0,183,23,1,0,0,0,184,185,3,56,28,0,185,186,5,48,0,0,186,187,3,34,
  	17,0,187,188,5,61,0,0,188,25,1,0,0,0,189,190,5,22,0,0,190,191,5,61,0,
  	0,191,27,1,0,0,0,192,193,5,23,0,0,193,194,5,61,0,0,194,29,1,0,0,0,195,
  	200,3,32,16,0,196,197,5,62,0,0,197,199,3,32,16,0,198,196,1,0,0,0,199,
  	202,1,0,0,0,200,198,1,0,0,0,200,201,1,0,0,0,201,31,1,0,0,0,202,200,1,
  	0,0,0,203,204,5,68,0,0,204,206,5,48,0,0,205,203,1,0,0,0,205,206,1,0,0,
  	0,206,207,1,0,0,0,207,208,3,34,17,0,208,33,1,0,0,0,209,210,3,36,18,0,
  	210,35,1,0,0,0,211,216,3,38,19,0,212,213,5,25,0,0,213,215,3,38,19,0,214,
  	212,1,0,0,0,215,218,1,0,0,0,216,214,1,0,0,0,216,217,1,0,0,0,217,37,1,
  	0,0,0,218,216,1,0,0,0,219,224,3,40,20,0,220,221,5,24,0,0,221,223,3,40,
  	20,0,222,220,1,0,0,0,223,226,1,0,0,0,224,222,1,0,0,0,224,225,1,0,0,0,
  	225,39,1,0,0,0,226,224,1,0,0,0,227,232,3,42,21,0,228,229,7,1,0,0,229,
  	231,3,42,21,0,230,228,1,0,0,0,231,234,1,0,0,0,232,230,1,0,0,0,232,233,
  	1,0,0,0,233,41,1,0,0,0,234,232,1,0,0,0,235,240,3,44,22,0,236,237,7,2,
  	0,0,237,239,3,44,22,0,238,236,1,0,0,0,239,242,1,0,0,0,240,238,1,0,0,0,
  	240,241,1,0,0,0,241,43,1,0,0,0,242,240,1,0,0,0,243,248,3,46,23,0,244,
  	245,7,3,0,0,245,247,3,46,23,0,246,244,1,0,0,0,247,250,1,0,0,0,248,246,
  	1,0,0,0,248,249,1,0,0,0,249,45,1,0,0,0,250,248,1,0,0,0,251,256,3,48,24,
  	0,252,253,7,4,0,0,253,255,3,48,24,0,254,252,1,0,0,0,255,258,1,0,0,0,256,
  	254,1,0,0,0,256,257,1,0,0,0,257,47,1,0,0,0,258,256,1,0,0,0,259,261,7,
  	5,0,0,260,259,1,0,0,0,260,261,1,0,0,0,261,262,1,0,0,0,262,263,3,50,25,
  	0,263,49,1,0,0,0,264,265,5,59,0,0,265,266,3,34,17,0,266,267,5,60,0,0,
  	267,272,1,0,0,0,268,272,3,52,26,0,269,272,3,56,28,0,270,272,3,54,27,0,
  	271,264,1,0,0,0,271,268,1,0,0,0,271,269,1,0,0,0,271,270,1,0,0,0,272,51,
  	1,0,0,0,273,274,7,6,0,0,274,53,1,0,0,0,275,276,5,68,0,0,276,285,5,59,
  	0,0,277,282,3,34,17,0,278,279,5,62,0,0,279,281,3,34,17,0,280,278,1,0,
  	0,0,281,284,1,0,0,0,282,280,1,0,0,0,282,283,1,0,0,0,283,286,1,0,0,0,284,
  	282,1,0,0,0,285,277,1,0,0,0,285,286,1,0,0,0,286,287,1,0,0,0,287,288,5,
  	60,0,0,288,55,1,0,0,0,289,293,5,68,0,0,290,293,3,62,31,0,291,293,3,58,
  	29,0,292,289,1,0,0,0,292,290,1,0,0,0,292,291,1,0,0,0,293,296,1,0,0,0,
  	294,295,5,65,0,0,295,297,3,64,32,0,296,294,1,0,0,0,296,297,1,0,0,0,297,
  	302,1,0,0,0,298,299,5,65,0,0,299,301,5,68,0,0,300,298,1,0,0,0,301,304,
  	1,0,0,0,302,300,1,0,0,0,302,303,1,0,0,0,303,318,1,0,0,0,304,302,1,0,0,
  	0,305,306,5,63,0,0,306,311,3,34,17,0,307,308,5,62,0,0,308,310,3,34,17,
  	0,309,307,1,0,0,0,310,313,1,0,0,0,311,309,1,0,0,0,311,312,1,0,0,0,312,
  	314,1,0,0,0,313,311,1,0,0,0,314,315,5,64,0,0,315,317,1,0,0,0,316,305,
  	1,0,0,0,317,320,1,0,0,0,318,316,1,0,0,0,318,319,1,0,0,0,319,57,1,0,0,
  	0,320,318,1,0,0,0,321,322,5,27,0,0,322,323,5,65,0,0,323,324,3,60,30,0,
  	324,59,1,0,0,0,325,326,7,7,0,0,326,61,1,0,0,0,327,328,7,8,0,0,328,63,
  	1,0,0,0,329,330,3,34,17,0,330,65,1,0,0,0,31,67,72,81,90,93,97,108,126,
  	139,144,151,162,168,179,200,205,216,224,232,240,248,256,260,271,282,285,
  	292,296,302,311,318
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  st_grammarParserStaticData = staticData.release();
}

}

st_grammarParser::st_grammarParser(TokenStream *input) : st_grammarParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

st_grammarParser::st_grammarParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  st_grammarParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *st_grammarParserStaticData->atn, st_grammarParserStaticData->decisionToDFA, st_grammarParserStaticData->sharedContextCache, options);
}

st_grammarParser::~st_grammarParser() {
  delete _interpreter;
}

const atn::ATN& st_grammarParser::getATN() const {
  return *st_grammarParserStaticData->atn;
}

std::string st_grammarParser::getGrammarFileName() const {
  return "st_grammar.g4";
}

const std::vector<std::string>& st_grammarParser::getRuleNames() const {
  return st_grammarParserStaticData->ruleNames;
}

const dfa::Vocabulary& st_grammarParser::getVocabulary() const {
  return st_grammarParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView st_grammarParser::getSerializedATN() const {
  return st_grammarParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

st_grammarParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::ProgramContext::EOF() {
  return getToken(st_grammarParser::EOF, 0);
}

st_grammarParser::VarBlockContext* st_grammarParser::ProgramContext::varBlock() {
  return getRuleContext<st_grammarParser::VarBlockContext>(0);
}

std::vector<st_grammarParser::StatementContext *> st_grammarParser::ProgramContext::statement() {
  return getRuleContexts<st_grammarParser::StatementContext>();
}

st_grammarParser::StatementContext* st_grammarParser::ProgramContext::statement(size_t i) {
  return getRuleContext<st_grammarParser::StatementContext>(i);
}


size_t st_grammarParser::ProgramContext::getRuleIndex() const {
  return st_grammarParser::RuleProgram;
}

void st_grammarParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void st_grammarParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any st_grammarParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::ProgramContext* st_grammarParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, st_grammarParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(67);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == st_grammarParser::VAR) {
      setState(66);
      varBlock();
    }
    setState(72);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 288230393327531041) != 0)) {
      setState(69);
      statement();
      setState(74);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(75);
    match(st_grammarParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarBlockContext ------------------------------------------------------------------

st_grammarParser::VarBlockContext::VarBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::VarBlockContext::VAR() {
  return getToken(st_grammarParser::VAR, 0);
}

tree::TerminalNode* st_grammarParser::VarBlockContext::END_VAR() {
  return getToken(st_grammarParser::END_VAR, 0);
}

std::vector<st_grammarParser::VariableDeclarationContext *> st_grammarParser::VarBlockContext::variableDeclaration() {
  return getRuleContexts<st_grammarParser::VariableDeclarationContext>();
}

st_grammarParser::VariableDeclarationContext* st_grammarParser::VarBlockContext::variableDeclaration(size_t i) {
  return getRuleContext<st_grammarParser::VariableDeclarationContext>(i);
}


size_t st_grammarParser::VarBlockContext::getRuleIndex() const {
  return st_grammarParser::RuleVarBlock;
}

void st_grammarParser::VarBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarBlock(this);
}

void st_grammarParser::VarBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarBlock(this);
}


std::any st_grammarParser::VarBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitVarBlock(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::VarBlockContext* st_grammarParser::varBlock() {
  VarBlockContext *_localctx = _tracker.createInstance<VarBlockContext>(_ctx, getState());
  enterRule(_localctx, 2, st_grammarParser::RuleVarBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    match(st_grammarParser::VAR);
    setState(79); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(78);
      variableDeclaration();
      setState(81); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == st_grammarParser::ID);
    setState(83);
    match(st_grammarParser::END_VAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

st_grammarParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::VariableDeclarationContext::ID() {
  return getToken(st_grammarParser::ID, 0);
}

tree::TerminalNode* st_grammarParser::VariableDeclarationContext::COLON() {
  return getToken(st_grammarParser::COLON, 0);
}

st_grammarParser::TypeSpecContext* st_grammarParser::VariableDeclarationContext::typeSpec() {
  return getRuleContext<st_grammarParser::TypeSpecContext>(0);
}

tree::TerminalNode* st_grammarParser::VariableDeclarationContext::ASSIGN() {
  return getToken(st_grammarParser::ASSIGN, 0);
}

st_grammarParser::ExpressionContext* st_grammarParser::VariableDeclarationContext::expression() {
  return getRuleContext<st_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* st_grammarParser::VariableDeclarationContext::SEMI() {
  return getToken(st_grammarParser::SEMI, 0);
}


size_t st_grammarParser::VariableDeclarationContext::getRuleIndex() const {
  return st_grammarParser::RuleVariableDeclaration;
}

void st_grammarParser::VariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclaration(this);
}

void st_grammarParser::VariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclaration(this);
}


std::any st_grammarParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::VariableDeclarationContext* st_grammarParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, st_grammarParser::RuleVariableDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    match(st_grammarParser::ID);
    setState(86);
    match(st_grammarParser::COLON);
    setState(87);
    typeSpec();
    setState(90);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == st_grammarParser::ASSIGN) {
      setState(88);
      match(st_grammarParser::ASSIGN);
      setState(89);
      expression();
    }
    setState(93);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == st_grammarParser::SEMI) {
      setState(92);
      match(st_grammarParser::SEMI);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSpecContext ------------------------------------------------------------------

st_grammarParser::TypeSpecContext::TypeSpecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

st_grammarParser::ElementaryTypeContext* st_grammarParser::TypeSpecContext::elementaryType() {
  return getRuleContext<st_grammarParser::ElementaryTypeContext>(0);
}

st_grammarParser::ArrayTypeContext* st_grammarParser::TypeSpecContext::arrayType() {
  return getRuleContext<st_grammarParser::ArrayTypeContext>(0);
}


size_t st_grammarParser::TypeSpecContext::getRuleIndex() const {
  return st_grammarParser::RuleTypeSpec;
}

void st_grammarParser::TypeSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSpec(this);
}

void st_grammarParser::TypeSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSpec(this);
}


std::any st_grammarParser::TypeSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitTypeSpec(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::TypeSpecContext* st_grammarParser::typeSpec() {
  TypeSpecContext *_localctx = _tracker.createInstance<TypeSpecContext>(_ctx, getState());
  enterRule(_localctx, 6, st_grammarParser::RuleTypeSpec);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(97);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case st_grammarParser::BOOL:
      case st_grammarParser::INT:
      case st_grammarParser::REAL:
      case st_grammarParser::STRING:
      case st_grammarParser::TIME: {
        enterOuterAlt(_localctx, 1);
        setState(95);
        elementaryType();
        break;
      }

      case st_grammarParser::ARRAY: {
        enterOuterAlt(_localctx, 2);
        setState(96);
        arrayType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementaryTypeContext ------------------------------------------------------------------

st_grammarParser::ElementaryTypeContext::ElementaryTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::ElementaryTypeContext::BOOL() {
  return getToken(st_grammarParser::BOOL, 0);
}

tree::TerminalNode* st_grammarParser::ElementaryTypeContext::INT() {
  return getToken(st_grammarParser::INT, 0);
}

tree::TerminalNode* st_grammarParser::ElementaryTypeContext::REAL() {
  return getToken(st_grammarParser::REAL, 0);
}

tree::TerminalNode* st_grammarParser::ElementaryTypeContext::STRING() {
  return getToken(st_grammarParser::STRING, 0);
}

tree::TerminalNode* st_grammarParser::ElementaryTypeContext::TIME() {
  return getToken(st_grammarParser::TIME, 0);
}


size_t st_grammarParser::ElementaryTypeContext::getRuleIndex() const {
  return st_grammarParser::RuleElementaryType;
}

void st_grammarParser::ElementaryTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementaryType(this);
}

void st_grammarParser::ElementaryTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementaryType(this);
}


std::any st_grammarParser::ElementaryTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitElementaryType(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::ElementaryTypeContext* st_grammarParser::elementaryType() {
  ElementaryTypeContext *_localctx = _tracker.createInstance<ElementaryTypeContext>(_ctx, getState());
  enterRule(_localctx, 8, st_grammarParser::RuleElementaryType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(99);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 248) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayTypeContext ------------------------------------------------------------------

st_grammarParser::ArrayTypeContext::ArrayTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::ArrayTypeContext::ARRAY() {
  return getToken(st_grammarParser::ARRAY, 0);
}

tree::TerminalNode* st_grammarParser::ArrayTypeContext::LBRACK() {
  return getToken(st_grammarParser::LBRACK, 0);
}

std::vector<st_grammarParser::DimensionRangeContext *> st_grammarParser::ArrayTypeContext::dimensionRange() {
  return getRuleContexts<st_grammarParser::DimensionRangeContext>();
}

st_grammarParser::DimensionRangeContext* st_grammarParser::ArrayTypeContext::dimensionRange(size_t i) {
  return getRuleContext<st_grammarParser::DimensionRangeContext>(i);
}

tree::TerminalNode* st_grammarParser::ArrayTypeContext::RBRACK() {
  return getToken(st_grammarParser::RBRACK, 0);
}

tree::TerminalNode* st_grammarParser::ArrayTypeContext::OF() {
  return getToken(st_grammarParser::OF, 0);
}

st_grammarParser::ElementaryTypeContext* st_grammarParser::ArrayTypeContext::elementaryType() {
  return getRuleContext<st_grammarParser::ElementaryTypeContext>(0);
}

std::vector<tree::TerminalNode *> st_grammarParser::ArrayTypeContext::COMMA() {
  return getTokens(st_grammarParser::COMMA);
}

tree::TerminalNode* st_grammarParser::ArrayTypeContext::COMMA(size_t i) {
  return getToken(st_grammarParser::COMMA, i);
}


size_t st_grammarParser::ArrayTypeContext::getRuleIndex() const {
  return st_grammarParser::RuleArrayType;
}

void st_grammarParser::ArrayTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayType(this);
}

void st_grammarParser::ArrayTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayType(this);
}


std::any st_grammarParser::ArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitArrayType(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::ArrayTypeContext* st_grammarParser::arrayType() {
  ArrayTypeContext *_localctx = _tracker.createInstance<ArrayTypeContext>(_ctx, getState());
  enterRule(_localctx, 10, st_grammarParser::RuleArrayType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    match(st_grammarParser::ARRAY);
    setState(102);
    match(st_grammarParser::LBRACK);
    setState(103);
    dimensionRange();
    setState(108);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == st_grammarParser::COMMA) {
      setState(104);
      match(st_grammarParser::COMMA);
      setState(105);
      dimensionRange();
      setState(110);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(111);
    match(st_grammarParser::RBRACK);
    setState(112);
    match(st_grammarParser::OF);
    setState(113);
    elementaryType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DimensionRangeContext ------------------------------------------------------------------

st_grammarParser::DimensionRangeContext::DimensionRangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<st_grammarParser::ExpressionContext *> st_grammarParser::DimensionRangeContext::expression() {
  return getRuleContexts<st_grammarParser::ExpressionContext>();
}

st_grammarParser::ExpressionContext* st_grammarParser::DimensionRangeContext::expression(size_t i) {
  return getRuleContext<st_grammarParser::ExpressionContext>(i);
}

tree::TerminalNode* st_grammarParser::DimensionRangeContext::DOTDOT() {
  return getToken(st_grammarParser::DOTDOT, 0);
}


size_t st_grammarParser::DimensionRangeContext::getRuleIndex() const {
  return st_grammarParser::RuleDimensionRange;
}

void st_grammarParser::DimensionRangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDimensionRange(this);
}

void st_grammarParser::DimensionRangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDimensionRange(this);
}


std::any st_grammarParser::DimensionRangeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitDimensionRange(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::DimensionRangeContext* st_grammarParser::dimensionRange() {
  DimensionRangeContext *_localctx = _tracker.createInstance<DimensionRangeContext>(_ctx, getState());
  enterRule(_localctx, 12, st_grammarParser::RuleDimensionRange);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    expression();
    setState(116);
    match(st_grammarParser::DOTDOT);
    setState(117);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

st_grammarParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

st_grammarParser::IfStatementContext* st_grammarParser::StatementContext::ifStatement() {
  return getRuleContext<st_grammarParser::IfStatementContext>(0);
}

st_grammarParser::ForStatementContext* st_grammarParser::StatementContext::forStatement() {
  return getRuleContext<st_grammarParser::ForStatementContext>(0);
}

st_grammarParser::WhileStatementContext* st_grammarParser::StatementContext::whileStatement() {
  return getRuleContext<st_grammarParser::WhileStatementContext>(0);
}

st_grammarParser::AssignmentContext* st_grammarParser::StatementContext::assignment() {
  return getRuleContext<st_grammarParser::AssignmentContext>(0);
}

st_grammarParser::FunctionCallContext* st_grammarParser::StatementContext::functionCall() {
  return getRuleContext<st_grammarParser::FunctionCallContext>(0);
}

st_grammarParser::ReturnStatementContext* st_grammarParser::StatementContext::returnStatement() {
  return getRuleContext<st_grammarParser::ReturnStatementContext>(0);
}

st_grammarParser::ExitStatementContext* st_grammarParser::StatementContext::exitStatement() {
  return getRuleContext<st_grammarParser::ExitStatementContext>(0);
}


size_t st_grammarParser::StatementContext::getRuleIndex() const {
  return st_grammarParser::RuleStatement;
}

void st_grammarParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void st_grammarParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any st_grammarParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::StatementContext* st_grammarParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 14, st_grammarParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(126);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(119);
      ifStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(120);
      forStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(121);
      whileStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(122);
      assignment();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(123);
      functionCall();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(124);
      returnStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(125);
      exitStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

st_grammarParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::IfStatementContext::IF() {
  return getToken(st_grammarParser::IF, 0);
}

std::vector<st_grammarParser::ExpressionContext *> st_grammarParser::IfStatementContext::expression() {
  return getRuleContexts<st_grammarParser::ExpressionContext>();
}

st_grammarParser::ExpressionContext* st_grammarParser::IfStatementContext::expression(size_t i) {
  return getRuleContext<st_grammarParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> st_grammarParser::IfStatementContext::THEN() {
  return getTokens(st_grammarParser::THEN);
}

tree::TerminalNode* st_grammarParser::IfStatementContext::THEN(size_t i) {
  return getToken(st_grammarParser::THEN, i);
}

std::vector<st_grammarParser::StatementListContext *> st_grammarParser::IfStatementContext::statementList() {
  return getRuleContexts<st_grammarParser::StatementListContext>();
}

st_grammarParser::StatementListContext* st_grammarParser::IfStatementContext::statementList(size_t i) {
  return getRuleContext<st_grammarParser::StatementListContext>(i);
}

tree::TerminalNode* st_grammarParser::IfStatementContext::END_IF() {
  return getToken(st_grammarParser::END_IF, 0);
}

std::vector<tree::TerminalNode *> st_grammarParser::IfStatementContext::ELSIF() {
  return getTokens(st_grammarParser::ELSIF);
}

tree::TerminalNode* st_grammarParser::IfStatementContext::ELSIF(size_t i) {
  return getToken(st_grammarParser::ELSIF, i);
}

tree::TerminalNode* st_grammarParser::IfStatementContext::ELSE() {
  return getToken(st_grammarParser::ELSE, 0);
}


size_t st_grammarParser::IfStatementContext::getRuleIndex() const {
  return st_grammarParser::RuleIfStatement;
}

void st_grammarParser::IfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatement(this);
}

void st_grammarParser::IfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatement(this);
}


std::any st_grammarParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::IfStatementContext* st_grammarParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 16, st_grammarParser::RuleIfStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(128);
    match(st_grammarParser::IF);
    setState(129);
    expression();
    setState(130);
    match(st_grammarParser::THEN);
    setState(131);
    statementList();
    setState(139);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == st_grammarParser::ELSIF) {
      setState(132);
      match(st_grammarParser::ELSIF);
      setState(133);
      expression();
      setState(134);
      match(st_grammarParser::THEN);
      setState(135);
      statementList();
      setState(141);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(144);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == st_grammarParser::ELSE) {
      setState(142);
      match(st_grammarParser::ELSE);
      setState(143);
      statementList();
    }
    setState(146);
    match(st_grammarParser::END_IF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementListContext ------------------------------------------------------------------

st_grammarParser::StatementListContext::StatementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<st_grammarParser::StatementContext *> st_grammarParser::StatementListContext::statement() {
  return getRuleContexts<st_grammarParser::StatementContext>();
}

st_grammarParser::StatementContext* st_grammarParser::StatementListContext::statement(size_t i) {
  return getRuleContext<st_grammarParser::StatementContext>(i);
}


size_t st_grammarParser::StatementListContext::getRuleIndex() const {
  return st_grammarParser::RuleStatementList;
}

void st_grammarParser::StatementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementList(this);
}

void st_grammarParser::StatementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementList(this);
}


std::any st_grammarParser::StatementListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitStatementList(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::StatementListContext* st_grammarParser::statementList() {
  StatementListContext *_localctx = _tracker.createInstance<StatementListContext>(_ctx, getState());
  enterRule(_localctx, 18, st_grammarParser::RuleStatementList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(151);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 288230393327531041) != 0)) {
      setState(148);
      statement();
      setState(153);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStatementContext ------------------------------------------------------------------

st_grammarParser::ForStatementContext::ForStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::ForStatementContext::FOR() {
  return getToken(st_grammarParser::FOR, 0);
}

tree::TerminalNode* st_grammarParser::ForStatementContext::ID() {
  return getToken(st_grammarParser::ID, 0);
}

tree::TerminalNode* st_grammarParser::ForStatementContext::ASSIGN() {
  return getToken(st_grammarParser::ASSIGN, 0);
}

std::vector<st_grammarParser::ExpressionContext *> st_grammarParser::ForStatementContext::expression() {
  return getRuleContexts<st_grammarParser::ExpressionContext>();
}

st_grammarParser::ExpressionContext* st_grammarParser::ForStatementContext::expression(size_t i) {
  return getRuleContext<st_grammarParser::ExpressionContext>(i);
}

tree::TerminalNode* st_grammarParser::ForStatementContext::TO() {
  return getToken(st_grammarParser::TO, 0);
}

tree::TerminalNode* st_grammarParser::ForStatementContext::DO() {
  return getToken(st_grammarParser::DO, 0);
}

tree::TerminalNode* st_grammarParser::ForStatementContext::END_FOR() {
  return getToken(st_grammarParser::END_FOR, 0);
}

tree::TerminalNode* st_grammarParser::ForStatementContext::BY() {
  return getToken(st_grammarParser::BY, 0);
}

std::vector<st_grammarParser::StatementContext *> st_grammarParser::ForStatementContext::statement() {
  return getRuleContexts<st_grammarParser::StatementContext>();
}

st_grammarParser::StatementContext* st_grammarParser::ForStatementContext::statement(size_t i) {
  return getRuleContext<st_grammarParser::StatementContext>(i);
}


size_t st_grammarParser::ForStatementContext::getRuleIndex() const {
  return st_grammarParser::RuleForStatement;
}

void st_grammarParser::ForStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForStatement(this);
}

void st_grammarParser::ForStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForStatement(this);
}


std::any st_grammarParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::ForStatementContext* st_grammarParser::forStatement() {
  ForStatementContext *_localctx = _tracker.createInstance<ForStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, st_grammarParser::RuleForStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(154);
    match(st_grammarParser::FOR);
    setState(155);
    match(st_grammarParser::ID);
    setState(156);
    match(st_grammarParser::ASSIGN);
    setState(157);
    expression();
    setState(158);
    match(st_grammarParser::TO);
    setState(159);
    expression();
    setState(162);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == st_grammarParser::BY) {
      setState(160);
      match(st_grammarParser::BY);
      setState(161);
      expression();
    }
    setState(164);
    match(st_grammarParser::DO);
    setState(168);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 288230393327531041) != 0)) {
      setState(165);
      statement();
      setState(170);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(171);
    match(st_grammarParser::END_FOR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatementContext ------------------------------------------------------------------

st_grammarParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::WhileStatementContext::WHILE() {
  return getToken(st_grammarParser::WHILE, 0);
}

st_grammarParser::ExpressionContext* st_grammarParser::WhileStatementContext::expression() {
  return getRuleContext<st_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* st_grammarParser::WhileStatementContext::DO() {
  return getToken(st_grammarParser::DO, 0);
}

tree::TerminalNode* st_grammarParser::WhileStatementContext::END_WHILE() {
  return getToken(st_grammarParser::END_WHILE, 0);
}

std::vector<st_grammarParser::StatementContext *> st_grammarParser::WhileStatementContext::statement() {
  return getRuleContexts<st_grammarParser::StatementContext>();
}

st_grammarParser::StatementContext* st_grammarParser::WhileStatementContext::statement(size_t i) {
  return getRuleContext<st_grammarParser::StatementContext>(i);
}


size_t st_grammarParser::WhileStatementContext::getRuleIndex() const {
  return st_grammarParser::RuleWhileStatement;
}

void st_grammarParser::WhileStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStatement(this);
}

void st_grammarParser::WhileStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStatement(this);
}


std::any st_grammarParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::WhileStatementContext* st_grammarParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 22, st_grammarParser::RuleWhileStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(173);
    match(st_grammarParser::WHILE);
    setState(174);
    expression();
    setState(175);
    match(st_grammarParser::DO);
    setState(179);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 288230393327531041) != 0)) {
      setState(176);
      statement();
      setState(181);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(182);
    match(st_grammarParser::END_WHILE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

st_grammarParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

st_grammarParser::VariableContext* st_grammarParser::AssignmentContext::variable() {
  return getRuleContext<st_grammarParser::VariableContext>(0);
}

tree::TerminalNode* st_grammarParser::AssignmentContext::ASSIGN() {
  return getToken(st_grammarParser::ASSIGN, 0);
}

st_grammarParser::ExpressionContext* st_grammarParser::AssignmentContext::expression() {
  return getRuleContext<st_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* st_grammarParser::AssignmentContext::SEMI() {
  return getToken(st_grammarParser::SEMI, 0);
}


size_t st_grammarParser::AssignmentContext::getRuleIndex() const {
  return st_grammarParser::RuleAssignment;
}

void st_grammarParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void st_grammarParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}


std::any st_grammarParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::AssignmentContext* st_grammarParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 24, st_grammarParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    variable();
    setState(185);
    match(st_grammarParser::ASSIGN);
    setState(186);
    expression();
    setState(187);
    match(st_grammarParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

st_grammarParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::ReturnStatementContext::RETURN() {
  return getToken(st_grammarParser::RETURN, 0);
}

tree::TerminalNode* st_grammarParser::ReturnStatementContext::SEMI() {
  return getToken(st_grammarParser::SEMI, 0);
}


size_t st_grammarParser::ReturnStatementContext::getRuleIndex() const {
  return st_grammarParser::RuleReturnStatement;
}

void st_grammarParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void st_grammarParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}


std::any st_grammarParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::ReturnStatementContext* st_grammarParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 26, st_grammarParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(189);
    match(st_grammarParser::RETURN);
    setState(190);
    match(st_grammarParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExitStatementContext ------------------------------------------------------------------

st_grammarParser::ExitStatementContext::ExitStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::ExitStatementContext::EXIT() {
  return getToken(st_grammarParser::EXIT, 0);
}

tree::TerminalNode* st_grammarParser::ExitStatementContext::SEMI() {
  return getToken(st_grammarParser::SEMI, 0);
}


size_t st_grammarParser::ExitStatementContext::getRuleIndex() const {
  return st_grammarParser::RuleExitStatement;
}

void st_grammarParser::ExitStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExitStatement(this);
}

void st_grammarParser::ExitStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExitStatement(this);
}


std::any st_grammarParser::ExitStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitExitStatement(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::ExitStatementContext* st_grammarParser::exitStatement() {
  ExitStatementContext *_localctx = _tracker.createInstance<ExitStatementContext>(_ctx, getState());
  enterRule(_localctx, 28, st_grammarParser::RuleExitStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(192);
    match(st_grammarParser::EXIT);
    setState(193);
    match(st_grammarParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListContext ------------------------------------------------------------------

st_grammarParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<st_grammarParser::ArgumentContext *> st_grammarParser::ArgumentListContext::argument() {
  return getRuleContexts<st_grammarParser::ArgumentContext>();
}

st_grammarParser::ArgumentContext* st_grammarParser::ArgumentListContext::argument(size_t i) {
  return getRuleContext<st_grammarParser::ArgumentContext>(i);
}

std::vector<tree::TerminalNode *> st_grammarParser::ArgumentListContext::COMMA() {
  return getTokens(st_grammarParser::COMMA);
}

tree::TerminalNode* st_grammarParser::ArgumentListContext::COMMA(size_t i) {
  return getToken(st_grammarParser::COMMA, i);
}


size_t st_grammarParser::ArgumentListContext::getRuleIndex() const {
  return st_grammarParser::RuleArgumentList;
}

void st_grammarParser::ArgumentListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentList(this);
}

void st_grammarParser::ArgumentListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentList(this);
}


std::any st_grammarParser::ArgumentListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitArgumentList(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::ArgumentListContext* st_grammarParser::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 30, st_grammarParser::RuleArgumentList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(195);
    argument();
    setState(200);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == st_grammarParser::COMMA) {
      setState(196);
      match(st_grammarParser::COMMA);
      setState(197);
      argument();
      setState(202);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentContext ------------------------------------------------------------------

st_grammarParser::ArgumentContext::ArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

st_grammarParser::ExpressionContext* st_grammarParser::ArgumentContext::expression() {
  return getRuleContext<st_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* st_grammarParser::ArgumentContext::ID() {
  return getToken(st_grammarParser::ID, 0);
}

tree::TerminalNode* st_grammarParser::ArgumentContext::ASSIGN() {
  return getToken(st_grammarParser::ASSIGN, 0);
}


size_t st_grammarParser::ArgumentContext::getRuleIndex() const {
  return st_grammarParser::RuleArgument;
}

void st_grammarParser::ArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgument(this);
}

void st_grammarParser::ArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgument(this);
}


std::any st_grammarParser::ArgumentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitArgument(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::ArgumentContext* st_grammarParser::argument() {
  ArgumentContext *_localctx = _tracker.createInstance<ArgumentContext>(_ctx, getState());
  enterRule(_localctx, 32, st_grammarParser::RuleArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(205);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(203);
      match(st_grammarParser::ID);
      setState(204);
      match(st_grammarParser::ASSIGN);
      break;
    }

    default:
      break;
    }
    setState(207);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

st_grammarParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

st_grammarParser::OrExpressionContext* st_grammarParser::ExpressionContext::orExpression() {
  return getRuleContext<st_grammarParser::OrExpressionContext>(0);
}


size_t st_grammarParser::ExpressionContext::getRuleIndex() const {
  return st_grammarParser::RuleExpression;
}

void st_grammarParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void st_grammarParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


std::any st_grammarParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::ExpressionContext* st_grammarParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 34, st_grammarParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    orExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OrExpressionContext ------------------------------------------------------------------

st_grammarParser::OrExpressionContext::OrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<st_grammarParser::AndExpressionContext *> st_grammarParser::OrExpressionContext::andExpression() {
  return getRuleContexts<st_grammarParser::AndExpressionContext>();
}

st_grammarParser::AndExpressionContext* st_grammarParser::OrExpressionContext::andExpression(size_t i) {
  return getRuleContext<st_grammarParser::AndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> st_grammarParser::OrExpressionContext::OR() {
  return getTokens(st_grammarParser::OR);
}

tree::TerminalNode* st_grammarParser::OrExpressionContext::OR(size_t i) {
  return getToken(st_grammarParser::OR, i);
}


size_t st_grammarParser::OrExpressionContext::getRuleIndex() const {
  return st_grammarParser::RuleOrExpression;
}

void st_grammarParser::OrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrExpression(this);
}

void st_grammarParser::OrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrExpression(this);
}


std::any st_grammarParser::OrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitOrExpression(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::OrExpressionContext* st_grammarParser::orExpression() {
  OrExpressionContext *_localctx = _tracker.createInstance<OrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 36, st_grammarParser::RuleOrExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(211);
    andExpression();
    setState(216);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(212);
        match(st_grammarParser::OR);
        setState(213);
        andExpression(); 
      }
      setState(218);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AndExpressionContext ------------------------------------------------------------------

st_grammarParser::AndExpressionContext::AndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<st_grammarParser::EqualityExpressionContext *> st_grammarParser::AndExpressionContext::equalityExpression() {
  return getRuleContexts<st_grammarParser::EqualityExpressionContext>();
}

st_grammarParser::EqualityExpressionContext* st_grammarParser::AndExpressionContext::equalityExpression(size_t i) {
  return getRuleContext<st_grammarParser::EqualityExpressionContext>(i);
}

std::vector<tree::TerminalNode *> st_grammarParser::AndExpressionContext::AND() {
  return getTokens(st_grammarParser::AND);
}

tree::TerminalNode* st_grammarParser::AndExpressionContext::AND(size_t i) {
  return getToken(st_grammarParser::AND, i);
}


size_t st_grammarParser::AndExpressionContext::getRuleIndex() const {
  return st_grammarParser::RuleAndExpression;
}

void st_grammarParser::AndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpression(this);
}

void st_grammarParser::AndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpression(this);
}


std::any st_grammarParser::AndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitAndExpression(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::AndExpressionContext* st_grammarParser::andExpression() {
  AndExpressionContext *_localctx = _tracker.createInstance<AndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 38, st_grammarParser::RuleAndExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(219);
    equalityExpression();
    setState(224);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(220);
        match(st_grammarParser::AND);
        setState(221);
        equalityExpression(); 
      }
      setState(226);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityExpressionContext ------------------------------------------------------------------

st_grammarParser::EqualityExpressionContext::EqualityExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<st_grammarParser::RelationalExpressionContext *> st_grammarParser::EqualityExpressionContext::relationalExpression() {
  return getRuleContexts<st_grammarParser::RelationalExpressionContext>();
}

st_grammarParser::RelationalExpressionContext* st_grammarParser::EqualityExpressionContext::relationalExpression(size_t i) {
  return getRuleContext<st_grammarParser::RelationalExpressionContext>(i);
}

std::vector<tree::TerminalNode *> st_grammarParser::EqualityExpressionContext::EQ() {
  return getTokens(st_grammarParser::EQ);
}

tree::TerminalNode* st_grammarParser::EqualityExpressionContext::EQ(size_t i) {
  return getToken(st_grammarParser::EQ, i);
}

std::vector<tree::TerminalNode *> st_grammarParser::EqualityExpressionContext::NEQ() {
  return getTokens(st_grammarParser::NEQ);
}

tree::TerminalNode* st_grammarParser::EqualityExpressionContext::NEQ(size_t i) {
  return getToken(st_grammarParser::NEQ, i);
}


size_t st_grammarParser::EqualityExpressionContext::getRuleIndex() const {
  return st_grammarParser::RuleEqualityExpression;
}

void st_grammarParser::EqualityExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpression(this);
}

void st_grammarParser::EqualityExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpression(this);
}


std::any st_grammarParser::EqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::EqualityExpressionContext* st_grammarParser::equalityExpression() {
  EqualityExpressionContext *_localctx = _tracker.createInstance<EqualityExpressionContext>(_ctx, getState());
  enterRule(_localctx, 40, st_grammarParser::RuleEqualityExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(227);
    relationalExpression();
    setState(232);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(228);
        _la = _input->LA(1);
        if (!(_la == st_grammarParser::EQ

        || _la == st_grammarParser::NEQ)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(229);
        relationalExpression(); 
      }
      setState(234);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

st_grammarParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<st_grammarParser::AdditiveExpressionContext *> st_grammarParser::RelationalExpressionContext::additiveExpression() {
  return getRuleContexts<st_grammarParser::AdditiveExpressionContext>();
}

st_grammarParser::AdditiveExpressionContext* st_grammarParser::RelationalExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<st_grammarParser::AdditiveExpressionContext>(i);
}

std::vector<tree::TerminalNode *> st_grammarParser::RelationalExpressionContext::LT() {
  return getTokens(st_grammarParser::LT);
}

tree::TerminalNode* st_grammarParser::RelationalExpressionContext::LT(size_t i) {
  return getToken(st_grammarParser::LT, i);
}

std::vector<tree::TerminalNode *> st_grammarParser::RelationalExpressionContext::LE() {
  return getTokens(st_grammarParser::LE);
}

tree::TerminalNode* st_grammarParser::RelationalExpressionContext::LE(size_t i) {
  return getToken(st_grammarParser::LE, i);
}

std::vector<tree::TerminalNode *> st_grammarParser::RelationalExpressionContext::GT() {
  return getTokens(st_grammarParser::GT);
}

tree::TerminalNode* st_grammarParser::RelationalExpressionContext::GT(size_t i) {
  return getToken(st_grammarParser::GT, i);
}

std::vector<tree::TerminalNode *> st_grammarParser::RelationalExpressionContext::GE() {
  return getTokens(st_grammarParser::GE);
}

tree::TerminalNode* st_grammarParser::RelationalExpressionContext::GE(size_t i) {
  return getToken(st_grammarParser::GE, i);
}


size_t st_grammarParser::RelationalExpressionContext::getRuleIndex() const {
  return st_grammarParser::RuleRelationalExpression;
}

void st_grammarParser::RelationalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpression(this);
}

void st_grammarParser::RelationalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpression(this);
}


std::any st_grammarParser::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::RelationalExpressionContext* st_grammarParser::relationalExpression() {
  RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 42, st_grammarParser::RuleRelationalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(235);
    additiveExpression();
    setState(240);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(236);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 33776997205278720) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(237);
        additiveExpression(); 
      }
      setState(242);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

st_grammarParser::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<st_grammarParser::MultiplicativeExpressionContext *> st_grammarParser::AdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContexts<st_grammarParser::MultiplicativeExpressionContext>();
}

st_grammarParser::MultiplicativeExpressionContext* st_grammarParser::AdditiveExpressionContext::multiplicativeExpression(size_t i) {
  return getRuleContext<st_grammarParser::MultiplicativeExpressionContext>(i);
}

std::vector<tree::TerminalNode *> st_grammarParser::AdditiveExpressionContext::ADD() {
  return getTokens(st_grammarParser::ADD);
}

tree::TerminalNode* st_grammarParser::AdditiveExpressionContext::ADD(size_t i) {
  return getToken(st_grammarParser::ADD, i);
}

std::vector<tree::TerminalNode *> st_grammarParser::AdditiveExpressionContext::SUB() {
  return getTokens(st_grammarParser::SUB);
}

tree::TerminalNode* st_grammarParser::AdditiveExpressionContext::SUB(size_t i) {
  return getToken(st_grammarParser::SUB, i);
}


size_t st_grammarParser::AdditiveExpressionContext::getRuleIndex() const {
  return st_grammarParser::RuleAdditiveExpression;
}

void st_grammarParser::AdditiveExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpression(this);
}

void st_grammarParser::AdditiveExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpression(this);
}


std::any st_grammarParser::AdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::AdditiveExpressionContext* st_grammarParser::additiveExpression() {
  AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, getState());
  enterRule(_localctx, 44, st_grammarParser::RuleAdditiveExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(243);
    multiplicativeExpression();
    setState(248);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(244);
        _la = _input->LA(1);
        if (!(_la == st_grammarParser::ADD

        || _la == st_grammarParser::SUB)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(245);
        multiplicativeExpression(); 
      }
      setState(250);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

st_grammarParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<st_grammarParser::UnaryExpressionContext *> st_grammarParser::MultiplicativeExpressionContext::unaryExpression() {
  return getRuleContexts<st_grammarParser::UnaryExpressionContext>();
}

st_grammarParser::UnaryExpressionContext* st_grammarParser::MultiplicativeExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<st_grammarParser::UnaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> st_grammarParser::MultiplicativeExpressionContext::MUL() {
  return getTokens(st_grammarParser::MUL);
}

tree::TerminalNode* st_grammarParser::MultiplicativeExpressionContext::MUL(size_t i) {
  return getToken(st_grammarParser::MUL, i);
}

std::vector<tree::TerminalNode *> st_grammarParser::MultiplicativeExpressionContext::DIV() {
  return getTokens(st_grammarParser::DIV);
}

tree::TerminalNode* st_grammarParser::MultiplicativeExpressionContext::DIV(size_t i) {
  return getToken(st_grammarParser::DIV, i);
}


size_t st_grammarParser::MultiplicativeExpressionContext::getRuleIndex() const {
  return st_grammarParser::RuleMultiplicativeExpression;
}

void st_grammarParser::MultiplicativeExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpression(this);
}

void st_grammarParser::MultiplicativeExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpression(this);
}


std::any st_grammarParser::MultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::MultiplicativeExpressionContext* st_grammarParser::multiplicativeExpression() {
  MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, getState());
  enterRule(_localctx, 46, st_grammarParser::RuleMultiplicativeExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(251);
    unaryExpression();
    setState(256);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(252);
        _la = _input->LA(1);
        if (!(_la == st_grammarParser::MUL

        || _la == st_grammarParser::DIV)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(253);
        unaryExpression(); 
      }
      setState(258);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

st_grammarParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

st_grammarParser::PrimaryExpressionContext* st_grammarParser::UnaryExpressionContext::primaryExpression() {
  return getRuleContext<st_grammarParser::PrimaryExpressionContext>(0);
}

tree::TerminalNode* st_grammarParser::UnaryExpressionContext::SUB() {
  return getToken(st_grammarParser::SUB, 0);
}

tree::TerminalNode* st_grammarParser::UnaryExpressionContext::NOT() {
  return getToken(st_grammarParser::NOT, 0);
}


size_t st_grammarParser::UnaryExpressionContext::getRuleIndex() const {
  return st_grammarParser::RuleUnaryExpression;
}

void st_grammarParser::UnaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpression(this);
}

void st_grammarParser::UnaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpression(this);
}


std::any st_grammarParser::UnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::UnaryExpressionContext* st_grammarParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 48, st_grammarParser::RuleUnaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(260);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == st_grammarParser::NOT

    || _la == st_grammarParser::SUB) {
      setState(259);
      _la = _input->LA(1);
      if (!(_la == st_grammarParser::NOT

      || _la == st_grammarParser::SUB)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(262);
    primaryExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

st_grammarParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::PrimaryExpressionContext::LPAREN() {
  return getToken(st_grammarParser::LPAREN, 0);
}

st_grammarParser::ExpressionContext* st_grammarParser::PrimaryExpressionContext::expression() {
  return getRuleContext<st_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* st_grammarParser::PrimaryExpressionContext::RPAREN() {
  return getToken(st_grammarParser::RPAREN, 0);
}

st_grammarParser::LiteralContext* st_grammarParser::PrimaryExpressionContext::literal() {
  return getRuleContext<st_grammarParser::LiteralContext>(0);
}

st_grammarParser::VariableContext* st_grammarParser::PrimaryExpressionContext::variable() {
  return getRuleContext<st_grammarParser::VariableContext>(0);
}

st_grammarParser::FunctionCallContext* st_grammarParser::PrimaryExpressionContext::functionCall() {
  return getRuleContext<st_grammarParser::FunctionCallContext>(0);
}


size_t st_grammarParser::PrimaryExpressionContext::getRuleIndex() const {
  return st_grammarParser::RulePrimaryExpression;
}

void st_grammarParser::PrimaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpression(this);
}

void st_grammarParser::PrimaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpression(this);
}


std::any st_grammarParser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::PrimaryExpressionContext* st_grammarParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 50, st_grammarParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(271);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(264);
      match(st_grammarParser::LPAREN);
      setState(265);
      expression();
      setState(266);
      match(st_grammarParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(268);
      literal();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(269);
      variable();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(270);
      functionCall();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

st_grammarParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::LiteralContext::INTEGER_LITERAL() {
  return getToken(st_grammarParser::INTEGER_LITERAL, 0);
}

tree::TerminalNode* st_grammarParser::LiteralContext::REAL_LITERAL() {
  return getToken(st_grammarParser::REAL_LITERAL, 0);
}

tree::TerminalNode* st_grammarParser::LiteralContext::BOOLEAN_LITERAL() {
  return getToken(st_grammarParser::BOOLEAN_LITERAL, 0);
}

tree::TerminalNode* st_grammarParser::LiteralContext::STRING_LITERAL() {
  return getToken(st_grammarParser::STRING_LITERAL, 0);
}


size_t st_grammarParser::LiteralContext::getRuleIndex() const {
  return st_grammarParser::RuleLiteral;
}

void st_grammarParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void st_grammarParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}


std::any st_grammarParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::LiteralContext* st_grammarParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 52, st_grammarParser::RuleLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(273);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 263882790666240) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

st_grammarParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::FunctionCallContext::ID() {
  return getToken(st_grammarParser::ID, 0);
}

tree::TerminalNode* st_grammarParser::FunctionCallContext::LPAREN() {
  return getToken(st_grammarParser::LPAREN, 0);
}

tree::TerminalNode* st_grammarParser::FunctionCallContext::RPAREN() {
  return getToken(st_grammarParser::RPAREN, 0);
}

std::vector<st_grammarParser::ExpressionContext *> st_grammarParser::FunctionCallContext::expression() {
  return getRuleContexts<st_grammarParser::ExpressionContext>();
}

st_grammarParser::ExpressionContext* st_grammarParser::FunctionCallContext::expression(size_t i) {
  return getRuleContext<st_grammarParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> st_grammarParser::FunctionCallContext::COMMA() {
  return getTokens(st_grammarParser::COMMA);
}

tree::TerminalNode* st_grammarParser::FunctionCallContext::COMMA(size_t i) {
  return getToken(st_grammarParser::COMMA, i);
}


size_t st_grammarParser::FunctionCallContext::getRuleIndex() const {
  return st_grammarParser::RuleFunctionCall;
}

void st_grammarParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void st_grammarParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}


std::any st_grammarParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::FunctionCallContext* st_grammarParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 54, st_grammarParser::RuleFunctionCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(275);
    match(st_grammarParser::ID);
    setState(276);
    match(st_grammarParser::LPAREN);
    setState(285);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 26) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 26)) & 4407714381763) != 0)) {
      setState(277);
      expression();
      setState(282);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == st_grammarParser::COMMA) {
        setState(278);
        match(st_grammarParser::COMMA);
        setState(279);
        expression();
        setState(284);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(287);
    match(st_grammarParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

st_grammarParser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> st_grammarParser::VariableContext::ID() {
  return getTokens(st_grammarParser::ID);
}

tree::TerminalNode* st_grammarParser::VariableContext::ID(size_t i) {
  return getToken(st_grammarParser::ID, i);
}

st_grammarParser::AbsoluteAddressBaseContext* st_grammarParser::VariableContext::absoluteAddressBase() {
  return getRuleContext<st_grammarParser::AbsoluteAddressBaseContext>(0);
}

st_grammarParser::DbVariableContext* st_grammarParser::VariableContext::dbVariable() {
  return getRuleContext<st_grammarParser::DbVariableContext>(0);
}

std::vector<tree::TerminalNode *> st_grammarParser::VariableContext::DOT() {
  return getTokens(st_grammarParser::DOT);
}

tree::TerminalNode* st_grammarParser::VariableContext::DOT(size_t i) {
  return getToken(st_grammarParser::DOT, i);
}

st_grammarParser::BitSpecifierContext* st_grammarParser::VariableContext::bitSpecifier() {
  return getRuleContext<st_grammarParser::BitSpecifierContext>(0);
}

std::vector<tree::TerminalNode *> st_grammarParser::VariableContext::LBRACK() {
  return getTokens(st_grammarParser::LBRACK);
}

tree::TerminalNode* st_grammarParser::VariableContext::LBRACK(size_t i) {
  return getToken(st_grammarParser::LBRACK, i);
}

std::vector<st_grammarParser::ExpressionContext *> st_grammarParser::VariableContext::expression() {
  return getRuleContexts<st_grammarParser::ExpressionContext>();
}

st_grammarParser::ExpressionContext* st_grammarParser::VariableContext::expression(size_t i) {
  return getRuleContext<st_grammarParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> st_grammarParser::VariableContext::RBRACK() {
  return getTokens(st_grammarParser::RBRACK);
}

tree::TerminalNode* st_grammarParser::VariableContext::RBRACK(size_t i) {
  return getToken(st_grammarParser::RBRACK, i);
}

std::vector<tree::TerminalNode *> st_grammarParser::VariableContext::COMMA() {
  return getTokens(st_grammarParser::COMMA);
}

tree::TerminalNode* st_grammarParser::VariableContext::COMMA(size_t i) {
  return getToken(st_grammarParser::COMMA, i);
}


size_t st_grammarParser::VariableContext::getRuleIndex() const {
  return st_grammarParser::RuleVariable;
}

void st_grammarParser::VariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable(this);
}

void st_grammarParser::VariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable(this);
}


std::any st_grammarParser::VariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitVariable(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::VariableContext* st_grammarParser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 56, st_grammarParser::RuleVariable);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(292);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case st_grammarParser::ID: {
        setState(289);
        match(st_grammarParser::ID);
        break;
      }

      case st_grammarParser::ABS_INPUT_BIT:
      case st_grammarParser::ABS_INPUT_BYTE:
      case st_grammarParser::ABS_INPUT_WORD:
      case st_grammarParser::ABS_INPUT_DWORD:
      case st_grammarParser::ABS_OUTPUT_BIT:
      case st_grammarParser::ABS_OUTPUT_BYTE:
      case st_grammarParser::ABS_OUTPUT_WORD:
      case st_grammarParser::ABS_OUTPUT_DWORD:
      case st_grammarParser::ABS_MEMORY_BIT:
      case st_grammarParser::ABS_MEMORY_BYTE:
      case st_grammarParser::ABS_MEMORY_WORD:
      case st_grammarParser::ABS_MEMORY_DWORD: {
        setState(290);
        absoluteAddressBase();
        break;
      }

      case st_grammarParser::DB_NUMBER: {
        setState(291);
        dbVariable();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(296);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      setState(294);
      match(st_grammarParser::DOT);
      setState(295);
      bitSpecifier();
      break;
    }

    default:
      break;
    }
    setState(302);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(298);
        match(st_grammarParser::DOT);
        setState(299);
        match(st_grammarParser::ID); 
      }
      setState(304);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    }
    setState(318);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(305);
        match(st_grammarParser::LBRACK);
        setState(306);
        expression();
        setState(311);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == st_grammarParser::COMMA) {
          setState(307);
          match(st_grammarParser::COMMA);
          setState(308);
          expression();
          setState(313);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(314);
        match(st_grammarParser::RBRACK); 
      }
      setState(320);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DbVariableContext ------------------------------------------------------------------

st_grammarParser::DbVariableContext::DbVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::DbVariableContext::DB_NUMBER() {
  return getToken(st_grammarParser::DB_NUMBER, 0);
}

tree::TerminalNode* st_grammarParser::DbVariableContext::DOT() {
  return getToken(st_grammarParser::DOT, 0);
}

st_grammarParser::DbAreaContext* st_grammarParser::DbVariableContext::dbArea() {
  return getRuleContext<st_grammarParser::DbAreaContext>(0);
}


size_t st_grammarParser::DbVariableContext::getRuleIndex() const {
  return st_grammarParser::RuleDbVariable;
}

void st_grammarParser::DbVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDbVariable(this);
}

void st_grammarParser::DbVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDbVariable(this);
}


std::any st_grammarParser::DbVariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitDbVariable(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::DbVariableContext* st_grammarParser::dbVariable() {
  DbVariableContext *_localctx = _tracker.createInstance<DbVariableContext>(_ctx, getState());
  enterRule(_localctx, 58, st_grammarParser::RuleDbVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(321);
    match(st_grammarParser::DB_NUMBER);
    setState(322);
    match(st_grammarParser::DOT);
    setState(323);
    dbArea();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DbAreaContext ------------------------------------------------------------------

st_grammarParser::DbAreaContext::DbAreaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::DbAreaContext::DB_BIT() {
  return getToken(st_grammarParser::DB_BIT, 0);
}

tree::TerminalNode* st_grammarParser::DbAreaContext::DB_BYTE() {
  return getToken(st_grammarParser::DB_BYTE, 0);
}

tree::TerminalNode* st_grammarParser::DbAreaContext::DB_WORD() {
  return getToken(st_grammarParser::DB_WORD, 0);
}

tree::TerminalNode* st_grammarParser::DbAreaContext::DB_DWORD() {
  return getToken(st_grammarParser::DB_DWORD, 0);
}


size_t st_grammarParser::DbAreaContext::getRuleIndex() const {
  return st_grammarParser::RuleDbArea;
}

void st_grammarParser::DbAreaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDbArea(this);
}

void st_grammarParser::DbAreaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDbArea(this);
}


std::any st_grammarParser::DbAreaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitDbArea(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::DbAreaContext* st_grammarParser::dbArea() {
  DbAreaContext *_localctx = _tracker.createInstance<DbAreaContext>(_ctx, getState());
  enterRule(_localctx, 60, st_grammarParser::RuleDbArea);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(325);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4026531840) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AbsoluteAddressBaseContext ------------------------------------------------------------------

st_grammarParser::AbsoluteAddressBaseContext::AbsoluteAddressBaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* st_grammarParser::AbsoluteAddressBaseContext::ABS_INPUT_BIT() {
  return getToken(st_grammarParser::ABS_INPUT_BIT, 0);
}

tree::TerminalNode* st_grammarParser::AbsoluteAddressBaseContext::ABS_INPUT_BYTE() {
  return getToken(st_grammarParser::ABS_INPUT_BYTE, 0);
}

tree::TerminalNode* st_grammarParser::AbsoluteAddressBaseContext::ABS_INPUT_WORD() {
  return getToken(st_grammarParser::ABS_INPUT_WORD, 0);
}

tree::TerminalNode* st_grammarParser::AbsoluteAddressBaseContext::ABS_INPUT_DWORD() {
  return getToken(st_grammarParser::ABS_INPUT_DWORD, 0);
}

tree::TerminalNode* st_grammarParser::AbsoluteAddressBaseContext::ABS_OUTPUT_BIT() {
  return getToken(st_grammarParser::ABS_OUTPUT_BIT, 0);
}

tree::TerminalNode* st_grammarParser::AbsoluteAddressBaseContext::ABS_OUTPUT_BYTE() {
  return getToken(st_grammarParser::ABS_OUTPUT_BYTE, 0);
}

tree::TerminalNode* st_grammarParser::AbsoluteAddressBaseContext::ABS_OUTPUT_WORD() {
  return getToken(st_grammarParser::ABS_OUTPUT_WORD, 0);
}

tree::TerminalNode* st_grammarParser::AbsoluteAddressBaseContext::ABS_OUTPUT_DWORD() {
  return getToken(st_grammarParser::ABS_OUTPUT_DWORD, 0);
}

tree::TerminalNode* st_grammarParser::AbsoluteAddressBaseContext::ABS_MEMORY_BIT() {
  return getToken(st_grammarParser::ABS_MEMORY_BIT, 0);
}

tree::TerminalNode* st_grammarParser::AbsoluteAddressBaseContext::ABS_MEMORY_BYTE() {
  return getToken(st_grammarParser::ABS_MEMORY_BYTE, 0);
}

tree::TerminalNode* st_grammarParser::AbsoluteAddressBaseContext::ABS_MEMORY_WORD() {
  return getToken(st_grammarParser::ABS_MEMORY_WORD, 0);
}

tree::TerminalNode* st_grammarParser::AbsoluteAddressBaseContext::ABS_MEMORY_DWORD() {
  return getToken(st_grammarParser::ABS_MEMORY_DWORD, 0);
}


size_t st_grammarParser::AbsoluteAddressBaseContext::getRuleIndex() const {
  return st_grammarParser::RuleAbsoluteAddressBase;
}

void st_grammarParser::AbsoluteAddressBaseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAbsoluteAddressBase(this);
}

void st_grammarParser::AbsoluteAddressBaseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAbsoluteAddressBase(this);
}


std::any st_grammarParser::AbsoluteAddressBaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitAbsoluteAddressBase(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::AbsoluteAddressBaseContext* st_grammarParser::absoluteAddressBase() {
  AbsoluteAddressBaseContext *_localctx = _tracker.createInstance<AbsoluteAddressBaseContext>(_ctx, getState());
  enterRule(_localctx, 62, st_grammarParser::RuleAbsoluteAddressBase);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(327);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17587891077120) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitSpecifierContext ------------------------------------------------------------------

st_grammarParser::BitSpecifierContext::BitSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

st_grammarParser::ExpressionContext* st_grammarParser::BitSpecifierContext::expression() {
  return getRuleContext<st_grammarParser::ExpressionContext>(0);
}


size_t st_grammarParser::BitSpecifierContext::getRuleIndex() const {
  return st_grammarParser::RuleBitSpecifier;
}

void st_grammarParser::BitSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitSpecifier(this);
}

void st_grammarParser::BitSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<st_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitSpecifier(this);
}


std::any st_grammarParser::BitSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<st_grammarVisitor*>(visitor))
    return parserVisitor->visitBitSpecifier(this);
  else
    return visitor->visitChildren(this);
}

st_grammarParser::BitSpecifierContext* st_grammarParser::bitSpecifier() {
  BitSpecifierContext *_localctx = _tracker.createInstance<BitSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 64, st_grammarParser::RuleBitSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(329);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void st_grammarParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  st_grammarParserInitialize();
#else
  ::antlr4::internal::call_once(st_grammarParserOnceFlag, st_grammarParserInitialize);
#endif
}
