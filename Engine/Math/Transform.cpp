#include "pch.h"
#include "Transform.h"

namespace gk
{
    std::istream& operator >> (std::istream& stream, Transform& transform)
    {
        stream >> transform.position;
        stream >> transform.scale;
        stream >> transform.angle;

        return stream;
    }

    void Transform::Update()
    {
        Matrix33 mxScale;
        mxScale.Scale(scale);

        Matrix33 mxRotate;
        mxRotate.Rotate(angle);

        Matrix33 mxTranslate;
        mxTranslate.Translate(position);

        matrix = mxScale * mxRotate * mxTranslate;
    }

    void Transform::Update(const Matrix33& mx)
    {
        Update();

        matrix = matrix * mx;
    }
}

