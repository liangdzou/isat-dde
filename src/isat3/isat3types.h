/****************************************************************************
 ****************************************************************************
 *
 * isat3types.h
 *
 ****************************************************************************
 ****************************************************************************/





#ifndef I3_ISAT3TYPES_H
#define I3_ISAT3TYPES_H




/****************************************************************************
 * prefixes
 ****************************************************************************/

/* I3_EXTERN for C++ and C */

#ifdef __cplusplus
#define I3_EXTERN			extern "C"
#else /* __cplusplus */
#define I3_EXTERN			extern
#endif /* __cplusplus */



/****************************************************************************
 * basic types
 ****************************************************************************/

typedef signed char			i3_s8_t;
typedef unsigned char			i3_u8_t;
typedef signed short int		i3_s16_t;
typedef unsigned short int		i3_u16_t;
typedef signed int			i3_s32_t;
typedef unsigned int			i3_u32_t;
typedef signed long long int		i3_s64_t;
typedef unsigned long long int		i3_u64_t;

typedef void				i3_void_t;
typedef char				i3_char_t;
typedef int				i3_int_t;
typedef unsigned int			i3_uint_t;
typedef long				i3_long_t;
typedef unsigned long			i3_ulong_t;
typedef i3_ulong_t			i3_addr_t;
typedef double				i3_double_t;
typedef size_t				i3_csize_t;

#ifdef __cplusplus
#define i3_none_t
#else /* __cplusplus */
typedef i3_void_t			i3_none_t;
#endif /* __cplusplus */



/****************************************************************************
 * genval
 ****************************************************************************/

typedef i3_s32_t			i3_genval32_t;

typedef i3_s64_t			i3_genval64_t;

typedef i3_genval32_t			i3_genval_t;



/****************************************************************************
 * index, offset, size, count
 ****************************************************************************/

#define I3_INDEX_NONE			(-1)
#define I3_OFFSET_NONE			I3_INDEX_NONE
#define I3_SIZE_NONE			I3_INDEX_NONE
#define I3_COUNT_NONE			I3_INDEX_NONE

typedef i3_s32_t			i3_index32_t;
typedef i3_index32_t			i3_offset32_t;
typedef i3_index32_t			i3_size32_t;
typedef i3_index32_t			i3_count32_t;

typedef i3_s64_t			i3_index64_t;
typedef i3_index64_t			i3_offset64_t;
typedef i3_index64_t			i3_count64_t;
typedef i3_index64_t			i3_size64_t;

typedef i3_index32_t			i3_index_t;
typedef i3_offset32_t			i3_offset_t;
typedef i3_size32_t			i3_size_t;
typedef i3_count32_t			i3_count_t;

typedef i3_u32_t			i3_uindex32_t;
typedef i3_uindex32_t			i3_uoffset32_t;
typedef i3_uindex32_t			i3_usize32_t;
typedef i3_uindex32_t			i3_ucount32_t;

typedef i3_u64_t			i3_uindex64_t;
typedef i3_uindex64_t			i3_uoffset64_t;
typedef i3_uindex64_t			i3_ucount64_t;
typedef i3_uindex64_t			i3_usize64_t;

typedef i3_uindex32_t			i3_uindex_t;
typedef i3_uoffset32_t			i3_uoffset_t;
typedef i3_usize32_t			i3_usize_t;
typedef i3_ucount32_t			i3_ucount_t;



/****************************************************************************
 * bool
 ****************************************************************************/

#define I3_BOOL_FALSE			0
#define I3_BOOL_FAIL			I3_BOOL_FALSE
#define I3_BOOL_TRUE			1
#define I3_BOOL_OK			I3_BOOL_TRUE

typedef i3_u8_t				i3_bool8_t;
typedef i3_u16_t			i3_bool16_t;
typedef i3_u32_t			i3_bool32_t;

typedef i3_bool32_t			i3_bool_t;



/****************************************************************************
 * truthval
 ****************************************************************************/

