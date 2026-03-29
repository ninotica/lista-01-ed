#include "ReservationSystem.hpp"

ReservationSystem::ReservationSystem(int room_count, int* room_capacities) {
    this->room_count = room_count;
    this->room_capacities = room_capacities;
    this->room_schedule = new ReservationRequest***[room_count];

    for (int room = 0; room < room_count; room++) {
        room_schedule[room] = new ReservationRequest**[5];
        for (int day = 0; day < 5; day++) {
            room_schedule[room][day] = new ReservationRequest*[14]();
        }
    }
}
ReservationSystem::~ReservationSystem() {
    for (int room = 0; room < room_count; room++) {
        for (int day = 0; day < 5; day++) {
            for (int hour = 0; hour < 14; hour++) {
                delete[] room_schedule[room][day][hour];
            }
            delete[] room_schedule[room][day];
        }
        delete[] room_schedule[room];
    }
    delete[] room_schedule;

}

bool ReservationSystem::reserve(ReservationRequest request) {
    int interval = request.getEndHour() - request.getStartHour();
    int day_index = -1;
    bool result = false;
    std::string week[] = {"segunda", "terça", "quarta", "quinta", "sexta"};
    ReservationRequest* req = new ReservationRequest(request);

    for (int day = 0; day < 5; day++) {
        if (week[day] == request.getWeekday()) {
            day_index = day;
        }
    }

    for (int room = 0; room < room_count; room++) {
        if (room_capacities[room] >= request.getStudentCount()) {
            result = true;

            for (int hour = 0; hour < interval; hour++) {
                if (room_schedule[room][day_index][request.getStartHour() + hour - 7] != nullptr) {
                    result = false;
                    break;
                }
            }

            if (result) {
                for (int hour = 0; hour < interval; hour++) {
                    room_schedule[room][day_index][request.getStartHour() + hour - 7] = req;
                }
                
                return result;
            }
        }
    }

    delete req;
    return result;
}
bool ReservationSystem::cancel(std::string course_name) {
    
}

void ReservationSystem::printSchedule() {
    
}
