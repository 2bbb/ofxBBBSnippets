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

#include <string>
#include <tuple>
#include <map>

namespace ofx{
    namespace GLFWUtils {
        std::pair<bool, std::string> glfwErrorCheck(const std::string &tag) {
            const char *error_str = nullptr;
            auto error_code = glfwGetError(&error_str);
            switch(error_code) {
                case GLFW_NO_ERROR:
                    return { true, "" };
                case GLFW_NOT_INITIALIZED:
                    ofLogError(tag) << "GLFW_NOT_INITIALIZED: " << error_str;
                    return { false, error_str };
                case GLFW_INVALID_VALUE:
                    ofLogError(tag) << "GLFW_INVALID_VALUE: " << error_str;
                    return { false, error_str };
                case GLFW_PLATFORM_ERROR:
                    ofLogError(tag) << "GLFW_PLATFORM_ERROR: " << error_str;
                    return { false, error_str };
                default:
                    ofLogError(tag) << "error: " << error_str;
                    return { false, error_str };
            }
        }
        
        
        template <typename Function, typename ... Arguments>
        bool callGLFWFunction(const std::string &tag,
                              Function fun,
                              Arguments && ... args)
        {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                fun(glfw_win_ptr, std::forward<Arguments>(args) ...);
                return true;
            } else {
                ofLogWarning(tag) << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found";
                return false;
            }
        }
        
