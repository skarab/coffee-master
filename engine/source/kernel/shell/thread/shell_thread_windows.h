#ifdef COFFEE_OS_WINDOWS

    public:

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasToStop() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        HANDLE _ThreadHandle;
        uint32 _ThreadID;
        bool _ItHasToStop;

        //-VARIABLES------------------------------------------------------------------------------//

        static HANDLE _MainThreadHandle;
        static uint32 _MainThreadID;

#endif
