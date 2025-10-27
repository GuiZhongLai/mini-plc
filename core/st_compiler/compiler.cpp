#include "compiler.h"
#include "plc_memory.h"

#include <regex>

Compiler::Compiler()
{
    code_.str("");
}

Compiler::~Compiler()
{
}

std::string Compiler::generateCode(st_grammarParser::ProgramContext *program)
{
    code_.str("");
    code_.clear(); // 清除 error state
    variableTypes_.clear();
    declaredVariables_.clear();
    indentLevel_ = 0;

    // ===== 生成头文件包含 =====
    code_ << "#include \"firmware.h\"\n\n";

    // ===== 生成 scan() 函数 =====
    code_ << "extern \"C\" void scan() {\n";
    increaseIndent();

    // 遍历语法树，生成变量声明和语句
    visitProgram(program);

    decreaseIndent();
    code_ << "}\n";

    return code_.str();
}

std::any Compiler::visitVarBlock(st_grammarParser::VarBlockContext *ctx)
{
    for (auto varDel : ctx->variableDeclaration())
    {
        visitVariableDeclaration(varDel);
    }
    return nullptr;
}

std::any Compiler::visitVariableDeclaration(st_grammarParser::VariableDeclarationContext *ctx)
{
    std::string varName = ctx->ID()->getText();
    std::string cppType;
    // 获取类型
    std::any typeResult = visitTypeSpec(ctx->typeSpec());
    if (typeResult.has_value())
    {
        cppType = std::any_cast<std::string>(typeResult);
    }
    else
    {
        cppType = "auto";
    }
    variableTypes_[varName] = cppType;

    // 处理数组
    if (ctx->typeSpec()->arrayType())
    {
        auto arrayType = ctx->typeSpec()->arrayType();
        ArrayInfo info;
        info.baseType = cppType;
        // 解析维度信息
        for (auto dimRange : arrayType->dimensionRange())
        {
            auto expressions = dimRange->expression();
            if (expressions.size() >= 2)
            {
                // 简化：假设是常量表达式
                int lower = 0, upper = 9; // 默认值
                try
                {
                    lower = std::stoi(expressions[0]->getText());
                    upper = std::stoi(expressions[1]->getText());
                }
                catch (...)
                {
                    // 如果不是数字，使用默认值
                }
                info.dimensions.push_back(ArrayDimension(lower, upper));
            }
        }
        arrayInfo_[varName] = info;
        // 修复：直接生成vector初始化，不要重复声明
        code_ << getIndent() << "std::vector<" << convertType(ctx->typeSpec()->arrayType()->elementaryType()->getText()) << "> " << varName;
        code_ << "(" << info.totalSize() << ", ";
        // 根据类型设置默认值
        std::string baseType = convertType(ctx->typeSpec()->arrayType()->elementaryType()->getText());
        if (baseType == "bool")
            code_ << "false";
        else if (baseType == "int" || baseType == "long")
            code_ << "0";
        else if (baseType == "double" || baseType == "float")
            code_ << "0.0";
        else if (baseType == "std::string")
            code_ << "\"\"";
        else
            code_ << "0";
        code_ << ")";
    }
    else
    {
        // 基本类型初始化
        code_ << getIndent() << cppType << " " << varName;
        if (cppType == "bool")
            code_ << " = false";
        else if (cppType == "int" || cppType == "long")
            code_ << " = 0";
        else if (cppType == "double" || cppType == "float")
            code_ << " = 0.0";
        else if (cppType == "std::string")
            code_ << " = \"\"";
    }
    code_ << ";\n";
    declaredVariables_.insert(varName);
    return varName;
}

std::any Compiler::visitTypeSpec(st_grammarParser::TypeSpecContext *ctx)
{
    if (ctx->elementaryType())
    {
        return visitElementaryType(ctx->elementaryType());
    }
    else if (ctx->arrayType())
    {
        return visitArrayType(ctx->arrayType());
    }
    return std::string("int"); // 默认类型
}

std::any Compiler::visitElementaryType(st_grammarParser::ElementaryTypeContext *ctx)
{
    std::string stType = ctx->getText();
    return std::any(convertType(stType));
}

std::any Compiler::visitArrayType(st_grammarParser::ArrayTypeContext *ctx)
{
    // 获取基础类型
    std::string baseType = std::any_cast<std::string>(visitElementaryType(ctx->elementaryType()));

    // 直接返回vector类型，大小计算在visitVariableDeclaration中进行
    std::string cppType = "std::vector<" + baseType + ">";

    return std::any(cppType);
}

