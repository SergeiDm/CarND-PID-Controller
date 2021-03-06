#define _USE_MATH_DEFINES

#include <uWS/uWS.h>
#include <iostream>
#include "json.hpp"
#include "PID.h"
#include <math.h>
#include <ctime>

// For convenience
using json = nlohmann::json;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
std::stringstream hasData(std::string s) {
	auto found_null = s.find("null");
	auto b1 = s.find_first_of("[");
	auto b2 = s.find_last_of("]");
	if (found_null != std::string::npos) {
		return std::stringstream();
	}
	else if (b1 != std::string::npos && b2 != std::string::npos) {
		std::stringstream tmp = std::stringstream();
		tmp.str(s.substr(b1, b2 - b1 + 1));
		return tmp;
	}
	return std::stringstream();
}


int main()
{
		uWS::Hub h;

		// Create PID controller for steering angle and speed
		PID_Angle pid_angle;
		PID_Speed pid_speed;
		
		// Initialize the pid variable.
		pid_angle.Init(0.06, 0.05, 0.06);
		pid_speed.Init(0.4, 0, 0.1);	

		// Set initial time and cte values
		int prev_time = clock();
		double prev_cte = 0.0;

		h.onMessage([&pid_angle, &pid_speed, &prev_time, &prev_cte](uWS::WebSocket<uWS::SERVER> *ws, char *data, size_t length, uWS::OpCode opCode) {
				// "42" at the start of the message means there's a websocket message event.
				// The 4 signifies a websocket message
				// The 2 signifies a websocket event
				if (length && length > 2 && data[0] == '4' && data[1] == '2') {
						auto s = hasData(std::string(data).substr(0, length));
						if (s.str() != "") {
								auto j = json::parse(s);
								std::string event = j[0].get<std::string>();
								if (event == "telemetry") {
										// j[1] is the data JSON object
										double cte = std::stod(j[1]["cte"].get<std::string>());
										double speed = std::stod(j[1]["speed"].get<std::string>());
										double angle = std::stod(j[1]["steering_angle"].get<std::string>());
										double steer_value;
										double throttle;									
										
										// Measure time and calculate difference between previous
										int time = clock();        
										double delta_time = (time - prev_time) / double(CLOCKS_PER_SEC);

										// Calculate steering angle
										pid_angle.UpdateError(cte, prev_cte, delta_time);
          steer_value = pid_angle.TotalError();
										if (steer_value > 1) {
												steer_value = 1;
										}
										else if (steer_value < -1) {
												steer_value = -1;
										}

										// Calculate speed
										pid_speed.UpdateError(cte, prev_cte, delta_time);
										throttle = pid_speed.TotalError();
										if (throttle > 1) {
												throttle = 1;
										}

										// Update previous values for cte and time
										prev_cte = cte;
										prev_time = time;
          
										// DEBUG
										std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;

										json msgJson;
										msgJson["steering_angle"] = steer_value;
										msgJson["throttle"] = throttle;
										auto msg = "42[\"steer\"," + msgJson.dump() + "]";
										std::cout << msg << std::endl;
										(*ws).send(msg.data(), msg.length(), uWS::OpCode::TEXT);
								}
						}
						else {
								// Manual driving
								std::string msg = "42[\"manual\",{}]";
								(*ws).send(msg.data(), msg.length(), uWS::OpCode::TEXT);
						}
				}
		});

		h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
				const std::string s = "<h1>Hello world!</h1>";
				if (req.getUrl().valueLength == 1)
				{
						res->end(s.data(), s.length());
				}
				else
				{
						// i guess this should be done more gracefully?
						res->end(nullptr, 0);
				}
		});

		h.onConnection([&h](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
				std::cout << "Connected!!!" << std::endl;
		});

		h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> *ws, int code, char *message, size_t length) {
				(*ws).close();
				std::cout << "Disconnected" << std::endl;
		});

		int port = 4567;
		if (h.listen("0.0.0.0", port))
		{
				std::cout << "Listening to port " << port << std::endl;
		}
		else
		{
				std::cerr << "Failed to listen to port" << std::endl;
				return -1;
		}
		h.run();
}