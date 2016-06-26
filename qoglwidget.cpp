#include "qoglwidget.h"
#include <cmath>
#include <QDebug>
#include "cylinder.h"
#include "sphere.h"
#include "cube.h"

int selectedCube = 0;
bool rotationMode = false;

QOGLWidget::QOGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    xRot = 25;
    yRot = 0.0; //-25.0

    xTran = 0.0;
    yTran = 0.0;
    zTran = 0.0;

    scale = 1.0;

    timer_game = new QTimer(this);                              //Ein Spieltimer wird erstellt der in bestimmten intervallen das Spiel vorantreibt
    timer_game->start(20);                                      //Timer soll alle 34 millisekunden auslösen (entspricht etwa 30 fps (17/1000 ~ 60fps))


    ball = Sphere(QVector3D(0.0, 4.0, 0.0), 0.5, 0.5);               //Die Spielkugel wird erstellt
    ball.setColor(0.2, 1.0, 0.8);
    ball.setDirection(QVector3D(0.0, 0.1, 0.0));

    for(int i = 0; i < NR_CUBES; i++){
        cube[i] = Cube(QVector3D((i)*4.25, -i*10.0, 0.0), 4.0, 1.0, 1.0);
        cube[i].setRotation(0.0, 0.0, 0.0);
        if(i == selectedCube){
            cube[i].setColor(0.0, 0.0, 1.0);
        }else{
            cube[i].setColor(0.5, 0.5, 0.5);
        }
    }

    setFocusPolicy(Qt::ClickFocus);                                     //Muss aktiviert sein, damit das Widget Key Events annimmt (da KeyEvents Fokus benötigen)
    connect(timer_game, SIGNAL(timeout()), this, SLOT(gameUpdate()));   //Immer wenn der Timer tickt, wird das SIGNAL vom SLOT gameUpdate() aufgefangen
}

QOGLWidget::~QOGLWidget()
{
}

void QOGLWidget::gameUpdate(){

    QVector3D a = QVector3D(0.0, - GRAVITY, 0.0)/ball.getMass();        //Erdanziehungskraft
    QVector3D luftreibung = - ball.getDirection().normalized() * 0.5 * 0.25 * ball.getArea() * ball.getDirection().lengthSquared(); //Luftwiderstand

    ball.setDirection(ball.getDirection() + a + luftreibung);           //Neue geschwindigkeit ist alte Geschwindigkeit + Erdanziehungskraft + Reibungskraft

    for(int i = 0; i < 1; i++){
        //alle cubes nach intersion testen, wenn sie intersionen, zeit ausrechnen bis zum intersionen und je nachdem welche zeit am geringsten ist, wird mit collision behandelt
        checkCollision(cube[i], ball);
    }

    update();
}

void QOGLWidget::checkCollision(Cube& cube, Sphere& sphere){

    float lambda = 0;
    QVector3D normal;
    QVector3D sphereOldPosition = sphere.getPos();
    QVector3D sphereOldVelocity = sphere.getDirection();

    QVector3D sphereNewPosition;

    QVector3D planes[4];
    QVector3D normals[4];

    QVector3D planes[0] = cube.getGlobalCoordinatesOfPoint(cube.getTop() + QVector3D(0.0, sphere.getRadius(), 0.0));
    QVector3D normals[0] = cube.getGlobalCoordinatesOfVector(QVector3D(0.0, 1.0, 0.0));

    bool isIntersecting = checkIntersection(plane_top, normal_top, sphereOldPosition, sphereOldVelocity, lambda);



    normal = normal_top;


    float distance_StartEnd = ((sphereOldPosition + sphereOldVelocity) - sphereOldPosition).length();
    float distance_StartCol = ((sphereOldPosition + lambda*sphereOldVelocity) - sphereOldPosition).length();

    sphereNewPosition = sphereOldPosition + sphereOldVelocity;

    if(isIntersecting){
        if(distance_StartCol <= distance_StartEnd){
            qDebug("collision");
            float geschwindigkeit = sphereOldVelocity.length();
            float lambdaToCollision = (distance_StartCol * lambda/ distance_StartEnd);
            float lambdaFromCollision = (1 - (distance_StartCol / distance_StartEnd))*lambda;

            QVector3D intersectionPoint = sphereOldPosition + lambdaToCollision * sphereOldVelocity;

            QVector3D ballVelocityUnit = sphereOldVelocity.normalized();
            QVector3D sphereNewVelocity;
            //if(geschwindigkeit <= 0.05){
                //sphereNewVelocity = QVector3D(0.0, 0.0, 0.0);
            //}else{
                sphereNewVelocity = (2*(QVector3D::dotProduct(-ballVelocityUnit, normal)) * normal + ballVelocityUnit);
                sphereNewVelocity = sphereNewVelocity * geschwindigkeit;
            //}
            sphereNewPosition = intersectionPoint + lambdaFromCollision * sphereNewVelocity;
            sphere.setDirection(sphereNewVelocity);
        }
    }
    sphere.setPos(sphereNewPosition);
}

