//Arnautu Stefan Image Processing
//Property of Nobody

#include "ImageProc.h"

namespace imgintf = CIMGInterface;

int main(int argc, char* argv[]) { 

	char const* image_path = argv[1];
	
	std::clock_t start;
	double duration;
	start = std::clock();
	
	ImageProc::Image* img = new ImageProc::Image[1];
	ImageProc::Image* img2 = new ImageProc::Image[1];
//	ImageProc::Image* img3 = new ImageProc::Image[1];

//	ImageProc::Image img3(image_path);
	imgintf::readImage(img,image_path);
	imgintf::readImage(img2,image_path);
//	imgintf::readImage(img3,image_path);
//	ImageProc::gaussian_filter(img,3);
//	ImageProc::rotate(img,30);
//	ImageProc::impulse_filter(img2,3);
//	ImageProc::bilateral_filterGray(img,21);
//	ImageProc::bilateral_filterColor(img,21,0);
//	ImageProc::bilateral_filterColor(img,21,1);
//	ImageProc::bilateral_filterColor(img,21,2);
//	ImageProc::gaussian_filter(img,5);
//	ImageProc::unsharp_masking_test(img,img2);
//	ImageProc::equalizeHistogramCumulative(img2);
//	ImageProc::equalizeHistogramRemap(img3);
//	ImageProc::sobel(img,img2);

	ImageProc::computeHistogram(img);
	ImageProc::computeHistogram(img2);
//	ImageProc::computeHistogram(img3);

	cimg_library::CImgDisplay init_disp(imgintf::displayImageGray(img));
	cimg_library::CImgDisplay init2_disp(imgintf::displayHist(img));
	cimg_library::CImgDisplay init3_disp(imgintf::displayImageGray(img2));
	cimg_library::CImgDisplay init4_disp(imgintf::displayHist(img2));
//	cimg_library::CImgDisplay init5_disp(imgintf::displayImageGray(img3));
//	cimg_library::CImgDisplay init6_disp(imgintf::displayHist(img3));
	
	
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "Time: " << duration << '\n';

	while (!init_disp.is_closed() && !init2_disp.is_closed()) {
    		init_disp.wait();
	}
	
	return 0;
}
