
#include "Image.h"

const uint16_t c_uint16_endian_test = 1; //used by is_bigendian() macro

uint32_t ImageProc::Image::Image_count;

ImageProc::Image::Image() {

	this->grayLevel = 0;
	this->imgType = "Clean Matrix";

	this->Hist = new double[256]; //allocate memory for histogram vector
	for(int i = 0; i < 256; i++)
		this->Hist[i] = 0; //initialize vector with zeroes;

	this->Image_count += 1;

}

ImageProc::Image::Image(char const* fileName) {

	FILE *fp;
	fp = fopen(fileName, "rb");

	uint16_t img_marker = 0;
	uint32_t cursor_position = 0;

	const uint8_t image_buffer_length = 1; //bytes
	uint8_t* image_buffer = new uint8_t[image_buffer_length];

	if(NULL != fp){

			while((image_buffer_length == fread(image_buffer, sizeof(image_buffer[0]), image_buffer_length, fp))){

				img_marker = (img_marker << 8) + image_buffer[0];

				switch(img_marker){

					case SOI:
						printf("SOI\n");
				//		printf("SOI  = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;

					case SOF0:
						printf("SOF0\n");
				//		printf("SOF0 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						f_readSOF0(fp);
						break;

					case SOF1:
						printf("SOF1\n");
				//		printf("SOF0 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;

					case SOF2:
						printf("SOF2\n");
				//		printf("SOF2 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;

					case DHT:
						printf("DHT\n");
				//		printf("DHT  = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
				
						f_readDHT(fp);
						
						break;

					case DQT:
						printf("DQT\n");
				//		printf("DQT  = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
				
						f_readDQT(fp);
						
						break;

					case DRI:
						printf("DRI\n");
				//		printf("DRI  = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case SOS:
						printf("SOS\n");
				//		printf("SOS  = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
											
					case RST0:
						printf("RST0\n");
				//		printf("RST0 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case RST1:
						printf("RST1\n");
				//		printf("RST1 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case RST2:
						printf("RST2\n");
				//		printf("RST2 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case RST3:
						printf("RST3\n");
				//		printf("RST3 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
											
					case RST4:
						printf("RST4\n");
				//		printf("RST4 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case RST5:
						printf("RST5\n");
				//		printf("RST5 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case RST6:
						printf("RST6\n");
				//		printf("RST6 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case RST7:
						printf("RST7\n");
				//		printf("RST7 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
											
					case APP0:
						printf("APP0\n");
				//		printf("APP0 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);

						f_readAPP0(fp);

						break;

					case APP1:
						printf("APP1\n");
				//		printf("APP1 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP2:
						printf("APP2\n");
				//		printf("APP2 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP3:
						printf("APP3\n");
				//		printf("APP3 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP4:
						printf("APP4\n");
				//		printf("APP4 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP5:
						printf("APP5\n");
				//		printf("APP5 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP6:
						printf("APP6\n");
				//		printf("APP6 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP7:
						printf("APP7\n");
				//		printf("APP7 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP8:
						printf("APP8\n");
				//		printf("APP8 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP9:
						printf("APP9\n");
				//		printf("APP9 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP10:
						printf("APP10\n");
				//		printf("APP10 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP11:
						printf("APP11\n");
				//		printf("APP11 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP12:
						printf("APP12\n");
				//		printf("APP12 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP13:
						printf("APP13\n");
				//		printf("APP13 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP14:
						printf("APP14\n");
				//		printf("APP14 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;
					
					case APP15:
						printf("APP15\n");
				//		printf("APP15 = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;

					
					case COM:
						printf("COM\n");
				//		printf("COM  = %x\n",img_marker);
				//		cursor_position = ftell(fp);
				//		printf("Position = %x\n",cursor_position);
						break;

					case EOI:
						printf("EOI\n");
						printf("EOI  = %x\n",img_marker);
						cursor_position = ftell(fp);
						printf("Position = %x\n",cursor_position);
						break;

					default:
						break;
				}//end switch

			}//end While
		
		//allocate memory
	//this->imageData = new unsigned int*[this->Height];
	//for (unsigned int i = 0; i < this->Height; i++)
	//	this->imageData[i] = new unsigned int[this->Width];

		//for (unsigned int i = 0; i < this->Height; i++) {
	//	for (unsigned int j = 0; j < this->Width; j++) {
	//		fscanf_s(fp, "%c", &c);
	//		this->imageData[i][j] = c;
	//	}
	//}

		fclose(fp);

	}else{
		std::cout << "Path or file not found " << "\"" << fileName << "\"" << std::endl;
	}// end if(NULL != fp){


//	delete[] image_type;
	delete[] image_buffer;
}

