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

//  Initialize the static, global time variable. (It is not used for
//  anything except printing state machine messages during debugging,
//  so don't feel the need to remeber its existance.
double car_controller::global_time = 0;

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
 *  double accel_to_stop(int destination_floor)                     *
 ********************************************************************
 *  Returns the required acceleration for constant deceleration for
 *  car to reach the dest_floor at zero velocity.
*/
double car_controller::accel_to_stop() {
  double dest_pos = dest_floor * floor_height;
  double accel = (velocity*velocity) / (2*(dest_pos-position));
  if(velocity > 0)
    accel *= -1;
  return accel;
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
  // Calculate new timer, position, and velocity
  timer += time;
  velocity = velocity + (acceleration * time);
  position = position + (velocity*time) + (acceleration/2)*time*time;

//cout << "v = " << velocity << ", y = " << position << ", a = " << acceleration << endl;

  // Increment the horriffic state machine
  control_state prev_state = state;
  switch(state) {
    case Home:
      home_next_state_logic();
      if(print && prev_state != state) {
        cout << "[" << name << "] switches state from [Home] to ["
          << state_string(state) << "] at floor "
          << current_floor() << " at " << ((int)global_time / 3600)
          << ":" << (((int)global_time / 60) % 60) << ":"
          << ((int)global_time % 60) << endl;
      }
    break;
    case Upstop:
      upstop_next_state_logic();
      if(print && prev_state != state) {
        cout <<"["<<name<<"] switches state from [Upstop] to ["
          << state_string(state) << "] at floor " << position / floor_height
          << " at " << ((int)global_time/3600) << ":"
          << (((int)global_time/60)%60) << ":" << ((int)global_time %60) << endl;
      }
    break;
    case Upstart:
      upstart_next_state_logic();
      if(print && prev_state != state) {
        cout <<"["<<name<<"] switches state from [Upstart] to ["
          << state_string(state) << "] going to floor " << dest_floor
          << " at " << ((int)global_time/3600) << ":"
          << (((int)global_time/60)%60) << ":" << ((int)global_time %60) << endl;
      }
    break;
    case Upaccel:
      upaccel_next_state_logic();
      if(print && prev_state != state) {
        cout <<"["<<name<<"] switches state from [Upaccel] to ["
          << state_string(state) << "] at floor " << position / floor_height
          << " at " << ((int)global_time/3600) << ":"
          << (((int)global_time/60)%60) << ":" << ((int)global_time %60) << endl;
      }
    break;
    case Uptravel:
      uptravel_next_state_logic();
      if(print && prev_state != state) {
        cout <<"["<<name<<"] switches state from [Uptravel] to ["
          << state_string(state) << "] at floor " << position / floor_height
          << " at " << ((int)global_time/3600) << ":"
          << (((int)global_time/60)%60) << ":" << ((int)global_time %60) << endl;
      }
    break;
    case Updecel:
      updecel_next_state_logic();
      if(print && prev_state != state) {
        cout <<"["<<name<<"] switches state from [Updecel] to ["
          << state_string(state) << "] at floor " << position / floor_height
          << " at " << ((int)global_time/3600) << ":"
          << (((int)global_time/60)%60) << ":" << ((int)global_time %60) << endl;
      }
    break;



    default:;
//      cerr << "Error: controller is in unrecognized state.\n";
//      exit(EXIT_FAILURE);
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
  if(dist2bot < dist2top) {
    state = Upstop;
    timer = 0;
  }
  // If the home level is closer to the top, then go to downstop.
  else {
    state = Downstop;
    timer = 0;
  }
}

void car_controller::upstop_next_state_logic() {
  if(timer < stop_time)
    return; // stay stopped until stop_time has passed
  /* Determine if there is any requests for floors above the current
     floor, whether it be uncleared hall up calls, destination
     requests, or uncleared hall down calls (from a higher floor). */
  if(call_requests->find_first_above(current_floor()) > current_floor()
     || stop_requests.find_first_above(current_floor()) > current_floor()
     || call_requests->find_highest_above(current_floor()) > current_floor())
  {
    state = Upstart;
    return;
  }
  /* If there are no requests above the current floor (proven by reaching
     this point), then the car should switch direction to down if there
     are requests below this floor */
  if(call_requests->find_lowest_below(current_floor()) < current_floor()
     || call_requests->find_first_below(current_floor()) < current_floor()
     || stop_requests.find_first_below(current_floor()) < current_floor())
  {
    state = Downstart;
    return;
  }
  /* Finally if there are absolutely no requests, the car should try
     to return home. */
  if(current_floor() == home_floor)
    state = Home;
  else if(home_floor < current_floor())
    state = Downstop;
  else
    state = Upstart;
}

void car_controller::upstart_next_state_logic() {
  state = Upaccel;
  /* It has already been determined to go up. Now need to choose
     the best destination floor (the closest one with a up call or
     stop request) or in liu of that, the highest down request
     or home. */
  int lowest_call_request, lowest_stop_request;
  lowest_call_request = call_requests->find_first_above(current_floor());
  lowest_stop_request = stop_requests.find_first_above(current_floor());
  if(lowest_call_request == current_floor() && lowest_stop_request == current_floor())
    {}
  else if(lowest_call_request == current_floor()) {
    dest_floor = lowest_stop_request;
    stop_requests.clear(lowest_stop_request);
    return;
  }
  else if(lowest_stop_request == current_floor()) {
    dest_floor = lowest_call_request;
    call_requests->clear_up(lowest_call_request);
    return;
  }
  else if(lowest_stop_request < lowest_call_request) {
    dest_floor = lowest_stop_request;
    stop_requests.clear(lowest_stop_request);
    return;
  }
  else {
    dest_floor = lowest_call_request;
    call_requests->clear_up(lowest_call_request);
    stop_requests.clear(lowest_call_request);
    return;
  }
  /*  If reach this point, then there were no up requests. Now try
      to goto a higher down request. */
  int highest_down_request = call_requests->find_highest_above(current_floor());
  if(highest_down_request > current_floor()) {
    dest_floor = highest_down_request;
    call_requests->clear_down(highest_down_request);
    return;
  }
  /*  If reach this point, then just go home. */
  dest_floor = home_floor;
}

void car_controller::upaccel_next_state_logic() {
  acceleration = max_accel;
  if(fabs(accel_to_stop()) >= max_accel)
    state = Updecel;
  else if(velocity >= max_speed)
    state = Uptravel;
}

void car_controller::uptravel_next_state_logic() {
  acceleration = 0;
  if(fabs(accel_to_stop()) >= max_accel)
    state = Updecel;
}

void car_controller::updecel_next_state_logic() {
  acceleration = accel_to_stop();
  if(current_floor() == dest_floor) {
    velocity = 0;
    acceleration = 0;
    state = Upstop;
  }
}

