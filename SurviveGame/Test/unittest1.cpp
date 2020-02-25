#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"
#include "SFML/Graphics.hpp"
#include "CollisionManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(UnitTest1)
	{
	public:

		bool isequal(float a, float b)
		{
			if (fabs(a - b) < 0.01)
				return true;
			else
				return false;
		};

		TEST_METHOD(TestMethod1)
		{
			sf::Vector2f up1(0, -1);
			CollisionManager collision_manager;

			sf::Vector2f up(0, -1);    //out_mtv going up
			sf::Vector2f left(-1, 0);  //out_mtv going left
			sf::Vector2f down(0, +1);  //out_mtv going down
			sf::Vector2f right(+1, 0); //out_mtv going right
			sf::Vector2f null(0, 0);  //out_mtv null

			bool is_up;
			bool is_left;
			bool is_down;
			bool is_right;
			bool is_null;

			//SET UP YOUR FIRST RECT
			sf::FloatRect rectSp1;

			rectSp1.top = 0;
			rectSp1.left = 0;
			rectSp1.height = 64;
			rectSp1.width = 64;

			//SET UP YOUR SECOND RECT
			sf::FloatRect rectSp2;

			rectSp1.top = 32;
			rectSp1.left = 0;
			rectSp1.height = 64;
			rectSp1.width = 64;

			//TESTING UP
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (isequal(collision_manager.getOutMtv().x, up.x) && isequal(collision_manager.getOutMtv().y, up.y))
				bool is_up = true;
			collision_manager.resetOutMtv();

			//TESTING LEFT
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (collision_manager.getOutMtv() == left)
				bool is_left = true;
			collision_manager.resetOutMtv();

			//TESTING DOWN
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (isequal(collision_manager.getOutMtv().x, down.x) && isequal(collision_manager.getOutMtv().y, down.y))
				bool is_down = true;
			collision_manager.resetOutMtv();

			//TESTING RIGHT
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (isequal(collision_manager.getOutMtv().x, right.x) && isequal(collision_manager.getOutMtv().y, right.y))
				bool is_right = true;
			collision_manager.resetOutMtv();

			//TESTING NULL
			collision_manager.CollideWithEntity(rectSp1, rectSp1);
			if (isequal(collision_manager.getOutMtv().x, null.x) && isequal(collision_manager.getOutMtv().y, null.y))
				bool is_null = true;
			collision_manager.resetOutMtv();

			Assert::AreEqual(true, is_up);
			Assert::AreEqual(false, is_left);
			Assert::AreEqual(false, is_down);
			Assert::AreEqual(false, is_right);
			Assert::AreEqual(false, is_null);

		}

	};
}