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
  hall_queues erc_halls(3, 8);

  // Initialize two elevator cars connected to the ERC hallway buttons
  elevator_car car1("car1", &erc_halls, 4, FLOOR_HEIGHT, SUPER_FUJIOATS);
  elevator_car car2("car2", &erc_halls, 6, FLOOR_HEIGHT, SUPER_FUJIOATS);

  // Generate some new passengers with random origin and dest floors
  passenger temp;
  for(int i = 0; i < 3; i++) {
    fill_new_passenger(&temp, 3, 8);
    cout << "passenger " << temp.id << " traveling from " << temp.origin_floor
      << " to " << temp.dest_floor << endl;
    erc_halls.push_passenger(temp);
  }

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
