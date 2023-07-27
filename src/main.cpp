#include "CLI11.hpp"
#include "inja.hpp"
#include "tmplt.h"
#include "variable_visitor.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>

std::string readFileContent(const std::string &path);
void writeFileContent(const std::string &path, const std::string &content);
inja::json interactiveBuildContext(const std::string &content);

struct AppOption {
  std::string inputTemplate;
  std::string outputPath;
};

int main(int argc, const char *argv[]) {
  CLI::App app;
  AppOption opt;

  app.set_version_flag("-v,--version", tmplt::version());
  app.add_option("TEMPLATE_NAME", opt.inputTemplate,
                 "Template that need to render")
      ->required();
  app.add_option("-o,--output", opt.outputPath, "Output path")
      ->default_val(std::filesystem::current_path())
      ->default_str("");

  CLI11_PARSE(app, argc, argv);

  if (!std::filesystem::is_regular_file(opt.inputTemplate)) {
    tmplt::die("Template file `" + opt.inputTemplate + "' not found");
    return 1;
  }

  std::filesystem::path inputPath(opt.inputTemplate);
  std::filesystem::path outputPath = opt.outputPath;
  if (std::filesystem::is_directory(outputPath)) {
    outputPath /= inputPath.filename();
  }

  auto templateContent = readFileContent(opt.inputTemplate);
  auto result =
      inja::render(templateContent, interactiveBuildContext(templateContent));

  try {
    writeFileContent(outputPath.string(), result);
    std::cout << "Rendered template to " << outputPath.string() << std::endl;
  } catch (std::exception &e) {
    tmplt::die(e.what());
  }

  return 0;
}

std::string readFileContent(const std::string &path) {
  if (!std::filesystem::is_regular_file(path) ||
      !std::filesystem::exists(path)) {
    tmplt::die("Template file `" + path + "' not found");
  }

  std::ifstream ifs(path);
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      (std::istreambuf_iterator<char>()));
  ifs.close();
  return content;
}

void writeFileContent(const std::string &filePath , const std::string &content) {
  std::ofstream ofs(filePath);
  ofs << content;
  ofs.close();
}

inja::json interactiveBuildContext(const std::string &content) {
  inja::json data;
  inja::Environment env;

  tmplt::VariableVisitor visitor;
  auto tmp = env.parse(content);
  tmp.root.accept(visitor);

  for (const auto &v : visitor.variables()) {
    std::cout << "Enter value for "
              << "\x1b[1m" << v << "\x1b[0m"
              << ": ";
    std::string value;
    std::cin >> value;
    data[v] = value;
  }

  return data;
}