std::any Compiler::visitProgram(st_grammarParser::ProgramContext *ctx)
{
    // 首先处理VAR块（如果有）
    if (ctx->varBlock())
    {
        visitVarBlock(ctx->varBlock());
        code_ << "\n"; // 在变量声明和语句之间添加空行
    }

    // 然后处理语句
    for (auto statement : ctx->statement())
    {
        visitStatement(statement);
    }
    return nullptr;
}

std::any Compiler::visitStatement(st_grammarParser::StatementContext *ctx)
{
    // 访问所有可能的语句类型
    if (ctx->ifStatement())
    {
        return visitIfStatement(ctx->ifStatement());
    }
    else if (ctx->forStatement())
    {
        return visitForStatement(ctx->forStatement());
    }
    else if (ctx->whileStatement())
    {
        return visitWhileStatement(ctx->whileStatement());
    }
    else if (ctx->assignment())
    {
        return visitAssignment(ctx->assignment());
    }
    else if (ctx->returnStatement())
    {
        return visitReturnStatement(ctx->returnStatement());
    }
    else if (ctx->exitStatement())
    {
        return visitExitStatement(ctx->exitStatement());
    }
    return nullptr;
}

std::any Compiler::visitStatementList(st_grammarParser::StatementListContext *ctx)
{
    for (auto statement : ctx->statement())
    {
        visitStatement(statement);
    }
    return nullptr;
}

std::any Compiler::visitIfStatement(st_grammarParser::IfStatementContext *ctx)
{
    code_ << getIndent() << "if (";
    visitExpression(ctx->expression(0));
    code_ << ") {\n";

    increaseIndent();
    visitStatementList(ctx->statementList(0));
    decreaseIndent();

    // 处理ELSIF分支
    for (size_t i = 1; i < ctx->expression().size(); i++)
    {
        code_ << getIndent() << "} else if (";
        visitExpression(ctx->expression(i));
        code_ << ") {\n";

        increaseIndent();
        visitStatementList(ctx->statementList(i));
        decreaseIndent();
    }

    // 处理ELSE分支
    if (ctx->ELSE())
    {
        code_ << getIndent() << "} else {\n";
        increaseIndent();
        visitStatementList(ctx->statementList().back());
        decreaseIndent();
    }

    code_ << getIndent() << "}\n";
    return nullptr;
}

std::any Compiler::visitForStatement(st_grammarParser::ForStatementContext *ctx)
{
    std::string loopVar = ctx->ID()->getText();
    code_ << getIndent() << "for (int " << loopVar << " = ";
    visitExpression(ctx->expression(0));
    code_ << "; " << loopVar << " <= ";
    visitExpression(ctx->expression(1));
    code_ << "; " << loopVar << "++) {\n";

    increaseIndent();
    for (auto statement : ctx->statement())
    {
        visitStatement(statement);
    }
    decreaseIndent();

    code_ << getIndent() << "}\n";
    return nullptr;
}

std::any Compiler::visitWhileStatement(st_grammarParser::WhileStatementContext *ctx)
{
    code_ << getIndent() << "while (";
    visitExpression(ctx->expression());
    code_ << ") {\n";

    increaseIndent();
    for (auto statement : ctx->statement())
    {
        visitStatement(statement);
    }
    decreaseIndent();

    code_ << getIndent() << "}\n";
    return nullptr;
}

std::any Compiler::visitAssignment(st_grammarParser::AssignmentContext *ctx)
{
    code_ << getIndent();

    auto lhsResult = visitVariable(ctx->variable());

    if (lhsResult.type() == typeid(PlcAddress))
    {
        PlcAddress addr = std::any_cast<PlcAddress>(lhsResult);

        // ====== 1. 根据宽度选择函数名 ======
        std::string funcName;
        switch (addr.width)
        {
        case DataWidth::BIT:
            funcName = "writeBit";
            break;
        case DataWidth::BYTE:
            funcName = "writeByte";
            break;
        case DataWidth::WORD:
            funcName = "writeWord";
            break;
        case DataWidth::DWORD:
            funcName = "writeDWord";
            break;
        default:
            funcName = "writeByte"; // fallback
            break;
        }

        // ====== 2. 生成函数调用 ======
        code_ << funcName << "("
              << "MemoryArea::" << areaToString(addr.area)
              << ", " << (addr.db_number >= 0 ? std::to_string(addr.db_number) : "0");

        // 偏移
        code_ << ", " << addr.offset;

        // 如果是 BIT，加 bit 参数
        if (addr.width == DataWidth::BIT)
        {
            code_ << ", " << addr.bit;
        }

        // 右值表达式
        code_ << ", ";
        visitExpression(ctx->expression());
        code_ << ");\n";
    }
    else
    {
        // 普通变量赋值
        code_ << " = ";
        visitExpression(ctx->expression());
        code_ << ";\n";
    }

    return nullptr;
}

