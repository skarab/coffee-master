#ifdef COFFEE_OS_WINDOWS

    public:

        //-ACCESSORS------------------------------------------------------------------------------//

        HINSTANCE GetDllInstance();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void ConvertDate(basic::Date& date, const SYSTEMTIME& system_date) const;

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _LogPlatform();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        HINSTANCE _DllInstance;
        real64 _PerformanceTimePerSecond;
        LARGE_INTEGER _TimeStart;
        real _TickCountStart;
        bool _ItHasPerformanceTimerEnabled;
        PROCESS_INFORMATION _PipeProcess;
        HANDLE _PipeRead;
        HANDLE _PipeWrite;

#endif
