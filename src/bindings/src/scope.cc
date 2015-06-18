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

#include "scope.h"

JsScope::JsScope(
      const std::string& scope_id,
      const std::string& config_file)
      : runtime_(
          unity::scopes::Runtime::create(
            scope_id,
            config_file)) {
}
JsScope::~JsScope() {
}

v8::Handle<v8::Object> JsScope::scope_base() {
  // TODO: !!!! wrong object ownership management
  return v8cpp::export_object<ScopeBase>(Isolate::GetCurrent(), scope_base_.get());
}

void JsScope::run() {
  runtime_.run_scope(scope_base_.get());
}
