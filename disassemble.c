// AUTO-GENERATED - DO NOT EDIT

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "disassemble.h"
#include "cmpbe_chunks.h"

#define BIT(b)          (1ull << (b))
#define MASK(count)    ((1ull << (count)) - 1)
#define SEXT(b, count) ((b ^ BIT(count - 1)) - BIT(count - 1))
#define UNUSED          __attribute__((unused))

#define VA_SRC_UNIFORM_TYPE 0x2
#define VA_SRC_IMM_TYPE     0x3

#define MAX_GPR_REGS 64
#define MAX_STACK_SLOTS 256

typedef struct {
   uint64_t raw_word;
   uint64_t gen_mask;
   uint64_t def_mask;
   int32_t  stack_slot;
   bool     is_store;
   bool     is_load;
   bool     is_reconverge;
   bool     is_branch;
   int32_t  branch_target_idx;

   uint32_t num_incoming_branches;
   uint32_t incoming_branch_offsets[16];

   uint64_t live_regs_in;
   uint64_t live_regs_out;
   uint8_t  live_stack_in[MAX_STACK_SLOTS];
   uint8_t  live_stack_out[MAX_STACK_SLOTS];
} AnalyzedInstruction;

UNUSED static const char *valhall_flow[] = {
   "",
   ".wait0",
   ".wait1",
   ".wait01",
   ".wait2",
   ".wait02",
   ".wait12",
   ".wait012",
   ".wait0126",
   ".wait",
   ".reconverge",
   ".reserved",
   ".wait_resource",
   ".discard",
   ".reserved",
   ".end",
};

UNUSED static const char *valhall_fau_special_page_0[] = {
   ".reserved",
   ".reserved",
   ".warp_id",
   ".reserved",
   ".framebuffer_size",
   ".atest_datum",
   ".sample",
   ".reserved",
   ".blend_descriptor_0",
   ".blend_descriptor_1",
   ".blend_descriptor_2",
   ".blend_descriptor_3",
   ".blend_descriptor_4",
   ".blend_descriptor_5",
   ".blend_descriptor_6",
   ".blend_descriptor_7",
};

UNUSED static const char *valhall_fau_special_page_1[] = {
   ".reserved",
   ".thread_local_pointer",
   ".reserved",
   ".workgroup_local_pointer",
   ".reserved",
   ".reserved",
   ".reserved",
   ".resource_table_pointer",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
};

UNUSED static const char *valhall_fau_special_page_3[] = {
   ".reserved",
   ".lane_id",
   ".reserved",
   ".core_id",
   ".shader_output",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".program_counter",
};

UNUSED static const char *valhall_swizzles_8_bit[] = {
   "",
   ".b3210",
   ".b0101",
   ".b2323",
   ".b0000",
   ".b1111",
   ".b2222",
   ".b3333",
   ".b2301",
   ".b1032",
   ".b0011",
   ".b2233",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
};

UNUSED static const char *valhall_lanes_8_bit[] = {
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".b00",
   ".b11",
   ".b22",
   ".b33",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
};

UNUSED static const char *valhall_half_swizzles_8_bit[] = {
   ".b00",
   ".b10",
   ".b20",
   ".b30",
   ".b01",
   ".b11",
   ".b21",
   ".b31",
   ".b02",
   ".b12",
   ".b22",
   ".b32",
   ".b03",
   ".b13",
   ".b23",
   ".b33",
};

UNUSED static const char *valhall_swizzles_16_bit[] = {
   ".h00",
   ".h10",
   "",
   ".h11",
   ".b00",
   ".b20",
   ".b02",
   ".b22",
   ".b11",
   ".b31",
   ".b13",
   ".b33",
   ".b01",
   ".b23",
   ".reserved",
   ".reserved",
};

UNUSED static const char *valhall_swizzles_32_bit[] = {
   "",
   ".reserved",
   ".h0",
   ".h1",
   ".b0",
   ".b1",
   ".b2",
   ".b3",
};

UNUSED static const char *valhall_swizzles_64_bit[] = {
   "",
   ".reserved",
   ".h0",
   ".h1",
   ".b0",
   ".b1",
   ".b2",
   ".b3",
   ".w0",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
};

UNUSED static const char *valhall_lane_8_bit[] = {
   ".b0",
   ".b1",
   ".b2",
   ".b3",
};

UNUSED static const char *valhall_combine[] = {
   "",
   ".h0",
   ".h1",
   ".and",
   ".lowbits",
};

UNUSED static const char *valhall_lane_16_bit[] = {
   ".h0",
   ".h1",
};

UNUSED static const char *valhall_load_lane_8_bit[] = {
   "",
   ".b1",
   ".b2",
   ".b3",
   ".h0",
   ".h1",
   ".w0",
   ".d0",
};

UNUSED static const char *valhall_load_lane_16_bit[] = {
   "",
   ".h1",
   ".w0",
   ".d0",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
};

UNUSED static const char *valhall_load_lane_24_bit[] = {
   "",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
};

UNUSED static const char *valhall_load_lane_32_bit[] = {
   "",
   ".d0",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
};

UNUSED static const char *valhall_load_lane_48_bit[] = {
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   "",
   ".reserved",
   ".reserved",
   ".reserved",
};

UNUSED static const char *valhall_load_lane_64_bit[] = {
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   "",
};

UNUSED static const char *valhall_load_lane_96_bit[] = {
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   "",
   ".reserved",
};

UNUSED static const char *valhall_load_lane_128_bit[] = {
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   "",
};

UNUSED static const char *valhall_round_mode[] = {
   "",
   ".rtp",
   ".rtn",
   ".rtz",
};

UNUSED static const char *valhall_result_type[] = {
   ".i1",
   ".f1",
   ".m1",
   ".u1",
};

UNUSED static const char *valhall_widen[] = {
   "",
   ".h0",
   ".h1",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
};

UNUSED static const char *valhall_clamp[] = {
   "",
   ".clamp_0_inf",
   ".clamp_m1_1",
   ".clamp_0_1",
};

UNUSED static const char *valhall_condition[] = {
   ".eq",
   ".gt",
   ".ge",
   ".ne",
   ".lt",
   ".le",
   ".gtlt",
   ".total",
};

UNUSED static const char *valhall_dimension[] = {
   ".1d",
   ".2d",
   ".3d",
   ".cube",
};

UNUSED static const char *valhall_lod_mode[] = {
   ".zero",
   ".computed",
   ".reserved",
   ".reserved",
   ".explicit",
   ".computed_bias",
   ".grdesc",
   ".reserved",
};

UNUSED static const char *valhall_register_format[] = {
   ".auto",
   ".reserved",
   ".f32",
   ".f16",
   ".s32",
   ".s16",
   ".u32",
   ".u16",
};

UNUSED static const char *valhall_staging_register_count[] = {
   ".sr0",
   ".sr1",
   ".sr2",
   ".sr3",
   ".sr4",
   ".sr5",
   ".sr6",
   ".sr7",
};

UNUSED static const char *valhall_staging_register_write_count[] = {
   ".write1",
   ".write2",
   ".write3",
   ".write4",
   ".write5",
   ".write6",
   ".write7",
   ".write8",
};

UNUSED static const char *valhall_write_mask[] = {
   ".reserved",
   ".r",
   ".g",
   ".rg",
   ".b",
   ".rb",
   ".gb",
   ".rgb",
   ".a",
   ".ra",
   ".ga",
   ".rga",
   ".ba",
   ".rba",
   ".gba",
   "",
};

UNUSED static const char *valhall_fetch_component[] = {
   ".gather4_r",
   ".gather4_g",
   ".gather4_b",
   ".gather4_a",
};

UNUSED static const char *valhall_register_type[] = {
   ".reserved",
   ".f",
   ".u",
   ".s",
};

UNUSED static const char *valhall_register_width[] = {
   ".16",
   ".32",
};

UNUSED static const char *valhall_varying_texture_register_width[] = {
   ".16",
   ".32",
   ".16.32",
   ".32.32",
};

UNUSED static const char *valhall_vector_size[] = {
   "",
   ".v2",
   ".v3",
   ".v4",
};

UNUSED static const char *valhall_slot[] = {
   ".slot0",
   ".slot1",
   ".slot2",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".slot7",
};

UNUSED static const char *valhall_memory_access[] = {
   "",
   ".istream",
   ".estream",
   ".force",
};

UNUSED static const char *valhall_subgroup_size[] = {
   ".subgroup2",
   ".subgroup4",
   ".subgroup8",
   "",
};

