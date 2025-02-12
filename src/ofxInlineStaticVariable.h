#pragma once

#ifndef OFXINLINESTATICVARIABLE_H
#define OFXINLINESTATICVARIABLE_H

#include <bbb/snippets/inline_static_variable.hpp>

template <typename type, typename tag = void>
using ofxInlineStaticVariable = bbb::inline_static_variable<type, tag>;

using ofxDummyRef = bbb::dummy_ref;

#endif // OFXINLINESTATICVARIABLE_H

