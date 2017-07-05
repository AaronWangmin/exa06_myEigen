#ifndef WEIGHTOBSERVATION_H
#define WEIGHTOBSERVATION_H

#include <Eigen/Dense>
using namespace Eigen;

class WeightObservation
{
public:
    WeightObservation(int countObs);                    // the same weight
    WeightObservation(int countObs, VectorXd weight);   // the different weight

    WeightObservation(VectorXd elevationAngle);         // base on elevation angle,added......

    WeightObservation(const WeightObservation &rhs);
    WeightObservation& operator= (const WeightObservation &rhs);

    int getCountObservation() const;        // ? const int get...
    const MatrixXd& getWeight() const;             // ? const MatrixXd get...


private:
    int n;      // count of observation
    MatrixXd p; // the weights of observation

    void assignment(const WeightObservation &rhs);
};

#endif // WEIGHTOBSERVATION_H
