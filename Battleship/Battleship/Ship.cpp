#include "Ship.h"

Ship::Ship(int size, eShipType type, std::map<std::pair<int,int>, bool> coordinates) :
	mSize(size),
	mType(type),
	mCoordinates(coordinates) 
{
}

Ship::Ship(): mSize(0), mType()
{
}


//void Ship::setType(eShipType mType)
//{
//    this->mType = mType;
//}
//
//void Ship::setCoordinates(std::map<std::pair<int,int>, bool> mCoordinates)
//{
//    this->mCoordinates = mCoordinates;
//}
//
//void Ship::setSize(int size)
//{
//    this->size = size;
//}

eShipType Ship::getType() const
{
	return this->mType;
}

std::map<std::pair<int,int>, bool> Ship::getCoordinates() const
{
	return this->mCoordinates;
}

int Ship::getSize()
{
    return this->mSize;
}

bool Ship::handleHit(std::pair<int,int> coords, AttackResult& res)
{
	// update only until size == 0 (don't allow negative size)
	auto initialTileStatus = this->mCoordinates[coords];
	if (this->mSize > 0)
	{
		res = AttackResult::Hit;
		if(initialTileStatus) // if the hit tile was "alive"
		{
			// update ship coordinates and size and report "sink" if the ship is sunk
			this->mCoordinates[coords] = false;
			this->mSize--;
			if (this->mSize == 0)
			{
				res = AttackResult::Sink;
			}
		}
	}
	else // ship is already sunk
	{
		res = AttackResult::Miss;
	}
	return initialTileStatus;
}






