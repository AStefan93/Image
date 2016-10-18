typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;

typedef signed char sint8;
typedef signed short int sint16;
typedef signed int sint32;

// JPEG Markers
enum AppMarkerTypes
{
    SOI    = 0xFFD8, SOF0   = 0xFFC0, SOF1   = 0xFFC1, SOF2   = 0xFFC2, 
	SOF3   = 0xFFC3, SOF5   = 0xFFC5, SOF6   = 0xFFC6, SOF7   = 0xFFC7,
	SOF9   = 0xFFC9, SOF10  = 0xFFCA, SOF11  = 0xFFCB, SOF13  = 0xFFCD,
	SOF14  = 0xFFCF, SOF15  = 0xFFCE, 
    DHT    = 0xFFC4, DQT    = 0xFFDB, DRI    = 0xFFDD, SOS    = 0xFFDA,

    RST0  = 0xFFD0, RST1  = 0xFFD1, RST2  = 0xFFD2, RST3  = 0xFFD3,
    RST4  = 0xFFD4, RST5  = 0xFFD5, RST6  = 0xFFD6, RST7  = 0xFFD7,

    APP0  = 0xFFE0, APP1  = 0xFFE1, APP2  = 0xFFE2, APP3  = 0xFFE3,
    APP4  = 0xFFE4, APP5  = 0xFFE5, APP6  = 0xFFE6, APP7  = 0xFFE7,
    APP8  = 0xFFE8, APP9  = 0xFFE9, APP10 = 0xFFEA, APP11 = 0xFFEB,
    APP12 = 0xFFEC, APP13 = 0xFFED, APP14 = 0xFFEE, APP15 = 0xFFEF,

    COM   = 0xFFFE, EOI   = 0xFFD9
};

typedef struct t_APP0_tag{
	
	uint64_t APP0_Length:16; // size is 2 bytes - Length of segment excluding APP0 marker
	uint64_t APP0_Identifier:40; //size is 5 bytes - 4A 46 58 58 00 = "JFXX" in ASCII, terminated by a null byte
	uint64_t APP0_DensityUnits:8; /*size is 1 byte 
									Units for the following pixel density fields 
									00 : No units; width:height pixel aspect ratio = Xdensity:Ydensity
									01 : Pixels per inch (2.54 cm)
									02 : Pixels per centimeter */
	uint64_t APP0_JFIF_Version:16; //size is 2 bytes - 01 02 is version 1.02
	uint64_t APP0_Xdensity:16; //size is 2 bytes Horizontal pixel density. Must not be zero.
	uint64_t APP0_Ydensity:16; //size is 2 bytes Vertical pixel density. Must not be zero.
	uint64_t APP0_Xthumbnail:8; //size is 1 bytes Horizontal pixel count of the following embedded RGB thumbnail. May be zero.
	uint64_t APP0_Ythumbnail:8; //size is 1 bytes Vertical pixel count of the following embedded RGB thumbnail. May be zero.

}t_APP0;

typedef struct t_JPEG_tag{
	// JPEG image starts with SOI and ends with EOI
	t_APP0 struct_APP0; //size is 16 bytes
}t_JPEG;