ImageProc::Image::Image(unsigned int H,unsigned int W) {

	this->grayLevel = 0;
	this->Height = H;
	this->Width = W;
	this->imgType = "None";

	this->Hist = new double[256]; //allocate memory for histogram vector
	for(int i = 0; i < 256; i++)
		this->Hist[i] = 0; //initialize vector with zeroes;

	//allocate memory
	this->imageData = new unsigned int*[H];
	for (unsigned int i = 0; i < H; i++)
		this->imageData[i] = new unsigned int[W];

	for (unsigned int i = 0; i < H; i++) {
		for (unsigned int j = 0; j < H; j++) {
			this->imageData[i][j] = 0;
		}
	}

	this->Image_count += 1;

}


//void ImageProc::Image::readPGMHeader(FILE* fp){
//
//	char* type = new char[2];
//	this->imgType.clear();
//
//	if(fp != NULL){
//		fscanf_s(fp, "%c", &type[0]);
//		fscanf_s(fp, "%c", &type[1]);
//		this->imgType += type[0];
//		this->imgType += type[1];
//		fscanf_s(fp, "%d", &this->Width);
//		fscanf_s(fp, "%d", &this->Height);
//		fscanf_s(fp, "%d\n", &this->grayLevel);
//	}else{
//		std::cout << "File not open. Check path." << std::endl;
//		getchar();
//		exit(-1);
//	}
//
//	delete type;
//}

//int ImageProc::Image::readPGM(char* fileName) {
//
//	unsigned char c;
//	FILE* fp;
//	fopen_s(&fp, fileName, "r");
//
//	this->readPGMHeader(fp);
//
//	//allocate memory
//	this->imageData = new unsigned int*[this->Height];
//	for (unsigned int i = 0; i < this->Height; i++)
//		this->imageData[i] = new unsigned int[this->Width];
//
//	for (unsigned int i = 0; i < this->Height; i++) {
//		for (unsigned int j = 0; j < this->Width; j++) {
//			if(this->imgType[1] == '2') //P2 type
//				fscanf_s(fp, "%d", &this->imageData[i][j]);
//			else if(this->imgType[1] == '5'){ //else P5 type
//				fscanf_s(fp,"%c", &c); 
//				this->imageData[i][j] = c;
//			}else { std::cout << "PGM type not supported" << this->imgType << std::endl; }
//		}
//	}
//
//	fclose(fp);
//
//	return 0;
//}

//void ImageProc::Image::writePGMHeader(FILE* fp){
//
//	if(fp != NULL){
//		fprintf(fp, "%c", this->imgType[0]);
//		fprintf(fp, "%c\n", this->imgType[1]);
//		fprintf(fp, "%d ", this->Width);
//		fprintf(fp, "%d\n", this->Height);
//		fprintf(fp, "%d\n", this->grayLevel);
//	}else{
//		std::cout << "File failed to open" << std::endl;
//		getchar();
//		exit(-1);
//	}
//
//}


//int ImageProc::Image::writePGM(char* fileName) {
//
//	FILE *fp;
//	fopen_s(&fp, fileName, "w");
//
//	this->writePGMHeader(fp);
//
//	for (unsigned int i = 0; i < this->Height; i++) {
//		for (unsigned int j = 0; j < this->Width; j++) {
//			fprintf(fp, "%.3d ", (unsigned char)this->imageData[i][j]);
//		}
//		fprintf(fp,"\n");
//	}
//
//	fclose(fp);
//
//	return 0;
//}

