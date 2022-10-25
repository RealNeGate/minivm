
#include "./wasm.h"

#include <stdint.h>

enum vm_wasm_lang_type_enum_t {
    VM_WASM_TYPE_NOT_SPECIFIED = 0x00,
    VM_WASM_TYPE_I32 = 0x7f,
    VM_WASM_TYPE_I64 = 0x7e,
    VM_WASM_TYPE_F32 = 0x7d,
    VM_WASM_TYPE_F64 = 0x7c,
    VM_WASM_TYPE_ANYFUNC = 0x70,
    VM_WASM_TYPE_FUNC = 0x60,
    VM_WASM_TYPE_BLOCK_TYPE = 0x40,
};

enum vm_wasm_external_kind_enum_t {
    VM_WASM_EXTERNAL_KIND_FUNCTION = 0,
    VM_WASM_EXTERNAL_KIND_TABLE = 1,
    VM_WASM_EXTERNAL_KIND_MEMORY = 2,
    VM_WASM_EXTERNAL_KIND_GLOBAL = 3,
};

enum vm_wasm_section_id_enum_t {
    VM_WASM_SECTION_ID_CUSTOM = 0,
    VM_WASM_SECTION_ID_TYPE = 1,
    VM_WASM_SECTION_ID_IMPORT = 2,
    VM_WASM_SECTION_ID_FUNCTION = 3,
    VM_WASM_SECTION_ID_TABLE = 4,
    VM_WASM_SECTION_ID_MEMORY = 5,
    VM_WASM_SECTION_ID_GLOBAL = 6,
    VM_WASM_SECTION_ID_EXPORT = 7,
    VM_WASM_SECTION_ID_START = 8,
    VM_WASM_SECTION_ID_ELEMENT = 9,
    VM_WASM_SECTION_ID_CODE = 10,
    VM_WASM_SECTION_ID_DATA = 11,
};

enum vm_wasm_opcode_enum_t {
    // FLOW CONTROL
    VM_WASM_OPCODE_UNREACHABLE = 0X0,
    VM_WASM_OPCODE_NOP = 0X1,
    VM_WASM_OPCODE_BLOCK = 0X2,
    VM_WASM_OPCODE_LOOP = 0X3,
    VM_WASM_OPCODE_IF = 0X4,
    VM_WASM_OPCODE_ELSE = 0X5,
    VM_WASM_OPCODE_END = 0XB,
    VM_WASM_OPCODE_BR = 0XC,
    VM_WASM_OPCODE_BR_IF = 0XD,
    VM_WASM_OPCODE_BR_TABLE = 0XE,
    VM_WASM_OPCODE_RETURN = 0XF,

    // CALLS
    VM_WASM_OPCODE_CALL = 0X10,
    VM_WASM_OPCODE_CALL_INDIRECT = 0X11,

    // PARAMETRIC OPERATORS
    VM_WASM_OPCODE_DROP = 0X1A,
    VM_WASM_OPCODE_SELECT = 0X1B,

    // VARIBALE ACCESS
    VM_WASM_OPCODE_GET_LOCAL = 0X20,
    VM_WASM_OPCODE_SET_LOCAL = 0X21,
    VM_WASM_OPCODE_TEE_LOCAL = 0X22,
    VM_WASM_OPCODE_GET_GLOBAL = 0X23,
    VM_WASM_OPCODE_SET_GLOBAL = 0X24,

