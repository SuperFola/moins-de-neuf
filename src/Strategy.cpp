#include <Strategy.hpp>

Strategy::Strategy(const std::string& name) :
    m_name(name)
{}

const std::string& Strategy::getName() const noexcept
{
    return m_name;
}

std::ostream& operator<<(std::ostream& os, const Strategy& strat)
{
    os << strat.m_name;
    return os;
}