ImageProc::Image::~Image() {

	if(this->Image_count > 0){
		
		for (unsigned int i = 0; i < this->Height; i++)
			delete[] this->imageData[i];
		delete[] this->imageData;
		
		for (unsigned int i = 0; i < this->Height; i++)
			delete[] this->Red[i];
		delete[] this->Red;
	
		for (unsigned int i = 0; i < this->Height; i++)
			delete[] this->Green[i];
		delete[] this->Green;
		
		for (unsigned int i = 0; i < this->Height; i++)
			delete[] this->Blue[i];
		delete[] this->Blue;

		delete[] this->Hist;
		
		this->Image_count -= 1;

	}

}

unsigned int ImageProc::Image::getHeight() {
	return this->Height;
}

unsigned int ImageProc::Image::setHeight(int H) {
	
	this->Height = H;

	return 0;
}


unsigned int ImageProc::Image::getWidth() {
	return this->Width;
}

unsigned int ImageProc::Image::setWidth(int W) {
	
	this->Width = W;

	return 0;
}

unsigned int ImageProc::Image::getgrayLevel() {
	return this->grayLevel;
}

std::string ImageProc::Image::getType() {
	return this->imgType;
}

unsigned int ImageProc::Image::setgrayLevel(int x){

	this->grayLevel = x;

	return 0;
}

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

	double rad = theta * ImageProc::pi / 180; //convert degrees to rad

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

		coef[distance + windowSize/2] = (std::exp(-(distance*distance)/pcoef))/(pi*pcoef);
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
		delete tempImage[H];
	delete tempImage;

	delete coef;

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
	double scoef = (std::sqrt(2*pi)*sigma);

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
	double scoef = (std::sqrt(2*pi)*sigma);

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

int ImageProc::unsharp_masking(Image* img,Image* img2){

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
		delete orgImg[H];
	}
	delete orgImg;

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