std::any Compiler::visitReturnStatement(st_grammarParser::ReturnStatementContext *ctx)
{
    (void)ctx;
    code_ << getIndent() << "return;\n";
    return nullptr;
}

std::any Compiler::visitExitStatement(st_grammarParser::ExitStatementContext *ctx)
{
    (void)ctx;
    code_ << getIndent() << "break;\n";
    return nullptr;
}

std::any Compiler::visitExpression(st_grammarParser::ExpressionContext *ctx)
{
    return visitOrExpression(ctx->orExpression());
}

std::any Compiler::visitOrExpression(st_grammarParser::OrExpressionContext *ctx)
{
    visitAndExpression(ctx->andExpression(0));

    for (size_t i = 1; i < ctx->andExpression().size(); i++)
    {
        code_ << " " << convertOperator("OR") << " ";
        visitAndExpression(ctx->andExpression(i));
    }

    return nullptr;
}

std::any Compiler::visitAndExpression(st_grammarParser::AndExpressionContext *ctx)
{
    visitEqualityExpression(ctx->equalityExpression(0));

    for (size_t i = 1; i < ctx->equalityExpression().size(); i++)
    {
        code_ << " " << convertOperator("AND") << " ";
        visitEqualityExpression(ctx->equalityExpression(i));
    }

    return nullptr;
}

std::any Compiler::visitEqualityExpression(st_grammarParser::EqualityExpressionContext *ctx)
{
    visitRelationalExpression(ctx->relationalExpression(0));

    for (size_t i = 1; i < ctx->relationalExpression().size(); i++)
    {
        if (ctx->EQ(i - 1))
        {
            code_ << " " << convertOperator("=") << " ";
        }
        else if (ctx->NEQ(i - 1))
        {
            code_ << " " << convertOperator("<>") << " ";
        }
        visitRelationalExpression(ctx->relationalExpression(i));
    }
    return nullptr;
}

std::any Compiler::visitRelationalExpression(st_grammarParser::RelationalExpressionContext *ctx)
{
    visitAdditiveExpression(ctx->additiveExpression(0));

    for (size_t i = 1; i < ctx->additiveExpression().size(); i++)
    {
        auto op = ctx->children[2 * i - 1]->getText();
        code_ << " " << convertOperator(op) << " ";
        visitAdditiveExpression(ctx->additiveExpression(i));
    }

    return nullptr;
}

std::any Compiler::visitAdditiveExpression(st_grammarParser::AdditiveExpressionContext *ctx)
{
    visitMultiplicativeExpression(ctx->multiplicativeExpression(0));

    for (size_t i = 1; i < ctx->multiplicativeExpression().size(); i++)
    {
        auto op = ctx->children[2 * i - 1]->getText();
        code_ << " " << op << " ";
        visitMultiplicativeExpression(ctx->multiplicativeExpression(i));
    }

    return nullptr;
}

std::any Compiler::visitMultiplicativeExpression(st_grammarParser::MultiplicativeExpressionContext *ctx)
{
    visitUnaryExpression(ctx->unaryExpression(0));
    for (size_t i = 1; i < ctx->unaryExpression().size(); i++)
    {
        size_t opIndex = 2 * i - 1;

        if (opIndex < ctx->children.size())
        {
            auto op = ctx->children[opIndex]->getText();
            code_ << " " << op << " ";
            visitUnaryExpression(ctx->unaryExpression(i));
        }
    }
    return nullptr;
}

std::any Compiler::visitUnaryExpression(st_grammarParser::UnaryExpressionContext *ctx)
{
    if (ctx->SUB())
    {
        code_ << "-";
    }
    else if (ctx->NOT())
    {
        code_ << convertOperator("NOT");
    }

    visitPrimaryExpression(ctx->primaryExpression());
    return nullptr;
}

