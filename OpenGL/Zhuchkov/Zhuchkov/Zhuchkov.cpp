#include <windows.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <math.h>

#pragma comment (lib,"opengl32.lib")
#ifndef M_PI
#define M_PI 3.14159265
#endif

float vert[] = { 1,1,0, 1,-1,0, -1,-1,0, -1,1,0 }; //задаем пол
float xAlfa = 25;
float zAlfa = 0;
POINTFLOAT pos = { 0,0 };

float pyramid[] = { 0,0,10, 1,1,0, 1,-1,0, -1,-1,0, -1,1,0, 1,1,0 };
float cube[] = { 1,1,0, 1,-1,0, -1,-1,0, -1,1,0, 1,1,0, 1,-1,0, 1,-1,2, 1,1,2, 1,-1,0, -1,-1,0, -1,-1,2, 1,-1,2, 1,1,0, -1,1,0, -1,1,2, 1,1,2, -1,1,0, -1,-1,0, -1,-1,2, -1,1,2 };
float vertex[] = { -1,-1,1, 1,-1,1, 1,1,1, -1,1,1 };
float normal[] = { 0,0,1, 0,0,1, 0,0,1, 0,0,1 };

float getRand()
{
    return (float)rand() / RAND_MAX * 2 - 1;
}

void Qu() //построение шестеренки
{
    glBegin(GL_QUADS); // задаю зубчики
    glColor3f(1, 1, 1); // цвет вершины
    glVertex2f(-1.0f, -1.0f);
    glColor3f(getRand(), getRand(), getRand());
    glVertex2f(-0.5f, 0.0f);
    glColor3f(getRand(), getRand(), getRand());
    glVertex2f(0.5f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
}

void Many(float x, float y, float size)
{
    // рисует много шестеренок
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    for (int i = 0; i < 9; i++)
    {
        glPushMatrix(); //матрица преобразованная определяет положение, размер, углы
        glRotatef(60 * i, 0, 0, 1); //поворачивает на угол 
        glTranslatef(0, 3.5, 0); //двигаем вправо
        Qu();// функция рисования 
        glBegin(GL_LINES);
        glVertex2f(1.7f, -1.4f);
        glVertex2f(1.0f, -1.0f);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
}

void Draw()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vertex);
    glNormalPointer(GL_FLOAT, 0, normal);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

}

void DrawCube()
{
    glPushMatrix();
    // glScalef(2, 2, 2);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glColor3f(0, 1, 1);
    Draw();
    glRotatef(90, 1, 0, 0);
    glColor3f(0, 1, 1);
    Draw();
    glRotatef(90, 1, 0, 0);
    glColor3f(0, 1, 1);
    Draw();
    glRotatef(90, 1, 0, 0);
    glColor3f(0, 1, 1);
    Draw();
    glRotatef(90, 0, 1, 0);
    glColor3f(0, 1, 1);
    Draw();
    glRotatef(180, 0, 1, 0);
    glColor3f(1, 1, 1);
    Draw();
    glDisable(GL_BLEND);
    glPopMatrix();
}


//glVertexPointer(3, GL_FLOAT, 0, &pyramid);

//glPushMatrix();
//glTranslatef(3, 3, 0);
//glScalef(1, 1, 0.5);
//glColor3f(0.5, 0.5, 1);
//glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
//glPopMatrix();


//glVertexPointer(3, GL_FLOAT, 0, &cube);
//glColor3f(0, 0, 1);
//glDrawArrays(GL_QUADS, 0, 20);

void ShowWorld()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vert);
    for (int i = -5; i < 5; i++)
        for (int j = -5; j < 5; j++)
        {
            glPushMatrix();
            if ((i + j) % 2 == 0) glColor3f(0, 0.5, 0);
            else glColor3f(1, 1, 1);
            glTranslatef(i * 2, j * 2, 0);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glPopMatrix();
        }

    glDisableClientState(GL_VERTEX_ARRAY);
}

void MoveCamera()
{
    if (GetKeyState(VK_UP) < 0) xAlfa = ++xAlfa > 180 ? 180 : xAlfa;
    if (GetKeyState(VK_DOWN) < 0) xAlfa = --xAlfa < 0 ? 0 : xAlfa;
    if (GetKeyState(VK_LEFT) < 0) zAlfa++;
    if (GetKeyState(VK_RIGHT) < 0) zAlfa--;

    float ugol = -zAlfa / 180 * M_PI;
    float speed = 0;
    if (GetKeyState('W') < 0) speed = 0.1;
    if (GetKeyState('S') < 0) speed = -0.1;
    if (GetKeyState('A') < 0) { speed = 0.1; ugol -= M_PI * 0.5; }
    if (GetKeyState('D') < 0) { speed = 0.1; ugol += M_PI * 0.5; }
    if (speed != 0)
    {
        pos.x += sin(ugol) * speed;
        pos.y += cos(ugol) * speed;
    }

    glRotatef(-xAlfa, 1, 0, 0);
    glRotatef(-zAlfa, 0, 0, 1);
    glTranslatef(-pos.x, -pos.y, -3);
}


int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(750, 750, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 80);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    float theta = 0.0f;

    srand(time(NULL));
    int mySeed = rand();

    //glLoadIdentity();
    //glOrtho(2, -2, -2,2, -1, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(1.0f, 0.0f, 0.0f, 0.0f); //задает цвет фона
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        srand(mySeed);

        glPushMatrix();

        //glLoadIdentity();
        //glTranslatef(0.2, 0, 0);
       //glRotatef(theta, 0.0f, 1.0f, 0.0f);

        glRotatef(-45, 1, 0, 0);
        glRotatef(20, 0, 0, 1);
        glTranslatef(0, 0, -3);

        glPushMatrix();
        //glRotatef(theta, 0, 1, 0);
        float position[] = { 1,0,0,0 };
        glLightfv(GL_LIGHT0, GL_POSITION, position);

        //glTranslatef(0, 0, 2.5);
        glScalef(0.5, 0.5, 0.5);
        glColor3f(1, 1, 1);
        Draw();
        glPopMatrix();

        MoveCamera();
        ShowWorld();
        glColor3f(0, 0, 1);
        glRotatef(theta, 0, 0, 1);
        DrawCube();

        //ВЕСЬ КОД ДЛЯ ШЕСТЕРЕНОК

        //glLoadIdentity(); //загружает единичную матрицу
        //glScalef(0.2, 0.2, 0.2); //уменьшили масштаб системы координат

        //glRotatef(theta, 0.0f, 0.0f, 1.0f);

        //glColor3f(1, 1, 1 );
        //Many(-3, -3, 0.4);// процедура рисования 
        //Many(2, 2, 0.7);
        //Many(-1.5, 0, 0.2);


        glPopMatrix(); //перед рисованием мы сохранили текущую матрицу в стек

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();

        theta += 0.08f;

    }

    glfwTerminate();
    //return 0;
}