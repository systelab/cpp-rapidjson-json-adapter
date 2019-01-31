#pragma once

namespace systelab { namespace test_utility {

	class EntityComparatorConfiguration
	{
	public:
		inline EntityComparatorConfiguration();
		inline EntityComparatorConfiguration(std::vector<std::string>);
		inline virtual ~EntityComparatorConfiguration();

		inline bool isMemberExcluded(const std::string&) const;

	private:
		std::vector<std::string> m_excludedMembers;
	};

}}

#include "EntityComparatorConfiguration.inl"
