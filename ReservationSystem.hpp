#include "ReservationRequest.hpp"
#ifndef RESERVATIONSYSTEM_HPP
#define RESERVATIONSYSTEM_HPP

class ReservationSystem {

private:
    int room_count;                         // Número de salas
    int* room_capacities;                   // Capacidade de cada sala
    ReservationRequest**** room_schedule;   // Grade de reservas [sala][dia][hora]
    
public:

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    /**
     * @brief Tenta reservar uma sala para a requisição dada.
     * 
     * @param request Requisição com dia, horários, nome da disciplina e número de alunos.
     * @return true se a reserva foi realizada, false caso contrário.
     */
    bool reserve(ReservationRequest request);
    /**
     * @brief Tenta cancelar a reserva de uma disciplina.
     * 
     * @param course_name Nome da disciplina a ser cancelada.
     * @return true se o cancelamento foi realizado, false caso contrário.
     */
    bool cancel(std::string course_name);

    /**
     * @brief Exibe a grade atual de reservas organizadas por sala.
     */
    void printSchedule();
};

#endif
