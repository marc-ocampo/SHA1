EE 298K Project 1

REFERENCES:
http://en.wikipedia.org/wiki/SHA-1
http://tools.ietf.org/html/rfc3174

COMPILATION:
0. Create ext folder
1. Run download-ext script to clone google test and build it
2. Go to the build folder (create the folder if needed) and run
   cmake .. && make

EXECUTION:
1. For unit test, run the command below in the build folder
   ./ut
2. For the package, run the command below in the build folder
   ./out <text-file>
