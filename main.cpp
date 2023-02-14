/*
*Computer Graphics Project #4: SkyBox Design
* Ananshu Bhatt
* CSCI 172
* Instructions to use program
* Zoom In                       : End_Key  (0.2 increment)
* Zoom Out                      : Home_Key (0.2 decrement)
* Rotate Up   (around x - axis) : Up_Key   (5 degree increment)
* Rotate Down (around x - axis) : Down_Key (5 degree increment)
* Rotate Left (around y - axis) : Left_Key (5 degree increment)
* Rotate Right(around y - axis) : Right_Key(5 degree decrement)
* Toggle Wire Frame             : w_Key
*
*/

#include <string.h>

#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <iostream>
#include <SOIL.h>
#include <math.h>

using namespace std;
const bool DEBUG = true; //turns debugging on/off

GLuint tex;


int numFaces = 12; //12  set faces per object file total faces = 36 (12*3)

//light settings
GLfloat position[] = { 0.0f, 1.0f, 1.0f, 0.0f };
const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };




GLfloat cubeX, cubeY, cubeZ=0;  //position for cube


GLfloat cubeAngleX, cubeAngleY=0;       //variable assigned for roatation
GLfloat skyBoxAngleX, skyBoxAngleY=0;   //variable assigned for roatation


GLfloat cubeSize=1; //size of the cube

//scale multiplier
GLfloat sMulC;//for cube
GLfloat sbMulC;//for skyBox


GLfloat camX; //setting camera position
GLfloat camY; //setting camera position


bool WireFrame = false; //setting wire frame equal to fasle

/* GLUT callback Handlers */

static void resize(int width, int height) //resize function
{
    double Ratio;

    width = (float)width;
    height = (float)height;

    Ratio = (double)width / (double)height;

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, Ratio, 0.1f, 1500.0f);
}

//GLuint tex;
 void loadTexture(char *fileName){
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &tex);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, tex); // images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.
    int width, height;                 // initializing and declaring width & height
    unsigned char *image;
    image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGB);
    if(!image)  //If there is no image or it cannot find it, then it will print an error
       cout << "Failed to find image" << endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // binding image data
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


