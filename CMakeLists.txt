cmake_minimum_required(VERSION 3.12)

enable_testing()

SET(VAST_PATH "" CACHE STRING "path to vast")
SET(VAST_TARGET "hl" CACHE STRING "target ir, hl/ll/llvm")

SET(TEST_DB False CACHE STRING "enable test db")
SET(CLEAN_DB False CACHE STRING "enable clean db before test")
SET(NEO4J_USER "neo4j" CACHE STRING "neo4j user name")
SET(NEO4J_PASSWORD "neo4j" CACHE STRING "neo4j user password")
SET(NEO4J_ADDRESS "localhost:7687" CACHE STRING "neo4j address")
SET(NEO4J_DATABASE "neo4j" CACHE STRING "neo4j database name")
SET(NEO4J_UID_ALLOC_SIZE 100 CACHE STRING "neo4j uid allocate size")

configure_file(lit.site.cfg.py.in lit.site.cfg.py @ONLY)

SET(LIT_PATH "" CACHE STRING "path to lit")
SET(LIT_BIN_NAME "lit" CACHE STRING "lit bin name")
SET(TESTCASE "." CACHE STRING "testcases to run, list of files or directories, relative path to 'testcases' directory")
string(JOIN "/" LIT ${LIT_PATH} ${LIT_BIN_NAME})

SET(PARALLEL 1 CACHE STRING "number of parallel process to run tests")

add_test(
    NAME vast-test-cxx
    COMMAND ${LIT} -v ${TESTCASE} -j ${PARALLEL}
)
