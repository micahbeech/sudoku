import argparse
import os

def fileExist(filename):
    try:
        with open(filename, 'r') as f:
            return True
    except IOError as e:
        return False

def runTest(filename, program):
    input = filename + ".in"
    args = filename + ".args"
    output = filename + ".out"

    if not fileExist(output):
        print("Could not find file", filename + ".out. Omitting test", filename + ".")
        return

    actual = os.popen("mktemp").read()

    if fileExist(input) and fileExist(args):
        os.system(program + " $(cat " + args + ") < " + input + " > " + actual)
    elif fileExist(input):
        os.system(program + " < " + input + " > " + actual)
    elif fileExist(output):
        os.system(program + " $(cat " + args + ")  > " + actual)
    else:
        os.system(program + " > " + actual)
    
    if not open(actual.strip()).read() == open(output).read():
        print("Test failed:", filename)
        print("Args:")
        if fileExist(args):
            os.system("cat " + args)
        print("Input:")
        if fileExist(input):
            os.system("cat " + input)
        print("Expected:")
        os.system("cat " + output)
        print("Actual:")
        os.system("cat " + actual)

    os.system("rm " + actual)

def main():
    parser = argparse.ArgumentParser(description="Runs input/output tests for a given program.")
    parser.add_argument('suitefile', help="Text file with name stubs of test files")
    parser.add_argument('program', help="Name of the program to be tested")

    args = vars(parser.parse_args())

    suiteFile = args['suitefile']
    programName = args['program']

    if fileExist(suiteFile):
        for filename in open(suiteFile).readlines():
            runTest(filename.strip(), programName)
    else:
        print("Could not open " + suiteFile)
        return

main()