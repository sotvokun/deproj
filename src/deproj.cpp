#include "variable_visitor.h"
#include "inja.hpp"

#include "deproj.h"

namespace deproj {

string_type render(
    const string_type &template_content,
    const variable_dict_type &variables
)
{
    inja::Environment env;

    VariableVisitor variable_visitor;
    auto template_instance = env.parse(template_content);
    template_instance.root.accept(variable_visitor);

    inja::json data;
    for (const auto &variable : variable_visitor.variables()) {
        if (variables.find(variable) == variables.end()) {
            die(std::format("{}; variable not defined", variable));
        }
        auto var = variables.at(variable);
        if (var.empty()) {
            data[variable] = inja::json::boolean_t{true};
        } else {
            data[variable] = inja::json::string_t{var};
        }
    }

    return env.render(template_content, data);
}

}