    // MEMORY-RELATED OPERATORS
    VM_WASM_OPCODE_I32_LOAD = 0X28,
    VM_WASM_OPCODE_I64_LOAD = 0X29,
    VM_WASM_OPCODE_F32_LOAD = 0X2A,
    VM_WASM_OPCODE_F64_LOAD = 0X2B,
    VM_WASM_OPCODE_I32_LOAD8_S = 0X2C,
    VM_WASM_OPCODE_I32_LOAD8_U = 0X2D,
    VM_WASM_OPCODE_I32_LOAD16_S = 0X2E,
    VM_WASM_OPCODE_I32_LOAD16_U = 0X2F,
    VM_WASM_OPCODE_I64_LOAD8_S = 0X30,
    VM_WASM_OPCODE_I64_LOAD8_U = 0X31,
    VM_WASM_OPCODE_I64_LOAD16_S = 0X32,
    VM_WASM_OPCODE_I64_LOAD16_U = 0X33,
    VM_WASM_OPCODE_I64_LOAD32_S = 0X34,
    VM_WASM_OPCODE_I64_LOAD32_U = 0X35,
    VM_WASM_OPCODE_I32_STORE = 0X36,
    VM_WASM_OPCODE_I64_STORE = 0X37,
    VM_WASM_OPCODE_F32_STORE = 0X38,
    VM_WASM_OPCODE_F64_STORE = 0X39,
    VM_WASM_OPCODE_I32_STORE8 = 0X3A,
    VM_WASM_OPCODE_I32_STORE16 = 0X3B,
    VM_WASM_OPCODE_I64_STORE8 = 0X3C,
    VM_WASM_OPCODE_I64_STORE16 = 0X3D,
    VM_WASM_OPCODE_I64_STORE32 = 0X3E,
    VM_WASM_OPCODE_CURRENT_MEMORY = 0X3F,
    VM_WASM_OPCODE_GROW_MEMORY = 0X40,

    // CONSTANTS
    VM_WASM_OPCODE_I32_CONST = 0X41,
    VM_WASM_OPCODE_I64_CONST = 0X42,
    VM_WASM_OPCODE_F32_CONST = 0X43,
    VM_WASM_OPCODE_F64_CONST = 0X44,

    // COMPARISON OPERATORS
    VM_WASM_OPCODE_I32_EQZ = 0X45,
    VM_WASM_OPCODE_I32_EQ = 0X46,
    VM_WASM_OPCODE_I32_NE = 0X47,
    VM_WASM_OPCODE_I32_LT_S = 0X48,
    VM_WASM_OPCODE_I32_LT_U = 0X49,
    VM_WASM_OPCODE_I32_GT_S = 0X4A,
    VM_WASM_OPCODE_I32_GT_U = 0X4B,
    VM_WASM_OPCODE_I32_LE_S = 0X4C,
    VM_WASM_OPCODE_I32_LE_U = 0X4D,
    VM_WASM_OPCODE_I32_GE_S = 0X4E,
    VM_WASM_OPCODE_I32_GE_U = 0X4F,
    VM_WASM_OPCODE_I64_EQZ = 0X50,
    VM_WASM_OPCODE_I64_EQ = 0X51,
    VM_WASM_OPCODE_I64_NE = 0X52,
    VM_WASM_OPCODE_I64_LT_S = 0X53,
    VM_WASM_OPCODE_I64_LT_U = 0X54,
    VM_WASM_OPCODE_I64_GT_S = 0X55,
    VM_WASM_OPCODE_I64_GT_U = 0X56,
    VM_WASM_OPCODE_I64_LE_S = 0X57,
    VM_WASM_OPCODE_I64_LE_U = 0X58,
    VM_WASM_OPCODE_I64_GE_S = 0X59,
    VM_WASM_OPCODE_I64_GE_U = 0X5A,
    VM_WASM_OPCODE_F32_EQ = 0X5B,
    VM_WASM_OPCODE_F32_NE = 0X5C,
    VM_WASM_OPCODE_F32_LT = 0X5D,
    VM_WASM_OPCODE_F32_GT = 0X5E,
    VM_WASM_OPCODE_F32_LE = 0X5F,
    VM_WASM_OPCODE_F32_GE = 0X60,
    VM_WASM_OPCODE_F64_EQ = 0X61,
    VM_WASM_OPCODE_F64_NE = 0X62,
    VM_WASM_OPCODE_F64_LT = 0X63,
    VM_WASM_OPCODE_F64_GT = 0X64,
    VM_WASM_OPCODE_F64_LE = 0X65,
    VM_WASM_OPCODE_F64_GE = 0X66,

