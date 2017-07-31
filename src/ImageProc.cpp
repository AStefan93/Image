#include "ImageProc.h"

const double Image_PI = std::acos(-1); // PI

int ImageProc::mirrorVertical(Image* img) {
	
	int temp;
	//CODE HERE
	for(unsigned int i = 0; i < img->getHeight(); i++){
		for(unsigned int j = 0; j < img->getWidth()/2; j++){
			temp = img->imageData[i][j];
			img->imageData[i][j] = img->imageData[i][img->getWidth() - j - 1];
			img->imageData[i][img->getWidth() - j] = temp;
		}
	}

	return 0;
}

int ImageProc::mirrorHorizontal(Image* img) {
	
	int temp;
	for(unsigned int i = 0; i < img->getHeight()/2; i++){
		for(unsigned int j = 0; j < img->getWidth(); j++){
			temp = img->imageData[i][j];
			img->imageData[i][j] = img->imageData[img->getHeight() - i - 1][j];
			img->imageData[img->getHeight() - i - 1][j] = temp;
		}
	}

	return 0;
}

int ImageProc::computeHistogram(Image* img){

	for(int i = 0; i < 256; i++)
		img->Hist[i] = 0; //initialize vector with zeroes;


	for(unsigned int i = 0; i < img->getHeight(); i++){
		for(unsigned int j = 0; j < img->getWidth(); j++){

			img->Hist[img->imageData[i][j]] ++;
			
		}
	}

	/*for(int i = 0; i < img->getHeight(); i++){
		for(int j = 0; j < img->getWidth(); j++){

			img->Hist[img->imageData[i][j]] = img->Hist[img->imageData[i][j]]/(img->getHeight()*img->getWidth()) ;
			
		}
	}*/

	return 0;
}

int ImageProc::equalizeHistogramRemap(Image* img){

	unsigned int max = img->getgrayLevel();
	int min = 0;
	int temp;

	ImageProc::computeHistogram(img);

	for(unsigned int i = 0; i < img->getgrayLevel(); i++){
			if((img->Hist[i] !=0) && (img->Hist[i-1] == 0) && min == 0)
				min = i;
	}

	for(unsigned int i = 0; i < img->getHeight(); i++){
		for(unsigned int j = 0; j < img->getWidth(); j++){
			temp = img->imageData[i][j] - min;
			if(temp < 0)
				temp = 0;
			img->imageData[i][j] = (int)(255*(temp*1.0/(max-min)));

			if(img->imageData[i][j] > img->getgrayLevel())
				img->setgrayLevel(img->imageData[i][j]);
		}
	}

	ImageProc::computeHistogram(img); //recompute the histogram

	return 0;
}

int ImageProc::equalizeHistogramCumulative(Image* img){

	double sum = 0;
	double lut[256];

	ImageProc::computeHistogram(img);

	// build a LUT containing scale factor
	for ( int i=0; i < 256 ; ++i )
	{
	  sum += img->Hist[i];
		lut[i] = (double)( sum * 255) / (img->getHeight()*img->getWidth());
	}

	// transform image using sum histogram as a LUT
	for(unsigned int i = 0; i < img->getHeight(); i++){
		for(unsigned int j = 0; j < img->getWidth(); j++){

			 img->imageData[i][j] = (unsigned int)lut[img->imageData[i][j]];

		}
	}

	unsigned int temp = 0;
	img->setgrayLevel(temp); // initialize graylevel to 0
	for(unsigned int i = 0; i < img->getHeight(); i++){
		for(unsigned int j = 0; j < img->getWidth(); j++){

			if(img->imageData[i][j] > temp){
				temp = img->imageData[i][j];
				img->setgrayLevel(temp); //set graylevel after histogram

			}
		}
	}

	ImageProc::computeHistogram(img); //recompute the histogram

	return 0;
}

int ImageProc::rotate(Image* img, float theta){

	unsigned int** tempImage;
	unsigned int x_prime;
	unsigned int y_prime;
	int32_t x_c; //horizontal coordonate relative to selected center. IT CAN BE NEGATIVE
	int32_t y_c; // vertical coordonate relative to selected center. IT CAN BE NEGATIVE

	uint32_t H = img->getHeight();
	uint32_t W = img->getWidth();

	double rad = theta * Image_PI / 180; //convert degrees to rad

	tempImage = new unsigned int*[H];
	for (unsigned int i = 0; i < H; i++)
		tempImage[i] = new unsigned int[W];
	for (unsigned int i = 0; i < H; i++)
		for(unsigned int j = 0; j < W; j++)
		tempImage[i][j] = 0; //initialise matrix with zeroes

	for(unsigned int i = 0; i < H; i++){
		for(unsigned int j = 0; j < W; j++){

			x_c = (int32_t)i - (int32_t)(H)/2;
			y_c = (int32_t)j - (int32_t)(W)/2;

			x_prime = (unsigned int)( std::cos(rad)*(x_c) - std::sin(rad)*(y_c)  + (H)/2 );
			y_prime = (unsigned int)( std::sin(rad)*(x_c) + std::cos(rad)*(y_c) + (W)/2);

			if((x_prime >= 0) && (x_prime < H) && (y_prime >= 0) && (y_prime < W))
				tempImage[x_prime][y_prime] = img->imageData[i][j]; 

		}
	}

	for(unsigned int i = 0; i < H; i++){
		for(unsigned int j = 0; j < W; j++){

			img->imageData[i][j] = tempImage[i][j];

		}
	}

	for (unsigned int i = 0; i < H; i++)
		delete[] tempImage[i];
	delete[] tempImage;

	return 0;
}