void ImageProc::Image::f_readAPP0(FILE* fp){

//	uint16_t img_marker = 0;
//	uint32_t cursor_position = 0;

	const uint8_t APP0_buffer_length = 1; //nr of bytes
	uint8_t* APP0_buffer = new uint8_t[APP0_buffer_length];

//	uint8_t* APP0_buffer_test = new uint8_t[20];

	if(NULL != fp){

		for(int i = 0; i < 2; i++){
			if((APP0_buffer_length == fread(APP0_buffer, sizeof(APP0_buffer[0]), APP0_buffer_length, fp))){

					this->struct_JPEG.struct_APP0.APP0_Length = (this->struct_JPEG.struct_APP0.APP0_Length << 8) + APP0_buffer[0];

			}//end if APP0_Length
		}//end for APP0_Length

		for(int i = 0; i < 5; i++){
			if((APP0_buffer_length == fread(APP0_buffer, sizeof(APP0_buffer[0]), APP0_buffer_length, fp))){

					this->struct_JPEG.struct_APP0.APP0_Identifier = (this->struct_JPEG.struct_APP0.APP0_Identifier << 8) + APP0_buffer[0];

			}//end if APP0_Identifier
		}//end for APP0_Identifier

		for(int i = 0; i < 2; i++){
			if((APP0_buffer_length == fread(APP0_buffer, sizeof(APP0_buffer[0]), APP0_buffer_length, fp))){

				this->struct_JPEG.struct_APP0.APP0_JFIF_Version = (this->struct_JPEG.struct_APP0.APP0_JFIF_Version << 8) + APP0_buffer[0];

			}//end if APP0_JFIF_Version
		}//end for APP0_JFIF_Version

		for(int i = 0; i < 1; i++){
			if((APP0_buffer_length == fread(APP0_buffer, sizeof(APP0_buffer[0]), APP0_buffer_length, fp))){

				this->struct_JPEG.struct_APP0.APP0_DensityUnits = APP0_buffer[0];

			}//end if APP0_DensityUnits
		}//end for APP0_DensityUnits

		for(int i = 0; i < 2; i++){
			if((APP0_buffer_length == fread(APP0_buffer, sizeof(APP0_buffer[0]), APP0_buffer_length, fp))){

				this->struct_JPEG.struct_APP0.APP0_Xdensity = (this->struct_JPEG.struct_APP0.APP0_Xdensity << 8) + APP0_buffer[0];

			}//end if APP0_Xdensity
		}//end for APP0_Xdensity

		for(int i = 0; i < 2; i++){
			if((APP0_buffer_length == fread(APP0_buffer, sizeof(APP0_buffer[0]), APP0_buffer_length, fp))){

				this->struct_JPEG.struct_APP0.APP0_Ydensity = (this->struct_JPEG.struct_APP0.APP0_Ydensity << 8) + APP0_buffer[0];

			}//end if APP0_Ydensity
		}//end for APP0_Ydensity

		for(int i = 0; i < 1; i++){
			if((APP0_buffer_length == fread(APP0_buffer, sizeof(APP0_buffer[0]), APP0_buffer_length, fp))){

				this->struct_JPEG.struct_APP0.APP0_Xthumbnail = (this->struct_JPEG.struct_APP0.APP0_Xthumbnail << 8) + APP0_buffer[0];

			}//end if APP0_Xthumbnail
		}//end for APP0_Xthumbnail

		for(int i = 0; i < 1; i++){
			if((APP0_buffer_length == fread(APP0_buffer, sizeof(APP0_buffer[0]), APP0_buffer_length, fp))){

				this->struct_JPEG.struct_APP0.APP0_Ythumbnail = (this->struct_JPEG.struct_APP0.APP0_Ythumbnail << 8) + APP0_buffer[0];

			}//end if APP0_Ythumbnail
		}//end for APP0_Ythumbnail

//		printf("APP0_Length = %d\n", this->struct_JPEG.struct_APP0.APP0_Length);
//		printf("APP0_Identifier = %x\n", this->struct_JPEG.struct_APP0.APP0_Identifier);
//		printf("APP0_JFIF_Version = %x\n", this->struct_JPEG.struct_APP0.APP0_JFIF_Version);
//		printf("APP0_DensityUnits = %d\n", this->struct_JPEG.struct_APP0.APP0_DensityUnits);
//		printf("APP0_Xdensity = %d\n", this->struct_JPEG.struct_APP0.APP0_Xdensity);
//		printf("APP0_Ydensity = %d\n", this->struct_JPEG.struct_APP0.APP0_Ydensity);
//		printf("APP0_Xthumbnail = %d\n", this->struct_JPEG.struct_APP0.APP0_Xthumbnail);
//		printf("APP0_Ythumbnail = %d\n", this->struct_JPEG.struct_APP0.APP0_Ythumbnail);
//		cursor_position = ftell(fp);
//		printf("Position = %d\n",cursor_position);
	}

}

