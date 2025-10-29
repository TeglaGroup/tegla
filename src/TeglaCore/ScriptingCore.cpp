#include "TeglaCore/ScriptingCore.h"

#include <iostream>

JSValue ScriptingCore::js_console_log(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
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

JSValue ScriptingCore::js_hook(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
    if (argc < 2) return JS_UNDEFINED;

    const char* name = JS_ToCString(ctx, argv[0]);
    if (!name) return JS_UNDEFINED;

    if (!JS_IsFunction(ctx, argv[1])) {
        JS_FreeCString(ctx, name);
        return JS_UNDEFINED;
    }

    ScriptingCore* self = (ScriptingCore*)JS_GetContextOpaque(ctx);

    auto cb = std::make_unique<JSCallback>();
    cb->ctx = ctx;
    cb->value = JS_DupValue(ctx, argv[1]);
    self->hooks[name].push_back(std::move(cb));

    JS_FreeCString(ctx, name);
    return JS_UNDEFINED;
}

ScriptingCore::ScriptingCore() {
    runtime = JS_NewRuntime();

    // no stack limit for now
    JS_SetMaxStackSize(runtime, 0);
    context = JS_NewContext(runtime);

    JS_SetContextOpaque(context, this);

    // add globals
    JSValue global = JS_GetGlobalObject(context);
    JSValue console = JS_NewObject(context);

    JS_SetPropertyStr(context, console, "log",
        JS_NewCFunction(context, js_console_log, "log", 1));
    JS_SetPropertyStr(context, global, "console", console);

    JS_SetPropertyStr(context, global,
        "hook", JS_NewCFunction(context, js_hook, "hook", 2));

    JS_FreeValue(context, global);
}

ScriptingCore::~ScriptingCore() {
    hooks.clear();

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

void ScriptingCore::FireEvent(const std::string& name, int argc, JSValueConst* argv) {
    auto it = hooks.find(name);
    if (it == hooks.end()) return;

    for (auto& cb : it->second) {
        if (!cb->active) continue;

        JSValue result = JS_Call(context, cb->value, JS_UNDEFINED, argc, argv);

        if (JS_IsException(result)) {
            JSValue exc = JS_GetException(context);
            const char* msg = JS_ToCString(context, exc);

            std::cerr << "JS exception in hook '" << name << "': " << msg << std::endl;

            JS_FreeCString(context, msg);
            JS_FreeValue(context, exc);
        }

        JS_FreeValue(context, result);
    }
}