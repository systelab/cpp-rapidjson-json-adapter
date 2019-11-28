#include "stdafx.h"
#include "RapidJSONAdapter/JSONAdapter.h"

#include "RapidJSONAdapter/JSONDocument.h"
#include "RapidJSONAdapter/JSONValue.h"

#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"


using namespace testing;
using namespace systelab::json::test_utility;

namespace systelab { namespace json { namespace rapidjson { namespace unit_test {

	class JSONSchemaValidationTest : public testing::Test
	{
	public:
		void SetUp()
		{
			m_jsonAdapter = std::make_unique<JSONAdapter>();
		}

		std::string getSimpleTypesSchemaDocument()
		{
			std::stringstream ss;
			ss << "{" << std::endl;
			ss << "    \"type\": \"object\"," << std::endl;
			ss << "    \"properties\":" << std::endl;
			ss << "    {" << std::endl;
			ss << "        \"intField\": { \"type\": \"integer\", \"minimum\": 0 }," << std::endl;
			ss << "        \"numField\": { \"type\": \"number\", \"maximum\": 3.5 }," << std::endl;
			ss << "        \"strField\": { \"type\": \"string\", \"minLength\": 3, \"maxLength\": 10, \"pattern\": \"^[A-Z]*$\" }," << std::endl;
			ss << "        \"enumField\": { \"type\": \"string\", \"enum\": [\"option1\", \"option2\"] }," << std::endl;
			ss << "        \"boolField\": { \"type\": \"boolean\" }," << std::endl;
			ss << "        \"dateField\": { \"type\": \"string\", \"format\": \"date-time\" }" << std::endl;
			ss << "    }," << std::endl;
			ss << "    \"required\": [\"intField\", \"strField\", \"boolField\"]," << std::endl;
			ss << "    \"additionalProperties\": false" << std::endl;
			ss << "}" << std::endl;

			return ss.str();
		}

		std::string getComplexSchemaDocument()
		{
			throw std::runtime_error("TODO");
		}

	protected:
		std::unique_ptr<JSONAdapter> m_jsonAdapter;
	};


	// Simple types schema
	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsTrueForJSONWithOnlyRequiredFields)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": 10," << std::endl;
		ss << "    \"strField\": \"ABCDE\"," << std::endl;
		ss << "    \"boolField\": true" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_TRUE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsTrueForJSONWithAllDefinedFields)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": 10," << std::endl;
		ss << "    \"numField\": 2.5," << std::endl;
		ss << "    \"strField\": \"ABCDE\"," << std::endl;
		ss << "    \"enumField\": \"option1\"," << std::endl;
		ss << "    \"boolField\": true," << std::endl;
		ss << "    \"dateField\": \"20201231\"" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_TRUE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsFalseForJSONWithAdditionalProperties)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": 10," << std::endl;
		ss << "    \"strField\": \"ABCDE\"," << std::endl;
		ss << "    \"boolField\": true," << std::endl;
		ss << "    \"additionalProp\": true" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsFalseForJSONWithMissingRequiredProperty)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": 10," << std::endl;
		ss << "    \"boolField\": true" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsFalseForJSONWithIntegerPropertyWithWrongTypeValue)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": false," << std::endl;
		ss << "    \"strField\": \"ABCDE\"," << std::endl;
		ss << "    \"boolField\": true" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsFalseForJSONWithIntegerPropertyWithTooLowValue)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": -1," << std::endl;
		ss << "    \"strField\": \"ABCDE\"," << std::endl;
		ss << "    \"boolField\": true" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsFalseForJSONWithNumberPropertyWithWrongTypeValue)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": 1," << std::endl;
		ss << "    \"numField\": false," << std::endl;
		ss << "    \"strField\": \"ABCDE\"," << std::endl;
		ss << "    \"boolField\": true" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsFalseForJSONWithNumberPropertyWithTooHighValue)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": 1," << std::endl;
		ss << "    \"numField\": 999," << std::endl;
		ss << "    \"strField\": \"ABCDE\"," << std::endl;
		ss << "    \"boolField\": true" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsFalseForJSONWithStringPropertyWithWrongTypeValue)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": 10," << std::endl;
		ss << "    \"strField\": 10," << std::endl;
		ss << "    \"boolField\": true" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsFalseForJSONWithStringPropertyWithTooShortValue)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": 10," << std::endl;
		ss << "    \"strField\": \"AB\"," << std::endl;
		ss << "    \"boolField\": true" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsFalseForJSONWithStringPropertyWithTooLongValue)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": 10," << std::endl;
		ss << "    \"strField\": \"ABCDEFGHIJKLMNOPRSTUVWXYZ\"," << std::endl;
		ss << "    \"boolField\": true" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsFalseForJSONWithStringPropertyWithWrongPatternValue)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": 10," << std::endl;
		ss << "    \"strField\": \"ABCDeFG\"," << std::endl;
		ss << "    \"boolField\": true" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsFalseForJSONWithEnumPropertyWithWrongValue)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": 10," << std::endl;
		ss << "    \"strField\": \"ABCDEFG\"," << std::endl;
		ss << "    \"boolField\": true," << std::endl;
		ss << "    \"enumField\": \"option3\"" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

	TEST_F(JSONSchemaValidationTest, testSimpleTypesSchemaValidationReturnsFalseForJSONWithBooleanPropertyWithWrongTypeValue)
	{
		std::stringstream ss;
		ss << "{" << std::endl;
		ss << "    \"intField\": 10," << std::endl;
		ss << "    \"strField\": \"ABCDEFG\"," << std::endl;
		ss << "    \"boolField\": 123" << std::endl;
		ss << "}" << std::endl;
		std::string document = ss.str();

		ASSERT_FALSE(test_utility::validateJSONSchema(document, getSimpleTypesSchemaDocument(), *m_jsonAdapter));
	}

}}}}