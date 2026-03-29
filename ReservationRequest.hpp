#include <iostream>
#ifndef RESERVATIONREQUEST_HPP
#define RESERVATIONREQUEST_HPP

class ReservationRequest {

private:
    std::string course_name;    // Nome da disciplina
    std::string weekday;        // Dia da semana
    int start_hour;             // Hora de início (formato 24h)
    int end_hour;               // Hora de término (formato 24h)
    int student_count;          // Número de alunos

public:

    ReservationRequest(std::string course_name, std::string weekday, int start_hour, int end_hour, int student_count);
    ~ReservationRequest();

    /**
     * @brief Retorna o horário inicial da reserva.
     * 
     * @return Hora inicial no formato 24h.
     */
    int getStartHour();
    /**
     * @brief Retorna o horário final da reserva.
     * 
     * @return Hora final no formato 24.
     */
    int getEndHour();
    /**
     * @brief Retorna o nome da disciplina da reserva.
     * 
     * @return Nome da disciplina.
     */
    std::string getCourseName();
    /**
     * @brief Retorna o dia da semana da reserva.
     * 
     * @return Nome do dia da semana.
     */
    std::string getWeekday();
    /**
     * @brief Retorna a quantidade de alunos da reserva.
     * 
     * @return Quantidade de alunos.
     */
    int getStudentCount();
};

#endif