int ImageProc::impulse_filter(Image* img,int windowSize){

	if((windowSize%2 == 0) || (windowSize < 3)){
		std::cout << "windowSize must be odd and higher or equal to 3" << std::endl;
	//	getchar();
		exit(-1);
	}

	unsigned int** tempImage;
	tempImage = new unsigned int*[img->getHeight()];
	for (unsigned int i = 0; i < img->getHeight(); i++)
		tempImage[i] = new unsigned int[img->getWidth()];
	for (unsigned int i = 0; i < img->getHeight(); i++)
		for(unsigned int j = 0; j < img->getWidth(); j++)
		tempImage[i][j] = 0; //initialise matrix with zeroes

	int* medianBufferX;
	int* medianBufferY;
	medianBufferX = new int[windowSize];
	medianBufferY = new int[windowSize];
	
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			for(int k = -windowSize/2; k < windowSize/2 + 1 ; k++){
				if((H+k)>=0 && (W+k)>=0 && (H+k)<img->getHeight() && (W+k) < img->getWidth()){
					medianBufferX[k+(windowSize/2)] = img->imageData[H][W+k];
					medianBufferY[k+(windowSize/2)] = img->imageData[H+k][W];
				}
				else {
					medianBufferX[k+(windowSize/2)] = 0;
					medianBufferY[k+(windowSize/2)] = 0;
				}
			}

			int aux;
			for(int i = 0; i < windowSize - 1; i++){
				for(int j = i+1; j < windowSize; j++){
					if(medianBufferX[i] > medianBufferX[j]){
						aux = medianBufferX[j];
						medianBufferX[j] = medianBufferX[i];
						medianBufferX[i] = aux;
					}
					if(medianBufferY[i] > medianBufferY[j]){
						aux = medianBufferY[j];
						medianBufferY[j] = medianBufferY[i];
						medianBufferY[i] = aux;
					}
				}
			}

			tempImage[H][W] = medianBufferX[windowSize/2]/2 + medianBufferY[windowSize/2]/2;
			
		}
	}

	for(unsigned int i = 0; i < img->getHeight(); i++){
		for(unsigned int j = 0; j < img->getWidth(); j++){

			img->imageData[i][j] = tempImage[i][j];

		}
	}

	for (unsigned int i = 0; i < img->getHeight(); i++)
		delete tempImage[i];
	delete tempImage;
	delete medianBufferX;
	delete medianBufferY;

	return 0;
}

int ImageProc::average_filter(Image* img,int windowSize,int n ){

	if((windowSize%2 == 0) || (windowSize < 3)){
		std::cout << "windowSize must be odd and higher or equal to 3" << std::endl;
	//	getchar();
		exit(-1);
	}

	if((n < 1)){
		std::cout << "n must be higher or equal to 1" << std::endl;
	//	getchar();
		exit(-1);
	}

	unsigned int** tempImage;

	tempImage = new unsigned int*[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		tempImage[H] = new unsigned int[img->getWidth()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		for(unsigned int W = 0; W < img->getWidth(); W++)
		tempImage[H][W] = 0; //initialise matrix with zeroes

	double avrFilterX = 0;
	double avrFilterY = 0;
	int length;
	double* coef;
	coef = new double[windowSize];
	double coefsum = 0;

	/* compute coefficients */
	for(int distance = -windowSize/2; distance <= windowSize/2; distance++) {

		if(distance < 0) length = -distance;
		else length = distance;

		coef[distance + windowSize/2] = std::pow(n*1.0, (windowSize/2 - length));
		coefsum += coef[distance + windowSize/2];

	}

	//compute temporary image for X axis
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			avrFilterX = 0;

			for(int distance = -windowSize/2; distance <= windowSize/2 ; distance++){
				if((W+distance)>=0 && (W+distance) < img->getWidth()){
						avrFilterX += img->imageData[H][W+distance]*(coef[distance + windowSize/2]/coefsum);
				}
				else {
					avrFilterX += 0;
				}
			}

			tempImage[H][W] = (int)avrFilterX;
			
		}
	}

	//copy image
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			img->imageData[H][W] = tempImage[H][W];

		}
	}

	//compute temporary image for Y axis
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			avrFilterY = 0;

			for(int distance = -windowSize/2; distance <= windowSize/2 ; distance++){
				if((H+distance)>=0 && (H+distance) < img->getHeight()){
						avrFilterY += img->imageData[H+distance][W]*(coef[distance + windowSize/2]/coefsum);
				}
				else {
					avrFilterY += 0;
				}
			}

			tempImage[H][W] = (int)avrFilterY;
			
		}
	}

	//copy image
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			img->imageData[H][W] = tempImage[H][W];

		}
	}


	for (unsigned int H = 0; H < img->getHeight(); H++)
		delete tempImage[H];
	delete tempImage;

	delete coef;

	return 0;
}