UNUSED static const char *valhall_lane_operation[] = {
   "",
   ".xor",
   ".accumulate",
   ".shift",
};

UNUSED static const char *valhall_inactive_result[] = {
   "",
   ".umax",
   ".i1",
   ".v2i1",
   ".smin",
   ".smax",
   ".v2smin",
   ".v2smax",
   ".v4smin",
   ".v4smax",
   ".f1",
   ".v2f1",
   ".infn",
   ".inf",
   ".v2infn",
   ".v2inf",
};

UNUSED static const char *valhall_mux[] = {
   ".neg",
   "",
   ".fp_zero",
   ".bit",
};

UNUSED static const char *valhall_sample_mode[] = {
   ".center",
   ".centroid",
   ".sample",
   ".explicit",
};

UNUSED static const char *valhall_update_mode[] = {
   ".store",
   ".retrieve",
   ".reserved",
   ".clobber",
};

UNUSED static const char *valhall_sample_and_update_mode[] = {
   ".center_store",
   ".centroid_store",
   ".sample_store",
   ".explicit_store",
   ".center_clobber",
   ".reserved",
   ".sample_clobber",
   ".retrieve",
};

UNUSED static const char *valhall_source[] = {
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".cycle_counter",
   ".system_timestamp",
};

UNUSED static const char *valhall_source_format[] = {
   ".src_flat32",
   ".src_flat16",
   ".src_f32",
   ".src_f16",
};

UNUSED static const char *valhall_atomic_operation[] = {
   ".reserved",
   ".reserved",
   ".aadd",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".reserved",
   ".asmin",
   ".asmax",
   ".aumin",
   ".aumax",
   ".aand",
   ".aor",
   ".axor",
   ".axchg",
};

UNUSED static const char *valhall_atomic_operation_with_1[] = {
   ".ainc",
   ".adec",
   ".aumax1",
   ".asmax1",
   ".aor1",
};

UNUSED static const char *valhall_nan_mode[] = {
   ".none",
   ".flush_nan",
   ".quiet_nan",
};

static const uint32_t va_immediates[32] = {
   0x0,
   0xffffffff,
   0x7fffffff,
   0xfafcfdfe,
   0x1000000,
   0x80002000,
   0x70605030,
   0xc0b0a090,
   0x3020100,
   0x7060504,
   0xb0a0908,
   0xf0e0d0c,
   0x13121110,
   0x17161514,
   0x1b1a1918,
   0x1f1e1d1c,
   0x3f800000,
   0x3dcccccd,
   0x3ea2f983,
   0x3f317218,
   0x40490fdb,
   0x0,
   0x477fff00,
   0x5c005bf8,
   0x2e660000,
   0x34000000,
   0x38000000,
   0x3c000000,
   0x40000000,
   0x44000000,
   0x48000000,
   0x42480000,
};

static void
va_print_live_set_ranges(FILE *fp, const char *prefix, uint64_t mask)
{
   uint32_t total_vregs = 0;
   fprintf(fp, "// %s: ", prefix);

   if (mask == 0) {
      fprintf(fp, "none (0 vregs) */\n");
      return;
   }

   bool first_range = true;
   int start = -1;
   int end = -1;

   for (int r = 0; r <= MAX_GPR_REGS; r++) {
      bool is_set = (r < MAX_GPR_REGS) && ((mask & BIT(r)) != 0);

      if (is_set) {
         total_vregs++;
         if (start == -1) {
            start = r;
         }
         end = r;
      } else {
         if (start != -1) {
            if (!first_range) {
               fprintf(fp, ",");
            }
            if (start == end) {
               fprintf(fp, "r%d", start);
            } else {
               fprintf(fp, "r%d-r%d", start, end);
            }
            first_range = false;
            start = -1;
            end = -1;
         }
      }
   }

   fprintf(fp, " (%u vregs)\n", total_vregs);
}

const char *
va_get_resource_name(const cmpbe_chunk_CMMN *ctx, unsigned type, unsigned value, unsigned fau_page)
{
    if (!ctx || type != VA_SRC_UNIFORM_TYPE) {
        return NULL;
    }
    unsigned pair_index = (value >> 1) | (fau_page << 5);
    if (ctx->ssym_43.symbols && ctx->ssym_43.symbols[pair_index].name.string_data) {
        return (const char *)ctx->ssym_43.symbols[pair_index].name.string_data;
    }

    return NULL;
}

static inline void
va_print_src(FILE *fp, unsigned type, unsigned value, unsigned size, unsigned fau_page,
             const cmpbe_chunk_CMMN *ctx, unsigned instr_idx, const uint32_t *first_def_idx)
{
   if (type == VA_SRC_IMM_TYPE) {
      if (value >= 32) {
         if (fau_page == 0)
            fputs(valhall_fau_special_page_0[(value - 0x20) >> 1] + 1, fp);
         else if (fau_page == 1)
            fputs(valhall_fau_special_page_1[(value - 0x20) >> 1] + 1, fp);
         else if (fau_page == 3)
            fputs(valhall_fau_special_page_3[(value - 0x20) >> 1] + 1, fp);
         else
            fprintf(fp, "reserved_page2");

         fprintf(fp, ".w%u", value & 1);
      } else {
         fprintf(fp, "0x%X", va_immediates[value]);
      }
   } else if (type == VA_SRC_UNIFORM_TYPE) {
      unsigned pair_index = (value >> 1) | (fau_page << 5);
      fprintf(fp, "u%u", pair_index);
      if (size <= 32)
         fprintf(fp, ".w%u", value & 1);

      if (ctx) {
         bool matched_meta = false;
         unsigned word_index = (pair_index * 2) + (value & 1);
         uint32_t byte_offset = word_index * 4;

         for (uint32_t c = 0; c < ctx->constant_count; c++) {
            if (ctx->constants[c].constant_id == byte_offset) {
               uint32_t raw_val = ctx->constants[c].value;
               float float_val;
               memcpy(&float_val, &raw_val, sizeof(float));
               if (raw_val != 0 && ((raw_val >= 0x38000000 && raw_val <= 0x4B800000) ||
                                    (raw_val >= 0xB8000000 && raw_val <= 0xCB800000))) {
                  fprintf(fp, " /* %gf */", float_val);
               } else {
                  fprintf(fp, " /* %u (0x%X) */", raw_val, raw_val);
               }
               matched_meta = true;
               break;
            }
         }
         if (!matched_meta) {
            for (uint32_t i = 0; i < ctx->ssym_24.count; i++) {
               for (uint32_t r = 0; r < ctx->ssym_24.symbols[i].rloc_count; r++) {
                  uint32_t start = ctx->ssym_24.symbols[i].relocations[r].offset;
                  uint32_t end = start + ctx->ssym_24.symbols[i].relocations[r].size;
                  if (byte_offset >= start && byte_offset < end) {
                     uint32_t internal_offset = byte_offset - start;
                     const char *member_name = NULL;
                     uint32_t member_base = 0;
                     if (ctx->ssym_24.symbols[i].type.tpib) {
                        const cmpbe_chunk_TPIB *tpib = ctx->ssym_24.symbols[i].type.tpib;
                        for (uint32_t m = 0; m < tpib->member_count; m++) {
                           if (internal_offset >= tpib->members[m].offset && tpib->members[m].offset >= member_base) {
                              member_name = (const char*)tpib->members[m].name.string_data;
                              member_base = tpib->members[m].offset;
                           }
                        }
                     }
                     if (member_name) {
                        if (internal_offset == member_base) {
                           fprintf(fp, " /* pushConstants_0.%s */", member_name);
                        } else {
                           fprintf(fp, " /* pushConstants_0.%s + %uB */", member_name, internal_offset - member_base);
                        }
                     } else {
                        fprintf(fp, " /* %s + %uB */", ctx->ssym_24.symbols[i].name.string_data, internal_offset);
                     }
                     matched_meta = true;
                     break;
                  }
               }
               if (matched_meta) break;
            }
         }
         if (!matched_meta) {
            // pair_index is actually not the binding id, but the symbol index
            fprintf(fp, " /* @%s */", ctx->ssym_43.symbols[pair_index].name.string_data);
         }
      }
   } else {
      bool discard = (type & 1);
      char *dmark = discard ? "^" : "";
      if (size > 32)
         fprintf(fp, "[r%u%s:r%u%s]", value, dmark, value + 1, dmark);
      else
         fprintf(fp, "r%u%s", value, dmark);

      if (value >= 55 && value <= 62 && instr_idx < first_def_idx[value]) {
         const char *compute_labels[] = {
            "gl_LocalInvocationID.xy", "gl_LocalInvocationID.z",
            "gl_WorkGroupID.x", "gl_WorkGroupID.y", "gl_WorkGroupID.z",
            "gl_GlobalInvocationID.x", "gl_GlobalInvocationID.y", "gl_GlobalInvocationID.z"
         };
         fprintf(fp, " /* %s */", compute_labels[value - 55]);
      }
   }
}