std::any Compiler::visitPrimaryExpression(st_grammarParser::PrimaryExpressionContext *ctx)
{
    if (ctx->expression())
    {
        code_ << "(";
        visitExpression(ctx->expression());
        code_ << ")";
    }
    else if (ctx->literal())
    {
        visitLiteral(ctx->literal());
    }
    else if (ctx->variable())
    {
        auto result = visitVariable(ctx->variable());
        if (result.has_value() && result.type() == typeid(PlcAddress))
        {
            PlcAddress addr = std::any_cast<PlcAddress>(result);

            // ====== 选择函数名 ======
            std::string funcName;
            switch (addr.width)
            {
            case DataWidth::BIT:
                funcName = "readBit";
                break;
            case DataWidth::BYTE:
                funcName = "readByte";
                break;
            case DataWidth::WORD:
                funcName = "readWord";
                break;
            case DataWidth::DWORD:
                funcName = "readDWord";
                break;
            default:
                funcName = "readByte"; // fallback
                break;
            }

            // ====== 生成调用 ======
            code_ << funcName << "(MemoryArea::" << areaToString(addr.area)
                  << ", " << (addr.db_number >= 0 ? std::to_string(addr.db_number) : "0")
                  << ", " << addr.offset;

            // BIT 需要 bit 参数
            if (addr.width == DataWidth::BIT)
            {
                code_ << ", " << addr.bit;
            }

            code_ << ")"; // 关闭函数调用
        }
        // 否则 visitVariable 已处理普通变量
    }
    else if (ctx->functionCall())
    {
        visitFunctionCall(ctx->functionCall());
    }
    return nullptr;
}

std::any Compiler::visitVariable(st_grammarParser::VariableContext *ctx)
{
    // === 情况1: 绝对地址 (%IX, %IB, %QX, %QB, %MX, %MB 等) ===
    if (ctx->absoluteAddressBase() != nullptr)
    {
        std::string text = ctx->absoluteAddressBase()->getText();
        std::regex absRegex(R"(^%([IQM])([XWB]?)(\d+)(?:\.(\d+))?$)");
        std::smatch matches;

        if (std::regex_match(text, matches, absRegex))
        {
            PlcAddress plcAddr{};
            std::string areaStr = matches[1].str();
            std::string typeStr = matches[2].str();
            int addr = std::stoi(matches[3].str());
            int bitPos = -1;
            if (matches[4].matched)
            {
                bitPos = std::stoi(matches[4].str());
            }

            // 设置区域
            if (areaStr == "I")
                plcAddr.area = MemoryArea::INPUT;
            else if (areaStr == "Q")
                plcAddr.area = MemoryArea::OUTPUT;
            else if (areaStr == "M")
                plcAddr.area = MemoryArea::MEMORY;
            else
                return std::any(); // 无效区域

            plcAddr.db_number = 0;
            plcAddr.offset = addr;

            // 设置宽度和位
            if (typeStr == "X" || bitPos != -1)
            {
                plcAddr.width = DataWidth::BIT;
                plcAddr.bit = (bitPos != -1) ? bitPos : 0;
            }
            else if (typeStr == "B" || typeStr.empty())
            {
                plcAddr.width = DataWidth::BYTE;
                plcAddr.bit = -1;
            }
            else if (typeStr == "W")
            {
                plcAddr.width = DataWidth::WORD;
                plcAddr.bit = -1;
            }
            else if (typeStr == "D")
            {
                plcAddr.width = DataWidth::DWORD;
                plcAddr.bit = -1;
            }
            else
            {
                plcAddr.width = DataWidth::BYTE;
                plcAddr.bit = -1;
            }

            return std::any(plcAddr);
        }
        else
        {
            std::cerr << "Invalid absolute address: " << text << std::endl;
            return std::any();
        }
    }

    // === 情况2: DB 变量 (DB1.DBB10, DB2.DBX3.5 等) ===
    if (ctx->dbVariable() != nullptr)
    {
        auto dbVar = ctx->dbVariable();
        std::string dbNumStr = dbVar->DB_NUMBER()->getText();
        std::regex dbRegex(R"(^DB(\d+)$)");
        std::smatch dbMatch;
        if (!std::regex_match(dbNumStr, dbMatch, dbRegex))
        {
            std::cerr << "Invalid DB number: " << dbNumStr << std::endl;
            return std::any();
        }
        int dbNum = std::stoi(dbMatch[1].str());

        std::string areaText = dbVar->dbArea()->getText();
        std::regex dbAreaRegex(R"(^DB([XBWD])(\d+)(?:\.(\d+))?$)");
        std::smatch areaMatch;

        if (std::regex_match(areaText, areaMatch, dbAreaRegex))
        {
            PlcAddress plcAddr{};
            plcAddr.area = MemoryArea::DATA_BLOCK;
            plcAddr.db_number = dbNum;

            std::string typeChar = areaMatch[1].str();
            int offset = std::stoi(areaMatch[2].str());
            int bitPos = -1;
            if (areaMatch[3].matched)
            {
                bitPos = std::stoi(areaMatch[3].str());
            }

            plcAddr.offset = offset;

            if (typeChar == "X" || bitPos != -1)
            {
                plcAddr.width = DataWidth::BIT;
                plcAddr.bit = (bitPos != -1) ? bitPos : 0;
            }
            else if (typeChar == "B")
            {
                plcAddr.width = DataWidth::BYTE;
                plcAddr.bit = -1;
            }
            else if (typeChar == "W")
            {
                plcAddr.width = DataWidth::WORD;
                plcAddr.bit = -1;
            }
            else if (typeChar == "D")
            {
                plcAddr.width = DataWidth::DWORD;
                plcAddr.bit = -1;
            }
            else
            {
                plcAddr.width = DataWidth::BYTE;
                plcAddr.bit = -1;
            }

            return std::any(plcAddr);
        }
        else
        {
            std::cerr << "Invalid DB area: " << areaText << std::endl;
            return std::any();
        }
    }

    // === 情况3: 普通变量 ===
    std::string varName = ctx->ID(0)->getText();
    code_ << varName;

    auto expressions = ctx->expression();

    // 数组处理逻辑
    if (!expressions.empty() && arrayInfo_.find(varName) != arrayInfo_.end())
    {
        auto &info = arrayInfo_[varName];
        if (expressions.size() == info.dimensions.size())
        {
            code_ << "[";
            for (size_t i = 0; i < expressions.size(); i++)
            {
                if (i > 0)
                    code_ << " + ";
                const auto &dim = info.dimensions[i];
                int stride = 1;
                for (size_t j = i + 1; j < info.dimensions.size(); j++)
                {
                    stride *= info.dimensions[j].size();
                }
                code_ << "(";
                visitExpression(expressions[i]);
                code_ << " - " << dim.lower << ") * " << stride;
            }
            code_ << "]";
        }
        else
        {
            for (auto expr : expressions)
            {
                code_ << "[";
                visitExpression(expr);
                code_ << "]";
            }
        }
    }
    else
    {
        for (auto expr : expressions)
        {
            code_ << "[";
            visitExpression(expr);
            code_ << "]";
        }
    }

    // 处理结构体成员等
    for (size_t i = 1; i < ctx->ID().size(); ++i)
    {
        code_ << "." << ctx->ID(i)->getText();
    }

    return std::any(varName);
}

