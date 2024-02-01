-Igoogletest/googletest/include: This flag tells the compiler where to find the Google Test headers.
-Lgoogletest/build/lib: This flag tells the linker where to find the Google Test libraries.
-lgtest -lgtest_main: These flags tell the linker to link against the Google Test libraries. gtest_main provides a main function so you don't need to write one; if you're providing your own main(), you might not need -lgtest_main.
-pthread: Google Test needs this flag for threading support.
-o test_json: This specifies the output file name for the compiled executable.

g++ -std=c++17 -Igoogletest/googletest/include test/test_json.cpp -lgtest -lgtest_main -pthread -o test_json

