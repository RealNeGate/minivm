
#include <stdint.h>
#include "./lib.h"

typedef uint8_t vm_wasm_immedate_t;
typedef uint8_t vm_wasm_opcode_t;
typedef uint8_t vm_wasm_section_id_t;
typedef uint8_t vm_wasm_lang_type_t;
typedef uint8_t vm_wasm_external_kind_t;

struct vm_wasm_preamble_t;
typedef struct vm_wasm_preamble_t vm_wasm_preamble_t;

struct vm_wasm_section_header_t;
typedef struct vm_wasm_section_header_t vm_wasm_section_header_t;

struct vm_wasm_br_table_t;
typedef struct vm_wasm_br_table_t vm_wasm_br_table_t;

struct vm_wasm_call_indirect_t;
typedef struct vm_wasm_call_indirect_t vm_wasm_call_indirect_t;

struct vm_wasm_memory_immediate_t;
typedef struct vm_wasm_memory_immediate_t vm_wasm_memory_immediate_t;

struct vm_wasm_type_function_t;
typedef struct vm_wasm_type_function_t vm_wasm_type_function_t;
 
struct vm_wasm_type_table_t;
typedef struct vm_wasm_type_table_t vm_wasm_type_table_t;

struct vm_wasm_type_t;
typedef struct vm_wasm_type_t vm_wasm_type_t;
 
struct vm_wasm_type_global_t;
typedef struct vm_wasm_type_global_t vm_wasm_type_global_t;
 
struct vm_wasm_type_memory_t;
typedef struct vm_wasm_type_memory_t vm_wasm_type_memory_t;
 
struct vm_wasm_section_custom_t;
typedef struct vm_wasm_section_custom_t vm_wasm_section_custom_t;

struct vm_wasm_section_type_entry_t;
typedef struct vm_wasm_section_type_entry_t vm_wasm_section_type_entry_t;

struct vm_wasm_section_type_t;
typedef struct vm_wasm_section_type_t vm_wasm_section_type_t;

struct vm_wasm_section_export_entry_t;
typedef struct vm_wasm_section_export_entry_t vm_wasm_section_export_entry_t;

struct vm_wasm_section_export_t;
typedef struct vm_wasm_section_export_t vm_wasm_section_export_t;

struct vm_wasm_section_import_entry_t;
typedef struct vm_wasm_section_import_entry_t vm_wasm_section_import_entry_t;

struct vm_wasm_section_import_t;
typedef struct vm_wasm_section_import_t vm_wasm_section_import_t;

struct vm_wasm_section_function_t;
typedef struct vm_wasm_section_function_t vm_wasm_section_function_t;

struct vm_wasm_section_table_t;
typedef struct vm_wasm_section_table_t vm_wasm_section_table_t;

struct vm_wasm_section_memory_t;
typedef struct vm_wasm_section_memory_t vm_wasm_section_memory_t;

struct vm_wasm_section_global_entry_t;
typedef struct vm_wasm_section_global_entry_t vm_wasm_section_global_entry_t;

struct vm_wasm_section_global_t;
typedef struct vm_wasm_section_global_t vm_wasm_section_global_t;

struct vm_wasm_section_start_t;
typedef struct vm_wasm_section_start_t vm_wasm_section_start_t;

struct vm_wasm_section_element_entry_t;
typedef struct vm_wasm_section_element_entry_t vm_wasm_section_element_entry_t;

struct vm_wasm_section_element_t;
typedef struct vm_wasm_section_element_t vm_wasm_section_element_t;

struct vm_wasm_section_code_entry_local_t;
typedef struct vm_wasm_section_code_entry_local_t vm_wasm_section_code_entry_local_t;

struct vm_wasm_section_code_entry_t;
typedef struct vm_wasm_section_code_entry_t vm_wasm_section_code_entry_t;

struct vm_wasm_section_code_t;
typedef struct vm_wasm_section_code_t vm_wasm_section_code_t;

struct vm_wasm_section_data_entry_t;
typedef struct vm_wasm_section_data_entry_t vm_wasm_section_data_entry_t;

