#include "weightobservation.h"

WeightObservation::WeightObservation(int count):n(count),
    p(MatrixXd::Identity(count,count))
{

}

WeightObservation::WeightObservation(int count,VectorXd weight)
    :n(count),
     p(weight.asDiagonal())
{

}

WeightObservation::WeightObservation(VectorXd elevationAngle)
{
    // added......
}

//WeightObservation::WeightObservation(const WeightObservation &rhs)
//    :n(rhs.getCountObservation()),
//     p(rhs.getWeight())
//{

//}

WeightObservation::WeightObservation(const WeightObservation &rhs)
{
    assignment(rhs);
}

WeightObservation& WeightObservation::operator = (const WeightObservation &rhs)
{
    assignment(rhs);
    return *this;
}

int WeightObservation::getCountObservation() const
{
    return n;
}

const MatrixXd& WeightObservation::getWeight() const
{
   return p;
}

void WeightObservation::assignment(const WeightObservation &rhs)
{
    this->n  = rhs.n;
    this->p  = rhs.p;
}
