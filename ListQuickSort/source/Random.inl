
namespace ns_Random
{
	template<typename ValueType>  inline ValueType Random::GetRandom(const ValueType& min, const ValueType& max)
	{
		::std::uniform_real_distribution<ValueType> range(min, max);
		return range(m_engine);
	}

	template<> inline int Random::GetRandom<int>(const int& min, const int& max)
	{
		std::uniform_int_distribution<> range(min, max);
		return range(m_engine);
	}
}