#pragma once

#include <zed.h>
#include <zed/platform/windows.h>

struct zed_heap_info_entry {
	string name;
};

struct zed_heap_info {
	string text[ 256  * 32 ];
	zed_heap_info_entry entries[ 256 ];
	uint entries_count;
} scratch_info;

enum { heap_page_size = 0x01000 }; //  4 kB =  4096 B
enum { heap_book_size = 0x10000 }; // 64 kB = 65536 B

struct zed_heap_entry {

};

struct zed_heap {
	handle memory;
	uint size;
	uint i;
} heap;

void heap_check() {
	SYSTEM_INFO info;

	GetSystemInfo( &info );

	uint page_size = info.dwPageSize;
	uint book_size = info.dwAllocationGranularity;

	// zed_debug_say( "Heap   - Page Size = %u, Book Size = %u\n", page_size, book_size )

	assert( page_size == heap_page_size );
	assert( book_size == heap_book_size );
}

void heap_init( uint book_count = 1 ) {
	heap_check();

	size_t size = heap_book_size * book_count;

	heap = {};
	heap.memory = (handle)VirtualAlloc( 0, size, MEM_RESERVE, PAGE_READWRITE );
}

void heap_allocate( handle entry, uint data_size ) {
	uint size = 0;

	while ( data_size >= size ) size += heap_page_size;

	if ( heap.i + size >= heap.size ) zed_die();

	// todo allocate at the end of the page so that overwrites cause a page fault
	// todo increment page_i again so that there are uncommitted pages between each alloc
}

void heap_exit() {
	VirtualFree( heap.memory, 0, MEM_RELEASE );
}
