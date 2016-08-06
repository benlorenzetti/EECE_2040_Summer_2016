/*  request_buttons.h
 ********************************************************************
 *  Hall Calls, Serviced Floors, and Stop Requests                  *
 ********************************************************************
 *  The tallest skyscrapers have multiple sets of elevators, and some
 *  sets may only serve select floors. For example, the John Hancock
 *  building in Chicago has a whole hallway of elevators that only
 *  serve the ground floor and the skydeck.
 *  
 *  Hall buttons and car destination buttons provide the interface
 *  between passengers and the elevator system, and they
 *  are the glue that bind multiple elevators that service the same
 *  floors together and that limit which floors a car may stop. 
 *  
 *  To model a building, you need a hall_buttons object for each set
 *  of equivalent elevators (those which service the exact same
 *  floors). A hall call object contains three binary tree structures
 *  with nodes containing floor numbers. The three trees are for:
 *  (1) up_calls, (2) down_calls, and (3) serviced_floors.
 *
 *  There is also a dest_buttons class to model the buttons inside
 *  the elevator. It has button trees for requested stops.
*/

#ifndef REQUEST_BUTTONS_H
#define REQUEST_BUTTONS_H

#include <set>

class hall_buttons {
  public:
    /*  param1: lowest floor number
        param2: top floor number */
    hall_buttons(int, int);
    /*  The next four functions allow humans and car_controllers to
        interface with the internal sets of service requests.
        @param1: a floor number */
    void request_up(int);
    void request_down(int);
    void clear_up(int);
    void clear_down(int);
    /*  Gets the floor number of the first active up request above
        the current floor, or current floor if no such requests.
        @param1: current floor */
    int find_first_above(int);
    /*  Gets the floor number of the first active down request below
        the current floor, or current floor if no such requests.
        @param1: current floor */
    int find_first_below(int);
    /*  Gets the floor of the highest down request above the current
        floor, or the current floor if no such requests exist.
        @param1: current floor */
    int find_highest_above(int);
    /*  Gets the floor of the lowest up request also below the
        current floor, or current floor if no such requests exist.
        @param1: current floor */
    int find_lowest_below(int);
    int get_service_distance(int, int);
/*  Takes in two floor numbers and returns the number of potential
    stops between these two floors. Returns zero if one or both
    floors is not serviced by this set of elevators.  
*/
    int get_bottom();
    int get_top();
//  Return the bottom and top floors in serviced_floors
  private:
    std::set<int> up_calls;
    std::set<int> down_calls;
    std::set<int> serviced_floors;
};

class dest_buttons {
  public:
    dest_buttons();
    void request_stop(int);   // (1) floor number
    void clear(int);          // (2) floor number
    void clear_all();         // clears stop_requests
    int find_first_above(int);
//  (1) current floor; (return) nearest floor above (1) in stop_req
    int find_first_below(int);
//  (1) current floor; (return) nearest floor below (1) in stop_req
  private:
    std::set<int> stop_requests;
};

#endif