int ImageProc::average_filter_color_sqrt(Image* img,int windowSize,int n,int channel){

	if((windowSize%2 == 0) || (windowSize < 3)){
		std::cout << "windowSize must be odd and higher or equal to 3" << std::endl;
	//	getchar();
		exit(-1);
	}

	if((n < 1)){
		std::cout << "n must be higher or equal to 1" << std::endl;
	//	getchar();
		exit(-1);
	}

	unsigned int** tempImage;

	tempImage = new unsigned int*[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		tempImage[H] = new unsigned int[img->getWidth()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		for(unsigned int W = 0; W < img->getWidth(); W++)
		tempImage[H][W] = 0; //initialise matrix with zeroes

	double avrFilterX = 0;
	double avrFilterY = 0;
	int length;
	double* coef;
	coef = new double[windowSize];
	double coefsum = 0;

	/* compute coefficients */
	for(int distance = -windowSize/2; distance <= windowSize/2; distance++) {

		if(distance < 0) length = -distance;
		else length = distance;

		coef[distance + windowSize/2] = std::pow(n*1.0, (windowSize/2 - length));
		coefsum += coef[distance + windowSize/2];

	}

	//compute temporary image for X axis
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			avrFilterX = 0;

			for(int distance = -windowSize/2; distance <= windowSize/2 ; distance++){
				if((W+distance)>=0 && (W+distance) < img->getWidth()){
					switch(channel){
						case 0: avrFilterX += img->Red[H][W+distance]*img->Red[H][W+distance]*(coef[distance + windowSize/2]/coefsum);
						break;
						case 1: avrFilterX += img->Green[H][W+distance]*img->Green[H][W+distance]*(coef[distance + windowSize/2]/coefsum);
						break;
						case 2: avrFilterX += img->Blue[H][W+distance]*img->Blue[H][W+distance]*(coef[distance + windowSize/2]/coefsum);
						break;
					}
				}
				else {
					avrFilterX += 0;
				}
			}

			tempImage[H][W] = (unsigned int)std::sqrt(avrFilterX);
			
		}
	}

	//copy image
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){
				switch(channel){
						case 0: img->Red[H][W] = tempImage[H][W];
						break;
						case 1: img->Green[H][W] = tempImage[H][W];
						break;
						case 2: img->Blue[H][W] = tempImage[H][W];
						break;
				}

		}
	}

	//compute temporary image for Y axis
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			avrFilterY = 0;

			for(int distance = -windowSize/2; distance <= windowSize/2 ; distance++){
				if((H+distance)>=0 && (H+distance) < img->getHeight()){
					switch(channel){
						case 0: avrFilterY += img->Red[H+distance][W]*img->Red[H+distance][W]*(coef[distance + windowSize/2]/coefsum);
						break;
						case 1: avrFilterY += img->Green[H+distance][W]*img->Green[H+distance][W]*(coef[distance + windowSize/2]/coefsum);
						break;
						case 2: avrFilterY += img->Blue[H+distance][W]*img->Blue[H+distance][W]*(coef[distance + windowSize/2]/coefsum);
						break;
					}
				}
				else {
					avrFilterY += 0;
				}
			}

			tempImage[H][W] = (unsigned int)std::sqrt(avrFilterY);
			
		}
	}

	//copy image
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){
			switch(channel){
						case 0: img->Red[H][W] = tempImage[H][W];
						break;
						case 1: img->Green[H][W] = tempImage[H][W];
						break;
						case 2: img->Blue[H][W] = tempImage[H][W];
						break;
			}

		}
	}


	for (unsigned int H = 0; H < img->getHeight(); H++)
		delete tempImage[H];
	delete tempImage;

	delete coef;

	return 0;
}

int ImageProc::average_filter_color_normal(Image* img,int windowSize,int n,int channel){

	if((windowSize%2 == 0) || (windowSize < 3)){
		std::cout << "windowSize must be odd and higher or equal to 3" << std::endl;
	//	getchar();
		exit(-1);
	}

	if((n < 1)){
		std::cout << "n must be higher or equal to 1" << std::endl;
	//	getchar();
		exit(-1);
	}

	unsigned int** tempImage;

	tempImage = new unsigned int*[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		tempImage[H] = new unsigned int[img->getWidth()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		for(unsigned int W = 0; W < img->getWidth(); W++)
		tempImage[H][W] = 0; //initialise matrix with zeroes

	double avrFilterX = 0;
	double avrFilterY = 0;
	int length;
	double* coef;
	coef = new double[windowSize];
	double coefsum = 0;

	/* compute coefficients */
	for(int distance = -windowSize/2; distance <= windowSize/2; distance++) {

		if(distance < 0) length = -distance;
		else length = distance;

		coef[distance + windowSize/2] = std::pow(n*1.0, (windowSize/2 - length));
		coefsum += coef[distance + windowSize/2];

	}

	//compute temporary image for X axis
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			avrFilterX = 0;

			for(int distance = -windowSize/2; distance <= windowSize/2 ; distance++){
				if((W+distance)>=0 && (W+distance) < img->getWidth()){
					switch(channel){
						case 0: avrFilterX += img->Red[H][W+distance]*(coef[distance + windowSize/2]/coefsum);
						break;
						case 1: avrFilterX += img->Green[H][W+distance]*(coef[distance + windowSize/2]/coefsum);
						break;
						case 2: avrFilterX += img->Blue[H][W+distance]*(coef[distance + windowSize/2]/coefsum);
						break;
					}
				}
				else {
					avrFilterX += 0;
				}
			}

			tempImage[H][W] = (unsigned int)avrFilterX;
			
		}
	}

	//copy image
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){
				switch(channel){
						case 0: img->Red[H][W] = tempImage[H][W];
						break;
						case 1: img->Green[H][W] = tempImage[H][W];
						break;
						case 2: img->Blue[H][W] = tempImage[H][W];
						break;
				}

		}
	}

	//compute temporary image for Y axis
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			avrFilterY = 0;

			for(int distance = -windowSize/2; distance <= windowSize/2 ; distance++){
				if((H+distance)>=0 && (H+distance) < img->getHeight()){
					switch(channel){
						case 0: avrFilterY += img->Red[H+distance][W]*(coef[distance + windowSize/2]/coefsum);
						break;
						case 1: avrFilterY += img->Green[H+distance][W]*(coef[distance + windowSize/2]/coefsum);
						break;
						case 2: avrFilterY += img->Blue[H+distance][W]*(coef[distance + windowSize/2]/coefsum);
						break;
					}
				}
				else {
					avrFilterY += 0;
				}
			}

			tempImage[H][W] = (unsigned int)avrFilterY;
			
		}
	}

	//copy image
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){
			switch(channel){
						case 0: img->Red[H][W] = tempImage[H][W];
						break;
						case 1: img->Green[H][W] = tempImage[H][W];
						break;
						case 2: img->Blue[H][W] = tempImage[H][W];
						break;
			}

		}
	}


	for (unsigned int H = 0; H < img->getHeight(); H++)
		delete tempImage[H];
	delete tempImage;

	delete coef;

	return 0;
}

