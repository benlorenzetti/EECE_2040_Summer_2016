/*  passengers_cars_and_queues.h
 ********************************************************************
 *  Passengers and Machine Wrapper Classes
 ********************************************************************
 *  There are three machines in the elevator problem that fit
 *  perfectly with OOP: elevator car controllers (car_controller),
 *  hall call buttons (call_buttons) and elevator destination buttons
 *  (stop_buttons). The car controller has a internal state
 *  machine, control system variables like position and velocity,
 *  and functions for adding and removing cargo weight.
 *  The button objects have functions for pressing buttons and for
 *  car controllers to clear them, and a car controller is connected
 *  to a set of hall buttons and interior destination buttons. 
 *  
 *  However modeling the movement of passengers is not so easy to do
 *  in a modular way. For example, an elevator car could have
 *  a container of passengers, but then elevator would depend on
 *  the definition of passenger, which it doesn't in real life.
 *
 *  Hence this header file. It includes car_controller, call_buttons,
 *  and dest_buttons from their own files and builds wrapper classes
 *  around them that make writing simulation easier.
*/
#include "car_controller.h"
#include "request_buttons.h"
/*
 *  A passenger struct contains information which is relevent to the
 *  simulation, such as origin_floor, dest_floor, request_time,
 *  queue_time, and travel_time.
 *
 *  An elevator_car object wraps a car_controller machine but also
 *  has a container for passengers, a passenger capacity (over top of
 *  the machine's mass capacity), and functions for boarding,
 *  disembarking, up-arrival lights, down-arrival lights, etc.
 *
 *  A hall_queues object wraps a hall_buttons machine and any number
 *  of elevator_cars. It implements separate queues of passengers at
 *  each level serviced by the machine.
 *  Operations include adding new passengers and simulating its
 *  elevator cars.
*/

#include <string>
#include <queue>
#include <deque>
#include <vector>

typedef struct {
    int id;
    int origin_floor;
    int dest_floor;
    double request_time;
    double queue_time;
    double travel_time;
} passenger;

/*  Initialize a passenger structure with random origin & dest floors
    @param1: ptr to passenger struct to initialize 
    @param2: bottom floor number
    @param3: top floor number                                      */
void fill_new_passenger(passenger *, int , int);

class hall_queues; // forward declaration...

class elevator_car : public car_controller {
  private:
    std::vector<passenger> onboard;
    int onboard_soft_cap;
  public:
    elevator_car(
      std::string name, // name for this car
      hall_queues *,    // set of vertically repeating hall queues for this car
      int,              // the home floor
      double,           // floor height
      elevator_model car_model // machine specs such as max speed, max mass, etc.
    );
    bool full();  // is there room for more passengers?
    bool empty(); // is the car currently empty?
    bool up_arrival(int); // is car boarding at <param1> floor and going up?
    bool down_arrival(int); // is car boarding at <param1> and going down?
    void board(passenger); // copy <param1> to list of passengers in elevator
    int disembark(std::deque<passenger> *);
};

class hall_queues : public hall_buttons {
  public:
    hall_queues(int, int);
    /*  Push a new passenger to the back of their origin_floors queue
        @param1: passenger to copy                                 */
    void all_floors_push_passenger(passenger);
    /*  Iterate through all of the registered elevator cars and pop
        people off the queue where car is stopped and traveling in
        the correct direction. If queue is not completely emptied
        into a stopped car, reactivate the call button.            */
    void all_floors_try_to_board();
    void register_car_function_for_car_constructor(elevator_car *);
  private:
    std::vector<elevator_car *> cars;
    std::vector<std::queue<passenger> > up_queues;
    std::vector<std::queue<passenger> > down_queues;
};
