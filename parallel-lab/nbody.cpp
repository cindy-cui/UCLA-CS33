/**
 * N-body simulation code for CS 33 (UCLA), Spring 2021
 * Author: Eric Newberry <enewberry@cs.ucla.edu>
 */

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include <omp.h>

struct Body
{
  double x;
  double y;
  double mass;
  double f_x = 0.0;
  double f_y = 0.0;
};

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "Usage:" << std::endl;
    std::cerr << argv[0] << " [input]" << std::endl;
    return 1;
  }

  // Open input file
  std::ifstream inputFile(argv[1]);
  if (!inputFile.good()) {
    std::cerr << "Could not open specified file" << std::endl;
    return 2;
  }

  // Load simulation constants
  double timestepSeconds;
  double gravityMs2;
  size_t nTimesteps;
  size_t nBodies;
  inputFile >> timestepSeconds >> gravityMs2 >> nTimesteps >> nBodies;
  if (!inputFile.good()) {
    std::cerr << "Unable to load simulation constants from file" << std::endl;
    inputFile.close();
    return 2;
  }

  // Load bodies (don't try to make this parallel!)
  Body* bodies = (Body*)malloc(nBodies * sizeof(Body));
  for (size_t i = 0; i < nBodies; i++) {
    // Format: start_x start_y mass_kg
    inputFile >> bodies[i].x >> bodies[i].y >> bodies[i].mass;
    if (!inputFile.good()) {
      std::cerr << "Unable to load bodies from file" << std::endl;
      free(bodies);
      inputFile.close();
      return 2;
    }
  }
  inputFile.close();

  double sumAccelerationX = 0.0;
  double sumAccelerationY = 0.0;
  double sumDisplacementX = 0.0;
  double sumDisplacementY = 0.0;

  // Run simulation
  for (size_t ts = 0; ts < nTimesteps; ts++) {
    std::cerr << "Timestamp " << ts << " (Time=" << (ts * timestepSeconds) << "s)" << std::endl;

    // Compute stage
    for (size_t body = 0; body < nBodies; body++) {
      bodies[body].f_x = 0.0;
      bodies[body].f_y = 0.0;

      // Calculate force vector based on every other body
      for (size_t otherBody = 0; otherBody < nBodies; otherBody++) {
        if (body == otherBody) {
          // Skip ourselves
          continue;
        }

        double dist = sqrt(pow(bodies[body].x - bodies[otherBody].x, 2.0) + pow(bodies[body].y - bodies[otherBody].y, 2.0));
        double f_i = (gravityMs2 * bodies[body].mass * bodies[otherBody].mass) / dist * timestepSeconds;
        double theta = atan((bodies[body].y - bodies[otherBody].y) / (bodies[body].x - bodies[otherBody].x));
        double f_xi = f_i * cos(theta);
        double f_yi = f_i * sin(theta);
        bodies[body].f_x += f_xi;
        bodies[body].f_y += f_yi;
      }
    }

    // Movement stage
    for (size_t body = 0; body < nBodies; body++) {
      // Now calculate the acceleration on each axis and the associated displacement
      double a_x = bodies[body].f_x / bodies[body].mass;
      double a_y = bodies[body].f_y / bodies[body].mass;
      double d_x = 1.0 / 2.0 * a_x * pow(timestepSeconds, 2.0);
      double d_y = 1.0 / 2.0 * a_y * pow(timestepSeconds, 2.0);

      // Apply displacement to body positions
      bodies[body].x += d_x;
      bodies[body].y += d_y;

      // Add to sums
      sumAccelerationX += fabs(a_x);
      sumAccelerationY += fabs(a_y);
      sumDisplacementX += fabs(d_x);
      sumDisplacementY += fabs(d_y);
    }
  }

  // Compute averages
  double avgAccelerationX = sumAccelerationX / (double)nBodies / (double)nTimesteps;
  double avgAccelerationY = sumAccelerationY / (double)nBodies / (double)nTimesteps;
  double avgDisplacementX = sumDisplacementX / (double)nBodies / (double)nTimesteps / (double)timestepSeconds;
  double avgDisplacementY = sumDisplacementY / (double)nBodies / (double)nTimesteps / (double)timestepSeconds;

  // Output final positions of bodies (don't try to make this parallel!)
  for (size_t i = 0; i < nBodies; i++) {
    std::cout << bodies[i].x << "\t" << bodies[i].y << std::endl;
  }
  // Output averages
  std::cout << "avg acceleration=(x=" << avgAccelerationX << " m/s^2, y=" << avgAccelerationY << " m/s^2)" << std::endl;
  std::cout << "avg displacement/second=(x=" << avgDisplacementX << " m, y=" << avgDisplacementY << " m)" << std::endl;

  free(bodies);
  return 0;
}
