#include "qoglwidget.h"
#include <cmath>
#include <QDebug>
#include "cylinder.h"
#include "sphere.h"
#include "cube.h"

int selectedCube = 0;
bool cylinderSet = true;
bool rotationMode = false;
bool gameStarted = false;
static constexpr float GRAVITY = 0.00981f;
static constexpr float REIBUNGSKONSTANTE = 0.1;

QOGLWidget::QOGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    xRot = 25;
    yRot = 0.0; //-25.0

    xTran = 0.0;
    yTran = 0.0;
    zTran = 0.0;

    scale = 0.5;

    timer_game = new QTimer(this);                              //Ein Spieltimer wird erstellt der in bestimmten intervallen das Spiel vorantreibt
    timer_game->start(10);                                      //Timer soll alle 34 millisekunden auslösen (entspricht etwa 30 fps (17/1000 ~ 60fps))


    ball = Sphere(QVector3D(0.0, 15.0, 0.0), 0.5, 0.5);               //Die Spielkugel wird erstellt
    ball.setColor(0.2, 1.0, 0.8);
    ball.setDirection(QVector3D(0.0, 0.0, 0.0));

    goal = Cube(QVector3D(0.0, -7.0, 0.0), 2, 5.0, 1.5);
    goal.setColor(0.7, 0.2, 0.7);

    obstacle = Cube(QVector3D(0.0, 0.0, 0.0), 20, 3, 1.1);
    obstacle.setColor(0.3, 0.3, 0.3);

    cylinder = Cylinder(QVector3D(0.0, 10.0, 0.0), 2, 1);
    cylinder.setColor(0.3, 0.3, 0.3);
    cylinder.setRotation(90, 0, 0);

    for(int i = 0; i < NR_CUBES; i++){
        cube[i] = Cube(QVector3D((i-2)*4.25, 6.0, 0.0), 4.0, 1.0, 1.0);
        cube[i].setRotation(0.0, 0.0, 0.0);
        cube[i].setColor(0.7, 0.4, 0.2);
    }

    setFocusPolicy(Qt::ClickFocus);                                     //Muss aktiviert sein, damit das Widget Key Events annimmt (da KeyEvents Fokus benötigen)
    connect(timer_game, SIGNAL(timeout()), this, SLOT(gameUpdate()));   //Immer wenn der Timer tickt, wird das SIGNAL vom SLOT gameUpdate() aufgefangen
}

QOGLWidget::~QOGLWidget()
{
}

//Die Metode dient zur physikalischen berechnung der Collision
void QOGLWidget::gameUpdate(){

    if(gameStarted){
        QVector3D gravitation = QVector3D(0.0, - GRAVITY, 0.0) * ball.getMass();        //Erdanziehungskraft
        QVector3D luftreibung = - ball.getDirection().normalized() * REIBUNGSKONSTANTE * ball.getDirection().lengthSquared(); //Luftwiderstand
        ball.setDirection(ball.getDirection() + gravitation + luftreibung);           //Neue geschwindigkeit ist alte Geschwindigkeit + Erdanziehungskraft + Reibungskraft

        QVector3D collision_point;
        QVector3D collision_normal;
        QVector3D sphere_newPosition = ball.getPos() + ball.getDirection();
        float lambda;

        for(int i = 0; i < NR_CUBES; i++){ //alle cubes werden nach collision getestet
            //alle cubes nach intersion testen, wenn sie intersionen, zeit ausrechnen bis zum intersionen und je nachdem welche zeit am geringsten ist, wird mit collision behandelt
            if(checkCollision(cube[i], ball, collision_point, collision_normal, lambda)){
                float geschwindigkeit = ball.getDirection().length();
                QVector3D ballVelocityUnit = ball.getDirection().normalized();
                QVector3D sphereNewVelocity;
                //if(geschwindigkeit <= 0.04){
                    //sphereNewVelocity = QVector3D(0.0, 0.0, 0.0);
                //}else{
                    sphereNewVelocity = (2*(QVector3D::dotProduct(-ballVelocityUnit, collision_normal)) * collision_normal + ballVelocityUnit);
                    sphereNewVelocity = sphereNewVelocity * geschwindigkeit;
                //}
                sphere_newPosition = collision_point + lambda * sphereNewVelocity;
                ball.setDirection(sphereNewVelocity);
                cube[i].setColor(1, 0.7, 0.5);
            }else{
                cube[i].fadeToColor(0.7, 0.4, 0.2);
            }
        }

        if(checkCollision(obstacle, ball, collision_point, collision_normal, lambda)){
            float geschwindigkeit = ball.getDirection().length();
            QVector3D ballVelocityUnit = ball.getDirection().normalized();
            QVector3D sphereNewVelocity;
            if(geschwindigkeit <= 0.04 && collision_normal != QVector3D(0.0, 1.0, 0.0)){
                sphereNewVelocity = QVector3D(0.0, 0.0, 0.0);
            }else{
                sphereNewVelocity = (2*(QVector3D::dotProduct(-ballVelocityUnit, collision_normal)) * collision_normal + ballVelocityUnit);
                sphereNewVelocity = sphereNewVelocity * geschwindigkeit;
            }
            sphere_newPosition = collision_point + lambda * sphereNewVelocity;
            ball.setDirection(sphereNewVelocity);
        }

        if(checkCollision(cylinder, ball, collision_normal)){
            double p = 2 * (QVector3D::dotProduct(ball.getDirection(), collision_normal)) / ball.getMass();
            ball.setDirection(ball.getDirection() - p * ball.getMass()* collision_normal);
            sphere_newPosition = (ball.getPos() + ball.getDirection());
        }

        if(checkCollision(goal, ball, collision_point, collision_normal, lambda)){
            for(int i = 0; i < NR_CUBES; i++){
                cube[i].fadeToColor(0.3, 0.3, 0.3);
            }
            ball.fadeToColor(0.0, 1.0, 0.0);
            goal.fadeToColor(0.0, 1.0, 0.0);
            gameStarted = false;
        }

        ball.setPos(sphere_newPosition);
    }
    update();
}

