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

#include "Camara.hpp"

#include "ports.h"
#include "temperaturas.h"

namespace IntroEE {
    Camara::Camara() :
        LM35(LM35_PORT),
        dir1(VENT1_PORT),
        dir2(VENT2_PORT),
        buzzer(LED1),
        rele(RELE_PORT),
        fan(VENTPWM_PORT),
        PC(USBTX, USBRX)
    {
        temp_base = 0.;
        dir1 = 1;
        dir2 = 0;
        fan = 0.;
        buzzer = 0;
        rele = 0;
        fan.period(0.0001);
    }

    void Camara::waitStartCommand() {
        char c;
        temp_base = 0.;
        fan = 0.;
        buzzer = 0;
        rele = 0;
        fan.period(0.0001);


        for (;;) {
            PC.printf("i\r\n");
            while(!PC.readable()) wait(0.1);
            c = PC.getc();
            switch (c) {
                case 'a': // Parafina
                    PC.printf("Parafina escolhida.m\r\n");
                    temp_base = TEMP_PARAFINA + 10; // Deixa esquentar 10°C acima da temperatura de fusao
                    return;

                case 'b': // Garrafa PET
                    PC.printf("Garrafa PET escolhida.m\r\n");
                    temp_base = TEMP_PET + 10;;
                    return;

                case 'c': // Sacola plastica
                    PC.printf("Sacola Plastca escolhida.m\r\n");
                    temp_base = TEMP_SACOLA + 10;
                    return;

                case 'd': // Copo descartavel
                    PC.printf("Copo Descartavel escolhido.m\r\n");
                    temp_base = TEMP_COPO + 10;
                    return;

                default:  // Comando desconhecido
                    PC.printf("Comando invalido.m\r\n");
            }
        }
    }

    void Camara::heatOn() {
        rele = 1;
    }

    void Camara::heatOff() {
        rele = 0;
    }

    void Camara::start() {
        char c;
        float temp = 0.;
        float diff = 0.;

autom:
        heatOn();   // Liga o resistor
        for (;;) {
            temp = LM35 * 480.0;             // Atualiza a leitura de temperatura

            diff = temp - temp_base;
            diff *= 0.1;
            if (diff > 0. && diff <= 1.) {   // Liga a ventoinha quando necessaario
                fan = diff;
                buzzer = 0;
            } else if (diff < 0.) {
                fan = 0.;
                buzzer = 0;
            } else if (diff > 1.) {
                buzzer = 1;
                fan = 1.;
            }

            PC.printf("%ft\r\n", temp);      // Envia tudo que esta acontecendo para o computador
            wait(0.05);
            PC.printf("%dv\r\n", (fan > 0));
            wait(0.05);
            PC.printf("%dr\r\n", (rele == 1));
            wait(0.05);
            PC.printf("%db\r\n", (buzzer == 1));
            wait(0.05);

            if (PC.readable()) {
                if (PC.getc() == 'd') {                  // Entra no modo manual
                    fan = 0.;
                    for (;;) {
                        temp = LM35 * 480.0;             // Atualiza a leitura de temperatura

                        PC.printf("%ft\r\n", temp);      // Envia tudo que esta acontecendo para o computador
                        wait(0.05);
                        PC.printf("%dv\r\n", (fan > 0));
                        wait(0.05);
                        PC.printf("%dr\r\n", (rele == 1));
                        wait(0.05);
                        PC.printf("%db\r\n", (buzzer == 1));
                        wait(0.05);

                        if (PC.readable()) {
                            c = PC.getc();
                            switch (c) {
                                case 'q':             // Para
                                    return;
                                case 'v':             // Forca a ventoinha a ligar/desligar;
                                    fan = !fan;
                                    break;
                                case 'b':             // Forca o buzzer a ligar/desligar
                                    buzzer = !buzzer;
                                    break;
                                case 'r':             // Forca a resistencia a ligar/desligar
                                    rele = !rele;
                                    break;
                                case 's':             // Volta ao modo automático
                                    goto autom;
                            }
                        }
                    }
                }
            }
        }
    }

    void Camara::stop() {
        heatOff();
        fan = 0.;
        buzzer = 0.;
        PC.printf("p\r\n");
        wait(1);
    }
}
