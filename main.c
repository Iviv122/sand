#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "sand.h"

#define ROWS 500
#define COLS 500


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


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

    window = glfwCreateWindow(500, 500, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
	setSand(matrix,0,0);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

	
	glLoadIdentity();
	glScalef(scale*2,scale*2,scale*2);
	
	glBegin(GL_POINTS);
	for(int y=ROWS-1;y>=0;--y){
	for(int x=0;x<COLS;++x){
	if(matrix[x][y]==1){
	updateSand(matrix,x,y);
	glVertex2f(x-(ROWS/2),y-(COLS/2));
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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){	
	double xpos,ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	
	int X = (int)xpos;
	int Y = (int)-ypos;
	printf("x: %f y: %f\n",xpos,ypos);
	printf("x: %d y: %d\n\n",X,Y);
	setSand(matrix,X,Y);
}
}
