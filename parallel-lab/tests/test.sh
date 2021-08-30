#!/bin/bash

echo "Running test cases..."

export OMP_NUM_THREADS=4

# Determine cwd
cwd=$(pwd | rev | cut -d"/" -f1 | rev)
if [[ "${cwd}" == "tests" ]]; then
  # Being run from within tests directory, so adjust paths accordingly
  prefix=".."
else
  # Being run from main directory
  prefix="."
fi

# Build to get latest version
make

rm -rf ${prefix}/tests/temp
mkdir -p ${prefix}/tests/temp

nTests=2
nPasses=0
nFailures=0
for test in $(seq 1 ${nTests}); do
  # Get runtime of base implementation
  /usr/bin/time -o ${prefix}/tests/temp/base.time -f "%E" ${prefix}/tests/base ${prefix}/tests/test${test}.in >/dev/null 2>&1

  # Get runtime of instructor implementation
  /usr/bin/time -o ${prefix}/tests/temp/instructor.time -f "%E" ${prefix}/tests/instructor-sol ${prefix}/tests/test${test}.in >/dev/null 2>&1

  # Get runtime of student implementation
  /usr/bin/time -o ${prefix}/tests/temp/student.time -f "%E" ${prefix}/nbody ${prefix}/tests/test${test}.in 2>/dev/null >${prefix}/tests/temp/test${test}.out
  diff -q ${prefix}/tests/test${test}.out ${prefix}/tests/temp/test${test}.out >/dev/null
  if [[ "$?" == "0" ]]; then
    echo -e "Test ${test}\t\tPASSED"

    # Analyze runtimes
    baseRuntime=$(cat ${prefix}/tests/temp/base.time)
    instructorRuntime=$(cat ${prefix}/tests/temp/instructor.time)
    studentRuntime=$(cat ${prefix}/tests/temp/student.time)
    echo -e "\tBase runtime:\t\t\t${baseRuntime} (M:SS.ss)"
    echo -e "\tInstructor solution runtime:\t${instructorRuntime} (M:SS.ss)"
    echo -e "\tYour runtime:\t\t\t${studentRuntime} (M:SS.ss)"

    nPasses=$((${nPasses} + 1))
  else
    echo -e "Test ${test}\t\t\tFAILED"
    nFailures=$((${nFailures} + 1))
  fi
done

echo ""
echo "Passed ${nPasses}/${nTests} tests"
echo "Runtime comparisons are inline above"

rm -rf ${prefix}/tests/temp