std::any Compiler::visitLiteral(st_grammarParser::LiteralContext *ctx)
{
    if (ctx->INTEGER_LITERAL())
    {
        code_ << ctx->INTEGER_LITERAL()->getText();
    }
    else if (ctx->REAL_LITERAL())
    {
        code_ << ctx->REAL_LITERAL()->getText();
    }
    else if (ctx->BOOLEAN_LITERAL())
    {
        std::string boolVal = ctx->BOOLEAN_LITERAL()->getText();
        if (boolVal == "TRUE")
            code_ << "true";
        else
            code_ << "false";
    }
    else if (ctx->STRING_LITERAL())
    {
        // 处理ST字符串字面量（单引号）到C++字符串（双引号）的转换
        std::string stStr = ctx->STRING_LITERAL()->getText();
        if (stStr.length() >= 2 && stStr[0] == '\'' && stStr[stStr.length() - 1] == '\'')
        {
            std::string content = stStr.substr(1, stStr.length() - 2);
            // 处理ST中的双单引号转义
            size_t pos = 0;
            while ((pos = content.find("''", pos)) != std::string::npos)
            {
                content.replace(pos, 2, "'");
                pos += 1;
            }
            code_ << "\"" << content << "\"";
        }
        else
        {
            code_ << "\"\"";
        }
    }
    return nullptr;
}

