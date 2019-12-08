#include "stdafx.h"

#include "RapidJSONAdapter/JSONAdapter.h"
#include "RapidJSONAdapter/JSONDocument.h"
#include "RapidJSONAdapter/JSONValue.h"

#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"


using namespace testing;
using namespace systelab::json::test_utility;

namespace systelab { namespace json { namespace rapidjson { namespace unit_test {

	class JSONDocumentSerializeTest : public testing::Test
	{
	public:
		void SetUp()
		{
			m_jsonAdapter = std::make_unique<JSONAdapter>();
		}

	protected:
		std::unique_ptr<JSONAdapter> m_jsonAdapter;
	};


	TEST_F(JSONDocumentSerializeTest, testSerializeEmptyDocument)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		ASSERT_TRUE(compareJSONs("null", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeEmptyObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);

		ASSERT_TRUE(compareJSONs("{}", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeSingleIntegerAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);
		jsonRootValue.addMember("attInt", 1234);

		ASSERT_TRUE(compareJSONs("{ \"attInt\": 1234 }", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeSingleLongAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);
		jsonRootValue.addMember("attLong", (long) 123456789);

		ASSERT_TRUE(compareJSONs("{ \"attLong\": 123456789 }", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeSingleLongLongAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);
		jsonRootValue.addMember("attLongLong", (long long) 1234567890123456789);

		ASSERT_TRUE(compareJSONs("{ \"attLongLong\": 1234567890123456789 }", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeSingleDoubleAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);
		jsonRootValue.addMember("attDouble", 1.2345);

		ASSERT_TRUE(compareJSONs("{ \"attDouble\": 1.2345 }", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeSingleTrueBooleanAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);
		jsonRootValue.addMember("attBoolean", true);

		ASSERT_TRUE(compareJSONs("{ \"attBoolean\": true }", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeSingleFalseBooleanAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);
		jsonRootValue.addMember("attBoolean", false);

		ASSERT_TRUE(compareJSONs("{ \"attBoolean\": false }", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeSingleStringAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);
		jsonRootValue.addMember("attString", "ABCDEF");

		ASSERT_TRUE(compareJSONs("{ \"attString\": \"ABCDEF\" }", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeSingleNullAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);
		jsonRootValue.addMember("attNull", jsonRootValue.buildValue(systelab::json::NULL_TYPE));

		ASSERT_TRUE(compareJSONs("{ \"attNull\": null }", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeSingleNulledAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);
		jsonRootValue.addMember("attNulled", "oldValue");
		jsonRootValue.getObjectMemberValue("attNulled").setNull();

		ASSERT_TRUE(compareJSONs("{ \"attNulled\": null }", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeSingleEmptyObjectAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);
		jsonRootValue.addMember("attObject", jsonRootValue.buildValue(systelab::json::OBJECT_TYPE));

		ASSERT_TRUE(compareJSONs("{ \"attObject\": {} }", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeSingleNonEmptyObjectAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);

		auto jsonObjectValue = jsonRootValue.buildValue(systelab::json::OBJECT_TYPE);
		jsonObjectValue->addMember("attSubObject", true);
		jsonRootValue.addMember("attObject", std::move(jsonObjectValue));

		ASSERT_TRUE(compareJSONs("{ \"attObject\": { \"attSubObject\": true } }", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeSingleArrayAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);

		auto jsonArrayValue = jsonRootValue.buildValue(systelab::json::ARRAY_TYPE);

		std::vector<int> arrayValues = { 9, 8, 7 };
		for (int arrayValue : arrayValues)
		{
			auto jsonArrayItem = jsonArrayValue->buildValue(systelab::json::NUMBER_TYPE);
			jsonArrayItem->setInteger(arrayValue);
			jsonArrayValue->addArrayValue(std::move(jsonArrayItem));
		}

		jsonRootValue.addMember("attArray", std::move(jsonArrayValue));

		ASSERT_TRUE(compareJSONs("{ \"attArray\": [9, 8, 7] }", jsonDocument->serialize(), *m_jsonAdapter));
	}

	TEST_F(JSONDocumentSerializeTest, testSerializeComplexJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);
		jsonRootValue.addMember("attInt", 1234);
		jsonRootValue.addMember("attDouble", 2.345);
		jsonRootValue.addMember("attTrue", true);
		jsonRootValue.addMember("attFalse", false);
		jsonRootValue.addMember("attString", "ABC XYZ");

		auto jsonArrayValue = jsonRootValue.buildValue(systelab::json::ARRAY_TYPE);

		std::vector<std::string> arrayValues = { "A", "B", "C" };
		for (std::string arrayValue : arrayValues)
		{
			auto jsonArrayItem = jsonArrayValue->buildValue(systelab::json::STRING_TYPE);
			jsonArrayItem->setString(arrayValue);
			jsonArrayValue->addArrayValue(std::move(jsonArrayItem));
		}

		jsonRootValue.addMember("attArray", std::move(jsonArrayValue));

		auto jsonObjectValue = jsonRootValue.buildValue(systelab::json::OBJECT_TYPE);
		jsonObjectValue->addMember("attNull", jsonObjectValue->buildValue(systelab::json::NULL_TYPE));
		jsonRootValue.addMember("attObject", std::move(jsonObjectValue));

		std::stringstream ss;
		ss << "{";
		ss << "    \"attInt\": 1234,";
		ss << "    \"attDouble\": 2.345,";
		ss << "    \"attTrue\": true,";
		ss << "    \"attFalse\": false,";
		ss << "    \"attString\": \"ABC XYZ\",";
		ss << "    \"attArray\": [\"A\", \"B\", \"C\"],";
		ss << "    \"attObject\": { \"attNull\": null }";
		ss << "}";
		std::string expectedJSON = ss.str();
		ASSERT_TRUE(compareJSONs(expectedJSON, jsonDocument->serialize(), *m_jsonAdapter));
	}

}}}}
