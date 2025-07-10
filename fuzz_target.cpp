#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept> 

void test_deref_mom(std::string data) {
    // This function uses a null deref to see if mayhem catches it with 'mom' 
    if (data.size() >= 3) {
        if (data.c_str()[0] == 'm' && data.c_str()[1] == 'o' && data.c_str()[2] == 'm') {
            std::cout << "Found 'mom' corner case!\n";
            *((volatile int*)0) = 123; // guaranteed crash
        }
	}
}

void test_runtime_error_dad(std::string data) {
    // This function uses a runtime error to see if mayhem catches it with input 'dad'. 
    if (data.size() >= 3) {
        if (data.c_str()[0] == 'd' && data.c_str()[1] == 'a' && data.c_str()[2] == 'd') {
            std::cout << "Found 'dad' corner case!\n";
             throw std::runtime_error("Found 'dad' corner case!"); // Alternative: throw an exception
        }
    }
}

void test_abort_bug(std::string data) {
    // This function uses a null deref to see if mayhem catches it with 'bug' 

    //  abort() will normally pop-up a dialoge and then silently exit with code 3. 
    // This disables that behavior to simply crash, which Mayhem can detect.
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);

    if (data.size() >= 3) {
        if (data.c_str()[0] == 'b' && data.c_str()[1] == 'u' && data.c_str()[2] == 'g') {
            std::cout << "Found 'bug' corner case!\n";
            abort(); // Uncomment to crash on this condition
        }
    }

}


int main(int argc, char* argv[]) {


    if (argc < 2) {
        std::cerr << "Usage: fuzz_target <input_file>\n";
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
		std::cerr << "Error opening file: " << argv[1] << "\n";
        return 1;
    }

    std::string data((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

	std::cout << "Read " << data.c_str() << " from input file.\n";

	test_abort_bug(data);
	test_deref_mom(data);
	test_runtime_error_dad(data);

    return 0;
}