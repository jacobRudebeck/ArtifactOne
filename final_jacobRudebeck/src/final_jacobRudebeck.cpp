//============================================================================
// Name        : final_jacobRudebeck.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*Header Inclusions */
#include <iostream>
#include <GL/freeglut.h>
#include <GL/glut.h>


//GLM Math Header Inclusions */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std; // Standard namespace

/*Used Functions*/
void UMouseMove(int x, int y);
void processSpecialKeys(int key, int xx, int yy);


// for scalling of the object

GLfloat scale_by_y=2.0f;
GLfloat scale_by_z=2.0f;
GLfloat scale_by_x=2.0f;


int view_state = 1; // Ortho view = 1, Perspective = 0

GLfloat lastMouseX = 400, lastMouseY = 300;  //locks mouse cursor at the center of the screen so you can move objectw
GLfloat sumX = 0, sumY = 0;
GLfloat mouseXoffset, mouseYoffset , yaw = 0.0f ,pitch = 0.0f; //mouse offset , yaw and pitch variables
GLfloat sensitivity = 0.05f; //used for mouse and camera sensitivity


GLint WindowWidth = 1200, WindowHeight = 960;


// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=0.0f;
// XZ position of the camera
float x=0.0f,z=0.0f;

//camera position
float cam_x = 0.0f;
float cam_y = 0.0f;
float cam_z = -1.0f;


//Initializes 3D rendering
void initRendering() {
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_COLOR_MATERIAL);
 glEnable(GL_LIGHTING); //Enable lighting
 glEnable(GL_LIGHT0); //Enable light #0
 glEnable(GL_LIGHT1); //Enable light #1
 glEnable(GL_NORMALIZE); //Automatically normalize normals
 glShadeModel(GL_SMOOTH); //Enable smooth shading
}

//Called when the window is resized
void handleResize(int w, int h) {
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 WindowWidth = w;
 WindowHeight = h;
 glViewport(0.0f,0.0f,WindowWidth,WindowHeight);
}

float _angle = -70.0f;

