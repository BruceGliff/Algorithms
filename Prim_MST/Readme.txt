Tested on Windows10
Should work fine on Linux

Default building with scripts launchCMake.bat or .sh depends on OS

Executable file Prim_MST.exe with test folder will be in ./build/bin/Release
Launch:
    Prim_MST {input file} {output file}

If there is no input file, then data gets from input stream
If there is no output file, then output goes to output stream
Output file has to be right after input file. No way to specify only output without input file

Examples:
    Prim_MST.exe ./test/input/input000.txt ./test/output/output000.txt
    Prim_MST.exe ./test/input/input001.txt > ./test/output/output001.txt
    Prim_MST.exe < ./test/input/input002.txt > ./test/output/output002.txt
    Prim_MST.exe

NO:
    Prim_MST.exe ./test/output/output00X.txt as output00X will be considered as input file

converter.cc is just for me to convert matrix into input format