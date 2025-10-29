#include "TeglaCore/ScriptingCore.h"

#include <iostream>

static JSValue js_console_log(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
    std::cout << "\033[34m";

    for (int i = 0; i < argc; i++) {
        const char* str = JS_ToCString(ctx, argv[i]);
        if (str) {
            std::cout << str;
            if (i < argc - 1)
                std::cout << " ";
            JS_FreeCString(ctx, str);
        }
    }

    std::cout << "\033[0m" << std::endl;
    return JS_UNDEFINED;
}

ScriptingCore::ScriptingCore() {
    runtime = JS_NewRuntime();

    // no stack limit for now
    JS_SetMaxStackSize(runtime, 0);
    context = JS_NewContext(runtime);

    // add globals
    JSValue global = JS_GetGlobalObject(context);
    JSValue console = JS_NewObject(context);

    JS_SetPropertyStr(context, console, "log",
        JS_NewCFunction(context, js_console_log, "log", 1));

    JS_SetPropertyStr(context, global, "console", console);

    JS_FreeValue(context, global);
}

ScriptingCore::~ScriptingCore() {
    JS_FreeContext(context);
    JS_FreeRuntime(runtime);
}

void ScriptingCore::RunEval(const std::string& code) {
    JSValue result = JS_Eval(context, code.c_str(), code.length(), "<eval>", JS_EVAL_TYPE_GLOBAL);

    if (JS_IsException(result)) {
        JSValue exception = JS_GetException(context);
        const char* errorMsg = JS_ToCString(context, exception);
        
        std::cerr << "JS script execption: " << errorMsg << std::endl;

        JS_FreeCString(context, errorMsg);
        JS_FreeValue(context, exception);
    }

    JS_FreeValue(context, result);
}