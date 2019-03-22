/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#include "TestFunctions.h"

namespace facebook {
namespace hermes {
namespace synthtest {

const char *hostCallsJSWithThisTrace() {
  return R"###(
{
  "version": 2,
  "globalObjID": 1,
  "env": {
    "mathRandomSeed": 0,
    "callsToDateNow": [],
    "callsToNewDate": [],
    "callsToDateAsFunction": []
  },
  "trace": [
    {
      "type": "CreateHostFunctionRecord",
      "time": 0,
      "objID": 10
    },
    {
      "type": "SetPropertyRecord",
      "time": 0,
      "objID": 1,
      "propName": "foo",
      "value": "object:10"
    },
    {
      "type": "BeginExecJSRecord",
      "time": 0
    },
    {
      "type": "CallToNativeRecord",
      "time": 0,
      "functionID": 10,
      "thisArg": "undefined:",
      "args": ["object:11"]
    },
    {
      "type": "GetPropertyRecord",
      "time": 0,
      "objID": 1,
      "propName": "f",
      "value": "object:12"
    },
    {
      "type": "CallFromNativeRecord",
      "time": 0,
      "functionID": 12,
      "thisArg": "object:11",
      "args": []
    },
    {
      "type": "ReturnToNativeRecord",
      "time": 0,
      "retval": "undefined:"
    },
    {
      "type": "ReturnFromNativeRecord",
      "time": 0,
      "retval": "undefined:"
    },
    {
      "type": "EndExecJSRecord",
      "retval": "undefined:",
      "time": 0
    }
  ]
}
)###";
}

const char *hostCallsJSWithThisSource() {
  return R"###(
'use strict';

(function(global) {
  // Native code creates a function foo.
  // foo calls f with o as this.
  // f calls the member function bar on its this argument
  // That call sets a to 2.
  var a = 1;
  global.f = function() {
    this.bar();
  };
  var o = {
    bar: function() {
      a = 2;
    }
  };
  global.foo(o);
  if (a !== 2) {
    throw new Error();
  }
})(this);
)###";
}

} // namespace synthtest
} // namespace hermes
} // namespace facebook