bool QOGLWidget::checkCollision(Cylinder& cylinder, Sphere& sphere, QVector3D& normal){

    float dx = -2*sphere.getPos().x()*cylinder.getPos().x() + sphere.getPos().x()*sphere.getPos().x() + cylinder.getPos().x()*cylinder.getPos().x();
    float dy = -2*sphere.getPos().y()*cylinder.getPos().y() + sphere.getPos().y()*sphere.getPos().y() + cylinder.getPos().y()*cylinder.getPos().y();



    if(dx + dy <= (pow(cylinder.getRadius() + sphere.getRadius(), 2))){
        normal = (sphere.getPos() - cylinder.getPos()).normalized();

        return true;
    }
    return false;
}

bool QOGLWidget::checkCollision(Cube& cube, Sphere& sphere, QVector3D& collision_point, QVector3D& collision_normal, float& lambda){ //könnte hiermit zusammenhängen

    QVector3D sphereOldPosition = sphere.getPos();
    QVector3D sphereOldVelocity = sphere.getDirection();
    float radius = sphere.getRadius();
    Plane planes[4];

    planes[0] = cube.getTopPlane();
    planes[0].setPos(planes[0].getPos() + radius * planes[0].getNormal());
    planes[1] = cube.getBottomPlane();
    planes[1].setPos(planes[1].getPos() + radius * planes[1].getNormal());
    planes[2] = cube.getRightPlane();
    planes[2].setPos(planes[2].getPos() + radius * planes[2].getNormal());
    planes[3] = cube.getLeftPlane();
    planes[3].setPos(planes[3].getPos() + radius * planes[3].getNormal());

    for(int i = 0; i < 4; i++){
        QVector3D plane = planes[i].getPos();
        QVector3D normal = planes[i].getNormal();
        bool isIntersecting = checkIntersection(plane, normal, sphereOldPosition, sphereOldVelocity, lambda);
        if(isIntersecting){
            float distance_StartEnd = ((sphereOldPosition + sphereOldVelocity) - sphereOldPosition).length();
            float distance_StartCol = ((sphereOldPosition + lambda*sphereOldVelocity) - sphereOldPosition).length();

            if(distance_StartCol <= distance_StartEnd){
                float lambdaToCollision = (distance_StartCol * lambda / distance_StartEnd);

                collision_point = sphereOldPosition + lambdaToCollision * sphereOldVelocity;

                if(isPointInCubePlane(collision_point, planes[i])){
                    collision_normal = planes[i].getNormal();
                    lambda = (1 - (distance_StartCol / distance_StartEnd))*lambda;
                    return true;
                }
            }
        }
    }

    return false;
}

