grammar st_grammar;

program: (varBlock)? statement* EOF;

// VAR 块
varBlock: VAR variableDeclaration+ END_VAR;
variableDeclaration: ID ':' typeSpec (':=' expression)? (';')?;
typeSpec: elementaryType | arrayType;
elementaryType: 'BOOL' | 'INT' | 'REAL' | 'STRING' | 'TIME';
arrayType:
	'ARRAY' '[' dimensionRange (',' dimensionRange)* ']' 'OF' elementaryType;
dimensionRange: expression '..' expression;

// 语句
statement:
	ifStatement
	| forStatement
	| whileStatement
	| assignment
	| functionCall
	| returnStatement
	| exitStatement;

ifStatement:
	IF expression THEN statementList (
		ELSIF expression THEN statementList
	)* (ELSE statementList)? END_IF;
statementList: statement*;
forStatement:
	FOR ID ':=' expression TO expression (BY expression)? DO statement* END_FOR;
whileStatement: WHILE expression DO statement* END_WHILE;
assignment: variable ':=' expression ';';
returnStatement: RETURN ';';
exitStatement: EXIT ';';
argumentList: argument (',' argument)*;
argument: (ID ':=')? expression;

// 表达式
expression: orExpression;
orExpression: andExpression (OR andExpression)*;
andExpression: equalityExpression (AND equalityExpression)*;
equalityExpression:
	relationalExpression (('=' | '<>') relationalExpression)*;
relationalExpression:
	additiveExpression (
		('<' | '<=' | '>' | '>=') additiveExpression
	)*;
additiveExpression:
	multiplicativeExpression (
		('+' | '-') multiplicativeExpression
	)*;
multiplicativeExpression:
	unaryExpression (('*' | '/') unaryExpression)*;
unaryExpression: ('-' | NOT)? primaryExpression;
primaryExpression:
	'(' expression ')'
	| literal
	| variable
	| functionCall;

literal:
	INTEGER_LITERAL
	| REAL_LITERAL
	| BOOLEAN_LITERAL
	| STRING_LITERAL;
functionCall: ID '(' (expression (',' expression)*)? ')';

// ========== 变量语法：支持所有形式 ==========
variable:
	// 普通变量 或 绝对地址基础 或 DB变量
	(ID | absoluteAddressBase | dbVariable)
	// 可选：位访问 .bit（如 .5, .7）
	('.' bitSpecifier)?
	// 可选：结构体成员
	('.' ID)*
	// 可选：数组索引
	('[' expression (',' expression)* ']')*;

// DB变量：DB1.DBB10，支持后续加 .bit
dbVariable: DB_NUMBER '.' dbArea;

// DB 区域（不含位号）
dbArea: DB_BIT | DB_BYTE | DB_WORD | DB_DWORD;

// 绝对地址基础（不含 .bit）
absoluteAddressBase:
	ABS_INPUT_BIT
	| ABS_INPUT_BYTE
	| ABS_INPUT_WORD
	| ABS_INPUT_DWORD
	| ABS_OUTPUT_BIT
	| ABS_OUTPUT_BYTE
	| ABS_OUTPUT_WORD
	| ABS_OUTPUT_DWORD
	| ABS_MEMORY_BIT
	| ABS_MEMORY_BYTE
	| ABS_MEMORY_WORD
	| ABS_MEMORY_DWORD;

// 位号：支持常量或变量，如 .5, .i
bitSpecifier: expression;

// ========== 词法规则 ==========

// 关键字
VAR: 'VAR';
END_VAR: 'END_VAR';
BOOL: 'BOOL';
INT: 'INT';
REAL: 'REAL';
STRING: 'STRING';
TIME: 'TIME';
ARRAY: 'ARRAY';
OF: 'OF';
IF: 'IF';
THEN: 'THEN';
END_IF: 'END_IF';
ELSIF: 'ELSIF';
ELSE: 'ELSE';
FOR: 'FOR';
TO: 'TO';
BY: 'BY';
DO: 'DO';
END_FOR: 'END_FOR';
WHILE: 'WHILE';
END_WHILE: 'END_WHILE';
RETURN: 'RETURN';
EXIT: 'EXIT';
AND: 'AND';
OR: 'OR';
NOT: 'NOT';

// ========== 绝对地址与DB（必须在ID前）==========

// DB 块编号：DB1, DB2
DB_NUMBER: 'DB' [0-9]+;

// DB 区域
DB_BIT: 'DBX' [0-9]+ ('.' [0-9]+)?; // DB1.DBX10.1
DB_BYTE: 'DBB' [0-9]+; // DB2.DBB15
DB_WORD: 'DBW' [0-9]+; // DB3.DBW100
DB_DWORD: 'DBD' [0-9]+; // DB4.DBD20

// 输入
ABS_INPUT_BIT: '%IX' [0-9]+ ('.' [0-9]+)?; // %IX100
ABS_INPUT_BYTE: '%IB' [0-9]+; // %IB1
ABS_INPUT_WORD: '%IW' [0-9]+; // %IW10
ABS_INPUT_DWORD: '%ID' [0-9]+; // %ID132

// 输出
ABS_OUTPUT_BIT: '%QX' [0-9]+ ('.' [0-9]+)?;
ABS_OUTPUT_BYTE: '%QB' [0-9]+;
ABS_OUTPUT_WORD: '%QW' [0-9]+;
ABS_OUTPUT_DWORD: '%QD' [0-9]+;

// 内存 M
ABS_MEMORY_BIT: '%MX' [0-9]+ ('.' [0-9]+)?;
ABS_MEMORY_BYTE: '%MB' [0-9]+;
ABS_MEMORY_WORD: '%MW' [0-9]+;
ABS_MEMORY_DWORD: '%MD' [0-9]+;

// ========== 字面量 ==========
BOOLEAN_LITERAL: 'TRUE' | 'FALSE';
INTEGER_LITERAL: [0-9]+;
REAL_LITERAL: [0-9]* '.' [0-9]+ ( [eE] [+-]? [0-9]+)?;
STRING_LITERAL: '\'' ( ~['\r\n] | '\'\'')* '\'';

// ========== 操作符和标点 ==========
ASSIGN: ':=';
EQ: '=';
NEQ: '<>';
LT: '<';
LE: '<=';
GT: '>';
GE: '>=';
ADD: '+';
SUB: '-';
MUL: '*';
DIV: '/';

LPAREN: '(';
RPAREN: ')';
SEMI: ';';
COMMA: ',';
LBRACK: '[';
RBRACK: ']';
DOT: '.';
COLON: ':';
DOTDOT: '..';

// ========== 标识符（最后）==========
ID: [a-zA-Z_] [a-zA-Z_0-9]*;

// ========== 忽略内容 ==========
WS: [ \t\r\n]+ -> skip;
COMMENT: '(*' (COMMENT | .)*? '*)' -> skip;
LINE_COMMENT: '//' ~[\r\n]* -> skip;