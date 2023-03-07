#pragma once


#ifdef __cplusplus
extern "C" {
#endif

// ����code
typedef enum op_codes
{
	op_Ldloc_2,
	op_Ldloc_3,
	op_Ldloc_S,
	op_Ldnull,
	op_Ldobj,
	op_Ldsfld,
	op_Ldsflda,
	op_Ldstr,
	op_Ldtoken,
	op_Ldvirtftn,
	op_Leave,
	op_Ldloc_1,
	op_Leave_S,
	op_Mkrefany,
	op_Mul,
	op_Mul_Ovf,
	op_Mul_Ovf_Un,
	op_Neg,
	op_Newarr,
	op_Newobj,
	op_Nop,
	op_Not,
	op_Or,
	op_Pop,
	op_Localloc,
	op_Ldloc_0,
	op_Ldloca_S,
	op_Ldloca,
	op_Ldelem_I2,
	op_Ldelem_I4,
	op_Ldelem_I8,
	op_Ldelem_R4,
	op_Ldelem_R8,
	op_Ldelem_Ref,
	op_Ldelem_U1,
	op_Ldelem_U2,
	op_Ldelem_U4,
	op_Ldfld,
	op_Ldflda,
	op_Ldftn,
	op_Ldind_I,
	op_Ldind_I1,
	op_Ldind_I2,
	op_Ldind_I4,
	op_Ldind_I8,
	op_Ldind_R4,
	op_Ldind_R8,
	op_Ldind_Ref,
	op_Ldind_U1,
	op_Ldind_U2,
	op_Ldind_U4,
	op_Ldlen,
	op_Ldloc,
	op_Prefix1,
	op_Ldelem_I1,
	op_Prefix2,
	op_Prefix4,
	op_Stind_I2,
	op_Stind_I4,
	op_Stind_I8,
	op_Stind_R4,
	op_Stind_R8,
	op_Stind_Ref,
	op_Stloc,
	op_Stloc_0,
	op_Stloc_1,
	op_Stloc_2,
	op_Stloc_3,
	op_Stind_I1,
	op_Stloc_S,
	op_Stsfld,
	op_Sub,
	op_Sub_Ovf,
	op_Sub_Ovf_Un,
	op_Switch,
	op_Tailcall,
	op_Throw,
	op_Unaligned,
	op_Unbox,
	op_Unbox_Any,
	op_Volatile,
	op_Stobj,
	op_Stind_I,
	op_Stfld,
	op_Stelem_Ref,
	op_Prefix5,
	op_Prefix6,
	op_Prefix7,
	op_Prefixref,
	op_Readonly,
	op_Refanytype,
	op_Refanyval,
	op_Rem,
	op_Rem_Un,
	op_Ret,
	op_Rethrow,
	op_Shl,
	op_Shr,
	op_Shr_Un,
	op_Sizeof,
	op_Starg,
	op_Starg_S,
	op_Stelem,
	op_Stelem_I,
	op_Stelem_I1,
	op_Stelem_I2,
	op_Stelem_I4,
	op_Stelem_I8,
	op_Stelem_R4,
	op_Stelem_R8,
	op_Prefix3,
	op_Xor,
	op_Ldelem_I,
	op_Ldelem,
	op_Brtrue,
	op_Brtrue_S,
	op_Br_S,
	op_Call,
	op_Calli,
	op_Callvirt,
	op_Castclass,
	op_Ceq,
	op_Cgt,
	op_Cgt_Un,
	op_Ckfinite,
	op_Brfalse_S,
	op_Clt,
	op_Constrained,
	op_Conv_I,
	op_Conv_I1,
	op_Conv_I2,
	op_Conv_I4,
	op_Conv_I8,
	op_Conv_Ovf_I,
	op_Conv_Ovf_I1,
	op_Conv_Ovf_I1_Un,
	op_Conv_Ovf_I2,
	op_Conv_Ovf_I2_Un,
	op_Clt_Un,
	op_Brfalse,
	op_Break,
	op_Br,
	op_Add_Ovf,
	op_Add_Ovf_Un,
	op_And,
	op_Arglist,
	op_Beq,
	op_Beq_S,
	op_Bge,
	op_Bge_S,
	op_Bge_Un,
	op_Bge_Un_S,
	op_Bgt,
	op_Bgt_S,
	op_Bgt_Un,
	op_Bgt_Un_S,
	op_Ble,
	op_Ble_S,
	op_Ble_Un,
	op_Ble_Un_S,
	op_Blt,
	op_Blt_S,
	op_Blt_Un,
	op_Blt_Un_S,
	op_Bne_Un,
	op_Bne_Un_S,
	op_Box,
	op_Conv_Ovf_I4,
	op_Ldelema,
	op_Conv_Ovf_I4_Un,
	op_Conv_Ovf_I8_Un,
	op_Jmp,
	op_Ldarg,
	op_Ldarga,
	op_Ldarga_S,
	op_Ldarg_0,
	op_Ldarg_1,
	op_Ldarg_2,
	op_Ldarg_3,
	op_Ldarg_S,
	op_Ldc_I4,
	op_Ldc_I4_0,
	op_Isinst,
	op_Ldc_I4_1,
	op_Ldc_I4_3,
	op_Ldc_I4_4,
	op_Ldc_I4_5,
	op_Ldc_I4_6,
	op_Ldc_I4_7,
	op_Ldc_I4_8,
	op_Ldc_I4_M1,
	op_Ldc_I4_S,
	op_Ldc_I8,
	op_Ldc_R4,
	op_Ldc_R8,
	op_Ldc_I4_2,
	op_Initobj,
	op_Initblk,
	op_Endfinally,
	op_Conv_Ovf_I_Un,
	op_Conv_Ovf_U,
	op_Conv_Ovf_U1,
	op_Conv_Ovf_U1_Un,
	op_Conv_Ovf_U2,
	op_Conv_Ovf_U2_Un,
	op_Conv_Ovf_U4,
	op_Conv_Ovf_U4_Un,
	op_Conv_Ovf_U8,
	op_Conv_Ovf_U8_Un,
	op_Conv_Ovf_U_Un,
	op_Conv_R4,
	op_Conv_R8,
	op_Conv_R_Un,
	op_Conv_U,
	op_Conv_U1,
	op_Conv_U2,
	op_Conv_U4,
	op_Conv_U8,
	op_Cpblk,
	op_Cpobj,
	op_Div,
	op_Div_Un,
	op_Dup,
	op_Endfilter,
	op_Conv_Ovf_I8,
}op_codes;

#ifdef __cplusplus
}
#endif