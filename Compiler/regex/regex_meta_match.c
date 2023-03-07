#include "regex_meta_match.h"
#include "regex_meta.h"
#include "regex_pattern.h"
#include "regex_guts.h"

////////////////////////////////////////////////////////////////////////////////////
// ^ 从开始行开始匹配
bool regex_meta_match_start_with(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;
	bool ret = string_stream_equal_string(ss_ptr, meta_ptr->meta);
	if (!ret) return ret;

	string_stream_move_next(ss_ptr);
	ret = regex_guts_comp_step(tree_ptr, ss_ptr);
	if (!ret) return ret;

	return ret;
}
// $ 从末端开始匹配
bool regex_meta_match_end_with(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;
	bool ret = string_stream_equal_string(ss_ptr, meta_ptr->meta);
	return ret;
}
// | 或运算符，匹配符号前或后的字符
bool regex_meta_match_or(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;
	bool ret = string_stream_equal_string(ss_ptr, meta_ptr->meta);
	return ret;
}

// \ 转义字符，用于匹配一些保留的字符 [ ] ( ) { } . * + ? ^ $ \ |
bool regex_meta_match_escape(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;
	bool ret = string_stream_equal_string(ss_ptr, meta_ptr->meta);
	if (!ret) return ret;

	string_stream_move_next(ss_ptr);
	char c = string_stream_char_at_cursor(ss_ptr);
	if (REGEX_IS_META_CHAR(c))
		return true;
	else
	{// 转义字符, \s \w \un
		if (c == 'b' || c == 'B' || c == 'd' || c == 'D' || c == 'f' || c == 'n'
			|| c == 'r' || c == 's' || c == 'S' || c == 't' || c == 'v'
			|| c == 'w' || c == 'W' || c == '<' || c == '>' || c == '(' || c == ')'
			|| c == '|')
		{
			return true;
		}

		do
		{
			if (c == 'c')
			{
				char f1 = string_stream_char_at(ss_ptr, ss_ptr->cursor + 1);
				if (f1 == 0) return false;
				if (REGEX_IS_LETTER(f1))
				{
					string_stream_move(ss_ptr, 1);
				}
			}
			else if (c == 'x')
			{// 16 进制转义值 匹配单个 Unicode 字素
				char f1 = string_stream_char_at(ss_ptr, ss_ptr->cursor + 1);
				char f2 = string_stream_char_at(ss_ptr, ss_ptr->cursor + 2);
				if (REGEX_IS_HEXADECIMAL(f1) && REGEX_IS_HEXADECIMAL(f2))
				{
					string_stream_move(ss_ptr, 2);
				}
			}
			else if (c == 'u')
			{// Unicode字符
				char f1 = string_stream_char_at(ss_ptr, ss_ptr->cursor + 1);
				char f2 = string_stream_char_at(ss_ptr, ss_ptr->cursor + 2);
				char f3 = string_stream_char_at(ss_ptr, ss_ptr->cursor + 3);
				char f4 = string_stream_char_at(ss_ptr, ss_ptr->cursor + 4);
				if (f1 == 0 || f2 == 0 || f3 == 0 || f4 == 0) return false;

				if (REGEX_IS_HEXADECIMAL(f1) && REGEX_IS_HEXADECIMAL(f2) && REGEX_IS_HEXADECIMAL(f3) && REGEX_IS_HEXADECIMAL(f4))
				{
					string_stream_move(ss_ptr, 4);
				}
			}
			else if (REGEX_IS_OCTAL(c))
			{
				char f1 = string_stream_char_at(ss_ptr, ss_ptr->cursor + 1);
				char f2 = string_stream_char_at(ss_ptr, ss_ptr->cursor + 2);

				if (REGEX_IS_OCTAL(f1) && REGEX_IS_OCTAL(f2))
				{
					string_stream_move(ss_ptr, 2);
				}
				else if (REGEX_IS_OCTAL(f1))
				{
					string_stream_move(ss_ptr, 1);
				}
			}
			else if (REGEX_IS_NUMBER(c))
			{
				int offset = 0;
				while (true)
				{
					char f = string_stream_char_at(ss_ptr, ss_ptr->cursor + offset + 1);
					if (!REGEX_IS_NUMBER(c))
					{
						break;
					}
					offset++;
				}
				string_stream_move(ss_ptr, offset);
			}
		} while (0);
	}

	return true;
}
// (abc) 字符集，匹配与abc完全相等的字符
bool regex_meta_match_equal_charset(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;

	bool ret = string_stream_equal_string(ss_ptr, meta_ptr->start_meta);
	if (!ret) return ret;

	string_stream_move_next(ss_ptr);
	while (true)
	{
		ret = regex_guts_comp_step(tree_ptr, ss_ptr);
		if (!ret) return ret;

		string_stream_move_next(ss_ptr);
		ret = string_stream_equal_string(ss_ptr, meta_ptr->end_meta);
		if (ret) break;

		if (string_stream_is_over(ss_ptr)) return false;
	}

	return ret;
}
// {n,m}匹配num个大括号之前的字符或字符集 (n <=num<=m)
bool regex_meta_match_range_count(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;
	bool ret = string_stream_equal_string(ss_ptr, meta_ptr->start_meta);
	if (!ret) return ret;

	string_stream_move_next(ss_ptr);
	ret = regex_guts_comp_step(tree_ptr, ss_ptr);
	if (!ret) return ret;

	string_stream_move_next(ss_ptr);
	ret = string_stream_equal_string(ss_ptr, meta_ptr->end_meta);
	if (!ret) return ret;
	return ret;
}
// + 匹配>=1个重复+号之前的字符
bool regex_meta_match_gequal_1_count(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;
	bool ret = string_stream_equal_string(ss_ptr, meta_ptr->meta);
	return ret;
}
// * 匹配>=0个重复*号之前的字符
bool regex_meta_match_gequal_0_count(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;
	bool ret = string_stream_equal_string(ss_ptr, meta_ptr->meta);
	return ret;
}
// [] 字符种类。匹配方括号内的任意字符
bool regex_meta_match_in_charset(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;
	bool ret = string_stream_equal_string(ss_ptr, meta_ptr->start_meta);
	if (!ret) return ret;

	char c = string_stream_char_at(ss_ptr, ss_ptr->cursor + 1);
	if (c == '^') return false;

	string_stream_move_next(ss_ptr);
	while (true)
	{
		ret = regex_guts_comp_step(tree_ptr, ss_ptr);
		if (!ret) return ret;

		string_stream_move_next(ss_ptr);
		ret = string_stream_equal_string(ss_ptr, meta_ptr->end_meta);
		if (ret) break;

		if (string_stream_is_over(ss_ptr)) return false;
	}

	return ret;
}
// [^] 否定字符种类。匹配除了方括号内的任意字符
bool regex_meta_match_notin_charset(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;
	bool ret = string_stream_equal_string(ss_ptr, meta_ptr->start_meta);
	if (!ret) return ret;

	string_stream_move_next(ss_ptr);
	while (true)
	{
		ret = regex_guts_comp_step(tree_ptr, ss_ptr);
		if (!ret) return ret;

		string_stream_move_next(ss_ptr);
		ret = string_stream_equal_string(ss_ptr, meta_ptr->end_meta);
		if (ret) break;

		if (string_stream_is_over(ss_ptr)) return false;
	}

	return ret;
}
// ? 标记?之前的字符为可选
bool regex_meta_match_optional(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;
	bool ret = string_stream_equal_string(ss_ptr, meta_ptr->meta);
	return ret;
}
// . 句号匹配任意当个字符，除了换行符
bool regex_meta_match_not_line_break(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;
	bool ret = string_stream_equal_string(ss_ptr, meta_ptr->meta);
	return ret;
}

