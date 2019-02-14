#include "RapidJSONAdapter/JSONAdapter.h"

#include "RapidJSONAdapter/JSONDocument.h"
#include "RapidJSONAdapter/JSONValue.h"

#include <gtest/gtest.h>


using namespace testing;

namespace systelab { namespace json { namespace rapidjson { namespace unit_test {

	class JSONDocumentParseTest : public testing::Test
	{
	public:
		void SetUp()
		{
			m_jsonAdapter = std::make_unique<JSONAdapter>();
		}

	protected:
		std::unique_ptr<JSONAdapter> m_jsonAdapter;
	};


	TEST_F(JSONDocumentParseTest, testSerializeEmptyDocumentReturnsNull)
	{
		auto emptyDocument = m_jsonAdapter->buildEmptyDocument();
		ASSERT_EQ("null", emptyDocument->serialize());
	}

}}}}
