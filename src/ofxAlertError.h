//
//  ofxAlertError.h
//
//  Created by 2bit on 2025/02/15.
//

#ifndef ofxAlertError_h
#define ofxAlertError_h

#include <bbb/snippets/noncopyable.hpp>

#include "ofSystemUtils.h"
#include <functional>
#include <string>

namespace ofx {
    struct AlertError : bbb::noncopyable {
        AlertError(const std::string &name,
                   std::function<bool()> fun,
                   bool exit_when_failed = true,
                   bool exit_when_error_was_thrown = true)
        : name{name}
        , fun{fun}
        {}
        
        virtual ~AlertError() {
            try {
                ofLogNotice(__func__);
                if(!fun()) {
                    ofSystemAlertDialog(name + " failed...");
                    if(exit_when_failed) ofExit(-1);
                }
            } catch(std::exception &e) {
                ofSystemAlertDialog(" error on " + name + ": " + e.what());
                if(exit_when_error_was_thrown) ofExit(-1);
            } catch(std::string error_message) {
                ofSystemAlertDialog(" error on " + name + ": " + error_message);
                if(exit_when_error_was_thrown) ofExit(-1);
            } catch(...) {
                ofSystemAlertDialog(" error on " + name);
                if(exit_when_error_was_thrown) ofExit(-1);
            }
        }
        
        AlertError &exitWhenFailed(bool will_exit) {
            exit_when_failed = will_exit;
            return *this;
        }
        AlertError &exitWhenErrorWasThrown(bool will_exit) {
            exit_when_error_was_thrown = will_exit;
            return *this;
        }
        
    protected:
        AlertError() = delete;
        std::string name;
        std::function<bool()> fun;
        bool exit_when_failed{true};
        bool exit_when_error_was_thrown{true};
    };
}; // namespace ofx

using ofxAlertError = ofx::AlertError;

#endif /* ofxAlertError_h */
