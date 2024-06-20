# 마이크로임베디드프로그래밍 : RPCar
## 개요
■ Raspberry Pi를 이용한 자동차

만든 목적

■ Raspberry Pi를 활용하여 

일정

2020.00.00 ~ 2020.00.00

참여자

대진대학교 컴퓨터공학과 20181479 현호성

대진대학교 컴퓨터 공학과 20180000 김현호

##  사용 기술 및 개발 환경
- OS : Raspbian
- Sensor :
- Language : C
- Tools : Vi, Vim


## 내용
사용 라이브러리

```
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>
```

기능
```
static float mercuryYear = 0, venusYear = 0, earthYear = 0, marsYear = 0, jupiterYear = 0, saturnrYear = 0, uranusYear = 0, neptuneYear = 0, plutoYear =0; //공전
static int Time = 0;             //자전
float zoom = 6.0;
float Angle = 3; // 카메라 각도
float RL = 3.0;
```

행성 구현
```
void mercury() {
    glPushMatrix();
    glRotatef((GLfloat)90, 1.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidTorus(0.003, 0.4, 4.0, 40);	//수성 궤도
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)mercuryYear, 0.0, 1.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    glColor3f(0.8, 0.8, 0.0);
    glutSolidSphere(0.03, 10, 10);    // 수성 
    glPopMatrix();
}
void venus() {
    glPushMatrix();
    glRotatef((GLfloat)90, 1.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidTorus(0.003, 0.55, 4.0, 40);	//금성 궤도
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)venusYear, 0.0, 1.0, 0.0);
    glTranslatef(0.55, 0.0, 0.0);
    glColor3f(0.7, 0.3, 0.0);
    glutSolidSphere(0.06, 10, 10);    // 금성 
    glPopMatrix();
}
void earth() {
    glPushMatrix();
    glRotatef((GLfloat)90, 1.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidTorus(0.003, 0.75, 4.0, 40);	//지구 궤도
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)earthYear, 0.0, 1.0, 0.0);
    glTranslatef(0.75, 0.0, 0.0);
    glColor3f(0.2, 0.2, 1.0);
    glutSolidSphere(0.065, 10, 10);    // 지구 

    glRotatef((GLfloat)earthYear, 0.0, 1.0, 0.0);
    glTranslatef(0.09, 0.0, 0.0);
    glColor3f(1.0, 1.0, 0.5);
    glutSolidSphere(0.020, 10, 10);    // 위성-달 

    glPopMatrix();
}
void mars() {
    glPushMatrix();
    glRotatef((GLfloat)90, 1.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidTorus(0.003, 0.90, 4.0, 40);	//화성 궤도
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)marsYear, 0.0, 1.0, 0.0);
    glTranslatef(0.90, 0.0, 0.0);
    glColor3f(1.0, 0.3, 0.0);
    glutSolidSphere(0.05, 10, 10);    // 화성 
    glPopMatrix();
}
void jupiter() {
    glPushMatrix();
    glRotatef((GLfloat)90, 1.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidTorus(0.004, 1.55, 4.0, 60);	//목성 궤도
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)jupiterYear, 0.0, 1.0, 0.0);
    glTranslatef(1.55, 0.0, 0.0);
    glColor3f(1.0, 0.9, 0.5);
    glutSolidSphere(0.357, 20, 20);    // 목성 
    
    glRotatef((GLfloat)jupiterYear, 0.3, 1.0, 0.0);
    glTranslatef(0.4, -0.1, 0.0);
    glColor3f(1.0, 1.0, 0.5);
    glutSolidSphere(0.04, 10, 10);    // 위성-이오 
    glPopMatrix();
}
void saturn() {
    glPushMatrix();
    glRotatef((GLfloat)90, 1.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidTorus(0.004, 2.3, 4.0, 60);	//토성 궤도
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)saturnrYear, 0.0, 1.0, 0.0);
    glTranslatef(2.3, 0.0, 0.0);
    glColor3f(1.0, 0.9, 0.4);
    glutSolidSphere(0.257, 20, 20);    // 토성 
    glPopMatrix();

    glPushMatrix();

    glRotatef((GLfloat)saturnrYear, 0.0, 1.0, 0.0);
    glTranslatef(2.3, 0.0, 0.0);
    glColor3f(1.0, 0.6, 0.1);
    glRotatef((GLfloat)200, 2.0, 2.0, 2.0);
    glutSolidTorus(0.08, 0.4, 2.5, 40);    // 토성 고리 

    glPopMatrix();
}
void uranus() {
    glPushMatrix();
    glRotatef((GLfloat)90, 1.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidTorus(0.004, 3.0, 4.0, 60);	//천왕성 궤도
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)uranusYear, 0.0, 1.0, 0.0);
    glTranslatef(3.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.6);
    glutSolidSphere(0.13, 20, 20);    // 천왕성 
    glPopMatrix();
}
void nepturne() {
    glPushMatrix();
    glRotatef((GLfloat)90, 1.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidTorus(0.004, 3.7, 4.0, 40);	//해왕성 궤도
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)neptuneYear, 0.0, 1.0, 0.0);
    glTranslatef(3.7, 0.0, 0.0);
    glColor3f(0.0, 0.5, 1.0);
    glutSolidSphere(0.125, 20, 20);    // 해왕성 
    glPopMatrix();
}
void pluto() {
    glPushMatrix();
    glRotatef((GLfloat)15, 0.0, 0.0, -1.0);
    glRotatef((GLfloat)90, 1.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidTorus(0.004, 3.8, 4.0, 40);	//명왕성 궤도
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)15, 0.0, 0.0, -1.0);
    glRotatef((GLfloat)plutoYear, 0.0, 0.8, 0.0);
    glTranslatef(3.7, 0.0, 0.0);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.03, 20, 20);    // 명왕성
    glPopMatrix();
}
```

