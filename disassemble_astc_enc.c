#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "disassemble.h"
#include "cmpbe_chunks.h"

#include "astc_enc_mbs2_shader.h"

void pretty_print_mbs2_shader(FILE *fp, const cmpbe_chunk_MBS2 *root)
{
    if (!root || !root->compilation_command) {
        fprintf(stderr, "Error: root is nullptr.\n");
        return;
    }

    const cmpbe_chunk_CCOM *ccom = root->compilation_command;

    if (ccom->common.binary_count == 0 || !ccom->common.binaries) {
        fprintf(stderr, "Error: no shaders\n");
        return;
    }

    const cmpbe_chunk_OBJC *bytecode = &ccom->common.binaries[0].bytecode;
    uint16_t registers = ccom->common.binaries[0].register_count;

    fprintf(fp, "; ======================================\n");
    fprintf(fp, "; VALHALL MBS2 SHADER (Dis)ASM\n");
    fprintf(fp, "; Entry: %s\n", ccom->kernel.entry_point_name.string_data);
    fprintf(fp, "; Vregs: %u / 64 (32 = max occupancy)\n", registers);
    fprintf(fp, "; Size: %u bytes, %u bytes of scratch alloca\n",
        bytecode->size, ccom->common.binaries[0].scratch_allocation_bytes);
    fprintf(fp, "; ======================================\n\n");
    disassemble_valhall(fp, bytecode->byte_code, bytecode->size, false, &ccom->common);
    fprintf(fp, "\n; End of Disassembly\n");
}

int main() {
    pretty_print_mbs2_shader(stdout, &MBS2);
}
