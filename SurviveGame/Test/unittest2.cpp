#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"
#include "SFML/Graphics.hpp"
#include "PlayerT.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test 
{
	TEST_CLASS(UnitTest2)
	{
	public:

		PlayerT player;

		TEST_METHOD(boostMSPlayer)
		{
			//set up player
			player.setMoveSpeed(150.f);
			player.setMoveSpeedDef(150.f);

			//set boost type
			BoostType::Type b_type = BoostType::MS;

			//method test
			player.boost(b_type);
			bool boosted = false;
			if (player.getMovSpeed() > player.getMovSpeedDef())
				boosted = true;
			else boosted = false;
			Assert::IsTrue(boosted);
		}

		TEST_METHOD(boostHPMaxPlayer)
		{
			//set up player
			player.setHp(100);
			player.setHpMax(100);

			//set boost type
			BoostType::Type b_type = BoostType::HP;

			//method test
			player.boost(b_type);
			bool boosted = false;
			if (player.getHp() == player.getHpMax())
				boosted = false;
			else boosted = true;
			Assert::IsFalse(boosted);
		}

		TEST_METHOD(boostHPPlayer)
		{
			//set up player
			player.setHp(60);
			player.setHpMax(100);

			//set boost type
			BoostType::Type b_type = BoostType::HP;

			//method test
			player.boost(b_type);
			bool boosted = false;
			if (player.getHp() == 90)
				boosted = true;
			else boosted = false;
			Assert::IsTrue(boosted);
		}
	};
}