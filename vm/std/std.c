
#include "./std.h"

#include "./io.h"
#include "../ast/ast.h"
#include "../obj.h"

void vm_std_os_exit(vm_std_closure_t *closure, vm_std_value_t *args) {
    exit((int)vm_value_to_i64(args[0]));
}

vm_ast_node_t vm_lang_lua_parse(vm_config_t *config, const char *str);
void vm_ast_comp_more(vm_ast_node_t node, vm_blocks_t *blocks);

void vm_std_load(vm_std_closure_t *closure, vm_std_value_t *args) {
    if (args[0].tag != VM_TAG_STRING) {
        *args = vm_std_value_cerr("cannot load non-string value");
        return;
    }
    const char *str = (const char *) args[0].value.string->buf;
    vm_ast_node_t node = vm_lang_lua_parse(closure->config, str);
    vm_ast_comp_more(node, closure->blocks);
    
    vm_std_value_t *vals = vm_malloc(sizeof(vm_std_value_t) * 2);
    vals[0] = (vm_std_value_t) {
        .tag = VM_TAG_I32,
        .value.i32 = 1,
    };
    vals += 1;
    vals[0] = (vm_std_value_t) {
        .tag = VM_TAG_FUN,
        .value.i32 = (int32_t) closure->blocks->entry->id,
    };
    // vm_io_buffer_t buf = {0};
    // vm_io_format_blocks(&buf, closure->blocks);
    // printf("%s\n", buf.buf);
    *args = (vm_std_value_t) {
        .tag = VM_TAG_CLOSURE,
        .value.closure = vals,
    };
}

void vm_std_assert(vm_std_closure_t *closure, vm_std_value_t *args) {
    vm_std_value_t val = args[0];
    if (val.tag == VM_TAG_NIL || (val.tag == VM_TAG_BOOL && !val.value.b)) {
        vm_std_value_t msg = args[1];
        vm_io_buffer_t *buf = vm_io_buffer_from_str(0, NULL);
        vm_io_print_lit(buf, msg);
        *args = (vm_std_value_t){
            .tag = VM_TAG_ERROR,
            .value.string = buf,
        };
    } else {
        *args = (vm_std_value_t){
            .tag = VM_TAG_NIL,
        };
    }
}

void vm_std_vm_closure(vm_std_closure_t *closure, vm_std_value_t *args) {
    int64_t nargs = 0;
    for (size_t i = 0; args[i].tag != 0; i++) {
        nargs += 1;
    }
    if (nargs == 0 || args[0].tag != VM_TAG_FUN) {
        *args = (vm_std_value_t){
            .tag = VM_TAG_NIL,
        };
        return;
    }
    vm_std_value_t *vals = vm_malloc(sizeof(vm_std_value_t) * (nargs + 1));
    vals[0] = (vm_std_value_t) {
        .tag = VM_TAG_I32,
        .value.i32 = (int32_t) nargs,
    };
    vals += 1;
    for (size_t i = 0; args[i].tag != 0; i++) {
        vals[i] = args[i];
    }
    *args = (vm_std_value_t){
        .tag = VM_TAG_CLOSURE,
        .value.closure = vals,
    };
    return;
}

void vm_std_vm_print(vm_std_closure_t *closure, vm_std_value_t *args) {
    for (size_t i = 0; args[i].tag; i++) {
        vm_io_buffer_t buf = {0};
        vm_io_debug(&buf, 0, "", args[i], NULL);
        printf("%.*s", (int) buf.len, buf.buf);
    }
}

void vm_std_vm_concat(vm_std_closure_t *closure, vm_std_value_t *args) {
    vm_io_buffer_t *buf = vm_io_buffer_from_str(0, NULL);
    for (size_t i = 0; args[i].tag != VM_TAG_UNK; i++) {
        if (
            args[i].tag == VM_TAG_STRING
        ) {
            vm_io_buffer_format(buf, "%.*s", (int) args[i].value.string->len, args[i].value.string->buf);
        } else if (
            args[i].tag == VM_TAG_I8
            || args[i].tag == VM_TAG_I16
            || args[i].tag == VM_TAG_I32
            || args[i].tag == VM_TAG_I64
            || args[i].tag == VM_TAG_F32
            || args[i].tag == VM_TAG_F64
        ) {
            vm_io_print_lit(buf, args[i]);
        } else {
            vm_io_buffer_t *ebuf = vm_io_buffer_from_cstr("attempt to concatenate a ");
            vm_io_format_tag(ebuf, args[i].tag);
            vm_io_buffer_format(ebuf, " value");
            *args = (vm_std_value_t) {
                .tag = VM_TAG_ERROR,
                .value.string = ebuf,
            };
            return;
        }
    }
    *args = (vm_std_value_t) {
        .tag = VM_TAG_STRING,
        .value.string = buf,
    };
    return;
}

