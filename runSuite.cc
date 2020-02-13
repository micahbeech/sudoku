#include <iostream>
#include <sys/wait.h>
#include <fstream>   
#include <string>
#include <cstdlib>
#include <cstdio>

int system_wrapper(std::string cmd) {
        int ret = system(cmd.c_str());
        return WEXITSTATUS(ret);
}

// tests to see if a file exists in the current directory
bool file_test(const std::string &filename) {
	return system_wrapper("test -f " + filename) == 0;
}

// gets the next filename from f
bool get_filename(std::ifstream &f, std::string &name) {
	f >> std::noskipws;
	name = "";
	char c;

	while (f >> c) {
		if (c == ' ' || c == '\n') {
			return true;
		} else {				
			name += c;
		}
	}
	return false;
}

// determines if name is a real filename or just whitespace
bool real_filename(std::string &name) {
	for (unsigned int i = 0; i < name.size(); ++i) {
		if (name.at(i) != ' ' && name.at(i)!= '\n') {
			return true;
		}
	}
	return false;
}	

// runs the file test on program
bool run_test(std::string &filename, std::string &program) {
	bool args_exist = file_test(filename + ".args");
	bool in_exist = file_test(filename + ".in");
	
	const std::string args = filename + ".args";
	const std::string input = filename + ".in";
	const std::string output = filename + ".out";

	if (!file_test(output)) {
		std::cerr << output + " does not exist or is not readable" << std::endl;
		return false;
	}
	
	#if 0
	std::ifstream args_file{args};
	std::ifstream input_file{input};

	args_file >> std::noskipws;
	
	char m ='\0';
	while (args_file >> m) {
		if (m != ' ' && m != '	' && m != '\n') {
			args_exist = true;
			break;
		}
		args_exist = false;
	}
	if (m == '\0') args_exist = false;
	#endif

	FILE *f1 = popen("mktemp", "r");
	char a[200];
	fscanf(f1, "\%s", a);
	pclose(f1);
	std::string actual = std::string(a);

	if (args_exist && in_exist) {
		system_wrapper(program + " $(cat " + args + ") < " + input + " > " + actual);
	} else if (args_exist) {
		system_wrapper(program + " $(cat " + args + ") > " + actual);
	} else if (in_exist) {
		system_wrapper(program + " < " + input + " > " + actual);
	} else {
		//system_wrapper(program + " > " + actual);
		std::cerr << "Please provide an input or arguments file" << std::endl;
		return 5;
	}

	std::ifstream x{actual};
	std::ifstream y{output};
	char c;
	char d;
	bool ret = false;
	while (x >> c && y >> d) {
		if (c != d) {
			ret = true;
			break;
		}
	}
	y >> d;
	ret = c != d;

	if (ret) {
		std::cout << "Test failed: " << filename << std::endl;
		std::cout << "Args:" << std::endl;
		if (args_exist) system_wrapper("cat " + args);
		std::cout << "Input:" << std::endl;
		if (in_exist) system_wrapper("cat " + input);
		std::cout << "Expected:" << std::endl;
		system_wrapper("cat " + output);
		std::cout << "Actual:" << std::endl;
		system_wrapper("cat " + actual);
	}

	system_wrapper("rm " + actual);
	return true;
}

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Incorrect number of arguments supplied to runSuite" << std::endl;
		return 1;
	} else if (!file_test(argv[1])) {
		std::cerr << std::string(argv[1]) + " does not exist or is not readable" << std::endl;
		return 2;
	}

	std::ifstream suitefile{argv[1]};
	std::string filename;
	std::string program = std::string(argv[2]);

	while (get_filename(suitefile, filename)) {
	       if (real_filename(filename)) {
		       if (!run_test(filename, program)) return 3;
	       }
	}
	return 0;
}
