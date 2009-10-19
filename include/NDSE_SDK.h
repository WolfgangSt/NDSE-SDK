#ifndef _NDSE_H_
#define _NDSE_H_

#ifdef WIN32
#define STDCALL __stdcall 
#else
#define STDCALL
#endif

#ifndef EXPORT
	#ifdef WIN32
	#define IMPORT __declspec(dllimport)
	#else
	#define IMPORT
	#endif
#else
	#define IMPORT EXPORT
#endif

#pragma warning(push)
#pragma warning(disable: 4200)

struct load_result
{
    unsigned long arm9_entry;
    unsigned long arm7_entry;
};

struct memory_block;

struct memory_region_base
{
	const char *name;
	unsigned int pages;
	unsigned long color;
	unsigned int priority;
	memory_block *start, *end;

	virtual void virt() = 0;
};

struct compiled_block
{
	char *code;            // compiled code
	size_t code_size;      // size of compiled code
	memory_block *block;
	char *remap[];         // remapping from ARM address to compiled code
};

struct compile_info
{
        compiled_block *arm;
        compiled_block *thumb;
};

struct memory_region_base;
struct memory_block /* final, do not inherit! */
{
        enum {
                PAGE_READPROT      = 0x01,
                PAGE_WRITEPROT     = 0x02,
                PAGE_EXECPROT      = 0x04,
                PAGE_INVALID       = 0x08,
                PAGE_NULL          = PAGE_INVALID | PAGE_EXECPROT | PAGE_WRITEPROT | PAGE_READPROT,
                PAGE_DIRTY_J7      = 0x10,
                PAGE_DIRTY_J9      = 0x20,
                PAGE_DIRTY_REACTOR = 0x40,
                PAGE_DIRTY_VRAM    = 0x80,
				PAGE_DIRTY_SRAM    = 0x100,
                PAGE_DIRTY         = PAGE_DIRTY_J7 | PAGE_DIRTY_J9 | PAGE_DIRTY_REACTOR | PAGE_DIRTY_VRAM |
				                     PAGE_DIRTY_SRAM
        };

        unsigned long flags;

        compile_info arm7;
        compile_info arm9;
		memory_region_base *base;
        unsigned long recompiles;

        char mem[];
};

typedef void (STDCALL *log_callback)(char* log);
typedef void (STDCALL *io_callback)(unsigned long addr, unsigned long *value);

extern "C"{

IMPORT void STDCALL Init();

IMPORT memory_block* STDCALL ARM9_GetPage(unsigned long addr);
IMPORT bool STDCALL ARM9_Run(unsigned long addr);
IMPORT void STDCALL ARM9_Log(log_callback cb);
IMPORT void STDCALL ARM9_Interrupt(unsigned long intr);
IMPORT void STDCALL ARM9_AddIOCallback(io_callback r, io_callback w);

IMPORT memory_block* STDCALL ARM7_GetPage(unsigned long addr);
IMPORT void STDCALL ARM7_Interrupt(unsigned long intr);
IMPORT void STDCALL ARM7_AddIOCallback(io_callback r, io_callback w);

IMPORT void STDCALL DEFAULT_Log(log_callback cb);
IMPORT bool STDCALL UTIL_LoadFile(const char *filename, load_result *result);
IMPORT memory_region_base* STDCALL MEM_GetVRAM(int bank);
IMPORT unsigned long STDCALL PageSize();
IMPORT unsigned long STDCALL DebugMax();
IMPORT const memory_region_base* STDCALL MEM_GetRegionInfo(memory_block *p);

IMPORT void STDCALL TouchSet(int x, int y);
}

const unsigned long PAGE_BITS = PageSize();
const unsigned long PAGE_SIZE = 1 << PAGE_BITS;
const unsigned long PAGE_MASK = PAGE_SIZE - 1;

#pragma warning(pop)

#endif