void vm_std_type(vm_std_closure_t *closure, vm_std_value_t *args) {
    const char *ret = "unknown";
    switch (args[0].tag) {
        case VM_TAG_NIL: {
            ret = "nil";
            break;
        }
        case VM_TAG_BOOL: {
            ret = "boolean";
            break;
        }
        case VM_TAG_I8: {
            ret = "number";
            break;
        }
        case VM_TAG_I16: {
            ret = "number";
            break;
        }
        case VM_TAG_I32: {
            ret = "number";
            break;
        }
        case VM_TAG_I64: {
            ret = "number";
            break;
        }
        case VM_TAG_F32: {
            ret = "number";
            break;
        }
        case VM_TAG_F64: {
            ret = "number";
            break;
        }
        case VM_TAG_STRING: {
            ret = "string";
            break;
        }
        case VM_TAG_CLOSURE: {
            ret = "function";
            break;
        }
        case VM_TAG_FUN: {
            ret = "function";
            break;
        }
        case VM_TAG_TAB: {
            ret = "table";
            break;
        }
        case VM_TAG_FFI: {
            ret = "function";
            break;
        }
        case VM_TAG_ERROR: {
            ret = "string";
            break;
        }
    }
    *args = vm_std_value_cstr(ret);
}

void vm_value_buffer_tostring(vm_io_buffer_t *buf, vm_std_value_t value) {
    switch (value.tag) {
        case VM_TAG_NIL: {
            vm_io_buffer_format(buf, "nil");
            break;
        }
        case VM_TAG_BOOL: {
            vm_io_buffer_format(buf, "%s", value.value.b ? "true" : "false");
            break;
        }
        case VM_TAG_I8: {
            vm_io_buffer_format(buf, "%" PRIi8, value.value.i8);
            break;
        }
        case VM_TAG_I16: {
            vm_io_buffer_format(buf, "%" PRIi16, value.value.i16);
            break;
        }
        case VM_TAG_I32: {
            vm_io_buffer_format(buf, "%" PRIi32, value.value.i32);
            break;
        }
        case VM_TAG_I64: {
            vm_io_buffer_format(buf, "%" PRIi64, value.value.i64);
            break;
        }
        case VM_TAG_F32: {
            vm_io_buffer_format(buf, VM_FORMAT_FLOAT, value.value.f32);
            break;
        }
        case VM_TAG_F64: {
            vm_io_buffer_format(buf, VM_FORMAT_FLOAT, value.value.f64);
            break;
        }
        case VM_TAG_STRING: {
            vm_io_buffer_format(buf, "%.*s", (int) value.value.string->len, value.value.string->buf);
            break;
        }
        case VM_TAG_CLOSURE: {
            vm_io_buffer_format(buf, "<function: %p>", value.value.closure);
            break;
        }
        case VM_TAG_FUN: {
            vm_io_buffer_format(buf, "<code: %p>", value.value.all);
            break;
        }
        case VM_TAG_TAB: {
            vm_io_buffer_format(buf, "<table: %p>", value.value.table);
            break;
        }
        case VM_TAG_FFI: {
            vm_io_buffer_format(buf, "<function: %p>", value.value.all);
            break;
        }
    }
}

void vm_std_tostring(vm_std_closure_t *closure, vm_std_value_t *args) {
    vm_io_buffer_t *out = vm_io_buffer_from_str(0, NULL);
    vm_value_buffer_tostring(out, *args);
    *args = (vm_std_value_t) {
        .tag = VM_TAG_STRING,
        .value.string = out,
    };
}

void vm_std_print(vm_std_closure_t *closure, vm_std_value_t *args) {
    vm_std_value_t *ret = args;
    vm_io_buffer_t out = {0};
    bool first = true;
    while (args->tag != 0) {
        if (!first) {
            vm_io_buffer_format(&out, "\t");
        }
        vm_value_buffer_tostring(&out, *args++);
        first = false;
    }
    fprintf(stdout, "%.*s\n", (int) out.len, out.buf);
    *ret = (vm_std_value_t){
        .tag = VM_TAG_NIL,
    };
}

vm_table_t *vm_std_new(void) {
    vm_table_t *std = vm_table_new();

    {
        vm_table_t *io = vm_table_new();
        vm_table_set_value(std, vm_std_value_cstr("io"), vm_std_value_table(io));
    }

    {
        vm_table_t *vm = vm_table_new();
        vm_table_set_value(vm, vm_std_value_cstr("print"), vm_std_value_ffi(&vm_std_vm_print));
        {
            vm_table_t *vm_ver = vm_table_new();
            vm_table_set_value(vm, vm_std_value_cstr("version"), vm_std_value_table(vm_ver));
        }
        vm_table_set_value(std, vm_std_value_cstr("vm"), vm_std_value_table(vm));
    }

    {
        vm_table_t *os = vm_table_new();
        vm_table_set_value(os, vm_std_value_cstr("exit"), vm_std_value_ffi(&vm_std_os_exit));
        vm_table_set_value(std, vm_std_value_cstr("os"), vm_std_value_table(os));
    }

    vm_table_set_value(std, vm_std_value_cstr("tostring"), vm_std_value_ffi(&vm_std_tostring));
    vm_table_set_value(std, vm_std_value_cstr("type"), vm_std_value_ffi(&vm_std_type));
    vm_table_set_value(std, vm_std_value_cstr("print"), vm_std_value_ffi(&vm_std_print));
    vm_table_set_value(std, vm_std_value_cstr("assert"), vm_std_value_ffi(&vm_std_assert));
    vm_table_set_value(std, vm_std_value_cstr("load"), vm_std_value_ffi(&vm_std_load));

    return std;
}
