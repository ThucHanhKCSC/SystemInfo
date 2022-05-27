#include "info.h"

void displayDataFromRegistry(const char *label, const char *path, const char *queryPath){
	char data[INFO_BUFFER_SIZE];
	memset(data, 0, sizeof(data));
	HKEY hkey;
	DWORD buffer = INFO_BUFFER_SIZE;
	in_label << label;
	RegOpenKeyA(HKEY_LOCAL_MACHINE, path, &hkey);
	RegQueryValueExA(hkey, queryPath, NULL, NULL, (LPBYTE)data, &buffer);
	in_data << data << std::endl;
	RegCloseKey(hkey);

}


void displayData_TIME_FromRegistry(const char *label, const char *path, const char *queryPath){
	char data[INFO_BUFFER_SIZE];
	memset(data, 0, sizeof(data));
	HKEY hkey;
	DWORD dwType = REG_DWORD;
	DWORD buffer = INFO_BUFFER_SIZE;
	in_label << label;
	RegOpenKeyA(HKEY_LOCAL_MACHINE, path, &hkey);
	RegQueryValueExA(hkey, queryPath, NULL, NULL, (LPBYTE)data, &buffer);
	
	int val[strlen(data)];
	std::string hexVal;
	std::stringstream ss;

	for (int i = strlen(data) - 1; i>=0; i--){
		val[i] = (int)data[i];
		val[i] &= 0xff;

		ss << std::hex << val[i];

	}
	hexVal = ss.str();
	
	std::stringstream ss2;

	ss2 << std::hex << hexVal;

	long long a = 0;

	ss2 >> a;

	time_t epch = a;

	in_data << asctime(gmtime(&epch));

	RegCloseKey(hkey);
}