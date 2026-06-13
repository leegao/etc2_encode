// Reverse engineered struct definitions compatible with cmpbe_v2_deserialize_MBS2_to_C

#ifndef CMPBE_CHUNKS_H
#define CMPBE_CHUNKS_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cmpbe_chunk_TPGE;
struct cmpbe_chunk_TPAR;
struct cmpbe_chunk_TPIB;
struct cmpbe_chunk_TPST;
struct cmpbe_chunk_TPSE;
struct cmpbe_chunk_RLOC;
struct cmpbe_chunk_SYMB;
struct cmpbe_chunk_FCST;
struct cmpbe_chunk_EBIN;
struct cmpbe_chunk_KWGS;
struct cmpbe_chunk_CCOM;

typedef enum {
    CMPBE_VEHW_CORE_VALHALL = 0x1c,
    CMPBE_VEHW_CORE_DEFAULT = 0x00
} cmpbe_chunk_VEHW_core;

typedef enum {
    CMPBE_VELA_LANG_SPIRV = 0x7
} cmpbe_chunk_VELA_lang;

typedef enum {
    CMPBE_TYPE_SCALAR_INT  = 0x2,
    CMPBE_TYPE_SCALAR_UINT = 0x3
} cmpbe_chunk_TPGE_scalar_type;

typedef enum {
    CMPBE_TYPE_SIZE_16BIT = 0x1,
    CMPBE_TYPE_SIZE_32BIT = 0x2
} cmpbe_chunk_TPGE_scalar_size;

typedef enum {
    CMPBE_PRECISION_LOW    = 0x0,
    CMPBE_PRECISION_MEDIUM = 0x1,
    CMPBE_PRECISION_HIGH   = 0x2
} cmpbe_chunk_TPGE_precision;

typedef enum {
    CMPBE_AUX_QUAL_NONE          = 0x0,
    CMPBE_AUX_QUAL_PUSH_CONSTANT = 0x8
} cmpbe_chunk_TPGE_aux_qualifier;

typedef enum {
    CMPBE_SYM_FLAG_NONE       = 0x00,
    CMPBE_SYM_FLAG_UNIFORM    = 0x24,
    CMPBE_SYM_FLAG_BUFFER_VAR = 0x824
} cmpbe_chunk_symbol_flags;

typedef enum {
    CMPBE_SEMANTICS_NONE = 0x0
} cmpbe_chunk_SYMB_semantics;

typedef enum {
    CMPBE_LAYOUT_STD140 = 0x0,
    CMPBE_LAYOUT_STD430 = 0x1
} cmpbe_chunk_TPIB_layout;

typedef enum {
    CMPBE_KIND_UNIFORM_BLOCK = 0x0,
    CMPBE_KIND_STORAGE_BLOCK = 0x1
} cmpbe_chunk_TPIB_kind;

typedef enum {
    CMPBE_PREPASS_FLAG_NONE = 0x0
} cmpbe_chunk_FSHA_prepass_flags;

typedef enum {
    CMPBE_FSHA_FLAG_COMPUTE = 0x42000,
    CMPBE_FSHA_FLAG_AUX_ALT = 0x20042000
} cmpbe_chunk_FSHA_flags;

typedef enum {
    CMPBE_VARIANT_DEFAULT = 0x00,
    CMPBE_VARIANT_ASTC    = 0x80
} cmpbe_chunk_FSHA_variant;

typedef enum {
    CMPBE_MBS2_RESERVED_DEFAULT = 0x0
} cmpbe_chunk_MBS2_reserved_enum;

typedef struct cmpbe_chunk_VEHW {
    cmpbe_chunk_VEHW_core core;
    uint32_t reserved1;
    uint32_t reserved2;
} cmpbe_chunk_VEHW;

typedef struct cmpbe_chunk_VELA {
    cmpbe_chunk_VELA_lang lang;
} cmpbe_chunk_VELA;

typedef struct cmpbe_chunk_STRI {
    uint32_t length;
    const uint8_t* string_data;
} cmpbe_chunk_STRI;

typedef struct cmpbe_chunk_SSYM {
    uint32_t count;
    struct cmpbe_chunk_SYMB* symbols;
} cmpbe_chunk_SSYM;

typedef struct cmpbe_chunk_TPGE {
    cmpbe_chunk_TPGE_scalar_type scalar_type;
    uint8_t component_count;
    cmpbe_chunk_TPGE_scalar_size scalar_size;
    cmpbe_chunk_TPGE_precision precision;
    uint32_t alignment;
    cmpbe_chunk_TPGE_aux_qualifier aux_qualifier;
    uint8_t reserved;
} cmpbe_chunk_TPGE;

typedef struct cmpbe_chunk_TYPE {
    const void* unknown0;
    struct cmpbe_chunk_TPAR* tpar;
    struct cmpbe_chunk_TPGE* tpge;
    struct cmpbe_chunk_TPIB* tpib;
    const void* unknown4;
    const void* unknown5;
    const void* unknown6;
    const void* unknown7;
    const void* unknown8;
    const void* unknown9;
    struct cmpbe_chunk_TPST* tpst;
    const void* unknown11;
} cmpbe_chunk_TYPE;