static void display(void) //display function
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camX, camY, 3, camX, camY, 0.0, 0.0, 1.0, 0.0); //creating viewing matrix

    if (WireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME

    glTranslatef(0,0,sMulC);
    glRotatef(skyBoxAngleX,1,0,0);
    glRotatef(skyBoxAngleY,0,1,0);

    glPushMatrix(); //creating skybox
        glScalef(5.0, 5.0, 5.0); //making it bigger
        glDisable(GL_NORMALIZE);    //Disable normalize
        glDisable(GL_LIGHTING);     //Disable lighting


        loadTexture("images/brick.png"); //image of skybox
        glBegin(GL_QUADS);  //GL_QUADS allows us to create a 4 sided polygon
            glTexCoord2f(1.0, 0.0);     //texture coordinates
            glVertex3f(-1.0, 1.0, -1.0);    //specifies vertexes

            glTexCoord2f(1.0, 1.0);     //second vertexes
            glVertex3f(-1.0, -1.0, -1.0);

            glTexCoord2f(0.0, 1.0);     //third vertexes
            glVertex3f(1.0, -1.0, -1.0);

            glTexCoord2f(0.0, 0.0);     //fourth vertexes
            glVertex3f(1.0, 1.0, -1.0);
        glEnd();


        glBegin(GL_QUADS);                  //Second Square
            glTexCoord2f(1.0, 0.0);
            glVertex3f(1.0, 1.0, -1.0);

            glTexCoord2f(1.0, 1.0);
            glVertex3f(1.0, -1.0, -1.0);

            glTexCoord2f(0.0, 1.0);
            glVertex3f(1.0, -1.0, 1.0);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(1.0, 1.0, 1.0);
        glEnd();


        glBegin(GL_QUADS);                  //Third Square which is left side
            glTexCoord2f(0.0, 0.0);
            glVertex3f(-1.0, 1.0, -1.0);

            glTexCoord2f(1.0, 0.0);
            glVertex3f(-1.0, 1.0, 1.0);

            glTexCoord2f(1.0, 1.0);
            glVertex3f(-1.0, -1.0, 1.0);

            glTexCoord2f(0.0, 1.0);
            glVertex3f(-1.0, -1.0, -1.0);
        glEnd();


        //Fourth Square
        glBegin(GL_QUADS);                  //would give 360 degree view with rotation
            glTexCoord2f(0.0, 0.0);
            glVertex3f(-1.0, 1.0, 1.0);

            glTexCoord2f(1.0, 0.0);
            glVertex3f(1.0, 1.0, 1.0);

            glTexCoord2f(1.0, 1.0);
            glVertex3f(1.0, -1.0, 1.0);

            glTexCoord2f(0.0, 1.0);
            glVertex3f(-1.0, -1.0, 1.0);
        glEnd();

        //Ceiling
        loadTexture("images/roof.png");
        glBegin(GL_QUADS);             //Fifth square which is made on top
            glTexCoord2f(0.0, 1.0);
            glVertex3f(1.0, 1.0, -1.0);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(1.0, 1.0, 1.0);

            glTexCoord2f(1.0, 0.0);
            glVertex3f(-1.0, 1.0, 1.0);

            glTexCoord2f(1.0, 1.0);
            glVertex3f(-1.0, 1.0, -1.0);
        glEnd();

        //creating Floor
        glBegin(GL_QUADS);              //bottom square which is the last one
            glTexCoord2f(1.0, 1.0);
            glVertex3f(-1.0, -1.0, 1.0);

            glTexCoord2f(0.0, 1.0);
            glVertex3f(1.0, -1.0, 1.0);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(1.0, -1.0, -1.0);

            glTexCoord2f(1.0, 0.0);
            glVertex3f(-1.0, -1.0, -1.0);
        glEnd();

        glEnable(GL_NORMALIZE); //Enabling Normalization
    glPopMatrix();

    //creating CUBE
    glPushMatrix();
    glRotatef(cubeAngleX,1,0,0);
    glRotatef(cubeAngleY,0,1,0);
        glScalef(1.0, 1.0, 1.0); //Make it bigger
        glDisable(GL_NORMALIZE);    //Disable normalize
        glDisable(GL_LIGHTING);     //Disable lighting

        //Front
        loadTexture("images/brick.jpg"); //This image will be loaded into the Square below
        glBegin(GL_QUADS);  //GL_QUADS allows us to create a 4 sided polygon
            glTexCoord2f(1.0, 0.0);     //texture coordinates
            glVertex3f(-1.0, 1.0, -1.0);    //specifing vertexes

            glTexCoord2f(1.0, 1.0);     //second vertex
            glVertex3f(-1.0, -1.0, -1.0);

            glTexCoord2f(0.0, 1.0);     //third vertex
            glVertex3f(1.0, -1.0, -1.0);

            glTexCoord2f(0.0, 0.0);     //fourth vertex
            glVertex3f(1.0, 1.0, -1.0);
        glEnd();

        //Right
        glBegin(GL_QUADS);                  //Second Square
            glTexCoord2f(1.0, 0.0);
            glVertex3f(1.0, 1.0, -1.0);

            glTexCoord2f(1.0, 1.0);
            glVertex3f(1.0, -1.0, -1.0);

            glTexCoord2f(0.0, 1.0);
            glVertex3f(1.0, -1.0, 1.0);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(1.0, 1.0, 1.0);
        glEnd();

        //Left side
        glBegin(GL_QUADS);                  //Third Square
            glTexCoord2f(0.0, 0.0);         //opposite side is being created
            glVertex3f(-1.0, 1.0, -1.0);

            glTexCoord2f(1.0, 0.0);
            glVertex3f(-1.0, 1.0, 1.0);

            glTexCoord2f(1.0, 1.0);
            glVertex3f(-1.0, -1.0, 1.0);

            glTexCoord2f(0.0, 1.0);
            glVertex3f(-1.0, -1.0, -1.0);
        glEnd();


        //Back side
        //Fourth Square is created
        glBegin(GL_QUADS);                  //completes 360 degree view and rotation
            glTexCoord2f(0.0, 0.0);         //again opposite side being created
            glVertex3f(-1.0, 1.0, 1.0);

            glTexCoord2f(1.0, 0.0);
            glVertex3f(1.0, 1.0, 1.0);

            glTexCoord2f(1.0, 1.0);
            glVertex3f(1.0, -1.0, 1.0);

            glTexCoord2f(0.0, 1.0);
            glVertex3f(-1.0, -1.0, 1.0);
        glEnd();

        //Ceiling is being created
        //loadTexture("images/roof.png");
        glBegin(GL_QUADS);             //Fifth square being made
            glTexCoord2f(0.0, 1.0);
            glVertex3f(1.0, 1.0, -1.0);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(1.0, 1.0, 1.0);

            glTexCoord2f(1.0, 0.0);
            glVertex3f(-1.0, 1.0, 1.0);

            glTexCoord2f(1.0, 1.0);
            glVertex3f(-1.0, 1.0, -1.0);
        glEnd();

        //Floor
        glBegin(GL_QUADS);              //Last square being made
            glTexCoord2f(1.0, 1.0);
            glVertex3f(-1.0, -1.0, 1.0);

            glTexCoord2f(0.0, 1.0);
            glVertex3f(1.0, -1.0, 1.0);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(1.0, -1.0, -1.0);

            glTexCoord2f(1.0, 0.0);
            glVertex3f(-1.0, -1.0, -1.0);
        glEnd();

        glEnable(GL_NORMALIZE); //Enable Normalization
    glPopMatrix();
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y) //assigning key
{
    switch (key)
    {
        //press ESC or 'q' to terminate program
    case 27:
    case 'q':
        exit(0);
        break;

        //user presses key 'a' and is able to preform a rotation left around the Y axis
    case 'a':
        if (DEBUG);
        cubeAngleY -= 5; //setting the angle to be rotated at 5 degrees
        break;

        //user presses key 'd' and is able to preform a rotation right around the Y axis
    case 'd':
        if (DEBUG);
        cubeAngleY += 5; //setting the angle to be rotated at 5 degrees
        break;

        //user presses key 'w' and is able to preform a rotation up around the X axis
    case 'w':
        if (DEBUG);
        cubeAngleX -= 5; //setting the angle to be rotated at 5 degrees
        break;

        //user presses key 's' and is able to preform a rotation down around the X axis
    case 's':
        if (DEBUG);
        cubeAngleX += 5; //setting the angle to be rotated at 5 degrees
        break;

        //user presses key 'j' and is rotate camera left around the Y axis
    case 'j':
        if (DEBUG);
        camX -= .2;
        break;

        //user presses key 'l' and is rotate camera right around the Y axis
    case 'l':
        if (DEBUG);
        camX += .2;
        break;

        //user presses key 'i' and is rotate camera up around the X axis
    case 'i':
        if (DEBUG);
        camY += .2;
        break;

        //user presses key 'k' and is rotate camera down around the X axis
    case 'k':
        if (DEBUG);
        camY -= .2;
        break;

        //user presses key 'o' and resets camera to initial position
    case 'o':
        if (DEBUG);
        camX = 0;
        camY = 0;
        break;

        //user presses key 'z' and is able to preform a zoom in
    case 'z':
        if (DEBUG);
        sMulC += 0.2; //increments by 0.2 in scaling function
        sbMulC += 0.2; //increments by 0.2 in scaling function

        //user presses key 'x' and is able to preform a zoom out
    case 'x':
        if (DEBUG);
        sMulC -= 0.2; //decrements by 0.2 in scaling function
        sbMulC -= 0.2; //decrements by 0.2 in scaling function
        break;

        //user presses key space and is able to reset
    case ' ':
        if (DEBUG);
        camX = 0;  //camera position
        camY = 0;  //camera position


        cubeAngleX = 0, cubeAngleY = 0;  //rotation degree variables for glRotatef
        skyBoxAngleX = 0, skyBoxAngleY = 180;
        break;

        //user presses key 'f' and is able to display the cube in wire frame mode
    case 'f':
        if (DEBUG);
        WireFrame = !WireFrame;//change the wireframe back and forth
        break;
    }
}

