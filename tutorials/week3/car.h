#ifndef TUTORIALS_WEEK3_CAR_H_
#define TUTORIALS_WEEK3_CAR_H_

#include <string>

class Car {
 public:
  //Car(const std::string& manufacturer): manufacturer_{manufacturer}, num_seats_{0} {}
  Car(const std::string& manufacturer, int num_seats):
    manufacturer_{manufacturer}, num_seats_{num_seats} {counter++;}
  Car(): Car("Unknown", 4) {}

  const std::string& getManufacturerName();
  const int& getNumSeats();

  static int getObjectCount();

  Car& operator=(const Car& original);


 private:
  std::string manufacturer_;
  int num_seats_;
  static int counter;
};

#endif  // TUTORIALS_WEEK3_CAR_H_
