#ifndef PID_H
#define PID_H

class PID_Angle {
public:

  // Errors
  double p_error;
  double i_error;
  double d_error;

  // Coefficients
  double Kp;
  double Ki;
  double Kd;

  // Constructor
  PID_Angle();

  // Destructor
  virtual ~PID_Angle();

  // Initialize PID
  void Init(double p, double i, double d);

  // Update the PID error variables given cross track error
  void UpdateError(double cte, double prev_cte, double delta_time);

  // Calculate the total PID error
		double TotalError();
};

class PID_Speed {
public:

		// Errors
		double p_error;
		double i_error;
		double d_error;

		// Coefficients
		double Kp;
		double Ki;
		double Kd;

		// Constructor
		PID_Speed();

		// Destructor
		virtual ~PID_Speed();

		// Initialize PID
		void Init(double p, double i, double d);

		// Update the PID error variables given cross track error
		void UpdateError(double cte, double prev_cte, double delta_time);

		// Calculate the total PID error
		double TotalError();
};

#endif /* PID_H */
