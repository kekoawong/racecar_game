// Kekoa Wong
// racecar.h
// racecar class

using namespace std;
#include "gfx.h"

class racecar {
	public:
		racecar();
		racecar(double, double, double, double);
		~racecar();
		void set_length(double);
		void set_width(double);
		void set_center(double, double);
		double get_front();
		double get_back();
		double get_lside();
		double get_rside();
		double get_lane1_c();
		double get_lane2_c();
		void display_car();
		void set_lanes(double, double);
		void display_lanes(double, double, double);

	private:
		double wid;
		double len;
		double front;
		double back;
		double lside;
		double rside;
		double lane_w;
		double lane1_c;
		double lane2_c;
};
