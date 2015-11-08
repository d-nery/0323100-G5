#include "mbed.h"
#include "ports.h"
#include "TextLCD.h"
#include "BufferedSerial.h"

AnalogIn       LM35(LM35_PORT);            // Sensor de Temperatura
AnalogIn       Pot(POTENCIOMETRO_PORT);    // Potenciometro

DigitalOut     dir1(VENT1_PORT);           // Direcoes Ventoinha
DigitalOut     dir2(VENT2_PORT);
DigitalOut     led1(LED1);
DigitalOut     led2(LED2);
DigitalOut     rele(RELE_PORT);

PwmOut         fan(VENTPWM_PORT);

BufferedSerial PC(USBTX, USBRX);

TextLCD        lcd(LCDRS, LCDE, LCDD4, LCDD5, LCDD6, LCDD7);

int main(void) {
    char c;
    float temp = 0.;
    float pot;

    dir1 = 1;
    dir2 = 0;
    rele = 1;

    fan = 0.0;
    fan.period(0.0001);

mark1:
    led1 = led2 = 0;
    fan = 0.0;
    do {
        PC.printf("Esperando comando de iniciom\r\n");
        if (PC.readable()) {
            c = PC.getc();
            PC.printf("Lido: %d | %cm\r\n", c, c);
        }
        wait(0.3);
    } while (c != 's');

    while (1) {
        if (PC.readable()) {
            c = PC.getc();
            PC.printf("Lido: %d | %cm\r\n", c, c);
            switch (c) {
            case 'v':
                fan = 1.0;
                break;
            case 'w':
                fan = 0.0;
                break;
            case 'l':
                led1 = (led1 == 0 ? 1 : 0);
                break;
            case 'p':
                goto mark1;
            }
        }
        temp = LM35 * 500.0;
        PC.printf("%ft\r\n", temp);
        wait(0.1);
        PC.printf("%dv\r\n", (fan == 1));
        wait(0.1);
        PC.printf("%dr\r\n", (rele == 1));
        wait(0.1);
        PC.printf("%dl\r\n", (led == 1));
        wait(0.1);
        // PC.printf("%fp\r\n", Pot * 5);
        // wait(0.1);
    }

    return -1;
}