bool regex_meta_match_letter_charset_lower(struct string_stream* ss_ptr, regex_meta* meta_ptr, regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;

	char c = string_stream_char_at_cursor(ss_ptr);
	if (c >= 'a' && c <= 'z') return true;
	return false;
}

bool regex_meta_match_letter_charset_upper(struct string_stream* ss_ptr, regex_meta* meta_ptr, regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;

	char c = string_stream_char_at_cursor(ss_ptr);
	if ((c >= 'A' && c <= 'Z')) return true;
	return false;
}

bool regex_meta_match_number_charset(struct string_stream* ss_ptr, regex_meta* meta_ptr, regex_pattern_tree* tree_ptr)
{
	char c = string_stream_char_at_cursor(ss_ptr);
	if (c >= '0' && c <= '9') return true;

	return false;
}

bool regex_meta_match_hyphen_letter(struct string_stream* ss_ptr, regex_meta* meta_ptr, regex_pattern_tree* tree_ptr)
{
	char c = string_stream_char_at_cursor(ss_ptr);
	if (c == '-') return true;

	return false;
}

bool regex_meta_match_hyphen_number(struct string_stream* ss_ptr, regex_meta* meta_ptr, regex_pattern_tree* tree_ptr)
{
	char c = string_stream_char_at_cursor(ss_ptr);
	if (c == ',') return true;

	return false;
}

bool regex_meta_match_no_meta_charset(struct string_stream* ss_ptr, regex_meta* meta_ptr, regex_pattern_tree* tree_ptr)
{
	if (ss_ptr == NULL || meta_ptr == NULL || tree_ptr == NULL) return false;

	int cursor = ss_ptr->cursor;
	do
	{
		if (string_stream_is_over(ss_ptr)) break;
		char c = string_stream_char_at(ss_ptr, cursor);
		if (c == '\0')
		{
			break;
		}
		if (REGEX_IS_META_CHAR(c))
		{
			cursor--;
			break;
		}
		cursor++;
	} while (cursor <= ss_ptr->string->size);

	if (cursor < ss_ptr->cursor) return false;

	int count = cursor - ss_ptr->cursor;
	string_stream_seek(ss_ptr, count, ess_cur);
	return true;
}