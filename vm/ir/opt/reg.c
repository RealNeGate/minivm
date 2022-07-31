#include "../build.h"

static inline size_t vm_ir_opt_alloc(uint8_t *used, size_t *regs, size_t reg)
{
    if (regs[reg] == SIZE_MAX)
    {
        size_t i = 0;
        while (used[i])
        {
            i += 1;
        }
        used[i] = 1;
        regs[reg] = i;
    }
    return regs[reg];
}

static inline void vm_ir_opt_block(vm_ir_block_t *block)
{
    uint8_t *used = vm_alloc0(sizeof(uint8_t) * block->nregs);
    size_t *regs = vm_alloc0(sizeof(size_t) * block->nregs);
    for (size_t i = 0; i < block->nregs; i++)
    {
        regs[i] = SIZE_MAX;
    }
    for (size_t i = 0; i < 2; i++)
    {
        if (block->branch->pass[i] == NULL)
        {
            continue;
        }
        vm_ir_arg_t **pass = block->branch->pass[i];
        for (size_t j = 0; j < block->branch->targets[i]->nargs; j++)
        {
            if (pass[j]->type == VM_IR_ARG_REG)
            {
                pass[j]->reg = vm_ir_opt_alloc(used, regs, pass[j]->reg);
            }
        }
    }
    for (size_t i = 0; i < 2; i++)
    {
        if (block->branch->args[i] != NULL && block->branch->args[i]->type == VM_IR_ARG_REG)
        {
            block->branch->args[i]->reg = vm_ir_opt_alloc(used, regs, block->branch->args[i]->reg);
        }
    }
    for (ptrdiff_t i = block->len-1; i >= 0; i--)
    {
        vm_ir_instr_t *instr = block->instrs[i];
        if (instr->out && instr->out->type == VM_IR_ARG_REG)
        {
            size_t old = instr->out->reg;
            if (regs[old] == SIZE_MAX)
            {
                vm_ir_arg_free(instr->out);
                instr->out = NULL;
            }
            else
            {
                instr->out->reg = regs[old];
                used[regs[old]] = 0;
                regs[old] = SIZE_MAX;
            }
        }
        for (size_t j = 0; instr->args[j] != NULL; j++)
        {
            vm_ir_arg_t *arg = instr->args[j];
            if (arg->type == VM_IR_ARG_REG)
            {
                arg->reg = vm_ir_opt_alloc(used, regs, arg->reg);
            }
        }
    }
    size_t write = 0;
    for (size_t i = 0; i < block->nargs; i++)
    {
        if (regs[block->args[i]] != SIZE_MAX)
        {
            block->args[write++] = regs[block->args[i]];
        }
    }
    block->nargs = write;
    vm_free(used);
    vm_free(regs);
}

void vm_ir_opt_reg(size_t nblocks, vm_ir_block_t *blocks)
{
    for (size_t i = 0; i < nblocks; i++)
    {
        vm_ir_block_t *block = &blocks[i];
        if (block->id != i)
        {
            continue;
        }
        vm_ir_opt_block(block);
        // if (block->isfunc) {
        //     fprintf(stderr, "\nfunc .%zu(", i);
        // } else {
        //     fprintf(stderr, ".%zu(", i);
        // }
        // for (size_t i = 0; i < block->nargs; i++)
        // {
        //     if (i != 0)
        //     {
        //         fprintf(stderr, " ");
        //     }
        //     fprintf(stderr, "r%zu", block->args[i]);
        // }
        // fprintf(stderr, ")\n");
        // vm_ir_print_block(stderr, block);
    }
}
