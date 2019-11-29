#include "stdafx.h"
#include "RapidJSONAdapter/JSONAdapter.h"

#include "RapidJSONAdapter/JSONDocument.h"
#include "RapidJSONAdapter/JSONValue.h"

#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"
#include "JSONAdapterTestUtilities/Mocks/MockJSONRemoteSchemaProvider.h"


using namespace testing;
using namespace systelab::json::test_utility;

namespace systelab { namespace json { namespace rapidjson { namespace unit_test {

	class JSONRemoteSchemaValidationTest : public testing::Test
	{
	public:
		void SetUp()
		{
			ON_CALL(m_jsonRemoteSchemaProvider, getRemoteSchemaDocumentProxy(_)).WillByDefault(Invoke(
				[this](const std::string& uri) -> IJSONDocument*
				{
					if (uri == "JSON_SCHEMA_MODEL_ADDRESS")
					{
						std::string addressSchema = getAddressSchemaDocument();
						return m_jsonAdapter.buildDocumentFromString(addressSchema).release();
					}

					return nullptr;
				}
			));
		}

		std::string getUserSchemaDocument()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "    \"type\": \"object\"," << std::endl;
			ss << "    \"properties\":" << std::endl;
			ss << "    {" << std::endl;
			ss << "        \"name\": { \"type\": \"string\" }," << std::endl;
			ss << "        \"surname\": { \"type\": \"string\" }," << std::endl;
			ss << "        \"address\":" << std::endl;
			ss << "        {" << std::endl;
			ss << "            \"$ref\": \"JSON_SCHEMA_MODEL_ADDRESS#/definitions/address\"" << std::endl;
			ss << "        }" << std::endl;
			ss << "    }," << std::endl;
			ss << "    \"required\": [\"name\", \"surname\"]," << std::endl;
			ss << "    \"additionalProperties\": false" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}

		std::string getAddressSchemaDocument()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "    \"$schema\": \"http://json-schema.org/draft-04/schema#\", " << std::endl;
			ss << "    \"id\": \"Address.json\"," << std::endl;
			ss << "    \"definitions\":" << std::endl;
			ss << "    {" << std::endl;
			ss << "        \"address\":" << std::endl;
			ss << "        {" << std::endl;
			ss << "            \"type\": \"object\"," << std::endl;
			ss << "            \"properties\":" << std::endl;
			ss << "            {" << std::endl;
			ss << "                \"city\": { \"type\": \"string\", \"minLength\": 1 }," << std::endl;
			ss << "                \"street\": { \"type\": \"string\", \"minLength\": 1, \"maxLength\": 25 }," << std::endl;
			ss << "                \"zip\": { \"type\": \"integer\" }" << std::endl;
			ss << "            }," << std::endl;
			ss << "            \"required\": [\"city\", \"street\"]," << std::endl;
			ss << "            \"additionalProperties\": false" << std::endl;
			ss << "        }" << std::endl;
			ss << "    }," << std::endl;
			ss << "    \"$ref\": \"#/definitions/address\"" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}

	protected:
		JSONAdapter m_jsonAdapter;
		MockJSONRemoteSchemaProvider m_jsonRemoteSchemaProvider;
	};


	// Positive cases
	TEST_F(JSONRemoteSchemaValidationTest, testUserSchemaValidationReturnsTrueForJSONWithoutAddress)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"name\": \"James\"," << std::endl;
		ss << "    \"surname\": \"Bond\"" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_TRUE(validateJSONSchema(document, getUserSchemaDocument(), m_jsonRemoteSchemaProvider, m_jsonAdapter));
	}

