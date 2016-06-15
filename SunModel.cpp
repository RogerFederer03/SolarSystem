//������3��
//1 ��glut.dll copy �� system32 Ŀ¼��
//2 ��Ҫ�õ���ͷ�ļ���������
//3 ��project-->set-->link �м����õ��Ŀ� *.lib
//*.h �ļ���Ҫcopy��\VC98\Include\GL�� ��#include <GL/*.h> ����
//*.lib�ļ�ֱ��copy��\VC98\LIB��

#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <glut.h>
#include "rf.h"
#include "mf.h"
#include "draw.h"


#define  DEG_TO_RAD 0.017453

static GLuint texName;
bool   g_bOrbitOn = true;
float  g_fSpeedmodifier = 1.0f;
float  g_fElpasedTime;
double g_dCurrentTime;
double g_dLastTime;

static GLdouble viewer[]= {-sin(10*DEG_TO_RAD),10*cos(10*DEG_TO_RAD), -25}; //��ʼ���ӽ�
static int year =0 ,day = 0;
float angle=0.0;

TEXTUREIMAGE  sunImg;
TEXTUREIMAGE  mercuImg;
TEXTUREIMAGE  venusImg;
TEXTUREIMAGE  earthImg;
TEXTUREIMAGE  moonImg;
TEXTUREIMAGE  marsImg;
TEXTUREIMAGE  jupiterImg;
TEXTUREIMAGE  saturnImg;
TEXTUREIMAGE  uranusImg;
TEXTUREIMAGE  neptuneImg;
TEXTUREIMAGE  skyImg;


#define NUM_TEXTURES    11
GLuint  textureObjects[NUM_TEXTURES];

MATERIAL material[NUM_TEXTURES];
// ����
LIGHT light =
{
    {0.0, 0.0, 0.0, 1.0},    // ���������
    {1.0, 1.0, 1.0, 1.0},    // ��������
    {1.0, 1.0, 1.0, 1.0},    // ��������
    {0.0, 0.0, 0.0, 1.0}    // ��Դλ��
};
// ����
MATERIAL materialSpace =                     //�ռ�
{
    {0.4, 0.4, 0.4, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    0.0
};

MATERIAL materialSun =                       //̫��
{
    {100.0, 100.0, 100.0, 20.0},
    {0.8, 0.8, 0.8, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    0.0
};

MATERIAL materialMercu =                     //ˮ��
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

MATERIAL materialVenus =                     //����
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

MATERIAL materialEarth =                     //����        
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};
MATERIAL materialMoon =                      //����
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    0.0
};

MATERIAL materialMars =                      //����
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

MATERIAL materialJupiter =                    //ľ��
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

MATERIAL materialSaturn =                     //����
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

MATERIAL materialUranus =                     //������
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

MATERIAL materialNeptune =                    //������
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

