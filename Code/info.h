#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "IPHLPAPI.lib")


#include <Windows.h>
#include <iostream>
#include <string.h>
#include <iomanip>
#include <string> 

#include <Iphlpapi.h>
#include <chrono>
#include <sstream>
#include <time.h>
#include <locale.h>

#include <iphlpapi.h>
//#include <stdio.h>
//#include <stdlib.h>
//#pragma comment(lib, "IPHLPAPI.lib")

#define INFO_BUFFER_SIZE 32767
#define in_label std::cout << std::left << std::setw(30) 
#define in_data std::cout << std::right << std::setw(40)

void displayDataFromRegistry(const char *label, const char *path, const char *queryPath);
void displayData_TIME_FromRegistry(const char *label, const char *path, const char *queryPath);