#include "Image.h"

const uint16_t c_uint16_endian_test = 1; //used by is_bigendian() macro

uint32_t ImageProc::Image::Image_count;

ImageProc::Image::Image() {

	this->grayLevel = 0;
	this->imgType = "Clean Matrix";

	this->Hist = new double[256]; //allocate memory for histogram vector
	for(int i = 0; i < 256; i++)
		this->Hist[i] = 0; //initialize vector with zeroes;
	normHist = new double[256]; //allocate memory for histogram vector
	for(int i = 0; i < 256; i++) //8 bit depth gray scale image
		normHist[i] = 0; //initialize vector with zeroes;
		
	setgrayLevel(0); // initialize graylevel to 0

	this->Image_count += 1;

}

ImageProc::Image::Image(char const* imgPath) {

	//read into Image object
	
	this->imgType = "Read from file";

	double R = 0.2126;
	double G = 0.7152;
	double B = 0.0722;

	cimg_library::CImg<unsigned char> image(imgPath);

	setHeight(image.height());
	setWidth(image.width());
	int imHeight = getHeight();
	int imWidth = getWidth();

	//allocate memory
	imageData = new unsigned int*[imHeight];
	for (int H = 0; H < imHeight; H++)
		imageData[H] = new unsigned int[imWidth];

	Red = new unsigned int*[imHeight];
	for (int i = 0; i < imHeight; i++)
		Red[i] = new unsigned int[imWidth];

	Green = new unsigned int*[imHeight];
	for (int i = 0; i < imHeight; i++)
		Green[i] = new unsigned int[imWidth];

	Blue = new unsigned int*[imHeight];
	for (int i = 0; i < imHeight; i++)
		Blue[i] = new unsigned int[imWidth];

	for (int H = 0; H < imHeight; H++) {
		for (int W = 0; W < imWidth; W++) {

			Red[H][W] = image(W,H,0,0);
			Green[H][W] = image(W,H,0,1);
			Blue[H][W] = image(W,H,0,2);
			imageData[H][W] = (unsigned int)(R*image(W,H,0,0) + G*image(W,H,0,1) + B*image(W,H,0,2));

		}
	}

	unsigned int temp = 0;
	setgrayLevel(temp); // initialize graylevel to 0
	for(unsigned int H = 0; H < getHeight(); H++){
		for(unsigned int W = 0; W < getWidth(); W++){

			if(imageData[H][W] > temp){
				temp = imageData[H][W];
				setgrayLevel(temp); //set new graylevel

			}
		}
	}
	
	this->Hist = new double[256]; //allocate memory for histogram vector
	this->normHist = new double[256]; //allocate memory for histogram vector
	
	for(int i = 0; i < 256; i++) //8 bit depth gray scale image
		Hist[i] = 0; //initialize vector with zeroes;
	
	for(int i = 0; i < 256; i++) //8 bit depth gray scale image
		normHist[i] = 0; //initialize vector with zeroes;
		
	Image_count += 1;

}


//JPEG decoder constructor - the uint8 x parameter serves no purpose other than to differentiate between the other constructor - to be modified in the future
ImageProc::Image::Image(char const* fileName,uint8 x) {

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

	setHeight(H);
	setWidth(W);
	this->imgType = "None";

	Hist = new double[256]; //allocate memory for histogram vector
	for(int i = 0; i < 256; i++)
		Hist[i] = 0; //initialize vector with zeroes;
		
	normHist = new double[256]; //allocate memory for histogram vector
	for(int i = 0; i < 256; i++) //8 bit depth gray scale image
		normHist[i] = 0; //initialize vector with zeroes;

	//allocate memory
	imageData = new unsigned int*[H];
	for (unsigned int i = 0; i < H; i++)
		imageData[i] = new unsigned int[W];
	Red = new unsigned int*[H];
	for (int i = 0; i < H; i++)
		Red[i] = new unsigned int[W];

	Green = new unsigned int*[H];
	for (int i = 0; i < H; i++)
		Green[i] = new unsigned int[W];

	Blue = new unsigned int*[H];
	for (int i = 0; i < H; i++)
		Blue[i] = new unsigned int[W];
		
	setgrayLevel(0); // initialize graylevel to 0

	//initialise with 0
	for (unsigned int i = 0; i < H; i++) {
		for (unsigned int j = 0; j < W; j++) {
			imageData[i][j] = 0;
			Red[i][j] = 0;
			Green[i][j] = 0;
			Blue[i][j] = 0;
		}
	}
	
	Image_count += 1;

}

