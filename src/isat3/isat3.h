/****************************************************************************
 ****************************************************************************
 *
 * isat3.h
 *
 ****************************************************************************
 *
 * NOTE: isat3_solve_*() functions are using setitimer and will register a
 *       signal handler if the specified timeout is larger 0
 *
 ****************************************************************************
 ****************************************************************************/





#ifndef I3_ISAT3_H
#define I3_ISAT3_H

#include "isat3types.h"




/****************************************************************************
 *
 * global data structures, types, defines and variables
 *
 ****************************************************************************/




#define ISAT3_PROBLEM_TYPE_NONE			I3_MODE_NONE
#define ISAT3_PROBLEM_TYPE_GENERIC		1
#define ISAT3_PROBLEM_TYPE_OPEN_FAULTS		2
#define ISAT3_PROBLEM_TYPE_WSA			3

#define ISAT3_RESULT_UNKNOWN			1
#define ISAT3_RESULT_UNSATISFIABLE		2
#define ISAT3_RESULT_UNSAT			ISAT3_RESULT_UNSATISFIABLE
#define ISAT3_RESULT_SATISFIABLE		3
#define ISAT3_RESULT_SAT			ISAT3_RESULT_SATISFIABLE
#define ISAT3_RESULT_SATISFIABLE_WITH_ALL	4
#define ISAT3_RESULT_SAT_WITH_ALL		ISAT3_RESULT_SATISFIABLE_WITH_ALL
#define ISAT3_RESULT_SATISFIABLE_WITH_SOME	5
#define ISAT3_RESULT_SAT_WITH_SOME		ISAT3_RESULT_SATISFIABLE_WITH_SOME
#define ISAT3_RESULT_CANDIDATE_SOLUTION		6
#define ISAT3_RESULT_CAND_SOL			ISAT3_RESULT_CANDIDATE_SOLUTION
#define ISAT3_RESULT_SAFE			7
#define ISAT3_RESULT_UNSAFE			8
#define ISAT3_RESULT_UNSAFE_WITH_ALL		9
#define ISAT3_RESULT_UNSAFE_WITH_SOME		10

#define ISAT3_MAX_TFRAME			1000000000

#define ISAT3_NODE_UOP_PRIME			0x01
#define ISAT3_NODE_UOP_NOT			0x02
#define ISAT3_NODE_UOP_ABS			0x03
#define ISAT3_NODE_UOP_MINUS			0x04
#define ISAT3_NODE_UOP_SIN			0x05
#define ISAT3_NODE_UOP_COS			0x06
#define ISAT3_NODE_UOP_EXP			0x07
#define ISAT3_NODE_UOP_EXP2			0x08
#define ISAT3_NODE_UOP_EXP10			0x09
#define ISAT3_NODE_UOP_LOG			0x0a
#define ISAT3_NODE_UOP_LOG2			0x0b
#define ISAT3_NODE_UOP_LOG10			0x0c

#define ISAT3_NODE_BOP_AND			0x10
#define ISAT3_NODE_BOP_NAND			0x11
#define ISAT3_NODE_BOP_OR			0x12
#define ISAT3_NODE_BOP_NOR			0x13
#define ISAT3_NODE_BOP_XOR			0x14
#define ISAT3_NODE_BOP_XNOR			0x15
#define ISAT3_NODE_BOP_IMPLIES			0x16
#define ISAT3_NODE_BOP_IFF			0x17
#define ISAT3_NODE_BOP_LESS			0x18
#define ISAT3_NODE_BOP_LESS_EQUAL		0x19
#define ISAT3_NODE_BOP_GREATER			0x1a
#define ISAT3_NODE_BOP_GREATER_EQUAL		0x1b
#define ISAT3_NODE_BOP_EQUAL			0x1c
#define ISAT3_NODE_BOP_NOT_EQUAL		0x1d
#define ISAT3_NODE_BOP_MIN			0x1e
#define ISAT3_NODE_BOP_MAX			0x1f
#define ISAT3_NODE_BOP_ADD			0x20
#define ISAT3_NODE_BOP_SUB			0x21
#define ISAT3_NODE_BOP_MULT			0x22
#define ISAT3_NODE_BOP_POWER			0x23
#define ISAT3_NODE_BOP_ROOT			0x24

#define ISAT3_NODE_NOP_AND			0x30
#define ISAT3_NODE_NOP_NAND			0x31
#define ISAT3_NODE_NOP_OR			0x32
#define ISAT3_NODE_NOP_NOR			0x33
#define ISAT3_NODE_NOP_XOR			0x34
#define ISAT3_NODE_NOP_XNOR			0x35
#define ISAT3_NODE_NOP_ADD			0x36
#define ISAT3_NODE_NOP_MULT			0x37

struct isat3_settings;
struct isat3;
struct isat3_node;




/****************************************************************************
 *
 * global functions
 *
 ****************************************************************************/




