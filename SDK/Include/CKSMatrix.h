// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
#ifndef CKSMATRIX_INC
#define CKSMATRIX_INC

#include "ck_export.h"
#include "CKSMath.h"

class CKCoord;
class CKCoord2D;
class CKMatrix;
class CKSCoord;

// AutoDuck comment block
// @doc External SDK
//
// @class This class represents a 4x4 transformation matrix.
// It has functions for operating on <c CKSCoord> objects and
// on other <c CKSMatrix> objects.  It is a transformation
// from local coordinates, generally view or entity coordinates,
// to world coordinates.  Multiplying a CKSCoord by a matrix converts
// it from local to world.  Dividing a CKSCoord by a matrix converts
// it from world to local.
//
// @end In order to reduce both in-memory and on-disk storage,
// several optimizations have been used in this class.  These
// optimizations are transparent to outside classes, but are very
// important when developing new methods in this class.
//
// The size of the <md CKSMatrix::m_adValues> array is rarely going
// to be the full sixteen values of a 4x4 array.  The transformation
// matrices contained inside entities will not contain the fourth column,
// which has only scale and perspective information.
//
// The following are the optimized sizes and their meanings.
//
// 0 : Identity matrix
//
// 1 : One of the 8 standard matrices (2-8).  The single value
// contained in the array is the matrix number.  The value should never
// be 1, since the standard matrix 1 is also the identity matrix, which
// should be represented by the identity matrix above.
//
// 3 : The rotation matrix is the identity matrix, but the translation
// vector found in the 4x4 matrix values [3][0] through [3][2] was
// non-zero.  This offset is stored in values 0 through 2.
//
// 4 : A combination of 1 and 3.  The first number is the standard view
// matrix, the next three are the global offset.
//
// 9 : The matrix contains a full rotation matrix.
//
// 12: The matrix contains a full rotation matrix and an offset vector.
// The rotation matrix is in values 0 through 8, and the vector in values
// 9 through 11
//
// 16: The matrix contains a full 4x4 transformation matrix
class CKSMatrix
    {
    // @Access Public Members
public:
    // @cmember,mfunc Constructors.
    //
    // @@syntax CKSMatrix()
    // @@syntax CKSMatrix(const std::vector<lt>double<gt> &rValues)
    // @@syntax CKSMatrix(const double adValues[16]);
    // @@syntax CKSMatrix(const double adValues[4][4]);
    // @@syntax CKSMatrix(const <c CKSMatrix> &rMatrix)
    // @@parm double | adValues | Array of values to use as the matrix
    // @@parm const std::vector<lt>double<gt> | rValues | Array of values
    // to use as the matrix
    // @@parm const <c CKSMatrix> | rMatrix | Matrix to copy
    CKSMatrix() {}
    CKSMatrix(const std::vector<double> &rValues)
        { if(rValues.size() == 16) m_adValues = rValues; }
    SDK_EXPORT CKSMatrix(const double adValues[16]);
    SDK_EXPORT CKSMatrix(const double adValues[4][4]);
    CKSMatrix(const CKSMatrix &rMatrix)
        { m_adValues = rMatrix.m_adValues; }

    SDK_EXPORT void operator=(const double adValues[16]);
    SDK_EXPORT void operator=(const double adValues[4][4]);
    void operator=(const CKSMatrix &rMatrix)
        { m_adValues = rMatrix.m_adValues; }

    // For internal use only
    CKSMatrix(const CKMatrix &rMatrix);
    void operator=(const CKMatrix &rMatrix);
    operator CKMatrix() const;
    void Set(size_t ulValues, double *pValues);

    // @cmember Do the current matrix values give a valid transformation
    // matrix, with no axial scaling, shearing, or perspective?
    SDK_EXPORT bool IsRigidTransform() const;

    // @cmember bool | IsIdentity() const ||
    // Is the matrix an identity matrix?  This function can
    // currently give false negatives, but never false positives.
    // It doesn't check the values in the matrix, but checks for the
    // special optimization for identity matrices.
    SDK_EXPORT bool IsIdentity() const { return(m_adValues.empty()); }

    // Attempt to convert the matrix to its smallest possible representation.
    SDK_EXPORT void Optimize();

    // Get one of the 8 standard views. return -1 if it is not a standard view
    SDK_EXPORT int GetStandardView ();

// @Group Operations
    // @cmember Transform this matrix using another matrix
    SDK_EXPORT void operator*=(const CKSMatrix &rMatrix);

    // @cmember Transform this matrix using another matrix
    SDK_EXPORT void operator/=(const CKSMatrix &rMatrix);

    // @cmember Compare matrix to another matrix
    SDK_EXPORT bool IsEqualTo(const CKSMatrix &rMatrix, bool bOffset = false) const;

    // @cmember Invert this matrix
    SDK_EXPORT void Invert();

    // @cmember Set this matrix to one of the 8 standard views.
    SDK_EXPORT void SetStandardView(int nViewNumber);

    // @cmember Modifies a <c CKSCoord> by multiplying it by this matrix
    SDK_EXPORT void Multiply(CKSCoord &rCoord) const;

    // @cmember Modifies a <c CKSCoord> by dividing it by this matrix
    SDK_EXPORT void Divide(CKSCoord &rCoord) const;

    // @cmember Applies a CKSCoord offset to the matrix
    SDK_EXPORT void Translate(const CKSCoord &rCoord);

    //@cmember Applies a vector offset to the matrix
    SDK_EXPORT void Translate(double dX, double dY, double dZ);

    // @cmember Translate the matrix using a coordinate in local space
    SDK_EXPORT void TranslateLocal(const CKSCoord &vecOffset);

    // @cmember Translate the matrix using a coordinate in local space
    SDK_EXPORT void TranslateLocal(double dX, double dY, double dZ);

    // @cmember Translate a matrix using a base point
    SDK_EXPORT void TranslateTo(const CKSCoord &rBasePtCoord);

    // @cmember Translate a matrix using a base point
    SDK_EXPORT void TranslateTo(double dX, double dY, double dZ);

    // @cmember Remove any translation component in the matrix.
    SDK_EXPORT void RemoveTranslation();

    // @cmember Rotates the matrix a given angle about an axis
    SDK_EXPORT void Rotate(double dXAng, double dYAng, double dZAng);

    // @cmember Rotates the matrix a given angle about an arbirary axis of
    //          its world space
    SDK_EXPORT void Rotate(double dAng, const CKSCoord &rAxis);

    // @cmember Rotates the matrix a given angle about an arbitrary axis of
    //          its local space
    SDK_EXPORT void RotateLocal(double dAng, const CKSCoord &rAxis);

    // @cmember Rotates the matrix a given angle about its axis of its
    // local space
    SDK_EXPORT void RotateLocal(double dXAng, double dYAng, double dZAng);

    // @cmember Replaces the matrix scale with the given scale value
    SDK_EXPORT void SetScale(double dScale);

    // @cmember Modifies a <c CKSCoord> by dividing it by this matrix
    SDK_EXPORT void VectorMultiply(CKSCoord &rCoord) const;

    // @cmember Modifies a <c CKSCoord> by dividing it by this matrix
    SDK_EXPORT void VectorDivide(CKSCoord &rCoord) const;

// @Group Data access
    // @cmember Fill in an array of doubles with the 4x4 matrix.
    SDK_EXPORT void GetValues(double adValues[16]) const;

    // @cmember Fill in an array of doubles with the 4x4 matrix.
    SDK_EXPORT void GetValues(double adValues[4][4]) const;

    // @cmember Get the scale of a Matrix
    SDK_EXPORT double GetScale() const;

    // @cmember Get the translation value of the matrix.
    SDK_EXPORT CKSCoord GetOffset() const;

    // @Access Private Data
private:
    // @cmember The array of data values for this matrix
    std::vector<double> m_adValues;
    };

