//
//  utilities.hpp
//  CirclePacking
//
//  Created by Callum Howard on 11/6/17.
//
//

#ifndef utilities_hpp
#define utilities_hpp

#include "cinder/gl/gl.h"

namespace ch {
    
    template<typename T>
    inline bool between(T a, T lower, T upper) { return a >= lower and a <= upper; }

}

#endif /* utilities_hpp */
