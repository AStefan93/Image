//Math functions for Image
#include "Image_math.h"

#define issigned(t) (((t)(-1)) < ((t) 0))

#define umaxof(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | (0xFULL << ((sizeof(t) * 8ULL) - 4ULL)))

#define smaxof(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | (0x7ULL << ((sizeof(t) * 8ULL) - 4ULL)))

#define maxof(t) ((unsigned long long) (issigned(t) ? smaxof(t) : umaxof(t)))


//returns the maximum value of an array
uint8 Math::uint8_maxValue(uint8* array, uint8 arraySize){
    uint8 max_value = 0;
    
    for(uint8 i = 0; i < arraySize; i++){
        
        if(array[i] > max_value){
            max_value = array[i];
        }
        
    }
    
    return max_value;
}

//returns the minimum value of an array
uint8 Math::uint8_minValue(uint8* array, uint8 arraySize){
    uint8 min_value = maxof(uint8);
    
    for(uint8 i = 0; i < arraySize; i++){
        
        if(array[i] < min_value){
            min_value = array[i];
        }
        
    }
    
    return min_value;
}


//calculate absolute frequency
uint32* Math::p_uint32_absFreq(uint8* symbol_array, uint32* abs_freq_array, uint8 array_size){
    
    //initialise abs_freq array
    for(uint8 i = 0; i < array_size; i++){
        abs_freq_array[i] = 0;
    }
    
    //calculate symbol frequency
    for (uint8 i = 0; i < array_size; i++){
        abs_freq_array[symbol_array[i]] = abs_freq_array[symbol_array[i]] + 1;
    }
    
    return abs_freq_array;
}   

//calculate relative frequency
//the totalNumber should be the length/array_size of the symbol_array in the function p_uint32_absFreq
uint32* Math::p_uint32_relFreq(uint8* abs_freq_array, uint32* symbolP_array, uint8 symbolP_array_size, uint32 totalNumber){
    
    //initialise abs_freq array
    for(uint8 i = 0; i < symbolP_array_size; i++){
        symbolP_array[i] = 0;
    }
    
    //calculate symbol frequency
    for (uint8 i = 0; i < symbolP_array_size; i++){
        symbolP_array[i] = abs_freq_array[i]/totalNumber;
    }
    
    return symbolP_array;
}
//generates the huffman dictionary
//the 3rd parameter represents the length of the symbol_array
//the 2nd parameter is the output of the function, the dictionary
void Math::v_genHuffmanDict(uint8* symbol_array, uint8* huffmanDict, uint8 array_size){
    
   // p_uint32_absFreq(symbol_array, abs_freq_array, array_size);
    //p_uint32_relFreq(abs_freq_array, symbolP_array, symbolP_array_size, totalNumber);
    
    //map symbols with relative frequencies
    
    //order symbols ascending by frequency
    
    //generate huffman tree
    
    //generate huffman dictionary based on tree
    
}

//function to calculate the cumulative sum of a normalised histogram vector of length 256 split between two classes by 1 threshold
//chapter 10.3, eq 10.3-4
void Math::v_cumulativeSums1Thresh(double* v,uint8_t k,double& P1, double& P2){
	
	P1 = 0;
	P2 = 0;
	for(int i = 0; i < k; i ++){
		P1 += v[i];
	}
	P2 = 1 - P1;
	
}

//v_cumulativeMeans calculates the average intensity of a "class" using an image's normalized histogram split between two classes by 1 threshold
void Math::v_cumMean(double* v, uint8_t k, double& cumMean_C1){

	cumMean_C1 = 0;
	for(int i = 0; i < k; i++){
		cumMean_C1 += i*v[i]; //sum(i*p(i)), where i is the intensity of a pixel and p(i) is it's probability
	}

}

//v_meanIntensity calculates the global mean of an image
//eq 10.3-9
void Math::v_meanIntensity(double* v, double& globalMean){

	globalMean = 0;
	for(int i = 0; i < 256; i++){
		globalMean += i*v[i]; //the global intensity mean of the image
	}

}

//v_variance calculates the intensity variance of all the pixels in the image
//chapter 10.3, equation 10.3-13 in Digital Image Processing Third Edition
void Math::v_varianceGlobal(double* v, double globalMean, double& variance){
	
	variance = 0;
	
	for(int i = 0; i < 256; i++){
		variance += (i - globalMean)*(i - globalMean) * v[i];
	}
	
}

//function calculates the between class variance
//chapter 10.3 equation 10.3-15 in Digital Image Processing Third Edition
void Math::v_betweenClassVariance(double P1, double P2, double cumMean_C1, double globalMean, double& varianceB){

	varianceB = 0;
	if((P1 != 0) && (P2 != 0)){//avoid division by zero
		varianceB = ((globalMean*P1 - cumMean_C1)*(globalMean*P1 - cumMean_C1))/(P1*P2);
	}
}
