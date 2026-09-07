#ifndef LEGACYOPENGLFUNCTIONS_H
#define LEGACYOPENGLFUNCTIONS_H

#include <QOpenGLContext>
#include <QOpenGLFunctions_2_1>
#include <QtGlobal>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QOpenGLVersionFunctionsFactory>
#endif

// QOpenGLFunctions_2_1 itself is deliberately non-copyable. Game objects are
// stored and assigned by value, so they use this stateless, copyable forwarding
// wrapper instead of inheriting Qt's function table directly.
class LegacyOpenGLFunctions
{
protected:
    static QOpenGLFunctions_2_1 *functions()
    {
        QOpenGLContext *context = QOpenGLContext::currentContext();
        Q_ASSERT(context);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        QOpenGLFunctions_2_1 *result =
            QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_2_1>(context);
#else
        QOpenGLFunctions_2_1 *result =
            context->versionFunctions<QOpenGLFunctions_2_1>();
#endif

        Q_ASSERT(result);
        return result;
    }

    void glPushMatrix() { functions()->glPushMatrix(); }
    void glPopMatrix() { functions()->glPopMatrix(); }
    void glTranslatef(float x, float y, float z) { functions()->glTranslatef(x, y, z); }
    void glRotatef(float angle, float x, float y, float z) { functions()->glRotatef(angle, x, y, z); }
    void glColor3f(float red, float green, float blue) { functions()->glColor3f(red, green, blue); }
    void glBegin(unsigned int mode) { functions()->glBegin(mode); }
    void glEnd() { functions()->glEnd(); }
    void glNormal3f(float x, float y, float z) { functions()->glNormal3f(x, y, z); }
    void glVertex3f(float x, float y, float z) { functions()->glVertex3f(x, y, z); }
};

#endif // LEGACYOPENGLFUNCTIONS_H
