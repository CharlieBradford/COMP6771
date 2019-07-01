#include "tutorials/week3/car.h"

class Car {
 public:
  Car(std::string& manufacturer, int& num_seats): manufacturer_{manufacturer}, num_seats_{nSeats} {}

  Car(std::string& manufacturer, int& num_seats) {
    manufacturer_ = manufacturer;
    num_seats_ = num_seats;
  }

  std::string manufacturer_;
  int num_seats_;
};
