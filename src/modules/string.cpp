// Copyright 2015 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "breadboard/modules/string.h"

#include <string>
#include <sstream>

#include "breadboard/base_node.h"
#include "breadboard/module_registry.h"

namespace breadboard {

// Compares two strings.
class EqualsNode : public BaseNode {
 public:
  virtual ~EqualsNode() {}

  static void OnRegister(NodeSignature* node_sig) {
    node_sig->AddInput<std::string>();
    node_sig->AddInput<std::string>();
    node_sig->AddOutput<bool>();
  }

  virtual void Initialize(NodeArguments* args) {
    auto str_a = args->GetInput<std::string>(0);
    auto str_b = args->GetInput<std::string>(1);
    args->SetOutput(0, *str_a == *str_b);
  }

  virtual void Execute(NodeArguments* args) { Initialize(args); }
};

// Converts the given int to a string.
class IntToStringNode : public BaseNode {
 public:
  virtual ~IntToStringNode() {}

  static void OnRegister(NodeSignature* node_sig) {
    node_sig->AddInput<int>();
    node_sig->AddOutput<std::string>();
  }

  virtual void Execute(NodeArguments* args) {
    auto i = args->GetInput<int>(0);
    std::stringstream stream;
    stream << *i;
    args->SetOutput(0, stream.str());
  }
};

// Converts the given float to a string.
class FloatToStringNode : public BaseNode {
 public:
  virtual ~FloatToStringNode() {}

  static void OnRegister(NodeSignature* node_sig) {
    node_sig->AddInput<float>();
    node_sig->AddOutput<std::string>();
  }

  virtual void Execute(NodeArguments* args) {
    auto f = args->GetInput<float>(0);
    std::stringstream stream;
    stream << *f;
    args->SetOutput(0, stream.str());
  }
};

// Concatenates the given strings.
class ConcatNode : public BaseNode {
 public:
  virtual ~ConcatNode() {}

  static void OnRegister(NodeSignature* node_sig) {
    node_sig->AddInput<std::string>();
    node_sig->AddInput<std::string>();
    node_sig->AddOutput<std::string>();
  }

  virtual void Execute(NodeArguments* args) {
    auto str_a = args->GetInput<std::string>(0);
    auto str_b = args->GetInput<std::string>(1);
    args->SetOutput(0, *str_a + *str_b);
  }
};

void InitializeStringModule(ModuleRegistry* module_registry) {
  Module* module = module_registry->RegisterModule("string");
  module->RegisterNode<EqualsNode>("equals");
  module->RegisterNode<IntToStringNode>("int_to_string");
  module->RegisterNode<FloatToStringNode>("float_to_string");
  module->RegisterNode<ConcatNode>("concat");
}

}  // namespace breadboard