    // NUMERIC OPERATORS
    VM_WASM_OPCODE_I32_CLZ = 0X67,
    VM_WASM_OPCODE_I32_CTZ = 0X68,
    VM_WASM_OPCODE_I32_POPCNT = 0X69,
    VM_WASM_OPCODE_I32_ADD = 0X6A,
    VM_WASM_OPCODE_I32_SUB = 0X6B,
    VM_WASM_OPCODE_I32_MUL = 0X6C,
    VM_WASM_OPCODE_I32_DIV_S = 0X6D,
    VM_WASM_OPCODE_I32_DIV_U = 0X6E,
    VM_WASM_OPCODE_I32_REM_S = 0X6F,
    VM_WASM_OPCODE_I32_REM_U = 0X70,
    VM_WASM_OPCODE_I32_AND = 0X71,
    VM_WASM_OPCODE_I32_OR = 0X72,
    VM_WASM_OPCODE_I32_XOR = 0X73,
    VM_WASM_OPCODE_I32_SHL = 0X74,
    VM_WASM_OPCODE_I32_SHR_S = 0X75,
    VM_WASM_OPCODE_I32_SHR_U = 0X76,
    VM_WASM_OPCODE_I32_ROTL = 0X77,
    VM_WASM_OPCODE_I32_ROTR = 0X78,
    VM_WASM_OPCODE_I64_CLZ = 0X79,
    VM_WASM_OPCODE_I64_CTZ = 0X7A,
    VM_WASM_OPCODE_I64_POPCNT = 0X7B,
    VM_WASM_OPCODE_I64_ADD = 0X7C,
    VM_WASM_OPCODE_I64_SUB = 0X7D,
    VM_WASM_OPCODE_I64_MUL = 0X7E,
    VM_WASM_OPCODE_I64_DIV_S = 0X7F,
    VM_WASM_OPCODE_I64_DIV_U = 0X80,
    VM_WASM_OPCODE_I64_REM_S = 0X81,
    VM_WASM_OPCODE_I64_REM_U = 0X82,
    VM_WASM_OPCODE_I64_AND = 0X83,
    VM_WASM_OPCODE_I64_OR = 0X84,
    VM_WASM_OPCODE_I64_XOR = 0X85,
    VM_WASM_OPCODE_I64_SHL = 0X86,
    VM_WASM_OPCODE_I64_SHR_S = 0X87,
    VM_WASM_OPCODE_I64_SHR_U = 0X88,
    VM_WASM_OPCODE_I64_ROTL = 0X89,
    VM_WASM_OPCODE_I64_ROTR = 0X8A,
    VM_WASM_OPCODE_F32_ABS = 0X8B,
    VM_WASM_OPCODE_F32_NEG = 0X8C,
    VM_WASM_OPCODE_F32_CEIL = 0X8D,
    VM_WASM_OPCODE_F32_FLOOR = 0X8E,
    VM_WASM_OPCODE_F32_TRUNC = 0X8F,
    VM_WASM_OPCODE_F32_NEAREST = 0X90,
    VM_WASM_OPCODE_F32_SQRT = 0X91,
    VM_WASM_OPCODE_F32_ADD = 0X92,
    VM_WASM_OPCODE_F32_SUB = 0X93,
    VM_WASM_OPCODE_F32_MUL = 0X94,
    VM_WASM_OPCODE_F32_DIV = 0X95,
    VM_WASM_OPCODE_F32_MIN = 0X96,
    VM_WASM_OPCODE_F32_MAX = 0X97,
    VM_WASM_OPCODE_F32_COPYSIGN = 0X98,
    VM_WASM_OPCODE_F64_ABS = 0X99,
    VM_WASM_OPCODE_F64_NEG = 0X9A,
    VM_WASM_OPCODE_F64_CEIL = 0X9B,
    VM_WASM_OPCODE_F64_FLOOR = 0X9C,
    VM_WASM_OPCODE_F64_TRUNC = 0X9D,
    VM_WASM_OPCODE_F64_NEAREST = 0X9E,
    VM_WASM_OPCODE_F64_SQRT = 0X9F,
    VM_WASM_OPCODE_F64_ADD = 0XA0,
    VM_WASM_OPCODE_F64_SUB = 0XA1,
    VM_WASM_OPCODE_F64_MUL = 0XA2,
    VM_WASM_OPCODE_F64_DIV = 0XA3,
    VM_WASM_OPCODE_F64_MIN = 0XA4,
    VM_WASM_OPCODE_F64_MAX = 0XA5,
    VM_WASM_OPCODE_F64_COPYSIGN = 0XA6,

