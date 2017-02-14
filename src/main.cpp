//Arnautu Stefan Image Processing
//Property of Nobody

#include "Image.h"

namespace imgintf = ImageProc::CIMGInterface;

int main(int argc, char* argv[]) { 

	char const* image_path = argv[1];
	
	std::clock_t start;
	double duration;
	start = std::clock();
	
//	ImageProc::Image* img = new ImageProc::Image[1];
//	ImageProc::Image* img2 = new ImageProc::Image[1];

	ImageProc::Image img3(image_path);

//	imgintf::readImage(img,image_path);
//	imgintf::readImage(img2,image_path);
//	ImageProc::gaussian_filter(img,3);
//	ImageProc::rotate(img,30);
//	ImageProc::bilateral_filterGray(img2,21);
//	ImageProc::bilateral_filterColor(img,21,0);
//	ImageProc::bilateral_filterColor(img,21,1);
//	ImageProc::bilateral_filterColor(img,21,2);
//	ImageProc::gaussian_filter(img,5);
//	ImageProc::equalizeHistogramCumulative(img);
//	ImageProc::impulse_filter(img,5);
//	ImageProc::unsharp_masking(img,img2);
//	ImageProc::sobel(img,img2);

//	ImageProc::computeHistogram(img);
//	ImageProc::computeHistogram(img2);

//	cimg_library::CImgDisplay init_disp(imgintf::displayImageGray(img));
//	cimg_library::CImgDisplay init2_disp(imgintf::displayHist(img));
//	cimg_library::CImgDisplay init3_disp(imgintf::displayImageGray(img2));
//	cimg_library::CImgDisplay init4_disp(imgintf::displayHist(img2));

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "Time: " << duration << '\n';

	return 0;
}
