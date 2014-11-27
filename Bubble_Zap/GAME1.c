#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<time.h>
static float xorig=240,yorig=0;
//float a1=xorig,b1=yorig,a2=xorig+20,b2=yorig+15,a3=xorig,b3=yorig+40,a4=xorig-20,b4=yorig+15,thet=3.14/10,inc=1;
static float a1=240,b1=0,a2=260,b2=15,a3=240,b3=40,a4=220,b4=15,thet=3.14/30,inc=3,thettrace=0;
int score,lose=0;
typedef struct ptss
{
  float x,y,rr,red,g,b;
}ptss;
ptss cir[5];
static int curve[5],signx[5];

float randomfloat(float r1, float r2)
{
  int range=((int)r2-(int)r1)-1;
  float n=rand()%range;
  float no;
  int i;
  for(i=1;i<7;i++)
    {
      no=rand()%10;
      no=no/pow(10,i);
      n=n+no;
    }
  n=n+r1;
  return n;
}
int randomm(int aa,int bb)
{
  int range=bb-aa;
  int n=rand()%range;
  n=n+aa;
  return n;
}

float pdistance(float px, float py, float px1, float py1, float px2,float  py2) 
{
  float A,B,C,D,dot,len_sq,param;
  A=px-px1;
  B=py-py1;
  C=px2-px1;
  D=py2-py1;
  dot=(A*C)+(B*D);
  len_sq=(C*C)+(D*D);
  param=dot/len_sq;
  float xx,yy,dx,dy;
  if (param<0||((px1==px2)&&(py1==py2))) 
    {
      xx = px1;
      yy = py1;
    }
  else if (param > 1) 
    {
      xx = px2;
      yy = py2;
    }
  else 
    {
      xx = px1 + (param * C);
      yy = py1 + (param * D);
    }
  dx = px - xx;
  dy = py - yy;
  return sqrt((dx * dx) + (dy * dy));
}

