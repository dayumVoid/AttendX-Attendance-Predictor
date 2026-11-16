#ifndef PREDICTOR_H
#define PREDICTOR_H

class Predictor {
private:
    double target;

public:
    explicit Predictor(double target = 75.0);

    double getTarget() const;
    double currentPercentage(int attended, int held) const;
    bool meetsTarget(int attended, int held) const;
    int classesNeeded(int attended, int held) const;
    int classesCanSkip(int attended, int held) const;
    double predictFinal(int attended, int held, int remaining, int willAttend) const;
    int minimumToAttend(int attended, int held, int remaining) const;
};

#endif