//assignment operator for Image objects
void ImageProc::Image::operator=(const ImageProc::Image& img){

	if (this != &img) { // self-assignment check expected
		uint32_t H = img.getHeight();
		uint32_t W = img.getWidth();
		
		this->Hist = new double[256]; //allocate memory for histogram vector

		this->normHist = new double[256]; //allocate memory for histogram vector
			
		//allocate memory
		this->imageData = new unsigned int*[H];
		for (unsigned int i = 0; i < H; i++)
			this->imageData[i] = new unsigned int[W];
		this->Red = new unsigned int*[H];
		for (int i = 0; i < H; i++)
			this->Red[i] = new unsigned int[W];

		this->Green = new unsigned int*[H];
		for (int i = 0; i < H; i++)
			this->Green[i] = new unsigned int[W];

		this->Blue = new unsigned int*[H];
		for (int i = 0; i < H; i++)
			this->Blue[i] = new unsigned int[W];
	
		this->Image_count += 1;

		this->setHeight(H);
		this->setWidth(W);
		this->setgrayLevel(img.getgrayLevel());
		
		//get values
		for(unsigned int i = 0; i < H; i++){
			for(unsigned int j = 0; j < W; j++){

				this->imageData[i][j] = img.imageData[i][j];
				this->Red[i][j] = img.Red[i][j];
				this->Green[i][j] = img.Green[i][j];
				this->Blue[i][j] = img.Blue[i][j];
		
			}
		}
		
		for(int i = 0; i < 256; i++){
			this->Hist[i] = img.Hist[i];
			this->normHist[i] = img.normHist[i];
		}	
	}
	
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
		delete[] this->normHist;
		
		this->Image_count -= 1;

	}

}

unsigned int ImageProc::Image::getHeight() const{
	return this->Height;
}

unsigned int ImageProc::Image::setHeight(int H) {
	
	this->Height = H;

	return 0;
}


unsigned int ImageProc::Image::getWidth() const{
	return this->Width;
}

unsigned int ImageProc::Image::setWidth(int W) {
	
	this->Width = W;

	return 0;
}

unsigned int ImageProc::Image::getgrayLevel() const{
	return this->grayLevel;
}

std::string ImageProc::Image::getType() const{
	return this->imgType;
}

