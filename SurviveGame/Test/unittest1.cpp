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

		TEST_METHOD(CollideWithEntity)
		{
			CollisionManager collision_manager;

			sf::Vector2f up(0, -1);    //out_mtv going up
			sf::Vector2f left(-1, 0);  //out_mtv going left
			sf::Vector2f down(0, +1);  //out_mtv going down
			sf::Vector2f right(+1, 0); //out_mtv going right
			sf::Vector2f null(0, 0);  //out_mtv null

			bool is_up = false;
			bool is_left = false;
			bool is_down = false;
			bool is_right = false;
			bool is_null = false;

			//SET UP YOUR FIRST RECT
			sf::FloatRect rectSp1;

			rectSp1.top = 0;
			rectSp1.left = 0;
			rectSp1.height = 64;
			rectSp1.width = 64;

			//SET UP YOUR SECOND RECT
			sf::FloatRect rectSp2;

			rectSp2.top = 32;
			rectSp2.left = 0;
			rectSp2.height = 64;
			rectSp2.width = 64;

			//TESTING UP
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (collision_manager.getOutMtv().x == 0 && collision_manager.getOutMtv().y < 0)
				is_up = true;
			collision_manager.resetOutMtv();

			//TESTING LEFT
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (collision_manager.getOutMtv().x < 0 && collision_manager.getOutMtv().y == 0)
				is_left = true;
			collision_manager.resetOutMtv();

			//TESTING DOWN
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (collision_manager.getOutMtv().x == 0 && collision_manager.getOutMtv().y > 0)
				is_down = true;
			collision_manager.resetOutMtv();

			//TESTING RIGHT
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (collision_manager.getOutMtv().x > 0 && collision_manager.getOutMtv().y == 0)
				is_right = true;
			collision_manager.resetOutMtv();

			//TESTING NULL
			collision_manager.CollideWithEntity(rectSp1, rectSp1);
			if (collision_manager.getOutMtv().x == 0 && collision_manager.getOutMtv().y == 0)
				is_null = true;
			collision_manager.resetOutMtv();

			Assert::IsTrue(is_up);
			/*Assert::IsFalse(is_left);
			Assert::IsFalse(is_down);
			Assert::IsFalse(is_right);
			Assert::IsFalse(is_null);*/
		}

	};
}