void ImageProc::Image::f_readSOF0(FILE* fp){

//	uint16_t img_marker = 0;
//	uint32_t cursor_position = 0;

	const uint8_t SOF0_buffer_length = 1; //nr of bytes
	uint8_t* SOF0_buffer = new uint8_t[SOF0_buffer_length];

//	uint8_t* APP0_buffer_test = new uint8_t[20];

	if(NULL != fp){

		for(int i = 0; i < 2; i++){
			if((SOF0_buffer_length == fread(SOF0_buffer, sizeof(SOF0_buffer[0]), SOF0_buffer_length, fp))){

					this->struct_JPEG.struct_SOF0.SOF0_Length = (this->struct_JPEG.struct_SOF0.SOF0_Length << 8) + SOF0_buffer[0];

			}//end if SOF0_Length
		}//end for SOF0_Length
		
		for(int i = 0; i < 1; i++){
			if((SOF0_buffer_length == fread(SOF0_buffer, sizeof(SOF0_buffer[0]), SOF0_buffer_length, fp))){

					this->struct_JPEG.struct_SOF0.SOF0_DataPrecision = (this->struct_JPEG.struct_SOF0.SOF0_DataPrecision << 8) + SOF0_buffer[0];

			}//end if SOF0_DataPrecision
		}//end for SOF0_DataPrecision
		
		for(int i = 0; i < 2; i++){
			if((SOF0_buffer_length == fread(SOF0_buffer, sizeof(SOF0_buffer[0]), SOF0_buffer_length, fp))){

					this->struct_JPEG.struct_SOF0.SOF0_ImageHeight = (this->struct_JPEG.struct_SOF0.SOF0_ImageHeight << 8) + SOF0_buffer[0];

			}//end if SOF0_ImageHeight
		}//end for SOF0_ImageHeight
		
		for(int i = 0; i < 2; i++){
			if((SOF0_buffer_length == fread(SOF0_buffer, sizeof(SOF0_buffer[0]), SOF0_buffer_length, fp))){

					this->struct_JPEG.struct_SOF0.SOF0_ImageWidth = (this->struct_JPEG.struct_SOF0.SOF0_ImageWidth << 8) + SOF0_buffer[0];

			}//end if SOF0_ImageWidth
		}//end for SOF0_ImageWidth
		
		for(int i = 0; i < 1; i++){
			if((SOF0_buffer_length == fread(SOF0_buffer, sizeof(SOF0_buffer[0]), SOF0_buffer_length, fp))){

					this->struct_JPEG.struct_SOF0.SOF0_NumberOfComponents = (this->struct_JPEG.struct_SOF0.SOF0_NumberOfComponents << 8) + SOF0_buffer[0];

			}//end if SOF0_NumberOfComponents
		}//end for SOF0_NumberOfComponents
		
		this->struct_JPEG.struct_SOF0.SOF0_Component = new t_SOF0_Component[this->struct_JPEG.struct_SOF0.SOF0_NumberOfComponents];
		
		for(int j = 0; j < this->struct_JPEG.struct_SOF0.SOF0_NumberOfComponents; j++){
			
			for(int i = 0; i < 1; i++){
				if((SOF0_buffer_length == fread(SOF0_buffer, sizeof(SOF0_buffer[0]), SOF0_buffer_length, fp))){

						this->struct_JPEG.struct_SOF0.SOF0_Component[j].SOF0_Component_ID = (this->struct_JPEG.struct_SOF0.SOF0_Component[j].SOF0_Component_ID << 8) + SOF0_buffer[0];

				}//end if SOF0_Component_ID
			}//end for SOF0_Component_ID
			
			for(int i = 0; i < 1; i++){
				if((SOF0_buffer_length == fread(SOF0_buffer, sizeof(SOF0_buffer[0]), SOF0_buffer_length, fp))){

						this->struct_JPEG.struct_SOF0.SOF0_Component[j].SOF0_Component_Sampling = (this->struct_JPEG.struct_SOF0.SOF0_Component[j].SOF0_Component_Sampling << 8) + SOF0_buffer[0];

				}//end if SOF0_Component_Sampling
			}//end for SOF0_Component_Sampling
			
			for(int i = 0; i < 1; i++){
				if((SOF0_buffer_length == fread(SOF0_buffer, sizeof(SOF0_buffer[0]), SOF0_buffer_length, fp))){

						this->struct_JPEG.struct_SOF0.SOF0_Component[j].SOF0_Component_DQTNumber = (this->struct_JPEG.struct_SOF0.SOF0_Component[j].SOF0_Component_DQTNumber << 8) + SOF0_buffer[0];

				}//end if SOF0_Component_DQTNumber
			}//end for SOF0_Component_DQTNumber
			
		}
		

		// printf("SOF0_Length = %d\n", this->struct_JPEG.struct_SOF0.SOF0_Length);
		// printf("SOF0_DataPrecision = %d\n", this->struct_JPEG.struct_SOF0.SOF0_DataPrecision);
		// printf("SOF0_ImageHeight = %d\n", this->struct_JPEG.struct_SOF0.SOF0_ImageHeight);
		// printf("SOF0_ImageWidth = %d\n", this->struct_JPEG.struct_SOF0.SOF0_ImageWidth);
		// printf("SOF0_NumberOfComponents = %d\n", this->struct_JPEG.struct_SOF0.SOF0_NumberOfComponents);
		// printf("SOF0_Component_ID = %d\n", this->struct_JPEG.struct_SOF0.SOF0_Component[0].SOF0_Component_ID);
		// printf("SOF0_Component_Sampling = %d\n", this->struct_JPEG.struct_SOF0.SOF0_Component[0].SOF0_Component_Sampling);
		// printf("SOF0_Component_DQTNumber = %d\n", this->struct_JPEG.struct_SOF0.SOF0_Component[0].SOF0_Component_DQTNumber);
		// printf("SOF0_Component_ID = %d\n", this->struct_JPEG.struct_SOF0.SOF0_Component[1].SOF0_Component_ID);
		// printf("SOF0_Component_Sampling = %d\n", this->struct_JPEG.struct_SOF0.SOF0_Component[1].SOF0_Component_Sampling);
		// printf("SOF0_Component_DQTNumber = %d\n", this->struct_JPEG.struct_SOF0.SOF0_Component[1].SOF0_Component_DQTNumber);
		// printf("SOF0_Component_ID = %d\n", this->struct_JPEG.struct_SOF0.SOF0_Component[2].SOF0_Component_ID);
		// printf("SOF0_Component_Sampling = %d\n", this->struct_JPEG.struct_SOF0.SOF0_Component[2].SOF0_Component_Sampling);
		// printf("SOF0_Component_DQTNumber = %d\n", this->struct_JPEG.struct_SOF0.SOF0_Component[2].SOF0_Component_DQTNumber);
		
//		cursor_position = ftell(fp);
//		printf("Position = %d\n",cursor_position);
	}

}