typedef struct cmpbe_chunk_TPAR {
    uint32_t array_size;
    struct cmpbe_chunk_TYPE element_type;
} cmpbe_chunk_TPAR;

typedef struct cmpbe_chunk_TPIB {
    cmpbe_chunk_TPIB_layout layout;
    cmpbe_chunk_TPIB_kind kind;
    uint32_t block_size;
    uint32_t member_count;
    struct cmpbe_chunk_TPSE* members;
    const void* reserved;
} cmpbe_chunk_TPIB;

typedef struct cmpbe_chunk_TPST {
    uint32_t size;
    uint32_t member_count;
    cmpbe_chunk_STRI tag;
    struct cmpbe_chunk_TPSE* members;
} cmpbe_chunk_TPST;

typedef struct cmpbe_chunk_TPSE {
    cmpbe_chunk_STRI name;
    uint32_t offset;
    uint16_t binding;
    cmpbe_chunk_symbol_flags flags;
    uint16_t location;
    cmpbe_chunk_SYMB_semantics semantics;
    cmpbe_chunk_TYPE type;
} cmpbe_chunk_TPSE;

typedef struct cmpbe_chunk_RLOC {
    uint16_t segment;
    uint16_t offset;
    uint16_t type;
    uint16_t size;
} cmpbe_chunk_RLOC;

typedef struct cmpbe_chunk_SYMB {
    cmpbe_chunk_STRI name;
    cmpbe_chunk_symbol_flags flags;
    cmpbe_chunk_SYMB_semantics semantics;
    uint8_t binding_set;
    uint32_t binding_id;
    uint16_t location;
    uint16_t component;
    cmpbe_chunk_TYPE type;
    uint32_t rloc_count;
    struct cmpbe_chunk_RLOC* relocations;
    uint32_t nested_count;
    const void* nested_symbols;
    const void* reserved1;
    const void* reserved2;
} cmpbe_chunk_SYMB;

typedef struct cmpbe_chunk_UBUF {
    uint32_t count;
    const void* data;
} cmpbe_chunk_UBUF;

typedef struct cmpbe_chunk_FCST {
    uint16_t size;
    uint16_t constant_id;
    uint32_t value;
} cmpbe_chunk_FCST;

typedef struct cmpbe_chunk_OBJC {
    uint32_t size;
    const uint8_t* byte_code;
} cmpbe_chunk_OBJC;

typedef struct cmpbe_chunk_EBIN {
    uint16_t id;
    uint16_t pipeline_stage;
    cmpbe_chunk_FSHA_prepass_flags prepass_flags;
    uint32_t uncompressed_code_size;
    uint16_t register_count;
    uint16_t local_thread_limit;
    uint32_t scratch_allocation_bytes;
    cmpbe_chunk_FSHA_flags fsha_flags;
    cmpbe_chunk_FSHA_variant variant;
    const void* unk0;
    const void* unk1;
    const void* unk2;
    const void* unk3;
    const void* unk4;
    cmpbe_chunk_OBJC bytecode;
    const void* unk5;
    const void* unk6;
} cmpbe_chunk_EBIN;

typedef struct cmpbe_chunk_CMMN {
    cmpbe_chunk_VELA language;
    cmpbe_chunk_SSYM ssym_2;
    cmpbe_chunk_SSYM ssym_3;
    cmpbe_chunk_SSYM ssym_24;
    cmpbe_chunk_SSYM ssym_25;
    cmpbe_chunk_SSYM ssym_26;
    cmpbe_chunk_SSYM ssym_43;
    cmpbe_chunk_UBUF ubuf_44;
    uint16_t compilation_flags;
    uint32_t constant_count;
    const struct cmpbe_chunk_FCST* constants;
    uint32_t binary_count;
    const struct cmpbe_chunk_EBIN* binaries;
    const void* common_tail;
} cmpbe_chunk_CMMN;

typedef struct cmpbe_chunk_KWGS {
    uint32_t workgroup_x;
    uint32_t workgroup_y;
    uint32_t workgroup_z;
} cmpbe_chunk_KWGS;

typedef struct cmpbe_chunk_KERN {
    cmpbe_chunk_STRI entry_point_name;
    uint32_t kernel_flags;
    const void* reserved1;
    uint32_t argument_count;
    cmpbe_chunk_MBS2_reserved_enum reserved_enum;
    const cmpbe_chunk_KWGS* workgroup_sizes;
} cmpbe_chunk_KERN;

typedef struct cmpbe_chunk_CCOM {
    cmpbe_chunk_CMMN common;
    cmpbe_chunk_KERN kernel;
    const void* custom_ext0;
    const void* custom_ext1;
} cmpbe_chunk_CCOM;

typedef struct cmpbe_chunk_MBS2 {
    uint32_t version;
    cmpbe_chunk_VEHW hardware;
    const void* interface_descriptor;
    const cmpbe_chunk_CCOM* compilation_command;
    const void* extension_tree0;
    const void* extension_tree1;
    const void* extension_tree2;
    const void* extension_tree3;
    const void* extension_tree4;
    const void* extension_tree5;
    const void* extension_tree6;
    const void* extension_tree7;
    const void* extension_tree8;
} cmpbe_chunk_MBS2;

#ifdef __cplusplus
}
#endif

#endif /* CMPBE_CHUNKS_H */
