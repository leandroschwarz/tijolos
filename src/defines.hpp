
#ifndef __DEFINES_HPP
#define __DEFINES_HPP

#define maximumOf(var1, var2)           ((var1 > var2) ? var1 : var2)
#define minimumOf(var1, var2)           ((var1 < var2) ? var1 : var2)
#define truncateBetween(var, min, max)  ((var < min) ? min : ((var > max) ? max : var))

#define SCREEN_WIDTH                    1280
#define SCREEN_HEIGHT                   900



struct KeyPressed {
    bool            keyLeftArrow;
    bool            keyRightArrow;
};

enum class Collision {
    NONE            = 0,
    LEFT            = 1,
    RIGHT           = 2,
    BOTTOM          = 3,
    TOP             = 4
};

#endif
