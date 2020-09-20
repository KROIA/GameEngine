#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <math.h>
#include <string>
#include <QDebug>


class Vector
{
    public:
        Vector();
        Vector(double angle, double length);
        Vector(const Vector&vec);
        virtual ~Vector();

        void setLength(double length);
        void setAngle(double rad);

        void setX(double x);
        void setY(double y);

        double getLength() const;
        double getAngle() const;

        double getX() const;
        double getY() const;

        Vector &operator+=(const Vector &vec); // adds a vector to it
        Vector &operator+=(const std::vector<Vector> &vecList);
        Vector operator+(const Vector &vec) const; // adds it self and the other vector and gives the resault back
        Vector &operator++(); // doubles its length


        Vector &operator*=(const double &scalar); // scales its length
        Vector operator*(const double &scalar) const; // scales its length and gives the resault back

        Vector &operator=(const Vector &vec);
        bool operator==(const Vector &vec);

        std::string toString() const;
        static double radToDeg(const double &rad);
        static double degToRad(const double &deg);

    private:
        double m_angle; //Rad
        double m_length;

};

#endif
