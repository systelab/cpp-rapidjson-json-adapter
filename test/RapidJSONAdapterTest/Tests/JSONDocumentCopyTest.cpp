#include "stdafx.h"

#include "RapidJSONAdapter/JSONAdapter.h"
#include "RapidJSONAdapter/JSONDocument.h"
#include "RapidJSONAdapter/JSONValue.h"

#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"


using namespace testing;
using namespace systelab::json::test_utility;

namespace systelab { namespace json { namespace rapidjson { namespace unit_test {

	class JSONDocumentCopyTest : public testing::Test
	{
	public:
		void SetUp()
		{
			m_jsonAdapter = std::make_unique<JSONAdapter>();
		}

	protected:
		std::unique_ptr<JSONAdapter> m_jsonAdapter;
	};


	TEST_F(JSONDocumentCopyTest, testCopySimpleValueIntoNewDocument)
	{
		std::stringstream ss;
		ss << "{";
		ss << "    \"attInt\": 1234,";
		ss << "    \"attString\": \"ABC XYZ\",";
		ss << "    \"attArray\": [\"A\", \"B\", \"C\"],";
		ss << "    \"attObject\": { \"attNull\": null }";
		ss << "}";

		auto jsonDocument = m_jsonAdapter->buildDocumentFromString(ss.str());
		auto& jsonValue = jsonDocument->getRootValue().getObjectMemberValue("attInt");

		auto jsonCopyDocument = jsonValue.buildDocument();
		ASSERT_TRUE(compareJSONs("1234", jsonCopyDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentCopyTest, testCopySimpleObjectIntoNewDocument)
	{
		std::stringstream ss;
		ss << "{";
		ss << "    \"attInt\": 1234,";
		ss << "    \"attString\": \"ABC XYZ\",";
		ss << "    \"attArray\": [\"A\", \"B\", \"C\"],";
		ss << "    \"attObject\": { \"attNull\": null }";
		ss << "}";

		auto jsonDocument = m_jsonAdapter->buildDocumentFromString(ss.str());
		auto& jsonValue = jsonDocument->getRootValue().getObjectMemberValue("attObject");

		auto jsonCopyDocument = jsonValue.buildDocument();
		ASSERT_TRUE(compareJSONs("{ \"attNull\": null }", jsonCopyDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentCopyTest, testCopyComplexObjectIntoNewDocument)
	{
		std::stringstream ss;
		ss << "{";
		ss << "    \"attInt\": 1234,";
		ss << "    \"attString\": \"ABC XYZ\",";
		ss << "    \"attArray\": [\"A\", \"B\", \"C\"],";
		ss << "    \"attObject\": { \"attSubobject\": { \"attKey\": 123456 } }";
		ss << "}";

		auto jsonDocument = m_jsonAdapter->buildDocumentFromString(ss.str());
		auto& jsonValue = jsonDocument->getRootValue().getObjectMemberValue("attObject");

		auto jsonCopyDocument = jsonValue.buildDocument();
		ASSERT_TRUE(compareJSONs("{ \"attSubobject\": { \"attKey\": 123456 } }", jsonCopyDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentCopyTest, testCopyArrayIntoNewDocument)
	{
		std::stringstream ss;
		ss << "{";
		ss << "    \"attInt\": 1234,";
		ss << "    \"attArray\": [\"A\", \"B\", \"C\"],";
		ss << "    \"attObject\": { \"attNull\": null }";
		ss << "}";

		auto jsonDocument = m_jsonAdapter->buildDocumentFromString(ss.str());
		auto& jsonValue = jsonDocument->getRootValue().getObjectMemberValue("attArray");

		auto jsonCopyDocument = jsonValue.buildDocument();
		ASSERT_TRUE(compareJSONs("[\"A\", \"B\", \"C\"]", jsonCopyDocument->serialize(), *m_jsonAdapter));
	}

}}}}
