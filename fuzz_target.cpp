﻿#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <assert.h>
#include <windows.h>


void test_address_sanitizer_boo(std::string data) {
    // This function uses a null deref to see if mayhem catches it with 'address_sanitizer' 
    if (data.size() >= 3) {
        if (data.c_str()[0] == 'b' && data.c_str()[1] == 'o' && data.c_str()[2] == 'o') {
            // Note: this will crash powershell in MSVC. 
            std::cout << "Found 'boo' address sanitizer corner case!\n";
            int* x = new int[100];
            x[100] = 5; 
            delete[] x;
        }
    }
}

void test_null_deref_mom(std::string data) {
    // This function uses a null deref to see if mayhem catches it with 'mom' 
    if (data.size() >= 3) {
        if (data.c_str()[0] == 'm' && data.c_str()[1] == 'o' && data.c_str()[2] == 'm') {
            std::cout << "Found 'mom' null deref corner case!\n";
            *((volatile int*)0) = 123; // guaranteed crash
        }
	}
}

void test_runtime_error_dad(std::string data) {
    // This function uses a runtime error to see if mayhem catches it with input 'dad'. 
    if (data.size() >= 3) {
        if (data.c_str()[0] == 'd' && data.c_str()[1] == 'a' && data.c_str()[2] == 'd') {
            std::cout << "Found 'dad' corner case!\n";
             throw std::runtime_error("Found 'dad' runtime_error corner case!"); // Alternative: throw an exception
        }
    }
}

void test_assert_cab(std::string data) {
    if (data.size() >= 3) {
        if (data.c_str()[0] == 'c' && data.c_str()[1] == 'a' && data.c_str()[2] == 'b') {
            std::cout << "Found 'cab' assert corner case!\n";
            assert(1 == 0);
        }
    }
}

void test_raise_fail_fast_dog(std::string data) {
    if (data.size() >= 3) {
        if (data.c_str()[0] == 'd' && data.c_str()[1] == 'o' && data.c_str()[2] == 'g') {
            std::cout << "Found 'dog' RaiseFailFastException!\n";
            RaiseFailFastException(nullptr, nullptr, 0);
        }
    }
}

void test_abort_set_behavior_set(std::string data) {
    // This function uses a null deref to see if mayhem catches it with 'set_behavior' 
    if (data.size() >= 3) {
        if (data.c_str()[0] == 's' && data.c_str()[1] == 'e' && data.c_str()[2] == 't') {
            std::cout << "Found 'set' set_abort_behavior + abort corner case!\n";
            //  abort() will normally pop-up a dialoge and then silently exit with code 3. 
            // This disables that behavior to simply crash.
            _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
            abort(); // abort(). You'll see this in the crash 

        }
    }
}

void test_abort_bug(std::string data) {
    // This function uses a null deref to see if mayhem catches it with 'bug' 

    if (data.size() >= 3) {
        if (data.c_str()[0] == 'b' && data.c_str()[1] == 'u' && data.c_str()[2] == 'g') {
            std::cout << "Found 'bug' abort corner case!\n";
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
	test_null_deref_mom(data);
	test_runtime_error_dad(data);
	test_abort_set_behavior_set(data);
	test_address_sanitizer_boo(data);
	test_raise_fail_fast_dog(data);
	test_assert_cab(data);

    return 0;
}