int ImageProc::gaussian_filter(Image* img,int sigma){

	if(sigma < 1){
		std::cout << "Sigma must be higher or equal to 1" << std::endl;
	//	getchar();
		exit(-1);
	}

	int windowSize;
	double pcoef = 2.0 * sigma * sigma;

	if(sigma%2 == 0)
		windowSize = 3*sigma - 1;
	else
		windowSize = 3*sigma;

	unsigned int** tempImage;

	tempImage = new unsigned int*[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		tempImage[H] = new unsigned int[img->getWidth()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		for(unsigned int W = 0; W < img->getWidth(); W++)
		tempImage[H][W] = 0; //initialise matrix with zeroes

	double gaussFilterX = 0;
	double gaussFilterY = 0;
	double* coef;
	coef = new double[windowSize];
	double coefsum = 0;

	/* compute coefficients */
	for(int distance = -windowSize/2; distance <= windowSize/2; distance++) {

		coef[distance + windowSize/2] = (std::exp(-(distance*distance)/pcoef))/(Image_PI*pcoef);
		coefsum += coef[distance + windowSize/2];

	}

	//compute temporary image for X axis
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			gaussFilterX = 0;

			for(int distance = -windowSize/2; distance <= windowSize/2 ; distance++){
				if((W+distance)>=0 && (W+distance) < img->getWidth()){
						gaussFilterX += img->imageData[H][W+distance]*(coef[distance + windowSize/2]/coefsum);
				}
				else {
					gaussFilterX += 0;
				}
			}

			tempImage[H][W] = (unsigned int)gaussFilterX;
			
		}
	}

	//copy image
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			img->imageData[H][W] = tempImage[H][W];

		}
	}

	//compute temporary image for Y axis
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			gaussFilterY = 0;

			for(int distance = -windowSize/2; distance <= windowSize/2 ; distance++){
				if((H+distance)>=0 && (H+distance) < img->getHeight()){
						gaussFilterY += img->imageData[H+distance][W]*(coef[distance + windowSize/2]/coefsum);
				}
				else {
					gaussFilterY += 0;
				}
			}

			tempImage[H][W] = (unsigned int)gaussFilterY;
			
		}
	}

	//copy image
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			img->imageData[H][W] = tempImage[H][W];

		}
	}


	for (unsigned int H = 0; H < img->getHeight(); H++)
		delete [] tempImage[H];
	delete [] tempImage;

	delete [] coef;

	return 0;
}