void init()
{ 
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    material[0]=materialSun;
    material[1]=materialEarth ;
    material[2]=materialMoon ;
    material[3]=materialSpace ;

    GLfloat light_ambient[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //��ʼ����������
    mf(sunImg, &textureObjects[0]);
    mf(mercuImg, &textureObjects[1]);
    mf(venusImg, &textureObjects[2]);
    mf(earthImg, &textureObjects[3]);
    mf(moonImg, &textureObjects[4]);
    mf(marsImg, &textureObjects[5]);
    mf(jupiterImg, &textureObjects[6]);
    mf(saturnImg, &textureObjects[7]);
    mf(uranusImg, &textureObjects[8]);
    mf(neptuneImg, &textureObjects[9]);
    mf(skyImg, &textureObjects[10]);
 }  

void reshape(int w,int h)
{
    glViewport(0,0,(GLfloat) w, (GLfloat) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,0,1);
    
}
void ShutdownRC(void)
{
    //ɾ������
   glDeleteTextures(NUM_TEXTURES, textureObjects);
}


void display(void)
{
    glLoadIdentity();
    
    //���ù۲���λ�ú͹۲�ķ���
    gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,0,1);

    //���ϵͳʱ��ʹ̫��ϵ�ж�̬Ч��
    g_dCurrentTime = timeGetTime();
    g_fElpasedTime = (float)((g_dCurrentTime - g_dLastTime) * 0.001);
    g_dLastTime    = g_dCurrentTime;

    GLfloat light_position[]={0.0, 0.0, 0.0, 1.0};



    static float fSunSpin    = 0.0f;//̫����ת�ٶ�  
    
    static float fMercuSpin  = 0.0f;//ˮ����ת�ٶ�    
    static float fMercuOrbit = 0.0f;//ˮ�ǹ�ת�ٶ�

    static float fVenusSpin  = 0.0f;//������ת�ٶ�    
    static float fVenusOrbit = 0.0f;//���ǹ�ת�ٶ�

    static float fEarthSpin  = 0.0f;//������ת�ٶ�    
    static float fEarthOrbit = 0.0f;//����ת�ٶ�

    static float fMoonSpin   = 0.0f;//������ת�ٶ�    
    static float fMoonOrbit  = 0.0f;//������ת�ٶ�

    static float fMarsSpin   = 0.0f;//������ת�ٶ�     
    static float fMarsOrbit  = 0.0f;//���ǹ�ת�ٶ�

    static float fJupiterSpin   = 0.0f;//ľ����ת�ٶ�    
    static float fJupiterOrbit  = 0.0f;//ľ�ǹ�ת�ٶ�

    static float fSaturnSpin   = 0.0f;//������ת�ٶ�      
    static float fSaturnOrbit  = 0.0f;//���ǹ�ת�ٶ�
  
    static float fUranusSpin   = 0.0f;//��������ת�ٶ�      
    static float fUranusOrbit  = 0.0f;//�����ǹ�ת�ٶ�

    static float fNeptuneSpin   = 0.0f;//��������ת�ٶ�      
    static float fNeptuneOrbit  = 0.0f;//�����ǹ�ת�ٶ�
    
    static float fSpace      = 0.0f;//̫�յ�ת�� 

    float spaceWidth =18.50;
    float spacedepth =8.0;

    static float MercuToSun=-3.0;//ˮ����̫���ľ���
    static float VenusToSun =-4.5;//������̫���ľ���
    static float EarthToSun =-6.0;//������̫���ľ���    
    static float MoonToEarth = -0.9f;//���������ľ���
    static float MarsToSun =-7.0;//������̫���ľ���
    static float JupiterToSun =-8.0;//ľ����̫���ľ���
    static float SaturnToSun =-9.0;//������̫���ľ���
    static float UranusToSun =-10.0;//��������̫���ľ���
    static float NeptuneToSun =-11.0;//��������̫���ľ���

    
     if( g_bOrbitOn == true )
     {
         fSunSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);
       
         fMercuSpin -= g_fSpeedmodifier * (g_fElpasedTime * 15.0f);
         fMercuOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 40.0f);

         fVenusSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);
         fVenusOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 30.0f);

         fEarthSpin  -= g_fSpeedmodifier * (g_fElpasedTime * 100.0f);
         fEarthOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 20.0f);

         fMoonSpin  -= g_fSpeedmodifier * (g_fElpasedTime * 50.0f);
         fMoonOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 200.0f);

         fMarsSpin -= g_fSpeedmodifier * (g_fElpasedTime * 30.0f);
         fMarsOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 50.0f);

         fJupiterSpin -= g_fSpeedmodifier * (g_fElpasedTime * 90.0f);
         fJupiterOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 35.0f);

         fSaturnSpin -= g_fSpeedmodifier * (g_fElpasedTime * 90.0f);
         fSaturnOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 25.0f);

         fUranusSpin -= g_fSpeedmodifier * (g_fElpasedTime * 70.0f);
         fUranusOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 15.0f);

         fNeptuneSpin -= g_fSpeedmodifier * (g_fElpasedTime * 40.0f);
         fNeptuneOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 5.0f);

    }

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW );


    //��������ͼ��
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //��Դλ��
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //�������ע�ʹ��º�̫���͵����һ��

    /************************̫��*******************************/
    //����̫������
    glMaterialfv(GL_FRONT, GL_SPECULAR,material[0].specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material[0].ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material[0].diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, material[0].shininess);
    glColor3f(1,1,1);

    //̫����λ�ã���С��ת�٣�������
    glPushMatrix();
    glRotatef(10,1,0.0,0.0);
    glRotatef(fSunSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[0]);
    gltDrawSphere(2,200,200); 
    glPopMatrix();
    /*****************************************************************************/

    /************************ˮ��*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fMercuOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,MercuToSun);
    glRotatef(fMercuSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[1]);
    gltDrawSphere(0.3,150,200); 
    glPopMatrix();    
    
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(MercuToSun*sin(DEG_TO_RAD*angle),0,MercuToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************����*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fVenusOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,VenusToSun);
    glRotatef(fVenusSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[2]);
    gltDrawSphere(0.5,150,200); 
    glPopMatrix();    
    
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(VenusToSun*sin(DEG_TO_RAD*angle),0,VenusToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************����*******************************/
    //���õ������
    glMaterialfv(GL_FRONT, GL_SPECULAR,material[1].specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material[1].ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material[1].diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, material[1].shininess);

    //�����λ�ã���С��ת�٣�������
    glPushMatrix();
    glRotatef(fEarthOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,EarthToSun);
    glRotatef(fEarthSpin,0.0,1.0,0.0);
    glRotatef(10,0,0.0,1.0);
    glRotatef(90,1,0.0,0.0);

    glBindTexture(GL_TEXTURE_2D , textureObjects[3]);
    gltDrawSphere(0.6,100,100); 
    glPopMatrix();

    //����Ĺ��
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(EarthToSun*sin(DEG_TO_RAD*angle),0,EarthToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************����*******************************/
    glPushMatrix();
    glRotatef( fEarthOrbit, 0.0f, 1.0f, 0.0f ); 
    glTranslatef( 0.0f, 0.0f, EarthToSun);         
    glRotatef( fMoonOrbit, 0.0f, 1.0f, 0.0f );  
    glTranslatef( 0.0f, 0.0f, MoonToEarth );    
    glRotatef( fMoonSpin, 0.0f, 1.0f, 0.0f );  
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[4]);
    gltDrawSphere(0.2,50,20); 
    glPopMatrix();
    /*****************************************************************************/

    /************************����*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fMarsOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,MarsToSun);
    glRotatef(fMarsSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[5]);
    gltDrawSphere(0.3,150,200); 
    glPopMatrix();    

    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(MarsToSun*sin(DEG_TO_RAD*angle),0,MarsToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************ľ��*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fJupiterOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,JupiterToSun);
    glRotatef(fJupiterSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[6]);
    gltDrawSphere(0.7,150,200); 
    glPopMatrix();    
    
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(JupiterToSun*sin(DEG_TO_RAD*angle),0,JupiterToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************����*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fSaturnOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,SaturnToSun);
    glRotatef(fSaturnSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[7]);
    gltDrawSphere(0.7,150,200); 
    glPopMatrix();    
    
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(SaturnToSun*sin(DEG_TO_RAD*angle),0,SaturnToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************������*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fUranusOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,UranusToSun);
    glRotatef(fUranusSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[8]);
    gltDrawSphere(0.7,150,200); 
    glPopMatrix();    

    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(UranusToSun*sin(DEG_TO_RAD*angle),0,UranusToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************������*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fNeptuneOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,NeptuneToSun);
    glRotatef(fNeptuneSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[9]);
    gltDrawSphere(0.6,150,200); 
    glPopMatrix();    

    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(NeptuneToSun*sin(DEG_TO_RAD*angle),0,NeptuneToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************�ռ䱳��*******************************/
    //�ռ����
    glMaterialfv(GL_FRONT, GL_SPECULAR,material[3].specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material[3].ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material[3].diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, material[3].shininess);

    //�ռ��λ�ã���С��ת�٣�������
    glPushMatrix();
    glRotatef(fSpace,0.0,0.0,1.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[10]);
    glRotatef(90,1,1.0,0.0);
    gltDrawSphere(40,100,100);
    glPopMatrix();
    /*****************************************************************************/
    
    glutSwapBuffers();    
    glFlush();

}



