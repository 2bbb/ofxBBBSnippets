#pragma once

#ifndef OFXLIMITEDLIFE_H
#define OFXLIMITEDLIFE_H

#include "ofUtils.h"

#include <bbb/snippets/limited_life.hpp>

template <typename base_type, float time_func() = ofGetElapsedTimef>
using ofxLimitedLifeInjector = bbb::limited_life_injector<base_type, time_func>;

template <typename base_type, float time_func() = ofGetElapsedTimef>
using ofxLimitedLife = bbb::limited_life<base_type, time_func>;

#endif // OFXLIMITEDLIFE_H
