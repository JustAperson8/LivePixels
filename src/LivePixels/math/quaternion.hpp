//
// Created by daniil on 18.08.20.
//

#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <iostream>
#include <cmath>

namespace lp
{
    template<class T = float>
    class Quaternion
    {
    private:
        T m_s, m_x, m_y, m_z;

    public:
        //region constructor && copy && destructor
    Quaternion(T s, T x, T y, T z)
            : m_s(s), m_x(x), m_y(y), m_z(z)
        {}

        Quaternion(const Quaternion &q)
            : m_s(q.m_s), m_x(q.m_x), m_y(q.m_y), m_z(q.m_z)
        {}

        Quaternion &operator=(const Quaternion &q)
        {
            m_s = q.m_s;
            m_x = q.m_x;
            m_y = q.m_y;
            m_z = q.m_z;
            return *this;
        }

        virtual ~Quaternion() = default;
        //endregion

    public:
	//region Getters && Setters
	[[nodiscard]] T getS() const { return m_s; }

	void setS(T mS) { m_s = mS; }

	[[nodiscard]] T getX() const { return m_x; }

	void setX(T mX) { m_x = mX; }

	[[nodiscard]] T getY() const { return m_y; }

	void setY(T mY) { m_y = mY; }

	[[nodiscard]] T getZ() const { return m_z; }

	void setZ(T mZ) { m_z = mZ; }
	//endregion

    public:
        //region += && -= && *=
        Quaternion &operator+=(const Quaternion &q)
        {
            m_s += q.m_s;
            m_x += q.m_x;
            m_y += q.m_y;
            m_z += q.m_z;
            return *this;
        }

        Quaternion &operator-=(const Quaternion &q)
        {
            m_s -= q.m_s;
            m_x -= q.m_x;
            m_y -= q.m_y;
            m_z -= q.m_z;
            return *this;
        }

        Quaternion &operator*=(const Quaternion &q)
        {
            T n_s, n_x, n_y, n_z;
            n_s = m_s * q.m_s - m_x * q.m_x - m_y * q.m_y - m_z * q.m_z;
            n_x = m_s * q.m_x + q.m_s * m_x + m_y * q.m_z - q.m_y * m_z;
            n_y = m_s * q.m_y + q.m_s * m_y + m_z * q.m_x - q.m_z * m_x;
            n_z = m_s * q.m_z + q.m_s * m_z + m_x * q.m_y - q.m_x * m_y;
            m_s = n_s;
            m_x = n_x;
            m_y = n_y;
            m_z = n_z;
            return *this;
        }

	Quaternion &operator/=(T num)
	{
	    m_s /= num;
	    m_x /= num;
	    m_y /= num;
	    m_z /= num;
	    return *this;
	}
        //endregion

    public:
        //region friend + && - && *
        friend Quaternion operator+(const Quaternion &q1, const Quaternion &q2)
        {
            Quaternion nq(q1);
            return nq += q2;
        }

        friend Quaternion operator-(const Quaternion &q1, const Quaternion &q2)
        {
            Quaternion nq(q1);
            return nq -= q2;
        }

        friend Quaternion operator*(const Quaternion &q1, const Quaternion &q2)
        {
            Quaternion nq(q1);
            return nq *= q2;
        }
        //endregion

        friend Quaternion operator/(Quaternion q1, const T num)
        {
            return q1 /= num;
        }

    public:
        T abs()
        {
            return std::sqrt(m_s * m_s + m_x * m_x + m_y * m_y + m_z * m_z);
        }

	Quaternion<T> conjugate()
	{
	    return {m_s, -m_x, -m_y, -m_z};
	}

	Quaternion<T> normal()
	{
	    T a = abs();
	    return {m_s / a, m_x / a, m_y / a, m_z / a};
	}

	Quaternion<T> inverse()
	{
	    T a = abs();
	    return conjugate() / (a * a);
	}

    public:
        friend std::ostream &operator<<(std::ostream &out, const Quaternion &q1)
        {
            out << q1.m_s << " + " << q1.m_x << "i" << " + " << q1.m_y << "j" << " + " << q1.m_z << "k";
            return out;
        }
    };
}

#endif //QUATERNION_HPP
