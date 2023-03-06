#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef REGISTERS
#define REGISTERS 4
#endif

#define CPU_MAX_REG_NUM 4

#if REGISTERS >= CPU_MAX_REG_NUM
#define CPU_NUM_REG CPU_MAX_REG_NUM
#else
#define CPU_NUM_REG REGISTERS
#endif

typedef uint8_t reg_t;

typedef struct {
    reg_t regs[CPU_NUM_REG];
} cpu_t;

enum CPU_COMMANDS {
    CPU_HLT,
    CPU_ADD,
    CPU_SUB,
    CPU_MOV,
    CPU_IR,
    CPU_RESERVED_COMMAND
};

enum CPU_REGISTERS {
    CPU_MIN_REG = 5,
    CPU_MAX_REG = CPU_MIN_REG + CPU_NUM_REG - 1
};

enum CPU_ERRORS {
    CPU_ERR_GOOD = 0,
    CPU_ERR_REG_INDEX_OUT_OF_RANGE,
    CPU_ERR_ILLEGAL_INSTRACTION
};

reg_t read_code(int* perr) {
    reg_t code = 0;
    int err = scanf("%hhu", &code);
    if (err == EOF || err == 0) {
        *perr = 1;
    }

    return code;
}

void read_n_codes(reg_t* codes, unsigned num_codes, int* perr) {
    for (unsigned i_code = 0; i_code < num_codes && *perr; ++i_code) {
        codes[i_code] = read_code(perr);
    }
}

void read_regs(reg_t* regs, unsigned num_regs, int* perr) {
    for (unsigned i_reg = 0; i_reg < num_regs; ++i_reg) {
        reg_t reg = read_code(perr);
        if (reg < CPU_MIN_REG || reg > CPU_MAX_REG) {
            *perr = CPU_ERR_REG_INDEX_OUT_OF_RANGE;
            return;
        }

        regs[i_reg] = reg - CPU_MIN_REG;
    }
}

int make_cpu_takt(cpu_t* cpu, reg_t code, int* perr) {
    switch (code) {
        case CPU_HLT: {
            return 1;
        }
        case CPU_ADD: {
            reg_t regs[2] = {};
            read_regs(regs, 2, perr);
            if (*perr) {
                return -1;
            }

            cpu->regs[regs[0]] = cpu->regs[regs[0]] + cpu->regs[regs[1]];
            break;
        }
        case CPU_SUB: {
            reg_t regs[2] = {};
            read_regs(regs, 2, perr);
            if (*perr) {
                return -1;
            }

            cpu->regs[regs[0]] = cpu->regs[regs[0]] - cpu->regs[regs[1]];
            break;
        }
        case CPU_MOV: {
            reg_t reg = 0;
            read_regs(&reg, 1, perr);
            if (*perr) {
                return -1;
            }

            reg_t val = read_code(perr);
            if (*perr) {
                return -1;
            }

            cpu->regs[reg] = val;
            break;
        }
        case CPU_IR: {
            for (unsigned i = 0; i + 1 < CPU_NUM_REG; ++i) {
                printf("%hhu ", cpu->regs[i]);
            }
            printf("%hhu\n", cpu->regs[CPU_NUM_REG - 1]);
            break;
        }
        default: {
            *perr = CPU_ERR_ILLEGAL_INSTRACTION;
            return -1;
            break;
        }
    }

    return 0;
}

int main() {
    cpu_t cpu = {};
    int err = CPU_ERR_GOOD;
    int* const perr = &err;

    while (1) {
        reg_t code = read_code(perr);
        if (err) {
            return -1;
        }

        if (make_cpu_takt(&cpu, code, perr)) {
            if (code == CPU_HLT) {
                return 0;
            }

            printf("-1\n");
            return 0;
        }
    }
}