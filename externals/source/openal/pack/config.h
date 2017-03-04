/* API declaration export attribute */
#define AL_API   
#define ALC_API  

/* Define to the library version */
#define ALSOFT_VERSION "1.15.1"

#define AL_ALEXT_PROTOTYPES

/* Define any available alignment declaration */
#ifdef ANDROID
    #define ALIGN(x)
//    __declspec(aligned(x))
#else
    #define ALIGN(x) __declspec(align(x))
    #ifdef __MINGW32__
    #define align(x) aligned(x)
    #endif
#endif

/* Define to the appropriate 'restrict' keyword */
#define RESTRICT __restrict

/* Define if we have the C11 aligned_alloc function */
//#define HAVE_ALIGNED_ALLOC

/* Define if we have the posix_memalign function */
//#define HAVE_POSIX_MEMALIGN

/* Define if we have the _aligned_malloc function */
#define HAVE__ALIGNED_MALLOC

/* Define if we have SSE CPU extensions */
#ifdef COFFEE_COMPILER_MSVC
    #define HAVE_SSE
#endif

/* Define if we have ARM Neon CPU extensions */
//#define HAVE_NEON

/* Define if we have the ALSA backend */
//#define HAVE_ALSA

/* Define if we have the OSS backend */
//#define HAVE_OSS

/* Define if we have the Solaris backend */
//#define HAVE_SOLARIS

/* Define if we have the SndIO backend */
//#define HAVE_SNDIO

/* Define if we have the MMDevApi backend */
//#define HAVE_MMDEVAPI

/* Define if we have the DSound backend */
// #define HAVE_DSOUND

/* Define if we have the Windows Multimedia backend */
#ifndef ANDROID
    #define HAVE_WINMM
#endif

/* Define if we have the PortAudio backend */
//#define HAVE_PORTAUDIO

/* Define if we have the PulseAudio backend */
//#define HAVE_PULSEAUDIO

/* Define if we have the CoreAudio backend */
//#define HAVE_COREAUDIO

/* Define if we have the OpenSL backend */
//#define HAVE_OPENSL

/* Define if we have the Wave Writer backend */
#define HAVE_WAVE

/* Define if we have the stat function */
#define HAVE_STAT

/* Define if we have the lrintf function */
//#define HAVE_LRINTF

/* Define if we have the strtof function */
//#define HAVE_STRTOF

/* Define if we have the __int64 type */
#ifndef ANDROID
    #define HAVE___INT64
#endif

/* Define to the size of a long int type */
#define SIZEOF_LONG sizeof(long int)

/* Define to the size of a long long int type */
#define SIZEOF_LONG_LONG sizeof(long long int)

/* Define if we have GCC's destructor attribute */
#if defined(COFFEE_COMPILER_MINGW) || defined(ANDROID)
    #define HAVE_GCC_DESTRUCTOR
#endif

/* Define if we have GCC's format attribute */
//#define HAVE_GCC_FORMAT

/* Define if we have stdint.h */
#ifdef ANDROID
    #define HAVE_STDINT_H
#endif

/* Define if we have windows.h */
#ifndef ANDROID
    #define HAVE_WINDOWS_H
#endif

/* Define if we have dlfcn.h */
#ifdef ANDROID
    #define HAVE_DLFCN_H
#endif

/* Define if we have pthread_np.h */
#ifndef ANDROID
    #define HAVE_PTHREAD_NP_H
#endif

/* Define if we have xmmintrin.h */
#ifdef COFFEE_COMPILER_MSVC
    #define HAVE_XMMINTRIN_H
#endif

/* Define if we have arm_neon.h */
//#define HAVE_ARM_NEON_H

/* Define if we have malloc.h */
#define HAVE_MALLOC_H

/* Define if we have cpuid.h */
//#define HAVE_CPUID_H

/* Define if we have guiddef.h */
//#define HAVE_GUIDDEF_H

/* Define if we have initguid.h */
//#define HAVE_INITGUID_H

/* Define if we have ieeefp.h */
//#define HAVE_IEEEFP_H

/* Define if we have float.h */
#define HAVE_FLOAT_H

/* Define if we have fenv.h */
//#define HAVE_FENV_H

/* Define if we have fesetround() */
#define HAVE_FESETROUND

/* Define if we have _controlfp() */
#ifndef ANDROID
    #define HAVE__CONTROLFP
#endif

/* Define if we have __control87_2() */
#ifndef ANDROID
    #define HAVE___CONTROL87_2
#endif

/* Define if we have pthread_setschedparam() */
#define HAVE_PTHREAD_SETSCHEDPARAM
