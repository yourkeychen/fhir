// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GOOGLE_FHIR_STU3_ANNOTATIONS_H_
#define GOOGLE_FHIR_STU3_ANNOTATIONS_H_


#include "google/protobuf/descriptor.pb.h"
#include "google/protobuf/message.h"
#include "proto/stu3/annotations.pb.h"

namespace google {
namespace fhir {
namespace stu3 {

using std::string;
const string& GetStructureDefinitionUrl(const ::google::protobuf::Descriptor* descriptor);

// Returns true if the passed-in descriptor is a profile of the template FHIR
// type
template <typename B>
const bool IsProfileOf(const ::google::protobuf::Descriptor* descriptor) {
  const string& base_url = GetStructureDefinitionUrl(B::descriptor());
  for (int i = 0;
       i < descriptor->options().ExtensionSize(stu3::proto::fhir_profile_base);
       i++) {
    if (descriptor->options().GetExtension(stu3::proto::fhir_profile_base, i) ==
        base_url) {
      return true;
    }
  }
  return false;
}

// Returns true if the passed-in message is a profile of the template FHIR type
template <typename B>
const bool IsProfileOf(const ::google::protobuf::Message& message) {
  return IsProfileOf<B>(message.GetDescriptor());
}

// Returns true if the passed-in message is either of the template FHIR type,
// or a profile of that type.
template <typename B>
const bool IsTypeOrProfileOf(const ::google::protobuf::Message& message) {
  const string& actual_type =
      GetStructureDefinitionUrl(message.GetDescriptor());
  return (!actual_type.empty() &&
          actual_type == GetStructureDefinitionUrl(B::descriptor())) ||
         IsProfileOf<B>(message);
}

const bool IsProfile(const ::google::protobuf::Descriptor* descriptor);

const bool IsChoiceType(const ::google::protobuf::FieldDescriptor* field);

const bool IsPrimitive(const ::google::protobuf::Descriptor* descriptor);

const bool IsResource(const ::google::protobuf::Descriptor* descriptor);

const bool IsReference(const ::google::protobuf::Descriptor* descriptor);

const bool HasValueset(const ::google::protobuf::Descriptor* descriptor);

const string& GetInlinedCodingSystem(const ::google::protobuf::FieldDescriptor* field);

const string& GetInlinedCodingCode(const ::google::protobuf::FieldDescriptor* field);

const string& GetValueRegex(const ::google::protobuf::Descriptor* descriptor);

}  // namespace stu3
}  // namespace fhir
}  // namespace google

#endif  // GOOGLE_FHIR_STU3_ANNOTATIONS_H_
