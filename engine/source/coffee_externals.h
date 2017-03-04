#ifndef _COFFEE_EXTERNALS_H_
#define _COFFEE_EXTERNALS_H_

// OpenGL

#include "glee.h"
#include "gl.h"
#include "glu.h"
#include "glext.h"

#ifdef COFFEE_OS_WINDOWS
    #include "wglext.h"
#endif

// Compression

#include "zlib.h"
#include "lz4.h"
#include "lz4hc.h"

// Physics

#include "Newton.h"
#include "JointLibrary.h"
#include "CustomPlayerController.h"

// Audio

#define ALC_API extern
#include "al.h"
#include "alc.h"    
#include "ogg/ogg.h"
#include "vorbis/vorbisfile.h"
#include "vorbis/vorbisenc.h"    

#endif
