#include "RapidJSONAdapter/JSONAdapter.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"
#include "JSONAdapterInterface/IJSONValue.h"

#include <iostream>


int main(int argc, char *argv[])
{
    std::unique_ptr<systelab::json::IJSONAdapter> jsonAdapter = std::make_unique<systelab::json::rapidjson::JSONAdapter>();
    std::unique_ptr<systelab::json::IJSONDocument> document = jsonAdapter->buildDocumentFromString("{\"working\":\"false\"}");
	std::cout << "Document built" << std::endl;

    systelab::json::IJSONValue& workingValue = document->getRootValue().getObjectMemberValue("working");
    workingValue.setBoolean(true);
	std::cout << "Working value updated" << std::endl;

	std::string serializedDocument = document->serialize();
    std::cout << serializedDocument << std::endl;

    return 0;
}
