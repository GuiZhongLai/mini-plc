#include <gtest/gtest.h>
#include <regex>
#include "../../core/memory/plc_memory.h"
#include "../../core/st_compiler/compiler.h"
#include "st_grammarLexer.h"
#include "st_grammarParser.h"
#include "antlr4-runtime.h"

class CompilerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        compiler = std::make_unique<Compiler>();
    }
    void TearDown() override
    {
        compiler.reset();
    }
    std::string compileSTProgram(const std::string &stCode)
    {
        std::stringstream inputStream(stCode);
        antlr4::ANTLRInputStream input(inputStream);
        st_grammarLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        st_grammarParser parser(&tokens);

        auto program = parser.program();
        return compiler->generateCode(program);
    }
    bool containsSubstring(const std::string &code, const std::string &substring)
    {
        return code.find(substring) != std::string::npos;
    }
    std::unique_ptr<Compiler> compiler;
};

// 基础功能测试
TEST_F(CompilerTest, BasicVariableDeclaration)
{
    std::string stCode = R"(
        VAR
            x : INT;
            y : BOOL;
            z : REAL;
        END_VAR
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "int x = 0;"));
    EXPECT_TRUE(containsSubstring(result, "bool y = false;"));
    EXPECT_TRUE(containsSubstring(result, "double z = 0.0;"));
    EXPECT_TRUE(containsSubstring(result, "#include \"firmware.h\""));
    EXPECT_TRUE(containsSubstring(result, "extern \"C\" void scan()"));
}
TEST_F(CompilerTest, ArrayDeclaration)
{
    std::string stCode = R"(
        VAR
            arr1 : ARRAY[1..10] OF INT;
            arr2 : ARRAY[0..5, 1..3] OF BOOL;
        END_VAR
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "std::vector<int> arr1"));
    EXPECT_TRUE(containsSubstring(result, "std::vector<bool> arr2"));
}
// 赋值语句测试
TEST_F(CompilerTest, BasicAssignment)
{
    std::string stCode = R"(
        VAR
            a : INT;
            b : INT;
        END_VAR
        a := 10;
        b := a + 5;
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "a = 10;"));
    EXPECT_TRUE(containsSubstring(result, "b = a + 5;"));
}
// 控制流测试
TEST_F(CompilerTest, IfStatement)
{
    std::string stCode = R"(
        VAR
            x : INT;
            y : INT;
        END_VAR
        IF x > 10 THEN
            y := 20;
        ELSIF x > 5 THEN
            y := 15;
        ELSE
            y := 10;
        END_IF
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "if (x > 10) {"));
    EXPECT_TRUE(containsSubstring(result, "} else if (x > 5) {"));
    EXPECT_TRUE(containsSubstring(result, "} else {"));
    EXPECT_TRUE(containsSubstring(result, "y = 20;"));
    EXPECT_TRUE(containsSubstring(result, "y = 15;"));
    EXPECT_TRUE(containsSubstring(result, "y = 10;"));
}
TEST_F(CompilerTest, ForLoop)
{
    std::string stCode = R"(
        VAR
            i : INT;
            sum : INT;
        END_VAR
        FOR i := 1 TO 10 DO
            sum := sum + i;
        END_FOR
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "for (int i = 1; i <= 10; i++)"));
    EXPECT_TRUE(containsSubstring(result, "sum = sum + i;"));
}
TEST_F(CompilerTest, WhileLoop)
{
    std::string stCode = R"(
        VAR
            x : INT;
        END_VAR
        WHILE x < 100 DO
            x := x + 1;
        END_WHILE
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "while (x < 100)"));
    EXPECT_TRUE(containsSubstring(result, "x = x + 1;"));
}
// 表达式测试
TEST_F(CompilerTest, ArithmeticExpressions)
{
    std::string stCode = R"(
        VAR
            a : INT;
            b : INT;
            c : INT;
        END_VAR
        a := (b + c) * 2 - 5 / 3;
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "a = (b + c) * 2 - 5 / 3;"));
}
TEST_F(CompilerTest, LogicalExpressions)
{
    std::string stCode = R"(
        VAR
            x : BOOL;
            y : BOOL;
            z : BOOL;
        END_VAR
        z := x AND y;
        z := x OR y;
        z := NOT x;
        z := (x = y);
        z := (x <> y);
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "z = x && y;"));
    EXPECT_TRUE(containsSubstring(result, "z = x || y;"));
    EXPECT_TRUE(containsSubstring(result, "z = !x;"));
    EXPECT_TRUE(containsSubstring(result, "z = (x == y);"));
    EXPECT_TRUE(containsSubstring(result, "z = (x != y);"));
}
// PLC地址测试
TEST_F(CompilerTest, PLCAbsoluteAddresses)
{
    std::string stCode = R"(
        %IX0.0 := TRUE;
        %QB4 := 100;
        %MW10 := %IW5 + 20;
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "writeBit(MemoryArea::INPUT, 0, 0, 0, true)"));
    EXPECT_TRUE(containsSubstring(result, "writeByte(MemoryArea::OUTPUT, 0, 4, 100)"));
    EXPECT_TRUE(containsSubstring(result, "writeWord(MemoryArea::MEMORY, 0, 10, readWord(MemoryArea::INPUT, 0, 5) + 20)"));
}
TEST_F(CompilerTest, PLCDataBlockAddresses)
{
    std::string stCode = R"(
        DB1.DBX0.1 := TRUE;
        DB2.DBB4 := 50;
        DB3.DBW10 := DB4.DBD20;
        DB3.DBX1.2 := DB3.DBX1.1;
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "writeBit(MemoryArea::DATA_BLOCK, 1, 0, 1, true)"));
    EXPECT_TRUE(containsSubstring(result, "writeByte(MemoryArea::DATA_BLOCK, 2, 4, 50)"));
    EXPECT_TRUE(containsSubstring(result, "writeWord(MemoryArea::DATA_BLOCK, 3, 10, readDWord(MemoryArea::DATA_BLOCK, 4, 20))"));
    EXPECT_TRUE(containsSubstring(result, "writeBit(MemoryArea::DATA_BLOCK, 3, 1, 2, readBit(MemoryArea::DATA_BLOCK, 3, 1, 1))"));
}
// 类型转换函数测试
TEST_F(CompilerTest, TypeConversionFunctions)
{
    std::string stCode = R"(
        VAR
            intVal : INT;
            realVal : REAL;
            boolVal : BOOL;
            strVal : STRING;
        END_VAR
        realVal := INT_TO_REAL(intVal);
        boolVal := INT_TO_BOOL(intVal);
        strVal := INT_TO_STRING(intVal);
        intVal := REAL_TO_INT(realVal);
        boolVal := REAL_TO_BOOL(realVal);
        strVal := REAL_TO_STRING(realVal);
        intVal := BOOL_TO_INT(boolVal);
        realVal := BOOL_TO_REAL(boolVal);
        strVal := BOOL_TO_STRING(boolVal);
        intVal := STRING_TO_INT(strVal);
        realVal := STRING_TO_REAL(strVal);
        boolVal := STRING_TO_BOOL(strVal);
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "static_cast<double>(intVal)"));
    EXPECT_TRUE(containsSubstring(result, "static_cast<bool>(intVal)"));
    EXPECT_TRUE(containsSubstring(result, "std::to_string(intVal)"));
    EXPECT_TRUE(containsSubstring(result, "static_cast<int>(realVal)"));
    EXPECT_TRUE(containsSubstring(result, "static_cast<bool>(realVal)"));
    EXPECT_TRUE(containsSubstring(result, "std::to_string(realVal)"));
    EXPECT_TRUE(containsSubstring(result, "static_cast<int>(boolVal)"));
    EXPECT_TRUE(containsSubstring(result, "static_cast<double>(boolVal)"));
    EXPECT_TRUE(containsSubstring(result, "boolVal ? \"TRUE\" : \"FALSE\""));
    EXPECT_TRUE(containsSubstring(result, "std::stoi(strVal)"));
    EXPECT_TRUE(containsSubstring(result, "std::stod(strVal)"));
    EXPECT_TRUE(containsSubstring(result, "strVal == \"TRUE\" || strVal == \"true\""));
}
// 字面量测试
TEST_F(CompilerTest, Literals)
{
    std::string stCode = R"(
        VAR
            intVal : INT;
            realVal : REAL;
            boolVal : BOOL;
            strVal : STRING;
        END_VAR
        intVal := 123;
        realVal := 3.14;
        boolVal := TRUE;
        strVal := 'Hello World';
        strVal := 'It''s a test';
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "intVal = 123;"));
    EXPECT_TRUE(containsSubstring(result, "realVal = 3.14;"));
    EXPECT_TRUE(containsSubstring(result, "boolVal = true;"));
    EXPECT_TRUE(containsSubstring(result, "strVal = \"Hello World\";"));
    EXPECT_TRUE(containsSubstring(result, "strVal = \"It's a test\";"));
}
// 数组索引测试
TEST_F(CompilerTest, ArrayIndexing)
{
    std::string stCode = R"(
        VAR
            arr : ARRAY[1..10] OF INT;
            i : INT;
        END_VAR
        i := 5;
        arr[i] := 100;
        arr[2] := arr[3] + arr[i];
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "arr[(i - 1) * 1] = 100;"));
    EXPECT_TRUE(containsSubstring(result, "arr[(2 - 1) * 1] = arr[(3 - 1) * 1] + arr[(i - 1) * 1];"));
}
// 控制语句测试
TEST_F(CompilerTest, ControlStatements)
{
    std::string stCode = R"(
        VAR
            i : INT;
        END_VAR
        FOR i := 1 TO 10 DO
            IF i = 5 THEN
                EXIT;
            END_IF
        END_FOR
        RETURN;
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "break;"));
    EXPECT_TRUE(containsSubstring(result, "return;"));
}
// 复杂表达式测试
TEST_F(CompilerTest, ComplexExpressions)
{
    std::string stCode = R"(
        VAR
            a : INT;
            b : INT;
            c : INT;
            d : INT;
            x : BOOL;
            y : BOOL;
            z : BOOL;
        END_VAR
        a := b + c * d - (a / b);
        x := (a > b) AND (c <= d) OR NOT y;
    )";
    std::string result = compileSTProgram(stCode);

    EXPECT_TRUE(containsSubstring(result, "a = b + c * d - (a / b);"));
    EXPECT_TRUE(containsSubstring(result, "x = (a > b) && (c <= d) || !y;"));
}
// 错误恢复测试
TEST_F(CompilerTest, EmptyProgram)
{
    std::string stCode = "";

    std::string result = compileSTProgram(stCode);

    // 应该生成基本的scan函数结构
    EXPECT_TRUE(containsSubstring(result, "extern \"C\" void scan()"));
    EXPECT_TRUE(containsSubstring(result, "#include \"firmware.h\""));
}
// 性能测试 - 生成大量代码
TEST_F(CompilerTest, LargeProgramGeneration)
{
    std::stringstream largeProgram;
    largeProgram << "VAR\n";

    // 生成100个变量
    for (int i = 0; i < 100; i++)
    {
        largeProgram << "    var" << i << " : INT;\n";
    }
    largeProgram << "END_VAR\n";

    // 生成一些操作
    for (int i = 0; i < 50; i++)
    {
        largeProgram << "var" << i << " := var" << (i + 1) << " + " << i << ";\n";
    }

    std::string result = compileSTProgram(largeProgram.str());

    // 验证基本结构正确
    EXPECT_TRUE(containsSubstring(result, "extern \"C\" void scan()"));
    EXPECT_TRUE(containsSubstring(result, "#include \"firmware.h\""));

    // 验证变量声明
    for (int i = 0; i < 100; i++)
    {
        EXPECT_TRUE(containsSubstring(result, "int var" + std::to_string(i)));
    }
}