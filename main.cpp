//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
// Modificaciones para soportar macOS: Carlos Rodríguez Domínguez 2016
// Creacion de los Objetos: Antonio Marfil Sánchez
//
// GPL
//**************************************************************************


#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif
#include <ctype.h>

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

bool pintar = true;
int opcion = 0;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
    //  Front_plane>0  Back_plane>PlanoDelantero)
    glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
    
    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-Observer_distance);
    glRotatef(Observer_angle_x,1,0,0);
    glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
    glBegin(GL_LINES);
    // eje X, color rojo
    glColor3f(1,0,0);
    glVertex3f(-AXIS_SIZE,0,0);
    glVertex3f(AXIS_SIZE,0,0);
    // eje Y, color verde
    glColor3f(0,1,0);
    glVertex3f(0,-AXIS_SIZE,0);
    glVertex3f(0,AXIS_SIZE,0);
    // eje Z, color azul
    glColor3f(0,0,1);
    glVertex3f(0,0,-AXIS_SIZE);
    glVertex3f(0,0,AXIS_SIZE);
    glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
    GLfloat Vertices[8][3]= {{5,0,0},{4,4,0},{0,5,0},{-4,4,0},{-5,0,0},{-4,-4,0},{0,-5,0},{4,-4,0}};
    
    GLfloat verticesTriangular[6][3]={{-2.5,5,-2.5},{2.5,5,-2.5},{0,5,2.5}, {-2.5,-5,-2.5},{2.5,-5,-2.5},{0,-5,2.5}};
    GLfloat aristasTriangular[9][2]={{0,1},{0,2},{1,2},{0,3},{1,4},{2,5},{3,4},{3,5},{5,4}};
    GLfloat triangulosTriangular[8][3]={{0,1,2},{3,4,5},{0,2,3},{2,3,5},{5,4,2},{2,1,4},{3,4,0},{4,1,0}};
    
    GLfloat verticesOcta[6][3]={{-2.5,0,-2.5},{2.5,0,-2.5},{-2.5,0,2.5},{2.5,0,2.5},{0,5,0},{0,-5,0}};
    GLfloat aristasOcta[12][2]={{0,1},{0,2},{1,3},{2,3},{0,4},{1,4},{2,4},{3,4},{0,5},{1,5},{2,5},{3,5}};
    GLfloat triangulosOcta[8][3]={{0,1,5},{1,3,5},{3,2,5},{2,0,5},{1,3,4},{3,2,4},{2,0,4},{0,1,4}};
    
    glColor3f(0,1,0);
    glPointSize(4);
    
    glBegin(GL_POINTS);
    for (int i=0;i<8;i++){
        glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd();
    
    

    if(opcion==1){
        
        glPointSize(4);
        glColor3f(1.0,0.0,0.0);
        glBegin (GL_POINTS);
        for (int j=0;j<6;j++){
            glVertex3fv((GLfloat *) &verticesTriangular[j]);
        }
        glEnd();
    }else if(opcion==0){
        
        glColor3f(0,1,0);
        glPointSize(4);
        
        glBegin(GL_POINTS);
        for (int i=0;i<8;i++){
            glVertex3fv((GLfloat *) &Vertices[i]);
        }
        glEnd();
    }else if(opcion==2){
        
        glPointSize(4);
        glColor3f(1.0,0.0,0.0);
        glBegin (GL_POINTS);
        for (int j=0;j<6;j++){
            glVertex3fv((GLfloat *) &verticesOcta[j]);
        }
        glEnd();
    }else if(opcion==3){
        
        glPointSize(4);
        glColor3f(1.0,0.0,0.0);
        glBegin (GL_POINTS);
        for (int j=0;j<6;j++){
            glVertex3fv((GLfloat *) &verticesTriangular[j]);
        }
        glEnd();
        
        glColor3f(0,0.0,1);
        glBegin (GL_LINES);
        for (int j=0;j<9;j++){
            for(int h=0; h<2; h++){
                glVertex3fv((GLfloat *) &verticesTriangular[(int) aristasTriangular[j][h]]);
            }
        }
        glEnd();
    }else if(opcion==4){
        
        glPointSize(4);
        glColor3f(1.0,0.0,0.0);
        glBegin (GL_POINTS);
        for (int j=0;j<6;j++){
            glVertex3fv((GLfloat *) &verticesOcta[j]);
        }
        glEnd();
        
        glColor3f(0,0.0,1);
        glBegin (GL_LINES);
        for (int j=0;j<12;j++){
            for(int h=0; h<2; h++){
                glVertex3fv((GLfloat *) &verticesOcta[(int) aristasOcta[j][h]]);
            }
        }
        glEnd();
    }else if(opcion==5){
        
        glPointSize(4);
        glColor3f(1.0,0.0,0.0);
        glBegin (GL_POINTS);
        for (int j=0;j<6;j++){
            glVertex3fv((GLfloat *) &verticesTriangular[j]);
        }
        glEnd();
        
        glColor3f(0,0.0,1);
        glBegin (GL_LINES);
        for (int j=0;j<9;j++){
            for(int h=0; h<2; h++){
                glVertex3fv((GLfloat *) &verticesTriangular[(int) aristasTriangular[j][h]]);
            }
        }
        glEnd();
        
        glColor3f(0,1,0);
        glBegin (GL_TRIANGLES);
        for (int j=0;j<8;j++){
            for(int h=0; h<3; h++){
                glVertex3fv((GLfloat *) &verticesTriangular[(int) triangulosTriangular[j][h]]);
            }
        }
        glEnd();
        
        
    }else if(opcion==6){
        
        glPointSize(4);
        glColor3f(1.0,0.0,0.0);
        glBegin (GL_POINTS);
        for (int j=0;j<6;j++){
            glVertex3fv((GLfloat *) &verticesOcta[j]);
        }
        glEnd();
        
        glColor3f(0,0.0,1);
        glBegin (GL_LINES);
        for (int j=0;j<12;j++){
            for(int h=0; h<2; h++){
                glVertex3fv((GLfloat *) &verticesOcta[(int) aristasOcta[j][h]]);
            }
        }
        glEnd();
        
        glColor3f(0,1,0);
        glBegin (GL_TRIANGLES);
        for (int j=0;j<8;j++){
            for(int h=0; h<3; h++){
                glVertex3fv((GLfloat *) &verticesOcta[(int) triangulosOcta[j][h]]);
            }
        }
        glEnd();
        
    }else if(opcion==7){
        glPointSize(4);
        glColor3f(1.0,0.0,0.0);
        glBegin (GL_POINTS);
        for (int j=0;j<6;j++){
            glVertex3fv((GLfloat *) &verticesTriangular[j]);
        }
        glEnd();
        
        glColor3f(0,0.0,1);
        glBegin (GL_LINES);
        for (int j=0;j<9;j++){
            for(int h=0; h<2; h++){
                glVertex3fv((GLfloat *) &verticesTriangular[(int) aristasTriangular[j][h]]);
            }
        }
        glEnd();
        
        glColor3f(0,1,0);
        glBegin (GL_TRIANGLES);
        for (int j=0;j<8;j++){
            if(j%2==0){
                glColor3f(0,1,0);
            }else{
                glColor3f(0.6,0.1,1);
            }
            for(int h=0; h<3; h++){
                glVertex3fv((GLfloat *) &verticesTriangular[(int) triangulosTriangular[j][h]]);
            }
        }
        glEnd();
    }else if(opcion==8){
        
        glPointSize(4);
        glColor3f(1.0,0.0,0.0);
        glBegin (GL_POINTS);
        for (int j=0;j<6;j++){
            glVertex3fv((GLfloat *) &verticesOcta[j]);
        }
        glEnd();
        
        glColor3f(0,0.0,1);
        glBegin (GL_LINES);
        for (int j=0;j<12;j++){
            for(int h=0; h<2; h++){
                glVertex3fv((GLfloat *) &verticesOcta[(int) aristasOcta[j][h]]);
            }
        }
        glEnd();
        
        glColor3f(0,1,0);
        glBegin (GL_TRIANGLES);
        for (int j=0;j<8;j++){
            if(j%2==0){
                glColor3f(0,1,0);
            }else{
                glColor3f(0.6,0.1,1);
            }
            for(int h=0; h<3; h++){
                glVertex3fv((GLfloat *) &verticesOcta[(int) triangulosOcta[j][h]]);
            }
        }
        glEnd();
    }
    
    glEnd();
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{
    
    clear_window();
    change_observer();
    if (pintar) {
        draw_axis();
        draw_objects();
    }

    glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
    change_projection();
    glViewport(0,0,Ancho1,Alto1);
    glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
    
    if (toupper(Tecla1)=='Q') exit(0);
    if (toupper(Tecla1)=='C'){
        pintar = !pintar;
        glutPostRedisplay();
    }
    if(Tecla1=='0'){
        opcion=0;
        glutPostRedisplay();
    }else if (Tecla1=='1'){
        //DIBUJA VERTICES PRISMA TRIANGULAR
        opcion=1;
        glutPostRedisplay();
    }else if (Tecla1=='2'){
        //DIBUJA VERTICES OCTAEDRO
        opcion=2;
        glutPostRedisplay();
    }else if (Tecla1=='3'){
        //DIBUJA ARISTAS PRISMA TRIANGULAR
        opcion=3;
        glutPostRedisplay();
    }else if (Tecla1=='4'){
        //DIBUJA ARISTAS OCTAEDRA
        opcion=4;
        glutPostRedisplay();
    }else if (Tecla1=='5'){
        //DIBUJA SOLIDO PRISMA TRIANGULAR
        opcion=5;
        glutPostRedisplay();
    }else if (Tecla1=='6'){
        //DIBUJA SOLIDO OCTAEDRA
        opcion=6;
        glutPostRedisplay();
    }else if (Tecla1=='7'){
        //DIBUJA AJEDREZ PRISMA TRIANGULAR
        opcion=7;
        glutPostRedisplay();
    }else if (Tecla1=='8'){
        //DIBUJA AJEDREZ OCTAEDRA
        opcion=8;
        glutPostRedisplay();
    }
    
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{
    
    switch (Tecla1){
        case GLUT_KEY_LEFT:Observer_angle_y--;break;
        case GLUT_KEY_RIGHT:Observer_angle_y++;break;
        case GLUT_KEY_UP:Observer_angle_x--;break;
        case GLUT_KEY_DOWN:Observer_angle_x++;break;
        case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
        case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
    }
    glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
    // se inicalizan la ventana y los planos de corte
    Window_width=5;
    Window_height=5;
    Front_plane=10;
    Back_plane=1000;
    
    // se inicia la posicion del observador, en el eje z
    Observer_distance=2*Front_plane;
    Observer_angle_x=0;
    Observer_angle_y=0;
    
    // se indica cual sera el color para limpiar la ventana	(r,v,a,al)
    // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
    glClearColor(1,1,1,1);
    
    // se habilita el z-bufer
    glEnable(GL_DEPTH_TEST);
    //
    change_projection();
    //
    glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    // se llama a la inicialización de glut
    glutInit(&argc, argv);
    
    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);
    
    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);
    
    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Práctica 1");
    
    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);
    
    // funcion de inicialización
    initialize();
    
    // inicio del bucle de eventos
    glutMainLoop();
    
    //DECLARACION DE VERTICES
    
    
    return 0;
}