struct vm_wasm_section_data_t;
typedef struct vm_wasm_section_data_t vm_wasm_section_data_t;

struct vm_wasm_instr_t;
typedef struct vm_wasm_instr_t vm_wasm_instr_t;

struct vm_wasm_module_t;
typedef struct vm_wasm_module_t vm_wasm_module_t;


struct vm_wasm_preamble_t {
    uint8_t magic[4];
    uint8_t version[4];
};

struct vm_wasm_section_header_t {
    vm_wasm_section_id_t id;
    uint64_t size;
};

struct vm_wasm_br_table_t {
    uint64_t num_targets;
    uint64_t *targets;
    uint64_t default_target;
};

struct vm_wasm_call_indirect_t {
    uint64_t index;
    uint8_t reserved;
};

struct vm_wasm_memory_immediate_t {
    uint64_t flags;
    uint64_t offset;
};

struct vm_wasm_type_function_t {
    uint64_t data;
};

struct vm_wasm_type_global_t {
    vm_wasm_external_kind_t content_type;
    uint8_t mutability;
};

struct vm_wasm_type_memory_t {
    uint64_t flags;
    uint64_t initial;
    uint64_t maximum;
};

struct vm_wasm_type_table_t {
    vm_wasm_lang_type_t element_type;
    vm_wasm_type_memory_t limits;
};

struct vm_wasm_type_t {
    union {
        vm_wasm_type_function_t function;  
        vm_wasm_type_global_t global; 
        vm_wasm_type_memory_t memory; 
        vm_wasm_type_table_t table; 
    };
    vm_wasm_lang_type_t tag;
};

// enum {
//     VM_WASM_SECTION_TYPE_CUSTOM = 0, 
//     VM_WASM_SECTION_TYPE_TYPE = 1, 
//     VM_WASM_SECTION_TYPE_IMPORT = 2, 
//     VM_WASM_SECTION_TYPE_FUNCTION = 3, 
//     VM_WASM_SECTION_TYPE_TABLE = 4, 
//     VM_WASM_SECTION_TYPE_MEMORY = 5, 
//     VM_WASM_SECTION_TYPE_GLOBAL = 6, 
//     VM_WASM_SECTION_TYPE_EXPORT = 7, 
//     VM_WASM_SECTION_TYPE_START = 8, 
//     VM_WASM_SECTION_TYPE_ELEMENT = 9, 
//     VM_WASM_SECTION_TYPE_CODE = 10, 
//     VM_WASM_SECTION_TYPE_DAT = 11, 
// };

struct vm_wasm_section_custom_t {
    void *payload;
};

struct vm_wasm_section_type_entry_t {
    uint64_t num_params;
    vm_wasm_lang_type_t *params;
    uint64_t num_returns;
    vm_wasm_lang_type_t type;
    vm_wasm_lang_type_t return_type;
    bool has_return_type;
};

struct vm_wasm_section_type_t {
    uint64_t num_entries;
    vm_wasm_section_type_entry_t *entries;
};

struct vm_wasm_section_import_entry_t {
    const char *module_str;
    const char *field_str;
    vm_wasm_external_kind_t kind;
    vm_wasm_type_t type;
};

struct vm_wasm_section_import_t {
    uint64_t num_entries;
    vm_wasm_section_import_entry_t *entries;
};

struct vm_wasm_section_function_t {
    uint64_t num_entries;
    uint64_t *entries;
};

struct vm_wasm_section_export_entry_t {
    const char *module_str;
    const char *field_str;
    const char *kind;
    vm_wasm_type_t type;
};

struct vm_wasm_section_export_t {
    uint64_t num_entries;
    vm_wasm_section_export_entry_t *entries;
};

struct vm_wasm_section_table_t {
    uint64_t num_entries;
    vm_wasm_type_table_t *entries;
};

struct vm_wasm_section_memory_t {
    uint64_t num_entries;
    vm_wasm_type_memory_t *entries;
};

struct vm_wasm_instr_t {
};

struct vm_wasm_section_global_entry_t {
    vm_wasm_type_global_t global;
    vm_wasm_instr_t init_expr;
};

