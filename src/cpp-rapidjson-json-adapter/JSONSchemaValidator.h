#pragma once

#include "IJSONSchemaValidator.h"

#include <rapidjson/schema.h>
#include <memory>

namespace systelab {
namespace json_adapter {
class IJSONRemoteSchemaProvider;
}
}  // namespace systelab

namespace systelab {
namespace json_adapter {
namespace rapidjson_adapter {

class JSONSchemaValidator : public IJSONSchemaValidator {
 private:
  class RapidjsonSchemaRemoteDocumentProvider
      : public rapidjson::IRemoteSchemaDocumentProvider {
   public:
    RapidjsonSchemaRemoteDocumentProvider(const IJSONRemoteSchemaProvider&);

    virtual const rapidjson::SchemaDocument* GetRemoteDocument(
        const char* uri, rapidjson::SizeType length);

   private:
    const IJSONRemoteSchemaProvider& m_remoteSchemaProvider;

    std::unique_ptr<rapidjson::SchemaDocument> buildSchemaDocument(
        const std::string& uri);
  };

 public:
  JSONSchemaValidator(const IJSONDocument&);
  JSONSchemaValidator(const IJSONDocument&, const IJSONRemoteSchemaProvider&);
  virtual ~JSONSchemaValidator();

  bool validate(const IJSONDocument&, std::string& reason) const;

 private:
  std::unique_ptr<RapidjsonSchemaRemoteDocumentProvider>
      m_rapidjsonRemoteSchemaProvider;
  std::unique_ptr<rapidjson::SchemaDocument> m_schemaDocument;
};

}  // namespace rapidjson_adapter
}  // namespace json_adapter
}  // namespace systelab
