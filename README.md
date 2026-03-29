# Sistema de Reserva de Salas

Sistema de gerenciamento de reservas de salas de aula desenvolvido em C++. Permite reservar, cancelar e visualizar a grade de ocupação de salas para disciplinas ao longo da semana útil.

---

## Compilação

Utilize o `g++` com o padrão C++11 ou superior:

```bash
g++ -std=c++11 main.cpp ReservationRequest.cpp ReservationSystem.cpp -o reservation_system
```

---

## Execução

```bash
./reservation_system
```

---

## Organização interna dos dados

A grade de reservas é representada por um array tridimensional de ponteiros:

```
room_schedule[sala][dia][hora]
```

- **sala** — índice de 0 a `room_count - 1`
- **dia** — índice de 0 a 4, correspondendo a segunda a sexta-feira
- **hora** — índice de 0 a 13, correspondendo ao intervalo de 7h às 21h (hora real − 7 = índice)

Cada posição do array armazena um ponteiro para um objeto `ReservationRequest`. Reservas que ocupam múltiplos horários fazem todas as posições do intervalo apontarem para o **mesmo objeto**, evitando duplicação de dados. Ao cancelar ou destruir uma reserva, o objeto é deletado e todas as referências são invalidadas com `nullptr`.

```
Exemplo: disciplina das 7h às 9h na sala 0, segunda-feira

room_schedule[0][0][0] → ReservationRequest*
room_schedule[0][0][1] → ReservationRequest*  (mesmo objeto)
room_schedule[0][0][2] → nullptr
...
```

---

## Estrutura dos arquivos

| Arquivo                  | Descrição                                              |
|--------------------------|--------------------------------------------------------|
| `main.cpp`               | Exemplo de uso do sistema                              |
| `ReservationRequest.hpp` | Declaração da classe que representa uma reserva        |
| `ReservationRequest.cpp` | Implementação dos métodos de `ReservationRequest`      |
| `ReservationSystem.hpp`  | Declaração da classe que gerencia as reservas          |
| `ReservationSystem.cpp`  | Implementação dos métodos de `ReservationSystem`       |