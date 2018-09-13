/**
 * This source code is licensed under the terms found in the LICENSE file in 
 * node-jsc's root directory.
 */

#include "config.h"
#include "v8.h"

#include "shim/helpers.h"

#include <JavaScriptCore/JSCInlines.h>

namespace v8
{

bool Boolean::Value() const
{
	return jscshim::GetValue(this).asBoolean();
}

} // v8