bool QOGLWidget::isPointInCubePlane(QVector3D point, Plane &plane){
    float distance_point_plane = point.distanceToPoint(plane.getPos());

    if(distance_point_plane >= plane.getLength()/2.0){   //prüft ob der Punkt außerhalb der bounds der plane ist
        if( distance_point_plane > (plane.getLength()/2.0)+(ball.getRadius())){
            return false;
        }
        //radius - delta vom überstieg = neuer normalen vektor (normieren nicht vergessen)
        QVector3D planeToPoint = point - plane.getPos();
        QVector3D planeToEnd;
        planeToEnd = (plane.getPos() + (ball.getRadius() + plane.getLength()/2.0) * planeToPoint.normalized()) - plane.getPos();
        QVector3D newNormal = ((planeToEnd - planeToPoint) + plane.getNormal()).normalized();

        qDebug("collided normal: x: %f, y: %f", plane.getNormal().x(), plane.getNormal().y());
        plane.setNormal(newNormal);
    }

    return true;
}

bool QOGLWidget::checkIntersection(QVector3D plane_pos, QVector3D plane_normal, QVector3D sphere_pos, QVector3D sphere_direction, float &lambda){

    float skalarProdukt = QVector3D::dotProduct(sphere_direction, plane_normal);

    if(skalarProdukt == 0.0){               //Wenn das Skalaprodukt 0 ist, sind die Vektoren senkrecht zueinander
        return false;
    }

    lambda = (QVector3D::dotProduct(plane_normal, plane_pos - sphere_pos)/skalarProdukt);


    if((sphere_pos+sphere_direction).distanceToPlane(plane_pos, plane_normal) > 0){
        return false;
    }

    if(lambda < 0){                         //Wenn Lambda < 0 ist dann fliegt die Kugel nicht richtung ebene
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

    /*//Ein Bunter Boden wird erstellt
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    for(int i = 0; i < 45; i++){
        float delta = (2.0f * M_PI) / 45;
        float step = i*delta;
        float x = 15 * cosf(step);
        float y = -15.0;
        float z = 15 * sinf(step);
        glColor3f(1.0/i, (1.0/45.0) * i, 0.5);
        glVertex3f(x, y, z);
    }
    glEnd();*/

    for(int i = 0; i < NR_CUBES; i++){
        cube[i].draw();
    }
    obstacle.draw();
    if(gameStarted){
        QVector3D ballpos = ball.getPos();
        ball.fadeToColor(0.5 + ballpos.x()/18, 0.5 + ballpos.y()/18, ballpos.x()/ballpos.y());
    }
    ball.draw();
    goal.draw();
    cylinder.draw();

    glPopMatrix();
    //----------------------------DRAW EVERYTHING
}

void QOGLWidget::initializeGL()
{
    //OpenGL Funktionen werden geladen und initialisiert
    initializeOpenGLFunctions();

    //Hintergrundfarbe wird gesetzt
    glClearColor(0.5,0.5,0.9,1);

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
        ball.setPos(QVector3D(0.0, 15.0, 0.0));
        if(cylinderSet){
            cylinderSet = false;
            cube[0].fadeToColor(1.0, 1.0, 1.0);
            return;
        }
        if(selectedCube < NR_CUBES){
            if(!rotationMode){
                rotationMode = true;
                cube[selectedCube].fadeToColor(0.8, 0.8, 0.8);
            }else{
                rotationMode = false;
                cube[selectedCube].fadeToColor(0.6, 0.6, 0.6);
                selectedCube++;
                if(selectedCube < NR_CUBES){
                    cube[selectedCube].fadeToColor(1.0, 1.0, 1.0);
                }else{
                    if(!cylinderSet){
                        gameStarted = true;
                    }
                }
            }
        }
        break;
    case Qt::Key_Right:
        xTran -= 0.1;
        break;
    case Qt::Key_Left:
        xTran += 0.1;
        break;
    case Qt::Key_Up:
        yTran -= 0.1;
        break;
    case Qt::Key_Down:
        yTran += 0.1;
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
            if(cylinderSet){
                QVector3D pos = cylinder.getPos();
                cylinder.setPos(QVector3D(pos.x()+dx, pos.y()-dy, pos.z()));
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
    if(scale < 0.4){
        scale = 0.4;
    }else if(scale > 1.0){
        scale = 1.0;
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
    if(xRot+dx > 70){
        xRot = 70;
    }
    if(xRot+dx > 0 && xRot+dx < 70){
        xRot = xRot + dx;
    }
}




