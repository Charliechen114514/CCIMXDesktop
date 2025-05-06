#include "Win32PlatformDrivers.h"
#include <TlHelp32.h>
#include <accctrl.h>
#include <aclapi.h>
#include <psapi.h>
#include <sddl.h>
#include <securitybaseapi.h>
#include <tchar.h>
#include <userenv.h>
namespace {

void from_windows_platform(MemoryInfoFetcher::MemoryStat& stat) {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);

	/* Thus make the adaptions here */
	stat.total_phys_memory = static_cast<quint64>(memInfo.ullTotalPhys);
	stat.total_virt_memory = static_cast<quint64>(memInfo.ullTotalVirtual);
	stat.avail_virt_memory = static_cast<quint64>(memInfo.ullAvailVirtual);
	stat.avail_phys_memory = static_cast<quint64>(memInfo.ullAvailPhys);
}

quint64 fileTimeToInt64(const FILETIME& ft) {
	ULARGE_INTEGER li;
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	return li.QuadPart;
}

void from_windows_cpu(CPUStateFetcher::CPUState& stat) {
	FILETIME idleTime, kernelTime, userTime;
	if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
		stat.idle = stat.kernel = stat.user = 0;
		return;
	}
	/* To seconds */
	stat.idle = fileTimeToInt64(idleTime) / 10000000.0;
	stat.kernel = fileTimeToInt64(kernelTime) / 10000000.0;
	stat.user = fileTimeToInt64(userTime) / 10000000.0;
	stat.tol = stat.kernel + stat.user;
}

QString getProcessUserName(HANDLE processHandle) {
	HANDLE token = nullptr;
	if (!OpenProcessToken(processHandle, TOKEN_QUERY, &token))
		return QString();

	DWORD size = 0;
	GetTokenInformation(token, TokenUser, nullptr, 0, &size);
	if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
		CloseHandle(token);
		return QString();
	}

	BYTE* buffer = new BYTE[size];
	if (!GetTokenInformation(token, TokenUser, buffer, size, &size)) {
		delete[] buffer;
		CloseHandle(token);
		return QString();
	}

	SID_NAME_USE sidType;
	TCHAR name[256], domain[256];
	DWORD nameLen = 256, domainLen = 256;

	if (LookupAccountSid(nullptr,
						 ((TOKEN_USER*)buffer)->User.Sid,
						 name, &nameLen,
						 domain, &domainLen, &sidType)) {
		QString user = QString::fromWCharArray(domain) + "\\" + QString::fromWCharArray(name);
		delete[] buffer;
		CloseHandle(token);
		return user;
	}

	delete[] buffer;
	CloseHandle(token);
	return QString();
}

qint64 getProcessMemoryUsageKB(HANDLE processHandle) {
	PROCESS_MEMORY_COUNTERS pmc;
	if (GetProcessMemoryInfo(processHandle, &pmc, sizeof(pmc))) {
		return static_cast<qint64>(pmc.WorkingSetSize) / 1024;
	}
	return -1;
}

void filled_windows_process_info(QList<ProcessBroswer::ProcessInfo>& lists) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
		return;
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hSnapshot, &pe)) {
		do {
			ProcessBroswer::ProcessInfo info;
			info.pid = pe.th32ProcessID;
			info.ppid = pe.th32ParentProcessID;
			info.name = QString::fromWCharArray(pe.szExeFile);
			info.threadCount = pe.cntThreads;

			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe.th32ProcessID);
			if (hProcess) {
				wchar_t path[MAX_PATH] = { 0 };
				if (GetModuleFileNameExW(hProcess, nullptr, path, MAX_PATH))
					info.fullPath = QString::fromWCharArray(path);

				info.memoryUsageKB = getProcessMemoryUsageKB(hProcess);
				info.userName = getProcessUserName(hProcess);

				CloseHandle(hProcess);
			}

			lists.append(info);
		} while (Process32Next(hSnapshot, &pe));
	}

	CloseHandle(hSnapshot);
}

}

void Win32PlatformMemoryInfoDriver::factory(MemoryInfoFetcher::MemoryStat& stat) {
	from_windows_platform(stat);
}

void Win32PlatformCPUStateDriver::factory(CPUStateFetcher::CPUState& stat) {
	from_windows_cpu(stat);
}

void Win32PlatformProcessBroswerDriver::
	factory(QList<ProcessBroswer::ProcessInfo>& lists) {
	/* set the list as clears */
	lists.clear();
	filled_windows_process_info(lists);
}
