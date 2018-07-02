g++ -std=c++11 -o b brute.cpp
g++ -std=c++11 -o a find.cpp
:loop
	b.exe > data.txt
	a.exe < data.txt
goto loop
cmd