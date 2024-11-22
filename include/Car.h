#include <Angel.h>
#include "Object.h"

#ifndef CAR_H
#define CAR_H


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