float distance(float px,float py,float px1,float py1,float px2,float py2)
{
  //  return abs(py-(px*m))/sqrt((m*m)+1);
  // return abs(px+py)/sqrt(2);
}
void init1(int i)
{
  cir[i].rr=randomfloat(20,80);
  cir[i].x=randomfloat(15,440);
  cir[i].y=randomm(480,700);
}
void init()
{
  int i;
  float red,green,blue;
  for(i=0;i<5;i++)
    {
      if(i==0)
	{
	  red=1;green=0;blue=0;
	}
      else if(i==1)
	{
	   red=1;green=1;blue=0;
	}
      else if(i==2)
	{
	   red=1;green=0;blue=1;
	}
      
      else if(i==3)
	{
	   red=0;green=0;blue=1;
	}
      else 
	{
	   red=0.1;green=0.6;blue=0.1;
	}
      cir[i].red=red;cir[i].g=green;cir[i].b=blue;
      cir[i].rr=randomfloat(20,80);
      cir[i].x=randomfloat(15,440);
      cir[i].y=randomm(480,700);
    }
}
void outputs(float x, float y, float r, float g, float b,  char *string)
{
  glColor3f(r,g,b);
  glRasterPos2f(x,y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) 
    {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}
void circle(float xc,float yc,float r,float rr,float gg,float bb)
{
  glBegin(GL_POLYGON);
  glColor3f(rr,gg,bb);
  float x,y;
  float theta=0,dtheta;
  dtheta=(1/r);
  for(;theta<(3.14*2);theta=theta+dtheta)
    {
      x=xc+r*cos(theta);
      y=yc+r*sin(theta);
      glVertex2i(x,y); 
    }
  glEnd();
  glFlush();
}
void motion()
{
  int i,signy;
  float yrand;
  for(i=0;i<5;i++)
    {
      if(curve[i]%250==0)
	signx[i]=rand()%2;
      if((cir[i].x+cir[i].rr)>480)
	signx[i]=0;
      if((cir[i].x-cir[i].rr)<0)
	signx[i]=1;
      //      signy=rand()%2;
      yrand=rand()%99999;
      if(yrand==0)
	yrand=1;
      yrand=yrand/100000;
      yrand=yrand/3;
      if((cir[i].y+cir[i].rr)<0)
	{
	  init1(i);
	}
      if(signx[i]==0)
	{
	  cir[i].x=cir[i].x-0.6;
	  cir[i].y=cir[i].y-yrand;
	}
      else
	{
	  cir[i].x=cir[i].x+0.6;
	  cir[i].y=cir[i].y-yrand;
	}
      curve[i]++;
    }
}
void polygon(float x1,float y1,float x2, float y2, float x3, float y3, float x4,float y4)
{
  glClearColor(1.0f,0.5f,0.0,0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);
  glColor3f(1.0f,1.0f,1.0f);
  glVertex2i(x1,y1);
  glVertex2i(x2,y2);
  glVertex2i(x3,y3);
  glVertex2i(x4,y4);
  glEnd();
  glFlush();
}
void polygon1(float x1,float y1,float x2, float y2, float x3, float y3, float x4,float y4)
{
  //glClearColor(1.0f,0.5f,0.0,0.0f);
  //glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);
  glColor3f(1.0f,1.0f,1.0f);
  glVertex2i(x1,y1);
  glVertex2i(x2,y2);
  glVertex2i(x3,y3);
  glVertex2i(x4,y4);
  glEnd();
  glFlush();
}
void translateo(float *x,float *y)
{
  *x=*x-xorig;
  *y=*y-yorig;
}
void translateb(float *x,float *y)
{
  *x=*x+xorig;
  *y=*y+yorig;
}
void rotate(float *x,float *y,float theta)
{
  float temp;
  //    printf("\n%f",thettrace);
  if(((thettrace+theta)<=2.407334)&&((thettrace+theta+(3.14/30))>=-2.407334))
    {
  //2.407334
      translateo(x,y);
      thettrace=thettrace+theta;
      temp=*x*cos(theta)+*y*sin(theta);
      *y=*x*(-sin(theta))+*y*cos(theta);
      *x=temp;
      translateb(x,y);
    }
}
void* doSomeThing(void* arg)
{
system("rvlc DotaSong.mp3");
}
int cnt;
void mydisplay()
{
  char str[15];
  int l;
  cnt++;
  //float e=0,f=0.3,g=1;
  float e=0,f=0,g=1;
  
  sprintf(str, "%d", score);
  glClearColor(1.0f,0.5f,0.0,0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  outputs(330,15,0.5,0,0.5,"SCORE: ");
  outputs(420,15,0.5,0,0.5,str);
  if(cnt%3==0)
    {
      e=0;f=0;g=1;
    }
  else if(cnt%3==1)
    {
      e=0;f=1;g=0;
    }
  else
    {
      e=1;f=0;g=0;
    }
  outputs(160,90,e,f,g,"BUBBLE ZAP ");
  for(l=0;l<5;l++)
    {
      // if(((cir[l].y+cir[l].rr)<b3)&&((cir[l].x+cir[l].rr)>a2)&&((((cir[l].x-cir[l].rr)>a2)&&((cir[l].x-cir[l].rr)<a4))||(((cir[l].x+cir[l].rr)>a2)||((cir[l].x+cir[l].rr)<a4))))
      if((cir[l].y-cir[l].rr)<0)
      {
	lose=1;
      }
    }
  if(lose==1)
    outputs(170,240,0.5,0,0.5,"GAME OVER");
  int i;
  glBegin(GL_POLYGON);
  glColor3f(0.0f,0.0f,1.0f);
  glVertex2i(a1,b1);
  glVertex2i(a2,b2);
  glVertex2i(a3,b3);
  glVertex2i(a4,b4);
  glEnd();
  glFlush();
  for(i=0;i<5;i++)
    {
      circle(cir[i].x,cir[i].y,cir[i].rr,cir[i].red,cir[i].g,cir[i].b);
    }
  motion();
  glutPostRedisplay();
}
void mykeyboard1(unsigned char k, int x, int y)
{
  float m;
  int abc;
  int l;
  float xxx;
  abc=(int)k;
  //  printf("%d",abc);
  if(abc==32)
    {
      m=(b1-b3)/(a1-a3);
      glBegin(GL_LINES);
      glColor3f(1.0f,1.0f,1.0f);
      glVertex2i(a3,b3);
      xxx=a3-((b3-480)/m);
      glVertex2i(xxx,480);
      glEnd();
      glFlush();
      polygon1(a1,b1,a2,b2,a3,b3,a4,b4);
      for(l=0;l<90000000;l++);
      for(l=0;l<5;l++)
	{
	   /* if(((cir[l].y+cir[l].rr)<b3)&&((cir[l].x+cir[l].rr)>a2)&&((((cir[l].x-cir[l].rr)>a2)&&((cir[l].x-cir[l].rr)<a4))||(((cir[l].x+cir[l].rr)>a2)||((cir[l].x+cir[l].rr)<a4)))) */
	   /*  { */
	   /*    lose=1; */
	   /*  } */
	  //	  if(((cir[l].y-cir[l].rr)<480)&&(xxx<((cir[l].x)+cir[l].rr))&&(xxx>((cir[l].x)-cir[l].rr)))
	  if((pdistance(cir[l].x,cir[l].y,a3,b3,xxx,480)-cir[l].rr)<0)
	    {
	      init1(l);
	      if(lose==0)
		score=score+10;
	    }
	}
    }
}

void mykeyboard(int k, int x, int y)
{
  // printf("\n%d",k);
   switch((int)k)
    {
    case 100://Left
      if((a4>0))
	{
	  a1=a1-inc;
	  a2=a2-inc;
	  a3=a3-inc;
	  a4=a4-inc;
	  xorig=xorig-inc;
	  polygon(a1,b1,a2,b2,a3,b3,a4,b4);
	}
      break;
    case 101://Up
      rotate(&a1,&b1,-thet);
      rotate(&a2,&b2,-thet);
      rotate(&a3,&b3,-thet);
      rotate(&a4,&b4,-thet);
      polygon(a1,b1,a2,b2,a3,b3,a4,b4);
      break;
    case 102://Right
      if(a2<480)
	{
	  a1=a1+inc;
	  a2=a2+inc;
	  a3=a3+inc;
	  a4=a4+inc;
	  xorig=xorig+inc;
	  polygon(a1,b1,a2,b2,a3,b3,a4,b4);
	}
      break;
    case 103://Down
      rotate(&a1,&b1,thet);
      rotate(&a2,&b2,thet);
      rotate(&a3,&b3,thet);
      rotate(&a4,&b4,thet);
      polygon(a1,b1,a2,b2,a3,b3,a4,b4);
      break;
     }
}
void main(int argc, char **argv)
{
  pthread_t tid[1];
  pthread_t * temp;
  pthread_create(&(tid[0]), NULL, &doSomeThing, NULL);
  srand(time(NULL));
  init();
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(480,480);
  glutInitWindowPosition(540,320);
  glutCreateWindow("my first attempt");
  glutSpecialFunc(mykeyboard);
  glutKeyboardFunc(mykeyboard1);
  glutDisplayFunc(mydisplay);
  glClearColor(1.0f,0.5f,0.0,0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(0.0,480.0,0.0,480.0);
  glutMainLoop();
}
