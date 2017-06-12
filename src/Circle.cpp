//
//  Circle.cpp
//  CirclePacking
//
//  Created by Callum Howard on 11/6/17.
//
//

#include "Circle.hpp"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace ch {

    using namespace ci;
    using namespace ci::app;

    void Circle::draw() const {
        gl::drawSolidCircle(center_, radius_);
    }

}
