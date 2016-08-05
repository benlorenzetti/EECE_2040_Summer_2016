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
  hall_buttons *interface,
  int home_floor,
  double floor_height,
  elevator_model car_model
)
: car_controller(name, interface, home_floor, floor_height, car_model)
{
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
