/*  request_buttons.cpp
 *  Ben Lorenzetti
 *  EECE 2040 Summer 2016
*/

#include "request_buttons.h"
#include <set>
using namespace std;

hall_calls::hall_calls(const int* floors_list, unsigned int list_size) {
  serviced_floors.clear();
  up_calls.clear();
  down_calls.clear();
  for(int i = 0; i < list_size; i++)
    serviced_floors.insert(floors_list[i]);
}

void hall_calls::request_up(int floor_number) {
  // Check that the floor is serviced
  if(serviced_floors.find(floor_number) == serviced_floors.end()) {
    // error handling
  }
  up_calls.insert(floor_number);
}

void hall_calls::request_down(int floor_number) {
  // Check that the floor is serviced
  if(serviced_floors.find(floor_number) == serviced_floors.end()) {
    // error handling
  }
  down_calls.insert(floor_number);
}

void hall_calls::clear_up(int floor_number) {
  set<int>::iterator it;
  it = up_calls.find(floor_number);
  if(it != up_calls.end())
    up_calls.erase(it);
}

void hall_calls::clear_down(int floor_number) {
  set<int>::iterator it;
  it = down_calls.find(floor_number);
  if(it != down_calls.end())
    down_calls.erase(it);
}

int hall_calls::find_first_above(int floor_number) {
  set<int>::iterator it;
  it = up_calls.begin();
  while(it != up_calls.end() && *it <= floor_number)
    it++;
  if(it == up_calls.end())
    return floor_number;
  else
    return *it;
}

int hall_calls::find_first_below(int floor_number) {
  set<int>::iterator it;
  it = down_calls.end();
  do {
    it--;
  } while (it != down_calls.begin() && *it >= floor_number);
  if(*it < floor_number)
    return *it;
  else
    return floor_number;
}

int hall_calls::get_service_distance(int origin, int dest) {
  set<int>::iterator origin_it, dest_it;
  origin_it = serviced_floors.find(origin);
  dest_it = serviced_floors.find(dest);
  if(origin_it == serviced_floors.end() || dest_it == serviced_floors.end())
    return 0; // trip cannot be serviced by this set of elevators
  int distance = 0;
  while(origin_it != dest_it)
    origin_it++, distance++;
  return distance;
}