void keyboard(unsigned char key ,int x,int y)
{
    switch(key)
    {
    case'+':
        ++g_fSpeedmodifier;
        glutPostRedisplay();
        break;

    case ' ':
        g_bOrbitOn = !g_bOrbitOn;
        glutPostRedisplay();
        break;

    case'-':
        --g_fSpeedmodifier;
        glutPostRedisplay();
        break;

    case'w':
        viewer[0]+= 0.1;
        break;

    case's':
        viewer[0]-= 0.1;
        break;

    case'a':
        viewer[1]+=0.1;
        break;

    case'd':
        viewer[1]-=0.1;
        break;

    case'x':
        viewer[2]+=0.1;
        break;

    case'c':
        viewer[2]-=0.1;
        break;

    default:
        break;

    }
    display();
}

void mouse(int btn, int state, int x, int y)
{

    //������

    static  int axis=0;

    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        axis++;
        axis=axis%5;
    }
    if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
    {
        axis--;
        if(axis==-1)
            axis=4;
    }
        switch(axis)
        {
        case 0:
            viewer[0]=-sin(10*DEG_TO_RAD);
            viewer[1]=cos(10*DEG_TO_RAD);
            viewer[2]=-15;
            break;

        case 1:
            viewer[0]=1;
            viewer[1]=20;
            viewer[2]=1;
            break;
            
        case 2:
            viewer[0]=-sin(10*DEG_TO_RAD);
            viewer[1]=10*cos(10*DEG_TO_RAD);
            viewer[2]=-13;
            break;

        case 3:
            viewer[0]=-5;
            viewer[1]=15;
            viewer[2]=-15;
            break;


        case 4:
            viewer[0]=-sin(10*DEG_TO_RAD);
            viewer[1]=10*cos(10*DEG_TO_RAD);
            viewer[2]=-25;
            break;

        default:
            break;
        }
        display();
    
}
int main(int argc, char**argv)
{
    //��ͼƬ
    LoadBmp("image//Sun.bmp"     , &sunImg);
    LoadBmp("image//Mercu.bmp"   , &mercuImg);
    LoadBmp("image//Venus.bmp"   , &venusImg);
    LoadBmp("image//Earth.bmp"   , &earthImg);
    LoadBmp("image//Moon.bmp"    , &moonImg);
    LoadBmp("image//Mars.bmp"    , &marsImg);
    LoadBmp("image//Jupiter.bmp" , &jupiterImg);
    LoadBmp("image//Saturn.bmp"  , &saturnImg);
    LoadBmp("image//Uranus.bmp"  , &uranusImg);
    LoadBmp("image//Neptune.bmp" , &neptuneImg);
    LoadBmp("image//sky.bmp"     , &skyImg);

    /*******************************************************/

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("ģ��̫��ϵ");
    init();
    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    ShutdownRC();

    //ɾ����������
    for(int i=0; i<NUM_TEXTURES; i++)
        glDeleteTextures(1, &textureObjects[i]);

    return 0;
}
