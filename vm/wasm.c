
#include "./wasm.h"

#include <stdint.h>

const char *const vm_wasm_lang_types[] = {
    [0x7f] = "i32",
    [0x7e] = "i64",
    [0x7d] = "f32",
    [0x7c] = "f64",
    [0x70] = "anyFunc",
    [0x60] = "func",
    [0x40] = "block_type",
};

const char *const vm_wasm_external_kind[] = {
    [0] = "function",
    [1] = "table",
    [2] = "memory",
    [3] = "global",
};

const char *const vm_wasm_section_ids[] = {
    [0] = "custom",
    [1] = "type",
    [2] = "import",
    [3] = "function",
    [4] = "table",
    [5] = "memory",
    [6] = "global",
    [7] = "export",
    [8] = "start",
    [9] = "element",
    [10] = "code",
    [11] = "data",
};

const char *vm_wasm_opcodes[] = {
    // flow control
    [0x0] = "unreachable",
    [0x1] = "nop",
    [0x2] = "block",
    [0x3] = "loop",
    [0x4] = "if",
    [0x5] = "else",
    [0xb] = "end",
    [0xc] = "br",
    [0xd] = "br_if",
    [0xe] = "br_table",
    [0xf] = "return",

    // calls
    [0x10] = "call",
    [0x11] = "call_indirect",

    // Parametric operators
    [0x1a] = "drop",
    [0x1b] = "select",

    // Varibale access
    [0x20] = "get_local",
    [0x21] = "set_local",
    [0x22] = "tee_local",
    [0x23] = "get_global",
    [0x24] = "set_global",

    // Memory-related operators
    [0x28] = "i32.load",
    [0x29] = "i64.load",
    [0x2a] = "f32.load",
    [0x2b] = "f64.load",
    [0x2c] = "i32.load8_s",
    [0x2d] = "i32.load8_u",
    [0x2e] = "i32.load16_s",
    [0x2f] = "i32.load16_u",
    [0x30] = "i64.load8_s",
    [0x31] = "i64.load8_u",
    [0x32] = "i64.load16_s",
    [0x33] = "i64.load16_u",
    [0x34] = "i64.load32_s",
    [0x35] = "i64.load32_u",
    [0x36] = "i32.store",
    [0x37] = "i64.store",
    [0x38] = "f32.store",
    [0x39] = "f64.store",
    [0x3a] = "i32.store8",
    [0x3b] = "i32.store16",
    [0x3c] = "i64.store8",
    [0x3d] = "i64.store16",
    [0x3e] = "i64.store32",
    [0x3f] = "current_memory",
    [0x40] = "grow_memory",

    // Constants
    [0x41] = "i32.const",
    [0x42] = "i64.const",
    [0x43] = "f32.const",
    [0x44] = "f64.const",

    // Comparison operators
    [0x45] = "i32.eqz",
    [0x46] = "i32.eq",
    [0x47] = "i32.ne",
    [0x48] = "i32.lt_s",
    [0x49] = "i32.lt_u",
    [0x4a] = "i32.gt_s",
    [0x4b] = "i32.gt_u",
    [0x4c] = "i32.le_s",
    [0x4d] = "i32.le_u",
    [0x4e] = "i32.ge_s",
    [0x4f] = "i32.ge_u",
    [0x50] = "i64.eqz",
    [0x51] = "i64.eq",
    [0x52] = "i64.ne",
    [0x53] = "i64.lt_s",
    [0x54] = "i64.lt_u",
    [0x55] = "i64.gt_s",
    [0x56] = "i64.gt_u",
    [0x57] = "i64.le_s",
    [0x58] = "i64.le_u",
    [0x59] = "i64.ge_s",
    [0x5a] = "i64.ge_u",
    [0x5b] = "f32.eq",
    [0x5c] = "f32.ne",
    [0x5d] = "f32.lt",
    [0x5e] = "f32.gt",
    [0x5f] = "f32.le",
    [0x60] = "f32.ge",
    [0x61] = "f64.eq",
    [0x62] = "f64.ne",
    [0x63] = "f64.lt",
    [0x64] = "f64.gt",
    [0x65] = "f64.le",
    [0x66] = "f64.ge",

    // Numeric operators
    [0x67] = "i32.clz",
    [0x68] = "i32.ctz",
    [0x69] = "i32.popcnt",
    [0x6a] = "i32.add",
    [0x6b] = "i32.sub",
    [0x6c] = "i32.mul",
    [0x6d] = "i32.div_s",
    [0x6e] = "i32.div_u",
    [0x6f] = "i32.rem_s",
    [0x70] = "i32.rem_u",
    [0x71] = "i32.and",
    [0x72] = "i32.or",
    [0x73] = "i32.xor",
    [0x74] = "i32.shl",
    [0x75] = "i32.shr_s",
    [0x76] = "i32.shr_u",
    [0x77] = "i32.rotl",
    [0x78] = "i32.rotr",
    [0x79] = "i64.clz",
    [0x7a] = "i64.ctz",
    [0x7b] = "i64.popcnt",
    [0x7c] = "i64.add",
    [0x7d] = "i64.sub",
    [0x7e] = "i64.mul",
    [0x7f] = "i64.div_s",
    [0x80] = "i64.div_u",
    [0x81] = "i64.rem_s",
    [0x82] = "i64.rem_u",
    [0x83] = "i64.and",
    [0x84] = "i64.or",
    [0x85] = "i64.xor",
    [0x86] = "i64.shl",
    [0x87] = "i64.shr_s",
    [0x88] = "i64.shr_u",
    [0x89] = "i64.rotl",
    [0x8a] = "i64.rotr",
    [0x8b] = "f32.abs",
    [0x8c] = "f32.neg",
    [0x8d] = "f32.ceil",
    [0x8e] = "f32.floor",
    [0x8f] = "f32.trunc",
    [0x90] = "f32.nearest",
    [0x91] = "f32.sqrt",
    [0x92] = "f32.add",
    [0x93] = "f32.sub",
    [0x94] = "f32.mul",
    [0x95] = "f32.div",
    [0x96] = "f32.min",
    [0x97] = "f32.max",
    [0x98] = "f32.copysign",
    [0x99] = "f64.abs",
    [0x9a] = "f64.neg",
    [0x9b] = "f64.ceil",
    [0x9c] = "f64.floor",
    [0x9d] = "f64.trunc",
    [0x9e] = "f64.nearest",
    [0x9f] = "f64.sqrt",
    [0xa0] = "f64.add",
    [0xa1] = "f64.sub",
    [0xa2] = "f64.mul",
    [0xa3] = "f64.div",
    [0xa4] = "f64.min",
    [0xa5] = "f64.max",
    [0xa6] = "f64.copysign",

    // Conversions
    [0xa7] = "i32.wrap/i64",
    [0xa8] = "i32.trunc_s/f32",
    [0xa9] = "i32.trunc_u/f32",
    [0xaa] = "i32.trunc_s/f64",
    [0xab] = "i32.trunc_u/f64",
    [0xac] = "i64.extend_s/i32",
    [0xad] = "i64.extend_u/i32",
    [0xae] = "i64.trunc_s/f32",
    [0xaf] = "i64.trunc_u/f32",
    [0xb0] = "i64.trunc_s/f64",
    [0xb1] = "i64.trunc_u/f64",
    [0xb2] = "f32.convert_s/i32",
    [0xb3] = "f32.convert_u/i32",
    [0xb4] = "f32.convert_s/i64",
    [0xb5] = "f32.convert_u/i64",
    [0xb6] = "f32.demote/f64",
    [0xb7] = "f64.convert_s/i32",
    [0xb8] = "f64.convert_u/i32",
    [0xb9] = "f64.convert_s/i64",
    [0xba] = "f64.convert_u/i64",
    [0xbb] = "f64.promote/f32",

    // Reinterpretations
    [0xbc] = "i32.reinterpret/f32",
    [0xbd] = "i64.reinterpret/f64",
    [0xbe] = "f32.reinterpret/i32",
    [0xbf] = "f64.reinterpret/i64",
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
        .name = vm_wasm_section_ids[id],
    };
}