	TEST_F(JSONRemoteSchemaValidationTest, testUserSchemaValidationReturnsTrueForJSONWithSimpleAddress)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"name\": \"James\"," << std::endl;
		ss << "    \"surname\": \"Bond\"," << std::endl;
		ss << "    \"address\":" << std::endl;
		ss << "    {" << std::endl;
		ss << "        \"city\": \"London\"," << std::endl;
		ss << "        \"street\": \"Trafalgar Square\"" << std::endl;
		ss << "    }" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_TRUE(validateJSONSchema(document, getUserSchemaDocument(), m_jsonRemoteSchemaProvider, m_jsonAdapter));
	}

	TEST_F(JSONRemoteSchemaValidationTest, testUserSchemaValidationReturnsTrueForJSONWithCompleteAddress)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"name\": \"James\"," << std::endl;
		ss << "    \"surname\": \"Bond\"," << std::endl;
		ss << "    \"address\":" << std::endl;
		ss << "    {" << std::endl;
		ss << "        \"city\": \"London\"," << std::endl;
		ss << "        \"street\": \"Trafalgar Square\"," << std::endl;
		ss << "        \"zip\": 700" << std::endl;
		ss << "    }" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_TRUE(validateJSONSchema(document, getUserSchemaDocument(), m_jsonRemoteSchemaProvider, m_jsonAdapter));
	}


	// Negative cases
	TEST_F(JSONRemoteSchemaValidationTest, testUserSchemaValidationReturnsFalseForJSONWithoutRequiredProperties)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"surname\": \"Bond\"" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(validateJSONSchema(document, getUserSchemaDocument(), m_jsonRemoteSchemaProvider, m_jsonAdapter));
	}

	TEST_F(JSONRemoteSchemaValidationTest, testUserSchemaValidationReturnsFalseForJSONWithAdditionalProperties)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"name\": \"James\"," << std::endl;
		ss << "    \"surname\": \"Bond\"," << std::endl;
		ss << "    \"age\": 35" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(validateJSONSchema(document, getUserSchemaDocument(), m_jsonRemoteSchemaProvider, m_jsonAdapter));
	}

	TEST_F(JSONRemoteSchemaValidationTest, testUserSchemaValidationReturnsFalseForJSONWithWrongTypeOnName)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"name\": 700," << std::endl;
		ss << "    \"surname\": \"Bond\"" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(validateJSONSchema(document, getUserSchemaDocument(), m_jsonRemoteSchemaProvider, m_jsonAdapter));
	}

	TEST_F(JSONRemoteSchemaValidationTest, testUserSchemaValidationReturnsFalseForJSONWithMissingAddressRequiredProperty)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"name\": \"James\"," << std::endl;
		ss << "    \"surname\": \"Bond\"," << std::endl;
		ss << "    \"address\":" << std::endl;
		ss << "    {" << std::endl;
		ss << "        \"city\": \"London\"" << std::endl;
		ss << "    }" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(validateJSONSchema(document, getUserSchemaDocument(), m_jsonRemoteSchemaProvider, m_jsonAdapter));
	}

	TEST_F(JSONRemoteSchemaValidationTest, testUserSchemaValidationReturnsFalseForJSONWithAdditionalPropertyOnAddress)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"name\": \"James\"," << std::endl;
		ss << "    \"surname\": \"Bond\"," << std::endl;
		ss << "    \"address\":" << std::endl;
		ss << "    {" << std::endl;
		ss << "        \"city\": \"London\"," << std::endl;
		ss << "        \"street\": \"Trafalgar Square\"," << std::endl;
		ss << "        \"coordinates\": \"007N, 007W\"" << std::endl;
		ss << "    }" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(validateJSONSchema(document, getUserSchemaDocument(), m_jsonRemoteSchemaProvider, m_jsonAdapter));
	}

	TEST_F(JSONRemoteSchemaValidationTest, testUserSchemaValidationReturnsFalseForJSONWithWrongTypeOnAddress)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"name\": \"James\"," << std::endl;
		ss << "    \"surname\": \"Bond\"," << std::endl;
		ss << "    \"address\":" << std::endl;
		ss << "    {" << std::endl;
		ss << "        \"city\": 123," << std::endl;
		ss << "        \"street\": \"Trafalgar Square\"" << std::endl;
		ss << "    }" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(validateJSONSchema(document, getUserSchemaDocument(), m_jsonRemoteSchemaProvider, m_jsonAdapter));
	}


	// Remote schema errors
	TEST_F(JSONRemoteSchemaValidationTest, testUserSchemaValidationReturnsTrueWhenAddressSchemaNotFound)
	{
		ON_CALL(m_jsonRemoteSchemaProvider, getRemoteSchemaDocumentProxy(_)).WillByDefault(ReturnNull());

		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"name\": \"James\"," << std::endl;
		ss << "    \"surname\": \"Bond\"" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_TRUE(validateJSONSchema(document, getUserSchemaDocument(), m_jsonRemoteSchemaProvider, m_jsonAdapter));
	}

	TEST_F(JSONRemoteSchemaValidationTest, testUserSchemaValidationReturnsTrueWhenAddressSchemaIsNotAJSON)
	{
		ON_CALL(m_jsonRemoteSchemaProvider, getRemoteSchemaDocumentProxy(_)).WillByDefault(Invoke(
			[this](const std::string& uri) -> IJSONDocument*
			{
				auto document = std::make_unique<::rapidjson::Document>();
				document->Parse("Not a JSON");
				return std::make_unique<JSONDocument>(std::move(document)).release();
			}
		));

		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"name\": \"James\"," << std::endl;
		ss << "    \"surname\": \"Bond\"" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_TRUE(validateJSONSchema(document, getUserSchemaDocument(), m_jsonRemoteSchemaProvider, m_jsonAdapter));
	}

}}}}
