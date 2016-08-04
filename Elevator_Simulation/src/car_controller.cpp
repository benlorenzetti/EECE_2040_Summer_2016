/*  car_controller.cpp
 *
*/

#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "car_controller.h"
using namespace std;

/********************************************************************  
 *  car_controller(...)                                             *
 ********************************************************************
*/
car_controller::car_controller(
  string name,
  hall_buttons *building_interface,
  int home_floor,
  double floor_height,
  double empty_mass,
  double max_accel,
  double max_speed,
  double stop_time,
  double stop_tolerance
) : call_requests(building_interface),
    home_floor(home_floor),
    floor_height(floor_height),
    empty_mass(empty_mass),
    max_accel(max_accel),
    max_speed(max_speed), 
    stop_time(stop_time),
    stop_tolerance(stop_tolerance)
{
  this->mass = empty_mass;
  this->position = home_floor * floor_height;
  this->velocity = 0;
  this->acceleration = 0;
  this->state = Home;
  this->stop_requests.clear_all();
  this->dest_floor = home_floor;
  this->timer = 0;
  this->name = name;
}

/********************************************************************
 *  int current_floor()                                             *
 ********************************************************************
 *  Returns a floor number if this car's position is within
 *  its stop_tolerance of a building floor, otherwise returns
 *  POSITION_BETWEEN_FLOORS.
*/
int car_controller::current_floor() {
  int closest_floor = (int)(position / floor_height + 0.5);
  if(fabs(closest_floor * floor_height - position) <= stop_tolerance)
    return closest_floor;
  else
    return POSITION_BETWEEN_FLOORS;
}

/********************************************************************
 *  void simulate(double inc_time, bool print)                      *
 ********************************************************************
 *  This function starts by modifying the car's physical variables
 *  (position and velocity) according to the controller's
 *  acceleration output and the equations of motion for the given
 *  incrementation time.
 *
 *  After processing the physical model, it increments the controller
 *  state machine according to the state diagram in the readme file.
 *  The state machine controls the acceleration.
*/
void car_controller::simulate(double time, bool print) {
  // Calculate new position and velocity
  velocity = velocity - (acceleration * time);
  position = position + (velocity*time) - (acceleration/2)*time*time;

  // Increment the horriffic state machine
  control_state prev_state = state;
  switch(state) {
    case Home:
      home_next_state_logic();
      if(print && prev_state != state)
        cout << "[" << name << "] switches states from [Home] to ["
          << state_string(state) << "] at floor "
          << current_floor() << endl;
    break;
    default:
      cerr << "Error: controller is in unrecognized state.\n";
      exit(EXIT_FAILURE);
  }
}

string state_string(control_state state) {
  switch(state) {
    case Home: return "Home";
    case Upstop: return "Upstop";
    case Upstart: return "Upstart";
    case Upaccel: return "Upaccel";
    case Uptravel: return "Uptravel";
    case Updecel: return "Updecel";
    case Downstop: return "Downstop";
    case Downstart: return "Downstart";
    case Downaccel: return "Downaccel";
    case Downtravel: return "Downtravel";
    case Downdecel: return "Downdecel";
    default:
      cerr << "state_string() error: state not recognized.\n";
      exit(EXIT_FAILURE);
  }
}

/********************************************************************
 *  Next State Logic Functions                                      *
 ********************************************************************
*/
void car_controller::home_next_state_logic() {
  // If the home level is closer to the bottom, then go to upstop.
  int top, bot, dist2top, dist2bot;
  top = call_requests->get_top();
  bot = call_requests->get_bottom();
  dist2top = call_requests->get_service_distance(top, home_floor);
  dist2bot = call_requests->get_service_distance(bot, home_floor);
  if(dist2bot < dist2top)
    state = Upstop;
  // If the home level is closer to the top, then go to downstop.
  state = Downstop;
}
