//
//  ofxPingPongFbo.h
//
//  Created by 2bit on 2025/02/15.
//

#ifndef ofxPingPongFbo_h
#define ofxPingPongFbo_h

#include "ofFbo.h"
#include "ofGLBaseTypes.h"
#include "ofGraphicsBaseTypes.h"

namespace ofx {
    struct PingPongFbo : public ofBaseDraws, public ofBaseHasTexture {
        void allocate(ofFboSettings settings, std::size_t num_fbo = 2) {
            if(num_fbo < 2) {
                ofLogWarning("ofxPingPongFbo") << "num_fbo must be 2 or more. now num_fbo is setted to 2.";
                num_fbo = 2;
            }
            current_fbo_index = 0;
            fbos.resize(num_fbo);
            for(auto& fbo : fbos) {
                fbo.allocate(settings);
                fbo.begin();
                ofClear(0, 0, 0, 0);
                fbo.end();
            }
        }
        
        void setAutomaticallyNextWithEnd(bool automatically_next_with_end) {
            this->automatically_next_with_end = automatically_next_with_end;
        }
        
        void begin(ofFboMode mode = OF_FBOMODE_PERSPECTIVE | OF_FBOMODE_MATRIXFLIP) const {
            currentFbo().begin(mode);
        }
        
        void end() const {
            end(automatically_next_with_end);
        }
        
        void end(bool with_next) const {
            currentFbo().end();
            if(with_next) next();
        }

        void readToPixels(ofPixels & pixels, int attachmentPoint = 0) const
        { currentFbo().readToPixels(pixels, attachmentPoint); }
        void readToPixels(ofShortPixels & pixels, int attachmentPoint = 0) const
        { currentFbo().readToPixels(pixels, attachmentPoint); }
        void readToPixels(ofFloatPixels & pixels, int attachmentPoint = 0) const
        { currentFbo().readToPixels(pixels, attachmentPoint); }
        
        void bind() const
        { currentFbo().bind(); }
        
        void unbind() const
        { currentFbo().unbind(); }
        
        void next() const {
            current_fbo_index = (current() + 1) % size();
        }
        
        using ofBaseDraws::draw;
        void draw(float x, float y, float w, float h) const override
        { currentFbo().draw(x, y, w, h); }
        
        float getWidth() const override
        { return currentFbo().getWidth(); }
        float getHeight() const override
        { return currentFbo().getHeight(); }
        
        ofTexture &getTexture() override
        { return currentFbo().getTexture(); }
        const ofTexture &getTexture() const override
        { return currentFbo().getTexture(); }
        
        ofTexture &getTexture(int attachmentPoint)
        { return currentFbo().getTexture(attachmentPoint); }
        const ofTexture &getTexture(int attachmentPoint) const
        { return currentFbo().getTexture(attachmentPoint); }
        
        ofTexture &getDepthTexture()
        { return currentFbo().getDepthTexture(); }
        const ofTexture &getDepthTexture() const
        { return currentFbo().getDepthTexture(); }

        void setUseTexture(bool) override {};
        bool isUsingTexture() const override { return true; }

        ofFbo &operator[](std::int64_t n) {
            while(n < 0) n += size();
            return fbos[(current() + n) % size()];
        }
        
        const ofFbo &operator[](std::int64_t n) const {
            while(n < 0) n += size();
            return fbos[(current() + n) % size()];
        }
        
        std::size_t size() const
        { return fbos.size(); }
        std::size_t current() const
        { return current_fbo_index; }
        
        ofFbo &currentFbo()
        { return fbos[current()]; }
        const ofFbo &currentFbo() const
        { return fbos[current()]; }

        ofFbo &prevFbo(std::size_t n = 1)
        { return fbos[(current() + size() - n % size()) % size()]; }
        const ofFbo &prevFbo(std::size_t n = 1) const
        { return fbos[(current() + size() - n % size()) % size()]; }
        
    protected:
        std::vector<ofFbo> fbos;
        mutable std::size_t current_fbo_index{0};
        bool automatically_next_with_end{false};
    };
}; // namespace ofx

using ofxPingPongFbo = ofx::PingPongFbo;

#endif /* ofxPingPongFbo_h */
