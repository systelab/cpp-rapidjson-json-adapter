#include "RapidJSONAdapter/JSONAdapter.h"

#include "JSONAdapterInterface/IJSONDocument.h"
#include "JSONAdapterInterface/IJSONValue.h"

#include <iostream>


int main()
{
    systelab::json::rapidjson::JSONAdapter jsonAdapter;
    std::unique_ptr<systelab::json::IJSONDocument> document = jsonAdapter.buildDocumentFromString("{\"working\":\"false\"}");

    systelab::json::IJSONValue& workingValue = document->getRootValue().getObjectMemberValue("working");
    workingValue.setBoolean(true);

    std::cout << document->serialize() << std::endl;

    return 0;
}
