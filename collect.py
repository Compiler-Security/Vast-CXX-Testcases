#!/usr/bin/python

import re
import os, sys, argparse
from typing import Dict, List, Tuple


build_dir = "build"
testlog_file = os.path.join(build_dir, "Testing/Temporary/LastTest.log")
testcase_dir = "testcases"

testcases : Dict[str, Tuple[str, List[str]]] = dict() # { testcase_name : (state, [categories...]) }
cat_statistics : Dict[str, List[int]] = dict() # { category_name : [num_pass, num_all] }

dir_not_cat = ["ignore", "Inputs"]
categories = sorted([dir for dir in os.listdir(testcase_dir) if os.path.isdir(os.path.join(testcase_dir, dir)) and not (dir in dir_not_cat)])

num_pass = 0
num_fail = 0

pat_pass = r"PASS: vast-test-cxx :: (?:\S+/)*([^/\s]+)\s"
pat_fail = r"FAIL: vast-test-cxx :: (?:\S+/)*([^/\s]+)\s"

with open(testlog_file, "r", encoding="utf-8") as testlog:

    for line in testlog:
        line = line.strip('\n')

        match = re.search(pat_pass, line)
        if match:
            testcase = match.group(1)
            testcases[testcase] = ("pass", [])
            num_pass += 1
            continue
        
        match = re.search(pat_fail, line)
        if match:
            testcase = match.group(1)
            testcases[testcase] = ("fail", [])
            num_fail += 1
    
unknown_pass = num_pass
unknown_all = num_pass + num_fail

for cat in categories:
    testcases_in_cat = os.listdir(os.path.join(testcase_dir, cat))
    cat_statistics[cat] = [0, 0]

    for testcase in testcases_in_cat:
        if not testcase in testcases:
            continue
        testcases[testcase][1].append(cat)

        if testcases[testcase][0] == "pass":
            cat_statistics[cat][0] += 1
            unknown_pass -= 1
        cat_statistics[cat][1] += 1
        unknown_all -= 1

parser = argparse.ArgumentParser(description="mld_test")
parser.add_argument("--reportfile", 
                    action="store", 
                    help="the location to print results, for test automation")
args = parser.parse_args()
if args.reportfile:
    fd = open(args.reportfile, "w")
else:
    fd = sys.stdout
fd.write(f"pass {num_pass}/{num_pass+num_fail}\n\n")
for cat, stat in cat_statistics.items():
    fd.write(f"{cat}: pass {stat[0]}/{stat[1]}\n")
# fd.write(f"unknown: pass {unknown_pass}/{unknown_all}\n")
