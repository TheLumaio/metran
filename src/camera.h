#ifndef CAMERA_H
#define CAMERA_H

#include <cstdio>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

class Camera
{
private:
    float m_x;
    float m_y;
    float m_zoom;
    
    int m_width;
    int m_height;
    
    bool m_attached;
    
public:
    Camera(float x=0, float y=0, float z=1, int width=1280, int height=720) :
        m_x(x),
        m_y(y),
        m_zoom(z),
        m_width(width),
        m_height(height),
        m_attached(false)
    {
    }
    
    void attach() {
        if (m_attached) {
            printf("Camera already attached!\n");
            return;
        }
        glPushMatrix();
        glTranslatef(floor(m_x+m_width/2), floor(m_y+m_height/2), 0);
        glScalef(m_zoom, m_zoom, 0);
        m_attached = true;
    }
    
    void detach() {
        if (!m_attached) {
            printf("Camera not attached!\n");
            return;
        }
        glPopMatrix();
        m_attached = false;
    }
    
    void moveTo(float x, float y) {
        m_x = x;
        m_y = y;
    }
    
    void move(float dx, float dy) {
        m_x += dx;
        m_y += dy;
    }
    
    void setZoom(float z) {
        m_zoom = z;
    }
    
    float getX() {
        return m_x;
    }
    
    float getY() {
        return m_y;
    }
};

#endif
