function number_parameter {
  check_failure "${BC_EXECUTABLE_PREFIX}$1${BC_EXECUTABLE_SUFFIX} -$2" "expected a value for command line argument -$2/--$3"
  check_failure "${BC_EXECUTABLE_PREFIX}$1${BC_EXECUTABLE_SUFFIX} --$3" "expected a value for command line argument -$2/--$3"

  check_failure "${BC_EXECUTABLE_PREFIX}$1${BC_EXECUTABLE_SUFFIX} -$2 wadjilad" "unable to parse command line argument -$2/--$3 value \"wadjilad\" as a number"
  check_failure "${BC_EXECUTABLE_PREFIX}$1${BC_EXECUTABLE_SUFFIX} --$3 wadjilad" "unable to parse command line argument -$2/--$3 value \"wadjilad\" as a number"

  check_failure "${BC_EXECUTABLE_PREFIX}$1${BC_EXECUTABLE_SUFFIX} -$2 53.34wa" "unable to parse command line argument -$2/--$3 value \"53.34wa\" as a number"
  check_failure "${BC_EXECUTABLE_PREFIX}$1${BC_EXECUTABLE_SUFFIX} --$3 53.34wa" "unable to parse command line argument -$2/--$3 value \"53.34wa\" as a number"
}
