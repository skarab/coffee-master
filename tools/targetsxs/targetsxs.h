//------------------------------------------------------------------------------------------------//
// Side by Side assembly enforcement
//------------------------------------------------------------------------------------------------//
// Here is the list of the various CRT version for Visual Studio 2005, 2008, 2010 :
//
// Visual Studio 2005                            8.0.50727.42         10/04/2006
// Visual Studio 2005 SP1                        8.0.50727.762        27/08/2007
// Visual Studio 2005 SP1 ATL/MS09-035           8.0.50727.4053       20/09/2010
// Visual Studio 2005 SP1 MFC/MS11-025           8.0.50727.6195       07/06/2011
// Visual Studio 2008                            9.0.21022.8          29/11/2007
// Visual Studio 2008 SP1                        9.0.30729.1          16/09/2008
// Visual Studio 2008 SP1 ATL/MS09-035           9.0.30729.4148       29/09/2010
// Visual Studio 2008 SP1 MFC/MS11-025           9.0.30729.6161       14/06/2011
// Visual Studio 2010                            10.0.30319.1         14/12/2010
// Visual Studio 2010 SP1                        10.0.40219.1         03/03/2011
// Visual Studio 2012 Update 3                   11.0.60610

// We force the SP1 for each compiler, since it's the painless.

#if defined(COFFEE_COMPILER_MSVC)
    #if defined(COFFEE_COMPILER_MSVC2005)
        #define _SXS_ASSEMBLY_VERSION "8.0.50727.762"
    #elif defined(COFFEE_COMPILER_MSVC2008)
        #define _SXS_ASSEMBLY_VERSION "9.0.30729.1"
    #elif defined(COFFEE_COMPILER_MSVC2010)
        #define _SXS_ASSEMBLY_VERSION "10.0.40219.1"
    #elif defined(COFFEE_COMPILER_MSVC2012)
        #define _SXS_ASSEMBLY_VERSION "11.0.60610"
    #endif
        
    #define _CRT_ASSEMBLY_VERSION _SXS_ASSEMBLY_VERSION
    #define _MFC_ASSEMBLY_VERSION _SXS_ASSEMBLY_VERSION
    #define _ATL_ASSEMBLY_VERSION _SXS_ASSEMBLY_VERSION

    #ifdef __cplusplus
    extern "C" {
    #endif
    __declspec(selectany) int _forceCRTManifest;
    __declspec(selectany) int _forceMFCManifest;
    __declspec(selectany) int _forceAtlDllManifest;
    __declspec(selectany) int _forceCRTManifestRTM;
    __declspec(selectany) int _forceMFCManifestRTM;
    __declspec(selectany) int _forceAtlDllManifestRTM;
    #ifdef __cplusplus
    }
    #endif
#endif
