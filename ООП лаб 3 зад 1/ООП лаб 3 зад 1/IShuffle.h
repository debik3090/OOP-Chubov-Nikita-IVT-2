#pragma once
#include <cstddef>

class IShuffle
{
public:
    virtual ~IShuffle() = default;

    // ѕроизвольно перемешать все операнды
    virtual void shuffle() = 0;

    // ѕеремешать операнды, наход€щиес€ на позици€х i и j
    virtual void shuffle(size_t i, size_t j) = 0;
};
