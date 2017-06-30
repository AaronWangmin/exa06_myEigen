#include "obsblock.h"

ObsBlock::ObsBlock()
    :ephoch(0),
     flagEphoc(0),
     countSat(0),
     clockOffsetRev(0)
{

}

ObsBlock::ObsBlock(const ObsBlock &rhs)
{
    assigment(rhs);
}

ObsBlock& ObsBlock::operator =(const ObsBlock &rhs)
{
    assigment(rhs);
    return *this;
}

void ObsBlock::assigment(const ObsBlock &rhs)
{
    this->ephoch            = rhs.ephoch;
    this->flagEphoc         = rhs.flagEphoc;
    this->countSat          = rhs.countSat;
    this->prnList           = rhs.prnList;
    this->clockOffsetRev    = rhs.clockOffsetRev;
    this->ephochObs         = rhs.ephochObs;
}
