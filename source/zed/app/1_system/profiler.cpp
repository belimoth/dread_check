#include <stdio.h>

#include <zed/app.h>
#include <zed/platform/windows.h>

#include <psapi.h>

void app_system_profiler_init() {

}

void app_system_profiler_report() {
	PERFORMANCE_INFORMATION info;

	printf( "\n" );
	printf( "system\n" );
	printf( "\n" );

	GetPerformanceInfo( &info, 0 );

	printf(
		"CommitTotal:                %16llu\n"
		"CommitLimit:                %16llu\n"
		"CommitPeak:                 %16llu\n"
		"PhysicalTotal:              %16llu\n"
		"PhysicalAvailable:          %16llu\n"
		"SystemCache:                %16llu\n"
		"KernelTotal:                %16llu\n"
		"KernelPaged:                %16llu\n"
		"KernelNonpaged:             %16llu\n"
		"PageSize:                   %16llu\n"
		"HandleCount:                %16lu\n"
		"ProcessCount:               %16lu\n"
		"ThreadCount:                %16lu\n",
		info.CommitTotal,
		info.CommitLimit,
		info.CommitPeak,
		info.PhysicalTotal,
		info.PhysicalAvailable,
		info.SystemCache,
		info.KernelTotal,
		info.KernelPaged,
		info.KernelNonpaged,
		info.PageSize,
		info.HandleCount,
		info.ProcessCount,
		info.ThreadCount
	);

	//

	printf( "\n" );

	MEMORYSTATUSEX status;

	GlobalMemoryStatusEx( &status );

	printf(
		"dwLength:                   %16lu\n"
		"dwMemoryLoad:               %16lu\n"
		"ullTotalPhys:               %16llu\n"
		"ullAvailPhys:               %16llu\n"
		"ullTotalPageFile:           %16llu\n"
		"ullAvailPageFile:           %16llu\n"
		"ullTotalVirtual:            %16llu\n"
		"ullAvailVirtual:            %16llu\n"
		"ullAvailExtendedVirtual:    %16llu\n",
		status.dwLength,
		status.dwMemoryLoad,
		status.ullTotalPhys,
		status.ullAvailPhys,
		status.ullTotalPageFile,
		status.ullAvailPageFile,
		status.ullTotalVirtual,
		status.ullAvailVirtual,
		status.ullAvailExtendedVirtual
	);

	// process

	HANDLE process = GetCurrentProcess();

	//

	printf( "\n" );
	printf( "process\n" );
	printf( "\n" );

	//

	PROCESS_MEMORY_COUNTERS pmc = {};

	GetProcessMemoryInfo( process, &pmc, sizeof(pmc) );

	printf(
		"PageFaultCount:             %16lu\n"
		"PeakWorkingSetSize:         %16llu\n"
		"WorkingSetSize:             %16llu\n"
		"QuotaPeakPagedPoolUsage:    %16llu\n"
		"QuotaPagedPoolUsage:        %16llu\n"
		"QuotaPeakNonPagedPoolUsage: %16llu\n"
		"QuotaNonPagedPoolUsage:     %16llu\n"
		"PagefileUsage:              %16llu\n"
		"PeakPagefileUsage:          %16llu\n",
		pmc.PageFaultCount,
		pmc.PeakWorkingSetSize,
		pmc.WorkingSetSize,
		pmc.QuotaPeakPagedPoolUsage,
		pmc.QuotaPagedPoolUsage,
		pmc.QuotaPeakNonPagedPoolUsage,
		pmc.QuotaNonPagedPoolUsage,
		pmc.PagefileUsage,
		pmc.PeakPagefileUsage
	);

	//

	printf( "\n" );
	printf( "modules\n" );
	printf( "\n" );

	//

	HMODULE modules[1024];
	DWORD   size_needed;

	EnumProcessModules( process, modules, sizeof(modules), &size_needed );

	for ( uint i = 0; i < ( size_needed / sizeof(HMODULE) ); i++ ) {
		char module_name[MAX_PATH];
		GetModuleFileNameEx( process, modules[i], module_name, sizeof(module_name) / sizeof(char) );
		printf( "0x%08X %s\n", *(uint *)&modules[i], module_name );
	}
}

void app_system_profiler_exit() {

}
