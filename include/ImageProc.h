//include guard
#ifndef IMAGE_PROC_HEADER
#define IMAGE_PROC_HEADER

#include "Image.h"
#include "CImg_wrapper.h"

namespace ImageProc {

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
	int unsharp_masking_test(Image* ,Image* );
	int stitch(Image* ,Image* );

	int segmentation(Image*,unsigned char);
	//cropping function
	//takes as input the input image, the output image and the square to which it will be cropped
	void crop(Image* ,Image* ,Square );
}

#endif