static inline void
va_print_float_src(FILE *fp, unsigned type, unsigned value, unsigned size, unsigned fau_page,
                   bool neg, bool abs, const cmpbe_chunk_CMMN *ctx, unsigned instr_idx, const uint32_t *first_def_idx)
{
   if (type == VA_SRC_IMM_TYPE) {
      assert(value < 32 && "overflow in LUT");
      fprintf(fp, "0x%X", va_immediates[value]);
   } else {
      va_print_src(fp, type, value, size, fau_page, ctx, instr_idx, first_def_idx);
   }

   if (neg) fprintf(fp, ".neg");
   if (abs) fprintf(fp, ".abs");
}

static inline void
va_print_dest(FILE *fp, unsigned mask, unsigned value, unsigned size, unsigned instr_idx, const uint32_t *first_def_idx)
{
   if (size > 32)
      fprintf(fp, "[r%u:r%u]", value, value + 1);
   else
      fprintf(fp, "r%u", value);

   if (mask != 0x3)
      fprintf(fp, ".h%u", (mask == 1) ? 0 : 1);

   if (value >= 55 && value <= 62 && instr_idx == first_def_idx[value]) {
      const char *compute_labels[] = {
         "gl_LocalInvocationID.xy", "gl_LocalInvocationID.z",
         "gl_WorkGroupID.x", "gl_WorkGroupID.y", "gl_WorkGroupID.z",
         "gl_GlobalInvocationID.x", "gl_GlobalInvocationID.y", "gl_GlobalInvocationID.z"
       };
      fprintf(fp, " /* clobbers %s */", compute_labels[value - 55]);
   }
}





static AnalyzedInstruction *program_ctx = NULL;

