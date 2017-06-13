#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "cinder/Log.h"
#include "cinder/Rand.h"
#include "Circle.hpp"
#include "utilities.hpp"

using namespace ci;
using namespace ci::app;

class CirclePackingApp : public App {
public:
    void setup() override;
    void mouseDown(MouseEvent event) override;
    void mouseDrag(MouseEvent event) override;
    void mouseWheel(MouseEvent event) override;
    void keyDown(KeyEvent event) override;
    void update() override;
    void draw() override;

private:
    inline void zoomAdd(float amount) {
        zoom_ = constrain(zoom_ + amount, zoomMin_, zoomMax_);
    };

    std::vector<ch::Circle> circles_;
    params::InterfaceGl params_;
    float circleRadius_;
    vec2 lastPos_;
    vec2 offset_;
    float zoom_;
    float zoomMax_;
    float zoomMin_;
    float zoomAmount_;
};

void CirclePackingApp::setup() {
    circleRadius_ = 5.0;

    zoom_ = 1.0;
    zoomMax_ = 5.0;
    zoomMin_ = 1.0;
    zoomAmount_ = 0.5;
    offset_ = vec2{};

    // set random seed
    auto r = Rand(1337);

    const auto windowCaption = "Parameters";
    params_ = params::InterfaceGl(windowCaption, ivec2{100, 200});
    params_.addParam("circle radius", &circleRadius_, "min=0.0 max=50.0 step=5");

    for (size_t i = 0; i < 20; ++i) {
        circles_.emplace_back(circleRadius_, vec2{
            r.randFloat(0, getWindowWidth()),
            r.randFloat(0, getWindowHeight())});
    }
}

void CirclePackingApp::mouseDown(MouseEvent event) {
    lastPos_ = event.getPos();
}

void CirclePackingApp::mouseDrag(MouseEvent event) {
    const vec2 pos = event.getPos();
    offset_ += (lastPos_ - pos) / zoom_;
    lastPos_ = pos;
}

void CirclePackingApp::mouseWheel(MouseEvent event) {
    zoomAdd(event.getWheelIncrement());
}

void CirclePackingApp::keyDown(KeyEvent event) {
    switch (event.getCode()) {
        case KeyEvent::KEY_UP:      break;
        case KeyEvent::KEY_DOWN:    break;
        default: CI_LOG_I(getWindowBounds()); break;
    }
}

void CirclePackingApp::update() { }

void CirclePackingApp::draw() {
    gl::clear(Color{0, 0, 0});
    gl::pushModelMatrix();

    // move origin to the center of the window for zooming
    gl::translate(+getWindowCenter());
    gl::scale(zoom_, zoom_);
    gl::translate(-getWindowCenter());

    // apply translational offset
    gl::translate(-offset_);

    gl::drawStrokedCircle(getWindowCenter(), 1);
    gl::drawStrokedCircle(getWindowCenter() + (offset_), 3);
    gl::drawStrokedCircle(getWindowCenter() + (offset_ / zoom_), 5);

    for (auto& circle : circles_) {
        circle.setRadius(circleRadius_);
        circle.draw();
    }

    gl::popModelMatrix();
    //params_.draw();
}

CINDER_APP( CirclePackingApp, RendererGl )
