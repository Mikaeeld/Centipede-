#pragma once

#include "CentipedeSegment.h"
#include "EntityManager.h"

class Centipede
{
public:
	Centipede() {}
	Centipede(EntityManager &entityManager, const Speed_ptr speed)
	{

		centipedeHead_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody1_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody2_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody3_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody4_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody5_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody6_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody7_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody8_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody9_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody10_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody11_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody12_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody13_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody14_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));
		centipedeBody15_ = shared_ptr<CentipedeSegment>(new CentipedeSegment(nullptr, nullptr, speed));

		centipedeHead_->updateChain(nullptr, centipedeBody1_);
		centipedeBody1_->updateChain(centipedeHead_, centipedeBody2_);
		centipedeBody2_->updateChain(centipedeBody1_, centipedeBody3_);
		centipedeBody3_->updateChain(centipedeBody2_, centipedeBody4_);
		centipedeBody4_->updateChain(centipedeBody3_, centipedeBody5_);
		centipedeBody5_->updateChain(centipedeBody4_, centipedeBody6_);
		centipedeBody6_->updateChain(centipedeBody5_, centipedeBody7_);
		centipedeBody7_->updateChain(centipedeBody6_, centipedeBody8_);
		centipedeBody8_->updateChain(centipedeBody7_, centipedeBody9_);
		centipedeBody9_->updateChain(centipedeBody8_, centipedeBody10_);
		centipedeBody10_->updateChain(centipedeBody9_, centipedeBody11_);
		centipedeBody11_->updateChain(centipedeBody10_, centipedeBody12_);
		centipedeBody12_->updateChain(centipedeBody11_, centipedeBody13_);
		centipedeBody13_->updateChain(centipedeBody12_, centipedeBody14_);
		centipedeBody14_->updateChain(centipedeBody13_, centipedeBody15_);
		centipedeBody15_->updateChain(centipedeBody14_, nullptr);

		centipedeHead_->setPosition(160 + 4, 16 + 4);

		entityManager.addEntity(centipedeHead_);
		entityManager.addEntity(centipedeBody1_);
		entityManager.addEntity(centipedeBody2_);
		entityManager.addEntity(centipedeBody3_);
		entityManager.addEntity(centipedeBody4_);
		entityManager.addEntity(centipedeBody5_);
		entityManager.addEntity(centipedeBody6_);
		entityManager.addEntity(centipedeBody7_);
		entityManager.addEntity(centipedeBody8_);
		entityManager.addEntity(centipedeBody9_);
		entityManager.addEntity(centipedeBody10_);
		entityManager.addEntity(centipedeBody11_);
		entityManager.addEntity(centipedeBody12_);
		entityManager.addEntity(centipedeBody13_);
		entityManager.addEntity(centipedeBody14_);
		entityManager.addEntity(centipedeBody15_);
	}

private:
	shared_ptr<CentipedeSegment> centipedeBody1_;
	shared_ptr<CentipedeSegment> centipedeBody2_;
	shared_ptr<CentipedeSegment> centipedeBody3_;
	shared_ptr<CentipedeSegment> centipedeBody4_;
	shared_ptr<CentipedeSegment> centipedeBody5_;
	shared_ptr<CentipedeSegment> centipedeBody6_;
	shared_ptr<CentipedeSegment> centipedeBody7_;
	shared_ptr<CentipedeSegment> centipedeBody8_;
	shared_ptr<CentipedeSegment> centipedeBody9_;
	shared_ptr<CentipedeSegment> centipedeBody10_;
	shared_ptr<CentipedeSegment> centipedeBody11_;
	shared_ptr<CentipedeSegment> centipedeBody12_;
	shared_ptr<CentipedeSegment> centipedeBody13_;
	shared_ptr<CentipedeSegment> centipedeBody14_;
	shared_ptr<CentipedeSegment> centipedeBody15_;
	shared_ptr<CentipedeSegment> centipedeHead_;
};