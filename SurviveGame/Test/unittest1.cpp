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

		CollisionManager collision_manager;

		sf::FloatRect rectSp1;
		sf::FloatRect rectSp2;

		bool is_up = false;
		bool is_left = false;
		bool is_down = false;
		bool is_right = false;
		bool is_null = false;

		TEST_METHOD(CollideUpWithEntity)
		{
			sf::Vector2f up(0, -1); //out_mtv going up

			//SET UP YOUR FIRST RECT

			rectSp1.top = 0;
			rectSp1.left = 0;
			rectSp1.height = 64;
			rectSp1.width = 64;

			//SET UP YOUR SECOND RECT

			rectSp2.top = 32;
			rectSp2.left = 0;
			rectSp2.height = 64;
			rectSp2.width = 64;

			//TESTING UP
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (collision_manager.getOutMtv().x == 0 && collision_manager.getOutMtv().y < 0)
				is_up = true;
			collision_manager.resetOutMtv();

			Assert::IsTrue(is_up);
		}

		TEST_METHOD(CollideDownWithEntity)
		{
			sf::Vector2f down(0, +1); //out_mtv going down

			//SET UP YOUR FIRST RECT

			rectSp1.top = 32;
			rectSp1.left = 0;
			rectSp1.height = 64;
			rectSp1.width = 64;

			//SET UP YOUR SECOND RECT

			rectSp2.top = 0;
			rectSp2.left = 0;
			rectSp2.height = 64;
			rectSp2.width = 64;

			//TESTING DOWN
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (collision_manager.getOutMtv().x == 0 && collision_manager.getOutMtv().y > 0)
				is_down = true;
			collision_manager.resetOutMtv();

			Assert::IsTrue(is_down);
		}

		TEST_METHOD(CollideLeftWithEntity)
		{
			sf::Vector2f left(-1, 0); //out_mtv going left

			//SET UP YOUR FIRST RECT

			rectSp1.top = 0;
			rectSp1.left = 0;
			rectSp1.height = 64;
			rectSp1.width = 64;

			//SET UP YOUR SECOND RECT

			rectSp2.top = 0;
			rectSp2.left = 32;
			rectSp2.height = 64;
			rectSp2.width = 64;

			//TESTING UP
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (collision_manager.getOutMtv().x < 0 && collision_manager.getOutMtv().y == 0)
				is_left = true;
			collision_manager.resetOutMtv();

			Assert::IsTrue(is_left);
		}

		TEST_METHOD(CollideRightWithEntity)
		{
			sf::Vector2f right(+1, 0); //out_mtv going up

			//SET UP YOUR FIRST RECT

			rectSp1.top = 0;
			rectSp1.left = 32;
			rectSp1.height = 64;
			rectSp1.width = 64;

			//SET UP YOUR SECOND RECT

			rectSp2.top = 0;
			rectSp2.left = 0;
			rectSp2.height = 64;
			rectSp2.width = 64;

			//TESTING UP
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (collision_manager.getOutMtv().x > 0 && collision_manager.getOutMtv().y == 0)
				is_right = true;
			collision_manager.resetOutMtv();

			Assert::IsTrue(is_right);
		}

		TEST_METHOD(CollideNULLWithEntity)
		{
			sf::Vector2f null(0, 0); //out_mtv going up

			//SET UP YOUR FIRST RECT

			rectSp1.top = 0;
			rectSp1.left = 0;
			rectSp1.height = 64;
			rectSp1.width = 64;

			//SET UP YOUR SECOND RECT

			rectSp2.top = 64;
			rectSp2.left = 64;
			rectSp2.height = 64;
			rectSp2.width = 64;

			//TESTING UP
			collision_manager.CollideWithEntity(rectSp1, rectSp2);
			if (collision_manager.getOutMtv().x == 0 && collision_manager.getOutMtv().y == 0)
				is_null = true;
			collision_manager.resetOutMtv();

			Assert::IsTrue(is_null);
		}

	};
}