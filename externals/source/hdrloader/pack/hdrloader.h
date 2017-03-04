
/***********************************************************************************
	Created:	17:9:2002
	FileName: 	hdrloader.h
	Author:		Igor Kravtchenko & Alexandre Chambriat
	
	Info:		Load HDR image in RGBE8 format
************************************************************************************/

class HDRLoaderResult {
public:
	int width, height;
	// per pixel R,G,B,E
	unsigned char *cols;
};

class HDRLoader {
public:
	static bool load(const char *fileName, HDRLoaderResult &res);
};

