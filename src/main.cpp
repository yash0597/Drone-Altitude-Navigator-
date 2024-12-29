#include <iostream>
#include "Logger.hpp"

int main()
{
    // A simple welcome message
    Logger::info("Starting HighAltitudeNavigator...");

    // For now, just demonstrate the logger
    Logger::info("This system will handle drone navigation logic.");

    // We'll eventually create objects from other modules:
    // - SensorManager
    // - PathPlanner
    // - DroneController
    // - etc.

    // Placeholder: Show usage (in the future, parse command-line args)
    std::cout << "Usage:\n"
              << "  1) The system will init sensors.\n"
              << "  2) Plan a path to a waypoint.\n"
              << "  3) Command the drone to move.\n"
              << "  4) Possibly handle collisions / flight modes.\n"
              << "  5) Enjoy a GUI or mission scripting.\n"
              << std::endl;

    // End of demonstration
    Logger::info("Exiting HighAltitudeNavigator (no real logic yet).");

    return 0;
}
