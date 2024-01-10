#include <exception>

#include "CLI11.hpp"
#include "deproj.h"
#include "file_utility.h"

CLI::App &init_main_app(CLI::App &app)
{
    app.set_version_flag("-v,--version", deproj::version());
    app.description("");

    auto opt_template = app.add_option("-t,--template", "Template file path");
    auto opt_output = app.add_option("-o,--output", "Output file path");
    auto opt_define = app.add_option("-D,--define", "Define a variable");

    opt_define->multi_option_policy(CLI::MultiOptionPolicy::TakeAll);

    app.final_callback([opt_template, opt_output, opt_define]() {
        auto template_path = opt_template->as<std::string>();
        auto output_path = opt_output->as<std::string>();
        auto defines = opt_define->as<std::vector<std::string>>();

        if (template_path.empty() || output_path.empty()) {
            throw CLI::CallForHelp();
        }

        try {
            if (!deproj::file_utility::exists(template_path)) {
                deproj::die(std::format("template file not found: {}", template_path));
            }

            deproj::variable_dict_type variables;
            for (const auto &define : defines) {
                auto pos = define.find('=');
                if (pos == std::string::npos) {
                    variables[define] = "";
                }

                auto key = define.substr(0, pos);
                auto value = define.substr(pos + 1);
                variables[key] = value;
            }

            auto template_content = deproj::file_utility::read(template_path);
            auto output_content = deproj::render(template_content, variables);
            deproj::file_utility::write(output_path, output_content);
        }
        catch (const std::exception &e) {
            deproj::die(e.what());
        }
    });

    return app;
}

int main(int argc, const char *argv[])
{
    CLI::App app;
    init_main_app(app);

    CLI11_PARSE(app, argc, argv);

    return 0;
}