typedef std::vector<CKSMatrix> CKSMatrixArray;

// @class A point in 3D space
class SDK_EXPORT CKSCoord
    {
public:
    CKSCoord() : m_dX(0), m_dY(0), m_dZ(0) {}
    CKSCoord(double x, double y, double z) :
            m_dX(x), m_dY(y), m_dZ(z) {}
    CKSCoord(const CKCoord &rCoord);
    CKSCoord(const double dValues[3]) :
        m_dX(dValues[0]), m_dY(dValues[1]), m_dZ(dValues[2]) {}

    CKSCoord &operator=(const CKCoord &rRight);
    operator CKCoord() const;

    // @cmember Multiply this <c CKSCoord> by a <c CKSMatrix>
    inline void operator*=(const CKSMatrix &rMatrix)
        { rMatrix.Multiply(*this); }

    // @cmember Divide this <c CKSCoord> by a <c CKSMatrix>
    inline void operator/=(const CKSMatrix &rMatrix)
        { rMatrix.Divide(*this); }

    // @cmember bool | operator== | (const CKSCoord &rRight) |
    // Compare this coordinate to another coordinate, within the
    // default tolerance of <c CKSMath>.
    inline bool operator==(const CKSCoord &rRight) const
        {return(CKSMath::EqualPoints(*this, rRight));}

    // @cmember bool | operator!= | (const CKSCoord &rRight) |
    // Compare this coordinate to another coordinate, within the
    // default tolerance of <c CKSMath>.
    inline bool operator!=(const CKSCoord &rRight) const
        {return(!CKSMath::EqualPoints(*this, rRight));}

    // @cmember CKSCoord | operator+() const | const CKCoord & |
    // Returns a <c CKSCoord> that is the sum of this
    // and another <c CKSCoord>.
    inline CKSCoord operator+(const CKSCoord &rC) const
        {
        return(CKSCoord(m_dX + rC.m_dX, m_dY + rC.m_dY, m_dZ + rC.m_dZ));
        }

    // @cmember CKSCoord | operator-() const | const CKSCoord & | Returns
    // a <c CKSCoord> that is the difference between this
    // and another <c CKSCoord>.
    inline CKSCoord operator-(const CKSCoord &rC) const
        {
        return(CKSCoord(m_dX - rC.m_dX, m_dY - rC.m_dY, m_dZ - rC.m_dZ));
        }

    // @cmember CKSCoord | operator-() const ||
    // Returns a <c CKSCoord> that is the negative of this <c CKSCoord>.
    inline CKSCoord operator-() const { return(CKSCoord(-m_dX, -m_dY, -m_dZ)); }

    // @cmember Modify this coordinate by scaling all values by a value dScale
    void operator/=(double dScale);

    // @cmember Modify this coordinate by scaling all values by a value dScale
    void operator*=(double dScale)
        { SetValues(m_dX * dScale, m_dY * dScale, m_dZ * dScale); }

    // @cmember Returns a <c CKSCoord> that is this <c CKSCoord> scaled by
    // a value <p dScale>
    CKSCoord operator/(double dScale);

    // @cmember Returns a <c CKSCoord> that is this <c CKSCoord> scaled by
    // a value <p dScale>
    CKSCoord operator*(double dScale)
        { return(CKSCoord(m_dX * dScale, m_dY * dScale, m_dZ * dScale)); }

    // @cmember Returns a <c CKSCoord> that is this <c CKSCoord> multiplied
    // by a <c CKSMatrix>
    CKSCoord operator*(const CKSMatrix &rMatrix) const;

    // @cmember Returns a <c CKSCoord> that is this <c CKSCoord> multiplied
    //          by the inverse of the <c CKSMatrix> (i.e. divided by)
    CKSCoord operator/(const CKSMatrix &rMatrix) const;

    // @cmember The magnitude of the Coord
    double Magnitude() const;

    // @cmember The magnitude squared of the Coord
    double MagnitudeSq() const;

    // @cmember Compute the angle of this Coord
    double Angle() const;

    // Compute the dot product of this coord and another coord
    double Dot(const CKSCoord &rRight) const;

    // Compute the cross product of this coord and another coord
    CKSCoord Cross(const CKSCoord &rRight) const;

    // @cmember convert this Coord t a unit vector
    void Normalize();

    // @cmember Set the members of this Coord individually
    void SetValues(double dX, double dY, double dZ);

    // @cmember Set the members of this Coord through an array
    void SetValues(const double adValues[3]);


    // @cmember Allows access to the x, y and z values by index
    double operator[](size_t n) const
        {
        switch(n)
            {
            // Default is to avoid a compiler warning.
            // THIS should NEVER be used.
            default:
//                ASSERT(FALSE);
            case 0: return(m_dX);
            case 1: return(m_dY);
            case 2: return(m_dZ);
            }
        }

    // @cmember Allows access to the x, y and z values by index
    double &operator[](size_t n)
        {
        switch(n)
            {
            // Default is to avoid a compiler warning.
            // THIS should NEVER be used.
            default:
//                ASSERT(FALSE);
            case 0: return(m_dX);
            case 1: return(m_dY);
            case 2: return(m_dZ);
            }
        }

    // @cmember The x, y, and z values of the Coord
    double m_dX, m_dY, m_dZ;
    };