        bool callGLFWGetBoolFunction(const std::string &tag,
                                     int attribute)
        {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                int result = glfwGetWindowAttrib(glfw_win_ptr, attribute);
                return result == GLFW_TRUE;
            } else {
                ofLogWarning(tag) << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found. always returns false regardless of whether it is iconified or not.";
                return false;
            }
        }
        
        bool callGLFWSetBoolFunction(const std::string &tag,
                                     int attribute,
                                     bool value)
        {
            auto of_glfw_win_ptr = dynamic_cast<ofAppGLFWWindow *>(ofGetWindowPtr());
            if(of_glfw_win_ptr) {
                auto glfw_win_ptr = of_glfw_win_ptr->getGLFWWindow();
                glfwSetWindowAttrib(glfw_win_ptr,
                                    attribute,
                                    value ? GLFW_TRUE : GLFW_FALSE);
                return true;
            } else {
                ofLogWarning(tag) << "window pointer (= ofGetWindowPtr()) can not be cast to ofAppGLFWWindow not found.";
                return false;
            }
        }

        bool minimizeWindow() {
            return callGLFWFunction("ofxGLFWUtils::minimizeWindow()", glfwIconifyWindow);
        }
        
        bool maximizeWindow() {
            return callGLFWFunction("ofxGLFWUtils::maximizeWindow()", glfwMaximizeWindow);
        }
        
        bool restoreWindow() {
            return callGLFWFunction("ofxGLFWUtils::restoreWindow()", glfwRestoreWindow);
        }
        
        bool showWindow() {
            return callGLFWFunction("ofxGLFWUtils::showWindow()", glfwShowWindow);
        }
        
        bool hideWindow() {
            return callGLFWFunction("ofxGLFWUtils::hideWindow()", glfwHideWindow);
        }
        
        bool focusWindow() {
            return callGLFWFunction("ofxGLFWUtils::focusWindow()", glfwFocusWindow);
        }
        
        bool isWindowIconified() {
            return callGLFWGetBoolFunction("ofxGLFWUtils::isWindowIconified()",
                                           GLFW_ICONIFIED);
        }
        
        bool isWindowFocused() {
            return callGLFWGetBoolFunction("ofxGLFWUtils::isWindowFocused()",
                                           GLFW_FOCUSED);
        }
        
        bool isWindowFloating() {
            return callGLFWGetBoolFunction("ofxGLFWUtils::isWindowFloating()",
                                           GLFW_FLOATING);
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
        
        bool isWindowDecorated() {
            return callGLFWGetBoolFunction("ofxGLFWUtils::isWindowDecorated()",
                                           GLFW_DECORATED);
        }
        
        bool setWindowDecorated(bool decorated) {
            return callGLFWSetBoolFunction("ofxGLFWUtils::setWindowDecorated()",
                                           GLFW_DECORATED,
                                           decorated);
        }

        bool isWindowCenterCursor() {
            return callGLFWGetBoolFunction("ofxGLFWUtils::isWindowCenterCursor()",
                                           GLFW_CENTER_CURSOR);
        }
        
        bool setWindowCenterCursor(bool center_cursor) {
            return callGLFWSetBoolFunction("ofxGLFWUtils::setWindowCenterCursor()",
                                           GLFW_CENTER_CURSOR,
                                           center_cursor);
        }

        bool showCursor() {
            return callGLFWFunction("ofxGLFWUtils::showCursor()",
                                    glfwSetInputMode,
                                    GLFW_CURSOR,
                                    GLFW_CURSOR_NORMAL);
        }
        bool hideCursor() {
            return callGLFWFunction("ofxGLFWUtils::hideCursor()",
                                    glfwSetInputMode,
                                    GLFW_CURSOR,
                                    GLFW_CURSOR_HIDDEN);
        }
        bool disableCursor() {
            return callGLFWFunction("ofxGLFWUtils::disableCursor()",
                                    glfwSetInputMode,
                                    GLFW_CURSOR,
                                    GLFW_CURSOR_DISABLED);
        }

#if (3 < GLFW_VERSION_MAJOR) || ((GLFW_VERSION_MAJOR == 3) && (3 < GLFW_VERSION_MINOR))
        bool isWindowMousePassthrough() {
            return callGLFWGetBoolFunction("ofxGLFWUtils::isWindowMousePassthrough()",
                                           GLFW_MOUSE_PASSTHROUGH);
        }
        
        bool setWindowMousePassthrough(bool passthrough) {
            return callGLFWSetBoolFunction("ofxGLFWUtils::setWindowMousePassthrough()",
                                           GLFW_MOUSE_PASSTHROUGH,
                                           passthrough);
        }
#else
        bool isWindowMousePassthrough() {
            ofLogError("ofxGLFWUtils::isWindowMousePassthrough()") << "GLFW 3.4+ required";
            return false;
        }
        
        bool setWindowMousePassthrough(bool passthrough) {
            ofLogError("ofxGLFWUtils::setWindowMousePassthrough()") << "GLFW 3.4+ required";
            return false;
        }
#endif
        
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
            return callGLFWFunction("ofxGLFWUtils::setWindowOpacity()",
                                    glfwSetWindowOpacity,
                                    opacity);
        }

        bool setWindowSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight) {
            return callGLFWFunction("ofxGLFWUtils::setWindowSizeLimits()",
                                    glfwSetWindowSizeLimits,
                                    minWidth <= 0 ? GLFW_DONT_CARE : minWidth,
                                    minHeight <= 0 ? GLFW_DONT_CARE : minHeight,
                                    maxWidth <= 0 ? GLFW_DONT_CARE : maxWidth,
                                    maxHeight <= 0 ? GLFW_DONT_CARE : maxHeight);
        }
        
        bool setWindowAspectRatio(int width, int height) {
            if(width <= 0 || height <= 0) {
                width = GLFW_DONT_CARE;
                height = GLFW_DONT_CARE;
            }
            return callGLFWFunction("ofxGLFWUtils::setWindowSizeLimits()",
                                    glfwSetWindowAspectRatio,
                                    width, height);
        }

        // monitor
        
        bool Monitor::setGamma(float gamma) {
            if(ptr == nullptr) {
                ofLogWarning("ofxGLFWUtils::Monitor::setGamma()") << "this monitor is not valid";
                return false;
            }
            
            GLFWmonitor *monitor = (GLFWmonitor *)ptr;
            if(monitor == nullptr) {
                ofLogError("ofxGLFWUtils::Monitor::setGammaRamp()") << "failed to get GLFWmonitor pointer";
                return false;
            }
            glfwSetGamma(monitor, gamma);
            
            auto result = glfwErrorCheck("ofxGLFWUtils::Monitor::setGamma()");
            return result.first;
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
            ramp.red = red.data();
            ramp.green = green.data();
            ramp.blue = blue.data();
            
            for(auto i = 0; i < ramp.size; ++i) {
                ramp.red[i] = gamma_ramp[i].r;
                ramp.green[i] = gamma_ramp[i].g;
                ramp.blue[i] = gamma_ramp[i].b;
            }
            
            GLFWmonitor *monitor = static_cast<GLFWmonitor *>(ptr);
            if(monitor == nullptr) {
                ofLogError("ofxGLFWUtils::Monitor::setGammaRamp()") << "failed to get GLFWmonitor pointer";
                return false;
            }
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
