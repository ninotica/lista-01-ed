#include "ReservationSystem.hpp"

int main() {
    int capacities[] = {30, 50, 80};

    ReservationSystem system(3, capacities);

    ReservationRequest data_structures("Data Structures", "segunda", 7, 9, 25);
    ReservationRequest calculus("Calculus", "segunda", 13, 15, 30);
    ReservationRequest linear_algebra("Linear Algebra", "quarta", 10, 12, 35);

    system.reserve(data_structures);
    system.reserve(calculus);
    system.reserve(linear_algebra);

    system.printSchedule();

    system.cancel("Calculus");

    system.printSchedule();
    
    return 0;
}