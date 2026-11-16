#include "Predictor.h"
#include <cmath>

Predictor::Predictor(double target) : target(target) {}

double Predictor::getTarget() const {
    return target;
}

double Predictor::currentPercentage(int attended, int held) const {
    if (held == 0) {
        return 0.0;
    }
    return 100.0 * attended / held;
}

bool Predictor::meetsTarget(int attended, int held) const {
    return 100.0 * attended >= target * held;
}

int Predictor::classesNeeded(int attended, int held) const {
    if (meetsTarget(attended, held)) {
        return 0;
    }
    double x = (target * held - 100.0 * attended) / (100.0 - target);
    return static_cast<int>(std::ceil(x - 1e-9));
}

int Predictor::classesCanSkip(int attended, int held) const {
    if (!meetsTarget(attended, held)) {
        return 0;
    }
    double y = (100.0 * attended - target * held) / target;
    return static_cast<int>(std::floor(y + 1e-9));
}

double Predictor::predictFinal(int attended, int held, int remaining, int willAttend) const {
    int total = held + remaining;
    if (total == 0) {
        return 0.0;
    }
    return 100.0 * (attended + willAttend) / total;
}

int Predictor::minimumToAttend(int attended, int held, int remaining) const {
    double x = target * (held + remaining) / 100.0 - attended;
    int needed = static_cast<int>(std::ceil(x - 1e-9));
    if (needed < 0) {
        needed = 0;
    }
    if (needed > remaining) {
        return -1;
    }
    return needed;
}
