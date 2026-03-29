#include "ReservationSystem.hpp"

const int WEEK_DAYS = 5; // Segunda à sexta
const int HOUR_SLOTS = 14; // Horários de 7h às 21h
const std::string WEEK[] = {"segunda", "terça", "quarta", "quinta", "sexta"};

ReservationSystem::ReservationSystem(int room_count, int* room_capacities) {
    this->room_count = room_count;
    this->room_capacities = room_capacities;
    // Aloca o array tridimensional de ponteiros para ReservationRequest
    this->room_schedule = new ReservationRequest***[room_count];

    for (int room = 0; room < room_count; room++) {
        room_schedule[room] = new ReservationRequest**[WEEK_DAYS];
        for (int day = 0; day < WEEK_DAYS; day++) {
            room_schedule[room][day] = new ReservationRequest*[HOUR_SLOTS](); // () inicializa todos os ponteiros com nullptr
        }
    }
}
ReservationSystem::~ReservationSystem() {
    for (int room = 0; room < room_count; room++) {
        for (int day = 0; day < WEEK_DAYS; day++) {
            for (int hour = 0; hour < HOUR_SLOTS; hour++) {
                ReservationRequest* request_ptr = room_schedule[room][day][hour];
                if (request_ptr != nullptr) {
                    int interval = request_ptr->getEndHour() - request_ptr->getStartHour();
                    delete request_ptr;
                    // Invalida todas as referências ao objeto deletado para evitar comportamento indefinido
                    for (int offset = 0; offset < interval; offset++) {
                        room_schedule[room][day][hour + offset] = nullptr;
                    }
                }
            }
            delete[] room_schedule[room][day];
        }
        delete[] room_schedule[room];
    }
    delete[] room_schedule;   
}

bool ReservationSystem::reserve(ReservationRequest request) {
    int start_hour = request.getStartHour();
    int end_hour = request.getEndHour();
    int interval = end_hour - start_hour;
    int student_count = request.getStudentCount();
    int day_index = -1;
    bool available = false;
    std::string week_day = request.getWeekday();
    ReservationRequest* request_ptr = new ReservationRequest(request);

    if (start_hour < 7 || end_hour > 21 || end_hour <= start_hour || student_count <= 0) {
        delete request_ptr;
        return available;
    }

    for (int day = 0; day < WEEK_DAYS; day++) {
        if (WEEK[day] == week_day) {
            day_index = day;
        }
    }

    for (int room = 0; room < room_count; room++) {
        if (room_capacities[room] >= student_count) {
            available = true;

            for (int hour = 0; hour < interval; hour++) {
                int hour_index = start_hour + hour - 7; // Horários começam às 7h, subtrai 7 para normalizar para índice 0–13
                if (room_schedule[room][day_index][hour_index] != nullptr) {
                    available = false;
                    break;
                }
            }

            if (available) {
                for (int hour = 0; hour < interval; hour++) {
                    int hour_index = start_hour + hour - 7;
                    room_schedule[room][day_index][hour_index] = request_ptr;
                }
                
                return available;
            }
        }
    }

    delete request_ptr;
    return available;
}
bool ReservationSystem::cancel(std::string course_name) {
    bool found = false;

    for (int room = 0; room < room_count; room++) {
        for (int day = 0; day < WEEK_DAYS; day++) {
            for (int hour = 0; hour < HOUR_SLOTS; hour++) {
                ReservationRequest* request_ptr = room_schedule[room][day][hour];

                if (request_ptr != nullptr && request_ptr->getCourseName() == course_name) {
                    int interval = request_ptr->getEndHour() - request_ptr->getStartHour();
                    delete request_ptr;
                    for (int offset = 0; offset < interval; offset++) {
                        room_schedule[room][day][hour + offset] = nullptr;
                    }

                    found = true;
                }
            }
        }
    }

    return found;
}

void ReservationSystem::printSchedule() {
    for (int room = 0; room < room_count; room++) {
        bool room_has_reservations = false;

        for (int day = 0; day < WEEK_DAYS; day++) {
            for (int hour = 0; hour < HOUR_SLOTS; hour++) {
                ReservationRequest* request_ptr = room_schedule[room][day][hour];
                if (request_ptr != nullptr) {
                    room_has_reservations = true;
                    break;
                }
            }
        }

        if (room_has_reservations) {
            std::cout << "Room " << room + 1 << std::endl;
        }
        
        for (int day = 0; day < WEEK_DAYS; day++) {
            bool day_has_reservations = false;
            std::string week_day = "";
        
            for (int hour = 0; hour < HOUR_SLOTS; hour++) {
                ReservationRequest* request_ptr = room_schedule[room][day][hour];
                if (request_ptr != nullptr) {
                    day_has_reservations = true;
                    week_day = request_ptr->getWeekday();
                    break;
                }
            }

            if (day_has_reservations) {
                std::cout << week_day << ":" << std::endl;
            }
            
            for (int hour = 0; hour < HOUR_SLOTS; hour++) {
                ReservationRequest* previous_request_ptr = room_schedule[room][day][hour - 1];
                ReservationRequest* request_ptr = room_schedule[room][day][hour];
                if (request_ptr != nullptr && (hour == 0 || request_ptr != previous_request_ptr)) {
                    int start_hour = request_ptr->getStartHour();
                    int end_hour = request_ptr->getEndHour();
                    std::string course_name = request_ptr->getCourseName();
                    std::cout << start_hour << "h~" << end_hour << "h: " << course_name << std::endl;
                }
            }
        }

        if (room_has_reservations) {
            std::cout << std::endl;
        }
    }    
}
