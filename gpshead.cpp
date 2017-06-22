#include "gpshead.h"

eph_t::eph_t()
    :week(0),sat(0),toc(0),
     af0(0),af1(0),af2(0),
     iode(0),Crs(0),Deln(0),M0(0),
     Cuc(0),e(0),Cus(0),A(0),
     toe(0),
     Cic(0),OMG0(0),Cis(0),
     i0(0),Crc(0),omg(0),OMGd(0),
     iDOT(0),code(0),toes(0),flag(0),
     sva(0),svh(0),tgd(0),iodc(0),
     ttr(0),
     fit(0),
     reserved(0),reserved01(0)
{

}

eph_t::eph_t(const eph_t &rhs)
{
    this->A             = rhs.A;
    this->af0           = rhs.af0;
    this->af1           = rhs.af1;
    this->af2           = rhs.af2;
    this->Cic           = rhs.Cic;
    this->Cis           = rhs.Cis;
    this->code          = rhs.code;
    this->Crc           = rhs.Crc;
    this->Crs           = rhs.Crs;
    this->Cuc           = rhs.Cuc;
    this->Cus           = rhs.Cus;
    this->Deln          = rhs.Deln;
    this->e             = rhs.e;
    this->fit           = rhs.fit;
    this->flag          = rhs.flag;
    this->i0            = rhs.i0;
    this->iDOT          = rhs.iDOT;
    this->iodc          = rhs.iodc;
    this->iode          = rhs.iode;
    this->M0            = rhs.M0;
    this->omg           = rhs.omg;
    this->OMG0          = rhs.OMG0;
    this->OMGd          = rhs.OMGd;
    this->reserved      = rhs.reserved;
    this->reserved01    = rhs.reserved01;
    this->sat           = rhs.sat;
    this->sva           = rhs.sva;
    this->svh           = rhs.svh;
    this->tgd           = rhs.tgd;
    this->toc           = rhs.toc;
    this->toe           = rhs.toe;
    this->toes          = rhs.toes;
    this->ttr           = rhs.ttr;
    this->week          = rhs.week;
}

