#!/bin/zsh

# chdir
cd "$(dirname "$(realpath "$0")")"

# load config
source config

# parse args
zparseopts -D - -vast-target:=vast_target
vast_target="${vast_target##*[= ]}"
if [[ -n ${vast_target} ]]; then
    VAST_TARGET=${vast_target}
fi

if [ -z ${LIT_BIN_NAME} ]; then
    LIT_BIN_NAME='lit'
fi
if [ -z ${TESTCASE} ]; then
    TESTCASE='.'
fi
if [ -z ${VAST_TARGET} ]; then
    VAST_TARGET='hl'
fi

# pull the latest commit
git fetch &> /dev/null
git pull &> /dev/null

# config and run test
BUILD_DIR="build"
if [[ ! -d ${BUILD_DIR} ]]; then
    mkdir ${BUILD_DIR}
fi
cd ${BUILD_DIR}

cmake .. \
    -DVAST_PATH=${VAST_PATH} -DLIT_PATH=${LIT_PATH} -DLIT_BIN_NAME=${LIT_BIN_NAME} \
    -DTESTCASE=${TESTCASE} -DVAST_TARGET=${VAST_TARGET} \
    -DPARALLEL=${PARALLEL} -DPARALLEL_THREAD=${PARALLEL_THREAD} -DPARALLEL_BATCH_SIZE=${PARALLEL_BATCH_SIZE} \
    -DTEST_DB=${TEST_DB} -DCLEAN_DB=${CLEAN_DB} \
    -DNEO4J_ADDRESS=${NEO4J_ADDRESS} -DNEO4J_UID_ALLOC_SIZE=${NEO4J_UID_ALLOC_SIZE} \
    -DVASTDB_PROFILE_LOG=${VASTDB_PROFILE_LOG} \
    &> /dev/null

ctest &> /dev/null

cd ..

# collect test result
python3 collect.py $*
