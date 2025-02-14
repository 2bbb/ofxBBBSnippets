#pragma once

#ifndef OFXCROSSFADE_H
#define OFXCROSSFADE_H

#include "ofGraphicsBaseTypes.h"
#include "ofTexture.h"
#include "ofImage.h"
#include "ofVideoPlayer.h"
#include "ofUtils.h"

#include <memory>

namespace ofx {
    struct CrossFade : public ofBaseDraws {
        using Ref = std::shared_ptr<CrossFade>;
        
        static Ref create(const ofBaseDraws &from, const ofBaseDraws &to, float duration)
        { return std::make_shared<CrossFade>(from, to, duration); }
        
        CrossFade(const ofBaseDraws &from, const ofBaseDraws &to, float duration)
        : duration{duration}
        , start_time{ofGetElapsedTimef()}
        , from{from}
        , to{to}
        {}
        
        bool completed() const
        { return duration + start_time <= ofGetElapsedTimef(); }
        virtual bool update()
        { return completed(); };
        
        virtual float getWidth() const override
        { return std::max(from.getWidth(), to.getWidth()); }
        
        virtual float getHeight() const override
        { return std::max(from.getHeight(), to.getHeight()); }
        
        using ofBaseDraws::draw;
        virtual void draw(float x, float y, float width, float height) const override {
            auto now = ofGetElapsedTimef();
            auto alpha = ofMap(now - start_time, 0, duration, 0, 255);
            ofSetColor(255, 255, 255);
            from.draw(x, y, width, height);
            ofSetColor(255, 255, 255, alpha);
            to.draw(x, y, width, height);
        }
        
        inline friend void update(Ref &ref) {
            if(ref && ref->update()) {
                ref.reset();
            }
        }

    protected:
        float duration{0.5f};
        float start_time;
        
        const ofBaseDraws &from;
        const ofBaseDraws &to;
    };
    
    struct VideoFader : public CrossFade {
        using Ref = std::shared_ptr<VideoFader>;
        
        VideoFader(ofVideoPlayer &from, ofVideoPlayer &to, float duration)
        : CrossFade{from, to, duration}
        , from{from}
        , to{to}
        {}
        
        bool update() override {
            if(!from.isPaused()) {
                from.update();
            }
            if(!to.isPaused()) {
                to.update();
            }
            if(completed()) {
                from.setPaused(true);
                from.setFrame(0);
                return true;
            }
            return false;
        }
        
        ofVideoPlayer &from;
        ofVideoPlayer &to;
    };
};

using ofxCrossFade = ofx::CrossFade;

#endif // OFXCROSSFADE_H
