# 마이크로임베디드프로그래밍 : RPCar
## 개요
■ Raspberry Pi를 이용한 자동차

만든 목적

■ Raspberry Pi를 활용하여 

일정

2022.10.20 ~ 2022.12.14

참여자

대진대학교 컴퓨터공학과 20181479 현호성

대진대학교 컴퓨터 공학과 20181466 김현호

##  사용 기술 및 개발 환경
- OS : Raspbian
- Sensor :
- Language : C
- Tools : Vi, Vim


## 내용


### 구현 기능

```
int RAN(int ran) {   // 왼쪽 오른쪽 랜덤으로 정해주기 위해 숫자 구하는 함수

    ran = rand() % 2;

    return ran;
}
```
자동차의 방향 전환 시 어느 방향으로 회전할 것인지 랜덤함수를 사용해서 랜덤으로 결정

```
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
```
초음파 센서를 활용하여 자동차 앞에 장애물을 식별하고 장애물과의 식별된 거리를 DC_MOTOR에 전달

```void DC_MOTOR(int data) {
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

```
전달 받은 거리를 이용하여 앞으로 전진하거나 가까운 경우 RAN()을 활용하여 방향 전환하고 계속해서 전진한다. 만약 갑작스럽게 등장한 장애물인 경우에는 후진한다.

```
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
```
장애물을 만나서 좌우로 회전할 때 회전하는 방향의 LED를 켠다.

```
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
```
라즈베리파이 GPIO 핀들을 초기화 한 후 자동차 관련 함수들을 무한 반복한다.
## 구현 결과물


유튜브 영상 링크 : <https://youtu.be/NdLFvqDE92M>

유튜브 영상 링크 : <https://youtu.be/tr5MButj-L4>