typedef std::vector<CKSCoord> CKSCoordArray;

// @class A point in 2D space
class CKSCoord2D
    {
public:
    CKSCoord2D() : m_dX(0), m_dY(0) {}
    CKSCoord2D(double x, double y) : m_dX(x), m_dY(y) {}
    CKSCoord2D(const CKCoord2D &rCoord);

    CKSCoord2D &operator=(const CKCoord2D &rRight);
    operator CKCoord2D() const;

    // @cmember Compare this coordinate to another coordinate, within the
    // default tolerance of <c CKSMath>.
    SDK_EXPORT bool operator==(const CKSCoord2D &rRight) const;

    // @cmember Compare this coordinate to another coordinate, within the
    // default tolerance of <c CKSMath>.
    SDK_EXPORT bool operator!=(const CKSCoord2D &rRight) const;

    // @cmember Allows access to the x and y values by index
    double operator[](size_t n) const
        {
        switch(n)
            {
            // Default is to avoid a compiler warning.
            // THIS should NEVER be used.
            default:
//                ASSERT(FALSE);
            case 0: return(m_dX);
            case 1: return(m_dY);
            }
        }

    // @cmember Allows access to the x and y values by index
    double &operator[](size_t n)
        {
        switch(n)
            {
            // Default is to avoid a compiler warning.
            // THIS should NEVER be used.
            default:
//                ASSERT(FALSE);
            case 0: return(m_dX);
            case 1: return(m_dY);
            }
        }

    // @cmember The x and y values of the point
    double m_dX, m_dY;
    };

#endif