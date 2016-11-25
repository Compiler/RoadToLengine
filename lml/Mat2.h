#pragma once
#include "Mat3x3.h"
#include "Mat3x3.h"
#include "Mat3x3.h"


namespace lml {

	class Mat2{
	public:
		Mat2(float topLeft, float topRight, float bottomLeft, float bottomRight);

		
		void transpose();
		void dot(Mat2 matrix);
		void dot(Mat3x3 matrix);
		void add(Mat2 matrix);
		Mat2 getDot(Mat2 matrix);
		float elementAt(int x, int y);


		~Mat2();


	private:

		float mat[2][2];
		
	};

}
