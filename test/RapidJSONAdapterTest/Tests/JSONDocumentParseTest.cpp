#include "stdafx.h"
#include "RapidJSONAdapter/JSONAdapter.h"

#include "RapidJSONAdapter/JSONDocument.h"
#include "RapidJSONAdapter/JSONValue.h"


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


	TEST_F(JSONDocumentParseTest, testBuildDocumentFromEmptyString)
	{
		auto jsonDocument = m_jsonAdapter->buildDocumentFromString("");
		ASSERT_TRUE(jsonDocument == NULL);
	}

	TEST_F(JSONDocumentParseTest, testBuildDocumentFromInvalidJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildDocumentFromString("This is not a JSON");
		ASSERT_TRUE(jsonDocument == NULL);
	}

	TEST_F(JSONDocumentParseTest, testBuildDocumentFromEmptyObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildDocumentFromString("{}");
		ASSERT_TRUE(jsonDocument != NULL);

		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonRootValue.getType());
		ASSERT_EQ(0u, jsonRootValue.getObjectMemberCount());
	}

	TEST_F(JSONDocumentParseTest, testBuildDocumentFromSingleIntegerAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildDocumentFromString("{ \"attInt\": 1234 }");
		ASSERT_TRUE(jsonDocument != NULL);

		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonRootValue.getType());
		ASSERT_EQ(1u, jsonRootValue.getObjectMemberCount());
		ASSERT_THAT(jsonRootValue.getObjectMemberNames(), ElementsAreArray({ "attInt" }));

		systelab::json::IJSONValue& jsonIntValue = jsonRootValue.getObjectMemberValue("attInt");
		ASSERT_EQ(systelab::json::NUMBER_TYPE, jsonIntValue.getType());
		ASSERT_TRUE(jsonIntValue.isInteger());
		ASSERT_EQ(1234, jsonIntValue.getInteger());
	}

	TEST_F(JSONDocumentParseTest, testBuildDocumentFromSingleDoubleAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildDocumentFromString("{ \"attDouble\": 1.2345 }");
		ASSERT_TRUE(jsonDocument != NULL);

		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonRootValue.getType());
		ASSERT_EQ(1u, jsonRootValue.getObjectMemberCount());
		ASSERT_THAT(jsonRootValue.getObjectMemberNames(), ElementsAreArray({ "attDouble" }));

		systelab::json::IJSONValue& jsonDoubleValue = jsonRootValue.getObjectMemberValue("attDouble");
		ASSERT_EQ(systelab::json::NUMBER_TYPE, jsonDoubleValue.getType());
		ASSERT_FALSE(jsonDoubleValue.isInteger());
		ASSERT_NEAR(1.2345, jsonDoubleValue.getDouble(), 1e-6);
	}

	TEST_F(JSONDocumentParseTest, testBuildDocumentFromSingleTrueBooleanAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildDocumentFromString("{ \"attBoolean\": true }");
		ASSERT_TRUE(jsonDocument != NULL);

		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonRootValue.getType());
		ASSERT_EQ(1u, jsonRootValue.getObjectMemberCount());
		ASSERT_THAT(jsonRootValue.getObjectMemberNames(), ElementsAreArray({ "attBoolean" }));

		systelab::json::IJSONValue& jsonBooleanValue = jsonRootValue.getObjectMemberValue("attBoolean");
		ASSERT_EQ(systelab::json::BOOLEAN_TYPE, jsonBooleanValue.getType());
		ASSERT_TRUE(jsonBooleanValue.getBoolean());
	}

	TEST_F(JSONDocumentParseTest, testBuildDocumentFromSingleFalseBooleanAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildDocumentFromString("{ \"attBoolean\": false }");
		ASSERT_TRUE(jsonDocument != NULL);

		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonRootValue.getType());
		ASSERT_EQ(1u, jsonRootValue.getObjectMemberCount());
		ASSERT_THAT(jsonRootValue.getObjectMemberNames(), ElementsAreArray({ "attBoolean" }));

		systelab::json::IJSONValue& jsonBooleanValue = jsonRootValue.getObjectMemberValue("attBoolean");
		ASSERT_EQ(systelab::json::BOOLEAN_TYPE, jsonBooleanValue.getType());
		ASSERT_FALSE(jsonBooleanValue.getBoolean());
	}

	TEST_F(JSONDocumentParseTest, testBuildDocumentFromSingleStringAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildDocumentFromString("{ \"attString\": \"ABCDEF\" }");
		ASSERT_TRUE(jsonDocument != NULL);

		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonRootValue.getType());
		ASSERT_EQ(1u, jsonRootValue.getObjectMemberCount());
		ASSERT_THAT(jsonRootValue.getObjectMemberNames(), ElementsAreArray({ "attString" }));

		systelab::json::IJSONValue& jsonStringValue = jsonRootValue.getObjectMemberValue("attString");
		ASSERT_EQ(systelab::json::STRING_TYPE, jsonStringValue.getType());
		ASSERT_EQ("ABCDEF", jsonStringValue.getString());
	}

	TEST_F(JSONDocumentParseTest, testBuildDocumentFromSingleNullAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildDocumentFromString("{ \"attNull\": null }");
		ASSERT_TRUE(jsonDocument != NULL);

		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonRootValue.getType());
		ASSERT_EQ(1u, jsonRootValue.getObjectMemberCount());
		ASSERT_THAT(jsonRootValue.getObjectMemberNames(), ElementsAreArray({ "attNull" }));

		systelab::json::IJSONValue& jsonNullValue = jsonRootValue.getObjectMemberValue("attNull");
		ASSERT_EQ(systelab::json::NULL_TYPE, jsonNullValue.getType());
		ASSERT_TRUE(jsonNullValue.isNull());
	}

	TEST_F(JSONDocumentParseTest, testBuildDocumentFromSingleEmptyObjectAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildDocumentFromString("{ \"attObject\": {} }");
		ASSERT_TRUE(jsonDocument != NULL);

		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonRootValue.getType());
		ASSERT_EQ(1u, jsonRootValue.getObjectMemberCount());
		ASSERT_THAT(jsonRootValue.getObjectMemberNames(), ElementsAreArray({ "attObject" }));

		systelab::json::IJSONValue& jsonObjectValue = jsonRootValue.getObjectMemberValue("attObject");
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonObjectValue.getType());
		ASSERT_EQ(0u, jsonObjectValue.getObjectMemberCount());
	}

	TEST_F(JSONDocumentParseTest, testBuildDocumentFromSingleNonEmptyObjectAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildDocumentFromString("{ \"attObject\": { \"attSubObject\": true } }");
		ASSERT_TRUE(jsonDocument != NULL);

		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonRootValue.getType());
		ASSERT_EQ(1u, jsonRootValue.getObjectMemberCount());
		ASSERT_THAT(jsonRootValue.getObjectMemberNames(), ElementsAreArray({ "attObject" }));

		systelab::json::IJSONValue& jsonObjectValue = jsonRootValue.getObjectMemberValue("attObject");
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonObjectValue.getType());
		ASSERT_EQ(1u, jsonObjectValue.getObjectMemberCount());
		ASSERT_THAT(jsonObjectValue.getObjectMemberNames(), ElementsAreArray({ "attSubObject" }));

		systelab::json::IJSONValue& jsonSubObjectValue = jsonObjectValue.getObjectMemberValue("attSubObject");
		ASSERT_EQ(systelab::json::BOOLEAN_TYPE, jsonSubObjectValue.getType());
		ASSERT_TRUE(jsonSubObjectValue.getBoolean());
	}

	TEST_F(JSONDocumentParseTest, testBuildDocumentFromSingleArrayAttributeObjectJSON)
	{
		auto jsonDocument = m_jsonAdapter->buildDocumentFromString("{ \"attArray\": [9, 8, 7] }");
		ASSERT_TRUE(jsonDocument != NULL);

		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonRootValue.getType());
		ASSERT_EQ(1u, jsonRootValue.getObjectMemberCount());
		ASSERT_THAT(jsonRootValue.getObjectMemberNames(), ElementsAreArray({ "attArray" }));

		systelab::json::IJSONValue& jsonArrayValue = jsonRootValue.getObjectMemberValue("attArray");
		ASSERT_EQ(systelab::json::ARRAY_TYPE, jsonArrayValue.getType());
		ASSERT_EQ(3, jsonArrayValue.getArrayValueCount());
		ASSERT_EQ(9, jsonArrayValue.getArrayValue(0).getInteger());
		ASSERT_EQ(8, jsonArrayValue.getArrayValue(1).getInteger());
		ASSERT_EQ(7, jsonArrayValue.getArrayValue(2).getInteger());
	}

	TEST_F(JSONDocumentParseTest, testBuildDocumentFromComplexJSON)
	{
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

		auto jsonDocument = m_jsonAdapter->buildDocumentFromString(ss.str());
		ASSERT_TRUE(jsonDocument != NULL);

		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonRootValue.getType());
		ASSERT_EQ(7u, jsonRootValue.getObjectMemberCount());
		ASSERT_THAT(jsonRootValue.getObjectMemberNames(),
					UnorderedElementsAreArray({ "attInt", "attDouble", "attTrue", "attFalse",
												"attString", "attArray", "attObject" }));

		ASSERT_EQ(systelab::json::NUMBER_TYPE, jsonRootValue.getObjectMemberValue("attInt").getType());
		ASSERT_EQ(1234, jsonRootValue.getObjectMemberValue("attInt").getInteger());

		ASSERT_EQ(systelab::json::NUMBER_TYPE, jsonRootValue.getObjectMemberValue("attDouble").getType());
		ASSERT_NEAR(2.345, jsonRootValue.getObjectMemberValue("attDouble").getDouble(), 1e-8);

		ASSERT_EQ(systelab::json::BOOLEAN_TYPE, jsonRootValue.getObjectMemberValue("attTrue").getType());
		ASSERT_TRUE(jsonRootValue.getObjectMemberValue("attTrue").getBoolean());

		ASSERT_EQ(systelab::json::BOOLEAN_TYPE, jsonRootValue.getObjectMemberValue("attFalse").getType());
		ASSERT_FALSE(jsonRootValue.getObjectMemberValue("attFalse").getBoolean());

		ASSERT_EQ(systelab::json::STRING_TYPE, jsonRootValue.getObjectMemberValue("attString").getType());
		ASSERT_EQ("ABC XYZ", jsonRootValue.getObjectMemberValue("attString").getString());

		systelab::json::IJSONValue& jsonArrayValue = jsonRootValue.getObjectMemberValue("attArray");
		ASSERT_EQ(systelab::json::ARRAY_TYPE, jsonArrayValue.getType());
		ASSERT_EQ(3, jsonArrayValue.getArrayValueCount());
		ASSERT_EQ("A", jsonArrayValue.getArrayValue(0).getString());
		ASSERT_EQ("B", jsonArrayValue.getArrayValue(1).getString());
		ASSERT_EQ("C", jsonArrayValue.getArrayValue(2).getString());

		systelab::json::IJSONValue& jsonObjectValue = jsonRootValue.getObjectMemberValue("attObject");
		ASSERT_EQ(systelab::json::OBJECT_TYPE, jsonObjectValue.getType());
		ASSERT_EQ(1, jsonObjectValue.getObjectMemberCount());
		ASSERT_THAT(jsonObjectValue.getObjectMemberNames(), UnorderedElementsAreArray({"attNull"}));
		ASSERT_EQ(systelab::json::NULL_TYPE, jsonObjectValue.getObjectMemberValue("attNull").getType());
	}

}}}}
