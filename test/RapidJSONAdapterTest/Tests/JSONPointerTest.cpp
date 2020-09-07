#include "stdafx.h"

#include "RapidJSONAdapter/JSONAdapter.h"
#include "RapidJSONAdapter/JSONDocument.h"
#include "RapidJSONAdapter/JSONValue.h"

#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"


using namespace testing;
using namespace systelab::json::test_utility;

namespace systelab { namespace json { namespace rapidjson { namespace unit_test {

	namespace {
		struct JSONPointerTestData
		{
			std::string jsonPointer;
			std::string expectedSerializedJSON;
		};

		std::vector<JSONPointerTestData> testData =
		{
			// Valid cases
			{ "attInt", "1234" },
			{ "attDouble", "2.345" },
			{ "attTrue", "true" },
			{ "attFalse", "false" },
			{ "attString", "\"ABC XYZ\"" },
			{ "attArray", "[\"A\",\"B\",\"C\"]" },
			{ "attArray/0", "\"A\"" },
			{ "attArray/1", "\"B\"" },
			{ "attArray/2", "\"C\"" },
			{ "attObject", "{\"attNull\":null}" },
			{ "attObject/attNull", "null" },
			{ "attComplex/attObj", "{\"attSubObj\": {\"att\": 9876} }" },
			{ "attComplex/attObj/attSubObj", "{\"att\": 9876}" },
			{ "attComplex/attObj/attSubObj/att", "9876" },
			{ "attComplex/attVector", "[{\"name\": \"first\"}, {\"name\": \"second\"}]" },
			{ "attComplex/attVector/0", "{\"name\": \"first\"}" },
			{ "attComplex/attVector/0/name", "\"first\"" },
			{ "attComplex/attVector/1", "{\"name\": \"second\"}" },
			{ "attComplex/attVector/1/name", "\"second\"" },
			{ "attComplex/attNumber", "666" },
			{ "attComplex/attString", "\"XYZ\"" },
			{ "attComplex/attBool", "true" },

			// Invalid cases
			{ "attNotExisting", "" },
			{ "attInt/notExisting", "" },
			{ "attString/notExisting", "" },
			{ "attArray/-1", "" },
			{ "attArray/3", "" },
			{ "attArray/noNumber", "" },
			{ "attComplex/invalidAttribute/attSubObj", "" },
		};
	}

	class JSONPointerTest : public testing::TestWithParam<JSONPointerTestData>
	{
	public:
		void SetUp()
		{
			m_jsonAdapter = std::make_unique<JSONAdapter>();

			std::stringstream ss;
			ss << "{";
			ss << "    \"attInt\": 1234,";
			ss << "    \"attDouble\": 2.345,";
			ss << "    \"attTrue\": true,";
			ss << "    \"attFalse\": false,";
			ss << "    \"attString\": \"ABC XYZ\",";
			ss << "    \"attArray\": [\"A\", \"B\", \"C\"],";
			ss << "    \"attObject\": { \"attNull\": null },";
			ss << "    \"attComplex\": {";
			ss << "        \"attObj\": { \"attSubObj\": { \"att\": 9876 } },";
			ss << "        \"attVector\": [{\"name\": \"first\"}, {\"name\": \"second\"}],";
			ss << "        \"attNumber\": 666,";
			ss << "        \"attString\": \"XYZ\",";
			ss << "        \"attBool\": true";
			ss << "    }";
			ss << "}";

			m_jsonDocument = m_jsonAdapter->buildDocumentFromString(ss.str());
		}

		std::string serializeJSONValue(const systelab::json::IJSONValue* jsonValue)
		{
			std::string serializedJSONValue;
			if (jsonValue)
			{
				serializedJSONValue = jsonValue->buildDocument()->serialize();
			}

			return serializedJSONValue;
		}

		testing::AssertionResult assertJSON(const std::string& expectedJSON, const std::string& toTestJSON)
		{
			if (expectedJSON.empty())
			{
				if (!toTestJSON.empty())
				{
					return testing::AssertionFailure() << "Not an empty JSON (actual=" << toTestJSON << ")";
				}
				
				return testing::AssertionSuccess();
			}
			else
			{
				return compareJSONs(expectedJSON, toTestJSON, *m_jsonAdapter);
			}
		}

	protected:
		std::unique_ptr<JSONAdapter> m_jsonAdapter;
		std::unique_ptr<IJSONDocument> m_jsonDocument;
	};


	TEST_P(JSONPointerTest, testGetJSONPointerValueReturnsExpectedSerializeEmptyDocument)
	{
		auto jsonValue = m_jsonDocument->getRootValue().getJSONPointerValue(GetParam().jsonPointer);
		std::string serializedJSONValue = serializeJSONValue(jsonValue);
		ASSERT_TRUE(assertJSON(GetParam().expectedSerializedJSON, serializedJSONValue));
	}

	TEST_P(JSONPointerTest, testGetJSONPointerValueConstReturnsExpectedSerializeEmptyDocument)
	{
		const auto& jsonDocumentConst = const_cast<const systelab::json::IJSONDocument&>(*m_jsonDocument);
		const auto jsonValue = jsonDocumentConst.getRootValue().getJSONPointerValue(GetParam().jsonPointer);
		std::string serializedJSONValue = serializeJSONValue(jsonValue);
		ASSERT_TRUE(assertJSON(GetParam().expectedSerializedJSON, serializedJSONValue));
	}

	INSTANTIATE_TEST_CASE_P(Test, JSONPointerTest, testing::ValuesIn(testData));

}}}}
