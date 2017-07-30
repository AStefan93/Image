//include guard
#ifndef IMAGE_MATH_H
#define IMAGE_MATH_H

//Math header for Image
#include "Image_math_types.h"
#include <math.h> //basic math functions

namespace Math {
    
    uint8 uint8_maxValue(uint8* , uint8 );
    uint8 uint8_minValue(uint8* , uint8 );
    //calculates the absolute frequency of all the individual symbols in the array
    //returns an array of the same size with the frequency for each symbol - the index of the returned array is the symbol
    uint32* p_uint32_absFreq(uint8* ,uint32*, uint8 );

}

//end include guard
#endif //IMAGE_MATH_H