#ifdef COFFEE_OS_WINDOWS

    public:

        //-ACCESSORS------------------------------------------------------------------------------//

        HWND GetPlatformWindow() const { return _Window; }

        //-QUERIES--------------------------------------------------------------------------------//

        void ListDevices(basic::Array<DISPLAY_DEVICE>& device_array) const;
        void ListModes(basic::Array<DEVMODE>& mode_array, uint32 device_index) const;
        bool GetDisplayMode(DEVMODE& display_mode, uint32 device_index, uint32 device_mode_index) const;
        void GetDesktopResolution(uint32& width, uint32& height, uint32& bpp, CONFIG_ASPECT_RATIO& aspect_ratio);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _CreatePlatformWindow();
        void _DestroyPlatformWindow();
        void _CreateWindowClass();
        ulong _CreateWindowStyle();
        void _CreateWindowDialog(ulong style);
        void _CreateWindowPixelFormat();
        void _UpdateSize(uint32 width, uint32 height);
        void _OnDropFiles(HDROP hdrop);
        
        //-FUNCTIONS------------------------------------------------------------------------------//

        static LRESULT CALLBACK _WindowFunction(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        HWND _Window;
        HDC _DesktopContext;
        HGLRC _OpenglContext;
        RECT _WindowRec;
        int32 _PixelFormat;
        bool _ItIsUpToDate;
        HDC _OldDC;
        HGLRC _OldContext;

#endif
