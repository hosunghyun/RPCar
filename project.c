#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>

#define TRIG 25   // pin 37
#define ECHO 23   // pin 33

#define LED1 2   // GPIO 13 왼쪽 led
#define LED2 5  // GPIO 18 오른쪽 led

#define BUZZER 3   // GPIO 15

const int B_IA_pwm = 1;      //wiringPi pin 11,12 IA방향(pwm) ,IB속도조절 변수
const int B_IB = 0;         // 앞 방향기준 오른쪽 바퀴

const int A_IA_pwm = 24;      // 35, 36
const int A_IB = 27;      //


int RAN(int ran) {   // 왼쪽 오른쪽 랜덤으로 정해주기 위해 숫자 구하는 함수

    ran = rand() % 2;

    return ran;
}

void HC_SR04(int data) {      // 초음파 센서 부분
    float dist, s, e;

    while (1) {
        digitalWrite(TRIG, 0);
        digitalWrite(TRIG, 1);
        delayMicroseconds(10);
        digitalWrite(TRIG, 0);
        while (digitalRead(ECHO) == 0) {
            s = micros();
        }
        while (digitalRead(ECHO) == 1) {
            e = micros();
        }
        dist = (e - s) / 58;


        delay(100);

        // 가까운 거리 
        if (dist < 30 && dist >= 10) data = 1;
        // 매우 가까운 거리
        if (dist < 10) data = 3;

;
        DC_MOTOR(data);

        data = 0;
        // 거리가 나오는지 확인 용
        //printf("distance(cm) : %f\n", dist);
    }
}

/*void BUZ(int data) {
    switch (data) {
    case 1:
        digitalWrite(BUZZER, HIGH);
        delay(1000);
        digitalWrite(BUZZER, LOW);
        delay(900);
    case 2:
        digitalWrite(BUZZER, HIGH);
        delay(500);
        digitalWrite(BUZZER, LOW);
        delay(400);
    case 3:
        digitalWrite(BUZZER, HIGH);
        delay(200);
        digitalWrite(BUZZER, LOW);
        delay(100);
    default:
        break;
    }
}*/

void Stop() {
    digitalWrite(B_IB, HIGH);
    pwmWrite(B_IA_pwm, 1024);
    digitalWrite(A_IB, HIGH);
    pwmWrite(A_IA_pwm, 1024);
}

void DC_MOTOR(int data) {
    int ran;
    int speed;

    ran = RAN(ran);

    if (data == 0) {
        printf("전진 중......\n");
        digitalWrite(B_IB, HIGH);
        pwmWrite(B_IA_pwm, 0);
        digitalWrite(A_IB, HIGH);
        pwmWrite(A_IA_pwm, 0);
    }

    if (data == 1) {
        // turn   위에 선언한 값이 0일경우 왼쪽으로 돌기 1이면 오른쪽으로 돌기
        // 왼쪽은 오른쪽 DC모터만 전진` 오른쪽이면 왼쪽 DC모터 전진
       // 일단 정지

        Stop();
        printf("좌, 우 고민중...\n");

        delay(200);


        // 때에따라서 좌, 또는 우로 회피
        switch (ran) {
        case 0:      // 왼쪽으로 가기
            printf("왼쪽으로 방향 전환하기...\n");
            digitalWrite(A_IB, HIGH);
            pwmWrite(A_IA_pwm, 1024);
            digitalWrite(B_IB, HIGH);
            pwmWrite(A_IA_pwm, 0);

            LED_ONOFF(ran);
            delay(1000);
            LED_ONOFF(ran);

            if (data != 1) {
                break;
            }

            ran = 3;
            
            break;
        case 1:      // 오른쪽으로 가기
            printf("오른쪽으로 방향 전환하기...\n");
            digitalWrite(B_IB, HIGH);
            pwmWrite(B_IA_pwm, 1024);
            digitalWrite(A_IB, HIGH);
            pwmWrite(B_IA_pwm, 0);

            LED_ONOFF(ran);

            delay(1000);

            if (data != 1) {
                break;
            }

            ran = 3;
            LED_ONOFF(ran);

            break;

        default:
            break;
        }
    }
    // 매우 가까운 거리에서는 부저를 울리며 후진한다
    if (data == 3) {
        printf("후진하는 중...\n");
        digitalWrite(B_IB, LOW);
        pwmWrite(B_IA_pwm, 1024);
        digitalWrite(A_IB, LOW);
        pwmWrite(A_IA_pwm, 1024);
        // 부저 울리기
        digitalWrite(BUZZER, HIGH);
        delay(1000);
        digitalWrite(BUZZER, LOW);
        delay(300);
    }
}


void LED_ONOFF(int data) {
    switch (data) {

        // 좌회전시 LED 왼쪽만 켜기
    case 0:
        digitalWrite(LED1, HIGH);
        break;

        // 우회전시 LED 오른쪽만 켜기
    case 1:
        digitalWrite(LED2, HIGH);
        break;
    case 3:
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        break;
    default:
        break;
    }
}


int main() {
    int data = 0;

    wiringPiSetup();

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    pinMode(B_IA_pwm, PWM_OUTPUT);
    pinMode(B_IB, OUTPUT);

    pinMode(A_IA_pwm, PWM_OUTPUT);
    pinMode(A_IB, OUTPUT);

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    pinMode(BUZZER, OUTPUT);

    if (wiringPiSetup() < 0) {
        exit(0);
    }

    while (1) {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        delay(1000);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);

        HC_SR04(data);
    }

    return 0;
}