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

		PlayerT player;

		TEST_METHOD(boostMSPlayer)
		{
			BoostType::Type b_type = BoostType::MS;
			player.boost(b_type);
			bool boosted = false;
			if (player.getMovSpeed() > player.getMovSpeedDef())
				boosted = true;
			else boosted = false;
			Assert::IsTrue(boosted);
		}

		TEST_METHOD(boostHPMaxPlayer)
		{
			BoostType::Type b_type = BoostType::HP;
			player.boost(b_type);
			bool boosted = false;
			if (player.getHp() == player.getHpMax())
				boosted = false;
			else boosted = true;
			Assert::IsFalse(boosted);
		}

		TEST_METHOD(boostHPPlayer)
		{
			int hp = 60;
			player.setHp(hp);
			BoostType::Type b_type = BoostType::HP;
			player.boost(b_type);
			bool boosted = false;
			if (player.getHp() == 90)
				boosted = true;
			else boosted = false;
			Assert::IsTrue(boosted);
		}
	};
}