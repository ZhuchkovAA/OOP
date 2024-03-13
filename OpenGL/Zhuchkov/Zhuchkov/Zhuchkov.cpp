#include <GLFW/glfw3.h>    // Подключение заголовочного файла для работы с GLFW
#define _USE_MATH_DEFINES  // Определение для использования математических констант
#include <conio.h>         // Подключение заголовочного файла для работы с консольным вводом-выводом

int main(void) {
    // Определение переменных для управления поворотом и положением 
    float angle = 0;
    float bias_X = 0;
    float bias_Y = 0;
    float bias_Z = 0;
    float delta_bias = 0.1;

    // Определение параметров освещения
    GLfloat light_position[] = { 0, 0, 1, 0 };
    GLfloat diffuse_color[] = { 0.3f, 0.4f, 0.5f, 0.6f };

    GLFWwindow* window;  // Объявление указателя на окно

    // Инициализация библиотеки GLFW
    if (!glfwInit())
        return -1;

    // Создание окна с заданным размером и заголовком
    window = glfwCreateWindow(1000, 1000, "LR1", NULL, NULL);
    if (!window) {  // Проверка на успешное создание окна
        glfwTerminate();  // Освобождение ресурсов GLFW
        return -1;
    }

    // Определение координат вершин 
    float vertices[] = { 0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,0.5,1,0.5,0,0,0,0,0,1,0.5,1,0.5,0,0,1,1,0,1,0.5,1,0.5,1,0,1,1,0,0,0.5,1,0.5 };

    // Установка созданного окна текущим контекстом OpenGL
    glfwMakeContextCurrent(window);

    // Включение теста глубины и материалов цвета
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    // Определение перспективы проекции
    glFrustum(-1, 1, -1, 1, 1, 100);

    // Включение освещения и установка его параметров
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);

    // Основной цикл программы
    while (!glfwWindowShouldClose(window)) {


        // Обработка поворота 
        if (angle > 360) {
            angle = 0;
        }

        // Очистка буфера цвета и буфера глубины
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 0); //фон

        // Установка указателя на массив вершин
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glEnableClientState(GL_VERTEX_ARRAY);
        angle += 1;  // Увеличение угла поворота

        // Включение смешивания и установка режима смешивания
        //glEnable(GL_BLEND);
        //glDepthMask(GL_FALSE);
        //glBlendFunc(GL_ONE, GL_ONE);

        glPushMatrix();
        glTranslatef(0, 0, -4);
        glRotatef(angle, 1, 1, 1);

        glColor3f(0, 1, 0);
        glDrawArrays(GL_QUADS, 0, 4);
        glColor3f(1, 0, 0);
        glDrawArrays(GL_TRIANGLES, 4, 3);
        glColor3f(0, 0, 1);
        glDrawArrays(GL_TRIANGLES, 7, 3);
        glColor3f(1, 0, 1);
        glDrawArrays(GL_TRIANGLES, 10, 3);
        glColor3f(0, 1, 1);
        glDrawArrays(GL_TRIANGLES, 13, 3);

        glPopMatrix();
        glDisableClientState(GL_VERTEX_ARRAY);

        // Отображение заднего и переднего буферов
        glfwSwapBuffers(window);

        // Обработка событий
        glfwPollEvents();
    }

    // Отключение смешивания
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    // Отключение источника света и указателя на массив вершин
    glDisable(GL_LIGHT0);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Завершение работы с GLFW
    glfwTerminate();

    return 0;
}