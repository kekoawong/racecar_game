// Kekoa Wong
// implementation of the racecar class
using namespace std;
#include "gfx.h"
#include "racecar.h"
#include <unistd.h>

racecar::racecar() {
	// declare variables
	wid = 0;
	len = 0;
	front = 0;
	back = 0;
	rside = 0;
	lside = 0;
	lane_w = 0;
	lane1_c = 0;
	lane2_c = 0;

}

racecar::~racecar() {}

racecar::racecar(double cx, double cy, double length, double width) {
	// declare variables
	wid = width;
	len = length;
	front = cy - len/2;
	back = cy + len/2;
	rside = cx + width/2;
	lside = cx - width/2;
	lane_w = width*1.1;
	lane1_c = 0;
	lane2_c = 0;
}

void racecar::set_length(double l) {
	len = l;
}

void racecar::set_width(double w) {
	wid = w;
}


void racecar::set_center(double cx, double cy) {
	front = cy - len/2;
	back = cy + len/2;
	rside = cx + wid/2;
	lside = cx - wid/2;
}

double racecar::get_front() {
	return front;
}

double racecar::get_back() {
	return back;
}

double racecar::get_lside() {
	return lside;
}

double racecar::get_rside() {
	return rside;
}

double racecar::get_lane1_c() {
	return lane1_c;
}

double racecar::get_lane2_c() {
	return lane2_c;
}

// will use gfx_line to create car
void racecar::display_car() { // needs to have window open in main driver
	double y1, y2, x1, x2, r;
	// spoiler area
	y1 = back - 0.2*len;
	gfx_line(lside, back, rside, back);
	gfx_line(lside, back, lside, y1);
	gfx_line(rside, back, rside, y1);
	gfx_line(lside, y1, rside, y1);

	// back centrifuge
	y2 = y1 - 0.2*len;
	x2 = rside - 0.35*wid;
	x1 = lside + 0.35*wid;
	gfx_line(x1, y1, x1, y2);
	gfx_line(x2, y1, x2, y2);

	// back wheels
	r = 0.13*wid;
	gfx_circle(x2 + r, y2 + r, r);
	gfx_circle(x1 - r, y2 +r, r);

	// main body
	x1 = lside + 0.25*wid;
	x2 = rside - 0.25*wid;
	y1 = front + 0.3*wid;
	gfx_line(x1, y1, x1, y2);
	gfx_line(x1, y2, x2, y2);
	gfx_line(x1, y1, x2, y1);
	gfx_line(x2, y1, x2, y2);

	// front centrifuge
	x1 = lside + 0.35*wid;
	x2 = rside - 0.35*wid;
	gfx_line(x1, front, x2, front);
	gfx_line(x1, front, x1, y1);
	gfx_line(x2, front, x2, y1);

	// front wheels
	r = 0.10*wid;
	gfx_circle(x2 + r, y1 - r, r);
	gfx_circle(x1 - r, y1 - r, r);
}

void racecar::set_lanes(double window_h, double window_w) {
	lane_w = wid*1.1;
	lane1_c = window_w/2 - lane_w/2;
	lane2_c = window_w/2 + lane_w/2;
}

void racecar::display_lanes(double window_h, double window_w, double starting_y) {
	// declare variables
	double cx = window_w/2;
	double y;
	double lane_l = window_h/10;
	lane_w = wid*1.1;
	// set the center of the lanes
	lane1_c = cx - lane_w/2;
	lane2_c = cx + lane_w/2;
	gfx_line(cx - lane_w - 2, 0, cx - lane_w - 2, window_h);
	gfx_line(cx + lane_w + 2, 0, cx + lane_w + 2, window_h);
	y = starting_y;

	// display lanes
	for (int i = 0; i < 7; i++) {
			gfx_line(cx, y, cx, y + lane_l);
			gfx_line(cx - lane_w, y, cx - lane_w, y + lane_l);
			gfx_line(cx + lane_w, y, cx + lane_w, y + lane_l);
			y = y + 2*lane_l;
			usleep(1000); 
	}
	gfx_flush();
}

