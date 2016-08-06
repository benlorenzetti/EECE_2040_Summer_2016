/*  request_buttons.cpp
 *  Ben Lorenzetti
 *  EECE 2040 Summer 2016
*/

#include "request_buttons.h"
#include <set>
using namespace std;

hall_buttons::hall_buttons(int bottom_floor, int top_floor) {
  serviced_floors.clear();
  up_calls.clear();
  down_calls.clear();
  for(int i = bottom_floor; i <= top_floor; i++)
    serviced_floors.insert(i);
}

void hall_buttons::request_up(int floor_number) {
  // Check that the floor is serviced
  if(serviced_floors.find(floor_number) == serviced_floors.end()) {
    // error handling
  }
  up_calls.insert(floor_number);
}

void hall_buttons::request_down(int floor_number) {
  // Check that the floor is serviced
  if(serviced_floors.find(floor_number) == serviced_floors.end()) {
    // error handling
  }
  down_calls.insert(floor_number);
}

void hall_buttons::clear_up(int floor_number) {
  set<int>::iterator it;
  it = up_calls.find(floor_number);
  if(it != up_calls.end())
    up_calls.erase(it);
}

void hall_buttons::clear_down(int floor_number) {
  set<int>::iterator it;
  it = down_calls.find(floor_number);
  if(it != down_calls.end())
    down_calls.erase(it);
}

int hall_buttons::find_first_above(int floor_number) {
  set<int>::iterator it;
  it = up_calls.begin();
  while(it != up_calls.end() && *it <= floor_number)
    it++;
  if(it == up_calls.end())
    return floor_number;
  else
    return *it;
}

int hall_buttons::find_first_below(int floor_number) {
  set<int>::iterator it;
  it = down_calls.end();
  if(it == down_calls.begin())
    return floor_number;
  do {
    it--;
  } while (it != down_calls.begin() && *it >= floor_number);
  if(*it < floor_number)
    return *it;
  else
    return floor_number;
}

int hall_buttons::find_highest_above(int floor_number) {
  set<int>::iterator it;
  if((it = down_calls.end()) == down_calls.begin())
    return floor_number;
  it--;
  if(*it > floor_number)
    return *it;
  else
    return floor_number;
}

int hall_buttons::find_lowest_below(int floor_number) {
  set<int>::iterator it;
  it = up_calls.begin();
  if(it == up_calls.end())
    return floor_number;
  else
    return *it;
}

int hall_buttons::get_service_distance(int origin, int dest) {
  set<int>::iterator origin_it, dest_it;
  origin_it = serviced_floors.find(origin);
  dest_it = serviced_floors.find(dest);
  if(origin_it == serviced_floors.end() || dest_it == serviced_floors.end())
    return 0; // trip cannot be serviced by this set of elevators
  int distance = 0;
  if(origin < dest) {
    while(origin_it != dest_it)
      origin_it++, distance++;
  }
  else {
    while(origin_it != dest_it)
      dest_it++, distance++;
  }
  return distance;
}

int hall_buttons::get_top() {
  set<int>::iterator it = serviced_floors.end();
  return *(--it);
}

int hall_buttons::get_bottom() {
  set<int>::iterator it = serviced_floors.begin();
  return *it;
}

dest_buttons::dest_buttons() {
  stop_requests.clear();
}

void dest_buttons::request_stop(int floor_number) {
  stop_requests.insert(floor_number);
}

void dest_buttons::clear_all() {
  stop_requests.clear();
}

void dest_buttons::clear(int floor_number) {
  set<int>::iterator it;
  if((it = stop_requests.find(floor_number)) != stop_requests.end());
    stop_requests.erase(it);
}

int dest_buttons::find_first_below(int floor_number) {
  set<int>::iterator it;
  it = stop_requests.end();
  if(it == stop_requests.begin())
    return floor_number;
  do {
    it--;
  } while (it != stop_requests.begin() && *it >= floor_number);
  if(*it < floor_number)
    return *it;
  else
    return floor_number;
 
}

int dest_buttons::find_first_above(int floor_number) {
  set<int>::iterator it;
  it = stop_requests.begin();
  while(it != stop_requests.end() && *it <= floor_number)
    it++;
  if(it == stop_requests.end())
    return floor_number;
  else
    return *it;
}


