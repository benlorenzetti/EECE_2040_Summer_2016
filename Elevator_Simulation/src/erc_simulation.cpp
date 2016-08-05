#include "passengers_cars_and_queues.h"
#include <iostream>
using namespace std;

const double FLOOR_HEIGHT = 3.0; // meters

const elevator_model SUPER_FUJIOATS = {
  2000, // empty mass (kg)
  2000, // max cargo mass (kg)
  1.0,  // max accel (m/s^2)
  5.0,  // max speed (m/s)
  10,   // station stop period (s)
  0.001 // station stop position tolerance (m)
};

int main() {
  // Initialize the hallway interface object for the ERC elevators
  int erc_floors[6] = {3, 4, 5, 6, 7, 8};
  hall_buttons erc_buttons(erc_floors, sizeof(erc_floors));

  // Initialize two elevator cars connected to the ERC hallway buttons
  elevator_car car1("car1", &erc_buttons, 4, FLOOR_HEIGHT, SUPER_FUJIOATS);
  elevator_car car2("car2", &erc_buttons, 6, FLOOR_HEIGHT, SUPER_FUJIOATS);

  passenger new_pass;
  fill_new_passenger(&new_pass, 3, 8);
  cout << "new_pass origin = " << new_pass.origin_floor << ", dest = " << new_pass.dest_floor << endl;
  car1.board(new_pass);

  int count = 0;
  for(int i=0; i<5000; i++) {
    car_controller::global_time += 0.01;
    car1.simulate(0.01, true);
    car2.simulate(0.01, true);
    count += car1.disembark(NULL);
    count += car2.disembark(NULL);
  }

  cout << "count = " << count << endl;
  
  return 0; 
}
