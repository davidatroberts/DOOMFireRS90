#ifndef FIRESTATE_H
#define FIRESTATE_H

#include <memory>

#include "State.h"

struct Context;

std::shared_ptr<State> createFireState(std::shared_ptr<Context> context);

#endif