uint8_t vm_wasm_parse_varuint1(FILE *in) {
    return vm_wasm_parse_byte(in);
}

int32_t vm_wasm_parse_varuint32(FILE *in) {
    return (uint32_t)vm_wasm_parse_sleb(in);
}

int64_t vm_wasm_parse_varuint64(FILE *in) {
    return (uint64_t)vm_wasm_parse_sleb(in);
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

const char *vm_wasm_parse_block_type(FILE *in) {
    return vm_wasm_lang_types[vm_wasm_parse_byte(in)];
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
        .element_type = vm_wasm_lang_types[vm_wasm_parse_byte(in)],
        .limits = vm_wasm_parse_type_memory(in),
    };
}

vm_wasm_type_global_t vm_wasm_parse_type_global(FILE *in) {
    return (vm_wasm_type_global_t){
        .content_type = vm_wasm_lang_types[vm_wasm_parse_byte(in)],
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

vm_wasm_type_t vm_wasm_parse_type(FILE *in, const char *tag) {
    if (!strcmp(tag, "function")) {
        return (vm_wasm_type_t) {
            .function = vm_wasm_parse_type_function(in),
            .tag = tag,
        };
    }
    if (!strcmp(tag, "table")) {
        return (vm_wasm_type_t) {
            .table = vm_wasm_parse_type_table(in),
            .tag = tag,
        };
    }
    if (!strcmp(tag, "global")) {
        return (vm_wasm_type_t) {
            .global = vm_wasm_parse_type_global(in),
            .tag = tag,
        };
    }
    if (!strcmp(tag, "memory")) {
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
        uint8_t type = vm_wasm_parse_byte(in);
        const char *form = vm_wasm_lang_types[type];
        uint64_t num_params = vm_wasm_parse_uleb(in);
        const char **params = vm_malloc(sizeof(const char *) * num_params);
        for (uint64_t j = 0; j < num_params; j++) {
            params[j] = vm_wasm_lang_types[vm_wasm_parse_byte(in)];
        }
        uint64_t num_returns = vm_wasm_parse_uleb(in);
        const char *return_type = NULL;
        if (num_returns) {
            return_type = vm_wasm_lang_types[vm_wasm_parse_byte(in)];
        }
        entries[i] = (vm_wasm_section_type_entry_t) {
            .form = form,
            .num_params = num_params,
            .params = params,
            .num_returns = num_returns,
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
        const char *kind = vm_wasm_external_kind[vm_wasm_parse_byte(in)];
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
    return (vm_wasm_section_code_t){

    };
}

vm_wasm_section_data_t vm_wasm_parse_section_data(FILE *in) {
    return (vm_wasm_section_data_t){

    };
}

vm_wasm_instr_t vm_wasm_parse_instr(FILE *in) {
    return (vm_wasm_instr_t){

    };
}

vm_wasm_module_t vm_wasm_parse_module(FILE *in) {
    return (vm_wasm_module_t){

    };
}
