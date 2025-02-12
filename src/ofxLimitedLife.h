#pragma once

#ifndef OFXLIMITEDLIFE_H
#define OFXLIMITEDLIFE_H

#include "ofUtils.h"

#include <bbb/snippets/limited_life.hpp>

template <typename base_type, float time_func() = ofGetElapsedTimef>
using ofxLimitedLifeInjector = bbb::LimitedLifeInjector<base_type, time_func>;

template <typename base_type, float time_func() = ofGetElapsedTimef>
using ofxLimitedLife = bbb::LimitedLife<base_type, time_func>;

#endif // OFXLIMITEDLIFE_H