bool QOGLWidget::checkIntersection(QVector3D plane_pos, QVector3D plane_normal, QVector3D sphere_pos, QVector3D sphere_direction, float &lambda){
    /*
    qDebug("is in");*/

    float skalarProdukt = QVector3D::dotProduct(sphere_direction, plane_normal);

    if(skalarProdukt == 0.0){               //Wenn das Skalaprodukt 0 ist, sind die Vektoren senkrecht zueinander
        return false;
    }

    lambda = (QVector3D::dotProduct(plane_normal, plane_pos - sphere_pos)/skalarProdukt);

    if(lambda < 0){
        return false;
    }

    return true;
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
        float x = 15 * cosf(step);
        float y = -5.0;
        float z = 15 * sinf(step);
        glColor3f(1.0/i, (1.0/45.0) * i, 0.5);
        glVertex3f(x, y, z);
    }
    glEnd();

    for(int i = 0; i < NR_CUBES; i++){
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
    switch(event->key()){
    case Qt::Key_Return:
        ball.setDirection(QVector3D(0.0, 0.5, 0.0));

        if(selectedCube < NR_CUBES){
            if(!rotationMode){
                rotationMode = true;
                cube[selectedCube].setColor(0.0, 1.0, 0.0);
            }else{
                rotationMode = false;
                cube[selectedCube].setColor(1.0, 0.0, 0.0);
                selectedCube++;
                if(selectedCube < NR_CUBES){
                    cube[selectedCube].setColor(0.0, 0.0, 1.0);
                }
            }
        }
        break;
    case Qt::Key_Right:
        xTran -= 0.05;
        break;
    case Qt::Key_Left:
        xTran += 0.05;
        break;
    case Qt::Key_Up:
        yTran -= 0.05;
        break;
    case Qt::Key_Down:
        yTran += 0.05;
        break;
    }
}

void QOGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastpos = event->pos();
}

void QOGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // Left button: Rotating around x and y axis
    if(event->buttons() == Qt::LeftButton)
    {
        float dx = 0;
        float dy = 0;
        dx = (lastpos.y() - event->y()) * -0.3;
        dy = (lastpos.x() - event->x()) * 0.3;

        changeRotation(dx, dy);
    }

    // Right button: Translating to left/right, near/far
    if(event->buttons() == Qt::RightButton)
    {
        float dx = 0;
        float dy = 0;
        dx = ((lastpos.x() - event->x()) * 0.005) * (-1);
        dy = ((lastpos.y() - event->y()) * 0.005) * (-1);

        if(selectedCube >= NR_CUBES){
            changeTranslation(dx, -dy);
        }else{
            if(!rotationMode){
                QVector3D pos = cube[selectedCube].getPos();
                cube[selectedCube].setPos(QVector3D(pos.x()+dx, pos.y()-dy, pos.z()));
            }else{
                float cubeZRot = cube[selectedCube].getZRot();
                cube[selectedCube].setRotation(0.0, 0.0, cubeZRot - (dx*50));
            }
        }
    }

    lastpos = event->pos();                 //Die aktuelle Mauszeiger Position wird gespeichert
}

void QOGLWidget::wheelEvent(QWheelEvent *event)
{
    float dzoom = event->angleDelta().ry() *0.0005;
    changeZoom(dzoom);
}

void QOGLWidget::changeTranslation(float dx, float dy)
{
    xTran = xTran + dx;
    yTran = yTran + dy;
}

void QOGLWidget::changeZoom(float dzoom)
{
    scale = scale + dzoom;
    if(scale < 0.1){
        scale = 0.1;
    }else if(scale > 2.0){
        scale = 2.0;
    }
}

void QOGLWidget::changeRotation(float dx, float dy)
{
    if(yRot+dy < -90){
        yRot = -90;
    }
    if(yRot+dy > 90){
        yRot = 90;
    }
    if(yRot+dy > -90 && yRot+dy < 90){
        yRot = yRot + dy;
    }

    if(xRot+dx < 0){
        xRot = 0;
    }
    if(xRot+dx > 90){
        xRot = 90;
    }
    if(xRot+dx > 0 && xRot+dx < 90){
        xRot = xRot + dx;
    }
}