void ImageProc::Image::f_readDQT(FILE* fp){


	const uint8_t DQT_buffer_length = 1; //nr of bytes
	uint8_t* DQT_buffer = new uint8_t[DQT_buffer_length];


	if(NULL != fp){

		for(int i = 0; i < 2; i++){
			if((DQT_buffer_length == fread(DQT_buffer, sizeof(DQT_buffer[0]), DQT_buffer_length, fp))){

					this->struct_JPEG.struct_DQT.DQT_Length = (this->struct_JPEG.struct_DQT.DQT_Length << 8) + DQT_buffer[0];

			}//end if DQT_Length
		}//end for DQT_Length
		
		for(int i = 0; i < 1; i++){
			if((DQT_buffer_length == fread(DQT_buffer, sizeof(DQT_buffer[0]), DQT_buffer_length, fp))){

					this->struct_JPEG.struct_DQT.DQT_TableInformation = (this->struct_JPEG.struct_DQT.DQT_TableInformation << 8) + DQT_buffer[0];

			}//end if DQT_TableInformation
		}//end for DQT_TableInformation
		
		this->struct_JPEG.struct_DQT.DQT_QTID = this->struct_JPEG.struct_DQT.DQT_TableInformation & 0x0F;
		this->struct_JPEG.struct_DQT.DQT_PrecisionOfQT = this->struct_JPEG.struct_DQT.DQT_TableInformation & 0xF0;
		
		this->struct_JPEG.struct_DQT.DQT_TableElement = new uint8_t[64 * (this->struct_JPEG.struct_DQT.DQT_PrecisionOfQT + 1)];

		
		for(int j = 0; j < 64 * (this->struct_JPEG.struct_DQT.DQT_PrecisionOfQT + 1); j++){
			
			for(int i = 0; i < 1; i++){
				if((DQT_buffer_length == fread(DQT_buffer, sizeof(DQT_buffer[0]), DQT_buffer_length, fp))){
	
						this->struct_JPEG.struct_DQT.DQT_TableElement[j] = (this->struct_JPEG.struct_DQT.DQT_TableElement[j] << 8) + DQT_buffer[0];
						// printf("DQT_TableElement[%d] = %d\n", j, this->struct_JPEG.struct_DQT.DQT_TableElement[j]);
	
				}//end if DQT_Component_ID
			}//end for DQT_Component_ID
		
		}
		// printf("DQT_Length = %lu\n", this->struct_JPEG.struct_DQT.DQT_Length);
		// printf("DQT_TableInformation = %lu\n", this->struct_JPEG.struct_DQT.DQT_TableInformation);
		// printf("DQT_QTID = %lu\n", this->struct_JPEG.struct_DQT.DQT_QTID);
		// printf("DQT_PrecisionOfQT = %lu\n", this->struct_JPEG.struct_DQT.DQT_PrecisionOfQT);
	
	}

}

