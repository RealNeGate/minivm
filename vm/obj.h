#include "std/io.h"

#if !defined(VM_HEADER_OBJ)
#define VM_HEADER_OBJ

union vm_value_t;
typedef union vm_value_t vm_value_t;

struct vm_pair_t;
typedef struct vm_pair_t vm_pair_t;

struct vm_table_t;
typedef struct vm_table_t vm_table_t;

struct vm_std_value_t;
typedef struct vm_std_value_t vm_std_value_t;

struct vm_std_closure_t;
typedef struct vm_std_closure_t vm_std_closure_t;

#include "lib.h"
#include "ir/tag.h"

union vm_value_t {
    void *all;
    bool b;
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    float f32;
    double f64;
    vm_io_buffer_t *string;
    vm_io_buffer_t *buffer;
    vm_table_t *table;
    vm_std_value_t *closure;
    void (*ffi)(vm_std_closure_t *closure, vm_std_value_t *args);
};

struct vm_std_value_t {
    vm_value_t value;
    uint32_t tag;
};

struct vm_pair_t {
    vm_value_t key_val;
    vm_value_t val_val;
    uint32_t key_tag;
    uint32_t val_tag;
};

struct vm_table_t {
    vm_pair_t *pairs;
    uint32_t len;
    uint32_t used;
    uint8_t alloc;
};

#include "ir/ir.h"

struct vm_std_closure_t {
    vm_config_t *config;
    vm_blocks_t *blocks;
};

bool vm_value_eq(vm_std_value_t lhs, vm_std_value_t rhs);
bool vm_value_is_int(vm_std_value_t val);
int64_t vm_value_to_i64(vm_std_value_t arg);
vm_std_value_t vm_value_from_i64(vm_tag_t tag, int64_t arg);

vm_table_t *vm_table_new(void);

vm_pair_t *vm_table_get(vm_table_t *table, vm_value_t key_val, uint32_t key_tag);
void vm_table_set(vm_table_t *table, vm_value_t key_val, vm_value_t val_val, uint32_t key_tag, uint32_t val_tag);

void vm_table_set_pair(vm_table_t *table, vm_pair_t *pair);
void vm_table_get_pair(vm_table_t *table, vm_pair_t *pair);

void vm_table_set_value(vm_table_t *table, vm_std_value_t key, vm_std_value_t value);
vm_std_value_t vm_table_get_value(vm_table_t *table, vm_std_value_t value);

#define vm_value_nil(x) ((vm_std_value_t) {.tag = VM_TAG_NIL})
#define vm_std_value_bool(x) ((vm_std_value_t) {.tag = VM_TAG_BOOL, .value.b = (x)})
#define vm_std_value_false(x) vm_std_value_bool(false)
#define vm_std_value_true(x) vm_std_value_bool(true)
#define vm_std_value_i8(x) ((vm_std_value_t) {.tag = VM_TAG_I8, .value.i8 = (x)})
#define vm_std_value_i8(x) ((vm_std_value_t) {.tag = VM_TAG_I8, .value.i8 = (x)})
#define vm_std_value_i16(x) ((vm_std_value_t) {.tag = VM_TAG_I16, .value.i16 = (x)})
#define vm_std_value_i32(x) ((vm_std_value_t) {.tag = VM_TAG_I32, .value.i32 = (x)})
#define vm_std_value_i64(x) ((vm_std_value_t) {.tag = VM_TAG_I64, .value.i64 = (x)})
#define vm_std_value_f32(x) ((vm_std_value_t) {.tag = VM_TAG_F32, .value.f32 = (x)})
#define vm_std_value_f64(x) ((vm_std_value_t) {.tag = VM_TAG_F64, .value.f64 = (x)})
#define vm_std_value_cstr(c) ((vm_std_value_t) {.tag = VM_TAG_STRING, .value.string = vm_io_buffer_from_cstr(c)})
#define vm_std_value_str(l, p) ((vm_std_value_t) {.tag = VM_TAG_STRING, .value.string = vm_io_buffer_from_str((l), (p))})
#define vm_std_value_ffi(x) ((vm_std_value_t) {.tag = VM_TAG_FFI, .value.ffi = (x)})
#define vm_std_value_table(x) ((vm_std_value_t) {.tag = VM_TAG_TAB, .value.table = (x)})
#define vm_std_value_cerr(c) ((vm_std_value_t) {.tag = VM_TAG_ERROR, .value.string = vm_io_buffer_from_cstr(c)})
#define vm_std_value_err(l, p) ((vm_std_value_t) {.tag = VM_TAG_ERROR, .value.string = vm_io_buffer_from_str((l), (p))})

#endif
