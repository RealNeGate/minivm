#pragma once

#include "libc.h"

typedef int32_t vm_reg_t;
typedef int32_t vm_opcode_t;

#include "obj.h"

enum vm_opcode_t
{
    VM_OPCODE_EXIT,
    VM_OPCODE_STORE_REG,
    VM_OPCODE_STORE_NONE,
    VM_OPCODE_STORE_BOOL,
    VM_OPCODE_STORE_INT,
    VM_OPCODE_STORE_FUN,
    VM_OPCODE_FUN_DONE,
    VM_OPCODE_EQUAL,
    VM_OPCODE_EQUAL_NUM,
    VM_OPCODE_NOT_EQUAL,
    VM_OPCODE_NOT_EQUAL_NUM,
    VM_OPCODE_LESS,
    VM_OPCODE_LESS_NUM,
    VM_OPCODE_GREATER,
    VM_OPCODE_GREATER_NUM,
    VM_OPCODE_LESS_THAN_EQUAL,
    VM_OPCODE_LESS_THAN_EQUAL_NUM,
    VM_OPCODE_GREATER_THAN_EQUAL,
    VM_OPCODE_GREATER_THAN_EQUAL_NUM,
    VM_OPCODE_JUMP,
    VM_OPCODE_BRANCH_FALSE,
    VM_OPCODE_BRANCH_TRUE,
    VM_OPCODE_BRANCH_EQUAL,
    VM_OPCODE_BRANCH_EQUAL_NUM,
    VM_OPCODE_BRANCH_NOT_EQUAL,
    VM_OPCODE_BRANCH_NOT_EQUAL_NUM,
    VM_OPCODE_BRANCH_LESS,
    VM_OPCODE_BRANCH_LESS_NUM,
    VM_OPCODE_BRANCH_GREATER,
    VM_OPCODE_BRANCH_GREATER_NUM,
    VM_OPCODE_BRANCH_LESS_THAN_EQUAL,
    VM_OPCODE_BRANCH_LESS_THAN_EQUAL_NUM,
    VM_OPCODE_BRANCH_GREATER_THAN_EQUAL,
    VM_OPCODE_BRANCH_GREATER_THAN_EQUAL_NUM,
    VM_OPCODE_INC,
    VM_OPCODE_INC_NUM,
    VM_OPCODE_DEC,
    VM_OPCODE_DEC_NUM,
    VM_OPCODE_ADD,
    VM_OPCODE_ADD_NUM,
    VM_OPCODE_SUB,
    VM_OPCODE_SUB_NUM,
    VM_OPCODE_MUL,
    VM_OPCODE_MUL_NUM,
    VM_OPCODE_DIV,
    VM_OPCODE_DIV_NUM,
    VM_OPCODE_MOD,
    VM_OPCODE_MOD_NUM,
    VM_OPCODE_CONCAT,
    VM_OPCODE_STATIC_CALL0,
    VM_OPCODE_STATIC_CALL1,
    VM_OPCODE_STATIC_CALL2,
    VM_OPCODE_STATIC_CALL,
    VM_OPCODE_TAIL_CALL0,
    VM_OPCODE_TAIL_CALL1,
    VM_OPCODE_TAIL_CALL2,
    VM_OPCODE_TAIL_CALL,
    VM_OPCODE_CALL0,
    VM_OPCODE_CALL1,
    VM_OPCODE_CALL2,
    VM_OPCODE_CALL,
    VM_OPCODE_RETURN,
    VM_OPCODE_PUTCHAR,
    VM_OPCODE_REF_NEW,
    VM_OPCODE_BOX_NEW,
    VM_OPCODE_STRING_NEW,
    VM_OPCODE_ARRAY_NEW,
    VM_OPCODE_MAP_NEW,
    VM_OPCODE_REF_GET,
    VM_OPCODE_BOX_GET,
    VM_OPCODE_BOX_SET,
    VM_OPCODE_LENGTH,
    VM_OPCODE_INDEX_GET,
    VM_OPCODE_INDEX_SET,
    VM_OPCODE_TYPE,
    VM_OPCODE_CALL_HANDLER,
    VM_OPCODE_SET_HANDLER,
    VM_OPCODE_RETURN_HANDLER,
    VM_OPCODE_EXIT_HANDLER,
    VM_OPCODE_EXEC,
    VM_OPCODE_MAX1,
    VM_OPCODE_MAX2P = 128,
};

typedef struct
{
    int index;
    int nargs;
    vm_reg_t outreg;
    void *locals;
} vm_stack_frame_t;

typedef struct
{
    int index;
    vm_reg_t outreg;
    void *locals;
    int resume;
    int exit;
} vm_handler_frame_t;