I3_EXTERN const i3_char_t *
isat3_get_version_string(
	i3_none_t);

I3_EXTERN i3_void_t
isat3_setup(
	i3_none_t);

I3_EXTERN i3_void_t
isat3_cleanup(
	i3_none_t);

I3_EXTERN i3_memsize_t
isat3_settings_get_struct_size(
	i3_none_t);

I3_EXTERN struct isat3_settings *
isat3_settings_init(
	struct isat3_settings		*is3_set);

I3_EXTERN i3_void_t
isat3_settings_deinit(
	struct isat3_settings		*is3_set);

I3_EXTERN i3_void_t
isat3_settings_set_problem_type(
	struct isat3_settings		*is3_set,
	i3_type_t			problem_type);

I3_EXTERN i3_void_t
isat3_settings_set_trace_file(
	struct isat3_settings		*is3_set,
	const i3_char_t			*path);

I3_EXTERN i3_void_t
isat3_settings_set_msw(
	struct isat3_settings		*is3_set,
	i3_double_t			msw);

I3_EXTERN i3_void_t
isat3_settings_set_mpr(
	struct isat3_settings		*is3_set,
	i3_double_t			mpr);

I3_EXTERN i3_memsize_t
isat3_get_struct_size(
	i3_none_t);

I3_EXTERN const i3_char_t *
isat3_get_result_string(
	i3_type_t			result);

I3_EXTERN i3_bool_t
isat3_result_contains_solution(
	i3_type_t			result);

I3_EXTERN i3_bool_t
isat3_result_contains_possible_solution(
	i3_type_t			result);

I3_EXTERN struct isat3 *
isat3_init(
	struct isat3			*is3);

I3_EXTERN struct isat3 *
isat3_init_with_settings(
	struct isat3			*is3,
	const struct isat3_settings	*is3_set);

I3_EXTERN i3_void_t
isat3_deinit(
	struct isat3			*is3);

I3_EXTERN struct isat3_node *
isat3_node_create_constant_false(
	struct isat3			*is3);

I3_EXTERN struct isat3_node *
isat3_node_create_constant_true(
	struct isat3			*is3);

I3_EXTERN struct isat3_node *
isat3_node_create_constant_integer(
	struct isat3			*is3,
	i3_s32_t			constant);

I3_EXTERN struct isat3_node *
isat3_node_create_constant_float(
	struct isat3			*is3,
	i3_double_t			constant);

I3_EXTERN struct isat3_node *
isat3_node_create_define(
	struct isat3			*is3,
	const i3_char_t			*name,
	struct isat3_node		*number);

I3_EXTERN struct isat3_node *
isat3_node_create_variable_boole(
	struct isat3			*is3,
	const i3_char_t			*name);

I3_EXTERN struct isat3_node *
isat3_node_create_variable_integer(
	struct isat3			*is3,
	const i3_char_t			*name,
	i3_s32_t			lower_bound,
	i3_s32_t			upper_bound);

I3_EXTERN struct isat3_node *
isat3_node_create_variable_float(
	struct isat3			*is3,
	const i3_char_t			*name,
	i3_double_t			lower_bound,
	i3_double_t			upper_bound);

I3_EXTERN struct isat3_node *
isat3_node_create_unary_operation(
	struct isat3			*is3,
	i3_type_t			uop,
	struct isat3_node		*operand);

I3_EXTERN struct isat3_node *
isat3_node_create_binary_operation(
	struct isat3			*is3,
	i3_type_t			bop,
	struct isat3_node		*operand1,
	struct isat3_node		*operand2);

I3_EXTERN struct isat3_node *
isat3_node_create_ternary_operation(
	struct isat3			*is3,
	i3_type_t			nop,
	struct isat3_node		*operand1,
	struct isat3_node		*operand2,
	struct isat3_node		*operand3);

I3_EXTERN struct isat3_node *
isat3_node_create_quaternary_operation(
	struct isat3			*is3,
	i3_type_t			nop,
	struct isat3_node		*operand1,
	struct isat3_node		*operand2,
	struct isat3_node		*operand3,
	struct isat3_node		*operand4);

I3_EXTERN struct isat3_node *
isat3_node_create_quinary_operation(
	struct isat3			*is3,
	i3_type_t			nop,
	struct isat3_node		*operand1,
	struct isat3_node		*operand2,
	struct isat3_node		*operand3,
	struct isat3_node		*operand4,
	struct isat3_node		*operand5);

I3_EXTERN struct isat3_node *
isat3_node_create_senary_operation(
	struct isat3			*is3,
	i3_type_t			nop,
	struct isat3_node		*operand1,
	struct isat3_node		*operand2,
	struct isat3_node		*operand3,
	struct isat3_node		*operand4,
	struct isat3_node		*operand5,
	struct isat3_node		*operand6);