int ImageProc::bilateral_filterGray(Image* img,int sigma){

	//gaussian filter with dynamic edge adjustment
	if(sigma < 1){
		std::cout << "Sigma must be higher or equal to 1" << std::endl;
	//	getchar();
		exit(-1);
	}

	int windowSize;
	int Height = img->getHeight();
	int Width = img->getWidth();
	double pcoef = 2 * sigma * sigma;
	double scoef = (std::sqrt(2*Image_PI)*sigma);

	if(sigma%2 == 0)
		windowSize = 6*sigma - 1;
	else
		windowSize = 6*sigma;

	unsigned int** tempImage;
	unsigned int** ImageCopy;

	tempImage = new unsigned int*[Height];
	for (int H = 0; H < Height; H++)
		tempImage[H] = new unsigned int[Width];
	ImageCopy = new unsigned int*[Height];
	for (int H = 0; H < Height; H++)
		ImageCopy[H] = new unsigned int[Width];

	for(int H = 0; H < Height; H++){
		for(int W = 0; W < Width; W++){
			ImageCopy[H][W] = img->imageData[H][W]; // copy image
		}
	}

	double gaussFilterX = 0;
	double gaussFilterY = 0;
	double icoef;
	double coefsum = 0;
	double intensityDif;
	double* dcoef;
	dcoef = new double[windowSize];

	int halfwindowSize = windowSize/2;

	/* compute coefficients */
	for(int distance = -halfwindowSize; distance <= halfwindowSize; distance++) {

		dcoef[distance + halfwindowSize] = std::exp(-(distance*distance)/pcoef)/scoef;
		
	}

	//compute temporary image for Y axis
	for(int H = 0; H < Height; H++){
		for(int W = 0; W < Width; W++){

			gaussFilterY = 0;
			coefsum = 0;

			//compute gauss filter
			for(int distance = -halfwindowSize; distance <= halfwindowSize ; distance++){
					if((W+distance)>=0 && (W+distance) < Width){
						intensityDif = ImageCopy[H][W] - ImageCopy[H][W+distance];
						icoef = dcoef[distance+halfwindowSize]*(std::exp(-(intensityDif*intensityDif)/pcoef));
						gaussFilterY += ImageCopy[H][W+distance]*icoef;
						coefsum += icoef;
					}
					else 
						gaussFilterY += 0;
				}
				tempImage[H][W] = (int)(gaussFilterY/coefsum);
			
		}
	}

	//copy image
	for(int H = 0; H < Height; H++){
		for(int W = 0; W < Width; W++){

			ImageCopy[H][W] = tempImage[H][W];

		}
	}

	//compute temporary image for X axis
	for(int H = 0; H < Height; H++){
		for(int W = 0; W < Width; W++){

			gaussFilterX = 0;
			coefsum = 0;

			//compute Gauss Filter
			for(int distance = -halfwindowSize; distance <= halfwindowSize ; distance++){
					if((H+distance)>=0 && (H+distance) < Height){
						intensityDif = ImageCopy[H][W] - ImageCopy[H+distance][W];
						icoef = dcoef[distance+halfwindowSize]*(std::exp(-(intensityDif*intensityDif)/pcoef));
						gaussFilterX += ImageCopy[H+distance][W]*icoef;
						coefsum += icoef;
					}
					else
						gaussFilterX += 0;
				}
				tempImage[H][W] = (int)(gaussFilterX/coefsum);
			
		}
	}

	//copy image
	for(int H = 0; H < Height; H++){
		for(int W = 0; W < Width; W++){

			img->imageData[H][W] = tempImage[H][W];

		}
	}


	for (int H = 0; H < Height; H++)
		delete tempImage[H];
	delete tempImage;

	return 0;
}

int ImageProc::bilateral_filterColor(Image* img,int sigma,int channel){

	//gaussian filter with dynamic edge adjustment
	if(sigma < 1){
		std::cout << "Sigma must be higher or equal to 1" << std::endl;
	//	getchar();
		exit(-1);
	}
	if(channel < 0 || channel > 2){
		std::cout << "Channel must be between 0 and 2, where 0 is Red and 2 is Blue" << std::endl;
	//	getchar();
		exit(-1);
	}

	int windowSize;
	int Height = img->getHeight();
	int Width = img->getWidth();
	double pcoef = 2 * sigma * sigma;
	double scoef = (std::sqrt(2*Image_PI)*sigma);

	if(sigma%2 == 0)
		windowSize = 6*sigma - 1;
	else
		windowSize = 6*sigma;

	double** tempImage;
	double** ImageCopy;

	tempImage = new double*[Height];
	for (int H = 0; H < Height; H++)
		tempImage[H] = new double[Width];
	ImageCopy = new double*[Height];
	for (int H = 0; H < Height; H++)
		ImageCopy[H] = new double[Width];

	for(int H = 0; H < Height; H++){
		for(int W = 0; W < Width; W++){
			switch(channel){
				case 0: ImageCopy[H][W] = img->Red[H][W]; // copy image
				break;
				case 1: ImageCopy[H][W] = img->Green[H][W]; // copy image
				break; 
				case 2: ImageCopy[H][W] = img->Blue[H][W]; // copy image
				break;
			}
		}
	}

	double gaussFilterX = 0;
	double gaussFilterY = 0;
	double icoef;
	double coefsum = 0;
	double intensityDif;
	double* dcoef;
	dcoef = new double[windowSize];

	int halfwindowSize = windowSize/2;

	/* compute coefficients */
	for(int distance = -halfwindowSize; distance <= halfwindowSize; distance++) {

		dcoef[distance + halfwindowSize] = std::exp(-(distance*distance)/pcoef)/scoef;
		
	}

	//compute temporary image for Y axis
	for(int H = 0; H < Height; H++){
		for(int W = 0; W < Width; W++){

			gaussFilterY = 0;
			coefsum = 0;

			//compute gauss filter
			for(int distance = -halfwindowSize; distance <= halfwindowSize ; distance++){
					if((W+distance)>=0 && (W+distance) < Width){
						intensityDif = ImageCopy[H][W] - ImageCopy[H][W+distance];
						icoef = dcoef[distance+halfwindowSize]*(std::exp(-(intensityDif*intensityDif)/pcoef));
						gaussFilterY += ImageCopy[H][W+distance]*icoef;
						coefsum += icoef;
					}
					else 
						gaussFilterY += 0;
				}
				tempImage[H][W] = (gaussFilterY/coefsum);
			
		}
	}

	//copy image
	for(int H = 0; H < Height; H++){
		for(int W = 0; W < Width; W++){

			ImageCopy[H][W] = tempImage[H][W];

		}
	}

	//compute temporary image for X axis
	for(int H = 0; H < Height; H++){
		for(int W = 0; W < Width; W++){

			gaussFilterX = 0;
			coefsum = 0;

			//compute Gauss Filter
			for(int distance = -halfwindowSize; distance <= halfwindowSize ; distance++){
					if((H+distance)>=0 && (H+distance) < Height){
						intensityDif = ImageCopy[H][W] - ImageCopy[H+distance][W];
						icoef = dcoef[distance+halfwindowSize]*(std::exp(-(intensityDif*intensityDif)/pcoef));
						gaussFilterX += ImageCopy[H+distance][W]*icoef;
						coefsum += icoef;
					}
					else
						gaussFilterX += 0;
				}
				tempImage[H][W] = (gaussFilterX/coefsum);
			
		}
	}

	//copy image
	for(int H = 0; H < Height; H++){
		for(int W = 0; W < Width; W++){
			switch(channel){
				case 0: img->Red[H][W] = (int)tempImage[H][W]; // copy image
				break;
				case 1: img->Green[H][W] = (int)tempImage[H][W]; // copy image
				break;
				case 2: img->Blue[H][W] = (int)tempImage[H][W]; // copy image
				break;
			}

		}
	}


	for (int H = 0; H < Height; H++)
		delete tempImage[H];
	delete tempImage;

	return 0;
}

