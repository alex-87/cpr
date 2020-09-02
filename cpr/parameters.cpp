#include "cpr/parameters.h"

#include <initializer_list>
#include <string>

#include "cpr/util.h"

namespace cpr {

Parameters::Parameters(const std::initializer_list<Parameter>& parameters) {
    // Create a temporary CurlHolder for URL encoding:
    CurlHolder holder;
    for (const auto& parameter : parameters) {
        AddParameter(parameter, holder);
    }
}

void Parameters::AddParameter(const Parameter& parameter) {
    // Create a temporary CurlHolder for URL encoding:
    CurlHolder holder;
    AddParameter(parameter, holder);
}

void Parameters::AddParameter(const Parameter& parameter, const CurlHolder& holder) {
    if (!content.empty()) {
        content += "&";
    }

    std::string escapedKey = holder.urlEncode(parameter.key);
    if (parameter.value.empty()) {
        content += escapedKey;
    } else {
        std::string escapedValue = holder.urlEncode(parameter.value);
        content += escapedKey + "=" + escapedValue;
    }
}

} // namespace cpr