I3_EXTERN struct isat3_node *
isat3_node_create_septenary_operation(
	struct isat3			*is3,
	i3_type_t			nop,
	struct isat3_node		*operand1,
	struct isat3_node		*operand2,
	struct isat3_node		*operand3,
	struct isat3_node		*operand4,
	struct isat3_node		*operand5,
	struct isat3_node		*operand6,
	struct isat3_node		*operand7);

I3_EXTERN struct isat3_node *
isat3_node_create_octary_operation(
	struct isat3			*is3,
	i3_type_t			nop,
	struct isat3_node		*operand1,
	struct isat3_node		*operand2,
	struct isat3_node		*operand3,
	struct isat3_node		*operand4,
	struct isat3_node		*operand5,
	struct isat3_node		*operand6,
	struct isat3_node		*operand7,
	struct isat3_node		*operand8);

I3_EXTERN struct isat3_node *
isat3_node_create_nonary_operation(
	struct isat3			*is3,
	i3_type_t			nop,
	struct isat3_node		*operand1,
	struct isat3_node		*operand2,
	struct isat3_node		*operand3,
	struct isat3_node		*operand4,
	struct isat3_node		*operand5,
	struct isat3_node		*operand6,
	struct isat3_node		*operand7,
	struct isat3_node		*operand8,
	struct isat3_node		*operand9);

I3_EXTERN struct isat3_node *
isat3_node_create_from_string(
	struct isat3			*is3,
	const i3_char_t			*string);

I3_EXTERN i3_void_t
isat3_node_destroy(
	struct isat3			*is3,
	struct isat3_node		*node);

I3_EXTERN const i3_char_t *
isat3_node_get_variable_name(
	struct isat3			*is3,
	const struct isat3_node		*node);

I3_EXTERN i3_type_t
isat3_solve_expr(
	struct isat3			*is3,
	struct isat3_node		*expr,
	i3_usecs_t			timeout);

I3_EXTERN i3_type_t
isat3_solve_bmc(
	struct isat3			*is3,
	struct isat3_node		*init,
	struct isat3_node		*trans,
	struct isat3_node		*target,
	i3_tframe_t			start_tframe,
	i3_tframe_t			max_tframe,
	i3_usecs_t			timeout);

I3_EXTERN i3_void_t
isat3_push_btpoint(
	struct isat3			*is3);

I3_EXTERN i3_void_t
isat3_push_btpoint_name(
	struct isat3			*is3,
	const i3_char_t			*name);

I3_EXTERN i3_void_t
isat3_pop_btpoint(
	struct isat3			*is3,
	i3_count_t			number);

I3_EXTERN i3_void_t
isat3_pop_btpoint_name(
	struct isat3			*is3,
	const i3_char_t			*name);

I3_EXTERN i3_void_t
isat3_add_constraint(
	struct isat3			*is3,
	struct isat3_node		*constraint);

I3_EXTERN i3_type_t
isat3_solve_constraints(
	struct isat3			*is3,
	i3_usecs_t			timeout);

I3_EXTERN i3_tframe_t
isat3_get_tframe(
	struct isat3			*is3);

I3_EXTERN i3_truthval_t
isat3_get_truth_value(
	struct isat3			*is3,
	const struct isat3_node		*node,
	i3_tframe_t			tframe);

I3_EXTERN i3_bool_t
isat3_is_lower_bound_strict(
	struct isat3			*is3,
	const struct isat3_node		*node,
	i3_tframe_t			tframe);

I3_EXTERN i3_bool_t
isat3_is_upper_bound_strict(
	struct isat3			*is3,
	const struct isat3_node		*node,
	i3_tframe_t			tframe);

I3_EXTERN i3_double_t
isat3_get_lower_bound(
	struct isat3			*is3,
	const struct isat3_node		*node,
	i3_tframe_t			tframe);

I3_EXTERN i3_double_t
isat3_get_upper_bound(
	struct isat3			*is3,
	const struct isat3_node		*node,
	i3_tframe_t			tframe);




/****************************************************************************
 *
 * for compatibility with earlier versions
 *
 ****************************************************************************/




I3_EXTERN struct isat3 *
isat3_init_with_problem_type(
	struct isat3			*is3,
	i3_type_t			problem_type);

I3_EXTERN struct isat3 *
isat3_init_with_msw_mpr(
	struct isat3			*is3,
	i3_double_t			msw,
	i3_double_t			mpr);

I3_EXTERN struct isat3 *
isat3_init_with_problem_type_and_trace_file(
	struct isat3			*is3,
	i3_type_t			problem_type,
	const i3_char_t			*path);

I3_EXTERN struct isat3 *
isat3_init_with_problem_type_and_trace_file_and_msw_mpr(
	struct isat3			*is3,
	i3_type_t			problem_type,
	const i3_char_t			*path,
	i3_double_t			msw,
	i3_double_t			mpr);



#endif /* !I3_ISAT3_H */
/******************************************************** Karsten Scheibler */
