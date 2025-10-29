#pragma once

#include <quickjs.h>
#include <string>

class ScriptingCore {
public:
    ScriptingCore();
    ~ScriptingCore();

    void RunEval(const std::string& code);

private:
    JSRuntime* runtime;
    JSContext* context;
};