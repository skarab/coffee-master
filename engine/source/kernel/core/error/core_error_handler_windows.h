#ifdef COFFEE_OS_WINDOWS

    //-TYPES----------------------------------------------------------------------------------//

    typedef struct _MINIDUMP_ERROR_INFORMATION
    {
	    DWORD ThreadId;
	    PEXCEPTION_POINTERS	ErrorPointers;
	    BOOL ClientPointers;
    } MINIDUMP_ERROR_INFORMATION, *PMINIDUMP_ERROR_INFORMATION;

    typedef enum _MINIDUMP_TYPE {
	    MiniDumpNormal =        0x00000000,
	    MiniDumpWithDataSegs =  0x00000001,
    } MINIDUMP_TYPE;

    typedef	BOOL (WINAPI * MINIDUMP_WRITE_DUMP)(
	    IN HANDLE hProcess,
	    IN DWORD ProcessId,
	    IN HANDLE hFile,
	    IN MINIDUMP_TYPE DumpType,
	    IN CONST PMINIDUMP_ERROR_INFORMATION ErrorParam, OPTIONAL
	    IN PVOID UserStreamParam, OPTIONAL
	    IN PVOID CallbackParam OPTIONAL);

    //-OPERATIONS-----------------------------------------------------------------------------//

    void _GenerateMiniDump();
    
    //-ATTRIBUTES-----------------------------------------------------------------------------//

    HMODULE	_DebugLibrary;
    MINIDUMP_WRITE_DUMP	_MiniDumpWriteDump;

#endif