//Draws the 3D scene
void drawScene() {

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//change between orthogonal view and perspective view
 if(view_state == 1){


	 //perspective view
	 glMatrixMode(GL_PROJECTION); // keep it like this
	 glLoadIdentity();

	 gluPerspective(45.0, (GLfloat)WindowWidth / (GLfloat)WindowHeight, 0.1f, 100.0f);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();


 }else if(view_state == 0){


	 //orthogonal view

	 glMatrixMode (GL_PROJECTION);
	 glLoadIdentity();
	 glOrtho(-5.0f, 5.0f, -5.0f ,5.0f, 0.1f, 100.0f);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();


 }



 glTranslatef(0.0f, 0.0f, -14.0f);

 gluLookAt(cam_x,cam_y,cam_z,x, 0.0f, z,x+lx, 1.0f, z+lz);

 //this will allow for zooming in and out

 glScalef(scale_by_x, scale_by_y, scale_by_z);

 //Add ambient light
 GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
 glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

 //Add positioned light
 GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
 GLfloat lightPos0[] = {0.0f, -8.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
 glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
 glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

 //Add directed light
 GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
 //Coming from the direction (-1, 0.5, 0.5)
 GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
 glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
 glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

 glRotatef(10, 1.0f, 0.0f, 0.0f);
 glRotatef(-10, 0.0f, 0.0f, 1.0f);
 glRotatef(_angle,0.0f, 1.0f, 0.0f);

  glColor3f(1.0f, 0.8f, 0.0f);
 glBegin(GL_QUADS);



//chair base

  //Front

     glNormal3f(0.0f, 0.0f, 1.0f);

   glVertex3f(-2.0f, -0.2f, 2.0f);

  glVertex3f(2.0f, -0.2f, 2.0f);

  glVertex3f(2.0f, 0.2f, 2.0f);

  glVertex3f(-2.0f, 0.2f, 2.0f);



  //Right

  glNormal3f(1.0f, 0.0f, 0.0f);

  glVertex3f(2.0f, -0.2f, -2.0f);

  glVertex3f(2.0f, 0.2f, -2.0f);

  glVertex3f(2.0f, 0.2f, 2.0f);

  glVertex3f(2.0f, -0.2f, 2.0f);



  //Back

  glNormal3f(0.0f, 0.0f, -1.0f);

  glVertex3f(-2.0f, -0.2f, -2.0f);

  glVertex3f(-2.0f, 0.2f, -2.0f);

  glVertex3f(2.0f, 0.2f, -2.0f);

  glVertex3f(2.0f, -0.2f, -2.0f);



  //Left

  glNormal3f(-1.0f, 0.0f, 0.0f);

  glVertex3f(-2.0f, -0.2f, -2.0f);

  glVertex3f(-2.0f, -0.2f, 2.0f);

  glVertex3f(-2.0f, 0.2f, 2.0f);

  glVertex3f(-2.0f, 0.2f, -2.0f);



  //top

  glNormal3f(0.0f,1.0f,0.0f);



  glVertex3f(2.0f, 0.2f, 2.0f);

  glVertex3f(-2.0f, 0.2f, 2.0f);

  glVertex3f(-2.0f, 0.2f, -2.0f);

  glVertex3f(2.0f, 0.2f, -2.0f);





     //bottom

     glNormal3f(0.0f,-1.0f,0.0f);



  glVertex3f(2.0f, -0.2f, 2.0f);

  glVertex3f(-2.0f, -0.2f, 2.0f);

  glVertex3f(-2.0f, -0.2f, -2.0f);

  glVertex3f(2.0f, -0.2f, -2.0f);



     //table leg front right

     //front

     glNormal3f(0.0f, 0.0f, 1.0f);



  glVertex3f(1.8f,-0.2f,1.6f);

  glVertex3f(1.4f, -0.2f, 1.6f);

  glVertex3f(1.4f, -3.0f, 1.6f);

  glVertex3f(1.8f, -3.0f, 1.6f);



     //back

     glNormal3f(0.0f, 0.0f, -1.0f);



  glVertex3f(1.8f,-0.2f,1.2f);

  glVertex3f(1.4f, -0.2f, 1.2f);

  glVertex3f(1.4f, -3.0f, 1.2f);

  glVertex3f(1.8f, -3.0f, 1.2f);



  //right

  glNormal3f(1.0f, 0.0f, 0.0f);



  glVertex3f(1.8f,-0.2f,1.6f);

  glVertex3f(1.8f, -0.2f, 1.2f);

  glVertex3f(1.8f, -3.0f, 1.2f);

  glVertex3f(1.8f, -3.0f, 1.6f);



     //left

     glNormal3f(-1.0f, 0.0f, 0.0f);



  glVertex3f(1.4f,-0.2f,1.6f);

  glVertex3f(1.4f, -0.2f, 1.2f);

  glVertex3f(1.4f, -3.0f, 1.2f);

  glVertex3f(1.4f, -3.0f, 1.6f);



  //back leg right

  //front

  glNormal3f(0.0f, 0.0f, -1.0f);



  glVertex3f(1.8f,-0.2f,-1.2f);

  glVertex3f(1.4f, -0.2f, -1.2f);

  glVertex3f(1.4f, -3.0f, -1.2f);

  glVertex3f(1.8f, -3.0f, -1.2f);



  //back

  glNormal3f(0.0f, 0.0f, -1.0f);



  glVertex3f(1.8f,-0.2f,-1.6f);

  glVertex3f(1.4f, -0.2f, -1.6f);

  glVertex3f(1.4f, -3.0f, -1.6f);

  glVertex3f(1.8f, -3.0f, -1.6f);



     //right

     glNormal3f(1.0f, 0.0f, 0.0f);



  glVertex3f(1.8f,-0.2f,-1.6f);

  glVertex3f(1.8f, -0.2f, -1.2f);

  glVertex3f(1.8f, -3.0f, -1.2f);

  glVertex3f(1.8f, -3.0f, -1.6f);



  //left

     glNormal3f(1.0f, 0.0f, 0.0f);



  glVertex3f(1.4f,-0.2f,-1.6f);

  glVertex3f(1.4f, -0.2f, -1.2f);

  glVertex3f(1.4f, -3.0f, -1.2f);

  glVertex3f(1.4f, -3.0f, -1.6f);



     //leg left front

     glNormal3f(0.0f, 0.0f, 1.0f);



  glVertex3f(-1.8f,-0.2f,1.6f);

  glVertex3f(-1.4f, -0.2f, 1.6f);

  glVertex3f(-1.4f, -3.0f, 1.6f);

  glVertex3f(-1.8f, -3.0f, 1.6f);



     //back

     glNormal3f(0.0f, 0.0f, -1.0f);



  glVertex3f(-1.8f,-0.2f,1.2f);

  glVertex3f(-1.4f, -0.2f, 1.2f);

  glVertex3f(-1.4f, -3.0f, 1.2f);

  glVertex3f(-1.8f, -3.0f, 1.2f);



  //right

  glNormal3f(1.0f, 0.0f, 0.0f);



  glVertex3f(-1.8f,-0.2f,1.6f);

  glVertex3f(-1.8f, -0.2f, 1.2f);

  glVertex3f(-1.8f, -3.0f, 1.2f);

  glVertex3f(-1.8f, -3.0f, 1.6f);



     //left

     glNormal3f(-1.0f, 0.0f, 0.0f);



  glVertex3f(-1.4f,-0.2f,1.6f);

  glVertex3f(-1.4f, -0.2f, 1.2f);

  glVertex3f(-1.4f, -3.0f, 1.2f);

  glVertex3f(-1.4f, -3.0f, 1.6f);



  //back leg left



  //front

  glNormal3f(0.0f, 0.0f, -1.0f);



  glVertex3f(-1.8f,-0.2f,-1.2f);

  glVertex3f(-1.4f, -0.2f, -1.2f);

  glVertex3f(-1.4f, -3.0f, -1.2f);

  glVertex3f(-1.8f, -3.0f, -1.2f);



  //back

  glNormal3f(0.0f, 0.0f, -1.0f);



  glVertex3f(-1.8f,-0.2f,-1.6f);

  glVertex3f(-1.4f, -0.2f, -1.6f);

  glVertex3f(-1.4f, -3.0f, -1.6f);

  glVertex3f(-1.8f, -3.0f, -1.6f);



     //right

     glNormal3f(1.0f, 0.0f, 0.0f);



  glVertex3f(-1.8f,-0.2f,-1.6f);

  glVertex3f(-1.8f, -0.2f, -1.2f);

  glVertex3f(-1.8f, -3.0f, -1.2f);

  glVertex3f(-1.8f, -3.0f, -1.6f);



  //left

     glNormal3f(-1.0f, 0.0f, 0.0f);



  glVertex3f(-1.4f,-0.2f,-1.6f);

  glVertex3f(-1.4f, -0.2f, -1.2f);

  glVertex3f(-1.4f, -3.0f, -1.2f);

  glVertex3f(-1.4f, -3.0f, -1.6f);
















  //chair back pole 1 far lft, make higher than mid poles

  //front



  glNormal3f(-1.0f, 0.0f, 0.0f);

  glVertex3f(-1.8f, 0.2f, -1.8f);

  glVertex3f(-1.5f, 0.2f, -1.8f);

  glVertex3f(-1.5f, 4.5f, -1.8f);

  glVertex3f(-1.8f, 4.5f, -1.8f);



     //back

  glNormal3f(-1.0f, 0.0f, 0.0f);

  glVertex3f(-1.8f, 0.2f, -2.0f);

  glVertex3f(-1.5f, 0.2f, -2.0f);

  glVertex3f(-1.5f, 4.5f, -2.0f);

  glVertex3f(-1.8f, 4.5f, -2.0f);





   glNormal3f(-1.0f, 0.0f, 0.0f);

  glVertex3f(-1.8f, 0.2f, -2.0f);

  glVertex3f(-1.8f, 4.5f, -2.0f);

  glVertex3f(-1.8f, 4.5f, -1.8f);

  glVertex3f(-1.8f, 0.2f, -1.8f);





     glVertex3f(-1.5f, 0.2f, -2.0f);

  glVertex3f(-1.5f, 4.5f, -2.0f);

  glVertex3f(-1.5f, 4.5f, -1.8f);

  glVertex3f(-1.5f, 0.2f, -1.8f);



  glVertex3f(-1.8f, 4.5f, -2.0f);

  glVertex3f(-1.8f, 4.5f, -1.8f);

  glVertex3f(-1.5f, 4.5f, -1.8f);

     glVertex3f(-1.5, 4.5f, -2.0f);






  //chair back pole 2 far right

  //front



  glNormal3f(1.0f, 0.0f, 0.0f);

  glVertex3f(1.8f, 0.2f, -1.8f);

  glVertex3f(1.5f, 0.2f, -1.8f);

  glVertex3f(1.5f, 4.5f, -1.8f);

  glVertex3f(1.8f, 4.5f, -1.8f);


  //back

glNormal3f(-1.0f, 0.0f, 0.0f);

glVertex3f(1.8f, 0.2f, -2.0f);

glVertex3f(1.5f, 0.2f, -2.0f);

glVertex3f(1.5f, 4.5f, -2.0f);

glVertex3f(1.8f, 4.5f, -2.0f);





glNormal3f(-1.0f, 0.0f, 0.0f);

glVertex3f(1.8f, 0.2f, -2.0f);

glVertex3f(1.8f, 4.5f, -2.0f);

glVertex3f(1.8f, 4.5f, -1.8f);

glVertex3f(1.8f, 0.2f, -1.8f);





  glVertex3f(1.5f, 0.2f, -2.0f);

glVertex3f(1.5f, 4.5f, -2.0f);

glVertex3f(1.5f, 4.5f, -1.8f);

glVertex3f(1.5f, 0.2f, -1.8f);



glVertex3f(1.8f, 4.5f, -2.0f);

glVertex3f(1.8f, 4.5f, -1.8f);

glVertex3f(1.5f, 4.5f, -1.8f);

  glVertex3f(1.5, 4.5f, -2.0f);




  //chair back pole 3 mid right

    //front



    glNormal3f(1.0f, 0.0f, 0.0f);

    glVertex3f(0.8f, 0.2f, -1.8f);

    glVertex3f(0.5f, 0.2f, -1.8f);

    glVertex3f(0.5f, 3.5f, -1.8f);

    glVertex3f(0.8f, 3.5f, -1.8f);


    //back

  glNormal3f(-1.0f, 0.0f, 0.0f);

  glVertex3f(0.8f, 0.2f, -2.0f);

  glVertex3f(0.5f, 0.2f, -2.0f);

  glVertex3f(0.5f, 3.5f, -2.0f);

  glVertex3f(0.8f, 3.5f, -2.0f);





  glNormal3f(-1.0f, 0.0f, 0.0f);

  glVertex3f(0.8f, 0.2f, -2.0f);

  glVertex3f(0.8f, 3.5f, -2.0f);

  glVertex3f(0.8f, 3.5f, -1.8f);

  glVertex3f(0.8f, 0.2f, -1.8f);





    glVertex3f(0.5f, 0.2f, -2.0f);

  glVertex3f(0.5f, 3.5f, -2.0f);

  glVertex3f(0.5f, 3.5f, -1.8f);

  glVertex3f(0.5f, 0.2f, -1.8f);



  glVertex3f(0.8f, 3.5f, -2.0f);

  glVertex3f(0.8f, 3.5f, -1.8f);

  glVertex3f(0.5f, 3.5f, -1.8f);

    glVertex3f(0.5, 3.5f, -2.0f);


    //chair back pole 4 mid left

    //front



       glNormal3f(1.0f, 0.0f, 0.0f);

       glVertex3f(-0.8f, 0.2f, -1.8f);

       glVertex3f(-0.5f, 0.2f, -1.8f);

       glVertex3f(-0.5f, 3.5f, -1.8f);

       glVertex3f(-0.8f, 3.5f, -1.8f);


       //back

     glNormal3f(-1.0f, 0.0f, 0.0f);

     glVertex3f(-0.8f, 0.2f, -2.0f);

     glVertex3f(-0.5f, 0.2f, -2.0f);

     glVertex3f(-0.5f, 3.5f, -2.0f);

     glVertex3f(-0.8f, 3.5f, -2.0f);





     glNormal3f(-1.0f, 0.0f, 0.0f);

     glVertex3f(-0.8f, 0.2f, -2.0f);

     glVertex3f(-0.8f, 3.5f, -2.0f);

     glVertex3f(-0.8f, 3.5f, -1.8f);

     glVertex3f(-0.8f, 0.2f, -1.8f);





       glVertex3f(-0.5f, 0.2f, -2.0f);

     glVertex3f(-0.5f, 3.5f, -2.0f);

     glVertex3f(-0.5f, 3.5f, -1.8f);

     glVertex3f(-0.5f, 0.2f, -1.8f);



     glVertex3f(-0.8f, 3.5f, -2.0f);

     glVertex3f(-0.8f, 3.5f, -1.8f);

     glVertex3f(-0.5f, 3.5f, -1.8f);

       glVertex3f(-0.5, 3.5f, -2.0f);



//back top pole

       //Front

           glNormal3f(-0.1f, 0.0f, 0.0f);

         glVertex3f(-1.5f, 3.5f, -1.8f);

        glVertex3f(-1.5f, 4.0f, -1.8f);

        glVertex3f(1.5f, 4.0f, -1.8f);

        glVertex3f(1.5f, 3.5f, -1.8f);

        //back

             glNormal3f(-1.0f, 0.0f, 0.0f);

              glVertex3f(-1.5f, 3.5f, -2.0f);

              glVertex3f(-1.5f, 4.0f, -2.0f);

              glVertex3f(1.5f, 4.0f, -2.0f);

              glVertex3f(1.5f, 3.5f, -2.0f);



//top
              glVertex3f(-1.5f, 3.5f, -2.0f);

                  glVertex3f(-1.5f, 3.5f, -1.8f);

                  glVertex3f(1.5, 3.5f, -1.8f);

                    glVertex3f(1.5, 3.5f, -2.0f);

                    //bottom
                                  glVertex3f(-1.5f, 4.0f, -2.0f);

                                      glVertex3f(-1.5f, 4.0f, -1.8f);

                                      glVertex3f(1.5, 4.0f, -1.8f);

                                        glVertex3f(1.5, 4.0f, -2.0f);














      glEnd();












 glutSwapBuffers();
}

void update(int value) {
 //_angle += 1.5f;
 if (_angle > 360) {
  _angle -= 360;
 }

 glutPostRedisplay();
 glutTimerFunc(25, update, 0);
}

void UMouseMove(int curr_x , int curr_y){


	//change camera position
	 cam_x = 10.0f * cos(yaw);
	 cam_y = 10.0f * sin(pitch);
	 cam_z = sin(yaw) * cos(pitch) * 10.0f;

	 // direction  mouse was moved
	 	   mouseXoffset = curr_x - lastMouseX;
	 	   mouseYoffset = lastMouseY - curr_y;

	 		  //updates with new mouse coordinates
	 		   lastMouseX = curr_x;
	 		   lastMouseY = curr_y;

	 		   //Applies sensitivity to mouse direction
	 		   mouseXoffset *= sensitivity;
	 		   mouseYoffset *= sensitivity;




	            //get  direction of  mouse
	 		   //if there is changes in yaw, then it is moving along X
	 		   if(yaw != yaw+mouseXoffset && pitch == pitch+mouseYoffset){

	 			   //INCREMENT yaw
	 			   yaw += mouseXoffset;

	 			   //else movement in y
	 		   }else if(pitch != pitch+mouseYoffset && yaw == yaw+mouseXoffset ){


	 			   //increment y to move vertical
	 			    pitch += mouseYoffset;


	 		   }

	 		  //Maintains a 90 degree pitch for gimbal lock
              if(pitch > 89.0f ){

            	   pitch = 89.0f;


              }

              if(pitch < -89.0f ){

                         	   pitch = -89.0f;


                           }

              //update camera position

	 		   cam_x = 5.0f * cos(yaw);
	 		   cam_y = 5.0f * sin(pitch);
	 		   cam_z = sin(yaw) * cos(pitch) * 10.0f;


}

void processSpecialKeys(int key, int xx, int yy) {


	//used for zooming object
	switch (key) {

	//zoom object out
		case GLUT_KEY_UP :
		   scale_by_y += 0.1f;
		   scale_by_x += 0.1f;
		   scale_by_z += 0.1f;
			break;

			//zoom object in
		case GLUT_KEY_DOWN :
			scale_by_y -= 0.1f;
			scale_by_x -= 0.1f;
			scale_by_z -= 0.1f;
			break;

			//change view state to orthogonal
	  case GLUT_KEY_LEFT :
		    view_state = 0;
			break;

			//change view state to perspective
	  case GLUT_KEY_RIGHT:
			view_state = 1;
			break;
	}



}



int main(int argc, char** argv) {
 //Initialize GLUT
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(1200, 960);

 //Create the window
 glutCreateWindow("Chair");
 initRendering();

 //Set handler functions
 glutDisplayFunc(drawScene);

 glutReshapeFunc(handleResize);

 glutPassiveMotionFunc(UMouseMove);

 glutSpecialFunc(processSpecialKeys);

 update(0);

 glutMainLoop();
 return 0;
}
