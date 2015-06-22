/*
 * Copyright 2015 Canonical Ltd.
 *
 * This file is part of unity-js-scopes.
 *
 * unity-js-scopes is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * unity-js-scopes is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "node.h"

#include <iostream>
#include <cstring>

#include <boost/filesystem.hpp>

namespace {
  const char kScopeInitPathArgumentHeader[] = "--scope=";
}

void usage() {
  std::cout << "unity-js-scopes-launcher "
            << kScopeInitPathArgumentHeader
            << "<path-to-ini-file>"
            << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    usage();
    return EXIT_FAILURE;
  }

  std::string ini_filename;
  for (int i = 0; i < argc; ++i) {
    std::string argument(argv[i]);
    if (argument.substr(0, sizeof(kScopeInitPathArgumentHeader)-1)
            == kScopeInitPathArgumentHeader) {
      ini_filename = argument.substr(sizeof(kScopeInitPathArgumentHeader)-1);
    }
  }

  if (ini_filename.empty()
      || !boost::filesystem::exists(ini_filename)) {
    std::cout << "Invalid or non existant scope ini file name";
    usage();
    return EXIT_FAILURE;
  }

  boost::filesystem::path p(ini_filename);

  if (p.extension().string() != ".ini") {
    std::cout << "Invalid scope ini file name extension "
              << ini_filename;
    return EXIT_FAILURE;
  }

  std::string base_name = p.filename().string();

  boost::filesystem::path script_path = p.parent_path();
  script_path += std::string("/") + p.stem().string() + ".js";

  if (!boost::filesystem::exists(script_path)) {
    std::cout << "Could not find scope javascript file";
    return EXIT_FAILURE;
  }

  std::vector<std::string::value_type>
    new_args_content(script_path.string().size() + 1);
  memcpy(&new_args_content[0],
         script_path.string().c_str(),
         new_args_content.size());

  std::vector<std::string::value_type*>
    new_args;
  new_args.push_back(&new_args_content[0]);

  return node::Start(
      new_args.size(),
      &new_args[0]);
}