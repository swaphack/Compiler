#pragma once


#ifdef __cplusplus
extern "C" {
#endif

#define STRING_HASH "#"
#define STRING_EMPTY " "

#define STRING_PERIOD "."
#define STRING_COMMA ","
#define STRING_SEMICOLON ";"

#define STRING_LEFT_PARENTHESES  "("
#define STRING_RIGHT_PARENTHESES  ")"

#define STRING_LEFT_BRACKETS  "["
#define STRING_RIGHT_BRACKETS  "]"

#define STRING_OPENING_BRACES  "{"
#define STRING_CLOSING_BRACES  "}"

#define STRING_MUL "*"
#define STRING_SUB "-"
#define STRING_ADD "+"
#define STRING_DIV "/"
#define STRING_ASSIGN "="

#define STRING_MUL_ASSIGN "*="
#define STRING_SUB_ASSIGN "-="
#define STRING_ADD_ASSIGN "+="
#define STRING_DIV_ASSIGN "/="

#define STRING_AUTO_ADD "++"
#define STRING_AUTO_SUB "--"

#define STRING_MOD "%"
#define STRING_NOT "!"

#define STRING_GREATER ">"
#define STRING_GEQUAL ">="

#define STRING_LESS "<"
#define STRING_LEQUAL "<="

#define STRING_EQUAL "=="
#define STRING_NOT_EQUAL "!="

#define STRING_QUESTION  "?"
#define STRING_QUESTION_CONDTION  ":"

#define STRING_AND  "&&"
#define STRING_OR  "||"

#define STRING_BIT_OR "|"
#define STRING_BIT_AND "&"
#define STRING_BIT_XOR "^"
#define STRING_BIT_COMPLEMENT "~"

#define STRING_BIT_OR_ASSIGN  "|="
#define STRING_BIT_AND_ASSIGN  "&="
#define STRING_BIT_XOR_ASSIGN  "^="
#define STRING_BIT_COMPLEMENT_ASSIGN  "~="

#define STRING_BIT_SHIFT_LEFT "<<"
#define STRING_BIT_SHIFT_RIGHT ">>"


#define STRING_STRUCT_PTR "->"

	// ������
#define IS_NUL_CHAR(C) (c == '\0')
// ���ַ�
#define IS_EMPTY_CHAR(C) (c == ' ')
// ����
#define IS_NUMBER_CHAR(c) ((c >= '0' && c <= '9') || c == '.')
// ��ĸ
#define IS_LETTER_CHAR(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
// ת���ַ�
#define IS_ESCAPE_CHAR(c) (c == '\r' || c == '\t' || c == '\v')
// ���з�
#define IS_LINE_BREAK_CHAR(c) (c == '\n')

// �ָ���
#define IS_DELIMITER_CHAR(c) (c == ',' || c == ';' || c == ':')
// ������
#define IS_OPERATOR_CHAR(c) (c == '*' || c == '-' || c == '+' || c == '/' || c == '=' || \
	c == '|' || c == '%' || c == '>' || c == '<' || c == '!' || c == '>' || c == '<' || \
	c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}' ||\
	c == '&' || c == '~' || c == '^' || c == ':' || c == '?')

// �������
#define IS_SPECIAL_CHAR(c) (c == '#' || c == '@' || c == '$' || c == '\\')

// �ַ������ַ���
#define IS_STRING_CHAR(c) (c == '\"' || c == '\'')

// ����
#define IS_VARIABLE_CHAR(c) ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c =='_')


#ifdef __cplusplus
}
#endif