//Standard libs
#include <iostream> //basic io
#include <string> //strings
#include <fstream> //basic file io
#include <conio.h> //getch()
#include <math.h> //sine, cosine
#include <random> //for generating population - genetic algorithm
#include <algorithm>    // std::sort
#include <stdint.h> //used for types(uint8_t, uint16_t etc)

//external libs
#include "CImg.h"

//internal libs
#include "Image_types.h"

//added for time 
#include <ctime>
#include <cstdio>

//DEFINES
#define is_bigendian() ( (*(char*)&c_uint16_endian_test) == 0 ) // returns 1 if paltform is little_endian

namespace ImageProc {

	class Image {
	public:
		Image(); //default contructor - 240*320 matrix with zeroes
		Image(unsigned int ,unsigned int); //creates H*W matrix with zeroes
		Image(char* ); //reads header and data from path file image
		~Image(); //deletes image
		unsigned int getHeight();//Height function
		unsigned int setHeight(int ); //set Height param
		unsigned int getWidth();// Width function
		unsigned int setWidth(int ); //set Width param
		unsigned int getgrayLevel(); //the number of gray levels
		unsigned int setgrayLevel(int); //sets the gray level
		std::string getType(); //gets the type
		unsigned int** imageData; //the stored image pixels
		unsigned int** Red;
		unsigned int** Green;
		unsigned int** Blue;
		double* Hist; //vector for the histogram

//		int readPGM(char* ); //reads file into image
//		int writePGM(char* ); //writes image to file

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

	};

	//class JPEG: public Image {

	//	private:
	//		t_JPEG struct_JPEG;

	//		void f_readAPP0(FILE* );
	//};

	const double pi = std::acos(-1); // PI

	int mirrorVertical(Image* ); //mirrors an image by the vertical axis
	int mirrorHorizontal(Image* ); //mirors an image by the horizontal axis
	int computeHistogram(Image* ); //computes the histogram of a grayscale image
	int equalizeHistogramRemap(Image* ); //already computes histogram
	int equalizeHistogramCumulative(Image* ); //better than HistogramRemap
	int rotate(Image* ,float ); //input angle
	int computeGrayLevel(Image* );

	int average_filter(Image* ,int ,int ); //image object, windowSize, extra parameter for edge preserving
	int average_filter_color_normal(Image* ,int ,int ,int); //image object, windowSize, extra parameter for edge preserving, channel number (red,green or blue)
	//the sqrt average filter computes the sqrt of the average of the squares for each pixel
	int average_filter_color_sqrt(Image*,int ,int ,int); //image object, windowSize, extra parameter for edge preserving, channel number (red,green or blue)
	int gaussian_filter(Image* ,int ); //image object, sigma
	int bilateral_filterGray(Image* ,int ); //image object, sigma
	int bilateral_filterColor(Image* ,int ,int ); //image object, sigma, channel
	int guided_filter(Image* ,Image* ,int );
	int impulse_filter(Image* ,int ); //image object, window size
	int sobel(Image* ,Image* ); //input image and output image
	int sobel(Image* ); //input image only overload - sobel image saved into input
	int canny(Image* ,int );
	int unsharp_masking(Image* ,Image* );
	int stitch(Image* ,Image* );

	int segmentation(Image*,unsigned char);

	namespace CIMGInterface{

		int readImage(ImageProc::Image* ,char*); //transforms imageread into Image object
		cimg_library::CImg<unsigned char> displayImageGray(ImageProc::Image* ); //take Image obj and returns CImg object
		cimg_library::CImg<unsigned char> displayImageColor(ImageProc::Image* ); //take Image obj and returns CImg object
		cimg_library::CImg<unsigned char> displayHist(ImageProc::Image* ); //take Image obj and returns CImg object - histogram

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

}