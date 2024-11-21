

#ifndef CAR_H
#define CAR_H

#include <Angel.h>
#include "Objects.h"


class Car : public Object {
 public:
    Car();

    ~Car();

    void driveForward();
    void driveBackward();
    void turnLeft();
    void turnRight();
    void draw() const;

 private:
};

#endif