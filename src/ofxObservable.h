#pragma once

#ifndef OFXOBSERVABLE_H
#define OFXOBSERVABLE_H

#include <bbb/snippets/observable.hpp>

template <typename value_type>
using ofxObservable = bbb::observable<value_type>;

#endif // OFXOBSERVABLE_H
