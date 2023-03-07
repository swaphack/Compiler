#pragma once


#ifdef __cplusplus
extern "C" {
#endif

	//数据类型关键字（12个）
#define C_KEY_WORD_CHAR  "char"
#define C_KEY_WORD_DOUBLE "double"
#define C_KEY_WORD_ENUM "enum"
#define C_KEY_WORD_FLOAT "float"
#define C_KEY_WORD_INT "int"
#define C_KEY_WORD_LONG "long"
#define C_KEY_WORD_SHORT "short"
#define C_KEY_WORD_SIGNED "signed"
#define C_KEY_WORD_STRUCT "struct"
#define C_KEY_WORD_UNION "union"
#define C_KEY_WORD_UNSIGNED "unsigned"
#define C_KEY_WORD_VOID "void"

//控制语句关键字
#define C_KEY_WORD_FOR  "for"
#define C_KEY_WORD_DO "do"
#define C_KEY_WORD_WHILE "while"
#define C_KEY_WORD_BREAK "break"
#define C_KEY_WORD_CONTINUE "continue"

#define C_KEY_WORD_IF "if"
#define C_KEY_WORD_ELSE "else"
#define C_KEY_WORD_GOTO "goto"

#define C_KEY_WORD_SWITCH "switch"
#define C_KEY_WORD_CASE "case"
#define C_KEY_WORD_DEFAULT "default"
#define C_KEY_WORD_RETURN "return"

//存储类型关键字
#define C_KEY_WORD_AUTO "auto"
#define C_KEY_WORD_EXTERN "extern"
#define C_KEY_WORD_REGISTER "register"
#define C_KEY_WORD_STATIC "static"


//存储类型关键字
#define C_KEY_WORD_CONST "const"
#define C_KEY_WORD_SIZEOF "sizeof"
#define C_KEY_WORD_TYPEDEF "typedef"
#define C_KEY_WORD_VOLATILE "volatile"

// 预处理
#define C_PREPROCESS_DEFINE "#define"
#define C_PREPROCESS_STRING "#"
#define C_PREPROCESS_CONCATE "##"
#define C_PREPROCESS_ARGS "..."
#define C_PREPROCESS_VAR_ARGS "__VA_ARGS__"

#define C_PREPROCESS_UNDEF "#undef"

#define C_PREPROCESS_IFDEF "#ifdef"
#define C_PREPROCESS_ELSE "#else"
#define C_PREPROCESS_ENDIF "#endif"
#define C_PREPROCESS_IFNDEF "#ifndef"

#define C_PREPROCESS_IF "#if"
#define C_PREPROCESS_ELIF "#elif"


struct analysis_table;
void init_analysis_table_with_c(struct analysis_table* at_ptr);

#ifdef __cplusplus
}
#endif