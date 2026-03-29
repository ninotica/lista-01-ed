#include "ReservationRequest.hpp"

ReservationRequest::ReservationRequest(std::string course_name, std::string weekday, int start_hour, int end_hour, int student_count) {
    this->course_name = course_name;
    this->weekday = weekday;
    this->start_hour = start_hour;
    this->end_hour = end_hour;
    this->student_count = student_count;
}
ReservationRequest::~ReservationRequest() {
    
}

int ReservationRequest::getStartHour() {
    return start_hour;
}
int ReservationRequest::getEndHour() {
    return end_hour;
}
std::string ReservationRequest::getCourseName() {
    return course_name;
}
std::string ReservationRequest::getWeekday() {
    return weekday;
}
int ReservationRequest::getStudentCount() {
    return student_count;
}