    // CONVERSIONS
    VM_WASM_OPCODE_I32_WRAP_I64 = 0XA7,
    VM_WASM_OPCODE_I32_TRUNC_S_F32 = 0XA8,
    VM_WASM_OPCODE_I32_TRUNC_U_F32 = 0XA9,
    VM_WASM_OPCODE_I32_TRUNC_S_F64 = 0XAA,
    VM_WASM_OPCODE_I32_TRUNC_U_F64 = 0XAB,
    VM_WASM_OPCODE_I64_EXTEND_S_I32 = 0XAC,
    VM_WASM_OPCODE_I64_EXTEND_U_I32 = 0XAD,
    VM_WASM_OPCODE_I64_TRUNC_S_F32 = 0XAE,
    VM_WASM_OPCODE_I64_TRUNC_U_F32 = 0XAF,
    VM_WASM_OPCODE_I64_TRUNC_S_F64 = 0XB0,
    VM_WASM_OPCODE_I64_TRUNC_U_F64 = 0XB1,
    VM_WASM_OPCODE_F32_CONVERT_S_I32 = 0XB2,
    VM_WASM_OPCODE_F32_CONVERT_U_I32 = 0XB3,
    VM_WASM_OPCODE_F32_CONVERT_S_I64 = 0XB4,
    VM_WASM_OPCODE_F32_CONVERT_U_I64 = 0XB5,
    VM_WASM_OPCODE_F32_DEMOTE_F64 = 0XB6,
    VM_WASM_OPCODE_F64_CONVERT_S_I32 = 0XB7,
    VM_WASM_OPCODE_F64_CONVERT_U_I32 = 0XB8,
    VM_WASM_OPCODE_F64_CONVERT_S_I64 = 0XB9,
    VM_WASM_OPCODE_F64_CONVERT_U_I64 = 0XBA,
    VM_WASM_OPCODE_F64_PROMOTE_F32 = 0XBB,

    // REINTERPRETATIONS
    VM_WASM_OPCODE_I32_REINTERPRET_F32 = 0XBC,
    VM_WASM_OPCODE_I64_REINTERPRET_F64 = 0XBD,
    VM_WASM_OPCODE_F32_REINTERPRET_I32 = 0XBE,
    VM_WASM_OPCODE_F64_REINTERPRET_I64 = 0XBF,
};

enum vm_wasm_memory_immediate_id_enum_t {
    VM_WASM_IMMEDIATE_NONE,
    VM_WASM_IMMEDIATE_BLOCK_TYPE,
    VM_WASM_IMMEDIATE_VARUINT1,
    VM_WASM_IMMEDIATE_VARUINT32,
    VM_WASM_IMMEDIATE_VARUINT64,
    VM_WASM_IMMEDIATE_VARINT32,
    VM_WASM_IMMEDIATE_VARINT64,
    VM_WASM_IMMEDIATE_UINT32,
    VM_WASM_IMMEDIATE_UINT64,
    VM_WASM_IMMEDIATE_BR_TABLE,
    VM_WASM_IMMEDIATE_CALL_INDIRECT,
    VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
};

vm_wasm_immediate_id_t vm_wasm_immediates[] = {
    [VM_WASM_OPCODE_BLOCK] = VM_WASM_IMMEDIATE_BLOCK_TYPE,
    [VM_WASM_OPCODE_LOOP] = VM_WASM_IMMEDIATE_BLOCK_TYPE,
    [VM_WASM_OPCODE_IF] = VM_WASM_IMMEDIATE_BLOCK_TYPE,
    [VM_WASM_OPCODE_BR] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_BR_IF] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_BR_TABLE] = VM_WASM_IMMEDIATE_BR_TABLE,
    [VM_WASM_OPCODE_CALL] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_CALL_INDIRECT] = VM_WASM_IMMEDIATE_CALL_INDIRECT,
    [VM_WASM_OPCODE_GET_LOCAL] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_SET_LOCAL] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_TEE_LOCAL] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_GET_GLOBAL] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_SET_GLOBAL] = VM_WASM_IMMEDIATE_VARUINT32,
    [VM_WASM_OPCODE_I32_LOAD] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_F32_LOAD] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_F64_LOAD] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_LOAD8_S] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_LOAD8_U] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_LOAD16_S] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_LOAD16_U] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD8_S] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD8_U] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD16_S] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD16_U] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD32_S] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_LOAD32_U] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_STORE] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_STORE] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_F32_STORE] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_F64_STORE] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_STORE8] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I32_STORE16] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_STORE8] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_STORE16] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_I64_STORE32] = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
    [VM_WASM_OPCODE_CURRENT_MEMORY] = VM_WASM_IMMEDIATE_VARUINT1,
    [VM_WASM_OPCODE_GROW_MEMORY] = VM_WASM_IMMEDIATE_VARUINT1,
    [VM_WASM_OPCODE_I32_CONST] = VM_WASM_IMMEDIATE_VARINT32,
    [VM_WASM_OPCODE_I64_CONST] = VM_WASM_IMMEDIATE_VARINT64,
    [VM_WASM_OPCODE_F32_CONST] = VM_WASM_IMMEDIATE_UINT32,
    [VM_WASM_OPCODE_F64_CONST] = VM_WASM_IMMEDIATE_UINT64,
    [VM_WASM_OPCODE_BLOCK] = VM_WASM_IMMEDIATE_BLOCK_TYPE,
};

