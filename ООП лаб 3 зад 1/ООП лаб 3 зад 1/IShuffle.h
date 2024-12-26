#pragma once
#include <cstddef>

class IShuffle
{
public:
    virtual ~IShuffle() = default;

    // ����������� ���������� ��� ��������
    virtual void shuffle() = 0;

    // ���������� ��������, ����������� �� �������� i � j
    virtual void shuffle(size_t i, size_t j) = 0;
};
