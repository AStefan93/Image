//CIMG INTERFACE

#include "CImg_wrapper.h"

int CIMGInterface::readImage(ImageProc::Image* img, char const* imgPath){

	//read into Image object

	double R = 0.2126;
	double G = 0.7152;
	double B = 0.0722;

	cimg_library::CImg<unsigned char> image(imgPath);

	img->setHeight(image.height());
	img->setWidth(image.width());
	int Height = img->getHeight();
	int Width = img->getWidth();

	//allocate memory
	img->imageData = new unsigned int*[Height];
	for (int H = 0; H < Height; H++)
		img->imageData[H] = new unsigned int[Width];

	img->Red = new unsigned int*[Height];
	for (int i = 0; i < Height; i++)
		img->Red[i] = new unsigned int[Width];

	img->Green = new unsigned int*[Height];
	for (int i = 0; i < Height; i++)
		img->Green[i] = new unsigned int[Width];

	img->Blue = new unsigned int*[Height];
	for (int i = 0; i < Height; i++)
		img->Blue[i] = new unsigned int[Width];

	for (int H = 0; H < Height; H++) {
		for (int W = 0; W < Width; W++) {

			img->Red[H][W] = image(W,H,0,0);
			img->Green[H][W] = image(W,H,0,1);
			img->Blue[H][W] = image(W,H,0,2);
			img->imageData[H][W] = (unsigned int)(R*image(W,H,0,0) + G*image(W,H,0,1) + B*image(W,H,0,2));

		}
	}

	unsigned int temp = 0;
	img->setgrayLevel(temp); // initialize graylevel to 0
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			if(img->imageData[H][W] > temp){
				temp = img->imageData[H][W];
				img->setgrayLevel(temp); //set new graylevel

			}
		}
	}

//	img->Image_count += 1;

	return 0;
}

cimg_library::CImg<unsigned char> CIMGInterface::displayImageColor(ImageProc::Image* img){

	//display Image object

	int Height = img->getHeight();
	int Width = img->getWidth();

	cimg_library::CImg<unsigned char> image(Width,Height,1,3,0);

	for (int H = 0; H < Height; H++) {
		for (int W = 0; W < Width; W++) {

			image(W,H,0,0) = img->Red[H][W];
			image(W,H,0,1) = img->Green[H][W];
			image(W,H,0,2) = img->Blue[H][W];

		}
	}

	return image;
}

cimg_library::CImg<unsigned char> CIMGInterface::displayImageGray(ImageProc::Image* img){

	//display Image object

	int Height = img->getHeight();
	int Width = img->getWidth();

	cimg_library::CImg<unsigned char> image(Width,Height,1,1);

	for (int H = 0; H < Height; H++) {
		for (int W = 0; W < Width; W++) {

			image(W,H,0,0) = img->imageData[H][W];

		}
	}

	return image;
}

cimg_library::CImg<unsigned char> CIMGInterface::displayHist(ImageProc::Image* img){

	int Height = 500;
	int Width = 2*256;

	int maxHist = 0;

	for(int k = 0; k < 256; k++){

		if(img->Hist[k] > maxHist)
			maxHist = (int)img->Hist[k];

	}

	cimg_library::CImg<unsigned char> histogram(2*256,Height,1,3,255);//width,height, , nr of channels, white level

	for(int W = 0; W < Width; W++){
		for(int H = Height; H > (Height -  (img->Hist[W/2]*1.0)/(maxHist + 100)*Height); H--){
			histogram(W,H,0) = 0;
			histogram(W,H,1) = 0;
//			histogram(W,H,2) = 255;
		}
	}

	return histogram;
}

cimg_library::CImg<unsigned char> CIMGInterface::saveImageGray(ImageProc::Image* img,char const* imgPath){

	//display Image object

	int Height = img->getHeight();
	int Width = img->getWidth();

	cimg_library::CImg<unsigned char> image(Width,Height,1,1);

	for (int H = 0; H < Height; H++) {
		for (int W = 0; W < Width; W++) {

			image(W,H,0,0) = img->imageData[H][W];

		}
	}
	
	image.save(imgPath);

	return image;
}

