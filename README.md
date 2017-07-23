EE 298K Project 1

REFERENCES:
http://en.wikipedia.org/wiki/SHA-1
http://tools.ietf.org/html/rfc3174

COMPILATION:
1. Run download-ext script to clone google test and build it
2. Go to the build folder
   a. if you want to run unit test, run
      cmake -Dtest=ON .. && make
   b. if you want to run the package, run
      cmake .. && make

EXECUTION:
1. For unit test, run the command below in the build folder
   ./ut
2. For the package, run the command below in the build folder
   ./out <text-file>