uint64_t vm_wasm_parse_uleb(FILE *in) {
    unsigned char buf;
    uint64_t x = 0;
    size_t bytes = 0;
    while (fread(&buf, 1, 1, in)) {
        x |= (buf & 0x7fULL) << (7 * bytes++);
        if (!(buf & 0x80U)) {
            break;
        }
    }
    return x;
}

int64_t vm_wasm_parse_sleb(FILE *in) {
    uint64_t ret = vm_wasm_parse_uleb(in);
    return *(int64_t *)&ret;
}

uint8_t vm_wasm_parse_byte(FILE *in) {
    uint8_t ret;
    fread(&ret, 1, 1, in);
    return ret;
}

vm_wasm_preamble_t vm_wasm_parse_preamble(FILE *in) {
    return (vm_wasm_preamble_t){
        .magic[0] = vm_wasm_parse_byte(in),
        .magic[1] = vm_wasm_parse_byte(in),
        .magic[2] = vm_wasm_parse_byte(in),
        .magic[3] = vm_wasm_parse_byte(in),
        .version[0] = vm_wasm_parse_byte(in),
        .version[1] = vm_wasm_parse_byte(in),
        .version[2] = vm_wasm_parse_byte(in),
        .version[3] = vm_wasm_parse_byte(in),
    };
}

vm_wasm_section_header_t vm_wasm_parse_section_header(FILE *in) {
    uint8_t id = vm_wasm_parse_byte(in);
    return (vm_wasm_section_header_t){
        .id = id,
        .size = vm_wasm_parse_uleb(in),
    };
}

uint8_t vm_wasm_parse_varuint1(FILE *in) {
    return vm_wasm_parse_byte(in);
}

int32_t vm_wasm_parse_varint32(FILE *in) {
    return (int32_t)vm_wasm_parse_sleb(in);
}

int64_t vm_wasm_parse_varint64(FILE *in) {
    return (int64_t)vm_wasm_parse_sleb(in);
}

int32_t vm_wasm_parse_varuint32(FILE *in) {
    return (uint32_t)vm_wasm_parse_uleb(in);
}

int64_t vm_wasm_parse_varuint64(FILE *in) {
    return (uint64_t)vm_wasm_parse_uleb(in);
}

uint32_t vm_wasm_parse_uint32(FILE *in) {
    uint32_t ret;
    fread(&ret, sizeof(uint32_t), 1, in);
    return ret;
}

uint64_t vm_wasm_parse_uint64(FILE *in) {
    uint64_t ret;
    fread(&ret, sizeof(uint64_t), 1, in);
    return ret;
}

vm_wasm_lang_type_t vm_wasm_parse_block_type(FILE *in) {
    return vm_wasm_parse_byte(in);
}

vm_wasm_br_table_t vm_wasm_parse_br_table(FILE *in) {
    uint64_t num = vm_wasm_parse_uleb(in);
    uint64_t *targets = vm_malloc(sizeof(uint64_t) * num);
    for (uint64_t i = 0; i < num; i++) {
        targets[i] = vm_wasm_parse_uleb(in);
    }
    uint64_t default_target = vm_wasm_parse_uleb(in);
    return (vm_wasm_br_table_t){
        .num_targets = num,
        .targets = targets,
        .default_target = default_target,
    };
}

