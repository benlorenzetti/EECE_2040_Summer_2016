#include "passengers_cars_and_queues.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <time.h>   // for time() to init rand
#include <stdlib.h> // for rand(), srand()
using namespace std;

void fill_new_passenger(passenger *p, int bottom_floor, int top_floor) {
  static bool random_init;
  static int id_count;
  // If the random number generator has not been initialized, do so
  if(!random_init) {
    random_init = true;
    srand(time(NULL));
  }
  int number_of_floors = top_floor - bottom_floor;
  // Generate a random, relative origin floor and different dest floor
  int origin, dest;
  origin = rand() % number_of_floors;
  do {}
  while((dest = rand() % number_of_floors) == origin);
  // Fill in the passenger structure
  p->id = id_count++;
  p->origin_floor = origin + bottom_floor;
  p->dest_floor = dest + bottom_floor;
  p->request_time = 0;
  p->queue_time = 0;
  p->travel_time = 0;
}

elevator_car::elevator_car(
  string name,
  hall_queues *interface,
  int home_floor,
  double floor_height,
  elevator_model car_model
)
: car_controller(name, static_cast<hall_buttons*>(interface), home_floor, floor_height, car_model)
{
  interface->register_car_function_for_car_constructor(this);
  onboard.clear();
  onboard_soft_cap = (int) car_model.max_cargo_mass / 90.0;
}

bool elevator_car::full() {
  return (onboard.size() >= onboard_soft_cap);
}

bool elevator_car::empty() {
  return (onboard.empty());
}

bool elevator_car::up_arrival(int floor_number) {
  return (state == Upstop && floor_number == current_floor());
}

bool elevator_car::down_arrival(int floor_number) {
  return (state == Downstop && floor_number == current_floor());
}

void elevator_car::board(passenger person) {
  person.queue_time = global_time - person.request_time;
  onboard.push_back(person);
  stop_requests.request_stop(person.dest_floor);
}

int elevator_car::disembark(deque<passenger> *passenger_history) {
  int count = 0;
  // No one can disembark when doors are closed
  if(state != Upstop && state != Downstop)
    return count;
  // Search onboard passengers for those destined to current floor
  vector<passenger>::iterator it = onboard.end();
  if(!onboard.size())
    return count;
  while(it-- != onboard.begin()) {
    if(current_floor() == (*it).dest_floor) {
       count++;
       if(passenger_history)
         passenger_history->push_back(*it);
       onboard.erase(it);
    }
  }
  return count;
}

hall_queues::hall_queues(int bottom_floor, int top_floor)
: hall_buttons(bottom_floor, top_floor)
{
  for(int i = bottom_floor; i <= top_floor; i++) {
    up_queues.push_back(queue<passenger>());
    down_queues.push_back(queue<passenger>());
  }
}

void hall_queues::all_floors_push_passenger(passenger new_pass) {
  int rel_origin, rel_dest;
  rel_origin = new_pass.origin_floor - get_bottom();
  // Add passenger to the correct queue and
  // Press the correct hall call button to summon a car
  if(new_pass.dest_floor < new_pass.origin_floor) {
    down_queues.at(rel_origin).push(new_pass);
    request_down(new_pass.origin_floor);
  }
  else {
    up_queues.at(rel_origin).push(new_pass);
    request_up(new_pass.origin_floor);
  }
}

void hall_queue::all_floors_try_to_board() {
  // Outer Loop is for each floor
  int floor_index, floor
  for(floor = get_bottom(); floor <= get_top(); floor++) {
    floor_index = floor - get_bottom();
    // Inner Loop is for each car
    int car_index;
    for(car_index = 0; car_index < cars.size(); car_index++) {
      if(cars[car_index]->up_arrival()) {
        while(!cars[car_index]->full() && !up_queues[floor_index].empty()) {
          cars[cars_index]->board(up_queues[floor_index].front());
          up_queues[floor_index].pop();
        }
        // If the car was too full, call another car
        if(!up_queues[floor_index].empty())
          request_up(floor);
      }
      if(cars[car_index]->down_arrival()) {
        while(!cars[car_index]->full() && !down_queues[floor_index].empty()) {
          cars[car_index]->board(down_queues[floor_index].front());
          down_queues[floor_index].pop();
        }
        // If the car was too full, call another car
        if(!down_queues[floor_index].empty())
          request_down(floor);
      }
    }// end inner loop (for each car)
  }  // end outer loop (for each floor)
  
}

void hall_queues::register_car_function_for_car_constructor(elevator_car *car) {
  cars.push_back(car);
}
