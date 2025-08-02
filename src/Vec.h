#pragma once
#include "Matrix.h"
class Vec : public Matrix
{
public:
    Vec(const std::vector<float>& v) :Matrix(v.size(), 1) { for (int i = 0; i < v.size(); ++i) { Set(i, 0, v.at(i)); } }
    
    float Dot(const Vec& other) const {
        float ret = 0;
        for (int i = 0; i < Rows(); ++i) {
            ret += other.At(i, 0) * At(i, 0);
        }
        return ret;
    }
    
    float Norm() const {
        return sqrtf(Dot(*this));
    }

    void Normalize() {
        float norm = Norm();
        if (norm < EPSILON) {
            throw -1;
        }

        for (int i = 0; i < Rows(); ++i) {
            Set(i, 0, At(i, 0) / norm);
        }
    }

};