vm_wasm_call_indirect_t vm_wasm_parse_call_indirect(FILE *in) {
    return (vm_wasm_call_indirect_t){
        .index = vm_wasm_parse_uleb(in),
        .reserved = vm_wasm_parse_byte(in),
    };
}

vm_wasm_memory_immediate_t vm_wasm_parse_memory_immediate(FILE *in) {
    return (vm_wasm_memory_immediate_t){
        .flags = vm_wasm_parse_uleb(in),
        .offset = vm_wasm_parse_uleb(in),
    };
}

vm_wasm_type_function_t vm_wasm_parse_type_function(FILE *in) {
    return (vm_wasm_type_function_t){
        .data = vm_wasm_parse_uleb(in),
    };
}

vm_wasm_type_table_t vm_wasm_parse_type_table(FILE *in) {
    return (vm_wasm_type_table_t){
        .element_type = vm_wasm_parse_byte(in),
        .limits = vm_wasm_parse_type_memory(in),
    };
}

vm_wasm_type_global_t vm_wasm_parse_type_global(FILE *in) {
    return (vm_wasm_type_global_t){
        .content_type = vm_wasm_parse_byte(in),
        .mutability = vm_wasm_parse_byte(in),
    };
}

vm_wasm_type_memory_t vm_wasm_parse_type_memory(FILE *in) {
    uint64_t flags = vm_wasm_parse_uleb(in);
    return (vm_wasm_type_memory_t){
        .flags = flags,
        .initial = vm_wasm_parse_uleb(in),
        .maximum = (flags % 2 == 1) ? vm_wasm_parse_uleb(in) : UINT64_MAX,
    };
}

vm_wasm_type_t vm_wasm_parse_type(FILE *in, vm_wasm_external_kind_t tag) {
    if (tag == VM_WASM_EXTERNAL_KIND_FUNCTION) {
        return (vm_wasm_type_t) {
            .function = vm_wasm_parse_type_function(in),
            .tag = tag,
        };
    }
    if (tag == VM_WASM_EXTERNAL_KIND_TABLE) {
        return (vm_wasm_type_t) {
            .table = vm_wasm_parse_type_table(in),
            .tag = tag,
        };
    }
    if (tag == VM_WASM_EXTERNAL_KIND_GLOBAL) {
        return (vm_wasm_type_t) {
            .global = vm_wasm_parse_type_global(in),
            .tag = tag,
        };
    }
    if (tag == VM_WASM_EXTERNAL_KIND_MEMORY) {
        return (vm_wasm_type_t) {
            .memory = vm_wasm_parse_type_memory(in),
            .tag = tag,
        };
    }
    __builtin_trap();
}

vm_wasm_section_custom_t vm_wasm_parse_section_custom(FILE *in, vm_wasm_section_header_t header) {
    void *payload = vm_malloc(header.size);
    fread(payload, 1, header.size, in);
    return (vm_wasm_section_custom_t){
        .payload = payload,
    };
}

vm_wasm_section_type_t vm_wasm_parse_section_type(FILE *in) {
    uint64_t num = vm_wasm_parse_uleb(in);
    vm_wasm_section_type_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_type_entry_t) * num);
    for (uint64_t i = 0; i < num; i++) {
        vm_wasm_section_type_entry_t entry;
        vm_wasm_lang_type_t type = vm_wasm_parse_byte(in);
        uint64_t num_params = vm_wasm_parse_uleb(in);
        vm_wasm_lang_type_t*params = vm_malloc(sizeof(vm_wasm_lang_type_t) * num_params);
        for (uint64_t j = 0; j < num_params; j++) {
            params[j] = vm_wasm_parse_byte(in);
        }
        uint64_t num_returns = vm_wasm_parse_uleb(in);
        vm_wasm_lang_type_t return_type = VM_WASM_TYPE_NOT_SPECIFIED;
        bool has_return_type = false;
        if (num_returns) {
            has_return_type = true;
            return_type = vm_wasm_parse_byte(in);
        }
        entries[i] = (vm_wasm_section_type_entry_t) {
            .type = type,
            .num_params = num_params,
            .params = params,
            .num_returns = num_returns,
            .has_return_type = has_return_type,
            .return_type = return_type,
        };
    }
    return (vm_wasm_section_type_t){
        .num_entries = num,
        .entries = entries,
    };
}

