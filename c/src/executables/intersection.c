#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include "../framework/unused.h"
#include "../framework/malloc.h"
#include "../framework/types.h"
#include "../framework/opcode.h"
#include "../framework/pointer.h"
#include "../framework/argument.h"
#include "../framework/executable.h"
#include "../framework/write_bc.h"

const char * bc_executable_name = "intersection";
const char * bc_executable_description = "combines any number of bc streams using a csg intersection";
const char * bc_executable_usage_prefix = "";
const char * bc_executable_usage_suffix = " | [consumer of bc stream]";
const bc_boolean_t bc_executable_reads_model_from_stdin = BC_BOOLEAN_FALSE;
const bc_boolean_t bc_executable_reads_models_from_command_line_arguments = BC_BOOLEAN_TRUE;

void bc_executable_cli(void) {
}

void bc_executable_before_first_file(void) {
}

static bc_pointer_t bc__pointer_offset = 0;
static bc_boolean_t bc__written_at_least_one_previous_file;
static bc_argument_t bc__last_written;
static bc_argument_t bc__accumulated_value;
static bc_boolean_t bc__empty_file = BC_BOOLEAN_TRUE;

static bc_argument_t bc__write_argument(
  bc_argument_t argument
) {
  if (argument.pointer > BC_POINTER_MAX) {
    return argument;
  } else {
    argument.pointer += bc__pointer_offset;
    return argument;
  }
}

void bc_executable_nullary(
  bc_opcode_t opcode
) {
  bc__empty_file = BC_BOOLEAN_FALSE;
  bc__last_written = bc_write_bc_nullary(opcode);
}

void bc_executable_unary(
  bc_opcode_t opcode,
  bc_argument_t argument_a
) {
  bc__empty_file = BC_BOOLEAN_FALSE;
  bc__last_written = bc_write_bc_unary(
    opcode,
    bc__write_argument(argument_a)
  );
}

void bc_executable_binary(
  bc_opcode_t opcode,
  bc_argument_t argument_a,
  bc_argument_t argument_b
) {
  bc__empty_file = BC_BOOLEAN_FALSE;
  bc__last_written = bc_write_bc_binary(
    opcode,
    bc__write_argument(argument_a),
    bc__write_argument(argument_b)
  );
}

void bc_executable_ternary(
  bc_opcode_t opcode,
  bc_argument_t argument_a,
  bc_argument_t argument_b,
  bc_argument_t argument_c
) {
  bc__empty_file = BC_BOOLEAN_FALSE;
  bc__last_written = bc_write_bc_ternary(
    opcode,
    bc__write_argument(argument_a),
    bc__write_argument(argument_b),
    bc__write_argument(argument_c)
  );
}

void bc_executable_eof(void) {
  if (bc__empty_file) {
    return;
  }

  bc__empty_file = BC_BOOLEAN_TRUE;

  if (bc__written_at_least_one_previous_file) {
    bc__last_written = bc_write_bc_binary(
      BC_OPCODE_MAXIMUM,
      bc__accumulated_value,
      bc__last_written
    );
  } else {
    bc__written_at_least_one_previous_file = BC_BOOLEAN_TRUE;
  }

  bc__accumulated_value = bc__last_written;
  bc__pointer_offset = bc__last_written.pointer + 1;
}

void bc_executable_after_last_file(void) {
}

bc_number_t bc_executable_get_parameter(
  void * parameter_context,
  size_t iteration,
  bc_opcode_id_t id
) {
  BC_UNUSED(parameter_context);
  BC_UNUSED(iteration);
  BC_UNUSED(id);
  return 0.0f;
}
