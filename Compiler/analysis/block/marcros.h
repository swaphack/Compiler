#pragma once


#ifdef __cplusplus
extern "C" {
#endif

// ������������
typedef enum delivery_type
{
	// ֵ����
	edt_value,
	// ��������
	edt_ref,
}delivery_type;



// ����Ȩ��
typedef enum access_type
{
	eat_public,
	eat_protected,
	eat_internal,
	eat_private,
}access_type;

// ������
typedef enum scope_type
{
	// ��
	est_block,
	// ����
	est_function,
	// �ṹ��
	est_struct,
	// �����ռ�
	est_namespace,
	// ȫ��
	est_global,
}scope_type;

#ifdef __cplusplus
}
#endif