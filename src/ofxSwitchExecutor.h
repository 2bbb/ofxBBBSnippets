//
//  ofxSwitchExecutor.h
//  ofxLocal2bbbAddonsDev
//
//  Created by 2bit on 2025/02/14.
//

#ifndef ofxSwitchExecutor_h
#define ofxSwitchExecutor_h

#include <map>

namespace ofx {
    template <typename enum_like>
    struct SwitchExecutor {
        void action(enum_like value, std::function<void()> action) {
            actions[value] = action;
        }
        
        void fallback(std::function<void()> action) {
            default_action = action;
        }
        
        void remove(enum_like value) {
            actions.erase(value);
        }
        
        void run(enum_like value) const {
            if(actions.find(value) != actions.end()) {
                actions.at(value)();
            } else {
                if(default_action) default_action();
            }
        }
        
    private:
        std::map<enum_like, std::function<void()>> actions;
        std::function<void()> default_action;
    };
};

template <typename enum_like>
using ofxSwitchExecutor = ofx::SwitchExecutor<enum_like>;

#endif /* ofxSwitchExecutor_h */
