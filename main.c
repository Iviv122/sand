#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "sand.h"

#define ROWS 500
#define COLS 500

float scale = (float)1/ROWS;

int** matrix;
int brushsize = 1;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS )
		brushsize++;
	if(key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
		brushsize--;
}


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
/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


	glfwSetKeyCallback(window, key_callback);
	
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){ //Remove sand on RMB
	double xpos,ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	int X = (int)xpos;
	int Y = (int)-ypos;
	printf("x: %f y: %f\n",xpos,ypos);
	printf("x: %d y: %d\n\n",X,Y);

	for(int y=-brushsize;y<brushsize+1;y++){
	for(int x=-brushsize;x<brushsize+1;x++){
		if(X+x >0 && X+x<500-1){
		unsetSand(matrix,X+x,Y+y);
	 }}}
	
	 }


	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){ //Place sand on LMB
	double xpos,ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	
	int X = (int)xpos;
	int Y = (int)-ypos;
	printf("x: %f y: %f\n",xpos,ypos);
	printf("x: %d y: %d\n\n",X,Y);

	for(int y=-brushsize;y<brushsize+1;y++){
	for(int x=-brushsize;x<brushsize+1;x++){
		if(X+x >0 && X+x<500-1){
		setSand(matrix,X+x,Y+y);
	 }}}
	}

	
	glLoadIdentity();
	glScalef(scale*2,scale*2,scale*2);	// to correctly show pixels and centrize
	glClearColor(1,1,1,1);			// bg white to show work area of mouse

	glBegin(GL_POINTS);
	for(int y=ROWS-1;y>=0;--y){
	for(int x=0;x<COLS;++x){		//fill bg as black/void
	glColor3f(0,0,0);
	glVertex2f(x-(ROWS/2),y-(COLS/2));
	
	if(matrix[x][y]==1){			// sand
	updateSand(matrix,x,y);
	glColor3f(1,1,1);
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

