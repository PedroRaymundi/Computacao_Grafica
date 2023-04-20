/*
* Defines a transform object that is basically a transformation matrix to the position
* */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>

struct Vector3
{
  float x, y, z;
  
  Vector3 () { x = y = z = 0.0f; }
  
  Vector3 (float _v)
  {
    x = y = z = _v;
  }
  
  Vector3 (float _x, float _y, float _z)
  {
    x = _x;
    y = _y;
    z = _z;
  }
  
  Vector3 normalize()
  {
    Vector3 ret;
    float mag = sqrt(x*x + y*y + z*z); // calculate the magnitude of the vector

    if (mag != 0) // avoid division by zero
    {
      ret.x = x / mag; // divide each component by the magnitude
      ret.y = y / mag;
      ret.z = z / mag;
    }

    return ret;
  }
};

struct Transform
{
  float vals[16];

  void identity()
  {
      memset(vals, 0x0, 16 * sizeof(float));

      // Setting identity matrix
      vals[0] = 1.0f;
      vals[5] = 1.0f;
      vals[10] = 1.0f;
      vals[15] = 1.0f;
  }

  Transform()
  {
    identity();
  }

  void scale(Vector3 s)
  {
    Transform temp;
    temp.vals[0] = s.x;
    temp.vals[5] = s.y;
    temp.vals[10] = s.z;
    
    // Multiply matrices
    Transform temp2 = (*this)*temp;
    
    memcpy(this->vals, temp2.vals, 16 * sizeof(float));
  }
  
  void set_scale(Vector3 s)
  {
    vals[0] = s.x;
    vals[5] = s.y;
    vals[10] = s.z;
  }
  
  void translate(Vector3 t)
  {
    Transform temp;
    temp.vals[3] = t.x;
    temp.vals[7] = t.y;
    temp.vals[11] = t.z;

    // Multiply matrices
    Transform temp2 = (*this)*temp;
    memcpy(this->vals, temp2.vals, 16 * sizeof(float));
  }
  
  void set_translation(Vector3 t)
  {
    vals[3] = t.x;
    vals[7] = t.y;
    vals[11] = t.z;
  }
  
  void set_rotation(float theta, Vector3 v)
  {
    vals[0] = v.x * v.x * (1 - cos(theta)) + cos(theta);
    vals[1] = v.y * v.x * (1 - cos(theta)) - v.z * sin(theta);
    vals[2] = v.z * v.x * (1 - cos(theta)) + v.y * sin(theta);

    vals[4] = v.x * v.y * (1 - cos(theta)) + v.z * sin(theta);
    vals[5] = v.y * v.y * (1 - cos(theta)) + cos(theta);
    vals[6] = v.z * v.y * (1 - cos(theta)) - v.x * sin(theta);

    vals[8] = v.z * v.x * (1 - cos(theta)) - v.y * sin(theta);
    vals[9] = v.z * v.y * (1 - cos(theta)) + v.x * sin(theta);
    vals[10] = v.z * v.z * (1 - cos(theta)) + cos(theta);
  }
  
  /* Rotates the matrix `theta` radians around the vector specified */
  void rotate(float theta, Vector3 v)
  {
    Transform temp;

    temp.set_rotation(theta, v);

    // Multiply matrices
    Transform temp2 = (*this) * temp;
    memcpy(this->vals, temp2.vals, 16 * sizeof(float));
  }

  // Applies the matrix to the vector, adding 1 as the homogeneous component
  Vector3 operator*(const Vector3& v) {
    float vec3[4] = {v.x, v.y, v.z, 1.0f};
    float new_vals[4];
    
    for (int i = 0; i < 4; i++) {
      new_vals[i] = 0.0f;
      for (int j = 0; j < 4; j++) {
        new_vals[i] += vals[j * 4 + i] * vec3[j];
      }
    }

    Vector3 result(new_vals[0] / new_vals[3], new_vals[1] / new_vals[3], new_vals[2] / new_vals[3]);

    return result;
  }
  
  // Multiply matrices
  Transform operator* (Transform t)
  {
    Transform ret;
    
    // Line 0
    ret.vals[0] = vals[0] * t.vals[0] + vals[1] * t.vals[4] + vals[2] * t.vals[8] + vals[3] * t.vals[12];
    ret.vals[1] = vals[0] * t.vals[1] + vals[1] * t.vals[5] + vals[2] * t.vals[9] + vals[3] * t.vals[13];
    ret.vals[2] = vals[0] * t.vals[2] + vals[1] * t.vals[6] + vals[2] * t.vals[10] + vals[3] * t.vals[14];
    ret.vals[3] = vals[0] * t.vals[3] + vals[1] * t.vals[7] + vals[2] * t.vals[11] + vals[3] * t.vals[15];
    
    // Line 1
    ret.vals[4] = vals[4] * t.vals[0] + vals[5] * t.vals[4] + vals[6] * t.vals[8] + vals[7] * t.vals[12];
    ret.vals[5] = vals[4] * t.vals[1] + vals[5] * t.vals[5] + vals[6] * t.vals[9] + vals[7] * t.vals[13];
    ret.vals[6] = vals[4] * t.vals[2] + vals[5] * t.vals[6] + vals[6] * t.vals[10] + vals[7] * t.vals[14];
    ret.vals[7] = vals[4] * t.vals[3] + vals[5] * t.vals[7] + vals[6] * t.vals[11] + vals[7] * t.vals[15];
    
    // Line 2
    ret.vals[8] = vals[8] * t.vals[0] + vals[9] * t.vals[4] + vals[10] * t.vals[8] + vals[11] * t.vals[12];
    ret.vals[9] = vals[8] * t.vals[1] + vals[9] * t.vals[5] + vals[10] * t.vals[9] + vals[11] * t.vals[13];
    ret.vals[10] = vals[8] * t.vals[2] + vals[9] * t.vals[6] + vals[10] * t.vals[10] + vals[11] * t.vals[14];
    ret.vals[11] = vals[8] * t.vals[3] + vals[9] * t.vals[7] + vals[10] * t.vals[11] + vals[11] * t.vals[15];
    
    // Line 3
    ret.vals[12] = vals[12] * t.vals[0] + vals[13] * t.vals[4] + vals[14] * t.vals[8] + vals[15] * t.vals[12];
    ret.vals[13] = vals[12] * t.vals[1] + vals[13] * t.vals[5] + vals[14] * t.vals[9] + vals[15] * t.vals[13];
    ret.vals[14] = vals[12] * t.vals[2] + vals[13] * t.vals[6] + vals[14] * t.vals[10] + vals[15] * t.vals[14];
    ret.vals[15] = vals[12] * t.vals[3] + vals[13] * t.vals[7] + vals[14] * t.vals[11] + vals[15] * t.vals[15];
    
    return ret;
  }
};

#endif // TRANSFORM_H
