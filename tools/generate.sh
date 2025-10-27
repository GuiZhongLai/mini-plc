#!/bin/bash
set -o errexit

# 获取脚本所在目录（即 tools/）
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# 基于 tools/ 的相对路径推导其他目录
PROJECT_ROOT="$SCRIPT_DIR/.."
ANTLR_JAR="$SCRIPT_DIR/antlr-4.13.1-complete.jar"
GRAMMAR_FILE="$PROJECT_ROOT/grammar/st_grammar.g4"
OUTPUT_DIR="$PROJECT_ROOT/generated"

# 确保输出目录存在
mkdir -p "$OUTPUT_DIR"

# 检查 ANTLR jar 是否存在
if [[ ! -f "$ANTLR_JAR" ]]; then
  echo "❌ 错误: 找不到 ANTLR JAR 文件: $ANTLR_JAR"
  exit 1
fi

# 检查语法文件是否存在
if [[ ! -f "$GRAMMAR_FILE" ]]; then
  echo "❌ 错误: 找不到语法文件: $GRAMMAR_FILE"
  exit 1
fi

# 执行 ANTLR 生成 C++ 代码
echo "🚀 正在生成 C++ 解析器..."
java -jar "$ANTLR_JAR" \
  -Dlanguage=Cpp \
  -listener \
  -visitor \
  -o "$OUTPUT_DIR" \
  -package antlrcpptest \
  "$GRAMMAR_FILE"

echo "✅ 成功！已生成到: $OUTPUT_DIR"