int ImageProc::guided_filter(Image* img, Image* guidanceImg,int sigma){

	return 0;
}

int ImageProc::sobel(Image* img,Image* dimg){

	//copy img to dimg
	dimg->imageData = new unsigned int *[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		dimg->imageData[H] = new unsigned int [img->getWidth()];

	dimg->setgrayLevel(img->getgrayLevel());
	dimg->setHeight(img->getHeight());
	dimg->setWidth(img->getWidth());

	//begin sobel
	unsigned char** sobelX;
	unsigned char** sobelY;
	unsigned char** sobelXY;
	unsigned char** sobelYX;

	sobelX = new unsigned char*[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		sobelX[H] = new unsigned char[img->getWidth()];
	sobelY = new unsigned char*[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		sobelY[H] = new unsigned char[img->getWidth()];
	sobelXY = new unsigned char*[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		sobelXY[H] = new unsigned char[img->getWidth()];
	sobelYX = new unsigned char*[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		sobelYX[H] = new unsigned char[img->getWidth()];

	//compute sobel filter Y
	for(unsigned int H = 1; H < img->getHeight() - 1; H++){
		for(unsigned int W = 1; W < img->getWidth() - 1; W++){

			sobelY[H][W] = (unsigned char)std::abs((double)img->imageData[H-1][W-1] + 2*img->imageData[H-1][W] + img->imageData[H-1][W+1]
			- img->imageData[H+1][W-1] - 2*img->imageData[H+1][W] - img->imageData[H+1][W+1]);
			
		}
	}
	//compute sobel filter X
	for(unsigned int H = 1; H < img->getHeight() - 1; H++){
		for(unsigned int W = 1; W < img->getWidth() - 1; W++){

			sobelX[H][W] = (unsigned char)std::abs((double)img->imageData[H-1][W-1] + 2*img->imageData[H][W-1] + img->imageData[H+1][W-1]
			- img->imageData[H-1][W+1] - 2*img->imageData[H][W+1] - img->imageData[H+1][W+1]);
			
		}
	}
	//compute XY diagonal filter
	for(unsigned int H = 1; H < img->getHeight() - 1; H++){
		for(unsigned int W = 1; W < img->getWidth() - 1; W++){

			sobelXY[H][W] = (unsigned char)std::abs((double)2*img->imageData[H-1][W-1] + img->imageData[H-1][W] + img->imageData[H][W-1]
			- img->imageData[H+1][W] - 2*img->imageData[H+1][W+1] - img->imageData[H][W+1]);
			
		}
	}
	//compute YX diagonal fitler
	for(unsigned int H = 1; H < img->getHeight() - 1; H++){
		for(unsigned int W = 1; W < img->getWidth() - 1; W++){

			sobelYX[H][W] = (unsigned char)std::abs((double)img->imageData[H-1][W] + 2*img->imageData[H-1][W+1] + img->imageData[H][W+1]
			- img->imageData[H][W-1] - 2*img->imageData[H+1][W-1] - img->imageData[H+1][W]);
			
		}
	}
	//end sobel

	//copy image
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			dimg->imageData[H][W] = (unsigned int)std::abs(sobelX[H][W]/4 + sobelY[H][W]/4 + sobelXY[H][W]/4 + sobelYX[H][W]/4);

		}
	}

	//set new gray level for dimg
	for(unsigned int i = 0; i < dimg->getHeight(); i++){
		for(unsigned int j = 0; j < dimg->getWidth(); j++){
			if(dimg->imageData[i][j] > dimg->getgrayLevel())
				dimg->setgrayLevel(dimg->imageData[i][j]);
		}
	}

	for (unsigned int H = 0; H < img->getHeight(); H++)
		delete sobelX[H];
	delete sobelX;
	for (unsigned int H = 0; H < img->getHeight(); H++)
		delete sobelY[H];
	delete sobelY;
	for (unsigned int H = 0; H < img->getHeight(); H++)
		delete sobelXY[H];
	delete sobelXY;
	for (unsigned int H = 0; H < img->getHeight(); H++)
		delete sobelYX[H];
	delete sobelYX;

	return 0;
}

int ImageProc::sobel(Image* img){

	//begin sobel
	unsigned char** sobelX;
	unsigned char** sobelY;
	unsigned char** sobelXY;
	unsigned char** sobelYX;

	sobelX = new unsigned char*[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		sobelX[H] = new unsigned char[img->getWidth()];
	sobelY = new unsigned char*[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		sobelY[H] = new unsigned char[img->getWidth()];
	sobelXY = new unsigned char*[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		sobelXY[H] = new unsigned char[img->getWidth()];
	sobelYX = new unsigned char*[img->getHeight()];
	for (unsigned int H = 0; H < img->getHeight(); H++)
		sobelYX[H] = new unsigned char[img->getWidth()];

	//compute sobel filter Y
	for(unsigned int H = 1; H < img->getHeight() - 1; H++){
		for(unsigned int W = 1; W < img->getWidth() - 1; W++){

			sobelY[H][W] = (unsigned char)std::abs((double)img->imageData[H-1][W-1] + 2*img->imageData[H-1][W] + img->imageData[H-1][W+1]
			- img->imageData[H+1][W-1] - 2*img->imageData[H+1][W] - img->imageData[H+1][W+1]);
			
		}
	}
	//compute sobel filter X
	for(unsigned int H = 1; H < img->getHeight() - 1; H++){
		for(unsigned int W = 1; W < img->getWidth() - 1; W++){

			sobelX[H][W] = (unsigned char)std::abs((double)img->imageData[H-1][W-1] + 2*img->imageData[H][W-1] + img->imageData[H+1][W-1]
			- img->imageData[H-1][W+1] - 2*img->imageData[H][W+1] - img->imageData[H+1][W+1]);
			
		}
	}
	//compute XY diagonal filter
	for(unsigned int H = 1; H < img->getHeight() - 1; H++){
		for(unsigned int W = 1; W < img->getWidth() - 1; W++){

			sobelXY[H][W] = (unsigned char)std::abs((double)2*img->imageData[H-1][W-1] + img->imageData[H-1][W] + img->imageData[H][W-1]
			- img->imageData[H+1][W] - 2*img->imageData[H+1][W+1] - img->imageData[H][W+1]);
			
		}
	}
	//compute YX diagonal fitler
	for(unsigned int H = 1; H < img->getHeight() - 1; H++){
		for(unsigned int W = 1; W < img->getWidth() - 1; W++){

			sobelYX[H][W] = (unsigned char)std::abs((double)img->imageData[H-1][W] + 2*img->imageData[H-1][W+1] + img->imageData[H][W+1]
			- img->imageData[H][W-1] - 2*img->imageData[H+1][W-1] - img->imageData[H+1][W]);
			
		}
	}
	//end sobel

	//copy image
	for(unsigned int H = 0; H < img->getHeight(); H++){
		for(unsigned int W = 0; W < img->getWidth(); W++){

			img->imageData[H][W] = (unsigned int)std::abs(sobelX[H][W]/4 + sobelY[H][W]/4 + sobelXY[H][W]/4 + sobelYX[H][W]/4);

		}
	}

	//set new gray level for dimg
	for(unsigned int i = 0; i < img->getHeight(); i++){
		for(unsigned int j = 0; j < img->getWidth(); j++){
			if(img->imageData[i][j] > img->getgrayLevel())
				img->setgrayLevel(img->imageData[i][j]);
		}
	}

	for (unsigned int H = 0; H < img->getHeight(); H++)
		delete sobelX[H];
	delete sobelX;
	for (unsigned int H = 0; H < img->getHeight(); H++)
		delete sobelY[H];
	delete sobelY;
	for (unsigned int H = 0; H < img->getHeight(); H++)
		delete sobelXY[H];
	delete sobelXY;
	for (unsigned int H = 0; H < img->getHeight(); H++)
		delete sobelYX[H];
	delete sobelYX;

	return 0;
}

int ImageProc::unsharp_masking_test(Image* img,Image* img2){
	
	unsigned int Height = img->getHeight();
	unsigned int Width = img->getWidth();

	//create pointer
	unsigned int** orgImg;

	orgImg = new unsigned int*[Height];
	for (unsigned int H = 0; H < Height; H++){
		orgImg[H] = new unsigned int[Width];
	}

	//int** tempImg;

	/*tempImg = new int*[Height];
	for (int H = 0; H < Height; H++){
		tempImg[H] = new int[Width];
	}*/
	//end create pointer

	for(unsigned int H = 0; H < Height; H++){
		for(unsigned int W = 0; W < Width; W++){
			orgImg[H][W] = img->imageData[H][W];
		}
	}

	ImageProc::gaussian_filter(img,3);

	float c = 0.75;
	float a = c/(2*c - 1);
	float b = (1-c)/(2*c -1);
	
	for(unsigned int H = 0; H < Height; H++){
		for(unsigned int W = 0; W < Width; W++){
			img2->imageData[H][W] = ((unsigned int)std::abs((a * orgImg[H][W]) - (b * (img->imageData[H][W]))));
		}
	//	std::cout << img2->imageData[H][0] << " ";
	}

	for(unsigned int H = 0; H < Height; H++){
		for(unsigned int W = 0; W < Width; W++){
			img->imageData[H][W] = orgImg[H][W];
		}
	}
	
	/*for(int H = 0; H < Height; H++){
		for(int W = 0; W < Width; W++){
			img2->imageData[H][W] = tempImg[H][W];
		}
	}*/

	//delete pointer

	for (unsigned int H = 0; H < Height; H++){
		delete [] orgImg[H];
	}
	delete [] orgImg;
	
	//for (int H = 0; H < Height; H++){
	//	delete tempImg[H];
	//}
	//delete tempImg;
	//end delete pointer

	return 0;
}

int ImageProc::segmentation(Image* img,unsigned char populationSize){

	//1 generate population
		//randomise 50 sigmas and 50 mius
	double* normalisedHistogram;
	normalisedHistogram = new double[256];

	int Height = img->getHeight();
	int Width = img->getWidth();

	double** gaussian1;
	gaussian1 = new double*[populationSize];
	for (int i = 0; i < populationSize; i++)
		gaussian1[i] = new double[256];

	double** gaussian2;
	gaussian2 = new double*[populationSize];
	for (int i = 0; i < populationSize; i++)
		gaussian2[i] = new double[256];

	MachineLearning::twogauss* individ;
	individ = new MachineLearning::twogauss[populationSize];

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,127);
	
	for(int i = 0; i < populationSize; i++){
		(individ+i)->sigma1 = distribution(generator);
		(individ+i)->A1 = distribution(generator)*1.0/127; //normalise amplitude to 0-1
		(individ+i)->miu1 = distribution(generator);

		(individ+i)->sigma2 = distribution(generator);
		(individ+i)->A2 = distribution(generator)*1.0/127; //normalise amplitude to 0-1
		(individ+i)->miu2 = distribution(generator)+128;

		(individ+i)->delta = 0;
	}

	//2 generate gaussians
		//compute 0-127 and 128-255 values for each gaussian

	for(int id = 0; id < populationSize; id++){
		for(int val = 0; val < 256; val++){

			gaussian1[id][val] = (individ+id)->A1*std::exp(-((val-(individ+id)->miu1)*(val-(individ+id)->miu1))/(2*(individ+id)->sigma1*(individ+id)->sigma1));
			gaussian2[id][val] = (individ+id)->A2*std::exp(-((val-(individ+id)->miu2)*(val-(individ+id)->miu2))/(2*(individ+id)->sigma2*(individ+id)->sigma2));

		}
	}

	/*for(int val = 0; val < 256; val++)
		std::cout << gaussian1[1][val] << " " << gaussian2[1][val] << std::endl;*/
	/*for(int i = 0; i < populationSize; i++)
		std::cout << miu1[i] << " " << miu2[i] << std::endl;*/

	for(int val = 0; val < 256; val++)
		normalisedHistogram[val] = img->Hist[val]/(Height*Width); //normalise Histogram to 0-1

	//3 compute fitness
	  // delta = histogram - each gaussian

	for(int id = 0; id < populationSize; id++){
		for(int val = 0; val < 256; val++){
			(individ+id)->delta = (individ+id)->delta + std::abs(normalisedHistogram[val] - std::max(gaussian1[id][val],gaussian2[id][val]));
		}
	}

	//4 select best individuals
	  // with lowest delta

	std::sort(individ,individ+populationSize,MachineLearning::indCompare); //sort delta ascending

	for(int i = 0; i < populationSize; i++)
		std::cout << (individ+i)->delta << "  " << (individ+i)->miu1 << "  " << (individ+i)->miu2 << std::endl;

	//5 mutate/cross
		//modify mean or standard deviation

	// return to 2 or stop if 50 generations passed


	delete normalisedHistogram;
	delete individ;

	for (int i = 0; i < populationSize; i++)
		delete gaussian1[i];
	delete gaussian1;
	for (int i = 0; i < populationSize; i++)
		delete gaussian2[i];
	delete gaussian2;

	return 0;
}


int ImageProc::stitch(Image* img1,Image* img2){



	return 0;
}

//The function "crop" crops the input image 'img' and copies the result to 'croppedImg'
//requires as input the coordinates of the upper right corner and lower left corner of the crop square
void ImageProc::crop(Image* img, Image* croppedImg, ImageProc::Square cropRegion){
	
	uint16 Height = img->getHeight();
	uint16 Width = img->getWidth();
	t_2DPoint uLC = cropRegion.getUpperLeftCorner();
	t_2DPoint lRC = cropRegion.getLowerRightCorner();
	
	if((Height >= (lRC.x - uLC.x)) && (Width >= (lRC.y - uLC.y)) && (Height >= lRC.x) && (Width >= lRC.y)){
		for(uint16 h = uLC.x; (h <= Height) && (h < lRC.x); h++){
			for(uint16 w = uLC.y; (w <= Width) && (w < lRC.y); w++){
			
				croppedImg->imageData[h - uLC.x][w - uLC.y] = img->imageData[h][w];
				
			}
		}
	}
	
}