vm_wasm_section_import_t vm_wasm_parse_section_import(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_section_import_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_import_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t module_len = vm_wasm_parse_uleb(in);
        char *module_str = vm_malloc(sizeof(char) * (module_len + 1));
        fread(module_str, 1, module_len, in);
        module_str[module_len] = '\0';
        uint64_t field_len = vm_wasm_parse_uleb(in);
        char *field_str = vm_malloc(sizeof(char) * (field_len + 1));
        fread(field_str, 1, field_len, in);
        field_str[field_len] = '\0';
        vm_wasm_external_kind_t kind = vm_wasm_parse_byte(in);
        vm_wasm_type_t type = vm_wasm_parse_type(in, kind);
        entries[i] = (vm_wasm_section_import_entry_t) {
            .module_str = module_str,
            .field_str = field_str,
            .kind = kind,
            .type = type,
        };
    }
    return (vm_wasm_section_import_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_function_t vm_wasm_parse_section_function(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    uint64_t *entries = vm_malloc(sizeof(uint64_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = vm_wasm_parse_uleb(in);
    }
    return (vm_wasm_section_function_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_table_t vm_wasm_parse_section_table(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_type_table_t *entries = vm_malloc(sizeof(vm_wasm_type_table_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = vm_wasm_parse_type_table(in);
    }
    return (vm_wasm_section_table_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_memory_t vm_wasm_parse_section_memory(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_type_memory_t *entries = vm_malloc(sizeof(vm_wasm_section_global_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = vm_wasm_parse_type_memory(in);
    }
    return (vm_wasm_section_memory_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_global_t vm_wasm_parse_section_global(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_section_global_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_global_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        entries[i] = (vm_wasm_section_global_entry_t) {
            .global = vm_wasm_parse_type_global(in),
            .init_expr = vm_wasm_parse_instr(in),
        };
    }
    return (vm_wasm_section_global_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_start_t vm_wasm_parse_section_start(FILE *in) {
    return (vm_wasm_section_start_t){
        .index = vm_wasm_parse_uleb(in),
    };
}

vm_wasm_section_element_t vm_wasm_parse_section_element(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_section_element_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_element_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t index = vm_wasm_parse_uleb(in);
        uint64_t offset = vm_wasm_parse_uleb(in);
        uint64_t num_elems = vm_wasm_parse_uleb(in);
        uint64_t *elems = vm_malloc(sizeof(uint64_t) * num_elems);
        for (uint64_t j = 0; j < num_elems; j++) {
            elems[j] = vm_wasm_parse_uleb(in);
        }
        entries[i] = (vm_wasm_section_element_entry_t){
            .index = index,
            .offset = offset,
            .num_elems = num_elems,
            .elems = elems,
        };
    }
    return (vm_wasm_section_element_t) {
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_code_t vm_wasm_parse_section_code(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_section_code_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_code_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t body_len = vm_wasm_parse_uleb(in);
        long end = ftell(in) + (long) body_len;
        uint64_t num_locals = vm_wasm_parse_uleb(in);
        vm_wasm_section_code_entry_local_t *locals = vm_malloc(sizeof(vm_wasm_section_code_entry_local_t) * num_locals);
        for (uint64_t j = 0; j < num_locals; j++) {
            uint64_t count = vm_wasm_parse_uleb(in);
            vm_wasm_lang_type_t type = vm_wasm_parse_byte(in);
            locals[j] = (vm_wasm_section_code_entry_local_t) {
                .count = count,
                .type = type,
            };
        }
        uint64_t alloc_instrs = 4;
        vm_wasm_instr_t *instrs = vm_malloc(sizeof(vm_wasm_instr_t) * alloc_instrs);
        uint64_t num_instrs;
        while (ftell(in) < end) {
            if (num_instrs + 1 >= alloc_instrs) {
                alloc_instrs = (alloc_instrs + 1) * 2;
                instrs = vm_realloc(instrs, sizeof(vm_wasm_instr_t) * alloc_instrs);
            }
            instrs[num_instrs] = vm_wasm_parse_instr(in);
            num_instrs += 1;
        }
        entries[i] = (vm_wasm_section_code_entry_t) {
            .num_locals = num_locals,
            .locals = locals,
            .num_instrs = num_instrs,
            .instrs = instrs,
        };
    }
    return (vm_wasm_section_code_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_section_data_t vm_wasm_parse_section_data(FILE *in) {
    uint64_t num_entries = vm_wasm_parse_uleb(in);
    vm_wasm_section_data_entry_t *entries = vm_malloc(sizeof(vm_wasm_section_data_entry_t) * num_entries);
    for (uint64_t i = 0; i < num_entries; i++) {
        uint64_t index = vm_wasm_parse_uleb(in);
        vm_wasm_instr_t offset = vm_wasm_parse_instr(in);
        uint64_t size = vm_wasm_parse_uleb(in);
        uint8_t *data = vm_malloc(sizeof(uint8_t) * size);
        fread(data, 1, size, in);
        entries[i] = (vm_wasm_section_data_entry_t) {
            .index = index,
            .offset = offset,
            .size = size,
            .data = data,
        };
    }
    return (vm_wasm_section_data_t){
        .num_entries = num_entries,
        .entries = entries,
    };
}

vm_wasm_instr_immediate_t vm_wasm_parse_instr_immediate(FILE *in, vm_wasm_immediate_id_t id) {
    if (id == VM_WASM_IMMEDIATE_BLOCK_TYPE) {
        return (vm_wasm_instr_immediate_t) {
            .id = VM_WASM_IMMEDIATE_BLOCK_TYPE,
            .block_type = vm_wasm_parse_block_type(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_VARUINT1) {
        return (vm_wasm_instr_immediate_t) {
            .id = VM_WASM_IMMEDIATE_VARUINT1,
            .varuint1 = vm_wasm_parse_varuint1(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_VARUINT32) {
        return (vm_wasm_instr_immediate_t) {
            .id = VM_WASM_IMMEDIATE_VARUINT32,
            .varuint32 = vm_wasm_parse_varuint32(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_VARUINT64) {
        return (vm_wasm_instr_immediate_t) {
            .id = VM_WASM_IMMEDIATE_VARUINT64,
            .varuint64 = vm_wasm_parse_varuint64(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_VARINT32) {
        return (vm_wasm_instr_immediate_t) {
            .id = VM_WASM_IMMEDIATE_VARINT32,
            .varint32 = vm_wasm_parse_varint32(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_VARINT64) {
        return (vm_wasm_instr_immediate_t) {
            .id = VM_WASM_IMMEDIATE_VARINT64,
            .varint64 = vm_wasm_parse_varint64(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_UINT32) {
        return (vm_wasm_instr_immediate_t) {
            .id = VM_WASM_IMMEDIATE_UINT32,
            .uint32 = vm_wasm_parse_uint32(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_UINT64) {
        return (vm_wasm_instr_immediate_t) {
            .id = VM_WASM_IMMEDIATE_UINT64,
            .uint64 = vm_wasm_parse_uint64(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_BR_TABLE) {
        return (vm_wasm_instr_immediate_t) {
            .id = VM_WASM_IMMEDIATE_BR_TABLE,
            .br_table = vm_wasm_parse_br_table(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_CALL_INDIRECT) {
        return (vm_wasm_instr_immediate_t) {
            .id = VM_WASM_IMMEDIATE_CALL_INDIRECT,
            .call_indirect = vm_wasm_parse_call_indirect(in),
        };
    }
    if (id == VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE) {
        return (vm_wasm_instr_immediate_t) {
            .id = VM_WASM_IMMEDIATE_MEMORY_IMMEDIATE,
            .memory_immediate = vm_wasm_parse_memory_immediate(in),
        };
    }
    __builtin_trap();
}

vm_wasm_instr_t vm_wasm_parse_instr(FILE *in) {
    vm_wasm_opcode_t opcode = vm_wasm_parse_sleb(in);
    vm_wasm_immediate_id_t immediate_id = vm_wasm_immediates[opcode];
    vm_wasm_instr_immediate_t immediate = vm_wasm_parse_instr_immediate(in, immediate_id);
    return (vm_wasm_instr_t){
        .opcode = opcode,
        .immediate = immediate,
    };
}

vm_wasm_module_t vm_wasm_parse_module(FILE *in) {
    return (vm_wasm_module_t){

    };
}
