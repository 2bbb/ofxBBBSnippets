//
//  ofxGLFWUtils.cpp
//
//  Created by 2bit on 2025/03/03.
//

#include "ofxGLFWUtils.h"

#include "ofAppRunner.h"
#include "ofAppGLFWWindow.h"
#include "ofLog.h"

#include "GLFW/glfw3.h"

namespace ofx{
    namespace GLFWUtils {
        bool minimizeWindow() {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                glfwIconifyWindow(glfw_win_ptr);
                return true;
            } else {
                ofLogWarning("ofxGLFWUtils::minimizeWindow()") << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found";
                return false;
            }
        }
        
        bool maximizeWindow() {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                glfwMaximizeWindow(glfw_win_ptr);
                return true;
            } else {
                ofLogWarning("ofxGLFWUtils::maximizeWindow()") << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found";
                return false;
            }
        }
        
        bool restoreWindow() {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                glfwRestoreWindow(glfw_win_ptr);
                return true;
            } else {
                ofLogWarning("ofxGLFWUtils::restoreWindow()") << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found";
                return false;
            }
        }
        
        bool showWindow() {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                glfwShowWindow(glfw_win_ptr);
                return true;
            } else {
                ofLogWarning("ofxGLFWUtils::showWindow()") << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found";
                return false;
            }
        }
        
        bool hideWindow() {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                glfwHideWindow(glfw_win_ptr);
                return true;
            } else {
                ofLogWarning("ofxGLFWUtils::hideWindow()") << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found";
                return false;
            }
        }
        
        bool focusWindow() {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                glfwFocusWindow(glfw_win_ptr);
                return true;
            } else {
                ofLogWarning("ofxGLFWUtils::focusWindow()") << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found";
                return false;
            }
        }
        
        bool isWindowIconified() {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                int iconified = glfwGetWindowAttrib(glfw_win_ptr, GLFW_ICONIFIED);
                return iconified == GLFW_TRUE;
            } else {
                ofLogWarning("ofxGLFWUtils::isWindowIconified()") << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found. always returns false regardless of whether it is iconified or not.";
                return false;
            }
        }
        
        bool isWindowFocused() {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                int focused = glfwGetWindowAttrib(glfw_win_ptr, GLFW_FOCUSED);
                return focused == GLFW_TRUE;
            } else {
                ofLogWarning("ofxGLFWUtils::isWindowFocused()") << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found. always returns false regardless of whether it is iconified or not.";
                return false;
            }
        }
        
        bool isWindowFloating() {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                int floating = glfwGetWindowAttrib(glfw_win_ptr, GLFW_FLOATING);
                return floating == GLFW_TRUE;
            } else {
                ofLogWarning("ofxGLFWUtils::isWindowFloating()") << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found. always returns false regardless of whether it is iconified or not.";
                return false;
            }
        }
        bool setWindowFloating(bool floating) {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                glfwSetWindowAttrib(glfw_win_ptr,
                                    GLFW_FLOATING,
                                    floating ? GLFW_TRUE : GLFW_FALSE);
                return true;
            } else {
                ofLogWarning("ofxGLFWUtils::setWindowFloating()") << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found.";
                return false;
            }
        }
        
        float getWindowOpacity(float opacity) {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                float opacity = glfwGetWindowOpacity(glfw_win_ptr);
                return opacity;
            } else {
                ofLogWarning("ofxGLFWUtils::getWindowOpacity()") << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found.  returns -1.0f";
                return -1.0f;
            }
        }
        bool setWindowOpacity(float opacity) {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                glfwSetWindowOpacity(glfw_win_ptr, opacity);
                return true;
            } else {
                ofLogWarning("ofxGLFWUtils::setWindowOpacity()") << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found.";
                return false;
            }
        }

        
        // monitor
        
        bool Monitor::setGamma(float gamma) {
            if(ptr == nullptr) {
                ofLogWarning("ofxGLFWUtils::Monitor::setGamma()") << "this monitor is not valid";
                return false;
            }
            
            GLFWmonitor *monitor = (GLFWmonitor *)ptr;
            glfwSetGamma(monitor, gamma);
            
            const char *error_str = nullptr;
            auto error_code = glfwGetError(&error_str);
            switch(error_code) {
                case GLFW_NO_ERROR:
                    return true;
                case GLFW_NOT_INITIALIZED:
                    ofLogError("ofxGLFWUtils::Monitor::setGamma()") << "GLFW_NOT_INITIALIZED: " << error_str;
                    return false;
                case GLFW_INVALID_VALUE:
                    ofLogError("ofxGLFWUtils::Monitor::setGamma()") << "GLFW_INVALID_VALUE: " << error_str;
                    return false;
                case GLFW_PLATFORM_ERROR:
                    ofLogError("ofxGLFWUtils::Monitor::setGamma()") << "GLFW_PLATFORM_ERROR: " << error_str;
                    return false;
                default:
                    ofLogError("ofxGLFWUtils::Monitor::setGamma()") << "unknown error: " << error_str;
                    return false;
            }
        }
        
        bool Monitor::setGammaRamp(const GammaRamp &gamma_ramp) {
            if(ptr == nullptr) {
                ofLogWarning("ofxGLFWUtils::Monitor::setGammaRamp()") << "this monitor is not valid";
                return false;
            }
            if(gamma_ramp.empty()) {
                ofLogWarning("ofxGLFWUtils::Monitor::setGammaRamp()") << "given gamma_ramp is empty, nothing to do";
                return false;
            }
            GLFWgammaramp ramp;
            std::vector<unsigned short> red;
            std::vector<unsigned short> green;
            std::vector<unsigned short> blue;
            ramp.size = gamma_ramp.size();
            red.resize(ramp.size);
            green.resize(ramp.size);
            blue.resize(ramp.size);
            
            GLFWmonitor *monitor = (GLFWmonitor *)ptr;
            glfwSetGammaRamp(monitor, &ramp);
            
            const char *error_str = nullptr;
            auto error_code = glfwGetError(&error_str);
            switch(error_code) {
                case GLFW_NO_ERROR:
                    return true;
                case GLFW_NOT_INITIALIZED:
                    ofLogError("ofxGLFWUtils::Monitor::setGamma()") << "GLFW_NOT_INITIALIZED: " << error_str;
                    return false;
                case GLFW_INVALID_VALUE:
                    ofLogError("ofxGLFWUtils::Monitor::setGamma()") << "GLFW_INVALID_VALUE: " << error_str;
                    return false;
                case GLFW_PLATFORM_ERROR:
                    ofLogError("ofxGLFWUtils::Monitor::setGamma()") << "GLFW_PLATFORM_ERROR: " << error_str;
                    return false;
                default:
                    ofLogError("ofxGLFWUtils::Monitor::setGamma()") << "unknown error: " << error_str;
                    return false;
            }
        }
        
        void parseGLFWMonitor(GLFWmonitor *monitor_ptr, Monitor &monitor) {
            monitor.name = glfwGetMonitorName(monitor_ptr);
            
            glfwGetMonitorPhysicalSize(monitor_ptr,
                                       &monitor.physicalSize.width_mm,
                                       &monitor.physicalSize.height_mm);
            glfwGetMonitorContentScale(monitor_ptr,
                                       &monitor.contentScale.x,
                                       &monitor.contentScale.y);
            glfwGetMonitorWorkarea(monitor_ptr,
                                   &monitor.workArea.x,
                                   &monitor.workArea.y,
                                   &monitor.workArea.width,
                                   &monitor.workArea.height);
            glfwGetMonitorPos(monitor_ptr,
                              &monitor.position.x,
                              &monitor.position.y);
            
            auto gamma_ramp = glfwGetGammaRamp(monitor_ptr);
            if(gamma_ramp != nullptr) {
                monitor.gammaRamp.resize(gamma_ramp->size);
                for(auto i = 0; i < monitor.gammaRamp.size(); ++i) {
                    auto &c = monitor.gammaRamp[i];
                    c.r = gamma_ramp->red[i];
                    c.g = gamma_ramp->green[i];
                    c.b = gamma_ramp->blue[i];
                }
            }
            
            int num_video_modes = 0;
            auto video_modes = glfwGetVideoModes(monitor_ptr, &num_video_modes);
            monitor.videoModes.resize(num_video_modes);
            for(int j = 0; j < num_video_modes; ++j) {
                auto &&video_mode = video_modes[j];
                monitor.videoModes[j].width = video_mode.width;
                monitor.videoModes[j].height = video_mode.height;
                monitor.videoModes[j].redBits = video_mode.redBits;
                monitor.videoModes[j].greenBits = video_mode.greenBits;
                monitor.videoModes[j].blueBits = video_mode.blueBits;
                monitor.videoModes[j].refreshRate = video_mode.refreshRate;
            }
        }
        
        Monitor getPrimaryMonitor() {
            Monitor monitor;
            auto monitor_ptr = glfwGetPrimaryMonitor();
            monitor.ptr = (void *)monitor_ptr;
            parseGLFWMonitor(monitor_ptr, monitor);
            return monitor;
        }
        
        std::vector<Monitor> getMonitorsInfo() {
            int num_monitors = 0;
            GLFWmonitor **monitors_ptr = glfwGetMonitors(&num_monitors);
            std::vector<Monitor> monitors;
            monitors.resize(num_monitors);
            for(int i = 0; i < num_monitors; ++i) {
                auto &monitor = monitors[i];
                auto monitor_ptr = monitors_ptr[i];
                monitor.ptr = (void *)monitor_ptr;
                parseGLFWMonitor(monitor_ptr, monitor);
            }
            return monitors;
        }
        
        Monitor getWindowMonitor() {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                auto monitor_ptr = glfwGetWindowMonitor(glfw_win_ptr);
                if(monitor_ptr == nullptr) {
                    ofLogError("ofxGLFWUtils::Monitor::getWindowMonitor()") << "monitor not found";
                    return {};
                }
                Monitor monitor;
                parseGLFWMonitor(monitor_ptr, monitor);
                return monitor;
            } else {
                return {};
            }
        }
    }
}
