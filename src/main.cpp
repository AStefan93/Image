//Arnautu Stefan Image Processing
//Property of Nobody

#include "ImageProc.h"

namespace imgintf = CIMGInterface;

int main(int argc, char* argv[]) { 
	

	char const* image_path = argv[1];
	char const* image_path2 = argv[2];

	std::clock_t start;
	double duration;
	start = std::clock();
	
	ImageProc::Image* img = new ImageProc::Image(image_path);
	ImageProc::Image* img2 = new ImageProc::Image(image_path);
//	ImageProc::Image* img3 = new ImageProc::Image[1];
	
	
	t_2DPoint* uLC = new t_2DPoint[1];
	t_2DPoint* lRC = new t_2DPoint[1];
	
//	imgintf::readImage(img,image_path);
//	imgintf::readImage(img2,image_path);
		
	uLC->x = img->getHeight()/2;
	uLC->y = 0;
	lRC->x = img->getHeight();
	lRC->y = img->getWidth();
	ImageProc::Square ROI(uLC,lRC);
	
//	ImageProc::Image* img2 = new ImageProc::Image(lRC->x - uLC->x,lRC->y - uLC->y);
	

//	ImageProc::crop(img,img2,ROI);
//	ImageProc::sobel(img2);

//	imgintf::saveImageGray(img2,image_path2);
//	imgintf::readImage(img2,image_path);
//	imgintf::readImage(img3,image_path);
//	ImageProc::gaussian_filter(img,3);
//	ImageProc::rotate(img,30);
//	ImageProc::rotate(img,45);
//	ImageProc::impulse_filter(img2,3);
//	ImageProc::bilateral_filterGray(img,21);
//	ImageProc::bilateral_filterColor(img,21,0);
//	ImageProc::bilateral_filterColor(img,21,1);
//	ImageProc::bilateral_filterColor(img,21,2);
//	ImageProc::gaussian_filter(img,5);
//	ImageProc::unsharp_masking_test(img,img2);

	ImageProc::equalizeHistogramCumulative(img2);
	
//	ImageProc::equalizeHistogramRemap(img3);
//	ImageProc::sobel(img,img2);

	ImageProc::computeHistogram(img);
	ImageProc::v_computeNormalizedHistogram(img);
//	ImageProc::computeHistogram(img2);
//	ImageProc::computeHistogram(img3);

//	printf("%f",img->normHist[10]);

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
	

//	delete uRC;
//	delete lLC;
	return 0;
}