unsigned int ImageProc::Image::setgrayLevel(int x){

	this->grayLevel = x;

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
		this->struct_JPEG.struct_DQT.DQT_PrecisionOfQT = (this->struct_JPEG.struct_DQT.DQT_TableInformation & 0xF0) >> 4;
		
		this->struct_JPEG.struct_DQT.DQT_TableElement = new uint8_t[64 * (this->struct_JPEG.struct_DQT.DQT_PrecisionOfQT + 1)];

		
		for(int j = 0; j < 64 * (this->struct_JPEG.struct_DQT.DQT_PrecisionOfQT + 1); j++){
			
			for(int i = 0; i < 1; i++){
				if((DQT_buffer_length == fread(DQT_buffer, sizeof(DQT_buffer[0]), DQT_buffer_length, fp))){
	
						this->struct_JPEG.struct_DQT.DQT_TableElement[j] = (this->struct_JPEG.struct_DQT.DQT_TableElement[j] << 8) + DQT_buffer[0];
//						 printf("DQT_TableElement[%d] = %d\n", j, this->struct_JPEG.struct_DQT.DQT_TableElement[j]);
	
				}//end if DQT_Component_ID
			}//end for DQT_Component_ID
		
		}
//		 printf("DQT_Length = %lu\n", this->struct_JPEG.struct_DQT.DQT_Length);
//		 printf("DQT_TableInformation = %lu\n", this->struct_JPEG.struct_DQT.DQT_TableInformation);
//		 printf("DQT_QTID = %lu\n", this->struct_JPEG.struct_DQT.DQT_QTID);
//		 printf("DQT_PrecisionOfQT = %lu\n", this->struct_JPEG.struct_DQT.DQT_PrecisionOfQT);
	
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
		
		this->struct_JPEG.struct_DHT.DHT_HuffmanTableID = this->struct_JPEG.struct_DHT.DHT_TableInformation & 0x0F;
		this->struct_JPEG.struct_DHT.DHT_TableClass = (this->struct_JPEG.struct_DHT.DHT_TableInformation & 0xF0) >> 4;
		
		for(int j = 0; j < 16; j++){
			
			for(int i = 0; i < 1; i++){
				if((DHT_buffer_length == fread(DHT_buffer, sizeof(DHT_buffer[0]), DHT_buffer_length, fp))){

					this->struct_JPEG.struct_DHT.DHT_NumberOfCodes[j] = (this->struct_JPEG.struct_DHT.DHT_NumberOfCodes[j] << 8) + DHT_buffer[0];
					
					printf("DHT_NumberOfCodes[%d] = %d\n", j+1, this->struct_JPEG.struct_DHT.DHT_NumberOfCodes[j]);
					
				}//end if DHT_NumberOfCodes
			}//end for DHT_NumberOfCodes
		
			
		}
		
		for (uint8_t x = 0; x < 16; x++){
			this->struct_JPEG.struct_DHT.DHT_TableElement[x] = new uint8_t[this->struct_JPEG.struct_DHT.DHT_NumberOfCodes[x]];
		}
		
		for(int j = 0; j < 16; j++){
		
			for(int z = 0; z < this->struct_JPEG.struct_DHT.DHT_NumberOfCodes[j]; z++){
			
				for(int i = 0; i < 1; i++){
					if((DHT_buffer_length == fread(DHT_buffer, sizeof(DHT_buffer[0]), DHT_buffer_length, fp))){

					this->struct_JPEG.struct_DHT.DHT_TableElement[j][z] = (this->struct_JPEG.struct_DHT.DHT_TableElement[j][z] << 8) + DHT_buffer[0];
				
					printf("DHT_TableElement[%d][%d] = %d\n", j+1, z, this->struct_JPEG.struct_DHT.DHT_TableElement[j][z]);
				
					}//end if DHT_NumberOfElements
				}//end for DHT_NumberOfElements
			}//end for DHT_NumberOfElements
			
			
		}	
		
		
		 printf("DHT_Length = %d\n", this->struct_JPEG.struct_DHT.DHT_Length);
		 printf("DHT_TableClass = %d\n", this->struct_JPEG.struct_DHT.DHT_TableClass);
		 printf("DHT_HuffmanTableID = %d\n", this->struct_JPEG.struct_DHT.DHT_HuffmanTableID);
	
	}

}

//Square
ImageProc::Square::Square(){
	
	this->upperLeftCorner.x = 0;
	this->upperLeftCorner.y = 0;
	this->lowerRightCorner.x = 0;
	this->lowerRightCorner.y = 0;
	
	//insert warning message
}

ImageProc::Square::Square(t_2DPoint* uLCorner, t_2DPoint* lRCorner){
	
	if((uLCorner->x <= lRCorner->x) && (uLCorner->y <= lRCorner->y)){
	
		this->upperLeftCorner.x = uLCorner->x;
		this->upperLeftCorner.y = uLCorner->y;
		this->lowerRightCorner.x = lRCorner->x;
		this->lowerRightCorner.y = lRCorner->y;
		
	}else{
		
		this->upperLeftCorner.x = 0;
		this->upperLeftCorner.y = 0;
		this->lowerRightCorner.x = 0;
		this->lowerRightCorner.y = 0;
		//insert warning message
			
	}
}

t_2DPoint ImageProc::Square::getUpperLeftCorner(){
	
	return this->upperLeftCorner;
	
}

t_2DPoint ImageProc::Square::getLowerRightCorner(){
	
	return this->lowerRightCorner;
	
}

void ImageProc::Square::setUpperLeftCorner(t_2DPoint* corner){
	
	this->upperLeftCorner.x = corner->x;
	this->upperLeftCorner.y = corner->y;
	
}

void ImageProc::Square::setLowerRightCorner(t_2DPoint* corner){
	
	this->lowerRightCorner.x = corner->x;
	this->lowerRightCorner.y = corner->y;
	
}

ImageProc::Square::~Square(){
	
	//insert warning message
}


//
//
//
//
//
//Machine Learning

bool MachineLearning::indCompare(MachineLearning::twogauss lhs, MachineLearning::twogauss rhs) { return lhs.delta < rhs.delta; }
