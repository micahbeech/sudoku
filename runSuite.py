import argparse
import os

def fileExist(filename):
    try:
        with open(filename, 'r') as f:
            return True
    except IOError as e:
        return False

def runTest(filename, program, directory, noError):
    input = directory + filename + ".in"
    args = directory + filename + ".args"
    output = directory + filename + ".out"
    error = " 2> /dev/null" if noError else ""

    if not fileExist(output):
        print("Could not find file", output + ". Omitting test", filename + ".")
        return

    actual = os.popen("mktemp").read().strip()

    if fileExist(input) and fileExist(args):
        os.system(program + " $(cat " + args + ") < " + input + " > " + actual + error)
    elif fileExist(input):
        os.system(program + " < " + input + " > " + actual + error)
    elif fileExist(output):
        os.system(program + " $(cat " + args + ")  > " + actual + error)
    else:
        os.system(program + " > " + actual + error)
    
    if not open(actual).read() == open(output).read():
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
    path = os.popen("pwd").read().strip()

    parser = argparse.ArgumentParser(description="Runs input/output tests for a given program.")
    parser.add_argument('program', help="Name of the program to be tested")
    parser.add_argument('-f', '--suitefile', nargs='?', default="suite.txt", help="Text file with name stubs of test files. Defaults to suite.txt")
    parser.add_argument('-d', '--directory', nargs='?', default=path, help="Path to directory with suitefile and test files from current directory. Defaults to current directory.")
    parser.add_argument('-e', '--error', action="store_true", help="Surpress output to stderr")

    args = vars(parser.parse_args())

    suiteFile = args['suitefile']
    programName = args['program']
    directory = args['directory']
    error = args['error']
    
    if directory[-1:] != '/':
        directory += "/"

    suiteFile = directory + suiteFile

    if fileExist(suiteFile):
        for filename in open(suiteFile).readlines():
            runTest(filename.strip(), programName, directory, error)
    else:
        print("Could not open " + suiteFile)
        return

main()
