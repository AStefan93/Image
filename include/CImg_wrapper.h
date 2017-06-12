//include guard
#ifndef CIMG_WRAPPER_H
#define CIMG_WRAPPER_H

//include external header
#include "CImg.h"
#include "Image.h"


namespace CIMGInterface{

	int readImage(ImageProc::Image* ,char const*); //transforms imageread into Image object
	cimg_library::CImg<unsigned char> displayImageGray(ImageProc::Image* ); //take Image obj and returns CImg object
	cimg_library::CImg<unsigned char> displayImageColor(ImageProc::Image* ); //take Image obj and returns CImg object
	cimg_library::CImg<unsigned char> displayHist(ImageProc::Image* ); //take Image obj and returns CImg object - histogram

}

//end include guard
#endif
