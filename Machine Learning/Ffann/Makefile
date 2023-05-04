CC=g++
CFLAGS=-Wall

all: main.exe gennet.exe netpsp.exe

main.exe: main.cpp
	$(CC) $(CFLAGS) -o main.exe main.cpp

gennet.exe: gennet.cpp
	$(CC) $(CFLAGS) -o gennet.exe gennet.cpp

netpsp.exe: netpsp.cpp
	$(CC) $(CFLAGS) -o netpsp.exe netpsp.cpp
clean:
	del main.exe gennet.exe netpsp.exe
