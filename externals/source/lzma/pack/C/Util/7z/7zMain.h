#ifndef _7ZMAIN_H_
#define _7ZMAIN_H_

#include <stdio.h>
#include <string.h>

#include "../../7z.h"
#include "../../7zAlloc.h"
#include "../../7zCrc.h"
#include "../../7zFile.h"
#include "../../7zVersion.h"

EXTERN_C_BEGIN

extern void(*LZMA_Progress)(float);
extern void(*LZMA_ListFile)(const char*, int);
extern int(*LZMA_FilterFile)(const char*, int);

int run7z(int numargs, const char **args);

EXTERN_C_END

#endif