std::any Compiler::visitFunctionCall(st_grammarParser::FunctionCallContext *ctx)
{
    // 直接获取函数名（第一个子节点就是 IDENTIFIER）
    auto funcName = ctx->getStart()->getText();

    // INT 转换
    if (funcName == "INT_TO_REAL")
    {
        if (ctx->expression().size() > 0)
        {
            code_ << "static_cast<double>(";
            visitExpression(ctx->expression(0));
            code_ << ")";
        }
    }
    else if (funcName == "INT_TO_BOOL")
    {
        if (ctx->expression().size() > 0)
        {
            code_ << "static_cast<bool>(";
            visitExpression(ctx->expression(0));
            code_ << ")";
        }
    }
    else if (funcName == "INT_TO_STRING")
    {
        if (ctx->expression().size() > 0)
        {
            code_ << "std::to_string(";
            visitExpression(ctx->expression(0));
            code_ << ")";
        }
    }

    // REAL 转换
    else if (funcName == "REAL_TO_INT")
    {
        if (ctx->expression().size() > 0)
        {
            code_ << "static_cast<int>(";
            visitExpression(ctx->expression(0));
            code_ << ")";
        }
    }
    else if (funcName == "REAL_TO_BOOL")
    {
        if (ctx->expression().size() > 0)
        {
            code_ << "static_cast<bool>(";
            visitExpression(ctx->expression(0));
            code_ << ")";
        }
    }
    else if (funcName == "REAL_TO_STRING")
    {
        if (ctx->expression().size() > 0)
        {
            code_ << "std::to_string(";
            visitExpression(ctx->expression(0));
            code_ << ")";
        }
    }

    // BOOL 转换
    else if (funcName == "BOOL_TO_INT")
    {
        if (ctx->expression().size() > 0)
        {
            code_ << "static_cast<int>(";
            visitExpression(ctx->expression(0));
            code_ << ")";
        }
    }
    else if (funcName == "BOOL_TO_REAL")
    {
        if (ctx->expression().size() > 0)
        {
            code_ << "static_cast<double>(";
            visitExpression(ctx->expression(0));
            code_ << ")";
        }
    }
    else if (funcName == "BOOL_TO_STRING")
    {
        if (ctx->expression().size() > 0)
        {
            code_ << "(";
            visitExpression(ctx->expression(0));
            code_ << " ? \"TRUE\" : \"FALSE\")";
        }
    }

    // STRING 转换
    else if (funcName == "STRING_TO_INT")
    {
        if (ctx->expression().size() > 0)
        {
            code_ << "std::stoi(";
            visitExpression(ctx->expression(0));
            code_ << ")";
        }
    }
    else if (funcName == "STRING_TO_REAL")
    {
        if (ctx->expression().size() > 0)
        {
            code_ << "std::stod(";
            visitExpression(ctx->expression(0));
            code_ << ")";
        }
    }
    else if (funcName == "STRING_TO_BOOL")
    {
        if (ctx->expression().size() > 0)
        {
            code_ << "(";
            visitExpression(ctx->expression(0));
            code_ << " == \"TRUE\" || ";
            visitExpression(ctx->expression(0));
            code_ << " == \"true\")";
        }
    }
    else
    {
        // 默认函数调用处理
        code_ << funcName << "(";
        for (size_t i = 0; i < ctx->expression().size(); i++)
        {
            if (i > 0)
                code_ << ", ";
            visitExpression(ctx->expression(i));
        }
        code_ << ")";
    }

    return nullptr;
}

std::string Compiler::getIndent()
{
    return std::string(indentLevel_ * 4, ' ');
}

void Compiler::increaseIndent()
{
    indentLevel_++;
}

void Compiler::decreaseIndent()
{
    if (indentLevel_ > 0)
    {
        indentLevel_--;
    }
}

std::string Compiler::convertOperator(const std::string &stOp)
{
    if (stOp == "=")
        return "==";
    if (stOp == "<>")
        return "!=";
    if (stOp == "AND")
        return "&&";
    if (stOp == "OR")
        return "||";
    if (stOp == "NOT")
        return "!";
    return stOp;
}

std::string Compiler::convertType(const std::string &stType)
{
    // 转换为大写进行比较
    std::string upperType = stType;
    std::transform(upperType.begin(), upperType.end(), upperType.begin(), ::toupper);

    static std::map<std::string, std::string> typeMap = {
        {"BOOL", "bool"},
        {"INT", "int"},
        {"REAL", "double"},
        {"STRING", "std::string"},
        {"TIME", "long"}};

    return typeMap.count(upperType) ? typeMap[upperType] : "auto";
}

std::string Compiler::areaToString(const int a)
{
    MemoryArea area = static_cast<MemoryArea>(a);
    switch (area)
    {
    case MemoryArea::INPUT:
        return "INPUT";
    case MemoryArea::OUTPUT:
        return "OUTPUT";
    case MemoryArea::MEMORY:
        return "MEMORY";
    case MemoryArea::DATA_BLOCK:
        return "DATA_BLOCK";
    default:
        return "MEMORY";
    }
}