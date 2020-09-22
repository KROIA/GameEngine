#include "vector.h"

Vector::Vector()
{
    m_length = 1;
    m_angle  = 0;


    m_x = cos(m_angle) * m_length;
    m_y = sin(m_angle) * m_length;
}
Vector::Vector(double angle, double length)
{
    this->setAngle(angle);
    this->setLength(length);
}
Vector::Vector(const Vector&vec)
{
    this->m_angle = vec.m_angle;
    this->m_length = vec.m_length;
    this->m_x = vec.m_x;
    this->m_y = vec.m_y;
}
Vector::~Vector()
{
    //qDebug() << "~Vector()";
}

void Vector::setLength(double length)
{
    if(length < 0)
    {
        setAngle(m_angle+M_PI); // change direction 180deg
        length = -length;
    }
    m_length = length;
    m_x = cos(m_angle) * m_length;
    m_y = sin(m_angle) * m_length;
}
void Vector::setAngle(double rad)
{
    m_angle = fmod(rad,2*M_PI);// Normalize to 0 - 2Pi
    if(m_angle < 0)
        m_angle+=2*M_PI;
    m_x = cos(m_angle) * m_length;
    m_y = sin(m_angle) * m_length;
}
void Vector::rotate(double rad)
{
    this->setAngle(m_angle+rad);
}
void Vector::setX(double x)
{
    m_x = x;
    double y1 = this->getY();
    m_length = sqrt(pow(y1,2)+pow(m_x,2));
    if(m_length < 0.0000001)
    {
        m_length = 0;
        m_angle = 0;
    }
    else
        m_angle = acos(m_x/m_length);
    if(y1 < 0)
        this->setAngle(2*M_PI-m_angle);
    //if(x < 0)
    //    this->setAngle(M_PI-m_angle);
}
void Vector::setY(double y)
{
    m_y = y;
    double x1 = this->getX();
    m_length = sqrt(pow(x1,2)+pow(m_y,2));
    if(m_length < 0.0000001)
    {
        m_length = 0;
        m_angle = 0;
    }
    else
        m_angle = asin(m_y/m_length);
    if(x1 < 0)
        this->setAngle(M_PI-m_angle);
   // if(y<0)
   //     this->setAngle(2*M_PI-m_angle);
}

double Vector::getLength() const
{
    return m_length;
}
double Vector::getAngle() const
{
    return m_angle;
}

double Vector::getX() const
{
    return m_x;
}
double Vector::getY() const
{
    return m_y;
}

Vector &Vector::operator+=(const Vector &vec)
{
    Vector sum = *this+vec;
    this->setAngle(sum.getAngle());
    this->setLength(sum.getLength());
    return *this;
}
Vector &Vector::operator+=(const std::vector<Vector> &vecList)
{
    if(vecList.size() == 0)
        return *this;
    Vector sum = *this;
    for(size_t element=0; element<vecList.size(); element++)
    {
        sum += vecList[element];
    }
    *this = sum;
    return *this;
}
Vector Vector::operator+(const Vector &vec) const
{
    double x1 = this->getX();
    double y1 = this->getY();

    double x2 = vec.getX();
    double y2 = vec.getY();

    double x3 = x1 + x2;
    double y3 = y1 + y2;
    Vector res;
    res.setX(x3);
    res.setY(y3);
    return res;
}
Vector &Vector::operator++()
{
    *this*=2;
    return *this;
}


Vector &Vector::operator-=(const Vector &vec)
{
    Vector div = *this-vec;
    this->setAngle(div.getAngle());
    this->setLength(div.getLength());
    return *this;
}
Vector &Vector::operator-=(const std::vector<Vector> &vecList)
{
    if(vecList.size() == 0)
        return *this;
    Vector div = *this;
    for(size_t element=0; element<vecList.size(); element++)
    {
        div -= vecList[element];
    }
    *this = div;
    return *this;
}
Vector Vector::operator-(const Vector &vec) const
{
    double x1 = this->getX();
    double y1 = this->getY();

    double x2 = vec.getX();
    double y2 = vec.getY();

    double x3 = x1 - x2;
    double y3 = y1 - y2;
    Vector res;
    res.setX(x3);
    res.setY(y3);
    return res;
}

Vector &Vector::operator*=(const double &scalar)
{
    Vector product = *this*scalar;
    this->setAngle(product.getAngle());
    this->setLength(product.getLength());
    return *this;
}
Vector Vector::operator*(const double &scalar) const
{
    return Vector(m_angle,m_length*scalar);
}

Vector &Vector::operator=(const Vector &vec)
{
    this->setAngle(vec.getAngle());
    this->setLength(vec.getLength());
    return *this;
}
bool Vector::operator==(const Vector &vec)
{
    /*bool res = false;
    if(m_angle == vec.m_angle && m_length == vec.m_length)
        res = true;

    return res;*/

    return static_cast<bool>(abs(m_angle - vec.m_angle) + abs(m_length - vec.m_length));
}

std::string Vector::toString() const
{
    return "direction: "+std::to_string(this->m_angle)+"rad, "+
            std::to_string(Vector::radToDeg(this->m_angle)) + "deg "+
            "  length: "+std::to_string(this->m_length);
}
double Vector::radToDeg(const double &rad)
{
    double deg = fmod(rad*180/M_PI,360);
    if(deg < 0)
        deg+=360;
    return deg;
}
double Vector::degToRad(const double &deg)
{
    double rad = fmod(deg*M_PI/180,360);
    if(rad < 0)
        rad+=2*M_PI;
    return rad;
}

double Vector::getDotProduct(const Vector &vec1,const Vector &vec2)
{
    return vec1.getX() * vec2.getX() +
           vec1.getY() * vec2.getY();
}
double Vector::getAngle(const Vector &vec1,const Vector &vec2)
{
    if((vec1.m_length * vec2.m_length) == 0)
    {
        qDebug() << "Vector::getAngle(const Vector &vec1,const Vector &vec2): no length";
        return 0;
    }
    return acos(Vector::getDotProduct(vec1,vec2) / (vec1.m_length * vec2.m_length));
}
Vector Vector::getAverage(const std::vector<Vector> &list)
{
    Vector vec(0,0);
    if(list.size() == 0)
        return vec;
    for(size_t i=0; i<list.size(); i++)
    {
        vec += list[i];
    }
    vec *= (1/(double)list.size());
    return vec;
}
