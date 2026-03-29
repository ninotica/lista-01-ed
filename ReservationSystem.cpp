#include "ReservationSystem.hpp"

const std::string week[] = {"segunda", "terça", "quarta", "quinta", "sexta"};

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
                ReservationRequest* req = room_schedule[room][day][hour];
                if (req != nullptr) {
                    int interval = req->getEndHour() - req->getStartHour();
                    delete req;
                    for (int reserved_hour = 0; reserved_hour < interval; reserved_hour++) {
                        room_schedule[room][day][hour + reserved_hour] = nullptr;
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
    bool result = false;
    std::string week_day = request.getWeekday();
    ReservationRequest* req = new ReservationRequest(request);

    for (int day = 0; day < 5; day++) {
        if (week[day] == week_day) {
            day_index = day;
        }
    }

    for (int room = 0; room < room_count; room++) {
        if (room_capacities[room] >= student_count) {
            result = true;

            for (int hour = 0; hour < interval; hour++) {
                if (room_schedule[room][day_index][start_hour + hour - 7] != nullptr) {
                    result = false;
                    break;
                }
            }

            if (result) {
                for (int hour = 0; hour < interval; hour++) {
                    room_schedule[room][day_index][start_hour + hour - 7] = req;
                }
                
                return result;
            }
        }
    }

    delete req;
    return result;
}
bool ReservationSystem::cancel(std::string course_name) {
    bool result = false;

    for (int room = 0; room < room_count; room++) {
        for (int day = 0; day < 5; day++) {
            for (int hour = 0; hour < 14; hour++) {
                ReservationRequest* req = room_schedule[room][day][hour];

                if (req != nullptr && req->getCourseName() == course_name) {
                    int interval = req->getEndHour() - req->getStartHour();
                    delete req;
                    for (int reserved_hour = 0; reserved_hour < interval; reserved_hour++) {
                        room_schedule[room][day][hour + reserved_hour] = nullptr;
                    }

                    result = true;
                }
            }
        }
    }

    return result;
}

void ReservationSystem::printSchedule() {
    for (int room = 0; room < room_count; room++) {
        bool check = false;

        for (int day = 0; day < 5; day++) {
            for (int hour = 0; hour < 14; hour++) {
                ReservationRequest* req = room_schedule[room][day][hour];
                if (req != nullptr) {
                    check = true;
                    break;
                }
            }
        }

        if (check) {
            std::cout << "Room " << room + 1 << std::endl;
        }
        
        for (int day = 0; day < 5; day++) {
            check = false;
            std::string week_day = "";
        
            for (int hour = 0; hour < 14; hour++) {
                ReservationRequest* req = room_schedule[room][day][hour];
                if (req != nullptr) {
                    check = true;
                    week_day = req->getWeekday();
                    break;
                }
            }

            if (check) {
                std::cout << week_day << ":" << std::endl;
            }
            
            for (int hour = 0; hour < 14; hour++) {
                ReservationRequest* pre_req = room_schedule[room][day][hour - 1];
                ReservationRequest* req = room_schedule[room][day][hour];
                if (req != nullptr && (hour == 0 || req != pre_req)) {
                    int start_hour = req->getStartHour();
                    int end_hour = req->getEndHour();
                    std::string course_name = req->getCourseName();
                    std::cout << start_hour << "h~" << end_hour << "h: " << course_name << std::endl;
                }
            }
        }
    }    
}
