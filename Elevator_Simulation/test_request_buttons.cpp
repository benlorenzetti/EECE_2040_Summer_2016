#include "request_buttons.h"
#include <iostream>
using namespace std;

int main() {
  int skydeck_service_floors[5] = {1, 2, 50, 51, 52};
  hall_calls skydeck(skydeck_service_floors, sizeof(skydeck_service_floors));
  skydeck.request_up(1);
  skydeck.request_up(51);
  skydeck.request_down(50);
  skydeck.request_down(2);
  cout << skydeck.find_first_above(1) << endl;
  cout << skydeck.find_first_below(52) << endl;
  return 0; 
}
