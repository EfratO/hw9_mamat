#These are variables. We define CXX, CXXFALGS, CXXLINK, OBJS, EXEC, RM

CXX     = g++
CXXFLAGS = -Wall -g -std=c++11
CXXLINK = $(CXX)
OBJS = string.o field.o ip.o port.o
EXEC = firewall.exe
RM = rm -f *.o *.exe libfirewall.so


$(EXEC): main.o libfirewall.so
	$(CXXLINK) main.o -o $(EXEC) -lfirewall -linput -L.
	
libfirewall.so: $(OBJS) 
	$(CXXLINK) -shared $(OBJS) -o libfirewall.so 

main.o: main.cpp ip.h port.h input.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp
	
ip.o: ip.h ip.cpp field.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.h port.cpp field.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp		
	
field.o: field.h field.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp
	
string.o: string.h string.cpp 
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp
	
clean:
	$(RM)
