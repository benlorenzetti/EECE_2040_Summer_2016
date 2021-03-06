/*  car_controller.h
 ********************************************************************
*/

#ifndef CAR_CONTROLLER_H
#define CAR_CONTROLLER_H

#include <string>
#include "request_buttons.h"
#include <limits.h>

const int POSITION_BETWEEN_FLOORS = INT_MIN;
// assumption made that INT_MIN is not a valid floor in a building

enum control_state {
  Home, Upstop, Upstart, Upaccel, Uptravel, Updecel,
  Downstop, Downstart, Downaccel, Downtravel, Downdecel
};
std::string state_string(control_state);

typedef struct {
    const double empty_mass;
    const double max_cargo_mass;
    const double max_accel;
    const double max_speed;
    const double stop_time;
    const double stop_tolerance;   
} elevator_model;

class car_controller {
  protected:
    // Physical Model Variables
    double mass;         // kilograms
    double position;     // meters
    double velocity;     // meters/sec
    double acceleration; // meters/sec^2
    // Control Logic Variables
    control_state state;
    hall_buttons* call_requests;
    dest_buttons stop_requests;
    const int home_floor;
    int dest_floor;
    double timer;
    const double floor_height;
    // Elevator Class/Model Variables
    std::string name;
    elevator_model car_model;
    /* stop_tolerance = maximum allowable height difference between
       hallway floor and car floor when stopped, in meters */
  public:
    // Global time is useful for printing debug messages for the state
    // machine. Nothing is harmed if someone reaches in and changes it.
    static double global_time;
    // Declare an Elevator Controller
    car_controller(
      std::string, // name
      hall_buttons *, // the building interface for this car
      int,    // home floor
      double, // floor height (m)
      elevator_model car_model
    );
    // Simulate the elevator's motion and controller state for an
    // increment of time. 
    void simulate(
      double, // time increment to advance this car
      bool    // select whether you want a printout of activity
    );
    //  Test if car's position is within stop_tolerance of a floor
    int current_floor();
                  // returns a floor number or CAR_NOT_AT_A_FLOOR
    //  Get the torque being applied to the motor by controller (N*m)
    double get_torque();
    /*  Get the acceleration rate required in order to slow the car
     *  at a constant rate such that the car reaches its dest_floor
     *  with exactly zero velocity: a smooth stop. */  
    double accel_to_stop();
    // Get car direction, if doors are open, and mass of people onboard
    control_state get_state();
    void load_cargo(double);
    void remove_cargo(double);
    
    // State Machine Next-State Functions
    void home_next_state_logic();
    void upstop_next_state_logic();
    void upstart_next_state_logic();
    void upaccel_next_state_logic();
    void uptravel_next_state_logic();
    void updecel_next_state_logic();
    void downstop_next_state_logic();
    void downstart_next_state_logic();
    void downaccel_next_state_logic();
    void downtravel_next_state_logic();
    void downdecel_next_state_logic();
};

#endif
