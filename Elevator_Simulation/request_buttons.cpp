/*  request_buttons.cpp
*/

#include "request_buttons.h"
#include <set>
using std;

hall_calls::hall_calls(unsigned int num_of_floors, const int* floors_list) {
  serviced_floors.clear();
  for(int i = 0; i < num_of_floors; i++)
    serviced_floors.insert(floors_list[i]);
}

void hall_calls::request_up(int floor_number)
  // Check that the floor is serviced
  if(serviced_floors.find(floor_number) == set::end) {
    // error handling
  }
  up_calls.insert(floor_number);
}

void hall_calls::request_down(int floor_number)
  // Check that the floor is serviced
  if(serviced_floors.find(floor_number) == set::end) {
    // error handling
  }
  down_calls.insert(floor_number);
}

void hall_calls::clear_up(int floor_number) {
  set<int>::iterator it;
  it = up_calls.find(floor_number);
  if(it != set::end)
    up_calls.clear(it);
}

void hall_calls::clear_down(int floor_number) {
  set<int>::iterator it;
  it = down_calls.find(floor_number);
  if(it != set::end)
    down_calls.clear(it);
}

int hall_calls::find_first_above(int floor_number) {
  set<int>::iterator it;
  it = up_calls.begin();
  while(it != set::end && *it <= floor_number)
    it++;
  if(it == set::end)
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

int get_service_distance(int origin, int dest) {
  set<int>::iterator origin_it, dest_it;
  origin_it = serviced_floors.find(origin);
  dest_it = serviced_floors.find(dest);
  if(origin_it == set::end || dest_it == set::end)
    return 0; // trip cannot be serviced by this set of elevators
  int distance = 0;
  while(origin_it != dest_it)
    origin_it++, distance++;
  return distance;
}
