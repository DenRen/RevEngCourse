#include <stdio.h>
#include <math.h>

typedef unsigned uint;

struct block {
    uint num_threads;
    uint num_threads_step;
    uint shared_mem_step;
    uint num_reg_step;
};

struct multiproc {
    uint num_threads;
    uint shared_mem_size;
    uint reg_size;
    uint num_regs;
    uint num_blocks;
};

struct gpu_desc {
    uint num_multiprocs;
    struct multiproc multiproc;
    struct block block;
};

uint calc_num_threads(const struct gpu_desc* gpu,
                      uint num_threads_per_block,
                      uint num_regs_per_thread,
                      uint shared_mem_per_block);

int main() {
    const struct gpu_desc fermi = {
        .num_multiprocs = 16,
        .multiproc = {
            .num_threads = 1536,
            .shared_mem_size = 49152,
            .reg_size = 4,
            .num_regs = 32768,
            .num_blocks = 8
        },
        .block = {
            .num_threads = 1024,
            .num_threads_step = 32,
            .shared_mem_step = 128,
            .num_reg_step = 2
        }
    };

    uint num_threads_per_block = 0;
    uint num_regs_per_thread = 0;
    uint shared_mem_per_block = 0;

    FILE* in = fopen("cuda.in", "r");
    if (in == NULL) {
        perror("fopen");
        return -1;
    }

    if (fscanf(in, "%u %u %u", &num_threads_per_block, &num_regs_per_thread, &shared_mem_per_block) != 3) {
        perror("scanf");

        fclose(in);
        return -1;
    }
    fclose(in);

    uint num_threads = calc_num_threads(&fermi, num_threads_per_block,
                                        num_regs_per_thread, shared_mem_per_block);

    uint useful_gpu_perc = (uint)round(100.0 * num_threads / fermi.multiproc.num_threads);

    FILE* out = fopen("cuda.out", "w");
    if (out == NULL) {
        perror("fopen");
        return -1;
    }

    fprintf(out, "%u\n", useful_gpu_perc);
    fclose(out);
}

uint min(uint a, uint b) {
    return a < b ? a : b;
}

uint div_up(uint dividend, uint divider) {
    return dividend / divider + (dividend % divider != 0);
}

uint round_up(uint dividend, uint divider) {
    return divider * div_up(dividend, divider);
}

uint calc_num_threads(const struct gpu_desc* gpu,
                      uint num_threads_per_block,
                      uint num_regs_per_thread,
                      uint shared_mem_per_block) {
    uint num_th_per_block_real = round_up(num_threads_per_block, gpu->block.num_threads_step);
    uint num_blocks_per_multiproc = min(gpu->multiproc.num_threads / num_th_per_block_real,
                                        gpu->multiproc.num_blocks);

    uint num_regs_per_thread_real = round_up(num_regs_per_thread, gpu->block.num_reg_step);
    uint num_regs_per_block = num_regs_per_thread_real * num_th_per_block_real;
    num_blocks_per_multiproc = min(num_blocks_per_multiproc, gpu->multiproc.num_regs / num_regs_per_block);

    if (shared_mem_per_block) {
        uint shared_mem_per_block_real = round_up(shared_mem_per_block, gpu->block.shared_mem_step);
        num_blocks_per_multiproc = min(num_blocks_per_multiproc,
                                       gpu->multiproc.shared_mem_size / shared_mem_per_block_real);
    }

    uint num_threads = num_blocks_per_multiproc * num_threads_per_block;
    return num_threads;
}