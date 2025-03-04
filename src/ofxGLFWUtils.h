//
//  ofxGLFWUtils.hpp
//
//  Created by 2bit on 2025/03/03.
//

#ifndef ofxGLFWUtils_h
#define ofxGLFWUtils_h

#include "ofColor.h"

#include <glm/glm.hpp>

#include <vector>
#include <functional>

namespace ofx {
    namespace GLFWUtils {
        bool minimizeWindow();
        bool maximizeWindow();
        bool restoreWindow();
        bool showWindow();
        bool hideWindow();
        bool focusWindow();

        bool isWindowIconified();
        bool isWindowFocused();
        
        bool isWindowFloating();
        bool setWindowFloating(bool floating);

        bool isWindowDecorated();
        bool setWindowDecorated(bool decorated);

        bool isWindowCenterCursor();
        bool setWindowCenterCursor(bool center_cursor);
        bool showCursor();
        bool hideCursor();
        bool disableCursor();

        bool isWindowMousePassthrough();
        bool setWindowMousePassthrough(bool passthrough);
        
        float getWindowOpacity(float opacity);
        bool setWindowOpacity(float opacity);
        
        bool setWindowSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight);
        bool setWindowAspectRatio(int width, int height);
        
        //
        
        struct PhysicalSize {
            int width_mm;
            int height_mm;
        };
        
        using ContentScale = glm::vec2;
        
        using Position = glm::ivec2;
        
        struct WorkArea {
            int x;
            int y;
            int width;
            int height;
        };
        
        using GammaRamp = std::vector<ofShortColor>;
        
        struct VideoMode {
            int width;
            int height;
            int redBits;
            int greenBits;
            int blueBits;
            int refreshRate;
        };
        
        struct Monitor {
            std::string name;
            
            PhysicalSize physicalSize;
            ContentScale contentScale;
            Position position;
            WorkArea workArea;
            std::vector<VideoMode> videoModes;
            GammaRamp gammaRamp;
            
            friend std::ostream &operator<<(std::ostream &os, const Monitor &m) {
                os << "[" << m.name << "]" << std::endl;
                os << "  physical size: " << m.physicalSize.width_mm << "mm x " << m.physicalSize.height_mm << "mm" << std::endl;
                os << "  content scale: " << m.contentScale.x << " x " << m.contentScale.y << std::endl;
                os << "  position: " << m.position.x << " x " << m.position.y << std::endl;
                os << "  work area: " << m.workArea.x << " x " << m.workArea.y << ", (" << m.workArea.width << " x " << m.workArea.height << ")" << std::endl;
                os << "  video modes:" << std::endl;
                os << "  size of gamma ramp: " << m.gammaRamp.size();
                for(auto &vm : m.videoModes) {
                    os << "    " << vm.width << " x " << vm.height << ", r: " << vm.redBits << ", g: " << vm.greenBits << ", b: " << vm.blueBits << ", " << vm.refreshRate << " Hz" << std::endl;
                }
                return os;
            }
            
            bool setGamma(float gammga);
            bool setGammaRamp(const GammaRamp &gamma_ramp);
            
        protected:
            void *ptr{nullptr};
            friend Monitor getPrimaryMonitor();
            friend std::vector<Monitor> getMonitorsInfo();
        };
        
        Monitor getPrimaryMonitor();
        std::vector<Monitor> getMonitorsInfo();
        
        Monitor getWindowMonitor();
    }
};

namespace ofxGLFWUtils = ofx::GLFWUtils;

#endif /* ofxGLFWUtils_h */
