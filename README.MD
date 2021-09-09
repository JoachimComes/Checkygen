CheckygenC unit-testing integrated in Doxygen

Joachim Comes

Abstract Checkygen generates tests from specifications inside the function body just like doxygen generates documentation from special comments above function definitions. At the same time checkygen reveals failed tests inside the Doxygen documentation.

Test driven development is today's call. Lots of methods and working environments assist TDD. To make sure that the writing of tests is really done before coding it would be useful to puttests and code closer together. This would be possible if the functions to be tested included their test specifications.

1 Test Driven Development

[https://eradman.com/posts/tdd-in-c.html||Eric Radman] puts it to the point: „The Internet is now littered with frameworks writing unit tests for C, which is unfortunate because they suggest that writing test code for C requires a kind of parallel project that is bolted on the side. Worse yet, papers and presentations on the subject suggest adapting your project to a C++ framework along with it's clumsy idioms. A dogged insistence on simplicity when structuring a project written in C enables you to pick the techniques that fit particular designs.“

In fact there is only one reason to write tests in “a kind of parallel project”: when coding and testing are different jobs of different people. This may have some advantages but this is definitely not the way of TDD.

Eric Radman suggests an approach similar to the one of MinUnit by John Brewer. Tests are executed by using some macros. But this tests need function mocks and a test runner, which calls them. Neither the tests are written close to the function nor are they executed automatically.

2 Document Driven Development

Test driven development is not all: without documentation it is worthless. With [https://www.doxygen.nl/index.html||Doxygen] documentations are generated from special comments inside the code. Comments and code are close together and can be read at once. While writing the code the requirements can be seen. In addition the Doxygen documentation shows this requirements in a more elegant form. The same should be true for tests. They should be written down inside the functions which are to be tested and not somewhere else. Thus code is written just behind the tests: who writes the code can also see the tests. At the same time, the test results should not only be sent to stdout but also more elegantly to the Doxygen documentation.

3 Putting it all together

Checkygen modifies the approach from Brewer and Radman. When the CHECKYGEN-flag is set each function runs all the tests the first time the function is called. The functions persist in comments, test specifications and code. That's all.

3.1 Unit Tests

For using Checkygen the code has to include checkygen.h. The code needs:

• a macro "DECLARE_TEST" in front of the main function.

• a macro "CREATE_TEST" just in the beginning of the main function

• a macro "REMOVE_TEST" at the end of the main function.

• Each function to be tested starts with a macro "START_TEST"

• followed by instructions for each test case and macros (only one per line) "TEST(a)" which test if "a" is true.

• Behind those tests a macro "STOP_TEST" is needed.

/* checkygen_example.c */checkygen.o is to link together with the other objects. If the program starts compiled with the CHECKYGEN flag each test will be executed only once. After this the tests are ignored. For demonstration purpose the code above is bad implemented: one of the test fails.

user@host:gcc -c -DCHECKYGEN checkygen_example.c checkygen.c

To show the test warning for the (e.g.) 1. test of function “multiple_of_two()” inside the Doxygen documentation a predefined Doxygen macro “\WRN{multiple_of_two1}” has to be written into the Doxygen documentation:

/**

After running the checkygen.sh script

user@host: ./checkygen.sh

the documentation shows a warning:


