#include "info.h"

#pragma comment(lib, "wbemuuid.lib")

int main(){
	in_label << "Host Name: ";
	CHAR host_name[INFO_BUFFER_SIZE];
	memset(host_name, 0, sizeof(host_name));
	DWORD buffer = INFO_BUFFER_SIZE;
	GetComputerNameA(host_name, &buffer);
	in_data << host_name << std::endl;

	displayDataFromRegistry("OS Name: ", "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductName");
	displayDataFromRegistry("OS Version: ", "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "BuildLab");
	displayDataFromRegistry("OS Manufacturer: ", "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\OEM", "Manufacturer");
	displayDataFromRegistry("OS Build Type: ", "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "CurrentType");

	std::cout << "Registered Organization: " << "\n"; 

	displayDataFromRegistry("Registered Owner: ", "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "RegisteredOwner");
	displayDataFromRegistry("Product ID: ", "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductId");
	displayData_TIME_FromRegistry("Original Install Date: ", "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "InstallDate");

	displayDataFromRegistry("System Manufacturer: ", "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardManufacturer");
	displayDataFromRegistry("System Model: ", "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemProductName");


	in_label << "Processor(s): ";
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	in_data << sysinfo.dwNumberOfProcessors << "\n";
	//free(sysinfo);


	displayDataFromRegistry("BIOS Version", "HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVersion");
	displayDataFromRegistry("Windows Directory", "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion" , "SystemRoot");
	displayDataFromRegistry("System Director", "SOFTWARE\\Microsoft\\AppV\\Client", "InstallPath");


	//Boot device:
	in_label << "Boot Device: ";
	WCHAR  VolumeName[MAX_PATH] = L"";
	//HANDLE FindHandle           = INVALID_HANDLE_VALUE;
	FindFirstVolumeW(VolumeName, ARRAYSIZE(VolumeName));
	std::wcout << std::right << std::setw(35) << VolumeName << std::endl;

	//System Locale
	setlocale(LC_ALL, ""); 
	in_label << "SYstem Locale: ";
	in_data << setlocale(LC_ALL, NULL) << std::endl;

	in_label << "Input Locale: ";
	in_data << setlocale(LC_ALL, NULL) << std::endl;

	//RAM
	MEMORYSTATUSEX memStatus;
	memStatus.dwLength = sizeof(memStatus);
	GlobalMemoryStatusEx (&memStatus);


	in_label << "Total Physical Memory: "; 
	in_data << memStatus.ullTotalPhys  << std::endl;
	
	in_label << "Available Physical Memory: ";
	in_data << memStatus.ullAvailPhys  << std::endl;

	in_label << "Virtual Memory: Max Size: ";
	in_data << memStatus.ullTotalPageFile << std::endl;

	in_label << "Virtual Memory: Available: ";
	in_data << memStatus.ullAvailPageFile << std::endl;

	in_label << "Virtual Memory: In Use: ";
	in_data << memStatus.ullTotalPageFile - memStatus.ullAvailPageFile << std::endl;

	//free(memStatus);

	displayDataFromRegistry("Page File Location(s)", "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management", "PagingFiles");
	displayDataFromRegistry("Logon Server: ", "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductName");

	//Adapter:
	in_label << "Network Card(s): ";

 	PIP_ADAPTER_ADDRESSES  pAdapterInfo;
 	PIP_ADAPTER_ADDRESSES  pAdapter = NULL;
 	DWORD dwRetVal = 0;

 	ULONG ulOutBufLen = sizeof(PIP_ADAPTER_ADDRESSES);

 	pAdapterInfo = (IP_ADAPTER_ADDRESSES *) malloc(ulOutBufLen);

 	dwRetVal = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, NULL, pAdapterInfo, &ulOutBufLen);

 	if(dwRetVal == ERROR_BUFFER_OVERFLOW){
 		free(pAdapterInfo);
 		pAdapterInfo = (IP_ADAPTER_ADDRESSES *) malloc(ulOutBufLen);
 		if(pAdapterInfo == NULL){
 			std::cout << "Error";
 		}
 		if(dwRetVal = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, NULL, pAdapterInfo, &ulOutBufLen) == NO_ERROR){
 			int count = 0;
 			PIP_ADAPTER_ADDRESSES backup = NULL;

 			backup = pAdapterInfo;

 			while(backup){
 				count += 1;
 				backup = backup->Next;
 			}

 			pAdapter = pAdapterInfo;
 			std::cout << std::right << std::setw(30 - 8) << count;
 			std::cout << " NIC(s) Installed." << std::endl;
 			
 			while(pAdapter){
 				std::wcout << std::right << std::setw(70) << pAdapter->FriendlyName << std::endl;
 				std::wcout << std::right << std::setw(70) << pAdapter->Description << std::endl;
 				std::cout << std::right << std::setw(70) << pAdapter->AdapterName << std::endl;
 				//std::cout << std::right << std::setw(70) << pAdapter->Dhcpv4Server  << std::endl;

 				std::cout << "\n";

 				pAdapter = pAdapter->Next;

 			}
 		}
 	}
	return 0;
}