struct vm_wasm_section_global_t {
    uint64_t num_entries;
    vm_wasm_section_global_entry_t *entries;
};

struct vm_wasm_section_start_t {
    uint64_t index;
};

struct vm_wasm_section_element_entry_t {
    uint64_t index;
    uint64_t offset;
    uint64_t num_elems;
    uint64_t *elems;
};

struct vm_wasm_section_element_t {
    uint64_t num_entries;
    vm_wasm_section_element_entry_t *entries;
};

struct vm_wasm_section_code_entry_local_t {
    uint64_t count;
    vm_wasm_lang_type_t type;
};

struct vm_wasm_section_code_entry_t {
    uint64_t num_locals;
    vm_wasm_section_code_entry_local_t *locals;
    uint64_t num_instrs;
    vm_wasm_instr_t *instrs;
};

struct vm_wasm_section_code_t {
    uint64_t num_entries;
    vm_wasm_section_code_entry_t *entries;
};

struct vm_wasm_section_data_entry_t {
    uint64_t index;
    vm_wasm_instr_t offset;
    uint64_t size;
    uint8_t *data;
};

struct vm_wasm_section_data_t {
    uint64_t num_entries;
    vm_wasm_section_data_entry_t *entries;
};

struct vm_wasm_module_t {

};

uint64_t vm_wasm_parse_uleb(FILE *in);
int64_t vm_wasm_parse_sleb(FILE *in);
uint8_t vm_wasm_parse_byte(FILE *in);
vm_wasm_preamble_t vm_wasm_parse_preamble(FILE *in);
vm_wasm_section_header_t vm_wasm_parse_section_header(FILE *in);
uint8_t vm_wasm_parse_varuint1(FILE *in);
int32_t vm_wasm_parse_varuint32(FILE *in);
int64_t vm_wasm_parse_varuint64(FILE *in);
uint32_t vm_wasm_parse_uint32(FILE *in);
uint64_t vm_wasm_parse_uint64(FILE *in);
vm_wasm_lang_type_t vm_wasm_parse_block_type(FILE *in);
vm_wasm_br_table_t vm_wasm_parse_br_table(FILE *in);
vm_wasm_call_indirect_t vm_wasm_parse_call_indirect(FILE *in);
vm_wasm_memory_immediate_t vm_wasm_parse_memory_immediate(FILE *in);
vm_wasm_type_function_t vm_wasm_parse_type_function(FILE *in);
vm_wasm_type_table_t vm_wasm_parse_type_table(FILE *in);
vm_wasm_type_global_t vm_wasm_parse_type_global(FILE *in);
vm_wasm_type_memory_t vm_wasm_parse_type_memory(FILE *in);
vm_wasm_type_t vm_wasm_parse_type(FILE *in, vm_wasm_lang_type_t tag);
vm_wasm_section_custom_t vm_wasm_parse_section_custom(FILE *in, vm_wasm_section_header_t header);
vm_wasm_section_type_t vm_wasm_parse_section_type(FILE *in);
vm_wasm_section_import_t vm_wasm_parse_section_import(FILE *in);
vm_wasm_section_function_t vm_wasm_parse_section_function(FILE *in);
vm_wasm_section_table_t vm_wasm_parse_section_table(FILE *in);
vm_wasm_section_memory_t vm_wasm_parse_section_memory(FILE *in);
vm_wasm_section_global_t vm_wasm_parse_section_global(FILE *in);
vm_wasm_section_start_t vm_wasm_parse_section_start(FILE *in);
vm_wasm_section_element_t vm_wasm_parse_section_element(FILE *in);
vm_wasm_section_code_t vm_wasm_parse_section_code(FILE *in);
vm_wasm_section_data_t vm_wasm_parse_section_data(FILE *in);
vm_wasm_instr_t vm_wasm_parse_instr(FILE *in);
vm_wasm_module_t vm_wasm_parse_module(FILE *in);

#define vm_wasm_parse_type_init_expr(in) (vm_wasm_parse_instr(in))
