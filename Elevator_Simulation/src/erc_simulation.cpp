#include "request_buttons.h"
#include "car_controller.h"
#include <iostream>
using namespace std;

const double FLOOR_HEIGHT = 3.0; // meters
const double EMPTY_MASS = 2000;  // kg
const double MAX_ACCEL = 1.0;    // m/s^2
const double MAX_SPEED = 5.0;    // m/s
const double STOP_TIME = 20;     // seconds with door open
const double STOP_TOLERANCE = 0.001; // m

int main() {
  // Initialize the hallway interface object for the ERC elevators
  int erc_floors[6] = {3, 4, 5, 6, 7, 8};
  hall_buttons erc_buttons(erc_floors, sizeof(erc_floors));

  // Initialize two elevator car controller connected to the ERC
  // hallway buttons
  car_controller car1("car1", &erc_buttons, 4, FLOOR_HEIGHT, EMPTY_MASS,
                      MAX_ACCEL, MAX_SPEED, STOP_TIME, STOP_TOLERANCE);
  car_controller car2("car2", &erc_buttons, 6, FLOOR_HEIGHT, EMPTY_MASS,
                      MAX_ACCEL, MAX_SPEED, STOP_TIME, STOP_TOLERANCE);

  // Make some calls
  erc_buttons.request_up(5);
  erc_buttons.request_down(7);
  erc_buttons.request_up(4);

  for(int i=0; i<10000; i++) {
    car_controller::global_time += 0.01;
    car1.simulate(0.01, true);
    car2.simulate(0.01, true);
  }
  
  return 0; 
}
