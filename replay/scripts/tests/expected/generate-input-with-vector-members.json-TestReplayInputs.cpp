/*
 * Copyright (C) 2014 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// DO NOT EDIT THIS FILE. It is automatically generated from generate-input-with-vector-members.json
// by the script: JavaScriptCore/replay/scripts/CodeGeneratorReplayInputs.py

#include "config.h"
#include "generate-input-with-vector-members.json-TestReplayInputs.h"

#if ENABLE(WEB_REPLAY)
#include "InternalNamespaceImplIncludeDummy.h"
#include <platform/ExternalNamespaceImplIncludeDummy.h>
#include <things/JSThing.h>
#include <things/WebThing.h>

namespace Test {
ArrayOfThings::ArrayOfThings(Vector<double>& doubles, Vector<JSThing>& jsthings, Vector<WebThing>& webthings)
    : NondeterministicInput<ArrayOfThings>()
    , m_doubles(doubles)
    , m_jsthings(jsthings)
    , m_webthings(webthings)
{
}

ArrayOfThings::~ArrayOfThings()
{
}
} // namespace Test

namespace JSC {
const AtomicString& InputTraits<Test::ArrayOfThings>::type()
{
    static NeverDestroyed<const AtomicString> type("ArrayOfThings", AtomicString::ConstructFromLiteral);
    return type;
}

void InputTraits<Test::ArrayOfThings>::encode(EncodedValue& encodedValue, const Test::ArrayOfThings& input)
{
    encodedValue.put<Vector<double>>(ASCIILiteral("doubles"), input.doubles());
    encodedValue.put<Vector<JSThing>>(ASCIILiteral("jsthings"), input.jsthings());
    encodedValue.put<Vector<WebCore::WebThing>>(ASCIILiteral("webthings"), input.webthings());
}

bool InputTraits<Test::ArrayOfThings>::decode(EncodedValue& encodedValue, std::unique_ptr<Test::ArrayOfThings>& input)
{
    Vector<double> doubles;
    if (!encodedValue.get<Vector<double>>(ASCIILiteral("doubles"), doubles))
        return false;

    Vector<JSThing> jsthings;
    if (!encodedValue.get<Vector<JSThing>>(ASCIILiteral("jsthings"), jsthings))
        return false;

    Vector<WebCore::WebThing> webthings;
    if (!encodedValue.get<Vector<WebCore::WebThing>>(ASCIILiteral("webthings"), webthings))
        return false;

    input = std::make_unique<Test::ArrayOfThings>(doubles, jsthings, webthings);
    return true;
}

} // namespace JSC

#endif // ENABLE(WEB_REPLAY)
