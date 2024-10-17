import os
import sys
import subprocess

from pathlib import Path
from typing import List


def list_tests(path: str) -> List[str]:
    tests = []
    for root, dirs, files in os.walk(path):
        for file in files:
            if file.endswith(".exe"):
                tests.append(os.path.join(root, file))
    return tests

def run_test(test: str, work_dir: str) -> int:
    print(f"\n")
    print(f"Running test: {test}")

    process = subprocess.Popen([test], cwd=work_dir, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
    for line in process.stdout:
        print(line, end='')
    process.wait()

    print(f"Test run finished: {test}")
    return process.returncode


def run_tests(tests_dir: str, work_dir: str) -> int:
    tests = list_tests(tests_dir)
    results = [run_test(test, work_dir) for test in tests]
    if any(results):
        return 1
    else:
        return 0


def main() -> int:
    tests_dir = Path(sys.argv[1])
    work_dir = Path(sys.argv[2])

    return run_tests(tests_dir, work_dir)

if __name__ == '__main__':
    sys.exit(main())
