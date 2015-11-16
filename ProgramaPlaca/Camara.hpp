/**
Escola Politecnica da Universidade de Sao Paulo
0323100 - Introducao a Engenharia Eletrica - 2015

Projeto de Câmara Térmica

Grupo 5
    Daniel Nery Silva de Oliveira - 9349051
    Daniel Seiji Tsutsumi         - 9349005
    Mariana Sartori Testa         - 9348773
    Mateus Almeida Barbosa        - 9349072
*/

#pragma once

#include "mbed.h"
#include "BufferedSerial.h"

namespace IntroEE {
    class Camara {
    private:
        AnalogIn         LM35;         // Sensor de Temperatura

        DigitalOut       dir1;         // Direcoes Ventoinha
        DigitalOut       dir2;

        DigitalOut       buzzer;       // buzzer
        DigitalOut       rele;         // Rele que ativa o resistor

        PwmOut           fan;          // Ventoinha

        // Serial para comunicacao com o computador
        //
        // Envia mensagens seguidas de caracteres identificadores e \r\n
        //  Xm - mensagem
        //  Xt - valor lido pelo sensor de temperatura
        //  Xr - valor do rele (0 ou 1)
        //  Xb - valor do buzzer (0 ou 1)
        //  Xv - valor da PWM da ventoinha (0 a 1)
		//   i - flag de inicio
		//   p - flag de parada
        BufferedSerial   PC;

        float            temp_base;                  // Temperatura necessaria

    public:
        Camara();
        void waitStartCommand();
        void heatOn();
        void heatOff();

		void start();
		void stop();
    };
}
