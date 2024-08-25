#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "sand.h"

#define ROWS 500
#define COLS 500

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

float scale = (float)1/ROWS;
int** matrix;
int main(void)
{


matrix = (int**)calloc(COLS,sizeof(int*));
for(int i=0;i<COLS;i++){
matrix[i] = (int*)calloc(ROWS,sizeof(int));
}


    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
	setSand(matrix,0,0);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

	
	glLoadIdentity();
	glScalef(scale,scale,scale);
	
	glBegin(GL_POINTS);
	for(int y=ROWS-1;y>=0;--y){
	for(int x=0;x<COLS;++x){
	
	if(matrix[x][y]==1){
	updateSand(matrix,x,y);
	glVertex2f(x-(COLS/2),y-(ROWS/2));
	}
	}
	}
	glEnd();





        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_REPEAT){
	setSand(matrix,249,300);
	}
}
