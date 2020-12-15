// Kekoa Wong
//project.cpp
// racecar game main driver
#include "gfx.h"
#include "racecar.h"
#include <stdlib.h> // srand and rand
#include <time.h> // for time

// declare function
double switch_lanes(char, double, racecar);
double lane_generation();

int main() {
	
	// declare variables
	int width = 700, height = 700;
	double car_length = 200, car_width = 150;
	char c;
	double starting_y = -height/5, vy = 2, y, x, ln, cx;
	bool loop = true;
	racecar user_car(width/2, height/2-100, car_length, car_width);
	racecar car2(-width, 5*height, car_length, car_width); // default car2 is off screen

	// open window
	gfx_open(width, height, "Racecar Game");
	gfx_color(255, 255, 255);

	// set user car initial center
	user_car.set_lanes(height, width);
	cx = user_car.get_lane1_c();
	
	while (loop) {
		gfx_clear();

		// graphics for user car
		user_car.set_center(cx, height/2+150);
		user_car.display_car();
		user_car.display_lanes(height, width, starting_y);

		// generate a new car everytime a new car goes off screen
		if (car2.get_front() > height) {
			// generate random lane
			ln = lane_generation();
			// set lane and center of the car
			if (ln == 1)
				x = user_car.get_lane1_c();
			else
				x = user_car.get_lane2_c();
			y = -car_length;
			car2.set_center(x, y);
		}

		// increment graphics of car2
		y = y + vy;
		car2.set_center(x, y);
		car2.display_car();

		// increment starting_y for lanes
		starting_y = starting_y + vy + 6;
		if (starting_y > height/10)
			starting_y = -height/10;

		// wait for event
		if (gfx_event_waiting()) {
			c = gfx_wait();
			// switch to right lane
			cx = switch_lanes(c, cx, user_car);
			// quit game
			if (c == 'q')
				loop = false;
			if (c == 'w')
				vy++;
			if (c == 's')
				vy--;
		}

		// check if user car collides with car2
		if ((user_car.get_front() < car2.get_back()) && !(user_car.get_back() < car2.get_front()) && x == cx) {
			gfx_clear();
			// reset speed
			vy = 2;
			// put car2 off screen
			y = -car_length;
			gfx_color(255, 255, 255);
			// display game over
			while (true) {
				gfx_text(width/2-30, height/2, "GAME OVER");
				gfx_text(width/2 - 100, height/2 + 20, "Press 'r' to Replay or 'q' to quit");
				if (gfx_event_waiting()) {
				 	c = gfx_wait();
				}
				if ((c == 'r') || (c == 'q'))
						break;
			}
			if (c == 'q')
				loop = false;
		}
	}

	return 0;
}

double switch_lanes(char c, double cx, racecar car) {
	// switch to right lane
	if ((c == 'd') && (cx == car.get_lane1_c())) {
		return car.get_lane2_c();
	}
	// switch to left lane
	else if ((c == 'a') && (cx == car.get_lane2_c())) {
		return car.get_lane1_c();
	}

	return cx;

}

double lane_generation() {
	// randomly generate number
	srand(time(0));
	double ln = rand() % 2 + 1;
	return ln;
}