void ImageProc::Image::f_readDHT(FILE* fp){


	const uint8_t DHT_buffer_length = 1; //nr of bytes
	uint8_t* DHT_buffer = new uint8_t[DHT_buffer_length];

	if(NULL != fp){

		for(int i = 0; i < 2; i++){
			if((DHT_buffer_length == fread(DHT_buffer, sizeof(DHT_buffer[0]), DHT_buffer_length, fp))){

					this->struct_JPEG.struct_DHT.DHT_Length = (this->struct_JPEG.struct_DHT.DHT_Length << 8) + DHT_buffer[0];

			}//end if DHT_Length
		}//end for DHT_Length
		
		for(int i = 0; i < 1; i++){
			if((DHT_buffer_length == fread(DHT_buffer, sizeof(DHT_buffer[0]), DHT_buffer_length, fp))){

					this->struct_JPEG.struct_DHT.DHT_TableInformation = (this->struct_JPEG.struct_DHT.DHT_TableInformation << 8) + DHT_buffer[0];

			}//end if DHT_TableInformation
		}//end for DHT_TableInformation
		
		this->struct_JPEG.struct_DHT.DHT_NumberOfElements = new uint8_t[16];
		
		for(int j = 0; j < 16; j++){
			
			for(int i = 0; i < 1; i++){
				if((DHT_buffer_length == fread(DHT_buffer, sizeof(DHT_buffer[0]), DHT_buffer_length, fp))){

					this->struct_JPEG.struct_DHT.DHT_NumberOfElements[j] = (this->struct_JPEG.struct_DHT.DHT_NumberOfElements[j] << 8) + DHT_buffer[0];
					
					printf("DHT_NumberOfElements[%d] = %d\n", j, this->struct_JPEG.struct_DHT.DHT_NumberOfElements[j]);
					
				}//end if DHT_NumberOfElements
			}//end for DHT_NumberOfElements
		
			
		}
		
		 printf("DHT_Length = %lu\n", this->struct_JPEG.struct_DHT.DHT_Length);
	
	}

}

//
//
//
//
//
//
//
//
//
//CIMG INTERFACE

int ImageProc::CIMGInterface::readImage(ImageProc::Image* img, char const* imgPath){

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

cimg_library::CImg<unsigned char> ImageProc::CIMGInterface::displayImageColor(ImageProc::Image* img){

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

cimg_library::CImg<unsigned char> ImageProc::CIMGInterface::displayImageGray(ImageProc::Image* img){

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

cimg_library::CImg<unsigned char> ImageProc::CIMGInterface::displayHist(ImageProc::Image* img){

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



//
//
//
//
//
//Machine Learning

bool ImageProc::MachineLearning::indCompare(MachineLearning::twogauss lhs, MachineLearning::twogauss rhs) { return lhs.delta < rhs.delta; }