#define I3_TRUTHVAL_FALSE		0
#define I3_TRUTHVAL_TRUE		1
#define I3_TRUTHVAL_UNDEF		2

typedef i3_u32_t			i3_truthval_t;



/****************************************************************************
 * type, mode, flag, mask, state
 ****************************************************************************/

#define I3_TYPE_NONE			0
#define I3_MODE_NONE			I3_TYPE_NONE
#define I3_FLAG_NONE			I3_TYPE_NONE
#define I3_MASK_NONE			I3_TYPE_NONE
#define I3_STATE_NONE			I3_TYPE_NONE

typedef i3_u8_t				i3_type8_t;
typedef i3_type8_t			i3_mode8_t;
typedef i3_type8_t			i3_flag8_t;
typedef i3_type8_t			i3_mask8_t;
typedef i3_type8_t			i3_state8_t;

typedef i3_u16_t			i3_type16_t;
typedef i3_type16_t			i3_mode16_t;
typedef i3_type16_t			i3_flag16_t;
typedef i3_type16_t			i3_mask16_t;
typedef i3_type16_t			i3_state16_t;

typedef i3_u32_t			i3_type32_t;
typedef i3_type32_t			i3_mode32_t;
typedef i3_type32_t			i3_flag32_t;
typedef i3_type32_t			i3_mask32_t;
typedef i3_type32_t			i3_state32_t;

typedef i3_type32_t			i3_type_t;
typedef i3_mode32_t			i3_mode_t;
typedef i3_flag32_t			i3_flag_t;
typedef i3_mask32_t			i3_mask_t;
typedef i3_state32_t			i3_state_t;



/****************************************************************************
 * refcount
 ****************************************************************************/

typedef i3_count_t			i3_refcount_t;



/****************************************************************************
 * memindex, memoffset, memsize, memcount
 ****************************************************************************/

typedef i3_long_t			i3_memindex_t;
typedef i3_memindex_t			i3_memoffset_t;
typedef i3_memindex_t			i3_memsize_t;
typedef i3_memindex_t			i3_memcount_t;
typedef i3_type_t			i3_memtype_t;



/****************************************************************************
 * strindex, stroffset, strsize, strlength
 ****************************************************************************/

typedef i3_memindex_t			i3_strindex_t;
typedef i3_strindex_t			i3_stroffset_t;
typedef i3_strindex_t			i3_strsize_t;
typedef i3_strindex_t			i3_strlength_t;



/****************************************************************************
 * fileoffset, filesize
 ****************************************************************************/

typedef i3_s64_t			i3_fileoffset_t;
typedef i3_fileoffset_t			i3_filesize_t;



/****************************************************************************
 * psecs, nsecs, usecs, msecs, secs
 ****************************************************************************/

typedef i3_s64_t			i3_psecs_t;
typedef i3_s64_t			i3_nsecs_t;
typedef i3_s64_t			i3_usecs_t;
typedef i3_s64_t			i3_msecs_t;
typedef i3_s64_t			i3_secs_t;



/****************************************************************************
 * livar, id, variable, literal, lbd, tframe, dl, varsignat, dlsignat
 ****************************************************************************/

#define I3_ID_NONE			0
#define I3_LITVAR_NONE			0
#define I3_VARIABLE_NONE		I3_LITVAR_NONE
#define I3_LITERAL_NONE			I3_LITVAR_NONE
#define I3_DL_NONE			I3_COUNT_NONE

typedef i3_u32_t			i3_litvar_t;
typedef i3_u32_t			i3_id_t;
typedef i3_litvar_t			i3_variable_t;
typedef i3_litvar_t			i3_literal_t;
typedef i3_litvar_t			i3_lbd_t;
typedef i3_count_t			i3_tframe_t;
typedef i3_count_t			i3_dl_t;
typedef i3_u32_t			i3_varsignat_t;
typedef i3_u64_t			i3_dlsignat_t;



#endif /* !I3_ISAT3TYPES_H */
/******************************************************** Karsten Scheibler */
