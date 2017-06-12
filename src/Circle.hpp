//
//  Circle.hpp
//  CirclePacking
//
//  Created by Callum Howard on 11/6/17.
//
//

#ifndef Circle_hpp
#define Circle_hpp

namespace ch {

    using namespace ci;
    using namespace ci::app;

    class Circle {
    public:
        Circle(float radius, const vec2 &center) : radius_{radius}, center_{center} {}

        void draw() const;

        void setRadius(float radius) { radius_ = radius; }
        void setCenter(vec2 center) { center_ = center; }

        inline bool within(const Area& a) const { return a.contains(center_); }

    private:
        float radius_;
        vec2 center_;
    };
}

#endif /* Circle_hpp */
