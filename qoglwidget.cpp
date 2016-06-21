#include "qoglwidget.h"
#include <cmath>
#include <QDebug>
#include "cylinder.h"
#include "sphere.h"
#include "cube.h"

int selectedCube = 0;

QOGLWidget::QOGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    xRot = 25;
    yRot = 0; //-25.0
    zRot = 0;

    xTran = 0;
    yTran = 0;
    zTran = 0;

    scale = 1.0;

    timer_game = new QTimer(this);                              //Ein Spieltimer wird erstellt der in bestimmten intervallen das Spiel vorantreibt
    timer_game->start(17);                                      //Timer soll alle 34 millisekunden auslösen (entspricht etwa 30 fps (17/1000 ~ 60fps))


    ball = Sphere(QVector3D(0.0, 4.0, 0.0), 0.5);               //Die Spielkugel wird erstellt
    ball.setColor(0.2, 1.0, 0.8);
    ball.setDirection(QVector3D(0.0, 0.5, 0.0));

    for(int i = 0; i < nr_cubes; i++){
        cube[i] = Cube(QVector3D(0.0, 0.0, i*1.25), 4.0, 1.0, 1.0);
        cube[i].setRotation(0.0, 0.0, 0.0);
        if(i == selectedCube){
            cube[i].setColor(0.0, 0.0, 1.0);
        }else{
            cube[i].setColor(1.0, 0.0, 0.0);
        }
    }


    setFocusPolicy(Qt::ClickFocus);                                     //Muss aktiviert sein, damit das Widget Key Events annimmt (da KeyEvents Fokus benötigen)
    connect(timer_game, SIGNAL(timeout()), this, SLOT(gameUpdate()));   //Immer wenn der Timer tickt, wird das SIGNAL vom SLOT gameUpdate() aufgefangen
}

QOGLWidget::~QOGLWidget()
{
}

void QOGLWidget::gameUpdate(){
    ball.updatePosition();
    checkCollision(ball, cube[0]);
    update();
}

void QOGLWidget::checkCollision(Sphere sphere, Cube cube){
    sphere.getDirection();
}

void QOGLWidget::paintGL()
{
    //Szene wird resetet
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Aus dem zwischenspeicher wird alles gelöscht
    glMatrixMode(GL_PROJECTION);                        //Wechselt in den Projection Matrix Mode
    glLoadIdentity();                                   //Projection Matrix wird gecleared
    glOrtho(-8, 8, -8, 8, -50, 50);                     //Die ränder von allem was man sehen kann wird gesetzt
    glMatrixMode(GL_MODELVIEW);                         //Wechselt in den Modelview um objekte zu rendern
    glLoadIdentity();                                   //Modelview wird erst gecleared

    //Rotiert die Komplette Ansicht
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glTranslatef(xTran, yTran, zTran);                  //Die Komplette Ansicht wird verschoben
    glScalef(scale, scale, scale);                      //Die Ansicht wird an allen Achsen gleichgroß skaliert

    //DRAW EVERYTHING----------------------------
    glPushMatrix();

    //Ein Bunter Boden wird erstellt
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    for(int i = 0; i < 45; i++){
        float delta = (2.0f * M_PI) / 45;
        float step = i*delta;
        float x = 30 * cosf(step);
        float y = -5.0;
        float z = 30 * sinf(step);
        glColor3f(1.0/i, (1.0/45.0) * i, 0.5);
        glVertex3f(x, y, z);
    }
    glEnd();

    for(int i = 0; i < nr_cubes; i++){
        cube[i].draw();
    }

    ball.draw();

    glPopMatrix();
    //----------------------------DRAW EVERYTHING
}