void Specialkeys(int key, int x, int y)
{
    switch (key)
    {
        //user presses key UP and SKYBOX is able to preform a rotation
    case GLUT_KEY_UP:
        if (DEBUG);
        skyBoxAngleX -= 5; //setting the angle to be rotated at 5 degrees
        break;

        //user presses key DOWN and SKYBOX is able to preform a rotation
    case GLUT_KEY_DOWN:
        if (DEBUG);
        skyBoxAngleX += 5; //setting the angle to be rotated at 5 degrees
        break;

        //user presses key LEFT and SKYBOX is able to preform a left rotation around the Y axis
    case GLUT_KEY_LEFT:
        if (DEBUG);
        skyBoxAngleY -= 5; //setting the angle to be rotated at 5 degrees
        break;

        //user presses key RIGHT and SKYBOX is able to preform a right rotation around the Y axis
    case GLUT_KEY_RIGHT:
        if (DEBUG);
        skyBoxAngleY += 5; //setting the angle to be rotated at 5 degrees
        break;
    }
    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay(); //displaying cube and skybox
}




static void init(void) //initialing the values
{
    camX = 0;   //initial camera position
    camY = 0;   //initial camera position


    cubeX = 0.0, cubeY = 0.0, cubeZ = -2.0; //cube position

    cubeAngleX = 0, cubeAngleY = 0;  //rotation degree variables being used
    skyBoxAngleX = 0, skyBoxAngleY = 180;

    sMulC = -2;  //scale multiplier for cube
    sbMulC = 6;  //scale multiplier for skyBox

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
}

/* Program entry point */

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(1000, 900);//starting size of window
    glutInitWindowPosition(0, 0);//starting window position
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Project 4: SkyBox Design");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
