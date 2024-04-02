#pragma once

#define CAPYBARA_SPEED 5
#define CAPYBARA_RUN_SPEED 10
#define CAYMAN_SPEED 7
#define CAYMAN_HUNT_SPEED 15
#define ORANGE_SPEED 2
#define CAPYBARA_RUN_DISTANCE 150
#define CAYMAN_HUNT_DISTANCE 250
// SCREAN
#define WIDTH 1920
#define HEIGHT 1080


#define SPRITES_PATH "C:/Program Files (x86)/for ecos/lake/"s
#define TYPE_CAYMAN "C:/Program Files (x86)/for ecos/lake/cayman_sprite.png" 
#define TYPE_CAPYBARA "C:/Program Files (x86)/for ecos/lake/capybara_sprite.png" 
#define TYPE_ORANGE "C:/Program Files (x86)/for ecos/lake/orange_sprite.png" 

#define BACKGROUND_PATH "C:/Program Files (x86)/for ecos/lake/background.png"

#define MIN_CAPYBARA_COUNT 16
#define MIN_CAYMAN_COUNT 5
#define MIN_ORANGE_COUNT 100
#define CAPYBARA_LIFE_TIME 80000
#define CAYMAN_LIFE_TIME 100000
#define ORANGE_LIFE_TIME 40000


#define CAPYBARA_EYE {91, 23}
#define CAYMAN_EYE {174, 49}

#define CAYMAN_CENTER {100.5, 40}
#define CAPYBARA_CENTER {48.5, 26.5}
#define ORANGE_CENTER {20, 20}

#define CAPYBARA_WIDTH 97
#define CAPYBARA_HEIGHT 53

#define CAYMAN_WIDTH 201
#define CAYMAN_HEIGHT 80



#define ACOSD(x) (acos(x) * 180 / M_PI)

#define DOT_PRODUCT(x, y) (x.i * y.i + x.j * y.j)
#define VECT_DIST(x) (sqrtf(x.i * x.i + x.j * x.j))

#define ANGLE_BY_DOT_PRODUCT(x, y) (ACOSD(DOT_PRODUCT(x, y)/(VECT_DIST(x) * VECT_DIST(y))))
