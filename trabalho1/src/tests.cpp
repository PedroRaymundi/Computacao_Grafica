#include <cmath>
#include <iostream>
#include "transform.hpp"
/*
#define M_PI 3.1415926535

void expect_float_eq(float a, float b, float tolerance = 1e-6)
{
  if (std::abs(a - b) > tolerance)
  {
    std::cout << "Expected " << b << ", but got " << a << std::endl;
  }
}

void matrix_tests()
{
    std::cout << "Transform constructor creates identity matrix\n";
    Transform transform_0;
    float expected_vals_0[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f};
    for(int i = 0; i < 16; i++){
        expect_float_eq(transform_0.vals[i], expected_vals_0[i]);
    }
    
    std::cout << "Transform scale method works correctly\n";
    Transform transform_1;
    Vector3 s(2.0f, 3.0f, 4.0f);
    transform_1.scale(s);
    
    float expected_vals_1[16] = {2.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 3.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 4.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f};
    for(int i = 0; i < 16; i++){
        expect_float_eq(transform_1.vals[i], expected_vals_1[i]);
    }
    
    std::cout << "Transform translate method works correctly\n";
    Transform transform_2;
    Vector3 t(2.0f, 3.0f, 4.0f);
    transform_2.translate(t);
    
    float expected_vals_2[16] = {1.0f, 0.0f, 0.0f, 2.0f,
                             0.0f, 1.0f, 0.0f, 3.0f,
                             0.0f, 0.0f, 1.0f, 4.0f,
                             0.0f, 0.0f, 0.0f, 1.0f};
    for(int i = 0; i < 16; i++){
        expect_float_eq(transform_2.vals[i], expected_vals_2[i]);
    }
    
//    std::cout << "Transform rotate method works correctly\n";
//    Transform transform_3;
//    Vector3 v(1.0f, 1.0f, 1.0f);
//    transform_3.rotate(M_PI / 2.0f, v);
//    
//    float expected_vals_3[16] = {0.333333343f, 0.666666687f, -0.666666687f, 0.0f,
//                             -0.666666687f, 0.333333343f, 0.666666687f, 0.0f,
//                             0.666666687f, -0.666666687f, 0.333333343f, 0.0f,
//                             0.0f, 0.0f, 0.0f, 1.0f};
//    for(int i = 0; i < 16; i++){
//        expect_float_eq(transform_3.vals[i], expected_vals_3[i]);
//    }
    
    std::cout << "Transform rotate method works correctly\n";
    Transform transform_3;
    Vector3 v(0.0f, 1.0f, 0.0f);
    transform_3.rotate(M_PI / 2.0f, v.normalize());

    float expected_vals_3[16] = { 0.0f, 0.0f, 1.0f, 0.0f,
                                  0.0f, 1.0f, 0.0f, 0.0f,
                                 -1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 1.0f};
    for(int i = 0; i < 16; i++){
      expect_float_eq(transform_3.vals[i], expected_vals_3[i]);
    }
}

int main(int argc, char **argv)
{
  std::cout << "Running vector tests";
      
  // Test a non-zero vector
  Vector3 v1(1.0f, 2.0f, 3.0f);
  Vector3 result1 = v1.normalize();
  expect_float_eq(result1.x, 0.267261f);
  expect_float_eq(result1.y, 0.534522f);
  expect_float_eq(result1.z, 0.801784f);

  // Test a zero vector
  Vector3 v2(0.0f, 0.0f, 0.0f);
  Vector3 result2 = v2.normalize();
  expect_float_eq(result2.x, 0.0f);
  expect_float_eq(result2.y, 0.0f);
  expect_float_eq(result2.z, 0.0f);

  // Test a negative vector
  Vector3 v3(-1.0f, -2.0f, -3.0f);
  Vector3 result3 = v3.normalize();
  expect_float_eq(result3.x, -0.267261f);
  expect_float_eq(result3.y, -0.534522f);
  expect_float_eq(result3.z, -0.801784f);

  // Test a unit vector
  Vector3 v4(1.0f, 0.0f, 0.0f);
  Vector3 result4 = v4.normalize();
  expect_float_eq(result4.x, 1.0f);
  expect_float_eq(result4.y, 0.0f);
  expect_float_eq(result4.z, 0.0f);
  
  std::cout << "Running matrix tests";
  matrix_tests();
}
*/