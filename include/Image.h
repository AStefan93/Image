//include guard
#ifndef IMAGE_HEADER
#define IMAGE_HEADER
//Standard libs
#include <iostream> //basic io
#include <string> //strings
#include <fstream> //basic file io
//#include <conio.h> //getch()
#include <random> //for generating population - genetic algorithm
#include <algorithm>    // std::sort

//internal type header
#include "Image_types.h"
//math functions
#include "Image_math.h"

//added for time calculation
#include <ctime>
#include <cstdio>

#define cimg_use_png //it won't work with png files otherwise
#include "CImg.h" //external CImg header

//DEFINES
#define is_bigendian() ( (*(char*)&c_uint16_endian_test) == 0 ) // returns 1 if platform is little_endian

namespace ImageProc {

	class Image {
	public:
		Image(); //default contructor - 240*320 matrix with zeroes
		Image(unsigned int ,unsigned int); //creates H*W matrix with zeroes
		Image(char const* ,uint8 ); //reads header and data from path file image - personal JPEG decoder
		Image(char const* ); //reads header and data from path file image
		~Image(); //deletes image
		unsigned int getHeight() const;//Height function
		unsigned int setHeight(int ); //set Height param
		unsigned int getWidth() const;// Width function
		unsigned int setWidth(int ); //set Width param
		unsigned int getgrayLevel() const; //the number of gray levels
		unsigned int setgrayLevel(int); //sets the gray level
		std::string getType() const; //gets the type
		unsigned int** imageData; //the stored gray image pixels
		unsigned int** Red;
		unsigned int** Green;
		unsigned int** Blue;
		double* Hist; //vector for the histogram
		double* normHist; //vector for the normalized histogram
		uint8 bitDepth; //the bit depth of the image - by default it's 8

//		int readPGM(char* ); //reads file into image
//		int writePGM(char* ); //writes image to file

		//Assignment operator
    		void operator=(const Image& );

	private:
		unsigned int Width; //width and height in pixels
		unsigned int Height; // the height
		unsigned int grayLevel; //number of gray levels can be any integer positive number
		std::string imgType; //type of the image extracted from the header

//		void readPGMHeader(FILE* ); //read header of PGM file
//		void writePGMHeader(FILE* ); //writes a PGM header to file

		static uint32_t Image_count; //counts objects for destructor

		t_JPEG struct_JPEG;
		void f_readAPP0(FILE* );
		void f_readSOF0(FILE* );
		void f_readDQT(FILE* );
		void f_readDHT(FILE* );

	};
	
	class Square {
		public:
			Square();
			Square(t_2DPoint* , t_2DPoint* );
			~Square();
			t_2DPoint getUpperLeftCorner();
			void setUpperLeftCorner(t_2DPoint* ); 
			t_2DPoint getLowerRightCorner();
			void setLowerRightCorner(t_2DPoint* );
		private:
			t_2DPoint upperLeftCorner;
			t_2DPoint lowerRightCorner;
	};

}

namespace MachineLearning{

		struct twogauss{
		double sigma1;
		double A1;
		int miu1;

		double sigma2;
		double A2;
		int miu2;

		double delta;
	};

		bool indCompare(twogauss lhs, twogauss rhs);


}
//end include guard
#endif
