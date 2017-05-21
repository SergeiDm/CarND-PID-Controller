#include "PID.h"
#include <math.h>

using namespace std;

PID_Angle::PID_Angle() {
  i_error = 0;
}

PID_Angle::~PID_Angle() {}

void PID_Angle::Init(double p, double i, double d) {
  Kp = p;
  Ki = i;
  Kd = d;
}

void PID_Angle::UpdateError(double cte, double prev_cte, double delta_time) {
  p_error = cte;
		i_error += cte * delta_time;
  d_error = (cte - prev_cte) / delta_time;
}

double PID_Angle::TotalError() {
  return (-Kp * p_error - Ki * i_error - Kd * d_error);
}

PID_Speed::PID_Speed() {
		i_error = 0;
}

PID_Speed::~PID_Speed() {}

void PID_Speed::Init(double p, double i, double d) {
		Kp = p;
		Ki = i;
		Kd = d;
}

void PID_Speed::UpdateError(double cte, double prev_cte, double delta_time) {
	 p_error = cte;
		i_error += cte * delta_time;
		d_error = (cte - prev_cte) / delta_time;
}

double PID_Speed::TotalError() {
		double sum = 0;
		if (p_error != 0) {
				sum += Kp / fabs(p_error);
		}
		if (i_error != 0) {
				sum += Ki / fabs(i_error);
		}
		if (d_error != 0) {
				sum += Kd / fabs(d_error);
		}

		return sum;
}
