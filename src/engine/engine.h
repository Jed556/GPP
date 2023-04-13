#ifndef ENGINE_H
#define ENGINE_H

#include "cards.h"
#include "display.h"
#include "prompt.h"
#include "quiz.h"
#include "text.h"

class Engine {
   public:
    std::string version();
};

#endif  // ENGINE_H