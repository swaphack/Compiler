#pragma once

// �ķ�

#ifdef __cplusplus
extern "C" {
#endif

struct string;
struct analysis_table;

// �Ƿ����ս�� �ؼ��֣�����
bool is_terminal_word(const struct string* word, struct analysis_table* st_ptr);
// �Ƿ���ս�� ���ͱ�ͺ���������
bool is_nonterminal_word(const struct string* word, struct analysis_table* st_ptr);


#ifdef __cplusplus
}
#endif