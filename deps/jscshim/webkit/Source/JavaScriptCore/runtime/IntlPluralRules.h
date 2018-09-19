/*
 * Copyright (C) 2018 Andy VanWagoner (andy@vanwagoner.family)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(INTL)

#include "JSDestructibleObject.h"
#include <unicode/unum.h>
#include <unicode/upluralrules.h>
#include <unicode/uvernum.h>

#define JSC_ICU_HAS_PLURALRULES_KEYWORDS (U_ICU_VERSION_MAJOR_NUM >= 59)
#define JSC_ICU_HAS_PLURALRULES_WITH_FORMAT (U_ICU_VERSION_MAJOR_NUM >= 59)

namespace JSC {

class IntlPluralRulesConstructor;
class JSBoundFunction;

class IntlPluralRules final : public JSDestructibleObject {
public:
    typedef JSDestructibleObject Base;

    static IntlPluralRules* create(VM&, Structure*);
    static Structure* createStructure(VM&, JSGlobalObject*, JSValue);

    DECLARE_INFO;

    void initializePluralRules(ExecState&, JSValue locales, JSValue options);
    JSValue select(ExecState&, double value);
    JSObject* resolvedOptions(ExecState&);

protected:
    IntlPluralRules(VM&, Structure*);
    void finishCreation(VM&);
    static void destroy(JSCell*);
    static void visitChildren(JSCell*, SlotVisitor&);

private:
    struct UPluralRulesDeleter {
        void operator()(UPluralRules*) const;
    };
    struct UNumberFormatDeleter {
        void operator()(UNumberFormat*) const;
    };

    bool m_initializedPluralRules { false };
    std::unique_ptr<UPluralRules, UPluralRulesDeleter> m_pluralRules;
    std::unique_ptr<UNumberFormat, UNumberFormatDeleter> m_numberFormat;

    String m_locale;
    UPluralType m_type { UPLURAL_TYPE_CARDINAL };
    unsigned m_minimumIntegerDigits { 1 };
    unsigned m_minimumFractionDigits { 0 };
    unsigned m_maximumFractionDigits { 3 };
    std::optional<unsigned> m_minimumSignificantDigits;
    std::optional<unsigned> m_maximumSignificantDigits;
};

} // namespace JSC

#endif // ENABLE(INTL)
