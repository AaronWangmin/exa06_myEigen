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

WeightObservation::WeightObservation(const WeightObservation &rhs)
    :n(rhs.getCountObservation()),
     p(rhs.getWeight())
{

}

int WeightObservation::getCountObservation() const
{
    return n;
}

MatrixXd WeightObservation::getWeight() const
{
   return p;
}