void QOGLWidget::initializeGL()
{
    //OpenGL Funktionen werden geladen und initialisiert
    initializeOpenGLFunctions();

    //Hintergrundfarbe wird gesetzt
    glClearColor(0,0,0,1);

    //Damit Transparenz gerendert werden kann
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //LIGHT 0----------------------------------------------
    //float light_ambient[] = { 0.2f, 0.2f, 0.2f, 0.2f };
    //glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    //glEnable(GL_LIGHT0);
    //----------------------------------------------LIGHT 0

    //LIGHT 1----------------------------------------------
    //Die Position des Lichts wird gesetzt
    float lightPosition1[] = { 0.0, 3.0, 20.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);

    float light_diffuse1[] = {0.8f, 0.8f, 0.8f, 1.f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse1 );
    glEnable(GL_LIGHT1);
    //----------------------------------------------LIGHT 1

    glShadeModel(GL_SMOOTH);    //Die belichtung von runden Objekten wird weich
    glEnable(GL_DEPTH_TEST);    //Tiefentest wird aktiviert
    glDepthFunc(GL_LESS);       //Objekte die hinter einem anderen Objekt stehen sollen nicht angezeigt werden
    glEnable(GL_LIGHTING);      //Licht wird aktiviert
    glEnable(GL_NORMALIZE);     //Normalvektoren werden mitskaliert wenn die szene verändert wird, damit der Normalvektor immer 1 lang ist (dient der belichtung)

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE); //Das Farbmaterial an den Objekten wird gesetzt
    glEnable(GL_COLOR_MATERIAL);                                //Das Farbmaterial wird aktiviert
}

void QOGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void QOGLWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return ||event->key() == Qt::Key_Enter){
        ball.setDirection(QVector3D(0.0, 0.5, 0.0));
        if(selectedCube + 1 < nr_cubes){
            cube[selectedCube].setColor(1.0, 0.0, 0.0);
            selectedCube++;
            cube[selectedCube].setColor(0.0, 0.0, 1.0);
        }else if(selectedCube + 1 == nr_cubes){
            cube[selectedCube].setColor(1.0, 0.0, 0.0);
            selectedCube++;
        }
    }
}

void QOGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastpos = event->pos();
}

void QOGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // ... and while moving, we calculate the dragging deltas

    // Left button: Rotating around y axis
    if(event->buttons() == Qt::LeftButton)
    {
        int dx = 0;
        int dy = 0;
        int dz = 0;
        dy = lastpos.x() - event->x();

        // Now let the world know that we want to rotate
        emit changeRotation( dx, dy, dz );
    }

    // Right button: Translating to left/right, up/down
    if(event->buttons() == Qt::RightButton)
    {
        float dx = 0;
        float dy = 0;
        float dz = 0;
        dx = ((lastpos.x() - event->x()) * 0.005) * (-1);
        dz = ((lastpos.y() - event->y()) * 0.005) * (-1);

        if(selectedCube >= nr_cubes){
            // Now let the world know that we want to translate
            emit changeTranslation(dx, dy, dz);
        }else{
            QVector3D pos = cube[selectedCube].getPos();
            cube[selectedCube].setPos(QVector3D(pos.x()+dx, pos.y(), pos.z()+dz));
        }
    }

    // Make the current position the starting point for the next dragging step
    lastpos = event->pos();
}

void QOGLWidget::wheelEvent(QWheelEvent *event)
{
    float dzoom = event->angleDelta().ry() *0.0005;
    emit changeZoom(dzoom);
}

void QOGLWidget::onChangeTranslation(float dx, float dy, float dz)
{
    xTran = xTran + dx;
    yTran = yTran + dy;
    zTran = zTran + dz;

    update();
}

void QOGLWidget::onChangeZoom(float dzoom)
{
    scale = scale + dzoom;
    if(scale < 0.1){
        scale = 0.1;
    }else if(scale > 2.0){
        scale = 2.0;
    }
    //qDebug("scale = %f | dzoom = %f", scale, dzoom);
    update();
}

void QOGLWidget::onChangeRotation(int dx, int dy, int dz)
{
    // To apply the requested rotation deltas, we increment...
    xRot = xRot + dx;
    if(yRot+dy < -180){
        yRot = -180;
    }
    if(yRot+dy > 180){
        yRot = 180;
    }
    if(yRot+dy > -180 && yRot+dy < 180){
        yRot = yRot + dy;
    }
    zRot = zRot + dz;
    update();
}




