#include "stdafx.h"

#include "RapidJSONAdapter/JSONAdapter.h"
#include "RapidJSONAdapter/JSONDocument.h"
#include "RapidJSONAdapter/JSONValue.h"

#include "JSONAdapterTestUtilities/JSONAdapterUtilities.h"
#include "JSONAdapterTestUtilities/Mocks/MockJSONValue.h"


using namespace testing;
using namespace systelab::json::test_utility;

namespace systelab { namespace json { namespace rapidjson { namespace unit_test {

	class JSONDocumentExceptionsTest : public testing::Test
	{
	public:
		void SetUp()
		{
			m_jsonAdapter = std::make_unique<JSONAdapter>();
		}

	protected:
		std::unique_ptr<JSONAdapter> m_jsonAdapter;
	};


	// addMember
	TEST_F(JSONDocumentExceptionsTest, testAddMemberThrowsExceptionWhenGivenValueNotARapidJSONValue)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);

		auto mockJSONValue = std::make_unique<MockJSONValue>();
		ASSERT_THROW(jsonRootValue.addMember("attError", std::move(mockJSONValue)), std::runtime_error);
	}

	TEST_F(JSONDocumentExceptionsTest, testAddMemberThrowsExceptionWhenGivenValueBelongsToAnotherDocument)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::OBJECT_TYPE);

		auto otherJSONDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& otherJSONRootValue = otherJSONDocument->getRootValue();
		auto otherJSONValue = otherJSONRootValue.buildValue(systelab::json::STRING_TYPE);
		ASSERT_THROW(jsonRootValue.addMember("attError", std::move(otherJSONValue)), std::runtime_error);
	}


	// addArrayValue
	TEST_F(JSONDocumentExceptionsTest, testAddArrayValueThrowsExceptionWhenGivenValueNotARapidJSONValue)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::ARRAY_TYPE);

		auto mockJSONValue = std::make_unique<MockJSONValue>();
		ASSERT_THROW(jsonRootValue.addArrayValue(std::move(mockJSONValue)), std::runtime_error);
	}

	TEST_F(JSONDocumentExceptionsTest, testAddArrayValueThrowsExceptionWhenGivenValueBelongsToAnotherDocument)
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& jsonRootValue = jsonDocument->getRootValue();
		jsonRootValue.setType(systelab::json::ARRAY_TYPE);

		auto otherJSONDocument = m_jsonAdapter->buildEmptyDocument();
		systelab::json::IJSONValue& otherJSONRootValue = otherJSONDocument->getRootValue();
		auto otherJSONValue = otherJSONRootValue.buildValue(systelab::json::STRING_TYPE);
		ASSERT_THROW(jsonRootValue.addArrayValue(std::move(otherJSONValue)), std::runtime_error);
	}

}}}}
