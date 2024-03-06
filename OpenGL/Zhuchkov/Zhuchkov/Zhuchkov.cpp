#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <cmath>

void drawHomeLower() {
    glBegin(GL_POLYGON);
    glColor3f(1, 0.6, 0.3);
    glVertex3f(-0.6, -1, 0);
    glVertex3f(-0.6, -0.5, 0);
    glVertex3f(-1, -0.5, 0);
    glVertex3f(-1, -1, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0.6, 0);
    glVertex3f(-0.6, -1, 0);
    glVertex3f(-0.6, -0.5, 0);
    glVertex3f(-0.3, -0.2, 0);
    glVertex3f(-0.3, -0.6, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(-1, -0.5, 0);
    glVertex3f(-0.6, -0.2, 0);
    glVertex3f(-0.3, -0.2, 0);
    glVertex3f(-0.6, -0.5, 0);
    glEnd();
}

void drawHomeUpper() {
    glBegin(GL_POLYGON);
    glColor3f(1, 0.6, 0.6);
    glVertex3f(-0.6, -0.2, 0);
    glVertex3f(-0.6, 0.3, 0);
    glVertex3f(-0.3, 0.3, 0);
    glVertex3f(-0.3, -0.2, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0.6, 0.67);
    glVertex3f(-0.3, -0.6, 0);
    glVertex3f(-0.3, 0.3, 0);
    glVertex3f(-0.14, 0.4, 0);
    glVertex3f(-0.14, -0.4, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(-0.6, 0.3, 0);
    glVertex3f(-0.46, 0.4, 0);
    glVertex3f(-0.14, 0.4, 0);
    glVertex3f(-0.3, 0.3, 0);
    glEnd();

}

void drawHomeLeft() {
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 0.6);
    glVertex3f(0.8, -0.6, 0);
    glVertex3f(0.8, 0.3, 0);
    glVertex3f(0.5, 0.3, 0);
    glVertex3f(0.5, -0.6, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.4, 0.67);
    glVertex3f(0.5, -0.6, 0);
    glVertex3f(0.5, 0.3, 0);
    glVertex3f(0.34, 0.4, 0);
    glVertex3f(0.34, -0.4, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0.4, 0.4);
    glVertex3f(0.8, 0.3, 0);
    glVertex3f(0.66, 0.4, 0);
    glVertex3f(0.34, 0.4, 0);
    glVertex3f(0.5, 0.3, 0);
    glEnd();

}

void drawDoroga() {
    glBegin(GL_POLYGON);
    glColor3f(0.28, 0.28, 0.28);
    glVertex3f(-2, -3, -1);
    glVertex3f(-2, -0.5, -1);
    glVertex3f(2, -0.5, -1);
    glVertex3f(2, -3, -1);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.74, 0.74, 0.74);
    glVertex3f(-1.04, -2, 0);
    glVertex3f(-0.04, -0.4, 0);
    glVertex3f(0.2, -0.4, 0);
    glVertex3f(1.04, -2, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.28, 0.28, 0.28);
    glVertex3f(-0.02, -2, 1);
    glVertex3f(0.05, -0.3, 1);
    glVertex3f(0.06, -0.3, 1);
    glVertex3f(0.01, -2, 1);
    glEnd();

}



int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(
        1000,
        1000,
        "ZhuchkovTown",
        NULL, NULL
    );

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    
    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glLoadIdentity();
    glFrustum(-0.6, 0.6, -1, 0.5, 2, 6);

    while (!glfwWindowShouldClose(window))
    {
        glNormal3f(0, 0, 1);
        glBlendFunc(GL_ONE, GL_ONE); 

        glClearColor(0.4, 0.8, 1, 1); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        static float alpha = 0;
        alpha -= 1;
        glPushMatrix();
        glTranslatef(0, 0, -4);
        float position[] = { 0, 0, 1, 0 };



        drawDoroga();
        drawHomeLower();
        drawHomeUpper();
        drawHomeLeft();

        glPopMatrix();
        glDisableClientState(GL_VERTEX_ARRAY);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