void
va_disasm_instr(FILE *fp, uint64_t instr, const cmpbe_chunk_CMMN *ctx, unsigned instr_idx, const uint32_t *first_def_idx)
{
   unsigned opcode;

   opcode = (instr >> 48) & 0x1ff;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];



         return;
      }


      fputs("NOP", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);


      break;
   }
   case 0x1f:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }



         return;
      }


      fputs("BRANCHZ", fp);
      if (instr & BIT(35)) fputs(".conservative", fp);
      if (instr & BIT(36)) fputs(".eq", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_combine[(instr >> 37) & 0x7], fp);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(27)) , 27));


      break;
   }
   case 0x20:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }



         return;
      }


      fputs("DISCARD.f32", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 26) & 0x3], fp);


      break;
   }
   case 0x2f:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }



         return;
      }


      fputs("BRANCHZI", fp);
      if (instr & BIT(35)) fputs(".conservative", fp);
      if (instr & BIT(36)) fputs(".eq", fp);
      if (instr & BIT(40)) fputs(".absolute", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_combine[(instr >> 37) & 0x7], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x45:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];



         return;
      }


      fputs("BARRIER", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);


      break;
   }
   case 0x154:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 30) & 3) <= 1) {
               uint32_t r = (instr >> 24) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CSEL.f32", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                         32, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 30) & 3, (instr >> 24) & 0x3f,
                         32, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x155:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 30) & 3) <= 1) {
               uint32_t r = (instr >> 24) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CSEL.v2f16", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                         16, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                         16, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 30) & 3, (instr >> 24) & 0x3f,
                         16, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x150:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 30) & 3) <= 1) {
               uint32_t r = (instr >> 24) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CSEL.u32", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 30) & 3, (instr >> 24) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x151:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 30) & 3) <= 1) {
               uint32_t r = (instr >> 24) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CSEL.v2u16", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 30) & 3, (instr >> 24) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x158:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 30) & 3) <= 1) {
               uint32_t r = (instr >> 24) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CSEL.s32", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 30) & 3, (instr >> 24) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x159:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 30) & 3) <= 1) {
               uint32_t r = (instr >> 24) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CSEL.v2s16", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 30) & 3, (instr >> 24) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x56:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_VAR_SPECIAL", fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fputs(valhall_sample_mode[(instr >> 38) & 0x3], fp);
      fputs(valhall_update_mode[(instr >> 36) & 0x3], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", index:0x%X", (uint32_t)  ((instr >> 12) & MASK(4)) );


      break;
   }
   case 0x40:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_VAR_BUF_FLAT_IMM", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }

      fprintf(fp, ", index:0x%X", (uint32_t)  ((instr >> 8) & MASK(11)) );


      break;
   }
   case 0x5f:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_VAR_BUF_FLAT", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x5c:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_VAR_BUF_IMM.f32", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_source_format[(instr >> 24) & 0xf], fp);
      fputs(valhall_sample_mode[(instr >> 38) & 0x3], fp);
      fputs(valhall_update_mode[(instr >> 36) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", index:0x%X", (uint32_t)  ((instr >> 16) & MASK(8)) );


      break;
   }
   case 0x5d:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_VAR_BUF_IMM.f16", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_source_format[(instr >> 24) & 0xf], fp);
      fputs(valhall_sample_mode[(instr >> 38) & 0x3], fp);
      fputs(valhall_update_mode[(instr >> 36) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", index:0x%X", (uint32_t)  ((instr >> 16) & MASK(8)) );


      break;
   }
   case 0x6c:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_VAR_BUF.f32", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_source_format[(instr >> 24) & 0xf], fp);
      fputs(valhall_sample_mode[(instr >> 38) & 0x3], fp);
      fputs(valhall_update_mode[(instr >> 36) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x6d:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_VAR_BUF.f16", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_source_format[(instr >> 24) & 0xf], fp);
      fputs(valhall_sample_mode[(instr >> 38) & 0x3], fp);
      fputs(valhall_update_mode[(instr >> 36) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x64:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_VAR", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fputs(valhall_sample_mode[(instr >> 38) & 0x3], fp);
      fputs(valhall_update_mode[(instr >> 36) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x54:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_VAR_IMM", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fputs(valhall_sample_mode[(instr >> 38) & 0x3], fp);
      fputs(valhall_update_mode[(instr >> 36) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", table:0x%X", (uint32_t)  ((instr >> 8) & MASK(4)) );

      fprintf(fp, ", index:0x%X", (uint32_t)  ((instr >> 12) & MASK(8)) );


      break;
   }
   case 0x55:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_VAR_FLAT", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x41:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_VAR_FLAT_IMM", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }

      fprintf(fp, ", table:0x%X", (uint32_t)  ((instr >> 8) & MASK(4)) );

      fprintf(fp, ", index:0x%X", (uint32_t)  ((instr >> 12) & MASK(8)) );


      break;
   }
   case 0x66:
   {

   opcode = (instr >> 37) & 0x3;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_ATTR_IMM", fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", index:0x%X", (uint32_t)  ((instr >> 20) & MASK(4)) );

      fprintf(fp, ", table:0x%X", (uint32_t)  ((instr >> 16) & MASK(4)) );


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_TEX_IMM", fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", index:0x%X", (uint32_t)  ((instr >> 20) & MASK(4)) );

      fprintf(fp, ", table:0x%X", (uint32_t)  ((instr >> 16) & MASK(4)) );


      break;
   }
   }

      break;
   }
   case 0x76:
   {

   opcode = (instr >> 37) & 0x3;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_ATTR", fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_TEX", fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0x44:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_GCLK_U64", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }


      break;
   }
   case 0x67:
   {

   opcode = (instr >> 37) & 0x3;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LEA_ATTR_IMM", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", table:0x%X", (uint32_t)  ((instr >> 16) & MASK(4)) );

      fprintf(fp, ", index:0x%X", (uint32_t)  ((instr >> 20) & MASK(4)) );


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LEA_TEX_IMM", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", table:0x%X", (uint32_t)  ((instr >> 16) & MASK(4)) );

      fprintf(fp, ", index:0x%X", (uint32_t)  ((instr >> 20) & MASK(4)) );


      break;
   }
   }

      break;
   }
   case 0x77:
   {

   opcode = (instr >> 37) & 0x3;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LEA_ATTR", fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LEA_TEX", fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0x6a:
   {

   opcode = (instr >> 27) & 0x7;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_PKA.i8", fp);
      fputs(valhall_load_lane_8_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_PKA.i16", fp);
      fputs(valhall_load_lane_16_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_PKA.i24", fp);
      fputs(valhall_load_lane_24_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x3:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_PKA.i32", fp);
      fputs(valhall_load_lane_32_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x4:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_PKA.i48", fp);
      fputs(valhall_load_lane_48_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x5:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_PKA.i64", fp);
      fputs(valhall_load_lane_64_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x6:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_PKA.i96", fp);
      fputs(valhall_load_lane_96_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x7:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_PKA.i128", fp);
      fputs(valhall_load_lane_128_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0x6e:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LEA_BUF", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x5e:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LEA_BUF_IMM", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", table:0x%X", (uint32_t)  ((instr >> 8) & MASK(4)) );

      fprintf(fp, ", index:0x%X", (uint32_t)  ((instr >> 12) & MASK(8)) );


      break;
   }
   case 0x60:
   {

   opcode = (instr >> 27) & 0x7;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_load = true;
               }
            }
         return;
      }


      fputs("LOAD.i8", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_load_lane_8_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_load = true;
               }
            }
         return;
      }


      fputs("LOAD.i16", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_load_lane_16_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_load = true;
               }
            }
         return;
      }


      fputs("LOAD.i24", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_load_lane_24_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x3:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_load = true;
               }
            }
         return;
      }


      fputs("LOAD.i32", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_load_lane_32_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x4:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_load = true;
               }
            }
         return;
      }


      fputs("LOAD.i48", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_load_lane_48_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x5:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_load = true;
               }
            }
         return;
      }


      fputs("LOAD.i64", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_load_lane_64_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x6:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_load = true;
               }
            }
         return;
      }


      fputs("LOAD.i96", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_load_lane_96_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x7:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_load = true;
               }
            }
         return;
      }


      fputs("LOAD.i128", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_load_lane_128_bit[(instr >> 36) & 0x7], fp);
      if (instr & BIT(39)) fputs(".unsigned", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   }

      break;
   }
   case 0x61:
   {

   opcode = (instr >> 27) & 0x7;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // STORE reads from staging registers to push to memory
                        ai->gen_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_store = true;
               }
            }
         return;
      }


      fputs("STORE.i8", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // STORE reads from staging registers to push to memory
                        ai->gen_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_store = true;
               }
            }
         return;
      }


      fputs("STORE.i16", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // STORE reads from staging registers to push to memory
                        ai->gen_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_store = true;
               }
            }
         return;
      }


      fputs("STORE.i24", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x3:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // STORE reads from staging registers to push to memory
                        ai->gen_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_store = true;
               }
            }
         return;
      }


      fputs("STORE.i32", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x4:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // STORE reads from staging registers to push to memory
                        ai->gen_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_store = true;
               }
            }
         return;
      }


      fputs("STORE.i48", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x5:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // STORE reads from staging registers to push to memory
                        ai->gen_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_store = true;
               }
            }
         return;
      }


      fputs("STORE.i64", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x6:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // STORE reads from staging registers to push to memory
                        ai->gen_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_store = true;
               }
            }
         return;
      }


      fputs("STORE.i96", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   case 0x7:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // STORE reads from staging registers to push to memory
                        ai->gen_mask |= BIT(base_r + i);
                  }
               }
            }


            if (((instr >> 6) & 0x3) != VA_SRC_UNIFORM_TYPE) {
               uint32_t parsed_offset = (instr >> 16) & 0xFFFF;
               if (parsed_offset < MAX_STACK_SLOTS) {
                  ai->stack_slot = parsed_offset;
                     ai->is_store = true;
               }
            }
         return;
      }


      fputs("STORE.i128", fp);
      fputs(valhall_memory_access[(instr >> 24) & 0x3], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:%d", (uint32_t) SEXT( ((instr >> 8) & MASK(16)) , 16));


      break;
   }
   }

      break;
   }
   case 0x6b:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LEA_PKA", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x70:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_CVT", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_memory_access[(instr >> 37) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:0x%X", (uint32_t)  ((instr >> 8) & MASK(8)) );


      break;
   }
   case 0x71:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("ST_CVT", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_memory_access[(instr >> 37) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:0x%X", (uint32_t)  ((instr >> 8) & MASK(8)) );


      break;
   }
   case 0x78:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("LD_TILE", fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x79:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("ST_TILE", fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x7f:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("BLEND", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_vector_size[(instr >> 28) & 0x3], fp);
      fputs(valhall_register_format[(instr >> 24) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", target:0x%X", (uint32_t)  ((instr >> 8) & MASK(8)) );


      break;
   }
   case 0x7d:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("ATEST", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 26) & 0x3], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x7e:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("ZS_EMIT", fp);
      if (instr & BIT(25)) fputs(".z", fp);
      if (instr & BIT(24)) fputs(".stencil", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x90:
   {

   opcode = (instr >> 16) & 0x1f;
   switch (opcode) {
   case 0x7:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("V2S16_TO_V2F16", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);


      break;
   }
   case 0x9:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("S32_TO_F32", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);


      break;
   }
   case 0x17:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("V2U16_TO_V2F16", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);


      break;
   }
   case 0x19:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("U32_TO_F32", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);


      break;
   }
   case 0x4:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("S16_TO_S32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_16_bit[(instr >> 28) & 0x1], fp);


      break;
   }
   case 0x5:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("S16_TO_F32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_16_bit[(instr >> 28) & 0x1], fp);


      break;
   }
   case 0x14:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("U16_TO_U32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_16_bit[(instr >> 28) & 0x1], fp);


      break;
   }
   case 0x15:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("U16_TO_F32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_16_bit[(instr >> 28) & 0x1], fp);


      break;
   }
   case 0xc:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("F32_TO_S32", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1c:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("F32_TO_U32", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);


      break;
   }
   case 0xe:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("V2F16_TO_V2S16", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x1e:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("V2F16_TO_V2U16", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0xa:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("F16_TO_S32", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_16_bit[(instr >> 28) & 0x1], fp);


      break;
   }
   case 0x1a:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("F16_TO_U32", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_16_bit[(instr >> 28) & 0x1], fp);


      break;
   }
   case 0xb:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("F16_TO_F32", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_16_bit[(instr >> 28) & 0x1], fp);


      break;
   }
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("S8_TO_S32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_8_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("S8_TO_F32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_8_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x10:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("U8_TO_U32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_8_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x11:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("U8_TO_F32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_8_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("V2S8_TO_V2S16", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_half_swizzles_8_bit[(instr >> 36) & 0xf], fp);


      break;
   }
   case 0x3:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("V2S8_TO_V2F16", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_half_swizzles_8_bit[(instr >> 36) & 0xf], fp);


      break;
   }
   case 0x12:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("V2U8_TO_V2U16", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_half_swizzles_8_bit[(instr >> 36) & 0xf], fp);


      break;
   }
   case 0x13:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("V2U8_TO_V2F16", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_half_swizzles_8_bit[(instr >> 36) & 0xf], fp);


      break;
   }
   case 0xd:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FROUND.f32", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0xf:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FROUND.v2f16", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   }

      break;
   }
   case 0x91:
   {

   opcode = (instr >> 16) & 0x1f;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("MOV.i32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x4:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CLZ.u32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x5:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CLZ.v2u16", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x6:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CLZ.v4u8", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x8:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IABS.s32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);


      break;
   }
   case 0x9:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IABS.v2s16", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);


      break;
   }
   case 0xa:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IABS.v4s8", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0xc:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("POPCOUNT.i32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0xd:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("BITREV.i32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0xe:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("NOT_OLD.i32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0x191:
   {

   opcode = (instr >> 16) & 0x1f;
   switch (opcode) {
   case 0xe:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("NOT_OLD.i64", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0x95:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("WMASK", fp);
      fputs(valhall_subgroup_size[(instr >> 36) & 0xf], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x98:
   {

   opcode = (instr >> 16) & 0x1f;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FLUSH.f32", fp);
      fputs(valhall_nan_mode[(instr >> 8) & 0x3], fp);
      if (instr & BIT(10)) fputs(".ftz", fp);
      if (instr & BIT(11)) fputs(".flush_inf", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FLUSH.v2f16", fp);
      fputs(valhall_nan_mode[(instr >> 8) & 0x3], fp);
      if (instr & BIT(10)) fputs(".ftz", fp);
      if (instr & BIT(11)) fputs(".flush_inf", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   }

      break;
   }
   case 0x99:
   {

   opcode = (instr >> 16) & 0x1f;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FREXPM.f32", fp);
      if (instr & BIT(24)) fputs(".sqrt", fp);
      if (instr & BIT(25)) fputs(".log", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FREXPM.v2f16", fp);
      if (instr & BIT(24)) fputs(".sqrt", fp);
      if (instr & BIT(25)) fputs(".log", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FREXPE.f32", fp);
      if (instr & BIT(24)) fputs(".sqrt", fp);
      if (instr & BIT(25)) fputs(".log", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x3:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FREXPE.v2f16", fp);
      if (instr & BIT(24)) fputs(".sqrt", fp);
      if (instr & BIT(25)) fputs(".log", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   }

      break;
   }
   case 0x9c:
   {

   opcode = (instr >> 16) & 0x1f;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FRCP.f32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FRCP.f16", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FRSQ.f32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x3:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FRSQ.f16", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x8:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FLOGD.f32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0xa:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FPCLASS.f32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0xb:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FPCLASS.f16", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0xc:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FLOG_TABLE.f32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0xe:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FRCP_APPROX.f32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0xf:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FRSQ_APPROX.f32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);


      break;
   }
   case 0x4:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FSIN_TABLE.u6", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x5:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FCOS_TABLE.u6", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x6:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FSINCOS_OFFSET.u6", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0xd:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FEXP_TABLE.u4", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0xa4:
   {

   opcode = (instr >> 16) & 0xf;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FADD.f32", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 26) & 0x3], fp);


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FMIN.f32", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 26) & 0x3], fp);


      break;
   }
   case 0x3:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FMAX.f32", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 26) & 0x3], fp);


      break;
   }
   case 0x6:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("LDEXP.f32", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x8:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FEXP.f32", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x9:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FADD_LSCALE.f32", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);


      break;
   }
   case 0xe:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FATAN_ASSIST.f32", fp);
      if (instr & BIT(24)) fputs(".second", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0xa5:
   {

   opcode = (instr >> 16) & 0xf;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FADD.v2f16", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0x3], fp);


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FMIN.v2f16", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0x3], fp);


      break;
   }
   case 0x3:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FMAX.v2f16", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0x3], fp);


      break;
   }
   case 0x4:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("V2F32_TO_V2F16", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x6:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("LDEXP.v2f16", fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0xa0:
   {

   opcode = (instr >> 16) & 0xf;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IADD.u32", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ISUB.u32", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xa:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IMUL.i32", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xb:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("HADD.u32", fp);
      if (instr & BIT(30)) fputs(".rhadd", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xf:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CLPER.i32", fp);
      fputs(valhall_subgroup_size[(instr >> 36) & 0xf], fp);
      fputs(valhall_lane_operation[(instr >> 32) & 0x3], fp);
      fputs(valhall_inactive_result[(instr >> 22) & 0xf], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   }

      break;
   }
   case 0xa1:
   {

   opcode = (instr >> 16) & 0xf;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IADD.v2u16", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0x5:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("MKVEC.v2i16", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_16_bit[(instr >> 28) & 0x1], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_16_bit[(instr >> 26) & 0x1], fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ISUB.v2u16", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xa:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IMUL.v2i16", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xb:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("HADD.v2u16", fp);
      if (instr & BIT(30)) fputs(".rhadd", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   }

      break;
   }
   case 0xa2:
   {

   opcode = (instr >> 16) & 0xf;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IADD.v4u8", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ISUB.v4u8", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xa:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IMUL.v4i8", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xb:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("HADD.v4u8", fp);
      if (instr & BIT(30)) fputs(".rhadd", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   }

      break;
   }
   case 0xa8:
   {

   opcode = (instr >> 16) & 0xf;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IADD.s32", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ISUB.s32", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xa:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IMUL.s32", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xb:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("HADD.s32", fp);
      if (instr & BIT(30)) fputs(".rhadd", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   }

      break;
   }
   case 0xa9:
   {

   opcode = (instr >> 16) & 0xf;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IADD.v2s16", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ISUB.v2s16", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xa:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IMUL.v2s16", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xb:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("HADD.v2s16", fp);
      if (instr & BIT(30)) fputs(".rhadd", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   }

      break;
   }
   case 0xaa:
   {

   opcode = (instr >> 16) & 0xf;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IADD.v4s8", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ISUB.v4s8", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xa:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IMUL.v4s8", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0xb:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("HADD.v4s8", fp);
      if (instr & BIT(30)) fputs(".rhadd", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   }

      break;
   }
   case 0x1a3:
   {

   opcode = (instr >> 16) & 0xf;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 36) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 26) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("IADD.u64", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 36) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 26) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("ISUB.u64", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0x6:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 26) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("SEG_ADD.u64", fp);
      if (instr & BIT(38)) fputs(".neg", fp);
      if (instr & BIT(39)) fputs(".preserve_null", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0x7:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 26) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("SHADDX.u64", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 26) & 0xf], fp);

      fprintf(fp, ", shift:0x%X", (uint32_t)  ((instr >> 20) & MASK(3)) );


      break;
   }
   case 0xa:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 36) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 26) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("IMULD.u64", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   }

      break;
   }
   case 0x1ab:
   {

   opcode = (instr >> 16) & 0xf;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 36) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 26) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("IADD.s64", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 36) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 26) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("ISUB.s64", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 26) & 0xf], fp);


      break;
   }
   case 0x7:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 26) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("SHADDX.s64", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 26) & 0xf], fp);

      fprintf(fp, ", shift:0x%X", (uint32_t)  ((instr >> 20) & MASK(3)) );


      break;
   }
   }

      break;
   }
   case 0xb2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FMA.f32", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 26) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 22) & 0x3, (instr >> 16) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(34), instr & BIT(35), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 24) & 0x3], fp);


      break;
   }
   case 0xb3:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FMA.v2f16", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fputs(valhall_round_mode[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 22) & 0x3, (instr >> 16) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(34), instr & BIT(35), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 24) & 0x3], fp);


      break;
   }
   case 0xb4:
   {

   opcode = (instr >> 24) & 0x703;
   switch (opcode) {
   case 0x100:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("LSHIFT_AND.i32", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("RSHIFT_AND.i32", fp);
      if (instr & BIT(34)) fputs(".signed", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x101:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("LSHIFT_OR.i32", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("RSHIFT_OR.i32", fp);
      if (instr & BIT(34)) fputs(".signed", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x102:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("LSHIFT_XOR.i32", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("RSHIFT_XOR.i32", fp);
      if (instr & BIT(34)) fputs(".signed", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   }

      break;
   }
   case 0xb5:
   {

   opcode = (instr >> 24) & 0x703;
   switch (opcode) {
   case 0x100:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("LSHIFT_AND.v2i16", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("RSHIFT_AND.v2i16", fp);
      if (instr & BIT(34)) fputs(".signed", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x101:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("LSHIFT_OR.v2i16", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("RSHIFT_OR.v2i16", fp);
      if (instr & BIT(34)) fputs(".signed", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x102:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("LSHIFT_XOR.v2i16", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("RSHIFT_XOR.v2i16", fp);
      if (instr & BIT(34)) fputs(".signed", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   }

      break;
   }
   case 0xb6:
   {

   opcode = (instr >> 24) & 0x703;
   switch (opcode) {
   case 0x100:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("LSHIFT_AND.v4i8", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("RSHIFT_AND.v4i8", fp);
      if (instr & BIT(34)) fputs(".signed", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x101:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("LSHIFT_OR.v4i8", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("RSHIFT_OR.v4i8", fp);
      if (instr & BIT(34)) fputs(".signed", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x102:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("LSHIFT_XOR.v4i8", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("RSHIFT_XOR.v4i8", fp);
      if (instr & BIT(34)) fputs(".signed", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   }

      break;
   }
   case 0x1b7:
   {

   opcode = (instr >> 24) & 0x703;
   switch (opcode) {
   case 0x100:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 36) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("LSHIFT_AND.i64", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 36) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("RSHIFT_AND.i64", fp);
      if (instr & BIT(34)) fputs(".signed", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x101:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 36) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("LSHIFT_OR.i64", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 36) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("RSHIFT_OR.i64", fp);
      if (instr & BIT(34)) fputs(".signed", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x102:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 36) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("LSHIFT_XOR.i64", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {

                        unsigned swz = (instr >> 36) & 0xf;
                        if ((swz & 1) == 0) {
                           ai->gen_mask |= BIT(r);
                        } else {
                           ai->gen_mask |= BIT(r + 1);
                        }
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r) | BIT(r + 1);
               }
            }

         return;
      }


      fputs("RSHIFT_XOR.i64", fp);
      if (instr & BIT(34)) fputs(".signed", fp);
      if (instr & BIT(30)) fputs(".not_result", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 64, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_64_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lanes_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      if (instr & BIT(35)) fputs(".not", fp);


      break;
   }
   }

      break;
   }
   case 0xb8:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("MUX.i32", fp);
      fputs(valhall_mux[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0xb9:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("MUX.v2i16", fp);
      fputs(valhall_mux[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0x3], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 24) & 0x3], fp);


      break;
   }
   case 0xba:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("MUX.v4i8", fp);
      fputs(valhall_mux[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0xbc:
   {

   opcode = (instr >> 24) & 0x1;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CUBE_SSEL", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CUBE_TSEL", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0xbd:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("MKVEC.v2i8", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_8_bit[(instr >> 38) & 0x3], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_lane_8_bit[(instr >> 36) & 0x3], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0xc0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CUBEFACE1", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 22) & 0x3, (instr >> 16) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(34), instr & BIT(35), ctx, instr_idx, first_def_idx);


      break;
   }
   case 0xc1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("CUBEFACE2_V9", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 22) & 0x3, (instr >> 16) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(34), instr & BIT(35), ctx, instr_idx, first_def_idx);


      break;
   }
   case 0xc2:
   {

   opcode = (instr >> 24) & 0x1;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IDPADD.v4s8", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IDPADD.v4u8", fp);
      if (instr & BIT(30)) fputs(".saturate", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0xf0:
   {

   opcode = (instr >> 24) & 0x3;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_OR.u32", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_AND.u32", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_MULTI.u32", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0xf1:
   {

   opcode = (instr >> 24) & 0x3;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_OR.v2u16", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_AND.v2u16", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0xf2:
   {

   opcode = (instr >> 24) & 0x3;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_OR.v4u8", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_AND.v4u8", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0xf4:
   {

   opcode = (instr >> 24) & 0x3;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FCMP_OR.f32", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 26) & 0x3], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FCMP_AND.f32", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_widen[(instr >> 26) & 0x3], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0xf5:
   {

   opcode = (instr >> 24) & 0x3;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FCMP_OR.v2f16", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0x3], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FCMP_AND.v2f16", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 28) & 0x3], fp);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         16, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0x3], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0xf8:
   {

   opcode = (instr >> 24) & 0x3;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_OR.s32", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_AND.s32", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x2:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_MULTI.s32", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_32_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0xf9:
   {

   opcode = (instr >> 24) & 0x3;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_OR.v2s16", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_AND.v2s16", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_16_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0xfa:
   {

   opcode = (instr >> 24) & 0x3;
   switch (opcode) {
   case 0x0:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_OR.v4s8", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x1:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("ICMP_AND.v4s8", fp);
      fputs(valhall_condition[(instr >> 32) & 0x7], fp);
      fputs(valhall_result_type[(instr >> 30) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 36) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 14) & 3, (instr >> 8) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(valhall_swizzles_8_bit[(instr >> 26) & 0xf], fp);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

      break;
   }
   case 0x110:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IADD_IMM.i32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", #0x%X", (uint32_t)  ((instr >> 8) & MASK(32)) );


      break;
   }
   case 0x111:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IADD_IMM.v2i16", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   16, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", #0x%X", (uint32_t)  ((instr >> 8) & MASK(32)) );


      break;
   }
   case 0x112:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("IADD_IMM.v4i8", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 8, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   8, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", #0x%X", (uint32_t)  ((instr >> 8) & MASK(32)) );


      break;
   }
   case 0x114:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FADD_IMM.f32", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", #0x%X", (uint32_t)  ((instr >> 8) & MASK(32)) );


      break;
   }
   case 0x115:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FADD_IMM.v2f16", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 16, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                         16, (instr >> 57) & 0x3, false, false, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", #0x%X", (uint32_t)  ((instr >> 8) & MASK(32)) );


      break;
   }
   case 0x69:
   {

   opcode = (instr >> 27) & 0x7;
   switch (opcode) {
   case 0x3:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


   {

         unsigned src0_type = (instr >> 6) & 3;
         unsigned src0_val  = (instr >> 0) & 0x3f;
         unsigned fau_page  = (instr >> 57) & 0x3;
         unsigned atomic_op = (instr >> 22) & 0xF;

         if (atomic_op == 0) { // ".ainc"
             const char *res_name = va_get_resource_name(ctx, src0_type, src0_val, fau_page);
             if (res_name && strstr(res_name, "_DEBUG_LINE_BUFFER_")) {
                 uint32_t parsed_offset = (instr >> 8) & 0xFFFF;
                 fprintf(fp, ">>> DEBUG_INFO: line %u <<<", parsed_offset / 4);
                 return;
             }
         }
   }
      fputs("ATOM1_RETURN.i32", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_atomic_operation_with_1[(instr >> 22) & 0xf], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:0x%X", (uint32_t)  ((instr >> 8) & MASK(8)) );


      break;
   }
   case 0x5:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


   {

         unsigned src0_type = (instr >> 6) & 3;
         unsigned src0_val  = (instr >> 0) & 0x3f;
         unsigned fau_page  = (instr >> 57) & 0x3;
         unsigned atomic_op = (instr >> 22) & 0xF;

         if (atomic_op == 0) { // ".ainc"
             const char *res_name = va_get_resource_name(ctx, src0_type, src0_val, fau_page);
             if (res_name && strstr(res_name, "_DEBUG_LINE_BUFFER_")) {
                 uint32_t parsed_offset = (instr >> 8) & 0xFFFF;
                 fprintf(fp, ">>> DEBUG_INFO: line %u <<<", parsed_offset / 4);
                 return;
             }
         }
   }
      fputs("ATOM1_RETURN.i64", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_atomic_operation_with_1[(instr >> 22) & 0xf], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:0x%X", (uint32_t)  ((instr >> 8) & MASK(8)) );


      break;
   }
   }

      break;
   }
   case 0x68:
   {

   opcode = (instr >> 27) & 0x7;
   switch (opcode) {
   case 0x3:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("ATOM.i32", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_atomic_operation[(instr >> 22) & 0xf], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:0x%X", (uint32_t)  ((instr >> 8) & MASK(8)) );


      break;
   }
   case 0x5:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("ATOM.i64", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      fputs(valhall_atomic_operation[(instr >> 22) & 0xf], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:0x%X", (uint32_t)  ((instr >> 8) & MASK(8)) );


      break;
   }
   }

      break;
   }
   case 0x120:
   {

   opcode = (instr >> 27) & 0x7;
   switch (opcode) {
   case 0x3:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 16) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }

            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("ATOM_RETURN.i32", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(26)) fputs(".compare", fp);
      fputs(valhall_atomic_operation[(instr >> 22) & 0xf], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 16) & 0x3f) + i));
      }
      fputs(", ", fp);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:0x%X", (uint32_t)  ((instr >> 8) & MASK(8)) );


      break;
   }
   case 0x5:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 16) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }

            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("ATOM_RETURN.i64", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(26)) fputs(".compare", fp);
      fputs(valhall_atomic_operation[(instr >> 22) & 0xf], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 16) & 0x3f) + i));
      }
      fputs(", ", fp);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);

      fprintf(fp, ", offset:0x%X", (uint32_t)  ((instr >> 8) & MASK(8)) );


      break;
   }
   }

      break;
   }
   case 0x125:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 16) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }

            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("TEX_FETCH", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_register_width[(instr >> 46) & 0x1], fp);
      fputs(valhall_write_mask[(instr >> 22) & 0xf], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(8)) fputs(".wide_indices", fp);
      if (instr & BIT(10)) fputs(".array_enable", fp);
      if (instr & BIT(11)) fputs(".texel_offset", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 16) & 0x3f) + i));
      }
      fputs(", ", fp);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x128:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 16) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }

            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("TEX_SINGLE", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_register_width[(instr >> 46) & 0x1], fp);
      fputs(valhall_write_mask[(instr >> 22) & 0xf], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(8)) fputs(".wide_indices", fp);
      if (instr & BIT(10)) fputs(".array_enable", fp);
      if (instr & BIT(11)) fputs(".texel_offset", fp);
      if (instr & BIT(12)) fputs(".shadow", fp);
      fputs(valhall_lod_mode[(instr >> 13) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 16) & 0x3f) + i));
      }
      fputs(", ", fp);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x129:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 16) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }

            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("TEX_GATHER", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_register_width[(instr >> 46) & 0x1], fp);
      fputs(valhall_write_mask[(instr >> 22) & 0xf], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(8)) fputs(".wide_indices", fp);
      if (instr & BIT(10)) fputs(".array_enable", fp);
      if (instr & BIT(11)) fputs(".texel_offset", fp);
      if (instr & BIT(13)) fputs(".integer_coordinates", fp);
      fputs(valhall_fetch_component[(instr >> 14) & 0x3], fp);
      if (instr & BIT(12)) fputs(".shadow", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 16) & 0x3f) + i));
      }
      fputs(", ", fp);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x12a:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 16) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }

            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("TEX_GRADIENT", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_register_width[(instr >> 46) & 0x1], fp);
      fputs(valhall_write_mask[(instr >> 22) & 0xf], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(8)) fputs(".wide_indices", fp);
      if (instr & BIT(13)) fputs(".lod_mode", fp);
      if (instr & BIT(14)) fputs(".lod_mode", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 16) & 0x3f) + i));
      }
      fputs(", ", fp);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x12f:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }


            {
               uint32_t base_r = (instr >> 16) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }

            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = ((instr >> 33) & 0x7);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("TEX_DUAL", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_register_width[(instr >> 46) & 0x1], fp);
      fputs(valhall_register_width[(instr >> 47) & 0x1], fp);
      fputs(valhall_write_mask[(instr >> 22) & 0xf], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(8)) fputs(".wide_indices", fp);
      if (instr & BIT(10)) fputs(".array_enable", fp);
      if (instr & BIT(11)) fputs(".texel_offset", fp);
      if (instr & BIT(12)) fputs(".shadow", fp);
      fputs(valhall_lod_mode[(instr >> 13) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 16) & 0x3f) + i));
      }
      fputs(", ", fp);

      fprintf(fp, "@");
      for (unsigned i = 0; i < ((instr >> 33) & 0x7); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x130:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("VAR_TEX_BUF_SINGLE", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_sample_and_update_mode[(instr >> 33) & 0x7], fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_varying_texture_register_width[(instr >> 24) & 0x3], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(10)) fputs(".array_enable", fp);
      if (instr & BIT(12)) fputs(".shadow", fp);
      fputs(valhall_lod_mode[(instr >> 13) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x131:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("VAR_TEX_BUF_GATHER", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_sample_and_update_mode[(instr >> 33) & 0x7], fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_varying_texture_register_width[(instr >> 24) & 0x3], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(10)) fputs(".array_enable", fp);
      if (instr & BIT(13)) fputs(".integer_coordinates", fp);
      fputs(valhall_fetch_component[(instr >> 14) & 0x3], fp);
      if (instr & BIT(12)) fputs(".shadow", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x132:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("VAR_TEX_BUF_GRADIENT", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_sample_and_update_mode[(instr >> 33) & 0x7], fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_varying_texture_register_width[(instr >> 24) & 0x3], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(10)) fputs(".array_enable", fp);
      if (instr & BIT(12)) fputs(".shadow", fp);
      if (instr & BIT(13)) fputs(".lod_mode", fp);
      if (instr & BIT(14)) fputs(".lod_mode", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x137:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("VAR_TEX_BUF_DUAL", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_sample_and_update_mode[(instr >> 33) & 0x7], fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_varying_texture_register_width[(instr >> 24) & 0x3], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(10)) fputs(".array_enable", fp);
      if (instr & BIT(12)) fputs(".shadow", fp);
      fputs(valhall_lod_mode[(instr >> 13) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x138:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("VAR_TEX_SINGLE", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_sample_and_update_mode[(instr >> 33) & 0x7], fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_varying_texture_register_width[(instr >> 24) & 0x3], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(10)) fputs(".array_enable", fp);
      if (instr & BIT(12)) fputs(".shadow", fp);
      fputs(valhall_lod_mode[(instr >> 13) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x139:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("VAR_TEX_GATHER", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_sample_and_update_mode[(instr >> 33) & 0x7], fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_varying_texture_register_width[(instr >> 24) & 0x3], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(10)) fputs(".array_enable", fp);
      if (instr & BIT(13)) fputs(".integer_coordinates", fp);
      fputs(valhall_fetch_component[(instr >> 14) & 0x3], fp);
      if (instr & BIT(12)) fputs(".shadow", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x13a:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("VAR_TEX_GRADIENT", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_sample_and_update_mode[(instr >> 33) & 0x7], fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_varying_texture_register_width[(instr >> 24) & 0x3], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(10)) fputs(".array_enable", fp);
      if (instr & BIT(12)) fputs(".shadow", fp);
      if (instr & BIT(13)) fputs(".lod_mode", fp);
      if (instr & BIT(14)) fputs(".lod_mode", fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x13f:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                        ai->gen_mask |= BIT(r) | BIT(r + 1);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            {
               uint32_t base_r = (instr >> 40) & 0x3f;
               uint32_t count = (((instr >> 36) & 0x7) + 1);
               for (uint32_t i = 0; i < count; ++i) {
                  if (base_r + i < 64) {
                        // LOAD and texture samples write into staging registers
                        ai->def_mask |= BIT(base_r + i);
                  }
               }
            }


         return;
      }


      fputs("VAR_TEX_DUAL", fp);
      fputs(valhall_slot[(instr >> 30) & 0x7], fp);
      if (instr & BIT(39)) fputs(".skip", fp);
      fputs(valhall_sample_and_update_mode[(instr >> 33) & 0x7], fp);
      fputs(valhall_register_type[(instr >> 26) & 0x3], fp);
      fputs(valhall_varying_texture_register_width[(instr >> 24) & 0x3], fp);
      fputs(valhall_dimension[(instr >> 28) & 0x3], fp);
      if (instr & BIT(10)) fputs(".array_enable", fp);
      if (instr & BIT(12)) fputs(".shadow", fp);
      fputs(valhall_lod_mode[(instr >> 13) & 0x7], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      fprintf(fp, "@");
      for (unsigned i = 0; i < (((instr >> 36) & 0x7) + 1); ++i) {
         fprintf(fp, "%sr%u", (i == 0) ? "" : ":",
                 (uint32_t) (((instr >> 40) & 0x3f) + i));
      }
      fputs(", ", fp);

      va_print_src(fp, (instr >> 6) & 3, (instr >> 0) & 0x3f,
                   64, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 22) & 3, (instr >> 16) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x160:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 30) & 3) <= 1) {
               uint32_t r = (instr >> 24) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FMA_RSCALE.f32", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 22) & 0x3, (instr >> 16) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(34), instr & BIT(35), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 30) & 3, (instr >> 24) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x161:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 30) & 3) <= 1) {
               uint32_t r = (instr >> 24) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FMA_RSCALE_N.f32", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 22) & 0x3, (instr >> 16) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(34), instr & BIT(35), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 30) & 3, (instr >> 24) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x162:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 30) & 3) <= 1) {
               uint32_t r = (instr >> 24) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FMA_RSCALE_LEFT.f32", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 22) & 0x3, (instr >> 16) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(34), instr & BIT(35), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 30) & 3, (instr >> 24) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   case 0x163:
   {


      if (!fp && program_ctx) {
         AnalyzedInstruction *ai = &program_ctx[instr_idx];
            if (((instr >> 6) & 3) <= 1) {
               uint32_t r = (instr >> 0) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 14) & 3) <= 1) {
               uint32_t r = (instr >> 8) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 22) & 3) <= 1) {
               uint32_t r = (instr >> 16) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }
            if (((instr >> 30) & 3) <= 1) {
               uint32_t r = (instr >> 24) & 0x3f;
               if (r < 64) {
                     ai->gen_mask |= BIT(r);
               }
            }


            if (((instr >> 46) & 3) != 0xC0) {
               uint32_t r = (instr >> 40) & 0x3f;
               if (r < 64) {
                     ai->def_mask |= BIT(r);
               }
            }

         return;
      }


      fputs("FMA_RSCALE_SCALE16.f32", fp);
      fputs(valhall_clamp[(instr >> 32) & 0x3], fp);
      fprintf(fp, "%s ", valhall_flow[(instr >> 59) & 0xf]);

      va_print_dest(fp, (instr >> 46) & 0x3, (instr >> 40) & 0x3f, 32, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 6) & 0x3, (instr >> 0) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(38), instr & BIT(39), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 14) & 0x3, (instr >> 8) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(36), instr & BIT(37), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_float_src(fp, (instr >> 22) & 0x3, (instr >> 16) & 0x3f,
                         32, (instr >> 57) & 0x3,
                         instr & BIT(34), instr & BIT(35), ctx, instr_idx, first_def_idx);
      fputs(", ", fp);

      va_print_src(fp, (instr >> 30) & 3, (instr >> 24) & 0x3f,
                   32, (instr >> 57) & 0x3, ctx, instr_idx, first_def_idx);


      break;
   }
   }

}

static bool is_branch(uint64_t instr)
{

   if ((instr & 0x1ff000000000000) == 0x1f000000000000) return true;

   if ((instr & 0x1ff000000000000) == 0x2f000000000000) return true;
   return false;
}

void
disassemble_valhall(FILE *fp, const void *code, size_t size, bool verbose, const cmpbe_chunk_CMMN *ctx)
{
   assert((size & 7) == 0);
   const uint64_t *words = (const uint64_t *)code;
   uint32_t instruction_count = size / 8;

   if (instruction_count == 0) return;

   AnalyzedInstruction *program = calloc(instruction_count, sizeof(AnalyzedInstruction));
   assert(program != NULL);

   uint32_t first_def_idx[64];
   for (int r = 0; r < 64; r++) first_def_idx[r] = 0xFFFFFFFF;

   program_ctx = program;

   uint32_t executable_limit = instruction_count;
   for (uint32_t i = 0; i < instruction_count; i++) {
      program[i].raw_word = words[i];
      program[i].branch_target_idx = -1;
      program[i].num_incoming_branches = 0;

      if (((words[i] >> 59) & 0x0F) == 0x0F) {
         executable_limit = i + 1;
         break;
      }

      va_disasm_instr(NULL, words[i], NULL, i, first_def_idx);

      for (int r = 0; r < 64; r++) {
         if ((program[i].def_mask & BIT(r)) && first_def_idx[r] == 0xFFFFFFFF) {
            first_def_idx[r] = i;
         }
      }

      if (program[i].is_branch = is_branch(words[i])) {
         int32_t relative_offset = (int32_t)SEXT((words[i] >> 8) & MASK(24), 24);
         int32_t dest_idx = (int32_t)i + 1 + relative_offset;
         if (dest_idx >= 0 && dest_idx < (int32_t)instruction_count) {
            program[i].branch_target_idx = dest_idx;
         }
      }
   }

   program_ctx = NULL;

   for (uint32_t i = 0; i < executable_limit; i++) {
      if (program[i].is_branch && program[i].branch_target_idx != -1) {
         uint32_t target = program[i].branch_target_idx;
         if (target < instruction_count) {
            uint32_t cnt = program[target].num_incoming_branches;
            if (cnt < 16) {
               program[target].incoming_branch_offsets[cnt] = i * 8;
               program[target].num_incoming_branches++;
            }
         }
      }
   }

   bool change = true;

   while (change) {
      change = false;
      for (int32_t i = (int32_t)executable_limit - 1; i >= 0; i--) {
         uint64_t next_live_regs = 0;
         uint8_t next_live_stack[MAX_STACK_SLOTS];
         memset(next_live_stack, 0, MAX_STACK_SLOTS);

         if (i == (int32_t)executable_limit - 1) {
            next_live_regs = 0;
         } else {
            next_live_regs = program[i + 1].live_regs_in;
            memcpy(next_live_stack, program[i + 1].live_stack_in, MAX_STACK_SLOTS);
         }

         if (program[i].branch_target_idx != -1) {
            uint32_t target = program[i].branch_target_idx;
            next_live_regs |= program[target].live_regs_in;
            for (int s = 0; s < MAX_STACK_SLOTS; s++) {
               if (program[target].live_stack_in[s]) next_live_stack[s] = 1;
            }
         }

         if (program[i].live_regs_out != next_live_regs) {
            program[i].live_regs_out = next_live_regs;
            change = true;
         }

         uint64_t computed_regs_in = program[i].gen_mask | (program[i].live_regs_out & ~program[i].def_mask);
         if (program[i].live_regs_in != computed_regs_in) {
            program[i].live_regs_in = computed_regs_in;
            change = true;
         }

         if (program[i].stack_slot != -1) {
            if (program[i].is_load) {
               next_live_stack[program[i].stack_slot] = 1;
            } else if (program[i].is_store) {
               next_live_stack[program[i].stack_slot] = 0;
            }
         }

         if (memcmp(program[i].live_stack_out, next_live_stack, MAX_STACK_SLOTS) != 0) {
            memcpy(program[i].live_stack_out, next_live_stack, MAX_STACK_SLOTS);
            change = true;
         }

         uint8_t computed_stack_in[MAX_STACK_SLOTS];
         memcpy(computed_stack_in, next_live_stack, MAX_STACK_SLOTS);
         if (program[i].stack_slot != -1 && program[i].is_load) {
            computed_stack_in[program[i].stack_slot] = 1;
         }

         if (memcmp(program[i].live_stack_in, computed_stack_in, MAX_STACK_SLOTS) != 0) {
            memcpy(program[i].live_stack_in, computed_stack_in, MAX_STACK_SLOTS);
            change = true;
         }
      }
   }

    bool in_data_section = false;
    fprintf(fp, ".text: // %u instructions\n", executable_limit);

    for (unsigned i = 0; i < instruction_count; ++i) {
        uint64_t instr = words[i];
        unsigned current_offset = i * 8;

        if (in_data_section) {
        uint32_t row_bytes = 8;
        uint64_t next_instr = 0;
        if (i + 1 < instruction_count) {
            next_instr = words[i + 1];
            row_bytes = 16;
        }
        uint32_t q0 = (uint32_t)(instr & 0xFFFFFFFF);
        uint32_t q1 = (uint32_t)(instr >> 32);
        uint32_t q2 = (uint32_t)(next_instr & 0xFFFFFFFF);
        uint32_t q3 = (uint32_t)(next_instr >> 32);

        unsigned char db[16];
        memcpy(&db[0], &instr, 8);
        if (row_bytes == 16) {
            memcpy(&db[8], &next_instr, 8);
            fprintf(fp, "/* [0x%04X] */  %08X %08X %08X %08X  | ", current_offset, q0, q1, q2, q3);
        } else {
            memset(&db[8], 0, 8);
            fprintf(fp, "/* [0x%04X] */  %08X %08X -------- --------  | ", current_offset, q0, q1);
        }
        for (int j = 0; j < 16; j++) {
            if (j < (int)row_bytes) {
                fprintf(fp, "%c", (db[j] >= 32 && db[j] <= 126) ? db[j] : '.');
            } else {
                fprintf(fp, " ");
            }
        }
        fprintf(fp, " |\n");
        if (row_bytes == 16) i++;
        continue;
        }

        bool is_jump_target = (program[i].num_incoming_branches > 0);
        bool is_branch_instr = program[i].is_branch;
        bool is_above_jump_target = (i + 1 < executable_limit) && (program[i + 1].num_incoming_branches > 0);

        bool live_flows_sequentially = false;
        if (i + 1 < executable_limit) {
            live_flows_sequentially = (program[i].live_regs_out == program[i + 1].live_regs_in);
        }

        bool show_as_generic_live = live_flows_sequentially && !is_jump_target;
        if (is_jump_target) {
        fprintf(fp, "/* Jump target from: ");
        for (uint32_t b = 0; b < program[i].num_incoming_branches; b++) {
            fprintf(fp, "0x%04X%s", program[i].incoming_branch_offsets[b], (b == program[i].num_incoming_branches - 1) ? "" : ", ");
        }
        fprintf(fp, " */\n");
        }

        if (show_as_generic_live) {
            va_print_live_set_ranges(fp, "live", program[i].live_regs_in);
        } else {
            va_print_live_set_ranges(fp, "live-in", program[i].live_regs_in);
        }

        fprintf(fp, "%4u [0x%04X] %016llX   ", i, current_offset, (unsigned long long)instr);
        va_disasm_instr(fp, instr, ctx, i, first_def_idx);

        if (is_branch_instr && program[i].branch_target_idx != -1) {
            fprintf(fp, " /* jumps to 0x%04X (instruction #%u) */",
                program[i].branch_target_idx * 8, program[i].branch_target_idx);
        }
        fprintf(fp, "\n");
        bool force_live_out = is_branch_instr || is_above_jump_target || !live_flows_sequentially;

        if (force_live_out) {
        va_print_live_set_ranges(fp, "live-out", program[i].live_regs_out);
            fprintf(fp, "\n");
        }

        if (((instr >> 59) & 0x0F) == 0x0F) {
            in_data_section = true;
            fprintf(fp, ".rodata: // %lu bytes\n", size - (executable_limit * 8));
        }
    }

    free(program);
    fprintf(fp, "\n");
}
