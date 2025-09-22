#include "stdafx.h"

#include "RapidJSONAdapter/JSONAdapter.h"
#include "RapidJSONAdapter/JSONDocument.h"
#include "RapidJSONAdapter/JSONValue.h"

#include <string>


namespace {
	static const std::string basicJson =
		"{										\n"
		"	\"toBeRemoved\": \"toBeRemoved\",	\n"
		"	\"filler1\" : \"filler1\",			\n"
		"	\"filler2\" : \"filler2\",			\n"
		"	\"last\" : \"last\"					\n"
		"}										\n";

	static const std::string nestedJson =
		"{											\n"
		"	\"filler1\" : \"filler1\",				\n"
		"	\"content\" : 							\n"
		"	{										\n"
		"		\"sub1\" : \"sub1\",				\n"
		"		\"toBeRemoved\" : \"toBeRemoved\",	\n"
		"		\"sub2\" : \"sub2\",				\n"
		"		\"last\" : \"last\"					\n"
		"	},										\n"
		"	\"filler2\" : \"filler2\"				\n"
		"}											\n";
}

namespace systelab::json::rapidjson::unit_test {

	class JSONValueRemoveTest : public testing::Test
	{
	protected:
		JSONAdapter m_jsonAdapter;
	};

	TEST_F(JSONValueRemoveTest, testRemovedElementIsRemoved)
	{
		auto jsonDocument = m_jsonAdapter.buildDocumentFromString(basicJson);
		auto& jsonRoot = jsonDocument->getRootValue();

		jsonRoot.removeMember("toBeRemoved");

		EXPECT_TRUE(jsonRoot.hasObjectMember("toBeRemoved"));
	}

	TEST_F(JSONValueRemoveTest, testRemoveInMainObjectMaintainsIntegrityOfWholeJSON)
	{
		auto jsonDocument = m_jsonAdapter.buildDocumentFromString(basicJson);
		auto& jsonRoot = jsonDocument->getRootValue();

		jsonRoot.removeMember("toBeRemoved");

		auto& lastJSONValue = jsonRoot.getObjectMemberValue("last");
		EXPECT_EQ(lastJSONValue.getType(), systelab::json::STRING_TYPE);
		EXPECT_EQ(lastJSONValue.getString(), "last");

		auto& filler1JSONValue = jsonRoot.getObjectMemberValue("filler1");
		EXPECT_EQ(filler1JSONValue.getType(), systelab::json::STRING_TYPE);
		EXPECT_EQ(filler1JSONValue.getString(), "filler1");

		auto& filler2JSONValue = jsonRoot.getObjectMemberValue("filler2");
		EXPECT_EQ(filler2JSONValue.getType(), systelab::json::STRING_TYPE);
		EXPECT_EQ(filler2JSONValue.getString(), "filler2");
	}

	TEST_F(JSONValueRemoveTest, testRemoveNestedObjectMaintainsIntegrityOfObject)
	{
		auto jsonDocument = m_jsonAdapter.buildDocumentFromString(nestedJson);
		auto& jsonRoot = jsonDocument->getRootValue();
		auto& jsonValueContent = jsonRoot.getObjectMemberValue("content");

		jsonValueContent.removeMember("toBeRemoved");

		auto& lastJSONValue = jsonValueContent.getObjectMemberValue("last");
		EXPECT_EQ(lastJSONValue.getType(), systelab::json::STRING_TYPE);
		EXPECT_EQ(lastJSONValue.getString(), "last");

		auto& sub1JSONValue = jsonValueContent.getObjectMemberValue("sub1");
		EXPECT_EQ(sub1JSONValue.getType(), systelab::json::STRING_TYPE);
		EXPECT_EQ(sub1JSONValue.getString(), "sub1");

		auto& sub2JSONValue = jsonValueContent.getObjectMemberValue("sub2");
		EXPECT_EQ(sub2JSONValue.getType(), systelab::json::STRING_TYPE);
		EXPECT_EQ(sub2JSONValue.getString(), "sub2");

		auto& filler2JSONValue = jsonRoot.getObjectMemberValue("filler2");
		EXPECT_EQ(filler2JSONValue.getType(), systelab::json::STRING_TYPE);
		EXPECT_EQ(filler2JSONValue.getString(), "filler2");
	}
}