행성의 공전 구현
```
void MyTimer(int Value) {               // 공전, 지구를 기준으로 나머지 행성들의 비율을 맞춘다.

    mercuryYear += (48.87 / 12);           //수
    venusYear += (35 / 12);           //금
    earthYear += (29.78 / 12);           //지
    marsYear += (24.13 / 12);           //화
    jupiterYear += (13.076 / 12);          //목
    saturnrYear += (9.69 / 12);           //토
    uranusYear += (6.81 / 12);           //천
    neptuneYear += (5.43 / 12);           //해
    plutoYear += (3.21 / 12);            //명

    Time = (Time + 2) % 360;         //자전
    if (mercuryYear > 360) mercuryYear -= 360;
    if (venusYear > 360) venusYear -= 360;
    if (earthYear > 360) earthYear -= 360;
    if (marsYear > 360) marsYear -= 360;
    if (jupiterYear > 360) jupiterYear -= 360;
    if (saturnrYear > 360) saturnrYear -= 360;
    if (uranusYear > 360) uranusYear -= 360;
    if (neptuneYear > 360) neptuneYear -= 360;
    if (plutoYear > 360) plutoYear -= 360;
    glutPostRedisplay();         // MyDisplay를 다시 호출한다.
    glutTimerFunc(40, MyTimer, 1);       // 타이머콜백을 다시 호출한다.
}
```

행성의 광원효과 구현
```
void InitLight() {
    GLfloat light_specular[] = { 1.0, 1.0, 1.0 };   // 직접광
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0 };   // 반사광
    GLfloat light_ambient[] = { 1.0, 1.0, 1.0 };   // 주변광
    GLfloat light_position[] = { 0.0, 0.0, 0.0 };   // 광원의 위치
    glShadeModel(GL_SMOOTH);       // 구로 셰이딩
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.8); // 주변광 좀 더 밝게 설정
}
```

카메라 각도
```
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
   
}
```

카메라 이동
```
void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': // 줌인
        zoom = zoom - 0.1;
        break;
    case 's': // 줌아웃
        zoom = zoom + 0.1;
        break;
    case 'a':
        RL = RL + 0.1;
        break;
    case 'd':
        RL = RL - 0.1;
        break;
    case 'z':
        Angle = Angle - 0.1;
        break;
    case 'x':
        Angle = Angle + 0.1;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
```

메인 화면 출력
```
void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("20181479현호성");

    glutKeyboardFunc(MyKeyboard);
    glutTimerFunc(40, MyTimer, 1);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
```


### 구현 기능



## 구현 결과물

![SolarSystem](https://github.com/hosunghyun/RPCar/assets/149512530/38acff12-bda3-46bb-b4aa-c3b13eb58eff)

유튜브 영상 링크 : <https://youtu.be/NdLFvqDE92M>

유튜브 영상 링크 : <https://youtu.be/tr5MButj-L4>
