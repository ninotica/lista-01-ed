#include "ReservationSystem.hpp"

int main() {
    int capacities[] = {30, 50, 80};

    ReservationSystem system(3, capacities);

    ReservationRequest data_structure("Data Structure", "segunda", 7, 9, 25);
    ReservationRequest calculus("Calculus", "segunda", 13, 15, 30);
    ReservationRequest linear_algebra("Linear Algebra", "quarta", 10, 12, 35);
    ReservationRequest artificial_intelligence("Artificial Intelligence", "segunda", 11, 13, 35);
    ReservationRequest machine_learning("Machine Learning", "segunda", 13, 15, 55);
    ReservationRequest analytic_geometry("Analytic Geometry", "quinta", 14, 16, 85);
    ReservationRequest database("Database", "segunda", 12, 14, 35);

    system.reserve(data_structure);
    system.reserve(calculus);
    system.reserve(linear_algebra);
    system.reserve(artificial_intelligence);
    system.reserve(machine_learning);
    

    system.printSchedule();

    system.reserve(analytic_geometry);
    system.reserve(database);

    system.printSchedule();

    system.cancel("Calculus");

    system.printSchedule();
    
    return 0;
}