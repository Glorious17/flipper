#include "qoglwidget.h"

QOGLWidget::QOGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    xRot = 25.0;
    yRot = 0.0; //-25
    zRot = 0;

    xTran = 0;
    yTran = 0;

    scale = 1.0;
}

QOGLWidget::~QOGLWidget()
{
}

void QOGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,0,0,1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /*float ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
    float specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
    float specularity[] = { 1.0, 1.0, 1.0, 1.0 };
    float shininess[] = { 60.0 };*/

    //LIGHT 0
    float light_ambient0[] = { 0.2f, 0.2f, 0.2f, 1.f };
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient0);
    //glEnable(GL_LIGHT0);

    //LIGHT 1
    float light_position1[] = {0.0f, 2.0f, 4.0f, 1.f };
    glLightfv(GL_LIGHT1, GL_POSITION,  light_position1);
    float light_diffuse1[] = {0.8f, 0.8f, 0.8f, 1.f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse1 );
    glEnable(GL_LIGHT1);

    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    /*// Properties of the objects' materials
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularity); // Reflectance
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess); // Shininess

    // Enable ambient light usage
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);*/
}

void QOGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void QOGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-5, 5, -5, 5, -5, 5);
    //glFrustum(-10, 10, -10, 10, -10, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //rotate
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    //drawQuad(QVector3D(0.0, 0.0, 0.0), 50, 0.05, 0.05); //X ACHSE
    //drawQuad(QVector3D(0.0, 0.0, 0.0), 0.05, 50, 0.05); //Y ACHSE
    //drawQuad(QVector3D(0.0, 0.0, 0.0), 0.05, 0.05, 50); //Z ACHSE

    //PLANE
    glColor4f(1, 1, 1, 0.3);
    glBegin(GL_QUADS);
    glVertex3f(-50, -2, -50);
    glVertex3f(50, -2, -50);
    glVertex3f(50, -2, 50);
    glVertex3f(-50, -2, 50);
    glEnd();

    //rechts/links | oben/unten | vorne/hinten
    glTranslatef(xTran, yTran, 0.0);

    //scale view
    glScalef(scale, scale, scale); // Scale along all axis

    //light position
    float lightPosition1[] = { 0.0, 2.0, 4.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);

    //draw everything
    glPushMatrix();

    cube1.setColor(0.0, 1.0, 0.1);
    cube1.setPos(QVector3D(0.0, 1.0, 3.0));
    cube1.draw();

    cylinder1.draw();

    glColor3f(1.0,1.0,1.0);
    drawSphere(QVector3D(0.0, 0.35, 0.0), 0.15);

    glPopMatrix();
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
        dx = ((lastpos.x() - event->x()) * 0.005) * (-1);
        dy = ((lastpos.y() - event->y()) * 0.005) * (1);

        // Now let the world know that we want to translate
        emit changeTranslation( dx, dy );
    }

    // Make the current position the starting point for the next dragging step
    lastpos = event->pos();
}

void QOGLWidget::wheelEvent(QWheelEvent *event)
{
    float dzoom = event->angleDelta().ry() *0.0005;
    emit changeZoom(dzoom);
}

void QOGLWidget::onChangeTranslation(float dx, float dy)
{
    // To apply the requested Translation deltas, we increment...
    xTran = xTran + dx;
    yTran = yTran + dy;

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
    yRot = yRot + dy;
    zRot = zRot + dz;
    update();
}

void QOGLWidget::drawSphere(QVector3D pos, float rad,
                            int nr_lat, int nr_lon )
{
    // Angle delta in both directions
    const float lat_delta = M_PI / float( nr_lat );
    const float lon_delta = M_PI / float( nr_lon );

    // Create horizontal stripes of squares
    for( float lon = 0.0f; lon < 1.0f*M_PI; lon += lon_delta )
    {
        glBegin( GL_QUAD_STRIP ) ;
        for( float lat = 0.0f; lat <= 2.0f*M_PI; lat += lat_delta )
        {
            // Each iteration adds another square, the other vertices
            // are taken from the existing stripe
            float xn1 = cosf( lat ) * sinf( lon );
            float yn1 = sinf( lat ) * sinf( lon );
            float zn1 = cosf( lon );

            // Set normal vector (important for lighting!)
            glNormal3f( xn1, yn1, zn1 );
            glVertex3f( pos.x()+rad*xn1, pos.y()+rad*yn1, pos.z()+rad*zn1 );

            float xn2 = cosf( lat ) * sinf( lon + lon_delta );
            float yn2 = sinf( lat ) * sinf( lon + lon_delta );
            float zn2 = cosf( lon + lon_delta );

            glNormal3f( xn2, yn2, zn2 );
            glVertex3f( pos.x()+rad*xn2, pos.y()+rad*yn2, pos.z()+rad*zn2 );
        }
        glEnd() ;
    }
}




