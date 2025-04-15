# new file : `type nul > filename.cpp`
# run : `.\run.ps1 filename.cpp`
g++ -std=c++17 -O2 -Wall $args[0] -o main
cat in.txt | .\main | Out-File -FilePath out.txt