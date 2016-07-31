#ifndef MINIASCAPE_RANDOM_STATE_GENERATOR
#define MINIASCAPE_RANDOM_STATE_GENERATOR
#include <random>

namespace miniascape
{

template<typename T_state>
class RandomStateGenerator{};

template<>
class RandomStateGenerator<bool>
{
    explicit RandomStateGenerator(const unsigned int s) : mt_(s), bn_(0.5){}
    ~RandomStateGenerator() = default;

    bool operator()(){return bn_(mt_);}

    std::mt19937 mt_;
    std::bernoulli_distribution bn_;
};

}

#endif /* MINIASCAPE_RANDOM_STATE_GENERATOR */
