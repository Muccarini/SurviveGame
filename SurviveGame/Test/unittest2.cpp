#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"
#include "SFML/Graphics.hpp"
#include "PlayerT.h"
#include "boost.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test 
{
	TEST_CLASS(UnitTest2)
	{
	public:
		EntityData entitydata;
		Boost boost;

		TEST_METHOD(updateBoost)
		{
			//set up player
			player.initHitBox() //player pos
				boost.update()
				assert
		}
	};
}