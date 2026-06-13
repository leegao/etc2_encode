/*
 * Copyright (C) 2021 Collabora Ltd.
 * SPDX-License-Identifier: MIT
 */

#ifndef __DISASM_H
#define __DISASM_H

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmpbe_chunks.h"
void va_disasm_instr(FILE *fp, uint64_t instr, const cmpbe_chunk_CMMN *ctx, unsigned instr_idx, const uint32_t *first_def_idx);
void disassemble_valhall(FILE *fp, const void *code, size_t size, bool verbose, const cmpbe_chunk_CMMN *ctx);

#endif
